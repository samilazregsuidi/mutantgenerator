#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <cmath>
#include <cassert>
#include <vector>

#include "compositeState.hpp"
#include "compositeTransition.hpp"
/**
 * Adds the global variables in the memory chunk.
 *
 * Does not set the payloadHash.
 */
compState::compState() 
	: prob(1.0)
	, trans(nullptr)
{}

unsigned long compState::hash(void) const {
	unsigned long* compHashPtr = new unsigned long[subStates.size()];
	int i = 0;
	for(auto elem : subStates)
		compHashPtr[i++] = elem.second->hash();
	
	unsigned long res = std::hash<std::string_view>{}(std::string_view(reinterpret_cast<byte*>(compHashPtr), subStates.size() * sizeof(unsigned long)));
	delete[] compHashPtr;
	return res;
}

compState* compState::deepCopy(void) const {
	compState* copy = new compState(*this);
	copy->subStates.clear();
	for(auto elem : subStates)
		copy->subStates[elem.first] = elem.second->deepCopy();
	return copy;
}

compState::~compState() {
	for(auto elem : subStates)
		delete elem.second;
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

/*byte compState::compare(const state& s2) const {
	auto compS2 = dynamic_cast<const compState&>(s2);
	for(auto [n1, s1] : subStates) {
		auto subStateS2 = compS2.getState(n1);
		if(subStateS2 == nullptr || subStateS2->hash() != s1->hash())
			return STATES_DIFF;
	}
	return STATES_SAME_S1_FRESH;
}*/

void compState::print(void) const {
	for(auto elem : subStates)
		elem.second->print();
	printf("prob : %lf\n", prob);
}

void compState::printTexada(void) const {
	for(auto elem : subStates)
		elem.second->printTexada();
	printf("..\n");
}

void compState::printGraphViz(unsigned long i) const {
	for(auto elem : subStates)
		elem.second->printGraphViz(i);
}

/**
 * Returns a list of all the executable transitions (for all the processes).
 * EFFECTS: None. (It CANNOT have any!)
 * WARNING:
 * 	In the end, does NOT (and must NEVER) modify the state payload.
 */
std::list<transition*> compState::executables(void) const {

	std::list<transition*> execs;

	std::vector<std::vector<transition*>> stateTransList;
	for(auto [name, s] : subStates) {
		auto Ts = s->executables();
		stateTransList.push_back(std::vector<transition*>{ std::begin(Ts), std::end(Ts) });
	}

	for(size_t i = 0; i < stateTransList.size(); ++i) {
		for(size_t j = 0; j < stateTransList[i].size(); ++j) {
			stateTransList[i][j];
		}
	}

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
state* compState::apply(const transition* trans) {
	
	auto compTrans = dynamic_cast<const compTransition*>(trans);

	for(auto trans : compTrans->Ts) {
		auto s = getState(trans->src->getName());
		assert(s);
		s->apply(trans);
	}

	this->prob *= trans->prob;

	this->trans = trans;

	return this;
}

bool compState::nullstate(void) const {
	for(auto elem : subStates)
		if(!elem.second->nullstate())
			return false;
	return true;
}

bool compState::endstate(void) const {
	for(auto elem : subStates)
		if(!elem.second->endstate())
			return false;
	return true;
}

bool compState::isAccepting(void) const {
	for(auto elem : subStates)
		if(elem.second->isAccepting())
			return true;
	return false;
}

state* compState::getState(const std::string& name) const {
	auto it = subStates.find(name);
	return it == subStates.end()? nullptr : it->second;
}

void compState::printHexadecimal(void) const {
	assert(false);
}