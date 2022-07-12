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
#include "channel.hpp"
#include "payload.hpp"
#include "transition.hpp"
/**
 * Adds the global variables in the memory chunk.
 *
 * Does not set the payloadHash.
 */
state::state(const fsm* stateMachine) 
	: globalSymTab(stateMachine->getGlobalSymTab())
	, stateMachine (stateMachine)
	, never(nullptr)
	, pidCounter(0)
	, nbProcesses(0)
	, lastStepPid(0)
	, global(nullptr)
	, handShakeChan(nullptr)
	, handShakeProc(nullptr)
	, exclusiveProc(nullptr)
	, timeout(false)
	, prob(1.0)
{

	global = new scope("global");
	global->addRawBytes(SIZE_EXCLUSIVITY_VAR);
	global->addRawBytes(SIZE_HANDSHAKE_VAR);

	for (const auto neverSym : globalSymTab->getSymbols<const neverSymNode*>()) {
		addNever(neverSym);
	}

	for (auto sym : globalSymTab->getSymbols<const varSymNode*>()) {
		global->addVariables(sym);
	}

	/**
	 * Runs every process with the attribute "active".
	 * Cardinalities are taken into account.
	 * Also, links the "never claim" FSM, if it exists, with the state.
	 */
	
	for (const auto procSym : globalSymTab->getSymbols<const procSymNode*>()) {
		
		assert(procSym->getActiveExpr());

		for(int i = 0; i < procSym->getActiveExpr()->getCstValue(); ++i){
			addProctype(procSym, i);
		}
	}

	global->init();

	// No process is executing something atomic
	global->getPayload()->setValue(OFFSET_EXCLUSIVITY_VAR, NO_PROCESS);
	// No rendezvous has been requested.
	global->getPayload()->setValue(OFFSET_HANDSHAKE_VAR, NO_HANDSHAKE);

	/*for(auto e : symPtr){
		std::cout << "symbol " << std::string(*e.first) << " at : "<<e.second<<"\n";
	}*/
}

unsigned long state::hash(void) const {
	return global->getPayload()->hash();
}

void state::setPayload(payload* payLoad) {
	global->setPayload(payLoad);
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
/*
state::state(const state& s) 
	: nbProcesses(s.nbProcesses)
	, payLoad(new payload(*s.payLoad))
{
	this->lastStepPid = s.lastStepPid;
	//this->features = nullptr; // see function description
	this->never = s.never->deepCopy();
	
	for(const auto& var : s.varList)
		addVar(var->deepCopy());

	// Copying processes information
	for(const auto& proc : s.procs) {
		procs.push_back(proc->deepCopy());
	}
}
*/
/*
state* state::deepCopy(void) const {
	state* copy = new state(globalSymTab, stateMachine);

	copy->pidCounter = pidCounter;
	copy->nbProcesses = nbProcesses;
	copy->nbNeverClaim = nbNeverClaim;
	copy->lastStepPid = lastStepPid;
	copy->payLoad = new payload(*payLoad);

	for(auto proc : procs) {
		auto procCopy = proc->deepCopy();
		procCopy->setState(copy);
		procCopy->setPayload(copy->payLoad);
		copy->procs.push_back(procCopy);
	}

	auto neverCopy = never->deepCopy();
	neverCopy->setState(copy);
	neverCopy->setPayload(copy->payLoad);
	copy->never = neverCopy;
	
	for(auto var : varList) {
		auto varCopy = var->deepCopy();
		varCopy->setPayload(copy->payLoad);
		copy->addVar(varCopy);
	}
}
*/

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
	delete global;
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
/*
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
	
	return STATES_SAME_S1_FRESH;
}*/

void state::print(void) const {
	
	global->print();
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
 * Reserves some memory for the proctype variables in the memory chunk.
 * Returns the pid of the newly created process.
 *
 * Does not change the payloadHash.
 */
process* state::addProctype(const procSymNode* procType, int i){
	
	if(nbProcesses > MAX_PROCESS) {
		printf("Cannot instantiate more than %d processes.", MAX_PROCESS);
		assert(false);
	}

	process* newProc = new process(this, procType, stateMachine->getFsmWithName(procType->getName()), pidCounter++, i);
	procs.push_back(newProc);

	nbProcesses++;
	return newProc;
}

process* state::addProctype(const procSymNode* procType, const std::list<const variable*>& args){
	
	process* newProc = new process(this, procType, stateMachine->getFsmWithName(procType->getName()), pidCounter++, args);
	procs.push_back(newProc);

	nbProcesses++;
	return newProc;
}

/**
 * Defines the never claim of the execution.
 *
 * Does not change the payloadHash.
 */
process* state::addNever(const neverSymNode* neverSym) {
	
	never = new process(this, neverSym, stateMachine->getFsmWithName(neverSym->getName()), -2);

	nbNeverClaim++;

	return never;
}

size_t state::_getSizeOf(void) const {
	return 0;
}

size_t state::getSizeOf(void) const {
	return global->getSizeOf();
}

/*******************************************************************************************************/

const process* state::getExclusiveProc(void) const {
	return exclusiveProc;
}

byte state::getExclusiveProcId(void) const {
	return getExclusiveProc()? getExclusiveProc()->getPid() : NO_PROCESS;
}

bool state::hasExclusivity(void) const {
	return getExclusiveProc() != nullptr;
}

void state::resetExclusivity(void) const {
	setExclusivity(NO_PROCESS);
}

void state::setExclusivity(const process* proc) const {
	exclusiveProc = proc;
	global->getPayload()->setValue<byte>(OFFSET_EXCLUSIVITY_VAR, (proc? proc->getPid() : NO_PROCESS));
}

void state::setExclusivity(byte pid) const {
	setExclusivity(getProc(pid));
}

bool state::requestHandShake(const std::pair<const channel*, const process*>& handShake) const {
	if(!hasHandShakeRequest()) {
		setHandShake(handShake);
		return true;
	} return false; 
}

void state::setHandShake(const std::pair<const channel*, const process*>& handShake) const {
	handShakeChan = handShake.first;
	handShakeProc = handShake.second;
	global->getPayload()->setValue<int>(OFFSET_HANDSHAKE_VAR, (handShakeChan? handShakeChan->getVariableId() : NO_HANDSHAKE));
}

/*void state::setHandShake(unsigned int cid) const {

}*/

std::pair<const channel*, const process*> state::getHandShakeRequest(void) const {
	return {handShakeChan, handShakeProc};
}

unsigned int state::getHandShakeRequestId(void) const {
	return hasHandShakeRequest()? getHandShakeRequest().first->getVariableId() : NO_HANDSHAKE;
}

const channel* state::getHandShakeRequestChan(void) const {
	return getHandShakeRequest().first;
}

const process* state::getHandShakeRequestProc(void) const {
	return getHandShakeRequest().second;
}

bool state::hasHandShakeRequest(void) const {
	return handShakeChan != nullptr;
}

void state::resetHandShake(void) const {
	handShakeChan = nullptr;
	global->getPayload()->setValue<int>(OFFSET_HANDSHAKE_VAR, NO_HANDSHAKE);
}

bool state::getTimeoutStatus(void) const {
	return timeout;
}

/**
 * Returns a list of all the executable transitions (for all the processes).
 * EFFECTS: None. (It CANNOT have any!)
 * WARNING:
 * 	In the end, does NOT (and must NEVER) modify the state payload.
 */
std::list<transition*> state::executables(void) const {

	const process* exclusivity = getExclusiveProc();
	auto handShake = getHandShakeRequest();

	std::list<transition*> execs;

	for(auto proc : procs)
		if (hasHandShakeRequest() || !hasExclusivity() || getExclusiveProcId() == proc->getPid())
			execs.merge(proc->executables());

	
	if (execs.size() == 0) {
		if(hasExclusivity()) {
			resetExclusivity();
			return executables();

		} else if (timeout == false) {
			timeout = true;
			return executables();
		}
		return execs;
	}

	setExclusivity(exclusivity);
	setHandShake(handShake);
	timeout = false;

	return execs;
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
state* state::apply(const transition* trans) {
	process* proc = trans->getProc();
	assert(proc);

	proc->apply(trans);

	assert(!getProc(lastStepPid)->isAtomic() || getExclusiveProcId() == lastStepPid);

	return this;
}