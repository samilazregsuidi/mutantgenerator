#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "error.h"
#include "main.h"
#include "list.h"
#include "stack.h"
#ifdef CEGAR
	#include "predicate.h"
#endif
#include "symbols.h"
#include "boolFct.h"
#include "automata.h"
#include "SAT.h"
#include "tvl.h"
#ifdef CLOCK
	#include "clockZone.h"
#endif
#include "state.h"
#include "execution.h"
#include "hashState.h"
#include "hashtableGen.h"
#include "../lib/RNGS/rngs.h"


#include <assert.h>

#ifdef PROFILE_EXEC
	PROFILER_REGISTER(pr_executables, "executables", 2000000);
	PROFILER_REGISTER(pr_apply, "apply", 1000000);
	PROFILER_REGISTER(pr_eval, "eval", 100000000);
	PROFILER_REGISTER(pr_checkEqualProps, "checkEqualProps", 1000000);
#endif

#define DYNAMIC_CHECK if(expression->iVal) 	{															\
			dynamicF = computeBoolFct(globalSymTab, mtypes, state, process, expression, flag, &foundFeature);		\
		if(!foundFeature) {																		\
			;																	\
		}																						\
		else {																					\
			return 1;																			\
		}																						\
	}


/*
 * APPLYING STATEMENTS
 * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * Performs a print statement from promela.  Helper for apply().
 * EFFECTS:
 * - Prints on standard out.
 * WARNING:
 * - argList->type must be equal to E_ARGLIST.
 */
void executePromelaPrint(ptSymTabNode globalSymTab, ptMTypeNode mtypes, char * message, ptExpNode argNode, ptState state, ptStateMask process) {
	if (!message) return;
	ptList argList = NULL;
	int argc = 0;
	ptExpNode currentArg = argNode;
	while(currentArg) {
		argc++;
		currentArg = currentArg->children[1];
	}
	int argi[argc];
	currentArg = argNode;
	int i = 0;
	while(currentArg) {
		argi[i] = eval(globalSymTab, mtypes, state, process, currentArg->children[0], EVAL_EXPRESSION, ADD());
		argList = listAdd(argList, &(argi[i]));
		i++;
		currentArg = currentArg->children[1];
	}
	i = 0;
	int j = 0;
	while(message[j]) {
		switch(message[j]) {
			case('%'):
				j++;
				switch(message[j]) {
					case('c'):
						printf("%c",argi[i]);
						i++;
						break;
					case('d'):
						printf("%d",argi[i]);
						i++;
						break;
					case('e'):
						printf("%s",getMTypeName(mtypes, argi[i]));
						i++;
						break;
					case('o'):
						printf("%o",argi[i]);
						i++;
						break;
					case('u'):
						printf("%u",argi[i]);
						i++;
						break;
					case('x'):
						printf("%x",argi[i]);
						i++;
						break;
				}
			break;

			case('\\'):
				j++;
				switch(message[j]) {
					case('a'):	printf("\a"); break;
					case('b'):	printf("\b"); break;
					case('f'):	printf("\f"); break;
					case('n'):	printf("\n"); break;
					case('r'):	printf("\r"); break;
					case('t'):	printf("\t"); break;
					case('v'):	printf("\v"); break;
					case('\\'):	printf("\\"); break;
				}
				break;

			default: printf("%c", message[j]);
		}
		j++;
	}
	listDestroy(argList);
}



/*
 * CHANNEL HELPERS
 * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * Returns a given channel 'len' (i.e. the number of messages stored in the channel).
 * EFFECTS: None.
 */
byte channelLen (ptSymTabNode globalSymTab, ptMTypeNode mtypes, ptState state, ptStateMask process, ptExpNode channelVar) {
	ptSymTabNode prefix = expressionSymbolLookUpLeft(channelVar);
	ptSymTabNode channel = expressionSymbolLookUpRight(channelVar);
	unsigned int offset;
	// Looking up if the variable is global or local to the process.
	if(prefix->global == 0)
		offset = getVarOffset(globalSymTab, mtypes, state, process, process->offset, channelVar);
	else
		offset = getVarOffset(globalSymTab, mtypes, state, process, 0, channelVar);
	if(channel->type == T_CID) offset = stateGetValue(state->payload, offset, T_CID);
	// The len value is stored in the payload, at the offset of the channel.
	return *((byte*) state->payload + offset);
}

/**
 * Gets the first message in the channel.
 *
 * EFFECTS:
 * 	- Modifies the payload by changing the value of some variable passed as argument for the reception.
 * WARNING:
 * 	This function does NOT check if there really is a message stored in the channel
 * 	and if the arguments of the polling respects the size and type of the parameters.
 */
void channelPoll(ptSymTabNode globalSymTab, ptMTypeNode mtypes, ptState state, ptStateMask process, ptExpNode expression) {
	ptExpNode channelVar = expression->children[0];
	ptSymTabNode prefix = expressionSymbolLookUpLeft(channelVar);
	ptSymTabNode channel = expressionSymbolLookUpRight(channelVar);
	unsigned int chanOffset;
	// Looking up if the variable is global or local to the process.
	if(prefix->global == 0)
		// local variable
		chanOffset = getVarOffset(globalSymTab, mtypes, state, process, process->offset, channelVar);
	else
		chanOffset = getVarOffset(globalSymTab, mtypes, state, process, 0, channelVar);
	ptSymTabNode messageFields;
	// If the channel's symbol represents a reference, it is replace by the true channel's symbol.
	if(channel->type == T_CID) {
		chanOffset = stateGetValue(state->payload, chanOffset, T_CID);
		channel = getChannelSymTab(state, chanOffset);
	}
	if(!channel)	failure("channelPoll/channelReceive: The given offset (%d) does not reference any existing channel.\n", chanOffset);
	messageFields = channel->child;
	chanOffset += 1;
	ptSymTabNode symbol;
	ptExpNode argList = expression->children[1];
	ptExpNode arg;
	unsigned int argOffset;
	byte * values;
	if (channel->capacity == 0)	chanOffset = 0; // As we're looking in the handshake chunk of memory, we must start reading at the beginning.
	// Every variable passed as argument of the reception has to be filled with the send value.
	while(messageFields) {
		arg = argList->children[0];
		symbol = expressionSymbolLookUpLeft(arg);
		if(!arg)	failure("Argument list has one NULL argument.\n");
		if(arg->type == E_RARG_VAR && (symbol)) {
			if(symbol->global == 0)
				argOffset = getVarOffset(globalSymTab, mtypes, state, process, process->offset, arg);
			else
				argOffset = getVarOffset(globalSymTab, mtypes, state, process, 0, arg);
			if (channel->capacity == 0) values = readValues(_handshake_transit, chanOffset, symbol->memSize);
			else values = readValues(state->payload, chanOffset, symbol->memSize);
			storeValues(state->payload, argOffset, symbol->memSize, values);
			free(values);
		}
		chanOffset += messageFields->memSize;
		messageFields = messageFields->next;
		argList = argList->children[1];
	}
}

/**
 * Stores a message in a given channel.
 *
 * EFFECTS:
 * 	- Modifies the state payload OR _handshake_transit by storing the message field.
 * 	- Modifies the state payload by incrementing the 'len' value of the concerned channel (EVEN in the
 * 	handshake case).
 * WARNING:
 * 	The message is supposed to fit the type and capacity constraints.
 * 	channelVar must refer to an ExpNode of type E_VARREF or E_VAR_NAME that
 * 	itself refers to a channel.
 */
void channelSend(ptSymTabNode globalSymTab, ptMTypeNode mtypes, ptState state, ptStateMask process, ptExpNode expression) {
	ptExpNode channelVar = expression->children[0];
	ptSymTabNode prefix = expressionSymbolLookUpLeft(channelVar);
	ptSymTabNode channel = expressionSymbolLookUpRight(channelVar);
	unsigned int offset;
	// Looking up if the variable is global or local to the process.
	if(prefix->global == 0)
		offset = getVarOffset(globalSymTab, mtypes, state, process, process->offset, channelVar); // local variable
	else
		offset = getVarOffset(globalSymTab, mtypes, state, process, 0, channelVar);
	if(channel->type == T_CID) {
		offset = stateGetValue(state->payload, offset, T_CID);
		channel = getChannelSymTab(state, offset);
	}
	byte* len = (byte*) (state->payload + offset);
	// If the channel's symbol represents a reference, it is replace by the true channel's symbol.
	offset += 1;
	// We points the first message stored in the channel.
	int messageSize = channel->memSize;
	if(channel->capacity == 0) {
		_handshake_transit = malloc(channel->memSize);
		offset = 0;
	}
	else offset += messageSize * (*len);
	// We points the memory cell to store the message.
	ptSymTabNode messageFields = channel->child;
	if(!messageFields)	failure("channelSend: The given offset does not reference any existing channel.\n");
	ptExpNode argList = expression->children[1];
	ptExpNode arg;
	ptSymTabNode var;
	unsigned int varOffset;
	int i;
	// The value of every field has to be stored in the part of the state payload allocated to the channel,
	// or in the _handshake_transit chunk of memory (if the channel is used for handshakes).
	while(messageFields) {
		if(!argList) failure("channelSend: arguments number does not fit parameters number.\n");
		arg = argList->children[0];
		var = expressionSymbolLookUpLeft(arg);
		if(var) {
			if (var->global == 0)
				varOffset = getVarOffset(globalSymTab, mtypes, state, process, process->offset, arg);
			else
				varOffset = getVarOffset(globalSymTab, mtypes, state, process, 0, arg);
			if (messageFields->type == T_CID || messageFields->type == T_CHAN) {
				if(messageFields->type == T_CID) {
					varOffset = stateGetValue(state->payload, varOffset, T_CID);
				}
				if(channel->capacity == 0) stateSetValue(_handshake_transit, offset, T_CID, varOffset);
				else stateSetValue(state->payload, offset, T_CID, varOffset);
			}
			else {
				byte* values = readValues(state->payload, varOffset, messageFields->memSize);
				if(channel->capacity == 0) storeValues(_handshake_transit, offset, messageFields->memSize, values);
				else storeValues(state->payload, offset, messageFields->memSize, values);
				free(values);
			}
		} else {
			if(channel->capacity == 0) stateSetValue(_handshake_transit, offset, messageFields->type, eval(globalSymTab, mtypes, state, process, arg, EVAL_EXPRESSION, ADD()));
			else stateSetValue(state->payload, offset, messageFields->type, eval(globalSymTab, mtypes, state, process, arg, EVAL_EXPRESSION, ADD()));
		}
		offset += messageFields->memSize;
		messageFields = messageFields->next;
		argList = argList->children[1];
	}
	(*len)++;
}

/**
 * Gets AND removes the first message of the channel.
 *
 * EFFECTS:
 * 	- Modifies the payload by changing the value of some variable passed as argument for the reception.
 * 	- Modifies the payload by decrementing the 'len' value of the channel (EVEN in the handshake case).
 * WARNING:
 * 	This function does NOT check if there really is a message stored in the channel.
 * 	channelVar must refer to an ExpNode of type E_VARREF or E_VAR_NAME that
 * 	itself refers to a channel.
 */
void channelReceive(ptSymTabNode globalSymTab, ptMTypeNode mtypes, ptState state, ptStateMask process, ptExpNode expression) {
	ptExpNode channelVar = expression->children[0];
	channelPoll(globalSymTab, mtypes, state, process, expression);
	// As it is a standard reception, the message must be 'removed' from the channel.
	// To do so, we simply decrease the 'len' value of the channel.
	ptSymTabNode prefix = expressionSymbolLookUpLeft(channelVar);
	ptSymTabNode channel = expressionSymbolLookUpRight(channelVar);
	unsigned int offset;
	// Looking up if the variable is global or local to the process.
	if(prefix->global == 0)
		offset = getVarOffset(globalSymTab, mtypes, state, process, process->offset, channelVar);
	else
		offset = getVarOffset(globalSymTab, mtypes, state, process, 0, channelVar);
	if(channel->type == T_CID) {
		offset = stateGetValue(state->payload, offset, T_CID);
		channel = getChannelSymTab(state, offset);
	}
	if(channel->capacity == 0 && _handshake_transit) {
		free(_handshake_transit);
		_handshake_transit = NULL;
		byte* len = (byte*) (state->payload + offset);
		(*len)--;
	}
	else {
		byte* len = (byte*) (state->payload + offset);
		(*len)--;
		offset +=1;
		byte* startPtr = (((byte*) state->payload) + offset);
		byte* nextPtr = startPtr + channel->memSize;
		int i;
		for (i = 0; i < channel->memSize * (*len) ; i++)
			*(startPtr + i) = *(nextPtr + i);
		// The empty space generated by the removal must be filled with 0.
		for(i = 0; i < channel->memSize; i++)
			*(startPtr + i + channel->memSize * (*len)) = 0;
	}
}


/**
 * Returns 0 iff a given channel has no message stored.
 * EFFECTS: None.
 */
byte channelIsEmpty(ptSymTabNode globalSymTab, ptMTypeNode mtypes, ptState state, ptStateMask process, ptExpNode channel) {
	return (channelLen(globalSymTab, mtypes, state, process, channel) == 0);
}

/**
 * Returns 0 iff a given channel has its buffer full.
 * EFFECTS: None.
 */
byte channelIsFull(ptSymTabNode globalSymTab, ptMTypeNode mtypes, ptState state, ptStateMask process, ptExpNode channelVar) {
	ptSymTabNode prefix = expressionSymbolLookUpLeft(channelVar);
	ptSymTabNode channel = expressionSymbolLookUpRight(channelVar);
	unsigned int offset;
	// Looking up if the variable is global or local to the process.
	if(prefix->global == 0)
		offset = getVarOffset(globalSymTab, mtypes, state, process, process->offset, channelVar);
	else
		offset = getVarOffset(globalSymTab, mtypes, state, process, 0, channelVar);
	if(channel->type == T_CID) {
		offset = stateGetValue(state->payload, offset, T_CID);
		channel = getChannelSymTab(state, offset);
	}
	// The len value is stored in the payload, at the offset of the channel.
	int len = *((byte*) state->payload + offset);
	return (len == channel->capacity);
}

ADD computeBoolFct(ptSymTabNode globalSymTab, ptMTypeNode mtypes, ptState state, ptStateMask process, ptExpNode expression, byte flag, byte * foundFeature) {
		if(!state || !process || !expression)
			return ADD();
#ifdef DEBUGEXEC
		printf("[computeBoolFct] Expression (%s) at line %d\n", getExpTypeName(expression->type), expression->lineNb);
#endif
		ADD addedFeatures_;
		tExpression2BoolReturn result;
		ADD formula;
		ADD formula2;
		ptSymTabNode symbol;
		ptExpNode tExp = NULL;
		ptExpNode aExp = NULL;
		byte foundSubFeature1 = 0;
		byte foundSubFeature2 = 0;
		unsigned int handshake = stateGetValue(state->payload, OFFSET_HANDSHAKE, T_INT);
		if(flag == EVAL_EXECUTABILITY && handshake != NO_HANDSHAKE && expression->type != E_STMNT_CHAN_RCV) return ADD();
		else {
			switch(expression->type) {
				case(E_STMNT_EXPR):
					formula = computeBoolFct(globalSymTab, mtypes, state, process, expression->children[0], flag, foundFeature);
					return formula;
				case(E_EXPR_PAR):
					return computeBoolFct(globalSymTab, mtypes, state, process, expression->children[0], flag, foundFeature);

				case(E_EXPR_GT):
				case(E_EXPR_LT):
				case(E_EXPR_GE):
				case(E_EXPR_LE):
				case(E_EXPR_EQ):
				case(E_EXPR_NE):
					if(expression->children[1]->type == E_EXPR_COUNT) {
							failure("[computeBoolFct] Multiplicity of features can only occur at left-hand side (line %d).\n", expression->lineNb);
					}
					if(expression->children[0]->type == E_EXPR_COUNT) {
						int countValue;
						if(expression->children[1]->type == E_EXPR_COUNT)
							failure("[computeBoolFct] Multiplicity of features cannot be compared.\n");
						result = expression2Bool(expression->children[0], globalSymTab);
						countValue = eval(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD());

						*foundFeature = 1;
						char varName[strlen(result.symbol->name)+13];
						char * suffix;
						if(result.symbol->type == T_FEAT)
							suffix = "";
						else
							suffix = ".is_in";
						switch(expression->type) {
							case(E_EXPR_GT):
								if(countValue >= result.symbol->bound)
									return getFalse();
								else if(countValue >= 0) { /* If #F > 3 then F[3].is_in is required */
									snprintf(varName, sizeof(varName), "%s[%d]%s", result.symbol->name, countValue, suffix);
									return createVariable(varName);
								}
								else result.boolFctResult = getTrue();

							case(E_EXPR_LT):
								if(countValue <= 0)
									return getFalse();
								else if(countValue <= result.symbol->bound) { /* If #F < 3 then F[2].is_in is forbidden */
									snprintf(varName, sizeof(varName), "%s[%d]%s", result.symbol->name, countValue-1, suffix);
									return negateBool(createVariable(varName), 0);
								}
								else result.boolFctResult = getTrue();

							case(E_EXPR_GE):
								if(countValue > result.symbol->bound)
									return getFalse();
								else if(countValue > 0) { /* If #F >= 3 then F[2].is_in is required */
									snprintf(varName, sizeof(varName), "%s[%d]%s", result.symbol->name, countValue-1, suffix);
									return createVariable(varName);
								}
								else result.boolFctResult = getTrue();

							case(E_EXPR_LE):
								if(countValue < 0)
									return getFalse();
								else if(countValue <= result.symbol->bound) { /* If #F <= 3 then F[3].is_in is forbidden */
									snprintf(varName, sizeof(varName), "%s[%d]%s", result.symbol->name, countValue, suffix);
									return negateBool(createVariable(varName), 0);
								}
								else result.boolFctResult = getTrue();

							case(E_EXPR_EQ):
								if(countValue < 0 || countValue > result.symbol->bound)
									return getFalse();
								else { /* If #F = 3 then F[2].is_in is required and F[3].is_in is forbidden */
									snprintf(varName, sizeof(varName), "%s[%d]%s", result.symbol->name, countValue-1, suffix);
									formula = createVariable(varName);
									snprintf(varName, sizeof(varName), "%s[%d]%s", result.symbol->name, countValue, suffix);
									formula = addConjunction(formula, negateBool(createVariable(varName), 0), 0, 0);
								}
							case(E_EXPR_NE):
								if(countValue < 0 || countValue > result.symbol->bound)
									return getTrue();
								else { /* If #F != 3 then F[2].is_in is forbidden or F[3].is_in is required */
									snprintf(varName, sizeof(varName), "%s[%d]%s", result.symbol->name, countValue-1, suffix);
									formula = createVariable(varName);
									snprintf(varName, sizeof(varName), "%s[%d]%s", result.symbol->name, countValue, suffix);
									formula = negateBool(addConjunction(formula, negateBool(createVariable(varName), 0), 0, 0), 0);
								}
						}
					}
#ifndef ATTR
					else return ADD();
#else
				case(E_EXPR_PLUS):
				case(E_EXPR_MINUS):
				case(E_EXPR_TIMES):
				case(E_EXPR_DIV):
				case(E_EXPR_MOD):
				case(E_EXPR_UMIN):

					formula = computeBoolFct(globalSymTab, mtypes, state, process, expression->children[0], flag, &foundSubFeature1);
					formula2 = computeBoolFct(globalSymTab, mtypes, state, process, expression->children[1], flag, &foundSubFeature2);
					if(foundSubFeature1 || foundSubFeature2)
						formula = createConstraintVar(formula, formula2, expression->type);
					else
						formula = ADD();
					*foundFeature = foundSubFeature1 || foundSubFeature2;
					return formula;
#endif

				case(E_EXPR_AND):
				case(E_EXPR_OR):
					formula = computeBoolFct(globalSymTab, mtypes, state, process, expression->children[0], flag, &foundSubFeature1);
					formula2 = computeBoolFct(globalSymTab, mtypes, state, process, expression->children[1], flag, &foundSubFeature2);
					if(!foundSubFeature1 && foundSubFeature2)
						failure("[computeBoolFct] Feature expression cannot be composed with other statements (line %d).\n", expression->lineNb);
					if(!foundSubFeature2 && foundSubFeature1)
						failure("[computeBoolFct] Feature expression cannot be composed with other statements (line %d).\n", expression->lineNb);
					*foundFeature = foundSubFeature1 || foundSubFeature2;
					return !(*foundFeature) ? ADD() : (expression->type == E_EXPR_AND) ? addConjunction(formula, formula2, 0, 0) : addDisjunction(formula, formula2, 0, 0);


				case(E_EXPR_NEG):
					formula = computeBoolFct(globalSymTab, mtypes, state, process, expression->children[0], flag, foundFeature);
					return *foundFeature ? negateBool(formula, 0) : ADD();

				case(E_EXPR_VAR):
					return computeBoolFct(globalSymTab, mtypes, state, process, expression->children[0], flag, foundFeature);
#ifdef ATTR
				case(E_EXPR_CONST):
					return createConstant(expression->iVal);
#endif
				case(E_VARREF):
				{
					aExp = expression;
					byte changedChild1 = 0;
					if(expression->iVal && process->context) { // Context-dependent feature
						//char * cpath = (char *) malloc(strlen(process->context->name) * sizeof(char));
						tExp = process->context->expression;
						while(tExp->children[1]) {
							tExp = tExp->children[1];
						}
						tExp->children[1] = expression;
						if(!tExp->children[0]->children[0]) {
							tExp->children[0]->children[0] = createExpNode(E_EXPR_CONST,  NULL, process->context->index, NULL, NULL, NULL, 0, NULL, NULL);
							changedChild1 = 1;
						}
						aExp = process->context->expression;
					}
					symbol = expressionSymbolLookUpLeft(aExp);
					if(symbol == NULL || symbol->type != T_UTYPE || symbol->utype == NULL) {
#ifdef ATTR
						return createConstant(eval(globalSymTab, mtypes, state, process, expression, flag, ADD()));
#else
						//failure("[computeBoolFct] Comparison between features and variables without Z3 is not allowed (line %d).\n", aExp->lineNb);
						*foundFeature = 0;
						return ADD();
#endif
					}
					ptSymTabNode feature = lookupInSymTab(symbol->utype->child, aExp->children[1]->children[0]->sVal);
					if(!feature) failure("[computeBoolFct] Could not find feature symbol %s.\n", aExp->children[1]->children[0]->sVal);
					if(feature->type != T_FEAT && feature->type != T_UFEAT) {
#ifdef ATTR
						return createConstant(eval(globalSymTab, mtypes, state, process, expression, flag, ADD()));
#else
						*foundFeature = 0;
						return ADD();
#endif
					}
					else if(feature->type == T_UFEAT) {
						*foundFeature = 1;
						int type;
						char * path;
						char * featurePath;
						path = feature2String(aExp, feature, NULL, &type);
						if(expression->iVal && process->context) {
							if(changedChild1) {
								destroyExpNode(tExp->children[0]->children[0]);
								tExp->children[0]->children[0] = NULL;
							}
							tExp->children[1] = NULL;
						}
						if(type == T_BOOL || type == T_FEAT || type == T_UFEAT || type == T_UTYPE) {
							ADD res = createVariable(path);
							free(path);
							return res;
						}
						else if(type == T_INT) {
#ifndef ATTR
							failure("[computeBoolFct] Feature attributes are not allowed in this version of ProVeLines (line %d).\n", aExp->lineNb);
#else
							ADD res = createAttribute(path);
							free(path);
							return res;
#endif
						}
						else
							failure("[computeBoolFct] Unknown attribute type (%s) at line %d.\n", getTypeName(type), aExp->lineNb);
					}
					break;
				}
				case(E_EXPR_COUNT):
					failure("[computeBoolFct] Unexpected occurrence of clones count (E_EXPR_COUNT) at line %d\n", expression->lineNb);

				default:
					if(foundFeature)
						*foundFeature = 0;
					return ADD();//failure("[computeBoolFct] Unexpected expression in Boolean function at line %d\n", expression->lineNb);
			}
		}
	}


/*
 * EXPRESSION EVALUATION
 * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * Evaluates an expression according to the PROMELA semantics.
 * The process given by the stateMask gives the local namespace in which the
 * the expression is evaluated.
 *
 * 'flag' is used to determine what is evaluated.
 * 	- EVAL_EXECUTABILITY when evaluating the executability.
 * 	- EVAL_EXPRESSION when evaluating the value of an expression.
 *
 * EFFECTS:
 * 	- When the expression is a handshake request and no other handshake request is being evaluated,
 * 	modifies the HANDSHAKE value in the payload.
 */
static byte _timeout = 0;
static byte _else = 0;
int eval(ptSymTabNode globalSymTab, ptMTypeNode mtypes, ptState state, ptStateMask process, ptExpNode expression, byte flag, const ADD& dynamicF) {
	if(!expression)	return 0;
#ifdef DEBUGEXEC
	printf("[eval] Expression %s at line %d\n", getExpTypeName(expression->type), expression->lineNb);
#endif
	#ifdef PROFILE_EXEC
		PROFILER_START(pr_eval);
	#endif
	byte foundFeature = 0;
	unsigned int offset, chanOffset;
	int returnValue = -1;
	ptSymTabNode channel, symbol;
	unsigned int handshake = stateGetValue(state->payload, OFFSET_HANDSHAKE, T_INT);
	if(flag == EVAL_EXECUTABILITY && handshake != NO_HANDSHAKE && expression->type != E_STMNT_CHAN_RCV) returnValue = 0;
	else {
		switch(expression->type) {
#ifdef CLOCK
			case(E_STMNT_WHEN):
			case(E_STMNT_WAIT):
				failure("[eval] Guard and invariant statements cannot be evaluated (line %d).\n", expression->lineNb);
#endif

			case(E_DECL):
				returnValue = 1;
				break;

			case(E_STMNT):
				returnValue = eval(globalSymTab, mtypes, state, process, expression->children[0], flag, dynamicF);
				break;

			case(E_STMNT_CHAN_RCV):
				symbol = expressionSymbolLookUpLeft(expression->children[0]);
				channel = expressionSymbolLookUpRight(expression->children[0]);
				if(symbol->global == 0)
					chanOffset = getVarOffset(globalSymTab, mtypes, state, process, process->offset, expression->children[0]);
				else
					chanOffset = getVarOffset(globalSymTab, mtypes, state, process, 0, expression->children[0]);
				if(channel->type == T_CID) {
						chanOffset = stateGetValue(state->payload, chanOffset, T_CID);
						channel = getChannelSymTab(state, chanOffset);
				}
				if(!channel) {
					printState(mtypes, state, NULL);
					failure("ERROR (eval (E_STMNT_CHAN_RCV, line %02d)): chanOffset (%d) does not reference any existing channel.\n", expression->lineNb, chanOffset);
				}
				if (channel->capacity == 0) {
					if(handshake != chanOffset)
						// Handshake request does not concern the channel.
						return 0;
				}
				if (channelIsEmpty(globalSymTab, mtypes, state, process, expression->children[0]))
					return 0;
				else {
					// Either a rendezvous concerns the channel, either the channel has a non null capacity and is not empty.
					ptExpNode currentArg = expression->children[1];
					ptSymTabNode param = channel->child;
					int varOffset;
					int sendValue;
					byte stop = 0;
					while(currentArg && !stop) {
						if(!param) failure("[eval] channelReceive: Argument numbers does not match with the parameters number.\n");
						if(currentArg->children[0]->type != E_RARG_VAR) {
							if(channel->capacity == 0) {
								varOffset = param->memOffset;//chanOffset + param->memOffset + 1;
								sendValue = stateGetValue(_handshake_transit, varOffset, param->type);
							} else {
								varOffset = chanOffset + param->memOffset + 1;
								sendValue = stateGetValue(state->payload, varOffset, param->type);
							}

							if (eval(globalSymTab, mtypes, state, process, currentArg->children[0], flag, ADD()) != sendValue) {
								returnValue = 0;
								stop = 1;
							}
						} else {
							symbol = expressionSymbolLookUpLeft(currentArg->children[0]);
							if (!symbol) {
								if(channel->capacity == 0) {
									varOffset = param->memOffset;//chanOffset + param->memOffset + 1;
									sendValue = stateGetValue(_handshake_transit, varOffset, param->type);
								} else {
									varOffset = chanOffset + param->memOffset + 1;
									sendValue = stateGetValue(state->payload, varOffset, param->type);
								}

								returnValue = eval(globalSymTab, mtypes, state, process, currentArg->children[0], EVAL_EXPRESSION, ADD());
								if (returnValue != -1 && returnValue != sendValue) {
									returnValue = 0;
									stop = 1;
								}
							}
						}
						param = param->next;
						currentArg = currentArg->children[1];
					}
					if(!stop) returnValue = 1;
				}
				break;

			case(E_STMNT_CHAN_SND):
				symbol = expressionSymbolLookUpLeft(expression->children[0]);
				channel = expressionSymbolLookUpRight(expression->children[0]);
				if(symbol->global == 0)	offset = getVarOffset(globalSymTab, mtypes, state, process, process->offset, expression->children[0]);
				else	offset = getVarOffset(globalSymTab, mtypes, state, process, 0, expression->children[0]);
				// If the symbol represents a reference to a channel, it is replaced by the true channel's symbol.
				if(channel->type == T_CID) {
					offset = stateGetValue(state->payload, offset, T_CID);
					channel = getChannelSymTab(state, offset);
				}
				if (channel->capacity == 0) {
					// We check if the rendezvous can be completed.
					if(stateGetValue(state->payload, OFFSET_HANDSHAKE, T_INT) != NO_HANDSHAKE) returnValue =  0;
					else {

						stateSetValue(state->payload, OFFSET_HANDSHAKE, T_INT, offset);
						returnValue = 1;
					}
				} else returnValue = (!channelIsFull(globalSymTab, mtypes, state, process, expression->children[0]));
				break;

			case(E_STMNT_IF):
			case(E_STMNT_DO):
			case(E_STMNT_OPT):
			case(E_STMNT_SEQ):
			case(E_STMNT_BREAK):
			case(E_STMNT_GOTO):
			case(E_STMNT_LABEL):
			case(E_STMNT_ASGN):
			case(E_STMNT_PRINT):
			case(E_STMNT_PRINTM):
				returnValue = 1;
				break;

			case(E_STMNT_INCR):
			case(E_STMNT_DECR):
				if(flag == EVAL_EXECUTABILITY) returnValue = 1;
				else returnValue = eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD());
				break;

			case(E_STMNT_ELSE):
				returnValue = (_else == 1);
				break;

			case(E_STMNT_ASSERT):
				returnValue = 1;
				break;

			case(E_STMNT_EXPR):
			case(E_EXPR_PAR):
				returnValue = eval(globalSymTab, mtypes, state, process, expression->children[0], flag, dynamicF);
				break;

			case(E_EXPR_PLUS):
				returnValue = eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD()) + eval(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD());
				break;

			case(E_EXPR_MINUS):
				returnValue = eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD()) - eval(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD());
				break;

			case(E_EXPR_TIMES):
				returnValue = eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD()) * eval(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD());
				break;

			case(E_EXPR_DIV):
				returnValue = eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD()) / eval(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD());
				break;

			case(E_EXPR_MOD):
				returnValue = eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD()) % eval(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD());
				break;

			case(E_EXPR_GT):
#if defined ATTR || defined MULTI
				DYNAMIC_CHECK
#endif
				returnValue = (eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD()) > eval(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD()));
				break;

			case(E_EXPR_LT):
#if defined ATTR || defined MULTI
				DYNAMIC_CHECK
#endif
				returnValue = (eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD()) < eval(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD()));
				break;

			case(E_EXPR_GE):
#if defined ATTR || defined MULTI
				DYNAMIC_CHECK
#endif
				returnValue = (eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD()) >= eval(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD()));
				break;

			case(E_EXPR_LE):
#if defined ATTR || defined MULTI
				DYNAMIC_CHECK
#endif
				returnValue = (eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD()) <= eval(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD()));
				break;

			case(E_EXPR_EQ):
#if defined ATTR || defined MULTI
				DYNAMIC_CHECK
#endif
				returnValue = (eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD()) == eval(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD()));
				break;

			case(E_EXPR_NE):
#if defined ATTR || defined MULTI
				DYNAMIC_CHECK
#endif
				returnValue = (eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD()) != eval(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD()));
				break;

			case(E_EXPR_AND):
#if defined ATTR || defined MULTI
				DYNAMIC_CHECK
#endif
				returnValue = 0;
				if(eval(globalSymTab, mtypes, state, process, expression->children[0], flag, dynamicF)) returnValue = eval(globalSymTab, mtypes, state, process, expression->children[1], flag, dynamicF);
				break;

			case(E_EXPR_OR):
#if defined ATTR || defined MULTI
				DYNAMIC_CHECK
#endif
				returnValue = eval(globalSymTab, mtypes, state, process, expression->children[0], flag, dynamicF);
				if(returnValue == 0) returnValue = eval(globalSymTab, mtypes, state, process, expression->children[1], flag, dynamicF);
				break;

			case(E_EXPR_UMIN):
				returnValue = - eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD());
				break;

			case(E_EXPR_NEG):
				returnValue = !eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD());
				break;

			case(E_EXPR_LSHIFT):
				returnValue = eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD()) << eval(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD());
				break;

			case(E_EXPR_RSHIFT):
				returnValue = eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD()) >> eval(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD());
				break;

			case(E_EXPR_BITWAND):
				returnValue = eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD()) & eval(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD());
				break;

			case(E_EXPR_BITWOR):
				returnValue = eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD()) | eval(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD());
				break;

			case(E_EXPR_BITWXOR):
				returnValue = eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD()) ^ eval(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD());
				break;

			case(E_EXPR_BITWNEG):
				returnValue = ~eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD());
				break;

			case(E_EXPR_COND):
				if(eval(globalSymTab, mtypes, state, process, expression->children[0], EVAL_EXPRESSION, ADD()) > 0)
					returnValue = eval(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD());
				else
					returnValue = eval(globalSymTab, mtypes, state, process, expression->children[2], flag, ADD());
				break;

			case(E_EXPR_RUN):
				returnValue = 1;
				break;

			case(E_EXPR_LEN):
				returnValue = channelLen(globalSymTab, mtypes, state, process, expression->children[0]);
				break;

			case(E_EXPR_VAR):
				returnValue = eval(globalSymTab, mtypes, state, process, expression->children[0], flag, dynamicF);
				break;

			case(E_EXPR_CONST):
				returnValue = expression->iVal;
				break;

			case(E_EXPR_TIMEOUT):
				returnValue = _timeout;
				break;

			case(E_EXPR_FULL):
				returnValue = channelIsFull(globalSymTab, mtypes, state, process, expression->children[0]);
				break;

			case(E_EXPR_NFULL):
				returnValue = !channelIsFull(globalSymTab, mtypes, state, process, expression->children[0]);
				break;

			case(E_EXPR_EMPTY):
				returnValue = channelIsEmpty(globalSymTab, mtypes, state, process, expression->children[0]);
				break;

			case(E_EXPR_NEMPTY):
				returnValue = !channelIsEmpty(globalSymTab, mtypes, state, process, expression->children[0]);
				break;


			case(E_VARREF):
				if(expression->iVal) {
					DYNAMIC_CHECK
				}
			case(E_VARREF_NAME):
			{
				symbol = expressionSymbolLookUpLeft(expression);
				ptSymTabNode field = expressionSymbolLookUpRight(expression);
				if(symbol) {
#ifdef CLOCK
					if(symbol->type == T_CLOCK) {
						failure("[eval] Clocks cannot be used in expressions other than clock constraints (line %d).\n", expression->lineNb);
					}
#endif
					// symbol != NULL iff the expression is a variable
					// Looking up if the variable is global or local to the process.
					if(symbol->global == 0)
						// local variable{
						offset = getVarOffset(globalSymTab, mtypes, state, process, process->offset, expression);
					else
						offset = getVarOffset(globalSymTab, mtypes, state, process, 0, expression);
					returnValue = stateGetValue(state->payload, offset, field->type);
				} else {

					// symbol == NULL iff the expression refers to a value of mtype OR a magic variable
					if(expression->type == E_VARREF) returnValue = expression->children[0]->iVal;
					else returnValue = expression->iVal;

					if(returnValue < 0) {
						switch(returnValue) {
							case(MVAR_SCRATCH): returnValue = MVAR_SCRATCH; break;
							case(MVAR_PID): returnValue = process->pid; break;
							case(MVAR_LAST): returnValue = state->lastStepPid; break;
							case(MVAR_NRPR): returnValue = state->nbProcesses; break;
							default: returnValue = 0; break;
						}
					}
				}
				break;
			}

			case(E_ARGLIST):
			case(E_RARG_VAR):
			case(E_RARG_EVAL):
			{
				returnValue = eval(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD());
				break;
			}
			case(E_RARG_CONST):
			{
				returnValue = expression->iVal;
				break;
			}
			case(E_EXPR_TRUE):
			{
				returnValue = 1;
				break;
			}
			case(E_EXPR_FALSE):
			{
				returnValue = 0;
				break;
			}
			case(E_EXPR_SKIP):
			{
				returnValue = true;
				break;
			}
		}
	}

	#ifdef PROFILE_EXEC
		PROFILER_END(pr_eval);
	#endif
#ifdef DEBUGEXEC
		printf("[/eval]\n");
#endif
	return returnValue;
}

int evalAndExplain(ptSymTabNode globalSymTab, ptMTypeNode mtypes, ptState state, ptStateMask process, ptExpNode expression, byte flag, const ADD& dynamicF, ptExpNode * explain) {
	if(!expression)	return 0;
	byte foundFeature = 0;
	unsigned int offset, chanOffset;
	int returnValue = -1;
	ptSymTabNode channel, symbol;
	unsigned int handshake = stateGetValue(state->payload, OFFSET_HANDSHAKE, T_INT);
	if(flag == EVAL_EXECUTABILITY && handshake != NO_HANDSHAKE && expression->type != E_STMNT_CHAN_RCV) returnValue = 0;
	else {
		switch(expression->type) {
#ifdef CLOCK
			case(E_STMNT_WHEN):
			case(E_STMNT_WAIT):
				failure("[eval] Guard and invariant statements cannot be evaluated (line %d).\n", expression->lineNb);
#endif

			case(E_DECL):
				returnValue = 1;
				break;

			case(E_STMNT):
				returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, dynamicF, explain);
				break;

			case(E_STMNT_CHAN_RCV):
				returnValue = 1;
				symbol = expressionSymbolLookUpLeft(expression->children[0]);
				channel = expressionSymbolLookUpRight(expression->children[0]);
				if(symbol->global == 0)
					chanOffset = getVarOffset(globalSymTab, mtypes, state, process, process->offset, expression->children[0]);
				else
					chanOffset = getVarOffset(globalSymTab, mtypes, state, process, 0, expression->children[0]);
				if(channel->type == T_CID) {
						chanOffset = stateGetValue(state->payload, chanOffset, T_CID);
						channel = getChannelSymTab(state, chanOffset);
				}
				if(!channel) {
					printState(mtypes, state, NULL);
					failure("ERROR (eval (E_STMNT_CHAN_RCV, line %02d)): chanOffset (%d) does not reference any existing channel.\n", expression->lineNb, chanOffset);
				}
				if (channel->capacity == 0) {
					if(handshake != chanOffset)
						// Handshake request does not concern the channel.
						return 0;
				}
				if (channelIsEmpty(globalSymTab, mtypes, state, process, expression->children[0]))
					return 0;
				else {
					// Either a rendezvous concerns the channel, either the channel has a non null capacity and is not empty.
					ptExpNode currentArg = expression->children[1];
					ptSymTabNode param = channel->child;
					int varOffset;
					int sendValue;
					byte stop = 0;
					while(currentArg && !stop) {
						if(!param) failure("[eval] channelReceive: Argument numbers does not match with the parameters number.\n");
						if(currentArg->children[0]->type != E_RARG_VAR) {
							if(channel->capacity == 0) {
								varOffset = param->memOffset;//chanOffset + param->memOffset + 1;
								sendValue = stateGetValue(_handshake_transit, varOffset, param->type);
							} else {
								varOffset = chanOffset + param->memOffset + 1;
								sendValue = stateGetValue(state->payload, varOffset, param->type);
							}

							if (evalAndExplain(globalSymTab, mtypes, state, process, currentArg->children[0], flag, ADD(), explain) != sendValue) {
								returnValue = 0;
								stop = 1;
							}
						} else {
							symbol = expressionSymbolLookUpLeft(currentArg->children[0]);
							if (!symbol) {
								if(channel->capacity == 0) {
									varOffset = param->memOffset;//chanOffset + param->memOffset + 1;
									sendValue = stateGetValue(_handshake_transit, varOffset, param->type);
								} else {
									varOffset = chanOffset + param->memOffset + 1;
									sendValue = stateGetValue(state->payload, varOffset, param->type);
								}

								returnValue = evalAndExplain(globalSymTab, mtypes, state, process, currentArg->children[0], EVAL_EXPRESSION, ADD(), explain);
								if (returnValue != -1 && returnValue != sendValue) {
									returnValue = 0;
									stop = 1;
								}
							}
						}
						param = param->next;
						currentArg = currentArg->children[1];
					}
					if(!stop) returnValue = 1;
				}
				break;

			case(E_STMNT_CHAN_SND):
				returnValue = 1;
				symbol = expressionSymbolLookUpLeft(expression->children[0]);
				channel = expressionSymbolLookUpRight(expression->children[0]);
				if(symbol->global == 0)	offset = getVarOffset(globalSymTab, mtypes, state, process, process->offset, expression->children[0]);
				else	offset = getVarOffset(globalSymTab, mtypes, state, process, 0, expression->children[0]);
				// If the symbol represents a reference to a channel, it is replaced by the true channel's symbol.
				if(channel->type == T_CID) {
					offset = stateGetValue(state->payload, offset, T_CID);
					channel = getChannelSymTab(state, offset);
				}
				if (channel->capacity == 0) {
					// We check if the rendezvous can be completed.
					if(stateGetValue(state->payload, OFFSET_HANDSHAKE, T_INT) != NO_HANDSHAKE) returnValue =  0;
					else {

						stateSetValue(state->payload, OFFSET_HANDSHAKE, T_INT, offset);
						returnValue = 1;
					}
				} else returnValue = (!channelIsFull(globalSymTab, mtypes, state, process, expression->children[0]));
				break;

			case(E_STMNT_IF):
			case(E_STMNT_DO):
			case(E_STMNT_OPT):
			case(E_STMNT_SEQ):
			case(E_STMNT_BREAK):
			case(E_STMNT_GOTO):
			case(E_STMNT_LABEL):
			case(E_STMNT_ASGN):
			case(E_STMNT_PRINT):
			case(E_STMNT_PRINTM):
				returnValue = 1;
				break;

			case(E_STMNT_INCR):
			case(E_STMNT_DECR):
				if(flag == EVAL_EXECUTABILITY) returnValue = 1;
				else returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain);
				break;

			case(E_STMNT_ELSE):
				returnValue = (_else == 1);
				break;

			case(E_STMNT_ASSERT):
				returnValue = 1;
				break;

			case(E_STMNT_EXPR):
			case(E_EXPR_PAR):
				returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, dynamicF, explain);
				break;

			case(E_EXPR_PLUS):
				returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain) + evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD(), explain);
				break;

			case(E_EXPR_MINUS):
				returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain) - evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD(), explain);
				break;

			case(E_EXPR_TIMES):
				returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain) * evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD(), explain);
				break;

			case(E_EXPR_DIV):
				returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain) / evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD(), explain);
				break;

			case(E_EXPR_MOD):
				returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain) % evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD(), explain);
				break;

			case(E_EXPR_GT):
#if defined ATTR || defined MULTI
				DYNAMIC_CHECK
#endif
				if(explain)
					*explain = expression;
				returnValue = (evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain) > evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD(), explain));
				break;

			case(E_EXPR_LT):
#if defined ATTR || defined MULTI
				DYNAMIC_CHECK
#endif
				if(explain)
					*explain = expression;
				returnValue = (evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain) < evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD(), explain));
				break;

			case(E_EXPR_GE):
#if defined ATTR || defined MULTI
				DYNAMIC_CHECK
#endif
				if(explain)
					*explain = expression;
				returnValue = (evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain) >= evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD(), explain));
				break;

			case(E_EXPR_LE):
#if defined ATTR || defined MULTI
				DYNAMIC_CHECK
#endif
				if(explain)
					*explain = expression;
				returnValue = (evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain) <= evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD(), explain));
				break;

			case(E_EXPR_EQ):
#if defined ATTR || defined MULTI
				DYNAMIC_CHECK
#endif
				if(explain)
					*explain = expression;
				returnValue = (evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain) == evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD(), explain));
				break;

			case(E_EXPR_NE):
#if defined ATTR || defined MULTI
				DYNAMIC_CHECK
#endif
				if(explain)
					*explain = expression;
				returnValue = (evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain) != evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD(), explain));
				break;

			case(E_EXPR_AND):
#if defined ATTR || defined MULTI
				DYNAMIC_CHECK
#endif
				returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, dynamicF, explain);
				if(returnValue) {
					returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, dynamicF, explain);
					if(!returnValue && explain)
						*explain = expression->children[1];
				}
				else {
					if(explain)
						*explain = expression->children[0];
				}
				break;

			case(E_EXPR_OR):
#if defined ATTR || defined MULTI
				DYNAMIC_CHECK
#endif
				returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, dynamicF, explain);
				if(!returnValue) {
					returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, dynamicF, explain);
					if(returnValue && explain)
						*explain = expression->children[1];
				}
				else {
					if(explain)
						*explain = expression->children[0];
				}
				break;

			case(E_EXPR_UMIN):
				returnValue = - evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain);
				break;

			case(E_EXPR_NEG):
				returnValue = !evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain);
				break;

			case(E_EXPR_LSHIFT):
				returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain) << evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD(), explain);
				break;

			case(E_EXPR_RSHIFT):
				returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain) >> evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD(), explain);
				break;

			case(E_EXPR_BITWAND):
				returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain) & evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD(), explain);
				break;

			case(E_EXPR_BITWOR):
				returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain) | evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD(), explain);
				break;

			case(E_EXPR_BITWXOR):
				returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain) ^ evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD(), explain);
				break;

			case(E_EXPR_BITWNEG):
				returnValue = ~evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain);
				break;

			case(E_EXPR_COND):
				if(evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], EVAL_EXPRESSION, ADD(), explain) > 0)
					returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[1], flag, ADD(), explain);
				else
					returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[2], flag, ADD(), explain);
				break;

			case(E_EXPR_RUN):
				returnValue = 1;
				break;

			case(E_EXPR_LEN):
				returnValue = channelLen(globalSymTab, mtypes, state, process, expression->children[0]);
				break;

			case(E_EXPR_VAR):
				returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, dynamicF, explain);
				break;

			case(E_EXPR_CONST):
				returnValue = expression->iVal;
				break;

			case(E_EXPR_TIMEOUT):
				returnValue = _timeout;
				break;

			case(E_EXPR_FULL):
				returnValue = channelIsFull(globalSymTab, mtypes, state, process, expression->children[0]);
				break;

			case(E_EXPR_NFULL):
				returnValue = !channelIsFull(globalSymTab, mtypes, state, process, expression->children[0]);
				break;

			case(E_EXPR_EMPTY):
				returnValue = channelIsEmpty(globalSymTab, mtypes, state, process, expression->children[0]);
				break;

			case(E_EXPR_NEMPTY):
				returnValue = !channelIsEmpty(globalSymTab, mtypes, state, process, expression->children[0]);
				break;


			case(E_VARREF):
				if(expression->iVal) {
					DYNAMIC_CHECK
				}
			case(E_VARREF_NAME):
			{
				symbol = expressionSymbolLookUpLeft(expression);
				ptSymTabNode field = expressionSymbolLookUpRight(expression);
				if(symbol) {
#ifdef CLOCK
					if(symbol->type == T_CLOCK) {
						failure("[eval] Clocks cannot be used in expressions other than clock constraints (line %d).\n", expression->lineNb);
					}
#endif
					// symbol != NULL iff the expression is a variable
					// Looking up if the variable is global or local to the process.
					if(symbol->global == 0)
						// local variable{
						offset = getVarOffset(globalSymTab, mtypes, state, process, process->offset, expression);
					else
						offset = getVarOffset(globalSymTab, mtypes, state, process, 0, expression);
					returnValue = stateGetValue(state->payload, offset, field->type);
				} else {

					// symbol == NULL iff the expression refers to a value of mtype OR a magic variable
					if(expression->type == E_VARREF) returnValue = expression->children[0]->iVal;
					else returnValue = expression->iVal;

					if(returnValue < 0) {
						switch(returnValue) {
							case(MVAR_SCRATCH): returnValue = MVAR_SCRATCH; break;
							case(MVAR_PID): returnValue = process->pid; break;
							case(MVAR_LAST): returnValue = state->lastStepPid; break;
							case(MVAR_NRPR): returnValue = state->nbProcesses; break;
							default: returnValue = 0; break;
						}
					}
				}
				break;
			}

			case(E_ARGLIST):
			case(E_RARG_VAR):
			case(E_RARG_EVAL):
				returnValue = evalAndExplain(globalSymTab, mtypes, state, process, expression->children[0], flag, ADD(), explain);
				break;

			case(E_RARG_CONST):
				returnValue = expression->iVal;
				break;
			case(E_EXPR_TRUE):
				returnValue = 1;
				break;
			case(E_EXPR_FALSE):
				returnValue = 0;
				break;

			case(E_EXPR_SKIP):
				returnValue = true;
				break;
		}
	}

	#ifdef PROFILE_EXEC
		PROFILER_END(pr_eval);
	#endif
#ifdef DEBUGEXEC
		printf("[/eval]\n");
#endif
	return returnValue;
}


#ifdef CLOCK
/*
 * Transforms an expression over the set of clocks into a clock zone.
 * Conventions:
 * 		- Expression either refers to an atomic constraint, the negation of a constraint, or a conjunction of constraints.
 * 		- An atomic constraints is an equation whose:
 * 			- left-hand side is either a clock or a difference of clocks
 * 			- right-hand side is an arbitrary arithmetic expression (which may involve variables)
 */
	ptClockZone evalZone(ptSymTabNode globalSymTab, ptMTypeNode mtypes, ptState state, ptStateMask process, ptExpNode expression) {
		ptExpNode valueNode, clocksNode;
		ptClockZone zone = initClockZone();
		switch(expression->type) {
			case(E_EXPR_PAR):
				return evalZone(globalSymTab, mtypes, state, process, expression->children[0]);
			break;

			case(E_EXPR_PLUS):
			case(E_EXPR_TIMES):
			case(E_EXPR_DIV):
			case(E_EXPR_MOD):
			case(E_EXPR_OR):
			case(E_EXPR_UMIN):
			case(E_EXPR_MINUS):
			case(E_EXPR_LSHIFT):
			case(E_EXPR_RSHIFT):
			case(E_EXPR_BITWAND):
			case(E_EXPR_BITWOR):
			case(E_EXPR_BITWXOR):
			case(E_EXPR_BITWNEG):
			case(E_EXPR_COND):
			case(E_EXPR_RUN):
			case(E_EXPR_LEN):
			case(E_EXPR_TIMEOUT):
			case(E_EXPR_FULL):
			case(E_EXPR_NFULL):
			case(E_EXPR_EMPTY):
			case(E_EXPR_NEMPTY):
			case(E_EXPR_VAR):
			case(E_VARREF):
			case(E_VARREF_NAME):
			case(E_EXPR_CONST):
			case(E_EXPR_NEG):
			case(E_EXPR_NE):
				failure("[evalZone] Unexpected expression at line %d: %s", expression->lineNb, getExpTypeName(expression->type));
			break;

			case(E_EXPR_GT):
			case(E_EXPR_LT):
			case(E_EXPR_GE):
			case(E_EXPR_LE):
			case(E_EXPR_EQ):
			{
				clocksNode = expression->children[0];
				valueNode = expression->children[1];
				char * c1 = NULL;
				char * c2 = NULL;
				ptSymTabNode sym1 = NULL, sym2 = NULL;
				if(clocksNode->type == E_EXPR_VAR) {
					sym1 = expressionSymbolLookUpLeft(clocksNode);
					c1 = sym1->name;
				}
				else if(clocksNode->type == E_EXPR_MINUS) {
					if(!clocksNode->children[0] || !clocksNode->children[0]->type != E_EXPR_VAR)
						failure("[evalZone] Unexpected expression at line %d: %s", expression->lineNb, expression->type);
					if(!clocksNode->children[1] || !clocksNode->children[1]->type != E_EXPR_VAR)
						failure("[evalZone] Unexpected expression at line %d: %s", expression->lineNb, expression->type);
					sym1 = expressionSymbolLookUpLeft(clocksNode->children[0]);
					sym2 = expressionSymbolLookUpLeft(clocksNode->children[1]);
					c1 = sym1->name;
					c2 = sym2->name;
				}
				int value = eval(globalSymTab, mtypes, state, process, valueNode, EVAL_EXPRESSION, ADD());
				switch(expression->type) {
					case(E_EXPR_GT):
						zone = zoneConstraint(zone, c2, c1, -value, 0, 0);
						break;
					case(E_EXPR_LT):
						zone = zoneConstraint(zone, c1, c2, value, 1, 0);
						break;
					case(E_EXPR_GE):
						zone = zoneConstraint(zone, c2, c1, -value, 1, 0);
						break;
					case(E_EXPR_LE):
						zone = zoneConstraint(zone, c1, c2, value, 0, 0);
						break;
					case(E_EXPR_EQ):
						zone = zoneConstraint(zone, c1, c2, value, 0, 0);
						zone = zoneConstraint(zone, c2, c1, -value, 0, 0);
						break;
				}
			break;
			}
			case(E_EXPR_AND):
				zone = zoneIntersect(zone, evalZone(globalSymTab, mtypes, state, process, expression->children[0]), 0);
				zone = zoneIntersect(zone, evalZone(globalSymTab, mtypes, state, process, expression->children[1]), 0);
			break;

		}
		return zone;
	}
#endif


byte checkEqualProps(ptList props, ptSymTabNode globalSymTab, ptMTypeNode mtypes, ptState s, ptList props2, ptSymTabNode globalSymTab2, ptMTypeNode mtypes2, ptState s2) {
#ifdef PROFILE_EXEC
	PROFILER_START(pr_checkEqualProps);
#endif
	ptList tmp = props;
	ptList tmp2 = props2;
	while(tmp && tmp2) {
		ptExpNode prop = (ptExpNode) tmp->value;
		ptExpNode prop2 = (ptExpNode) tmp2->value;
		// Props contains only global variables => mask apssed as argument is irrelevant.
		byte eval1 = eval(globalSymTab, mtypes, s, s->mask, prop, EVAL_EXECUTABILITY, ADD());
		byte eval2 = eval(globalSymTab2, mtypes2, s2, s2->mask, prop2, EVAL_EXECUTABILITY, ADD());
		if(eval1 != eval2) {
#ifdef PROFILE_EXEC
			PROFILER_END(pr_checkEqualProps);
#endif
			return 0;
		}
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
	if((tmp && !tmp2) || (!tmp && tmp2)) {
		failure("[checkEqualProps] Property lists do not have the same length (first has %d; second has %d).\n", listCount(props), listCount(props2));
	}
#ifdef PROFILE_EXEC
	PROFILER_END(pr_checkEqualProps);
#endif
	return 1;
}

/*
 * EXECUTABLE TRANSITIONS IN STATE
 * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * Returns a list of all the executable transitions (for all the processes).
 * EFFECTS: None. (It CANNOT have any!)
 * WARNING:
 * 	In the end, does NOT (and must NEVER) modify the state payload.
 */
ptList executables(ptSymTabNode globalSymTab, ptMTypeNode mtypes, ptState state, byte stutter, int nbErrors, byte * hasDeadlock, ADD* featuresOut, byte* allProductsOut, ADD* noOutgoing, byte* resetExclusivity) {
#ifdef DEBUGEXEC
	printf("[Executables]\n");
#endif
	if(resetExclusivity) *resetExclusivity = false;
	if(!state) {
		failure("EXECUTABLE: state is null\n");
		return NULL;
	}
	#ifdef PROFILE_EXEC
		PROFILER_START(pr_executables);
	#endif
	byte noDeadlock = 0;// when 1, then we're sure that there are no deadlocks; when 0 and still in loop we don't know.  when 0 and out of loop, then there is a deadlock.
	byte noLocalDeadlock = 0;// when 1, then we're sure that there is an executable transition for the current process; when 0 and still in (inner) loop we don't know.  when 0 and out of (inner) loop, the proctype has no executable transitions.
	byte freeOut = 0; // when 1, featuresOut must be free'd at the end of the function.
	byte freeAllOut = 0; // when 1, allProductsOut must be free'd at the end of the function.
	byte satFD = 0; // when 1, we KNOW that the features of considered transition satisfy the base FD.
	byte notSatFD = 0; // when 1, we KNOW that the features of considered transition do NOT satisfy the base FD.
#ifdef STOCHASTIC
	byte process_nbr = 0; // number of processes that can execute a transition
#endif
	ADD currentFeatures;

#if defined ATTR || defined MULTI
	ADD dynamicF, accElse;//, accTimeout = NULL;
#endif
#ifdef CLOCK
	byte timeTrans = 0;
	ptList tmpTrans = NULL;
#endif
	if(!featuresOut && fullDeadlockCheck) {
		featuresOut = new ADD();
		freeOut = 1;
	}
	if(!allProductsOut && fullDeadlockCheck) {
		allProductsOut = (byte*) malloc (sizeof(byte));
		*allProductsOut = 0;
		freeAllOut = 1;
	}

	byte exclusive = stateGetValue(state->payload, OFFSET_EXCLUSIVE, T_BYTE);
	int handshake = stateGetValue(state->payload, OFFSET_HANDSHAKE, T_INT);
	ptStateMask maskPtr = state->mask->next; // The first mask concerns the global variables. So, we skip this one.
	ptList E = NULL; // List of all the executable transitions.
	ptList e = NULL; // List of all the executable transitions that concerns the current process.
	ptList currentTrans = NULL;
	ptProcessTransition ableTrans = NULL;
	_timeout = 0;
	byte endOfProgram = 1;
	ptFsmNode node = NULL;
#ifdef CLOCK 
	ptClockZone newZone = NULL, transZone = NULL;
#endif

	int counter = 0;

AllProc:
	maskPtr = state->mask->next;
	while (maskPtr) {
		node = getNodePointer(state, maskPtr);
		if(!node) {
			maskPtr = maskPtr->next;
			continue;
		}
		endOfProgram = 0;
		e = NULL;
		if (stateGetValue(state->payload, OFFSET_EXCLUSIVE, T_BYTE) == NO_PROCESS || stateGetValue(state->payload, OFFSET_HANDSHAKE, T_INT) != NO_HANDSHAKE || stateGetValue(state->payload, OFFSET_EXCLUSIVE, T_BYTE) == maskPtr->pid) {
		
			//boolFctGarbageCollect("stateGetValue");
			
			_else = 0;
#if defined ATTR || defined MULTI
			//destroyBool(accElse);
			//accElse = NULL;
#endif
OneProc:	currentTrans = node->trans;
			noLocalDeadlock = 0;
OneTrans:	while(currentTrans) {
#ifdef CLOCK
				newZone = NULL;
				timeTrans = 0;
				if(((ptFsmTrans)currentTrans->value)->expression->type == E_STMNT_WHEN) {
					timeTrans = 1;
					transZone = evalZone(globalSymTab, mtypes, state, maskPtr, ((ptFsmTrans)currentTrans->value)->expression->children[0]);
					newZone = zoneIntersect(state->zone, zoneCopy(transZone), 1);
					if(zoneEmpty(newZone)) {
						zoneDestroy(newZone);
						newZone = NULL;
						zoneDestroy(transZone);
						transZone = NULL;
						currentTrans = currentTrans->next;
						goto OneTrans;
					}
					if(((ptFsmTrans)currentTrans->value)->target && ((ptFsmTrans)currentTrans->value)->target->trans) {
						tmpTrans = currentTrans;
						currentTrans = ((ptFsmTrans)currentTrans->value)->target->trans;
					}
					else
						failure("Transition guards must be followed by a statement (line %d).\n", ((ptFsmTrans)currentTrans->value)->expression->lineNb);
				}
#endif
#if defined ATTR || defined MULTI
				if(eval(globalSymTab, mtypes, state, maskPtr, ((ptFsmTrans)currentTrans->value)->expression, EVAL_EXECUTABILITY, dynamicF) > 0) {
#else
				if(eval(globalSymTab, mtypes, state, maskPtr, ((ptFsmTrans)currentTrans->value)->expression, EVAL_EXECUTABILITY, ADD()) > 0) {
				
					//boolFctGarbageCollect("eval");
#endif

#ifdef CLOCK
					if(timeTrans)
						currentFeatures = ((ptFsmTrans)tmpTrans->value)->features;
					else
						currentFeatures = ((ptFsmTrans)currentTrans->value)->features;
#endif
					// The features required for this transition to fire:
					/*printf("\n\ntransition -> %ld : ", ((ptFsmTrans)currentTrans->value)->lineNb);
					printf("\nstate->features : "); printBool(state->features);
					printf("\nedge->features : "); printBool(currentFeatures);
					printf("\nedge->prob : %f\n", ((ptFsmTrans)currentTrans->value)->expression->prob);*/
					ADD conjunct = addConjunction(((ptFsmTrans)currentTrans->value)->features, state->features, 1, 1);
						
					//boolFctGarbageCollect("conjunct");
						
						
					//printf("\nFEATURES : "); printBool(conjunct); printf("\n\n\n");

#if defined ATTR || defined MULTI
					if(!maskPtr)
						failure("No mask");
					if(!maskPtr->process)
						failure("No process");
					if(!maskPtr->process->fsm)
						failure("No fsm");
					if(!maskPtr->process->fsm->init)
						failure("No init");
					if(node && node == maskPtr->process->fsm->init && maskPtr->context){
						conjunct = addConjunction(conjunct, createVariable(maskPtr->context->name), 0, 1);
					}
#endif
					if((stateGetValue(state->payload, OFFSET_HANDSHAKE, T_INT) != NO_HANDSHAKE) && (((ptFsmTrans)currentTrans->value)->expression->type == E_STMNT_CHAN_SND)) {
						ADD original = state->features;
						state->features = conjunct;
						
						//boolFctGarbageCollect("state->features = conjunct;");
#ifdef CLOCK
						ptClockZone originalZone = state->zone;
						state->zone = newZone ? newZone : state->zone;
#endif
						ptExpNode expression = ((ptFsmTrans)currentTrans->value)->expression;
						channelSend(globalSymTab, mtypes, state, maskPtr, expression);
						// channelSend has modified the value of HANDSHAKE and one other byte in the payload.
						// These two will have to get back their original value.
						// Also, channelSend has allocated memory to handshake_transit: it will have to be free'd.
						byte responseHasDeadlock = 0;
						ptList e_ = executables(globalSymTab, mtypes, state, 0, nbErrors, &responseHasDeadlock, featuresOut, allProductsOut, noOutgoing, NULL);
						
						//boolFctGarbageCollect("executables(globalSymTab, mtypes, state, 0, nbErrors, &responseHasDeadlock, featuresOut, allProductsOut, noOutgoing, ADD());");
						
						if(!responseHasDeadlock) {
							noDeadlock = 1;
							noLocalDeadlock = 1;
						}
						// After the recursive call, each transition in e_ is executable and its features satisfy the modified base FD.
						// featuresOut contains all the outgoing features from now on, included the ones of the response that satisfy the base FD (those may not satisfy the modified FD, though).
						// *allProductsOut == 1 if the outgoing features reference all the products.
						ptList response = e_;
						while(response) {
#ifdef CLOCK
							if(timeTrans)
								ableTrans = createProcessTransition(maskPtr, (ptFsmTrans)(currentTrans->value), ADD(), transZone, (ptProcessTransition) response->value);
							else
								ableTrans = createProcessTransition(maskPtr, (ptFsmTrans)(currentTrans->value), ADD(), NULL, (ptProcessTransition) response->value);
#else
							ableTrans = createProcessTransition(maskPtr, (ptFsmTrans)(currentTrans->value), ADD(), (ptProcessTransition) response->value);
#endif
#ifdef STOCHASTIC
							ableTrans->prob = ((ptFsmTrans)(currentTrans->value))->expression->prob * ((ptProcessTransition) response->value)->prob;

#endif
							e = listAdd(e, ableTrans);
							response = response->next;
							noDeadlock = 1;
							noLocalDeadlock = 1;
							satFD = 1;
						}
						listDestroy(e_);

						state->features = original;
#ifdef CLOCK
						state->zone = originalZone;
#endif
						// The state must be reverted back to its original form
						// in order to ensure that the payload has not be modified.
						ptExpNode channelVar = expression->children[0];
						ptSymTabNode prefix = expressionSymbolLookUpLeft(channelVar);
						ptSymTabNode channel = expressionSymbolLookUpRight(channelVar);
						unsigned int offset;
						if(prefix->global == 0)
							offset = getVarOffset(globalSymTab, mtypes, state, maskPtr, maskPtr->offset, channelVar); // local variable
						else
							offset = getVarOffset(globalSymTab, mtypes, state, maskPtr, 0, channelVar);
						if(channel->type == T_CID)
							offset = stateGetValue(state->payload, offset, T_CID);
						stateSetValue(state->payload, offset, T_BYTE, 0);
						stateSetValue(state->payload, OFFSET_HANDSHAKE, T_INT, NO_HANDSHAKE);
						if(_handshake_transit) free(_handshake_transit);
						_handshake_transit = NULL;
					} else {
						satFD = 0;
						notSatFD = 0;
#if defined ATTR || defined MULTI
						accElse = addConjunction(accElse, negateBool(dynamicF, 0), 0, 0);
						//accTimeout = addConjunction(accTimeout, negateBool(dynamicF, 0), 0, 0);
						conjunct = addConjunction(conjunct, dynamicF, 0, 0);
						//if(_timeout && accTimeout)
						//	conjunct = addConjunction(conjunct, accTimeout, 0, 1);
						if(_else && accElse)
							conjunct = addConjunction(conjunct, accElse, 0, 1);
#endif
						//boolFctGarbageCollect("conjunct = addConjunction(conjunct, accElse, 0, 1);");


#if defined(ATTR) || defined(MULTI)
						if((!(node && node == maskPtr->process->fsm->init && maskPtr->context)) || isSatisfiableWrtFD(conjunct)) {
#else
						
						if(((ptFsmTrans)currentTrans->value)->features.Nil() || isSatisfiableWrtFD(conjunct)) {
#endif
							
							//boolFctGarbageCollect("!(currentFeatures) || isSatisfiableWrtFD(conjunct)");
#ifdef CLOCK
						if(timeTrans)
							ableTrans = createProcessTransition(maskPtr, (ptFsmTrans)(currentTrans->value), conjunct, zoneCopy(transZone), NULL);
						else
							ableTrans = createProcessTransition(maskPtr, (ptFsmTrans)(currentTrans->value), conjunct, NULL, NULL);
#else
							ableTrans = createProcessTransition(maskPtr, (ptFsmTrans)(currentTrans->value), conjunct, NULL);
							
							//printBool(conjunct);
#endif
#ifdef STOCHASTIC
							ableTrans->prob = ((ptFsmTrans)(currentTrans->value))->expression->prob;
#endif
#ifdef DEBUGEXEC
							printf("Transition Added.\n");
#endif
							e = listAdd(e, ableTrans);

							noDeadlock = 1;
							noLocalDeadlock = 1;
							satFD = 1;
						}
						else if(nbErrors > 0) {
							// When the features required for firing the transition are not satisfiable wrt the FD,
							// then we have to check whether they are satisfiable wrt the base FD!
							// Only if the transition is also not satisfiable wrt the base FD could it be that we have
							// a deadlock.  Since the only reason for testing this is to prevent false deadlocks from
							// being reported, we don't do it when we already know that there is no deadlock or when
							// the base FD and the FD are identical, hence the condition:
							if(!noDeadlock) {
								if(isSatisfiableWrtBaseFD(conjunct)) {
									// The features satisfy the base FD (but not the modified one).
									noDeadlock = 1;
									noLocalDeadlock = 1;
									satFD = 1;
								}
								else notSatFD = 1; // The features do not satisfy the base FD.
							}
						}
						else {
							notSatFD = 1; // FD = Base FD and the features do not satisfy it.
						}
						
						//boolFctGarbageCollect("isSatisfiableWrtBaseFD(conjunct)");
						
						if(fullDeadlockCheck && !(*allProductsOut) && !notSatFD && (satFD || isSatisfiableWrtBaseFD(conjunct))) {
							// The features satisfy the base FD -> we add it to the outgoing features.
							if(conjunct) *featuresOut = addDisjunction(*featuresOut, conjunct, 0, 1);
							else {
								delete featuresOut;
								*allProductsOut = 1;
							}
						}
					}// if (stateGetValue...)
					
					//destroyBool(conjunct);
					//conjunct = NULL;
					
					//boolFctGarbageCollect("destroyBool(conjunct);");
					
				}// if eval(globalSymTab, mtypes, ...)
#ifdef CLOCK
				if(timeTrans) {
					timeTrans = 0;
					currentTrans = tmpTrans;
				}
#endif
				currentTrans = currentTrans->next;
			} // While(currentTrans)

			if(e) 	{
#ifdef STOCHASTIC
				process_nbr++;
				double totalProb = 0.0;
				double check = 0.0;
				ptList tmp = NULL;
				int nb_proc_trans = 0;
				for(tmp = e; tmp; tmp = tmp->next) {
					ableTrans = (ptProcessTransition) tmp->value;
					if(isTautology(ableTrans->features)) {
						totalProb += ableTrans->prob;
						nb_proc_trans++;
					}
				}
				for(tmp = e; tmp; tmp = tmp->next) {
					ableTrans = (ptProcessTransition) tmp->value;
					if(isTautology(ableTrans->features)) {
						ableTrans->prob = ableTrans->prob / totalProb;
						/*if(!spinMode)
							ableTrans->prob *= 1.0 / nb_proc_trans;*/
						check += ableTrans->prob;

					}
				}

				assert(check <= 1.0);
				//printf("check trans : %f\n", check);
#endif
				//counter++;
				//printf("counter %d\n", counter);
                E = listConcat(E, e);
                //E = listAdd(E, e);
			}
#if defined ATTR || defined MULTI
			if ((!noLocalDeadlock || accElse) && !_else) {
#else
			if (!noLocalDeadlock && !_else) {
#endif
				e = NULL;
				_else = 1;
				goto OneProc;
			}
		}
		maskPtr = maskPtr->next;
	}

	if (!noDeadlock && stateGetValue(state->payload, OFFSET_EXCLUSIVE, T_BYTE) != NO_PROCESS) {
		stateSetValue(state->payload, OFFSET_EXCLUSIVE, T_BYTE, NO_PROCESS);
		if(resetExclusivity) *resetExclusivity = true;
		goto AllProc;
	}
	if (!noDeadlock && !_timeout) {
		_timeout = 1;
		goto AllProc;
	}

	stateSetValue(state->payload, OFFSET_EXCLUSIVE, T_BYTE, exclusive);
	stateSetValue(state->payload, OFFSET_HANDSHAKE, T_INT, handshake);

	if(!noDeadlock && stutter && endOfProgram) { // We create a "blank" transition if we're in the (real) final state and if the stutter extension is asked and if there is no real transition.
		ptProcessTransition stutterTrans = (ptProcessTransition) malloc(sizeof(tProcessTransition));
		if(!stutterTrans) failure("Out of memory (creating processTransition).\n");
		stutterTrans->process = NULL;
		stutterTrans->features = state->features;
		stutterTrans->trans = NULL;
		stutterTrans->response = NULL;
		E = listAdd(E, stutterTrans);
		noDeadlock = 1;
		if(fullDeadlockCheck && !(*allProductsOut)) {
			if(stutterTrans->features) *featuresOut = addDisjunction(*featuresOut, stutterTrans->features, 0, 1);
			else {
				delete featuresOut;
				*allProductsOut = 1;
			}
		}
	}
	
	//boolFctGarbageCollect("stutterTrans->features = state->features;");

	#ifdef PROFILE_EXEC
		PROFILER_END(pr_executables);
	#endif

	if(hasDeadlock) {
		*hasDeadlock = (noDeadlock == 0);
	}
	if(freeOut) {
		// if freeOut, then we are in the first call to executables(globalSymTab, mtypes, ) (i.e. not a recursive call)
		// thus, we must return the features that have no outgoing transition
		if(fullDeadlockCheck && !(*allProductsOut) && *featuresOut) {
			*noOutgoing = addConjunction(state->features, negateBool(*featuresOut, 0), 1, 0);
		}
		delete featuresOut;
	}
	
	//boolFctGarbageCollect("*noOutgoing = addConjunction(state->features, negateBool(*featuresOut, 0), 1, 0);");

	if(freeAllOut) delete(allProductsOut);
#ifdef STOCHASTIC
	ptList tmp = NULL;
	double totalProb = 0;
	for(tmp = E; tmp; tmp = tmp->next) {
		ableTrans = (ptProcessTransition) tmp->value;
		ableTrans->prob = ableTrans->prob / process_nbr;
		totalProb += ableTrans->prob;
	}

	assert(totalProb <= 1.0);
	//printf("check proc : %f\n", totalProb);

	/*printf("-----------------------------------------------\n");
	for(tmp = E; tmp; tmp = tmp->next) {
		ableTrans = (ptProcessTransition) tmp->value;
		printf("\n\ntransition -> %ld : ", ((ptFsmTrans)ableTrans->trans)->lineNb);
		printf("\nproc_trans->features : "); printBool(ableTrans->features);
		printf("\nproc_trans->prob : %f\n", ableTrans->prob);
	}*/

#endif

#ifdef DEBUGEXEC
	printf("[/Executables]\n\n\n");
#endif
	return E;
}

/**
 * Returns a list of lists of transitions that eventually lead to a non-stutter-bisimilar state or the first encountered stutter-bisimilar divergent state.
 */
ptList executablesNonStutter(ptList props, ptSymTabNode globalSymTab, ptMTypeNode mtypes, ptState state, byte stutter, int nbErrors, byte* hasDeadlock, ADD* featuresOut, byte* allProductsOut, ADD* noOutgoing) {
	//printf("[executablesNonStutter]\n");
	ptList _ENS = NULL;
	ptList E = NULL;
	ptList tmp = NULL;
	ptList prevs = NULL;
	ptState prev = NULL, s_ = NULL;
	ptProcessTransition currentTrans = NULL;
	byte resetExclusivity = false;
	byte foundCandidate = 0;
	byte foundVisited = 0;
	ptState stateCopy = stateDuplicate(state);
	stateCopy->features = state->features;
	ptStackElt elt = createStackElement(stateCopy,0);
	elt->E = executables(globalSymTab, mtypes, stateCopy, stutter, nbErrors, hasDeadlock, featuresOut, allProductsOut, noOutgoing, &resetExclusivity);
	if(resetExclusivity) {
		stateSetValue(state->payload, OFFSET_EXCLUSIVE, T_BYTE, NO_PROCESS);
		stateSetValue(stateCopy->payload, OFFSET_EXCLUSIVE, T_BYTE, NO_PROCESS);
	}
	state->payloadHash = hashState(state);
	stateCopy->payloadHash = hashState(stateCopy);

	elt->E_save = elt->E;
	ptStack stack = push(NULL, elt);
	ptStack stackFeatures = NULL;
	void * onStack = createHashtable();
	void * visited = createHashtable();
	htInsert(onStack, state->payloadHash, stateCopy);
	htInsert(visited, state->payloadHash, stateCopy);
	// To avoid memory leaks
	int * newKey = (int *) malloc(sizeof(int));
	*newKey = stateCopy->payloadHash;
	ptList addedKeys = listAdd(NULL, newKey);
	ptList addedStates = NULL;

	int i = 0;
	while(!empty(stack)) {
		i++;
		ptStackElt current = top(stack);
		if(!current->E) {
			pop(&stack);
			delete top(stackFeatures);
			pop(&stackFeatures);
			htRemove(onStack, current->state->payloadHash, current->state);
			stateDestroy(current->state, 0);
			current->state = NULL;
			destroyStackElement(current, processTrans);
		}
		else {
			foundCandidate = 0;
			foundVisited = 0;
			currentTrans = (ptProcessTransition) current->E->value;
			s_ = apply(globalSymTab, mtypes, current->state, currentTrans, 1, NULL);
			E = executables(globalSymTab, mtypes, s_, stutter, nbErrors, hasDeadlock, featuresOut, allProductsOut, noOutgoing, &resetExclusivity);
			if(resetExclusivity) {
				stateSetValue(s_->payload, OFFSET_EXCLUSIVE, T_BYTE, NO_PROCESS);
			}
			s_->payloadHash = hashState(s_);
			prevs = htSearch(visited, s_->payloadHash);
			tmp = prevs;
			while(tmp) {
				prev = (ptState) tmp->value;
				if (memcmp(prev->payload, s_->payload, prev->payloadSize) == 0) {
					foundVisited = 1;
					stateDestroy(s_, false);
					destroyProcTransList(E, processTrans);
					E = NULL;
				}
				tmp = tmp->next;
			}
			if(!foundVisited) {
				// CUDD REF WARNING 
				ADD* topStack = static_cast<ADD*>(top(stackFeatures));
				stackFeatures = push(stackFeatures, &addConjunction(*topStack, currentTrans->features, 1, 1));
				ptState s_Copy = stateDuplicate(s_);
				htInsert(visited, s_Copy->payloadHash, s_Copy);
				// To avoid memory leaks
				newKey = (int *) malloc(sizeof(int));
				*newKey = s_Copy->payloadHash;
				addedKeys = listAdd(addedKeys, newKey);
				addedStates = listAdd(addedStates, s_Copy);

				if(checkEqualProps(props, globalSymTab, mtypes, current->state, props, globalSymTab, mtypes, s_)) {
					prevs = htSearch(onStack, s_->payloadHash);
					tmp = prevs;
					while(tmp) {
						prev = (ptState) tmp->value;
						if (memcmp(prev->payload, s_->payload, s_->payloadSize) == 0) {
							foundCandidate = 1;
						}
						tmp = tmp->next;
					}
					if(!foundCandidate) {
						elt = createStackElement(s_,0);
						elt->E = E;
						elt->E_save = elt->E;

						stack = push(stack, elt);
						htInsert(onStack, s_->payloadHash, s_);
					}
				}
				else {
					foundCandidate = 1;
				}
				if(foundCandidate) {
					destroyProcTransList(E, processTrans);
					E = NULL;
					ptDirectTransition dtrans = new tDirectTransition();
					dtrans->target = s_;
					dtrans->features = *static_cast<ADD*>(top(stackFeatures));
					pop(&stackFeatures);
					_ENS = listAdd(_ENS, dtrans);
				}
				//destroyBool(s_->features);
				//s_->features = NULL;
				s_ = NULL;
			}
			current->E = current->E->next;
		}
	}

	// Free memory
	tmp = addedStates;
	while(tmp) {
		s_ = (ptState) tmp->value;
		stateDestroy(s_, false);
		s_ = NULL;
		tmp = tmp->next;
	}
	listDestroy(addedStates);
	destroyEntries(visited, addedKeys);
	tmp = addedKeys;
	while(tmp) {
		newKey = (int *) tmp->value;
		free(newKey);
		tmp = tmp->next;
	}
	listDestroy(addedKeys);
	destroyHashtable(visited);
	destroyHashtable(onStack);

	return _ENS;
}

/**
 * Returns all the fire-able transitions of the NEVER claim of the given state.
 */
ptList executablesNever(ptSymTabNode globalSymTab, ptMTypeNode mtypes, ptState state) {
	ptFsmNode neverNode;
	_else = 0;
	if(!state || !state->never || !(neverNode = getNodePointer(state, state->never))) return NULL;
	else {
		ptList fireAble = NULL;
		ptList transList;
Eval:	transList = neverNode->trans;
		while(transList) {
			if(eval(globalSymTab, mtypes, state, state->never, ((ptFsmTrans)(transList->value))->expression, EVAL_EXECUTABILITY, ADD())) {
				fireAble = listAdd(fireAble, transList->value);
			}
			transList = transList->next;
		}
		if(!fireAble && _else == 0) {
			_else = 1;
			goto Eval;
		}
		return fireAble;
	}
}

/**
 * Creates a transition between states.
 */
#ifdef CLOCK
	ptProcessTransition createProcessTransition(ptStateMask process, ptFsmTrans trans, const ADD& features, ptClockZone guard, ptProcessTransition response) {
#else
	ptProcessTransition createProcessTransition(ptStateMask process, ptFsmTrans trans, const ADD& features, ptProcessTransition response) {
#endif
	ptProcessTransition ptrans = new tProcessTransition();
	if(!ptrans) failure("Out of memory (creating processTransition).\n");
	ptrans->process = process;
	ptrans->trans = trans;
	ptrans->features = features;
#ifdef CLOCK
	ptrans->guard = guard;
#endif
	ptrans->response = response;
	return ptrans;
}

/**
 * Executes a statement and returns the new reached state. The transition must be executable.
 * The preserve parameter controls whether or not the state that is passed is preserved.
 *
 * The features expression of the processTransition is not modified. The value of this expression is
 * copied into the new state. Thus, when this state is destroyed, the features expression of the
 * processTransition is not deleted.
 *
 * assertViolation is a return value set to true in case the statement on the transition was an assert
 * that evaluated to false.
 */
ptState apply(ptSymTabNode globalSymTab, ptMTypeNode mtypes, ptState state, ptProcessTransition procTrans, byte preserve, byte* assertViolation) {
	ptStateMask process = procTrans->process;
	ptFsmTrans trans = procTrans->trans;
	ptExpNode expression = trans->expression;
#ifdef DEBUGEXEC
	printf("[apply]\n");
	printf("Expression %s at line %d\n", getExpTypeName(expression->type), expression->lineNb);
#endif
	if(!procTrans)
		failure("[apply] cannot apply NULL transition.\n");
	if(assertViolation) *assertViolation = 0;
	ptState copy;
	if(preserve) copy = stateDuplicate(state);
	else copy = state;

	// Stutter trasnition
	if(!procTrans->process || !procTrans->trans) {
		copy->features = procTrans->features;
		//procTrans->features = NULL;
		assert(false);
		return copy;
	}

	#ifdef PROFILE_EXEC
		PROFILER_START(pr_apply);
	#endif

	//ptStateMask process = procTrans->process;
	//ptFsmTrans trans = procTrans->trans;
	//ptExpNode expression = trans->expression;
	ptExpNode currentArg;
	ptSymTabNode symbol, field, chanSymbLeft, channel;
	unsigned int offset, chanOffset;
	int previousValue, pid;

	// It will be set at the end
	//copy->features = NULL;
	byte leaveUntouched = 0; // Set to 1 in case of a rendez-vous channel send.
Apply:
#ifdef DEBUGEXEC
	printf("Expression %s at line %d\n", getExpTypeName(expression->type), expression->lineNb);
#endif
	switch(expression->type) {
		case(E_DECL):
		case(E_STMNT):
			break;
#ifdef CLOCK
			case(E_STMNT_WHEN):
/*				copy->zone = zoneFuture(copy->zone, 0);
				if(state->invariant)
					copy->zone = zoneIntersect(copy->zone, state->invariant, 0);
				copy->zone = zoneIntersect(copy->zone, evalZone(globalSymTab, mtypes, state, process, expression->children[0]), 0);
				if(expression->symTab) { // There are clocks to reset
					ptSymTabNode reset = expression->symTab;
					while(reset) {
						copy->zone = zoneReset(copy->zone, reset->name, 0);
						reset = reset->next;
					}
				}
				apply(globalSymTab, mtypes, copy, procTrans->response, 0, assertViolation);
				leaveUntouched = 1;
				break;*/
			case(E_STMNT_WAIT):
				failure("Guard and invariant statements cannot be evaluated (line %d).\n", expression->lineNb);
#endif


		case(E_STMNT_CHAN_RCV):
			channelReceive(globalSymTab, mtypes, copy, process, expression);
			// If there was a rendezvous request, it has been accepted.
			break;

		case(E_STMNT_CHAN_SND):
		{
			// Sends the message in the correct channel.
			// Increases by one unit the number of messages of this channel.
			// If the channel was a rendezvous channel, _handshake_transit has been allocated.
			channelSend(globalSymTab, mtypes, copy, process, expression);
			ptSymTabNode channel = expressionSymbolLookUpRight(expression->children[0]);
			ptSymTabNode prefix  = expressionSymbolLookUpLeft(expression->children[0]);

			if(prefix->global == 0) offset = getVarOffset(globalSymTab, mtypes, copy, process, process->offset, expression->children[0]);
			else offset = getVarOffset(globalSymTab, mtypes, copy, process, 0, expression->children[0]);

			// If the symbol represents a reference to a channel, it is replaced by the true channel's symbol.
			if(channel->type == T_CID) {
				offset = stateGetValue(state->payload, offset, T_CID);
				channel = getChannelSymTab(state, offset);
			}
			if(channel->capacity == 0) {
				leaveUntouched = 1;
#ifdef CLOCK
				copy->zone = zoneFuture(copy->zone, 0);
				if(state->invariant)
					copy->zone = zoneIntersect(copy->zone, state->invariant, 0);
				if(procTrans->guard)
					copy->zone = zoneIntersect(copy->zone, procTrans->guard, 0);
				if(expression->symTab) { // There are clocks to reset
					ptSymTabNode reset = expression->symTab;
					while(reset) {
						copy->zone = zoneReset(copy->zone, reset->name, 0);
						reset = reset->next;
					}
				}
				if(procTrans->trans->target->trans) {
					ptExpNode nextExpr = ((ptFsmTrans) procTrans->trans->target->trans->value)->expression;
					if(nextExpr->type == E_STMNT_WAIT) {
						if(copy->invariant)
							copy->invariant = zoneIntersect(copy->invariant, evalZone(globalSymTab, mtypes, copy, process, nextExpr->children[0]), 0);
						else
							copy->invariant = evalZone(globalSymTab, mtypes, state, process, nextExpr->children[0]);
						procTrans->trans = (ptFsmTrans) procTrans->trans->target->trans->value;
					}
				}
				if(copy->invariant) { // No invariant = discrete transition
					copy->zone = zoneIntersect(copy->zone, copy->invariant, 0);
					copy->zone = zoneFuture(copy->zone, 0);
					copy->zone = zoneIntersect(copy->zone, copy->invariant, 0);
				}
				else {
					copy->zone = zoneFuture(copy->zone, 0);
				}
#endif
				if(!procTrans->response) failure("Applying handshake without any response transition!\n");
				// Send was a rendezvous request. We immediately try to complete this rendezvous.
				stateSetValue(copy->payload, OFFSET_HANDSHAKE, T_INT, offset);
				// If the sender had the exclusivity, it lost it because of the rendezvous completion.
				stateSetValue(copy->payload, OFFSET_EXCLUSIVE, T_BYTE, NO_PROCESS);
				// Proceed in automaton
				storeNodePointer(copy, maskLookup(copy, procTrans->process->pid), procTrans->trans->target);
				// Applying the response transition.
				// Note that the features of the resulting state will be: "state->features & request_transition->features & response_transition->features"
				// Also, applying this transition will free _handshake_transit (because of calling "channelReceive()").
				// Furthermore, the number of message in the rendezvous channel will be 0.
				
				//c.f. SAMI...
				procTrans->response->prob = procTrans->prob;
				//

				copy = apply(globalSymTab, mtypes, copy, procTrans->response, 0, assertViolation);
				stateSetValue(copy->payload, OFFSET_HANDSHAKE, T_INT, NO_HANDSHAKE); // Rendezvous completed: HANDSHAKE is reset.
			}
			break;
		}
		case(E_STMNT_IF):
		case(E_STMNT_DO):
		case(E_STMNT_OPT):
		case(E_STMNT_SEQ):
		case(E_STMNT_BREAK):
		case(E_STMNT_GOTO):
		case(E_STMNT_LABEL):
			failure("Found control statement while applying an expression at line %2d\n", expression->lineNb);
			break;

		case(E_STMNT_ASGN):
			symbol = expressionSymbolLookUpLeft(expression->children[0]);
			field = expressionSymbolLookUpRight(expression->children[0]);
			if(symbol->global == 0)
				offset = getVarOffset(globalSymTab, mtypes, copy, process, process->offset, expression->children[0]);
			else
				offset = getVarOffset(globalSymTab, mtypes, copy, process, 0, expression->children[0]);
			if (field->type == T_CID)	{
				chanSymbLeft = expressionSymbolLookUpLeft(expression->children[1]);
				channel = expressionSymbolLookUpRight(expression->children[1]);
				if (chanSymbLeft->global == 0)
					chanOffset = getVarOffset(globalSymTab, mtypes, copy, process, process->offset, expression->children[1]);
				else
					chanOffset = getVarOffset(globalSymTab, mtypes, copy, process, 0, expression->children[1]);
				if(channel->type == T_CID) chanOffset = stateGetValue(state->payload, chanOffset, T_CID);
				stateSetValue(copy->payload, offset, T_CID, chanOffset);
			}
			else stateSetValue(copy->payload, offset, field->type, eval(globalSymTab, mtypes, copy, process, expression->children[1], EVAL_EXPRESSION, ADD()));
			break;

		case(E_STMNT_INCR):
			symbol = expressionSymbolLookUpLeft(expression->children[0]);
			field = expressionSymbolLookUpRight(expression->children[0]);
			if(symbol->global == 0)
				offset = getVarOffset(globalSymTab, mtypes, copy, process, process->offset, expression->children[0]);
			else
				offset = getVarOffset(globalSymTab, mtypes, copy, process, 0, expression->children[0]);
			previousValue = stateGetValue(copy->payload, offset, field->type);
			stateSetValue(copy->payload, offset, field->type, previousValue+1);
			break;

		case(E_STMNT_DECR):
			symbol = expressionSymbolLookUpLeft(expression->children[0]);
			field = expressionSymbolLookUpRight(expression->children[0]);
			if(symbol->global == 0)
				offset = getVarOffset(globalSymTab, mtypes, copy, process, process->offset, expression->children[0]);
			else
				offset = getVarOffset(globalSymTab, mtypes, copy, process, 0, expression->children[0]);
			previousValue = stateGetValue(copy->payload, offset, field->type);
			stateSetValue(copy->payload, offset, field->type, previousValue-1);
			break;

		case(E_STMNT_PRINT):
			executePromelaPrint(globalSymTab, mtypes, expression->sVal, expression->children[0], state, process);
			break;

		case(E_STMNT_PRINTM): {
				int value;
				if(expression->children[0]) {
					symbol = expressionSymbolLookUpLeft(expression->children[0]);
					field = expressionSymbolLookUpRight(expression->children[0]);
					if(symbol->global == 0)
						offset = getVarOffset(globalSymTab, mtypes, copy, process, process->offset, expression->children[0]);
					else
						offset = getVarOffset(globalSymTab, mtypes, copy, process, 0, expression->children[0]);
					value = stateGetValue(copy->payload, offset, field->type);
				} else {
					value = expression->iVal;
				}
			break;
		}
		case(E_STMNT_ELSE):
			break;

		case(E_STMNT_ASSERT):
			if(eval(globalSymTab, mtypes, state, process, expression->children[0], EVAL_EXPRESSION, ADD()) == 0) {
				if(assertViolation) *assertViolation = 1;
			}
			break;

		case(E_STMNT_EXPR):
		case(E_EXPR_PAR):
			expression = expression->children[0];
			goto Apply;

		case(E_EXPR_PLUS):
		case(E_EXPR_MINUS):
		case(E_EXPR_TIMES):
		case(E_EXPR_DIV):
		case(E_EXPR_MOD):
		case(E_EXPR_UMIN):
			failure("Found arithmetic expression while applying an expression at line %2d\n", expression->lineNb);
			break;

		case(E_RARG_EVAL):
		case(E_EXPR_CONST):
		case(E_EXPR_GT):
		case(E_EXPR_LT):
		case(E_EXPR_GE):
		case(E_EXPR_LE):
		case(E_EXPR_EQ):
		case(E_EXPR_NE):
		case(E_EXPR_AND):
		case(E_EXPR_OR):
		case(E_EXPR_NEG):
		case(E_EXPR_LSHIFT):
		case(E_EXPR_RSHIFT):
		case(E_EXPR_BITWAND):
		case(E_EXPR_BITWOR):
		case(E_EXPR_BITWXOR):
		case(E_EXPR_BITWNEG):
		case(E_EXPR_COND):
		case(E_EXPR_TIMEOUT):
		case(E_EXPR_FULL):
		case(E_EXPR_NFULL):
		case(E_EXPR_EMPTY):
		case(E_EXPR_NEMPTY):
			break;

		case(E_EXPR_RUN):
		{	// A new process can run iff MAX_PROCESS processes or less are currently running.
			if(copy->nbProcesses > MAX_PROCESS) failure("Cannot instantiate more than %d processes.", MAX_PROCESS);
			else {
				int pid;
				if(expression->children[1]) {
#if defined ATTR || defined MULTI
					ptSymTabNode container = expressionSymbolLookUpLeft(expression->children[1]);
					if(!container || !container->utype || !expression->children[1]->children[1]->children[0]->sVal)
						failure("[eval] Unknown context at line %d.\n", expression->lineNb);
					ptSymTabNode feature = lookupInSymTab(container->utype->child, expression->children[1]->children[1]->children[0]->sVal);
					char * path = feature2String(expression->children[1], feature, NULL, NULL);
					pid = stateAddProctype(copy, expression->symTab, path, expression->children[1], 0);
#else
					failure("[eval] Feature contexts are not allowed in this variant of SNIP.\n");
#endif
				}
				else
					pid = stateAddProctype(copy, expression->symTab, NULL, NULL, 0);
				ptStateMask mask = maskLookup(copy, pid);
				ptExpNode argList = expression->children[0];
				ptExpNode arg;
				ptSymTabNode param = expression->symTab->fsm->symTab;
				unsigned int varOffset;
				while (argList) {
					if(!param) failure("RUN statement: arguments number does not fit parameters number.\n");
					arg = argList->children[0];
					symbol = expressionSymbolLookUpLeft(arg);
					offset = mask->offset + param->memOffset;
					if(symbol) {
						/* Argument is a variable. Possibly an instance of a user type. */
						if(symbol->global == 0)	varOffset = getVarOffset(globalSymTab, mtypes, copy, process, process->offset, arg);
						else 	varOffset = getVarOffset(globalSymTab, mtypes, copy, process, 0, arg);
						if (param->type == T_CID)	{
							channel = expressionSymbolLookUpRight(arg);
							if(channel->type == T_CID) varOffset = stateGetValue(state->payload, varOffset, T_CID);
							stateSetValue(copy->payload, offset, T_CID, varOffset);
						}
						else {
							byte * values = readValues(copy->payload, varOffset, param->memSize*param->bound);
							storeValues(copy->payload, offset, param->memSize*param->bound, values);
							free(values);
						}
					}
					else 	stateSetValue(copy->payload, offset, param->type, eval(globalSymTab, mtypes, copy, process, arg, EVAL_EXPRESSION, ADD()));
					argList = argList->children[1];
					param = param->next;
				}

			}
		}
		break;

		case(E_EXPR_LEN):
		case(E_EXPR_VAR):
		case(E_ARGLIST):
		case(E_VARREF):
		case(E_VARREF_NAME):
		case(E_RARG_VAR):
		case(E_RARG_CONST):
		case(E_EXPR_SKIP):
		case(E_EXPR_TRUE):
		case(E_EXPR_FALSE):
			break;
	}


	// All of this is not needed in case of a rendez-vous
	if(!leaveUntouched) {
		
		// To be able to fire the transition, both boolean formulas have to be conjuncted, this was already calculated in executables and is reused here
		copy->features = procTrans->features;
#ifdef STOCHASTIC

//printf("before copy->features : "); printBool(copy->features);
		
		//printf("********************** APPLY **********************\n");
		//printf("transition -> %ld : prob %g", ((ptFsmTrans)procTrans->trans)->lineNb, procTrans->prob);

		copy->features = addConjunction(copy->features, createConstant(procTrans->prob), 0, 0);
		//printf("\nstate->features : "); printBool(copy->features);

		//printMinterms(copy->features);
		//printBool(copy->features);
		
		/*printf("\nafter copy->features : "); printBool(copy->features); printf("\n");
		printf("***************************************************\n");*/

#endif
		// Proceed in automaton
		storeNodePointer(copy, maskLookup(copy, procTrans->process->pid), procTrans->trans->target);

		// Set exclusivity of process
		if(procTrans->trans->target && (procTrans->trans->target->flags & N_ATOMIC) == N_ATOMIC) stateSetValue(copy->payload, OFFSET_EXCLUSIVE, T_BYTE, process->pid);
		else stateSetValue(copy->payload, OFFSET_EXCLUSIVE, T_BYTE, NO_PROCESS);

		copy->lastStepPid = procTrans->process->pid;
		stateClean(copy);
#ifdef CLOCK

		copy->zone = zoneFuture(copy->zone, 0);
		if(state->invariant)
			copy->zone = zoneIntersect(copy->zone, state->invariant, 0);
		if(procTrans->guard)
			copy->zone = zoneIntersect(copy->zone, procTrans->guard, 0);

		if(expression->symTab) { // There are clocks to reset
			ptSymTabNode reset = expression->symTab;
			while(reset) {
				copy->zone = zoneReset(copy->zone, reset->name, 0);
				reset = reset->next;
			}
		}

		if(procTrans->trans->target->trans) {
			ptExpNode nextExpr = ((ptFsmTrans) procTrans->trans->target->trans->value)->expression;
			if(nextExpr->type == E_STMNT_WAIT) {
				if(copy->invariant)
					copy->invariant = zoneIntersect(copy->invariant, evalZone(globalSymTab, mtypes, copy, process, nextExpr->children[0]), 0);
				else
					copy->invariant = evalZone(globalSymTab, mtypes, state, process, nextExpr->children[0]);
				storeNodePointer(copy, maskLookup(copy, procTrans->process->pid), ((ptFsmTrans) procTrans->trans->target->trans->value)->target);
			}
		}

		if(copy->invariant) { // No invariant = discrete transition
			copy->zone = zoneIntersect(copy->zone, copy->invariant, 0);
			copy->zone = zoneFuture(copy->zone, 0);
			copy->zone = zoneIntersect(copy->zone, copy->invariant, 0);
		}
		else
			copy->zone = zoneFuture(copy->zone, 0);

#endif
	}


#ifdef DEBUGEXEC
	printf("[/apply]\n");
#endif
	#ifdef PROFILE_EXEC
		PROFILER_END(pr_apply);
	#endif
	return copy;
}



/*
 * Applies an executable transition of the never claim.
 * The function does not duplicate the state. Thus, it is modified.
 */
ptState applyNever(ptSymTabNode globalSymTab, ptMTypeNode mtypes, ptState state, struct fsmTrans_ * transition) {
	storeNodePointer(state, state->never, transition->target);
	return state;
}

/*
 * EXECUTION STACK
 * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * Creates a stack element used by the iterative model-checking algorithm.
 */
ptStackElt createStackElement(ptState state, int nbErrors) {
	ptStackElt elt = new tStackElt();
	if(!elt) failure("Out of memory (creating stack element).\n");
	elt->state = state;
	elt->E_never = NULL;
	elt->E_never_save = NULL;
	elt->E = NULL;
	elt->E_save = NULL;
	elt->nbErrors = nbErrors;
#ifdef CEGARTRANS
	elt->trans = NULL;
	elt->accFeatures = NULL;
#endif
	return elt;
}

/**
 * Destroys a stack element. It means that the two full transition lists
 * will be destroyed, so will the pointer to the stack element itself.
 *
 * Payload and features are NOT destroyed, since they remain in the
 * visited states hashtable.
 */
void destroyStackElement(ptStackElt elt, byte process_or_direct) {
	if(elt) {
		if(elt->E_never_save) listDestroy(elt->E_never_save);
		if(elt->E_save) {
			destroyProcTransList(elt->E_save, process_or_direct);
		}
		if(elt->state) stateDestroy(elt->state, false);
		delete(elt);
	}
}

/**
 * Copies a process transition.
 */
ptProcessTransition copyProcessTransition(ptProcessTransition ptrans) {
	if(!ptrans) return NULL;
	ptProcessTransition copy = new tProcessTransition();
	if(!copy) failure("Out of memory (creating processTransition).\n");
	copy->process = ptrans->process;
	copy->trans = ptrans->trans;
	copy->features = ptrans->features;
	copy->response = copyProcessTransition(ptrans->response);
#ifdef CLOCK
	copy->guard = zoneCopy(ptrans->guard);
#endif
#ifdef STOCHASTIC
	copy->prob = ptrans->prob;
#endif
	return copy;
}

/**
 * Choose randomly a processTransition from a list.
 * The choice is based on a PRNG (see "rngs.c" for details).
 */
ptProcessTransition selectTransition(ptList transList) {
	double randDouble = Random();
	ptList currentTrans = transList;
	int max = 0;
	while(currentTrans) {
		max++;
		currentTrans = currentTrans->next;
	}
	int randInt = (max * randDouble);
	currentTrans = transList;
	while(randInt > 0) {
		currentTrans = currentTrans->next;
		randInt--;
	}
	return (ptProcessTransition) currentTrans->value;
}


void destroyProcessTransition(ptProcessTransition trans) {
	if(trans) {
		destroyProcessTransition(trans->response);
		//destroyBool(trans->features);
#ifdef CLOCK
		zoneDestroy(trans->guard);
#endif
		delete(trans);
	}
}

/**
 * Frees the memory used by processTransition structures contained in a list.
 * The list MUST contain ONLY some ptProcessTransition.
 * However, it does NOT free the memory used by the stateMasks and the fsmTrans.
 * It DOES free the features expression of the processTransition, as well as
 * the one contained in the response transition.
 */
void destroyProcTransList(ptList list, byte process_or_direct) {
	ptList temp;
	while(list) {
		temp = list->next;
		if(process_or_direct == directTrans) {
			ptDirectTransition trans = (ptDirectTransition) list->value;
			if(trans->target) stateDestroy(trans->target, false);
			//if(trans->features) destroyBool(trans->features);
			delete((ptDirectTransition) list->value);
		}
		else {
			destroyProcessTransition((ptProcessTransition) list->value);
		}
		delete(list);
		list = temp;
	}
}


/**
 * Debugging function: accesses each procTrans field (to force segmentation
 * faults if they were voided by error) and prints info to stdout.
 * EFFECTS: None.
 */
void checkProcTransList(ptList list) {
	ptProcessTransition current;
	int i = 0;
	while(list) {
		current = (ptProcessTransition) list->value;
		list = list->next;
		printf("     - Trans %d\n", i);

		printf("       features");
		if(!current->features) printf(" = NULL");
		;//else printBool(current->features);
		printf("\n");

		printf("       process  = %s\n", current->process ? "OK" : "NULL");
		printf("       trans    = %s\n", current->trans ? "OK" : "NULL");
		i++;
	}
}

byte isProbabilisticTransList(ptList list){
    double res = 0.;
    
    if(listCount(list) == 1)
        return 0;
    
    while(list){
        if((res += ((ptProcessTransition)list->value)->prob) > 1.)
            return 0;
        list = list->next;
    }
    return 1;
}

/**
 * Will print a stack in reverse (!) order, when the "loopBegin" state is encountered
 * a message "loop begins here" will be printed before the state.
 *
 * The stack MUST contain ONLY ptState pointers as values.
 * This functions highly depends on the implementation of the stack.
 * If that implementation was to be modified, this function must be changed as well.
 */
void printStackElementStack(ptSymTabNode globalSymTab, ptMTypeNode mtypes, ptStack stackPtr, ptState loopBegin, ptStackElt prevTopElt) {
	stackPtr = reverse(stackPtr, 1);
	ptStack curLevel = stackPtr;
	ptState curState;
	ptState prev = NULL;
	if(prevTopElt) prev = prevTopElt->state;

	while(curLevel) {
		curState = ((ptStackElt) curLevel->value)->state;
		if(loopBegin && (curState == loopBegin || (curState->payloadHash == loopBegin->payloadHash && memcmp(curState->payload, loopBegin->payload, curState->payloadSize) == 0))) {
			printf("    -- Loop beings here --\n    --\n");
			printState(mtypes, curState, prev);
			prev = NULL;
			printf("    -- Loop begin repeated in full:\n");
		}
		printState(mtypes, curState, prev);
		prev = curState;
		curLevel = curLevel->prev;
	}

	if(loopBegin == NULL && prev && stackPtr && ((ptStackElt) top(stackPtr))->state != prev) {
		printf("    -- Final state repeated in full:\n");
		printState(mtypes, prev, NULL); // repeat the last state in full
	}

	destroyStack(stackPtr);
}

/**
 * Destroys a stack of stack elements.
 */
void destroyStackElementStack(ptStack stackPtr, byte process_or_direct) {
	ptStack temp;
	while(stackPtr) {
		temp = stackPtr->prev;
		destroyStackElement((ptStackElt) stackPtr->value, process_or_direct);
		stackPtr = temp;
	}
}

/**
 * Debugging functions
 */
void checkStackElementStack(ptStack stack) {
	ptStackElt current;
	int i = 0;
	printf(" ******\nChecking stack..\n");
	while(stack) {
		current = (ptStackElt) stack->value;
		stack = stack->prev;

		printf(" - Item %d:\n", i);
		if(!current->state) printf("   state = NULL  ->  ERROR\n");
		else printf("   State: %u\n", current->state->payloadHash);

		printf("   state->E: \n");
		if(!current->E) printf("    = NULL\n");
		else checkProcTransList(current->E);

		printf("   state->E_save: \n");
		if(!current->E_save) printf("    = NULL\n");
		else checkProcTransList(current->E_save);
/*
		printf("   state->E_never: \n");
		if(!current->E_never) printf("    = NULL\n");
		else listCheck(current->E_never);

		printf("   state->E_never_save: \n");
		if(!current->E_never_save) printf("    = NULL\n");
		else listCheck(current->E_never_save);*/

		i++;
	}
	printf("Check done.\n ******\n");
}


/*
 * NORMAL EXECUTION (NO VERIFICATION)
 * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * Executes the program until no transition can be fired or until maxStep reaches 0.
 * If you do not want to set a maxStep value, give it a negative value.
 * Then, the execution will continue until the program has no transition available.
 * In that case, it also means that an infinite loop will result in an infinite execution.
 */
void launchExecution(ptSymTabNode globalSymTab, ptMTypeNode mtypes) {
	// Initialise
	ptState init = stateCreateInitial(globalSymTab, mtypes);
	byte assertViolated;
	//initSolverWithFD(getFeatureModelClauses());
	long int nbStatesExplored = 1;
	ptState state = init, prev = NULL;
	ptState nextState;
	ptProcessTransition nextTrans;
	ptList E, E_;
	E = executables(globalSymTab, mtypes, state, 0, 0, NULL, NULL, NULL, NULL, NULL);
	while(E) {
		if(limitExploration && nbStatesExplored >= limitExploration) {
			printf("Reached limit of %ld states to explore.\n", limitExploration);
			exit(EXIT_NO_VERIFICATION);
		}
		nextTrans = selectTransition(E);
		nextState = apply(globalSymTab, mtypes, state, nextTrans, 0, &assertViolated);
		nextState->lastStepPid = nextTrans->process->pid;
		//stateDestroy(state);
		state = nextState;
		destroyProcTransList(E, processTrans);
		if(assertViolated) printf("Assert at line %d violated.\n", nextTrans->trans->lineNb);
		prev = state;
		E = executables(globalSymTab, mtypes, state, 0, 0, NULL, NULL, NULL, NULL, NULL);
		nbStatesExplored++;
	}
	ptStateMask currentSM = state->mask;
	stateDestroy(state, false);
	printf("End of execution.\n");
}
