#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <cmath>

#include "programState.hpp"

#include "process.hpp"

#include "ast.hpp"
#include "automata.hpp"

#include "variable.hpp"
#include "channel.hpp"
#include "payload.hpp"

#include "programTransition.hpp"
#include "rendezVousTransition.hpp"

/**
 * Adds the global variables in the memory chunk.
 *
 * Does not set the payloadHash.
 */

progState::progState(const fsm* stateMachine) 
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
	, trans(nullptr)
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

unsigned long progState::hash(void) const {
	return global->hash();
}

void progState::setPayload(payload* payLoad) {
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

progState* progState::deepCopy(void) const {
	progState* copy = new progState(*this);
	auto newScope = global->deepCopy();
	newScope->setPayload(global->getPayload()->copy());
	copy->assign(newScope);
	return copy;
}

void progState::assign(scope* sc) {
	procs.clear();
	global = sc;

	for(auto proc : sc->getProcesses()) {
		proc->setProgState(this);
		procs.push_back(proc);
	}

	if(never) {
		never = dynamic_cast<process*>(global->getSubScope(never->getName()));
		assert(never);
		never->setProgState(this);
	}

	if(handShakeChan) {
		handShakeChan = global->getChannel(handShakeChan->getName());
		assert(handShakeChan);
	}
	if(handShakeProc) {
		handShakeProc = global->getProcess(handShakeProc->getName());
		assert(handShakeProc);
	}
	if(exclusiveProc) {
		exclusiveProc = global->getProcess(exclusiveProc->getName());
		assert(exclusiveProc);
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

progState::~progState() {
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

byte progState::compare(const state& s2) const {

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

void progState::print(void) const {
	global->print();
	printf("prob : %lf\n", prob);
}

void progState::printTexada(void) const {
	global->printTexada();
}

void progState::printGraphViz(unsigned long i) const {
	std::ofstream stateFile;
	//stateFile.open("trace/" + std::to_string(hash()));
	stateFile.open("trace/" + std::to_string(i) + ".dot");
	
	std::list<const fsmNode*> locs;
	for(auto p : procs)
		locs.push_back(p->getFsmNodePointer());
	
	std::list<const fsmEdge*> edges;
	if(auto progTrans = dynamic_cast<const progTransition*>(trans)) {
		edges.push_back(progTrans->getEdge());
		auto t = progTrans;
		const RVTransition* rvTrans = dynamic_cast<const RVTransition*>(t);
		while (rvTrans && (t = rvTrans->getResponse())){
			edges.push_back(t->getEdge());
			rvTrans = dynamic_cast<const RVTransition*>(t);
		}
	}

	stateMachine->printGraphVisWithLocations(stateFile, locs, edges);
	stateFile.close();
}

/**
 * Returns the stateMask of a given pid.
 */
process* progState::getProc(int pid) const {
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
process* progState::addProctype(const procSymNode* procType, int i){
	
	if(nbProcesses > MAX_PROCESS) {
		printf("Cannot instantiate more than %d processes.", MAX_PROCESS);
		assert(false);
	}

	process* newProc = new process(this, procType, stateMachine->getFsmWithName(procType->getName()), pidCounter++, i);
	procs.push_back(newProc);

	nbProcesses++;
	return newProc;
}

process* progState::addProctype(const procSymNode* procType, const std::list<const variable*>& args){
	
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
process* progState::addNever(const neverSymNode* neverSym) {
	
	never = new process(this, neverSym, stateMachine->getFsmWithName(neverSym->getName()), -2);

	nbNeverClaim++;

	return never;
}

size_t progState::_getSizeOf(void) const {
	return 0;
}

size_t progState::getSizeOf(void) const {
	return global->getSizeOf();
}

/*******************************************************************************************************/

const process* progState::getExclusiveProc(void) const {
	return exclusiveProc;
}

byte progState::getExclusiveProcId(void) const {
	return getExclusiveProc()? getExclusiveProc()->getPid() : NO_PROCESS;
}

bool progState::hasExclusivity(void) const {
	return getExclusiveProc() != nullptr;
}

void progState::resetExclusivity(void) const {
	setExclusivity(NO_PROCESS);
}

void progState::setExclusivity(const process* proc) const {
	exclusiveProc = proc;
	global->getPayload()->setValue<byte>(OFFSET_EXCLUSIVITY_VAR, (proc? proc->getPid() : NO_PROCESS));
}

void progState::setExclusivity(byte pid) const {
	setExclusivity(getProc(pid));
}

bool progState::requestHandShake(const std::pair<const channel*, const process*>& handShake) const {
	if(!hasHandShakeRequest()) {
		setHandShake(handShake);
		return true;
	} return false; 
}

void progState::setHandShake(const std::pair<const channel*, const process*>& handShake) const {
	handShakeChan = handShake.first;
	handShakeProc = handShake.second;
	global->getPayload()->setValue<int>(OFFSET_HANDSHAKE_VAR, (handShakeChan? handShakeChan->getVariableId() : NO_HANDSHAKE));
}

/*void progState::setHandShake(unsigned int cid) const {

}*/

std::pair<const channel*, const process*> progState::getHandShakeRequest(void) const {
	return {handShakeChan, handShakeProc};
}

unsigned int progState::getHandShakeRequestId(void) const {
	return hasHandShakeRequest()? getHandShakeRequest().first->getVariableId() : NO_HANDSHAKE;
}

const channel* progState::getHandShakeRequestChan(void) const {
	return getHandShakeRequest().first;
}

const process* progState::getHandShakeRequestProc(void) const {
	return getHandShakeRequest().second;
}

bool progState::hasHandShakeRequest(void) const {
	return handShakeChan != nullptr;
}

void progState::resetHandShake(void) const {
	handShakeChan = nullptr;
	global->getPayload()->setValue<int>(OFFSET_HANDSHAKE_VAR, NO_HANDSHAKE);
}

bool progState::getTimeoutStatus(void) const {
	return timeout;
}

/**
 * Returns a list of all the executable transitions (for all the processes).
 * EFFECTS: None. (It CANNOT have any!)
 * WARNING:
 * 	In the end, does NOT (and must NEVER) modify the state payload.
 */
std::list<transition*> progState::executables(void) const {

	std::list<transition*> execs;

	const process* exclusivity = getExclusiveProc();
	auto handShake = getHandShakeRequest();

	for(auto proc : procs) {
		if (hasHandShakeRequest() || !hasExclusivity() || getExclusiveProcId() == proc->getPid()) {
			auto Ts = proc->executables();

			//assert(std::fabs([=](){ double resProb = 0.0; for(auto t : Ts) resProb += t->prob; return resProb; }() - (Ts.size() ? 1.0 : 0.0)) < std::numeric_limits<double>::epsilon());

			for(auto t : Ts)
				t->prob /= procs.size();
			
			
			
			execs.merge(Ts);
		}
	}

	//assert(std::fabs([=](){ double resProb = 0.0; for(auto t : execs) resProb += t->prob; return resProb; }() - (execs.size() ? 1.0 : 0.0)) < std::numeric_limits<double>::epsilon());
	
	if (execs.size() == 0) {

		if(hasExclusivity()) {
			resetExclusivity();
			execs = executables();	

		} else if (timeout == false) {
			timeout = true;
			execs = executables();
			timeout = false;
		}
	}

	setExclusivity(exclusivity);
	setHandShake(handShake);

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
state* progState::apply(const transition* trans) {
	process* proc = dynamic_cast<const progTransition*>(trans)->getProc();
	assert(proc);
	//warning if "different" procs have the same pid i.e., dynamic proc creation
	proc = getProc(proc->getPid());

	proc->apply(trans);

	assert(!getProc(lastStepPid)->isAtomic() || getExclusiveProcId() == lastStepPid);

	this->prob *= trans->prob;

	this->trans = trans;

	return this;
}

/*const ADD& progState::getFeatures(void) const {
	return features;
}*/

bool progState::nullstate(void) const {
	for(auto p : procs)
		if(!p->nullstate())
			return false;
	return true;
}

bool progState::endstate(void) const {
	for(auto p : procs)
		if(!p->endstate())
			return false;
	return true;
}

bool progState::isAccepting(void) const {
	return never->isAccepting();
}

bool progState::isAtomic(void) const {
	for(auto p : procs)
		if(p->isAtomic())
			return true;
	return false;
}

void progState::printHexadecimal(void) const {
	global->printHexadecimal();
}