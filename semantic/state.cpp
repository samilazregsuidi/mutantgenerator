#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "error.h"

#include "state.hpp"
#include "process.hpp"

#include "ast.hpp"
#include "automata.hpp"

#include "variable.hpp"
#include "payload.hpp"
/**
 * Adds the global variables in the memory chunk.
 *
 * Does not set the payloadHash.
 */
state::state(const symTable* globalSymTab, const fsm* stateMachine) 
	: globalSymTab(globalSymTab)
	, stateMachine (stateMachine)
	, never(nullptr)
	, nbProcesses(0)
	, lastStepPid(0)
	, payLoad(new payload(SYS_VARS_SIZE))
{

	for (const auto neverSym : globalSymTab->getSymbols<const neverSymNode*>()) {
		this->addNever(neverSym);
	}

	for (auto sym : globalSymTab->getSymbols<const varSymNode*>()) {
		addVariable(sym);
	}

	/**
	 * Runs every process with the attribute "active".
	 * Cardinalities are taken into account.
	 * Also, links the "never claim" FSM, if it exists, with the state.
	 */
	
	for (const auto procSym : globalSymTab->getSymbols<const procSymNode*>()) {
		
		assert(procSym->getActiveExpr());

		for(int i = 0; i < procSym->getActiveExpr()->getCstValue(); ++i){
			this->addProctype(procSym, i);
		}
	}

	payLoad->alloc();
	// No process is executing something atomic
	payLoad->setValue(OFFSET_EXCLUSIVE, NO_PROCESS);
	// No rendezvous has been requested.
	payLoad->setValue(OFFSET_HANDSHAKE, NO_HANDSHAKE);

	never->init();

	for (auto var : varList)
		var->init();

	for (auto proc : procs)
		proc->init();
		
	/*for(auto e : symPtr){
		std::cout << "symbol " << std::string(*e.first) << " at : "<<e.second<<"\n";
	}*/
}

/*
 * STATE DUPLICATION
 * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * Duplicates a state.
 *
 * This function does NOT duplicate the boolean formula of the state.  This is because it is only
 * used in apply() and there the copy of the boolean formula is of no use.
 */
state::state(const state& s) 
	: nbProcesses(s.nbProcesses)
	, payLoad(new payload(*s.payLoad))
{
	this->lastStepPid = s.lastStepPid;
	//this->features = nullptr; // see function description
	this->never = new process(*s.never);
	
	for(const auto& var : s.varList)
		addVar(var->deepCopy());

	// Copying processes information
	for(const auto& proc : s.procs) {
		procs.push_back(proc->deepCopy());
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

	for(auto proc : procs)
		delete proc;

	if(this->never) 
		delete this->never; 

	for(auto var: varList)
		delete var;

	if(payLoad) 
		delete(payLoad);
}

static byte _timeout = 0;
static byte _else = 0;

int state::eval(const process* proc, const astNode* node, byte flag) const {

	assert(node);
	if(!node)	
		return 0;

	byte foundFeature = 0;
	unsigned int offset, chanOffset;
	int returnValue = -1;
	chanSymNode* channel;
	symbol* sym;
	unsigned int handshake = payLoad->getValue<unsigned int>(OFFSET_HANDSHAKE);

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
				returnValue = eval(proc, *node->getChildren().cbegin(), flag);
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
					returnValue = eval(proc, *node->getChildren().cbegin(), flag);
				break;

			case(astNode::E_STMNT_ELSE):
				returnValue = (_else == 1);
				break;
			
			case(astNode::E_EXPR_PLUS):
				returnValue = eval(proc, binaryExpr->getLeftExpr(), flag) + eval(proc, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_MINUS):
				returnValue = eval(proc, binaryExpr->getLeftExpr(), flag) - eval(proc, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_TIMES):
				returnValue = eval(proc, binaryExpr->getLeftExpr(), flag) * eval(proc, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_DIV):
				returnValue = eval(proc, binaryExpr->getLeftExpr(), flag) / eval(proc, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_MOD):
				returnValue = eval(proc, binaryExpr->getLeftExpr(), flag) % eval(proc, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_GT):
				returnValue = (eval(proc, binaryExpr->getLeftExpr(), flag) > eval(proc, binaryExpr->getRightExpr(), flag));
				break;

			case(astNode::E_EXPR_LT):
				returnValue = (eval(proc, binaryExpr->getLeftExpr(), flag) < eval(proc, binaryExpr->getRightExpr(), flag));
				break;

			case(astNode::E_EXPR_GE):
				returnValue = (eval(proc, binaryExpr->getLeftExpr(), flag) >= eval(proc, binaryExpr->getRightExpr(), flag));
				break;

			case(astNode::E_EXPR_LE):
				returnValue = (eval(proc, binaryExpr->getLeftExpr(), flag) <= eval(proc, binaryExpr->getRightExpr(), flag));
				break;

			case(astNode::E_EXPR_EQ):
				returnValue = (eval(proc, binaryExpr->getLeftExpr(), flag) == eval(proc, binaryExpr->getRightExpr(), flag));
				break;

			case(astNode::E_EXPR_NE):
				returnValue = (eval(proc, binaryExpr->getLeftExpr(), flag) != eval(proc, binaryExpr->getRightExpr(), flag));
				break;

			case(astNode::E_EXPR_AND):
				returnValue = 0;
				if(eval(proc, binaryExpr->getLeftExpr(), flag)) 
					returnValue = eval(proc, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_OR):
				returnValue = eval(proc, binaryExpr->getLeftExpr(), flag);
				if(returnValue == 0) returnValue = eval(proc, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_UMIN):
				returnValue = - eval(proc, unaryExpr->getExpr(), flag);
				break;

			case(astNode::E_EXPR_NEG):
				returnValue = !eval(proc, unaryExpr->getExpr(), flag);
				break;

			case(astNode::E_EXPR_LSHIFT):
				returnValue = eval(proc, binaryExpr->getLeftExpr(), flag) << eval(proc, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_RSHIFT):
				returnValue = eval(proc, binaryExpr->getLeftExpr(), flag) >> eval(proc, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_BITWAND):
				returnValue = eval(proc, binaryExpr->getLeftExpr(), flag) & eval(proc, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_BITWOR):
				returnValue = eval(proc, binaryExpr->getLeftExpr(), flag) | eval(proc, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_BITWXOR):
				returnValue = eval(proc, binaryExpr->getLeftExpr(), flag) ^ eval(proc, binaryExpr->getRightExpr(), flag);
				break;

			case(astNode::E_EXPR_BITWNEG):
				returnValue = ~eval(proc, unaryExpr->getExpr(), flag);
				break;

			case(astNode::E_EXPR_COND):
			{
				auto cond = dynamic_cast<const exprCond*>(node);
				if(eval(proc, cond->getCond(), EVAL_EXPRESSION) > 0)
					returnValue = eval(proc, cond->getThen(), flag);
				else
					returnValue = eval(proc, cond->getElse(), flag);
				break;
			}

			case(astNode::E_EXPR_LEN):
			{
				auto varRef = dynamic_cast<const exprUnary*>(node)->getExpr();
				auto var = proc->getVar(varRef);
				if(!var) {
					var = getVar(varRef, proc);
				}
				assert(var);
				auto chanVar = dynamic_cast<channel*>(var);
				assert(chanVar);
				returnValue = chanVar->len();
				break;
			}

			case(astNode::E_EXPR_CONST):
				returnValue = dynamic_cast<const exprConst*>(node)->getCstValue();
				break;

			case(astNode::E_EXPR_TIMEOUT):
				returnValue = _timeout;
				break;

			case(astNode::E_EXPR_FULL):
			case(astNode::E_EXPR_NFULL):
			{
				auto varRef = dynamic_cast<const exprUnary*>(node)->getExpr();
				auto var = proc->getVar(varRef);
				if(!var) {
					var = getVar(varRef, proc);
				}
				assert(var);
				auto chanVar = dynamic_cast<channel*>(var);
				assert(chanVar);
				returnValue = node->getType() == astNode::E_EXPR_FULL? chanVar->isFull() : !chanVar->isFull();
				break;
			}

			case(astNode::E_EXPR_EMPTY):
			case(astNode::E_EXPR_NEMPTY):
			{
				auto varRef = dynamic_cast<const exprUnary*>(node)->getExpr();
				auto var = proc->getVar(varRef);
				if(!var) {
					var = getVar(varRef, proc);
				}
				assert(var);
				auto chanVar = dynamic_cast<channel*>(var);
				assert(chanVar);
				returnValue = node->getType() == astNode::E_EXPR_EMPTY? chanVar->isEmpty() : !chanVar->isEmpty();
				break;
			}

			case(astNode::E_VARREF):
			case(astNode::E_VARREF_NAME):
			{
				auto varRef = dynamic_cast<const exprVarRef*>(node);
				auto var = proc->getVar(varRef);
				if(!var) {
					var = getVar(varRef, proc);
				}
				assert(var);
				returnValue = var->getValue();
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

/**
 * state is necessary to evaluate the index of an array expression.
 * Give the offset of the variable referenced by a E_VARREF expression.
 * On first call, preOffset must have the same value as the offset of its environment (i.e. global or process).
 * /!\ process is the environment in which the variable is ANALYZED, NOT in the one the variable is DEFINED.
 */

/*
unsigned int state::getVarOffset(const process* varProc, const expr* varExpr) const {
	
	assert(varExpr->getType() == astNode::E_RARG_VAR || varExpr->getType() == astNode::E_EXPR_VAR
	|| varExpr->getType() == astNode::E_VARREF || varExpr->getType() == astNode::E_VARREF_NAME);

	if(varExpr->getType() == astNode::E_RARG_VAR) {
		auto var = dynamic_cast<const exprRArgVar*>(varExpr);
		assert(var);
		return this->getVarOffset(varProc, var->getVarRef());

	} else if(varExpr->getType() == astNode::astNode::E_EXPR_VAR) {
		auto var = dynamic_cast<const exprVar*>(varExpr);
		assert(var);
		return this->getVarOffset(varProc, var->getVarRef());
	
	} else if(varExpr->getType() == astNode::E_VARREF) {
		auto var = dynamic_cast<const exprVarRef*>(varExpr);
		assert(var);
		unsigned int highOffset = this->getVarOffset(varProc, var->getField());
		if(!var->getSubField())
			return highOffset;
		else
			return this->getVarOffset(varProc, var->getSubField());

	} else if (varExpr->getType() == astNode::E_VARREF_NAME) {
		auto varRefName = dynamic_cast<const exprVarRefName*>(varExpr);
		auto sym = varRefName->getSymbol();
		int index = 0;
		
		if(varRefName->getIndex())
			index = this->eval(varProc, varRefName->getIndex(), EVAL_EXPRESSION);
		
		return varOffset.at(std::make_tuple<>(varProc, sym, index));
	
	} else assert(false);
	
	return 0; // only to please compiler
}*/

std::string state::getVarName(const expr* varExpr, const process* proc) const {
	
	assert(varExpr->getType() == astNode::E_RARG_VAR || varExpr->getType() == astNode::E_EXPR_VAR
	|| varExpr->getType() == astNode::E_VARREF || varExpr->getType() == astNode::E_VARREF_NAME);

	std::string varName;

	if(varExpr->getType() == astNode::E_RARG_VAR) {
		auto var = dynamic_cast<const exprRArgVar*>(varExpr);
		assert(var);
		return this->getVarName(var->getVarRef(), proc);

	} else if(varExpr->getType() == astNode::astNode::E_EXPR_VAR) {
		auto var = dynamic_cast<const exprVar*>(varExpr);
		assert(var);
		return this->getVarName(var->getVarRef(), proc);
	
	} else if(varExpr->getType() == astNode::E_VARREF) {
		auto var = dynamic_cast<const exprVarRef*>(varExpr);
		assert(var);
		varName = this->getVarName(var->getField(), proc);
		return !var->getSubField()? varName : varName + "." + this->getVarName(var->getSubField(), proc);

	} else if (varExpr->getType() == astNode::E_VARREF_NAME) {
		auto varRefName = dynamic_cast<const exprVarRefName*>(varExpr);
		varName = varRefName->getName();
		int index = varRefName->getIndex() ? this->eval(proc, varRefName->getIndex(), EVAL_EXPRESSION) : 0;
		return index? varName : varName+"["+std::to_string(index)+"]";
	
	} else assert(false);
	
	return varName; // only to please compiler
}

variable* state::getVar(const expr* varExpr, const process* proc) const {
	return varMap.at(getVarName(varExpr, proc));
}

/**
 * Returns the stateMask of a given pid.
 */
process* state::getProc(int pid) const {
	for(auto proc : procs)
		if(proc->getPid() == pid)
			return proc;
	return nullptr;
}

/**
 * Gets the symbol table of a channel by giving its offset in the memory chunk.
 * The structure contained in this->chanRefs is used to get the table.
 * If no channel exists at the given offset, returns nullptr.
 */
/*const chanSymNode* state::getChannelSymTab(unsigned int chanOffset) const {
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
}*/

/*
 * ACCESS AND MODIFICATION OF LARGE STATE CHUNKS
 * * * * * * * * * * * * * * * * * * * * * * * */

// TODO: differences between the three following functions?

/**
 * Helper for killProctype and and initVariables
 */

/*
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
*/

/**
 * Helper for stateCreateInitial and addProctype
 *
 * Initialises all variables in a state.  The proc is used to get the symbol table.
 *
 * Does not change the payloadHash.
 */



/**
 * Helper for killProctype
 *
 * Removes the channels references whose offset is between infBound and supBound (both included).
 */
/*void state::removeChannelRefs(unsigned int infBound, unsigned int supBound) {
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
}*/

void state::addVar(variable* var) {
	varMap[var->getName()] = var;
	varList.push_back(var);
}

variable* state::addVariable(const varSymNode* varSym){
	assert(varSym);

	if(varSym->getType() == symbol::T_CHAN)
		return addChannel(dynamic_cast<const chanSymNode*>(varSym));

	for(int i = 0; i < varSym->getBound(); ++i){
		addVar(new variable(payLoad, payLoad->getSize(), varSym, i));
		payLoad->addSize(varSym->getSizeOf());
	}
}

variable* state::addChannel(const chanSymNode* chanSym){
	assert(chanSym);
	
	for(int i = 0; i < chanSym->getBound(); ++i){

		auto chanVar = new channel(payLoad, payLoad->getSize(), chanSym, i);
		addVar(chanVar);
		payLoad->addSize(chanVar->getSizeOf());
	}

	return nullptr;
}

/**
 * Reserves some memory for the proctype variables in the memory chunk.
 * Returns the pid of the newly created process.
 *
 * Does not change the payloadHash.
 */
int state::addProctype(const procSymNode* procType, int i){
	
	process* newProc = new process(this, payLoad->getSize(), procType, stateMachine->getFsmWithName(procType->getName()), pid++, i);

	payLoad->addSize(newProc->getSizeOf());

	this->nbProcesses++;

	return newProc->pid;
}

/**
 * Defines the never claim of the execution.
 *
 * Does not change the payloadHash.
 */
void state::addNever(const neverSymNode* neverSym) {
	
	this->never = new process(this, payLoad->getSize(), neverSym, stateMachine->getFsmWithName(neverSym->getName()), -2);

	this->nbNeverClaim++;
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
	
	process* proc = nullptr;

	for(auto _ : procs) {
		if(_->getPid() == pid) {
			proc = _;
			break;
		}
	}

	procs.remove(proc);
	//TODO : modify payload...
	assert(false);
	nbProcesses--;
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
byte state::compare(const state& s2) const {

	if(!(*payLoad == *s2.payLoad))	
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
	assert(false);
	/*while(this->last->pid >= 0 && !getNodePointer(this->last))
		this->killProctype(this->last->pid);*/
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



*/

void state::printState(void) const {
	
	for(auto var : varList)
		var->print();

	if(this->never)
		never->print();
	
	for(auto proc : procs)
		proc->print();
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