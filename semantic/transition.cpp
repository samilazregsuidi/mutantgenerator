#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "error.h"
#include "main.h"
#include "list.h"
#include "boolFct.h"
#ifdef CEGAR
	#include "predicate.h"
#endif
#include "stack.h"
#include "symbols.h"
#include "automata.h"
#include "SAT.h"
#ifdef CLOCK
	#include "clockZone.h"
#endif
#include "state.h"
#include "execution.h"

#ifdef PROFILE_STATE
	PROFILER_REGISTER(pr_stateOnStack, "stateOnStack", 200);
	PROFILER_REGISTER(pr_pr_stateDuplicate, "pr_stateDuplicate", 10);
#endif

/*
 * ACCESS AND MODIFICATION OF VARIABLES
 * * * * * * * * * * * * * * * * * * * * * * * */

ptFsmNode getNodePointer(ptState state, ptStateMask mask) {
	return  (ptFsmNode) *((void **) (((byte *)state->payload) + mask->offset - sizeof(ptFsmNode)));
}

void storeNodePointer(ptState state, ptStateMask mask, ptFsmNode pointer) {
	void ** ptr = (void **) (((byte*)state->payload) + mask->offset - sizeof(ptFsmNode));
	*ptr = pointer;
}

/**
 * state is necessary to evaluate the index of an array expression.
 * Give the offset of the variable referenced by a E_VARREF expression.
 * On first call, preOffset must have the same value as the offset of its environment (i.e. global or process).
 * /!\ process is the environment in which the variable is ANALYZED, NOT in the one the variable is DEFINED.
 */
unsigned int getVarOffset(ptSymTabNode globalSymTab, ptMTypeNode mtypes, ptState state, ptStateMask process, unsigned int preOffset, ptExpNode expression) {
	if(expression->type == E_RARG_VAR  || expression->type == E_EXPR_VAR) {
		return getVarOffset(globalSymTab, mtypes, state, process, preOffset, expression->children[0]);
	} else if(expression->type == E_VARREF) {
		unsigned int highOffset = getVarOffset(globalSymTab, mtypes, state, process, preOffset, expression->children[0]);
		if(!expression->children[1])
			return highOffset;
		else
			return getVarOffset(globalSymTab, mtypes, state, process, highOffset, expression->children[1]);
	} else if (expression->type == E_VARREF_NAME) {
		int index = 0;
		if(expression->children[0]) index = eval(globalSymTab, mtypes, state, process, expression->children[0], EVAL_EXPRESSION, ADD());
		if(expression->symTab->type == T_CHAN) {
			if(expression->symTab->capacity != 0) return preOffset + expression->symTab->memOffset + (expression->symTab->capacity * expression->symTab->memSize + 1) * index;
			else					  return preOffset + expression->symTab->memOffset + index;
		}
		else {
			return preOffset + expression->symTab->memOffset + expression->symTab->memSize * index;
		}
	}
	failure("Function getVarOffset is undefined for expression with type other than E_EXPR_VAR, E_RARG_VAR, E_VARREF and E_VARREF_NAME.\n"
			"The type of the encountered expression was: %d\n", expression->type);
	return 0; // only to please the Eclipse analyser
}


/**
 * Stores 'nb' bytes in a memory chunk, at offset 'offset'.
 * Those bytes are read from the byte array 'values'.
 * The array is not freed afterward.
 *
 * Does not change the payloadHash.
 */
void storeValues(void * chunk, unsigned int offset, int nb, byte * values) {
	byte* bytePtr = chunk + offset;
	int i;
	for(i = 0; i < nb; i++) *(bytePtr + i) = values[i];
}

/**
 * Reads 'nb' bytes in a memory chunk of the state, at offset 'offset', puts them in an array of byte and returns it.
 */
byte* readValues(void * chunk, unsigned int offset, int nb) {
	byte* bytePtr = chunk + offset;
	byte* values = (byte*) calloc(nb, sizeof(byte));
	if(!values) failure("Out of memory (creating byte array of size %d).\n", nb);
	int i;
	for(i = 0; i < nb; i++)
		values[i] = *(bytePtr + i);
	return values;
}

/*
 * Gets the value of ONE cells in a memory chunk of the state.
 */
int stateGetValue(void * chunk, unsigned int offset, int type) {
	byte* bytePtr;
	bytePtr = ((byte*)chunk) + offset;
	switch(getTypeSize(type)) {
		case (1):
			return *bytePtr;
		case (2):
			return *((short *) (bytePtr));
		case (4):
			return *((int *) (bytePtr));
	}
	return 0; // only to please the Eclipse analyser
}

/**
 * Sets the value of ONE cells in the memory chunk.
 *
 * Does not change the payloadHash.
 */
void stateSetValue(void * chunk, unsigned int offset, int type, int value) {
	byte* bytePtr;
	bytePtr = ((byte*)chunk) + offset;
	short * shortPtr = (short *)bytePtr;
	int * intPtr = (int *)bytePtr;
	switch(getTypeSize(type)) {
		case (1):
			*bytePtr = (byte) value;
			break;
		case (2):
			*shortPtr = (short) value;
			break;
		case (4):
			*intPtr = value;
			break;
	}
}

/**
 * Returns the stateMask of a given pid.
 */
ptStateMask maskLookup(ptState state, int pid) {
	ptStateMask mask = state->mask;
	while (mask->pid != pid) {
		mask = mask->next;
		if(!mask)
			return NULL;
	}
	return mask;
}

/**
 * Gets the symbol table of a channel by giving its offset in the memory chunk.
 * The structure contained in state->chanRefs is used to get the table.
 * If no channel exists at the given offset, returns NULL.
 */
ptSymTabNode getChannelSymTab(ptState state, unsigned int chanOffset) {
	ptChannelRef currentRef = state->chanRefs;
	int currentOffset;
	int i;
	while(currentRef) {
		for(i = 0; i < currentRef->symTab->bound; i++) {
			currentOffset = currentRef->channelOffset + (currentRef->symTab->capacity * currentRef->symTab->memSize + 1) * i;
			if(currentOffset == chanOffset)
				return currentRef->symTab;
		}
		currentRef = currentRef->next;
	}
	failure("[getChannelSymTab] Channel with offset %d does not exist.\n", chanOffset);
	return NULL;
}


/*
 * ACCESS AND MODIFICATION OF LARGE STATE CHUNKS
 * * * * * * * * * * * * * * * * * * * * * * * */

// TODO: differences between the three following functions?

/**
 * Helper for stateKillProctype and and initVariables
 */
void initSymTab(ptState state, unsigned int preOffset, ptSymTabNode var) {
	ptSymTabNode currentField = var;
	while(currentField) {
		if(currentField->init) stateSetValue(state->payload, preOffset + currentField->memOffset, currentField->type, currentField->init->iVal);
		if(currentField->type == T_UTYPE) initSymTab(state, preOffset + currentField->memOffset, currentField->utype->child);
		currentField = currentField->next;
	}
}

/**
 * Helper for stateCreateInitial and stateAddProctype
 *
 * Initialises all variables in a state.  The mask is used to get the symbol table.
 *
 * Does not change the payloadHash.
 */
void initVariables(ptState state, ptStateMask mask) {
	ptSymTabNode currentSTN;
	if(mask->pid == -1)	currentSTN = mask->process;
	else currentSTN = mask->process->fsm->symTab;
	initSymTab(state, mask->offset, currentSTN);
}

/**
 * Helper for stateAddProctype
 *
 * Initiate the bytes stored in a given chunk of memory.
 * Offset must be counted in bytes.
 */
void initValues(byte* startPtr, unsigned int offset, int bytesNbr, byte value) {
	int i;
	for (i = 0; i < bytesNbr; i++) *(startPtr + offset + i) = value;
}

/**
 * Helper for stateKillProctype
 *
 * Removes the channels references whose offset is between infBound and supBound (both included).
 */
void removeChannelRefs(ptState state, unsigned int infBound, unsigned int supBound) {
	if(!state->chanRefs) return;
	ptChannelRef freePtr = state->chanRefs;
	ptChannelRef currentRef = state->chanRefs;
	while(currentRef->channelOffset >= infBound && currentRef->channelOffset <= supBound) {
		state->chanRefs = state->chanRefs->next;
		delete(currentRef);
		currentRef = state->chanRefs;
	}
	while(currentRef->next) {
		if(currentRef->next->channelOffset >= infBound && currentRef->next->channelOffset <= supBound) {
			freePtr = currentRef->next;
			currentRef->next = currentRef->next->next;
			delete freePtr;
		}
		else	currentRef = currentRef->next;
	}
}

/**
 * Adds the global variables in the memory chunk.
 *
 * Does not set the payloadHash.
 */
ptState stateCreateInitial(ptSymTabNode globalSymTab, ptMTypeNode mtypes) {
	ptState newState = new tState();
	if(!newState) failure("Out of memory (creating State).\n");
	newState->nbProcesses = 0;
	newState->mask = new tStateMask();
	if(!newState->mask) failure("Out of memory (creating StateMask).\n");
	newState->mask->process = globalSymTab;
	newState->mask->pid = -1;
	newState->mask->offset = 0;
	newState->mask->context = NULL;
	newState->mask->next = NULL;
	newState->last = newState->mask;
	newState->lastStepPid = 0;
	newState->features = getTrue();
	newState->never = NULL;
	newState->chanRefs = NULL;
#ifdef CLOCK
	newState->zone = initClockZone();
	newState->zone = zoneResetAll(newState->zone);
	newState->invariant = NULL;
#endif
	ptSymTabNode variable = globalSymTab;
	newState->payloadHash = 0;
	newState->payloadSize = SYS_VARS_SIZE;
	while (variable) {
		if (variable->type == T_CHAN) {
			ptChannelRef oldRef = newState->chanRefs;
			newState->chanRefs = new tChannelRef();
			if(!newState->chanRefs) failure("Out of memory (creating channelRef).\n");
			newState->chanRefs->channelOffset = newState->payloadSize;
			newState->chanRefs->symTab = variable;
			newState->chanRefs->next = oldRef;
			if (variable->capacity != 0)
				newState->payloadSize += (1 + variable->memSize * variable->capacity) * variable->bound;
			else
				newState->payloadSize += variable->bound;
		}
		else if (variable->type != T_PROC && variable->type != T_TDEF)
			newState->payloadSize += variable->memSize * variable->bound;
		variable = variable->next;
	}
	// if(verbosity == VERBOSITY_HIGH) printf("Total memory used by global variables (in bytes): %d.\n", newState->payloadSize);
	newState->payload = calloc(1, newState->payloadSize);
	if(!newState->payload) failure("Out of memory (registering global variables).\n");

	/**
	 * Runs every process with the attribute "active".
	 * Cardinalities are taken into account.
	 * Also, links the "never claim" FSM, if it exists, with the state.
	 */
	ptSymTabNode symPtr = globalSymTab;
	int i;
	int bound;
	while(symPtr) {
		if(symPtr->type == T_PROC) {
			ptExpNode inst = symPtr->init;
			if(!inst)
				stateAddProctype(newState, symPtr, NULL, NULL, 0);
			else if(inst->type == E_EXPR_CONST) {
				bound = inst->iVal;
				for (i = 0; i < bound; i++) {
					stateAddProctype(newState, symPtr, NULL, NULL, 0);
				}
			}
			else if(inst->type == E_EXPR_COUNT) {
				if(!(inst->children[0]->children[0]->children[0] && inst->children[0]->children[0]->children[1]))
					failure("Bad syntax tree ?\n");
				ptSymTabNode container = lookupInSymTab(globalSymTab, inst->children[0]->children[0]->children[0]->sVal);
				if(container == NULL || container->type != T_UTYPE || container->utype == NULL)
					failure("Unknown feature in proctype cardinality (line %d).\n", inst->lineNb);
				ptSymTabNode feature = lookupInSymTab(container->utype->child, inst->children[0]->children[0]->children[1]->children[0]->sVal);
				ptSymTabNode a_symbol;
				char * path = feature2String(inst->children[0]->children[0], feature, &a_symbol, NULL);
				bound = a_symbol->bound;
				if(bound <= 1)
					stateAddProctype(newState, symPtr, path, inst->children[0]->children[0], 0);
				else {
					char * suffix = "";
					int length = strlen(path);
					char * mPath = (char *) malloc((length) * sizeof(char));
					if(path[length-1] == ']') {
						strncpy(mPath, path, length-3);
					}
					else {
						mPath = (char *) malloc((length) * sizeof(char));
						strncpy(mPath, path, length-9);
						suffix = ".is_in";
					}
					for (i = 0; i < bound; i++) {
						char * varName = (char *) malloc(length+2 * sizeof(char));
						snprintf(varName, length+2, "%s[%d]%s", mPath, i, suffix);
						stateAddProctype(newState, symPtr, varName, inst->children[0]->children[0], i);
					}
				}
			}
		else failure("Expression type is %s (line %d)\n", getExpTypeName(inst->type), inst->lineNb);
		}
		else if(symPtr->type == T_NEVER) stateAddNever(newState, symPtr);
		symPtr = symPtr->next;
	}

	// No process is executing something atomic
	stateSetValue(newState->payload, OFFSET_EXCLUSIVE, T_BYTE, NO_PROCESS);
	// No rendezvous has been requested.
	stateSetValue(newState->payload, OFFSET_HANDSHAKE, T_INT, NO_HANDSHAKE);
	initVariables(newState, newState->mask);
	return newState;
}

/**
 * Reserves some memory for the proctype variables in the memory chunk.
 * Returns the pid of the newly created process.
 *
 * Does not change the payloadHash.
 */
int stateAddProctype(ptState state, ptSymTabNode proctype, char * cname, ptExpNode cexp, int index) {
	if((!cname && cexp) || (cname && !cexp))
		failure("[stateAddProctype] Only cname or cexp is NULL.\n");
#ifdef DEBUGEXEC
	printf("[stateAddProctype] Context %s.\n", cname);
#endif
	ptStateMask newStateMask;
	// There's no hole in pids allocation: the new stateMask is added at the end of the list.
	newStateMask = new tStateMask();
	if(!state->mask) failure("Out of memory (creating StateMask).\n");
	state->last->next = newStateMask;
	newStateMask->pid = state->last->pid+1;
	newStateMask->next = NULL;
	state->last = newStateMask;
	newStateMask->offset = state->payloadSize + sizeof(ptFsmNode);
	newStateMask->process = proctype;
	ptContext context = NULL;
	if(cname && cexp) {
		context = new tContext();
		context->name = cname;
		context->expression = cexp;
		context->index = index;
	}
	newStateMask->context = context;
	// Need to reallocate memory of payload.
	ptSymTabNode variable = proctype->fsm->symTab;
	int newSize = 0;
	while(variable) {
		if(variable->type == T_CHAN) {
			ptChannelRef oldRef = state->chanRefs;
			state->chanRefs = new tChannelRef();
			if(!state->chanRefs) failure("Out of memory (creating channelRef).\n");
			state->chanRefs->channelOffset = newStateMask->offset + variable->memOffset;
			state->chanRefs->symTab = variable;
			state->chanRefs->next = oldRef;
			if (variable->capacity != 0)
				newSize += (1 + variable->memSize * variable->capacity) * variable->bound;
			else
				newSize += variable->bound;
		}
		else if (variable->type != T_PROC && variable->type != T_TDEF)
			newSize += variable->memSize * variable->bound;
		variable = variable->next;
	}
	state->payload = realloc(state->payload, state->payloadSize + newSize + sizeof(ptFsmNode));
	if(!state->payload) failure("Out of memory (registering process variables).\n");
	initValues((byte*)state->payload, state->payloadSize, newSize + sizeof(ptFsmNode), 0);
	state->nbProcesses++;
	state->payloadSize += newSize + sizeof(ptFsmNode);
	storeNodePointer(state, newStateMask, proctype->fsm->init);
	initVariables(state, newStateMask);
	return newStateMask->pid;
}

/**
 * Defines the never claim of the execution.
 *
 * Does not change the payloadHash.
 */
void stateAddNever(ptState state, ptSymTabNode neverSymTab) {
	state->never = new tStateMask();
	if(!state->never) failure("Out of memory (creating maks of never claim).\n");
	state->never->pid = -2;
	state->never->offset = SYS_VARS_SIZE;
	state->never->next = NULL;
	state->never->process = neverSymTab->fsm->symTab;
	state->never->context = NULL;
	storeNodePointer(state, state->never, neverSymTab->fsm->init);
}

/**
 * Tries to remove the process with a given pid.
 * If it succeeds then
 *  - the stateMask of the process is removed
 *  - the number of processes in the states updated
 *  - the chunk of memory of the process is removed from the state's payload.
 *
 * Does not change the payloadHash.
 */
void stateKillProctype(ptState state, int pid) {
	ptStateMask previous = state->mask;
	ptStateMask searchStateMask = state->last;
	if(searchStateMask->pid == pid) {
		/* Destroying the references of the channels that were declared in the killed process. */
		removeChannelRefs(state, searchStateMask->offset, state->payloadSize);
		while(previous->pid != searchStateMask->pid) {
			state->last = previous;
			previous = previous->next;
		}
		state->last->next = NULL;
		state->nbProcesses--;
		state->payloadSize = searchStateMask->offset - sizeof(ptFsmNode);
		state->payload = realloc(state->payload, state->payloadSize * sizeof(byte));
		if(!state->payload) failure("stateKillProctype: Error occurred while reducing the size of the state's payload.\n");
		searchStateMask->process = NULL;
		searchStateMask->next = NULL;
		delete(searchStateMask);
	}
}

/**
 * Tries to remove every terminated process. (See "stateKillProctype" for exact effect).
 */
void stateClean(ptState state) {
	while(state->last->pid >= 0 && !getNodePointer(state, state->last))
		stateKillProctype(state, state->last->pid);
}

/**
 * Frees the memory used by a given state. It does NOT free any symbol tables, FSM or mtypes list.
 * However, it DOES free:
 *  - the memory chunk,
 *  - all state masks of active processes,
 *  - the state mask of the never claim (if any),
 *  - all channel references,
 *
 * If the keepPayloadAndFeatures parameter is false, it also frees:
 *  - boolean formula and
 *  - the state structure itself.
 *
 * This parameter is only true when destroying a stack element where the payload and boolean function
 * are still used in the visited states hashtable.
 */
void stateDestroy(ptState state, byte keepPayloadAndFeatures) {
	if(state) {
		void* willy;
		ptStateMask maskPtr = state->mask;
		while(maskPtr) {
			willy = maskPtr;
			if(maskPtr->context) {
				free(maskPtr->context->name);
				delete(maskPtr->context);
			}
			maskPtr = maskPtr->next;
			delete(willy);
		}
		ptChannelRef chanPtr = state->chanRefs;
		while(chanPtr) {
			willy = chanPtr;
			chanPtr = chanPtr->next;
			delete(willy);
		}
		if(state->never) delete(state->never);
		if(!keepPayloadAndFeatures) {
			//destroyBool(state->features);
			free(state->payload);
#ifdef CLOCK
			zoneDestroy(state->zone);			// Time zone in which the state is reachable.
#endif
		}
#ifdef CLOCK
		if(state->invariant) zoneDestroy(state->invariant);
#endif
		delete state;
	}
}

/*
 * STATE PRINTING
 * * * * * * * * * * * * * * * * * * * * * * * */

void printChanState(ptMTypeNode mtypes, char varNameParent[200], byte* printedSomething, ptState state, ptState diffState, ptStateMask stateMask, ptSymTabNode channel, int varIndex, int processOffset);
void printfTypedefState(ptMTypeNode mtypes, char varNameParent[200], byte* printedSomething, ptState state, ptState diffState, ptStateMask stateMask, ptSymTabNode utypeFields, ptSymTabNode parent, int varIndex, int processOffset, int varOffset);

/**
 * Function for printing user types.
 */
void printfTypedefState(ptMTypeNode mtypes, char varNameParent[200], byte* printedSomething, ptState state, ptState diffState, ptStateMask stateMask, ptSymTabNode utypeFields, ptSymTabNode parent, int varIndex, int processOffset, int varOffset) {
	char varName[200];
	char varNameBase[200];
	int i, value;
	ptSymTabNode currentSTN = utypeFields;
	while(currentSTN) {
		sprintf(varNameBase, "%s.%s", varNameParent, currentSTN->name);
		for (i = 0; i < currentSTN->bound; i++) {
			if(currentSTN->bound > 1) sprintf(varName, "%s[%02d]", varNameBase, i);
			else sprintf(varName, "%s", varNameBase);

			int realOffset = varOffset + parent->memSize * varIndex  + currentSTN->memOffset + getTypeSize(currentSTN->type)*i;
			if (currentSTN->type == T_UTYPE) 	 printfTypedefState(mtypes, varName, printedSomething, state, diffState, stateMask, currentSTN->utype->child, currentSTN, i, processOffset, realOffset);
			else if (currentSTN->type == T_CHAN) printChanState(mtypes, varName, printedSomething, state, diffState, stateMask, currentSTN, i, processOffset);
			else {
				value = stateGetValue(state->payload, processOffset+realOffset, currentSTN->type);
				if(!diffState || value != stateGetValue(diffState->payload, processOffset+realOffset, currentSTN->type)){
					*printedSomething = 1;
					if(currentSTN->type == T_MTYPE) printf("   %-35s = %s\n", varName, getMTypeName(mtypes, value));
					else 							printf("   %-35s = %d\n", varName, value);
				}
			}
		}
		currentSTN = currentSTN->next;
	}
}

/**
 * Function for printing variables of type 'channel'.
 */
void printChanState(ptMTypeNode mtypes, char varNameParent[200], byte* printedSomething, ptState state, ptState diffState, ptStateMask stateMask, ptSymTabNode channel, int varIndex, int processOffset) {
	char varName[200];
	char varNameBase[200];
	int i, j, value, fieldNumber, realOffset;

	int channelOffset;
	if (channel->capacity != 0) channelOffset = channel->memOffset + (1 + channel->memSize * channel-> capacity) * varIndex;
	else						channelOffset = channel->memOffset + varIndex;

	ptSymTabNode symbol;
	for (i = 0; i < channel->capacity; i++) {
		fieldNumber = 0;
		symbol = channel->child;
		while(symbol) {
			sprintf(varNameBase, "%s.s%02d.f%02d", varNameParent, i, fieldNumber);

			for (j = 0; j < symbol->bound; j++) {
				if(symbol->bound > 1) sprintf(varName, "%s[%02d]", varNameBase, j);
				else sprintf(varName, "%s", varNameBase);

				realOffset = channel->memOffset + 1 + channel->memSize * varIndex * channel->capacity + varIndex + channel->memSize * i + symbol->memOffset + getTypeSize(symbol->type)* j;
				if (symbol->type == T_UTYPE) printfTypedefState(mtypes, varName, printedSomething, state, diffState, stateMask, symbol->utype->child, symbol, j, processOffset, realOffset);
				else {
					value = stateGetValue(state->payload, realOffset, symbol->type);
					if(!diffState || value != stateGetValue(diffState->payload, realOffset, symbol->type)) {
						*printedSomething = 1;
						if(symbol->type == T_MTYPE) printf("   %-35s = %s\n", varName, getMTypeName(mtypes, value));
						else 						printf("   %-35s = %d\n", varName, value);
					}
				}
			}
			fieldNumber++;
			symbol = symbol->next;
		}
	}
}

/**
 * General function for state printing.
 *
 * If the second parameter is provided, only values that are different from it will be printed.
 */
void printState(ptMTypeNode mtypes, ptState state, ptState diffState) {
	ptStateMask currentSM = state->mask;
	ptStateMask currentDiffSM = diffState ? diffState->mask : NULL;
	ptSymTabNode currentSTN;
	ptFsmNode node, diffnode = NULL;
	int offset, i, value;
	char varName[200];
	char varNameBase[200];

	byte printedSomething = 0;

	// printf("   %-30s = %u\n", "State hash", state->payloadHash);
	byte printFeature;
	if(trace == FULL_TRACE || !diffState) printFeature = 1;
	else if(state->features.Nil() && !diffState->features.Nil()) printFeature = 1;
	else if(!state->features.Nil() && diffState->features.Nil()) printFeature = 1;
	else {
		ADD diffNeg = negateBool(diffState->features, 0);
		ADD conjunct = addConjunction(diffNeg, state->features, 0, 1);
		printFeature = isSatisfiable(conjunct);
	}

	if(printFeature) {
		printedSomething = 1;
		printf("   %-35s = \n", "features");
		printBool(state->features);
	} else printf("/");
	
	printf("\n");
	
#ifdef CLOCK
	printZone(state->zone);
	printf("\n");
#endif
	if(state->never) {
		node = getNodePointer(state, state->never);
		if(trace == FULL_TRACE || !diffState || (node && node->flags & N_ACCEPT == N_ACCEPT)) {
			if(diffState && diffState->never) diffnode = getNodePointer(diffState, diffState->never);
			if(!diffnode || node != diffnode) {
				printedSomething = 1;
				if(node)	printf("   never                               @ NL%02d %s\n", node->lineNb, node->flags & N_ACCEPT == N_ACCEPT ? " (accepting)" : "");
				else 		printf("   never                               @ end\n");
			}
		}
	}

	while(currentSM) {
		if(currentDiffSM && currentDiffSM->pid != currentSM->pid) currentDiffSM = NULL;

		if(currentSM->pid != -1 && (trace == FULL_TRACE || !diffState)) {
			node = getNodePointer(state, currentSM);
			if(currentDiffSM) diffnode = getNodePointer(diffState, currentDiffSM);
			if(!currentDiffSM || node != diffnode) {
				printedSomething = 1;
				if(node) 	printf("   pid %02d, %-27s @ NL%02d\n", currentSM->pid, currentSM->process->name, node->lineNb);
				else 		printf("   pid %02d, %-27s @ end\n", 	currentSM->pid, currentSM->process->name);
			}
		}

		if(currentSM->pid == -1) currentSTN = currentSM->process;
		else currentSTN = currentSM->process->fsm->symTab;

		while(currentSTN) {
			if(currentSTN->type != T_PROC && currentSTN->type != T_TDEF && currentSTN->type != T_NEVER) {
				sprintf(varNameBase, "%s.%s", currentSM->pid == -1 ? "globals" : currentSM->process->name, currentSTN->name);

				for (i = 0; i < currentSTN->bound; i++) {
					if(currentSTN->bound > 1) sprintf(varName, "%s[%02d]", varNameBase, i);
					else sprintf(varName, "%s", varNameBase);

					if (currentSTN->type == T_UTYPE)	 printfTypedefState(mtypes, varName, &printedSomething, state, currentDiffSM ? diffState : NULL, currentSM, currentSTN->utype->child, currentSTN, i, currentSM->offset, currentSTN->memOffset);
					else if (currentSTN->type == T_CHAN) printChanState(mtypes, varName, &printedSomething, state, currentDiffSM ? diffState : NULL, currentSM, currentSTN, i, currentSM->offset);
					else {
						offset = currentSM->offset + currentSTN->memOffset + getTypeSize(currentSTN->type)*i;
						value = stateGetValue(state->payload, offset, currentSTN->type);
						if(!currentDiffSM || value != stateGetValue(diffState->payload, offset, currentSTN->type)) {
							printedSomething = 1;
							if(currentSTN->type == T_MTYPE) printf("   %-35s = %s\n", varName, getMTypeName(mtypes, value));
							else printf("   %-35s = %d\n", varName, value);
						}
					}
				}
			}
			currentSTN = currentSTN->next;
		}

		currentDiffSM = currentDiffSM ? currentDiffSM->next : NULL;
		currentSM = currentSM->next;
	}

	if(printedSomething) printf("    --\n");
}

/**
 * Debugging function: prints the raw bytes (as integers) of the payload
 */
void printPayload(ptState state) {
	int i;
	for(i = 0; i < state->payloadSize; i++) {
		printf("%u ", *(((byte*)state->payload)+i));
	}
	printf("\n\n");
}


/*
 * STATE DUPLICATION
 * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * Duplicates a list of stateMasks.
 */
ptStateMask stateMasksDuplicate(ptStateMask mask) {
	if(!mask) return NULL;
	ptStateMask copyMask = new tStateMask();
	if(!copyMask) failure("Out of memory (creating stateMask).\n");
	copyMask->process = mask->process;
	copyMask->pid = mask->pid;
	copyMask->offset = mask->offset;

	copyMask->context = NULL;
	if(mask->context) {
		copyMask->context = new tContext();
		copyMask->context->name = (char*) malloc(sizeof(char) * (strlen(mask->context->name)+1));
		strcpy(copyMask->context->name, mask->context->name);
		copyMask->context->expression = mask->context->expression;
		copyMask->context->index = mask->context->index;
	}
	if (mask->next) copyMask->next = stateMasksDuplicate(mask->next);
	else copyMask->next = NULL;
	return copyMask;
}

/**
 * Duplicates a list of chanRefs.
 */
ptChannelRef chanRefsDuplicate(ptChannelRef chanref) {
	if(!chanref) return NULL;
	ptChannelRef newRef = new tChannelRef();
	if(!newRef) failure("Out of memory (creating channelRef).\n");
	newRef->channelOffset = chanref->channelOffset;
	newRef->symTab = chanref->symTab;
	newRef->next = chanRefsDuplicate(chanref->next);
	return newRef;
}

/**
 * Duplicates a state.
 *
 * This function does NOT duplicate the boolean formula of the state.  This is because it is only
 * used in apply() and there the copy of the boolean formula is of no use.
 */
ptState stateDuplicate(ptState state) {
	if(!state) return NULL;
	#ifdef PROFILE_STATE
		PROFILER_START(pr_stateDuplicate);
	#endif

	ptState copy = new tState();
	if(!copy) failure("Out of memory (creating state).\n");
	copy->nbProcesses = state->nbProcesses;
	copy->payloadSize = state->payloadSize;
	copy->payloadHash = state->payloadHash;
	copy->payload = NULL;
	if(copy->payloadSize > 0) {
		copy->payload = malloc(copy->payloadSize);
		if(!copy->payload) failure("Out of memory (allocating state payload).\n");
		memcpy(copy->payload, state->payload, copy->payloadSize);
	}

	copy->lastStepPid = state->lastStepPid;
	//copy->features = NULL; // see function description
	copy->never = stateMasksDuplicate(state->never);
	copy->chanRefs = chanRefsDuplicate(state->chanRefs);

#ifdef CLOCK
	copy->zone = zoneCopy(state->zone);			// Time zone in which the state is reachable.
	copy->invariant = NULL;	// Will be updated during apply()
#endif

	// Copying processes information
	copy->mask = stateMasksDuplicate(state->mask);
	copy->last = copy->mask;
	if(copy->last) {
		while(copy->last->next) copy->last = copy->last->next;
	}

	#ifdef PROFILE_STATE
		PROFILER_END(pr_stateDuplicate);
	#endif
	return copy;
}


/*
 * STATE COMPARISON
 * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * Compares s1 a newly reached state
 *     with s2 a state known to be reachable
 * to see whether s1 is a state that was already visited.
 *
 * When s1 was not yet visited, then we say it's "fresh".
 *
 * Returns:
 * 	- STATES_DIFF 			 if s1 and s2 are totally different states, meaning s1 is fresh.
 * 	- STATES_SAME_S1_VISITED if s1 and s2 are identical but s2 is reachable by more products; hence, s1 adds nothing new
 *  - STATES_SAME_S1_FRESH	 if s1 and s2 are identical but s1 has products that were not explored with s2; hence, s1 is fresh
 */
byte stateCompare(ptState s1, void* s2Payload, const ADD& s2Features) {
	if(!s1 && !s2Payload) 										return STATES_SAME_S1_VISITED;
	if((s1 && !s2Payload) || (!s1 && s2Payload)) 				return STATES_DIFF;
	if(memcmp(s1->payload, s2Payload, s1->payloadSize) != 0)	return STATES_DIFF;

	// Now that we know both states are identical, we check whether:
	//  s1 -> s2
	//
	// If this holds, then s1 is reachable in less products, which means
	//                that it can be considered as visited.
	// It not,        then s1 is reachable by at least one product that
	//                was not previously explored, so it contains some
	//                fresh info, and exploration must continue.

#ifdef CLOCK
	return STATES_SAME_S1_VISITED;
#else
	// Convention: NULL means 'true'.
	if(!s2Features) return STATES_SAME_S1_VISITED;
	if(!s1->features) return STATES_SAME_S1_FRESH;	// Here we do not check the case in which s2->features != NULL but still a tautology;
													// There is a compilation parameter CHECK_TAUTOLOGY that can be set to check for
													// tautologies before they end up here.

	if(implies(s1->features, s2Features)) return STATES_SAME_S1_VISITED;
#endif
	return STATES_SAME_S1_FRESH;
}
