#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "error.h"

#include "state.hpp"
#include "symbols.hpp"
#include "ast.hpp"
#include "automata.hpp"


#ifdef PROFILE_STATE
	PROFILER_REGISTER(pr_stateOnStack, "stateOnStack", 200);
	PROFILER_REGISTER(pr_pr_stateDuplicate, "pr_stateDuplicate", 10);
#endif

/**
 * Adds the global variables in the memory chunk.
 *
 * Does not set the payloadHash.
 */
state::state(const symTable* globalSymTab, const fsm* stateMachine) 
	: globalSymTab(globalSymTab)
	, stateMachine (stateMachine)
	, first(nullptr)
	, last(nullptr)
	, never(nullptr)
	, chanRefs(nullptr)
	, nbProcesses(0)
	, lastStepPid(0)
	, payload(nullptr)
	, payloadSize(SYS_VARS_SIZE)
	, payloadHash(0)
{

	/*this->first = new process();
	this->first->sym = globalSymTab;
	this->first->pid = -1;
	this->first->offset = 0;
	this->first->next = nullptr;
	this->last = this->first;
	this->lastStepPid = 0;*/
	//this->features = getTrue();

	for (auto sym : globalSymTab->getSymbols<const varSymNode*>()) {
		
		setSymOffset(sym, this->payloadSize);
		
		if (sym->getType() == symbol::T_CHAN) {
			addChannel(dynamic_cast<const chanSymNode*>(sym));
		}
		else {
			addVariable(sym);
		}
	}
	// if(verbosity == VERBOSITY_HIGH) printf("Total memory used by global variables (in bytes): %d.\n", this->payloadSize);
	this->payload = calloc(1, this->payloadSize);

	/**
	 * Runs every process with the attribute "active".
	 * Cardinalities are taken into account.
	 * Also, links the "never claim" FSM, if it exists, with the state.
	 */
	for (const auto sym : globalSymTab->getSymbols()) {
		if(sym->getType() == symbol::T_PROC) {
			auto procSym = dynamic_cast<const procSymNode*>(sym);
			expr* inst = procSym->getActiveExpr();
			if(!inst)
				this->addProctype(procSym);
			else if(inst->getType() == astNode::astNode::E_EXPR_CONST) {
				auto cstExpr = dynamic_cast<const exprConst*>(inst);
				assert(cstExpr);
				int bound = cstExpr->getCstValue();
				for (int i = 0; i < bound; i++) {
					this->addProctype(procSym);
				}
			} else {
				assert(false);
			}
		} else if(sym->getType() == symbol::T_NEVER) {
			auto neverSym = dynamic_cast<const neverSymNode*>(sym);
			assert(neverSym);
			this->addNever(neverSym);
		}
	}

	// No process is executing something atomic
	this->setValue(OFFSET_EXCLUSIVE, NO_PROCESS);
	// No rendezvous has been requested.
	this->setValue(OFFSET_HANDSHAKE, NO_HANDSHAKE);
	this->initGlobalVariables();

	/*for(auto e : symPtr){
		std::cout << "symbol " << std::string(*e.first) << " at : "<<e.second<<"\n";
	}*/
}

/*
 * STATE DUPLICATION
 * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * Duplicates a list of stateMasks.
 */

process::process(void) 
	: sym(nullptr)
	, pid(-1)
	, varOffset(0)
	, next(nullptr)
{}


process::process(const process& p) 
	: sym(p.sym)
	, pid(p.pid)
	, varOffset(p.varOffset)
	, next(nullptr)
{
	if(p.next)
		next = new process(*p.next);
}

process::~process() {
	if(next)
		delete next;
}



channelRef::channelRef(void)
	: channelOffset(0)
	, chanSym(nullptr)
	, next(nullptr)
{
}

/**
 * Duplicates a list of chanRefs.
 */
channelRef::channelRef(const channelRef& c)
	: channelOffset(c.channelOffset)
	, chanSym(c.chanSym)
	, next(nullptr)
{
	if(c.next)
		next = new channelRef(*c.next);
}

channelRef::~channelRef(){
	if(next)
		delete next;
}

/**
 * Duplicates a state.
 *
 * This function does NOT duplicate the boolean formula of the state.  This is because it is only
 * used in apply() and there the copy of the boolean formula is of no use.
 */
state::state(const state& s) 
	: nbProcesses(s.nbProcesses)
	, payloadSize(s.payloadSize)
	, payloadHash(s.payloadHash)
{
	
	this->payload = nullptr;
	if(this->payloadSize > 0) {
		this->payload = malloc(this->payloadSize);
		memcpy(this->payload, s.payload, this->payloadSize);
	}

	this->lastStepPid = s.lastStepPid;
	//this->features = nullptr; // see function description
	this->never = new process(*s.never);
	this->chanRefs = new channelRef(*s.chanRefs);

	// Copying processes information
	this->first = new process(*s.first);
	this->last = this->first;
	if(this->last) {
		while(this->last->next) this->last = this->last->next;
	}
}

/**
 * Frees the memory used by a given state. It does NOT free any symbol tables, FSM or mtypes list.
 * However, it DOES free:
 *  - the memory chunk,
 *  - all state procs of active processes,
 *  - the state proc of the never claim (if any),
 *  - all channel references,
 *
 * If the keepPayloadAndFeatures parameter is false, it also frees:
 *  - boolean formula and
 *  - the state structure itself.
 *
 * This parameter is only true when destroying a stack element where the payload and boolean function
 * are still used in the visited states hashtable.
 */

state::~state() {

	if(first)
		delete first;

	if(chanRefs)
		delete chanRefs;

	if(this->never) 
		delete this->never; 

	free(this->payload);
}

static byte _timeout = 0;
static byte _else = 0;

int state::eval(unsigned int procOffset, const astNode* node, byte flag) const {

	assert(node);
	if(!node)	
		return 0;

	byte foundFeature = 0;
	unsigned int offset, chanOffset;
	int returnValue = -1;
	chanSymNode* channel;
	symbol* sym;
	unsigned int handshake = getValue<unsigned int>(OFFSET_HANDSHAKE);

	if(flag == EVAL_EXECUTABILITY && handshake != NO_HANDSHAKE && node->getType() != astNode::E_STMNT_CHAN_RCV) 
		returnValue = 0;

	else {

		auto binaryExpr = dynamic_cast<const exprBinary*>(node);
		auto unaryExpr = dynamic_cast<const exprUnary*>(node);

		switch(node->getType()) {

			case(astNode::E_VAR_DECL):
			case(astNode::E_PROC_DECL):
			case(astNode::E_CHAN_DECL):
			case(astNode::E_INIT_DECL):
			case(astNode::E_INLINE_DECL):
			case(astNode::E_TDEF_DECL):
			case(astNode::E_MTYPE_DECL):

			case(astNode::E_STMNT_IF):
			case(astNode::E_STMNT_DO):
			case(astNode::E_STMNT_OPT):
			case(astNode::E_STMNT_SEQ):
			case(astNode::E_STMNT_BREAK):
			case(astNode::E_STMNT_GOTO):
			case(astNode::E_STMNT_LABEL):
			case(astNode::E_STMNT_ASGN):
			case(astNode::E_STMNT_PRINT):
			case(astNode::E_STMNT_PRINTM):
			case(astNode::E_STMNT_ASSERT):

			case(astNode::E_EXPR_RUN):
			case(astNode::E_EXPR_TRUE):
			case(astNode::E_EXPR_SKIP):
			
				returnValue = 1;
				break;

			case(astNode::E_STMNT):
			case(astNode::E_STMNT_EXPR):
			
			case(astNode::E_EXPR_PAR):
			case(astNode::E_EXPR_VAR):
			
			case(astNode::E_ARGLIST):
			case(astNode::E_RARG_VAR):
			case(astNode::E_RARG_EVAL):
			{
				if(node->getType() == astNode::E_ARGLIST)
					assert(false);

				//these types have only one node...
				returnValue = eval(procOffset, *node->getChildren().cbegin(), flag);
				break;
			}
/*
			case(astNode::E_STMNT_CHAN_RCV):
				sym = nodeSymbolLookUpLeft(node->children[0]);
				channel = nodeSymbolLookUpRight(node->children[0]);
				if(symbol->global == 0)
					chanOffset = getVarOffset(globalSymTab, mtypes, state, process, process->offset, node->children[0]);
				else
					chanOffset = getVarOffset(globalSymTab, mtypes, state, process, 0, node->children[0]);
				if(channel->type == T_CID) {
						chanOffset = stateGetValue(state->payload, chanOffset, T_CID);
						channel = getChannelSymTab(state, chanOffset);
				}
				if(!channel) {
					printState(mtypes, state, NULL);
					failure("ERROR (eval (astNode::E_STMNT_CHAN_RCV, line %02d)): chanOffset (%d) does not reference any existing channel.\n", node->lineNb, chanOffset);
				}
				if (channel->capacity == 0) {
					if(handshake != chanOffset)
						// Handshake request does not concern the channel.
						return 0;
				}
				if (channelIsEmpty(globalSymTab, mtypes, state, process, node->children[0]))
					return 0;
				else {
					// Either a rendezvous concerns the channel, either the channel has a non null capacity and is not empty.
					ptExpNode currentArg = node->children[1];
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

							if (eval(procOffset, currentArg->children[0], flag) != sendValue) {
								returnValue = 0;
								stop = 1;
							}
						} else {
							symbol = nodeSymbolLookUpLeft(currentArg->children[0]);
							if (!symbol) {
								if(channel->capacity == 0) {
									varOffset = param->memOffset;//chanOffset + param->memOffset + 1;
									sendValue = stateGetValue(_handshake_transit, varOffset, param->type);
								} else {
									varOffset = chanOffset + param->memOffset + 1;
									sendValue = stateGetValue(state->payload, varOffset, param->type);
								}

								returnValue = eval(procOffset, currentArg->children[0], EVAL_EXPRESSION, ADD());
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

			case(astNode::E_STMNT_CHAN_SND):
				symbol = nodeSymbolLookUpLeft(node->children[0]);
				channel = nodeSymbolLookUpRight(node->children[0]);
				if(symbol->global == 0)	offset = getVarOffset(globalSymTab, mtypes, state, process, process->offset, node->children[0]);
				else	offset = getVarOffset(globalSymTab, mtypes, state, process, 0, node->children[0]);
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
				} else returnValue = (!channelIsFull(globalSymTab, mtypes, state, process, node->children[0]));
				break;
*/
			case(astNode::E_STMNT_INCR):
			case(astNode::E_STMNT_DECR):
				if(flag == EVAL_EXECUTABILITY) 
					returnValue = 1;
				else 
					returnValue = eval(procOffset, *node->getChildren().cbegin(), flag);
				break;

			case(astNode::E_STMNT_ELSE):
				returnValue = (_else == 1);
				break;
			
			case(astNode::E_EXPR_PLUS):
				returnValue = eval(procOffset, binaryExpr->getLeftExpr(), flag) + eval(procOffset, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_MINUS):
				returnValue = eval(procOffset, binaryExpr->getLeftExpr(), flag) - eval(procOffset, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_TIMES):
				returnValue = eval(procOffset, binaryExpr->getLeftExpr(), flag) * eval(procOffset, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_DIV):
				returnValue = eval(procOffset, binaryExpr->getLeftExpr(), flag) / eval(procOffset, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_MOD):
				returnValue = eval(procOffset, binaryExpr->getLeftExpr(), flag) % eval(procOffset, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_GT):
				returnValue = (eval(procOffset, binaryExpr->getLeftExpr(), flag) > eval(procOffset, binaryExpr->getRightExpr(), flag));
				break;

			case(astNode::E_EXPR_LT):
				returnValue = (eval(procOffset, binaryExpr->getLeftExpr(), flag) < eval(procOffset, binaryExpr->getRightExpr(), flag));
				break;

			case(astNode::E_EXPR_GE):
				returnValue = (eval(procOffset, binaryExpr->getLeftExpr(), flag) >= eval(procOffset, binaryExpr->getRightExpr(), flag));
				break;

			case(astNode::E_EXPR_LE):
				returnValue = (eval(procOffset, binaryExpr->getLeftExpr(), flag) <= eval(procOffset, binaryExpr->getRightExpr(), flag));
				break;

			case(astNode::E_EXPR_EQ):
				returnValue = (eval(procOffset, binaryExpr->getLeftExpr(), flag) == eval(procOffset, binaryExpr->getRightExpr(), flag));
				break;

			case(astNode::E_EXPR_NE):
				returnValue = (eval(procOffset, binaryExpr->getLeftExpr(), flag) != eval(procOffset, binaryExpr->getRightExpr(), flag));
				break;

			case(astNode::E_EXPR_AND):
				returnValue = 0;
				if(eval(procOffset, binaryExpr->getLeftExpr(), flag)) 
					returnValue = eval(procOffset, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_OR):
				returnValue = eval(procOffset, binaryExpr->getLeftExpr(), flag);
				if(returnValue == 0) returnValue = eval(procOffset, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_UMIN):
				returnValue = - eval(procOffset, unaryExpr->getExpr(), flag);
				break;

			case(astNode::E_EXPR_NEG):
				returnValue = !eval(procOffset, unaryExpr->getExpr(), flag);
				break;

			case(astNode::E_EXPR_LSHIFT):
				returnValue = eval(procOffset, binaryExpr->getLeftExpr(), flag) << eval(procOffset, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_RSHIFT):
				returnValue = eval(procOffset, binaryExpr->getLeftExpr(), flag) >> eval(procOffset, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_BITWAND):
				returnValue = eval(procOffset, binaryExpr->getLeftExpr(), flag) & eval(procOffset, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_BITWOR):
				returnValue = eval(procOffset, binaryExpr->getLeftExpr(), flag) | eval(procOffset, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_BITWXOR):
				returnValue = eval(procOffset, binaryExpr->getLeftExpr(), flag) ^ eval(procOffset, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_BITWNEG):
				returnValue = ~eval(procOffset, unaryExpr->getExpr(), flag);
				break;

			case(astNode::E_EXPR_COND):
			{
				auto cond = dynamic_cast<const exprCond*>(node);
				if(eval(procOffset, cond->getCond(), EVAL_EXPRESSION) > 0)
					returnValue = eval(procOffset, cond->getThen(), flag);
				else
					returnValue = eval(procOffset, cond->getElse(), flag);
				break;
			}

			case(astNode::E_EXPR_LEN):
				returnValue = channelLen(procOffset, dynamic_cast<const exprLen*>(node)->getExpr());
				break;

			case(astNode::E_EXPR_CONST):
				returnValue = dynamic_cast<const exprConst*>(node)->getCstValue();
				break;

			case(astNode::E_EXPR_TIMEOUT):
				returnValue = _timeout;
				break;

			case(astNode::E_EXPR_FULL):
				returnValue = channelIsFull(procOffset, dynamic_cast<const exprLen*>(node)->getExpr());
				break;

			case(astNode::E_EXPR_NFULL):
				returnValue = !channelIsFull(procOffset, dynamic_cast<const exprNFull*>(node)->getExpr());
				break;

			case(astNode::E_EXPR_EMPTY):
				returnValue = channelIsEmpty(procOffset, dynamic_cast<const exprEmpty*>(node)->getExpr());
				break;

			case(astNode::E_EXPR_NEMPTY):
				returnValue = !channelIsEmpty(procOffset, dynamic_cast<const exprNEmpty*>(node)->getExpr());
				break;


			case(astNode::E_VARREF):
			{
				auto varRef = dynamic_cast<const exprVarRef*>(node);
				auto sym = varRef->getFinalSymbol();
				returnValue = getValue<int>(getVarOffset(sym, (sym->isGlobal()? 0 : procOffset + this->offset.at(sym)), varRef));
			}
			case(astNode::E_VARREF_NAME):
			{
				auto varRef = dynamic_cast<const exprVarRefName*>(node);
				auto sym = varRef->getSymbol();
				returnValue = getValue<int>(getVarOffset(sym, (sym->isGlobal()? 0 : procOffset + this->offset.at(sym)), varRef));
				break;
			}

			
			case(astNode::E_RARG_CONST):
			{
				returnValue = dynamic_cast<const exprRArgConst*>(node)->getCstValue();
				break;
			}
			case(astNode::E_EXPR_FALSE):
			{
				returnValue = 0;
				break;
			}
			default:
				assert(false);
		}
	}
	return returnValue;
}
/*
 * ACCESS AND MODIFICATION OF VARIABLES
 * * * * * * * * * * * * * * * * * * * * * * * */

const fsmNode* state::getNodePointer(const process* proc) const {
	const fsmNode** nodePtr = reinterpret_cast<const fsmNode**>((((byte*)this->payload) + proc->varOffset - sizeof(fsmNode*)));
	assert(nodePtr);
	return *nodePtr;
}

void state::storeNodePointer(process* proc, const fsmNode* pointer) {
	assert(proc);
	assert(pointer);

	const fsmNode** nodePtr = reinterpret_cast<const fsmNode**>((((byte*)this->payload) + proc->varOffset - sizeof(fsmNode*)));
	assert(nodePtr);
	*nodePtr = pointer;
}

/**
 * state is necessary to evaluate the index of an array expression.
 * Give the offset of the variable referenced by a E_VARREF expression.
 * On first call, preOffset must have the same value as the offset of its environment (i.e. global or process).
 * /!\ process is the environment in which the variable is ANALYZED, NOT in the one the variable is DEFINED.
 */
unsigned int state::getVarOffset(const symbol* sym, unsigned int preOffset, const expr* expr) const {
	if(expr->getType() == astNode::E_RARG_VAR) {
		auto var = dynamic_cast<const exprVar*>(expr);
		assert(var);
		return this->getVarOffset(sym, preOffset, var);

	} else if(expr->getType() == astNode::astNode::E_EXPR_VAR) {
		auto var = dynamic_cast<const exprVar*>(expr);
		assert(var);
		return this->getVarOffset(sym, preOffset, var);
	
	} else if(expr->getType() == astNode::E_VARREF) {
		auto varRef = dynamic_cast<const exprVarRef*>(expr);
		assert(varRef);
		unsigned int highOffset = this->getVarOffset(sym, preOffset, varRef->getField());
		if(!varRef->getSubField())
			return highOffset;
		else
			return this->getVarOffset(sym, highOffset, varRef->getSubField());

	} else if (expr->getType() == astNode::E_VARREF_NAME) {
		auto varRefName = dynamic_cast<const exprVarRefName*>(expr);
		sym = varRefName->getSymbol();
		int index = 0;
		
		if(varRefName->getIndex())
			index = this->eval(preOffset, varRefName->getIndex(), EVAL_EXPRESSION);
		
		if(sym->getType() == symbol::T_CHAN) {
			auto chanSym = dynamic_cast<const chanSymNode*>(varRefName->getSymbol());
			assert(chanSym);
			if(chanSym->getCapacity() != 0) 
				return preOffset + offset.at(chanSym) + (chanSym->getTypeSize() + 1) * index;
			else
				return preOffset + offset.at(chanSym) + index;
		}
		else
			return preOffset + offset.at(sym) + sym->getTypeSize() * index;
	}
	assert(false);
	return 0; // only to please compiler
}


/**
 * Stores 'nb' bytes in a memory chunk, at offset 'offset'.
 * Those bytes are read from the byte array 'values'.
 * The array is not freed afterward.
 *
 * Does not change the payloadHash.
 */
void state::storeValues(unsigned int offset, int nb, const byte * values) {
	byte* bytePtr = reinterpret_cast<byte*>(this->payload);
	assert(bytePtr);
	bytePtr += offset;
	
	for(int i = 0; i < nb; i++) 
		*(bytePtr + i) = values[i];
}

/**
 * Reads 'nb' bytes in a memory chunk of the state, at offset 'offset', puts them in an array of byte and returns it.
 */
const byte* state::readValues(unsigned int offset, int nb) const {
	byte* bytePtr = reinterpret_cast<byte*>(this->payload);
	assert(bytePtr);
	bytePtr += offset;

	byte* values = (byte*) calloc(nb, sizeof(byte));
	for(int i = 0; i < nb; i++)
		values[i] = *(bytePtr + i);
	return values;
}

/**
 * Returns the stateMask of a given pid.
 */
process* state::getProc(int pid) const {
	process* proc = this->first;
	while (proc->pid != pid) {
		proc = proc->next;
		if(!proc)
			return nullptr;
	}
	return proc;
}

/**
 * Gets the symbol table of a channel by giving its offset in the memory chunk.
 * The structure contained in this->chanRefs is used to get the table.
 * If no channel exists at the given offset, returns nullptr.
 */
const chanSymNode* state::getChannelSymTab(unsigned int chanOffset) const {
	channelRef* currentRef = this->chanRefs;
	while(currentRef) {
		for(unsigned int i = 0; i < currentRef->chanSym->getBound(); i++) {
			auto currentOffset = currentRef->channelOffset + (currentRef->chanSym->getType() + 1) * i;
			if(currentOffset == chanOffset)
				return currentRef->chanSym;
		}
		currentRef = currentRef->next;
	}
	return nullptr;
}

unsigned int padding(const varSymNode* varSym){
	switch(varSym->getType()){
		case symbol::T_BIT:
		case symbol::T_BOOL:
		case symbol::T_BYTE:
		case symbol::T_CID:
		case symbol::T_CHAN:
		case symbol::T_MTYPE:
		case symbol::T_PID:
			return 1;
		
		case symbol::T_SHORT:
			return 2;

		case symbol::T_INT:
			return 4;
		
		case symbol::T_UTYPE:
			return padding(*dynamic_cast<const utypeSymNode*>(varSym)->getUType()->getFields().cbegin());

		default:
			assert(false);
			return -1;
	}
	return -1;
}

void state::setSymOffset(const varSymNode* varSym, unsigned int preOffset) {
	//assert(payloadSize >= preOffset);

	if(offset.find(varSym) != offset.end())
		return;

	unsigned int pad = preOffset % padding(varSym);
	offset[varSym] = preOffset + pad;
	payloadSize += pad;
	

	if(varSym->getType() == symbol::T_UTYPE){
		for(auto field : dynamic_cast<const utypeSymNode*>(varSym)->getUType()->getFields()){
			setSymOffset(field, preOffset);
			preOffset += pad + field->getSizeOf();
		}
	}
}

/*
 * ACCESS AND MODIFICATION OF LARGE STATE CHUNKS
 * * * * * * * * * * * * * * * * * * * * * * * */

// TODO: differences between the three following functions?

/**
 * Helper for killProctype and and initVariables
 */

void state::initSym(unsigned int preOffset, const varSymNode* varSym) {
	if(varSym->getType() == symbol::T_UTYPE) {
		for(auto field : dynamic_cast<const utypeSymNode*>(varSym)->getUType()->getFields()){
			initSym(preOffset, field);
		}
	} else {
		if(varSym->getInitExpr() && varSym->getInitExpr()->getType() == astNode::astNode::E_EXPR_CONST)
			this->setValue(preOffset + offset.at(varSym), dynamic_cast<const exprConst*>(varSym->getInitExpr()));
	}
}

void state::initSymTab(unsigned int preOffset, const symTable* symTab) {
	for(auto varSym : symTab->getSymbols<const varSymNode*>()) {
		initSym(preOffset, varSym);
	}
}

/**
 * Helper for stateCreateInitial and addProctype
 *
 * Initialises all variables in a state.  The proc is used to get the symbol table.
 *
 * Does not change the payloadHash.
 */

void state::initGlobalVariables(void) {
	this->initSymTab(0, globalSymTab);
}

void state::initVariables(const process* proc) {
	this->initSymTab(proc->varOffset, proc->sym->getSymTable());
}

/**
 * Helper for addProctype
 *
 * Initiate the bytes stored in a given chunk of memory.
 * Offset must be counted in bytes.
 */
void initValues(void* startPtr, unsigned int offset, int bytesNbr, byte value) {
	memset(reinterpret_cast<byte*>(startPtr) + offset, value, bytesNbr);
}

/**
 * Helper for killProctype
 *
 * Removes the channels references whose offset is between infBound and supBound (both included).
 */
void state::removeChannelRefs(unsigned int infBound, unsigned int supBound) {
	channelRef* freePtr = this->chanRefs;
	channelRef* currentRef = this->chanRefs;
	while(currentRef->channelOffset >= infBound && currentRef->channelOffset <= supBound) {
		this->chanRefs = this->chanRefs->next;
		delete(currentRef);
		currentRef = this->chanRefs;
	}
	while(currentRef->next) {
		if(currentRef->next->channelOffset >= infBound && currentRef->next->channelOffset <= supBound) {
			freePtr = currentRef->next;
			currentRef->next = currentRef->next->next;
			delete freePtr;
		}
		else	
			currentRef = currentRef->next;
	}
}


void state::addChannel(const chanSymNode* chanSym, const process* chanProc){
	assert(chanSym);
	channelRef* oldRef = this->chanRefs;
	this->chanRefs = new channelRef();
	this->chanRefs->channelOffset = this->payloadSize;
	this->chanRefs->chanSym = chanSym;
	this->chanRefs->next = oldRef;

	
	//this->payloadSize += (1 + chanSym->getTypeSize()) * chanSym->getBound();
	for(int i = 0; i < chanSym->getBound(); ++i){
		
		varOffset[std::make_tuple<>(chanProc, chanSym, i)] = this->payloadSize++;
		
		if (chanSym->getCapacity() != 0) {
			for(int j = 0; j < chanSym->getCapacity(); ++j){
				for(auto varSym: chanSym->getTypeList())
					addVariable(varSym, chanProc);
			}
		}
	}
}

void state::addVariable(const varSymNode* varSym, const process* varProc){
	assert(varSym);
	
	unsigned int pad = payloadSize % padding(varSym);
	payloadSize += pad;

	for(int i = 0; i < varSym->getBound(); ++i){
		
		varOffset[std::make_tuple<>(varProc, varSym, i)] = payloadSize;
		
		if(varSym->getType() == symbol::T_UTYPE){
			auto utype = dynamic_cast<const utypeSymNode*>(varSym)->getUType();
			for(auto field : utype->getFields())
				addVariable(field, varProc);
		
		} else
			payloadSize += varSym->getTypeSize();
	}
}

/**
 * Reserves some memory for the proctype variables in the memory chunk.
 * Returns the pid of the newly created process.
 *
 * Does not change the payloadHash.
 */
int state::addProctype(const procSymNode* procType){
	
	process* newProc = new process();
	newProc->sym = procType;

	if(!this->first)
		this->first = newProc;

	if(this->last) {
		newProc->pid = this->last->pid+1;
		this->last->next = newProc;
	}
	
	this->last = newProc;

	payloadSize += sizeof(fsmNode*);
	newProc->varOffset = payloadSize;

	auto oldSize = payloadSize;

	for(auto varSym : procType->getSymTable()->getSymbols<const varSymNode*>()) {
		if(varSym->getType() == symbol::T_CHAN)
			addChannel(dynamic_cast<const chanSymNode*>(varSym), newProc);
		else
			addVariable(varSym, newProc);
	}

	this->payload = realloc(this->payload, this->payloadSize);
	this->storeNodePointer(newProc, stateMachine->getFsmWithName(procType->getName()));
	initValues(this->payload, oldSize, this->payloadSize, 0);

	this->nbProcesses++;
	
	this->initVariables(newProc);
	return newProc->pid;
}

/**
 * Defines the never claim of the execution.
 *
 * Does not change the payloadHash.
 */
void state::addNever(const neverSymNode* neverSym) {
	this->never = new process();
	this->never->pid = -2;
	this->never->varOffset = SYS_VARS_SIZE;
	this->never->next = nullptr;
	this->never->sym = neverSym;
	this->storeNodePointer(this->never, stateMachine->getFsmWithName(neverSym->getName()));
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
void state::killProctype(int pid) {
	process* previous = this->first;
	process* searchStateMask = this->last;
	if(searchStateMask->pid == pid) {
		/* Destroying the references of the channels that were declared in the killed process. */
		this->removeChannelRefs(searchStateMask->varOffset, this->payloadSize);
		while(previous->pid != searchStateMask->pid) {
			this->last = previous;
			previous = previous->next;
		}
		this->last->next = nullptr;
		this->nbProcesses--;
		this->payloadSize = searchStateMask->varOffset - sizeof(fsmNode*);
		this->payload = realloc(this->payload, this->payloadSize * sizeof(byte));
		searchStateMask->sym = nullptr;
		searchStateMask->next = nullptr;
		delete searchStateMask;
	}
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
byte state::compare(const void* s2Payload) const {
	if(!s2Payload)
		return STATES_DIFF;
	if(memcmp(payload, s2Payload, payloadSize) != 0)	
		return STATES_DIFF;

	// Now that we know both states are identical, we check whether:
	//  s1 -> s2
	//
	// If this holds, then s1 is reachable in less products, which means
	//                that it can be considered as visited.
	// It not,        then s1 is reachable by at least one product that
	//                was not previously explored, so it contains some
	//                fresh info, and exploration must continue.

	// Convention: nullptr means 'true'.
	/*if(!s2Features) return STATES_SAME_S1_VISITED;
	if(!s1->features) return STATES_SAME_S1_FRESH;	// Here we do not check the case in which s2->features != nullptr but still a tautology;
													// There is a compilation parameter CHECK_TAUTOLOGY that can be set to check for
													// tautologies before they end up here.

	if(implies(s1->features, s2Features)) return STATES_SAME_S1_VISITED;
	*/
	return STATES_SAME_S1_FRESH;
}

/**
 * Tries to remove every terminated process. (See "killProctype" for exact effect).
 */
void state::clean(void) {
	while(this->last->pid >= 0 && !getNodePointer(this->last))
		this->killProctype(this->last->pid);
}

/*
 * STATE PRINTING
 * * * * * * * * * * * * * * * * * * * * * * * */

/*void printChanState(ptMTypeNode mtypes, char varNameParent[200], byte* printedSomething, state* state, state* diffState, process* stateMask, ptSymTabNode channel, int varIndex, int processOffset);
void printfTypedefState(ptMTypeNode mtypes, char varNameParent[200], byte* printedSomething, state* state, state* diffState, process* stateMask, ptSymTabNode utypeFields, ptSymTabNode parent, int varIndex, int processOffset, int varOffset);

/**
 * Function for printing user types.
 */
/*void printfTypedefState(ptMTypeNode mtypes, char varNameParent[200], byte* printedSomething, state* state, state* diffState, process* stateMask, ptSymTabNode utypeFields, ptSymTabNode parent, int varIndex, int processOffset, int varOffset) {
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
				value = stateGetValue(this->payload, processOffset+realOffset, currentSTN->type);
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
/*void printChanState(ptMTypeNode mtypes, char varNameParent[200], byte* printedSomething, state* state, state* diffState, process* stateMask, ptSymTabNode channel, int varIndex, int processOffset) {
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
					value = stateGetValue(this->payload, realOffset, symbol->type);
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
/*void state::printState(const state* diffState) {
	process* currentSM = this->first;
	process* currentDiffSM = diffState ? diffState->proc : nullptr;
	ptSymTabNode currentSTN;
	fsmNode* node, diffnode = nullptr;
	int offset, i, value;
	char varName[200];
	char varNameBase[200];

	byte printedSomething = 0;

	// printf("   %-30s = %u\n", "State hash", this->payloadHash);
	byte printFeature;
	if(trace == FULL_TRACE || !diffState) printFeature = 1;
	else if(this->features.Nil() && !diffState->features.Nil()) printFeature = 1;
	else if(!this->features.Nil() && diffState->features.Nil()) printFeature = 1;
	else {
		ADD diffNeg = negateBool(diffState->features, 0);
		ADD conjunct = addConjunction(diffNeg, this->features, 0, 1);
		printFeature = isSatisfiable(conjunct);
	}

	if(printFeature) {
		printedSomething = 1;
		printf("   %-35s = \n", "features");
		printBool(this->features);
	} else printf("/");
	
	printf("\n");
	
#ifdef CLOCK
	printZone(this->zone);
	printf("\n");
#endif
	if(this->never) {
		node = getNodePointer(state, this->never);
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
		if(currentDiffSM && currentDiffSM->pid != currentSM->pid) currentDiffSM = nullptr;

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

					if (currentSTN->type == T_UTYPE)	 printfTypedefState(mtypes, varName, &printedSomething, state, currentDiffSM ? diffState : nullptr, currentSM, currentSTN->utype->child, currentSTN, i, currentSM->offset, currentSTN->memOffset);
					else if (currentSTN->type == T_CHAN) printChanState(mtypes, varName, &printedSomething, state, currentDiffSM ? diffState : nullptr, currentSM, currentSTN, i, currentSM->offset);
					else {
						offset = currentSM->offset + currentSTN->memOffset + getTypeSize(currentSTN->type)*i;
						value = stateGetValue(this->payload, offset, currentSTN->type);
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

		currentDiffSM = currentDiffSM ? currentDiffSM->next : nullptr;
		currentSM = currentSM->next;
	}

	if(printedSomething) printf("    --\n");
}

/**
 * Debugging function: prints the raw bytes (as integers) of the payload
 */
/*void printPayload(state* state) {
	int i;
	for(i = 0; i < this->payloadSize; i++) {
		printf("%u ", *(((byte*)this->payload)+i));
	}
	printf("\n\n");
}*/