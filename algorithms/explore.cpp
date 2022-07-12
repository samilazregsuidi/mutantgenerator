#include "explore.hpp"

#include <stdio.h>

#include "state.hpp"
#include "transition.hpp"
#include "process.hpp"

static 		unsigned int _nbErrors = 0;				// Total number of encountered problems
static long unsigned int _nbStatesExplored = 1;		// Total of distinct states (without features) explored
static long unsigned int _nbStatesReExplored = 0;	// Total of states that had to be re-explored because new products were found to be able to reach them
static long unsigned int _nbStatesStops = 0;		// Total of states where exploration backtracked because they were already visited before
static long unsigned int _nbStatesExploredInner = 0;// As before, but for inner search.
static long unsigned int _nbStatesReExploredInner = 0;//As before, but for inner search.
static long unsigned int _nbStatesStopsInner = 0;	// As before, but for inner search.
static long unsigned int _depth = 0;				// Current exploration depth (inner and outer)

void launchExecution(const fsm* automata) {
	state* current = new state(automata);
	while(transition* trans = transition::sample(current->executables())){
		current->apply(trans);
		printf("--------------------------------------\n");
		current->print();
		//add error status
	}
}

void countStates(const fsm* automata) {
	state* current = new state(automata);

}

void startNestedDFS(const fsm* automata) {
    _nbStatesExplored = 0;
	_nbStatesReExplored = 0;
	printf("[startNestedDFS]\n");
	// Create initial state
	state* init = new state(automata);

	
    //htVisitedStatesInsert(init->payloadHash, init, DFS_OUTER);
	//htOuterStatesInsert(init->payloadHash, init);

	// Sanity checks
    auto neverClaim = init->getNeverClaim();
	if(!neverClaim || !neverClaim->nullstate() || neverClaim->transitions().size() == 0) {
        assert(false);
        printf("init->never is NULL\n");
    }

    std::stack<state*> stack;
    stack.push(init);

	if(outerDFS(stack) == 0) 
        printf("Property satisfied");
}

byte outerDFS(std::stack<state*>& stackOuter) {

	byte error = 0;
    byte exhaustive = 1;
	byte temp; // TODO remove

	// Execution continues as long as the
	//  - stack is not empty
	//  - no error was found (except in the exhaustive case)
	while(!stackOuter.empty() && (!error || exhaustive)) {

		auto current = stackOuter.top();
		auto neverClaim = current->getNeverClaim();

		if(0 < _nbErrors /*&& temp*/) {
			//DEBUG_PRINT("    +-> is known to violate, backtrack.\n");
			stackOuter.pop();
			//htOuterStatesRemove(current->state->payloadHash, current->state->payload, current->state->payloadSize);
			//destroyStackElement(current, processTrans);
			_depth--;
		// If the node of the never claim is NULL, then it had a loose end which was taken in the
		// previous transition.  This means that we are in a final state, which is assumed to be
		// accepting; hence:
		} else if(neverClaim->endstate()) {
			// Safety property violated.
			// We have to pop two states off the stack to get to the violating state:
			//  -> the current top is a skip transition fired from an accepting state
			//  -> the state below that is the accepting state
			//  -> the state below that is the state that actually led to the accepting state to be reachable.
			//     i.e. this state is the actual violating state.
			stackOuter.pop();
			
            auto newTop = stackOuter.top();
            stackOuter.pop();

			//STOP_ERROR("Safety property violated", ((ptStackElt) top(stackOuter))->state->features, stackOuter, NULL, NULL);
			error = 1;
			//htOuterStatesRemove(current->state->payloadHash, current->state->payload, current->state->payloadSize);

			newTop = stackOuter.top();
            stackOuter.pop();
			_depth = _depth - 3;

		// Otherwise, the state can be explored (or exploration continue)
		} else {
			//DEBUG_PRINT("    +-> exploring...\n");
			//current->setErrorStatus = _nbErrors;

			for(auto p : current->post()){
				if(p->hasDeadlock()) {
					printf("Found deadlock");
					p->addError();
				}
				stackOuter.push(p);
			}

			// If the element is uninitialised; the executable transitions have to be determined
			if(!current->E_save && !current->E_never_save) {
				DEBUG_PRINT("    +-> initialising...\n");
				if(E) {
					current->E = E;
					E = NULL;
				}
				else
					current->E = executables(globalSymTab, mtypes, current->state, 1, _nbErrors, &hasDeadlock, NULL, NULL, &noOutgoing, &resetExclusivity);
				current->E_save = current->E;
				current->E_never = executablesNever(globalSymTab, mtypes, current->state);
				current->E_never_save = current->E_never;
				// Check for deadlocks
				if(hasDeadlock) {
#ifndef CEGAR
					STOP_ERROR("Found deadlock", current->state->features, stackOuter, NULL, NULL);
#else
					STOP_ERROR("Found deadlock", current->state->features, stackOuter, NULL, NULL);
					ce = createCounterExample(stackOuter, NULL, current->state->features);
					ces = listAdd(ces, ce);
					_allProductsFail = !addConstraintToFD(negateBool(current->state->features));
#endif
					error = 1;
					current->E = NULL; // This will cause backtracking
				} else if(!current->E_never) current->E = NULL;
				if(fullDeadlockCheck && noOutgoing) {
					if(isSatisfiableWrtFD(noOutgoing)) {
#ifndef CEGAR
						STOP_ERROR("Found trivially invalid end state; the following set of products can reach the state, but has no outgoing transition.", noOutgoing, stackOuter, NULL, NULL);
#else
						STOP_ERROR("Found trivially invalid end state; the following set of products can reach the state, but has no outgoing transition.", noOutgoing, stackOuter, NULL, NULL);
						ce = createCounterExample(stackOuter, NULL, noOutgoing);
						ces = listAdd(ces, ce);
						_allProductsFail = !addConstraintToFD(negateBool(noOutgoing));
#endif
						error = 1;
					}
					destroyBool(noOutgoing);
					noOutgoing = NULL;
				}
			}
			// If we have explored all transitions of the state (!current->E_never; see "struct stackElt"
			// in stack.h), we check whether the state is accepting and start a backlink search if it is;
			// otherwise just backtrack
			if(!current->E) {
				DEBUG_PRINT("    +-> all transitions of state fired, acceptance check and backtracking...\n");
				// Back these values up, the inner search will free current->state before returning
				void* payloadBak = current->state->payload;
				unsigned int payloadHashBak = current->state->payloadHash;
				unsigned int payloadSizeBak = current->state->payloadSize;
				if((neverNode->flags & N_ACCEPT) == N_ACCEPT) {
					DEBUG_PRINT("    +-> found accepting, starting inner...\n");
					new = createStackElement(current->state, _nbErrors);
					ptStack stackInner = push(NULL, new);
#ifdef CEGAR
					new->accFeatures = copyBool(current->accFeatures);
#endif
					_depth++;
					_nbStatesExploredInner++;
#ifndef CEGAR
					error = innerDFS(globalSymTab, mtypes, stackOuter, stackInner) || error; // error needs to be to the right, for otherwise lazy evaluation might cause the innerDFS call to be skipped
#else
					ces = listConcat(ces, innerDFS(globalSymTab, mtypes, stackOuter, stackInner));
#endif
					current->state = NULL; // it will have been destroyed when the innerDFS backtracked for the last time
				}
				pop(&stackOuter);
				htOuterStatesRemove(payloadHashBak, payloadBak, payloadSizeBak);
				destroyStackElement(current, processTrans);
				_depth--;

			// ..., or there is a transition to be executed:
			} else if(current->E) {
#ifdef CEGAR
				ptBoolFct conjunction = addConjunction(current->accFeatures, ((ptProcessTransition) current->E->value)->trans->origFeatures, 1, 1);
				if(isSatisfiableWrtFD(conjunction)) {
#endif
				DEBUG_PRINT_d("    +-> firing transition TL%02d...", ((ptProcessTransition) current->E->value)->trans ? ((ptProcessTransition) current->E->value)->trans->lineNb : -1);
				s_ = apply(globalSymTab, mtypes, current->state, (ptProcessTransition) current->E->value, 1, &assertViolation);
				s_ = applyNever(globalSymTab, mtypes, s_, (ptFsmTrans) current->E_never->value);
				E = executables(globalSymTab, mtypes, s_, 1, _nbErrors, &hasDeadlock, NULL, NULL, &noOutgoing, &resetExclusivity);
				if(resetExclusivity) {
					stateSetValue(s_->payload, OFFSET_EXCLUSIVE, T_BYTE, NO_PROCESS);
					DEBUG_PRINT_d("         - lost exclusivity, state became %u\n", s_->payloadHash);
				}

				s_->payloadHash = hashState(s_);
				DEBUG_PRINT_d(" got %u\n", s_->payloadHash);
				if(assertViolation) {
					char msg[40];
					sprintf(msg, "Assertion at line %d violated", ((ptProcessTransition) current->E->value)->trans->lineNb);
					STOP_ERROR(msg, s_->features, stackOuter, NULL, NULL);
					error = 1;
					stateDestroy(s_, false);
					s_ = NULL;
					destroyProcTransList(E, processTrans);
					E = NULL;

				} else {
					prevS_ = NULL;
					if(htVisitedStatesFind(s_->payloadHash, s_, DFS_OUTER, &prevS_)) {
						DEBUG_PRINT("         - state already visited.\n");
						stateDestroy(s_, false);
						s_ = NULL;
						destroyProcTransList(E, processTrans);
						E = NULL;
						_nbStatesStops++;

					} else {
						if(prevS_) {
							DEBUG_PRINT("         - state visited but features fresh, pushing on stack.\n");
							// The state was visited already, but the current copy is "fresher".
							// No need to insert it into the hash table, just update the feature expression

							// Important: PrevS_ can only be a state that was fully explored with the features
							// it has now. This is because:
							//  - it has been visited already (otherwise, it wouldn't be in the hashtab)
							//  - it is not a state on the current stack (otherwise, it wouldn't be fresh)
							// This means, that all states that could be visited with prevS_->features have
							// been visited already.  So, when we continue, we use s_->features and not
							// s_->features || prevS_->features.
							ptBoolFct negPrev = negateBool(prevS_->outerFeatures);
							if(s_->features == NULL) {
								destroyBool(prevS_->outerFeatures);
								prevS_->outerFeatures = getTrue();
							} else {
								prevS_->outerFeatures = addDisjunction(prevS_->outerFeatures, s_->features, 0, 1);

								#ifdef CHECK_TAUTOLOGY
									if(prevS_->outerFeatures && isTautology(prevS_->outerFeatures)) {
										destroyBool(prevS_->outerFeatures);
										prevS_->outerFeatures = getTrue();
									}
								#endif
							}
							s_->features = addConjunction(negPrev, s_->features, 0, 0);
							free(s_->payload);
							s_->payload = prevS_->payload;

							// The state is not a new state:
							_nbStatesReExplored++;
							STATS;

						} else {
							DEBUG_PRINT("         - state fresh, pushing on stack.\n");
							// The state was not visited at all
							htVisitedStatesInsert(s_->payloadHash, s_, DFS_OUTER);
							_nbStatesExplored++;
							STATS;

						}
						new = createStackElement(s_, _nbErrors);
#ifdef CEGAR
						new->trans = ((ptProcessTransition) current->E->value)->trans;
						new->accFeatures = conjunction;
#endif
						stackOuter = push(stackOuter, new);
						htOuterStatesInsert(s_->payloadHash, s_);
						_depth++;
					} // fresh state
				} // no assert violation
#ifdef CEGAR
				}
				else
					destroyBool(conjunction);
#endif
				// Simulate nested loop: when at the end of E, restart the E and advance the E_never
				// The deadlock test (E empty) is already done.  This also guarantees that E->value
				// is never NULL in the above apply(globalSymTab, mtypes, ).
				current->E_never = current->E_never->next;
				if(!current->E_never) {
					current->E = current->E->next;
					current->E_never = current->E_never_save;
				}
			} // fire transition
		} // explore state
	} // end while

#ifndef CEGAR
	// If error is true and we end up here, then we're in exhaustive mode. A summary has to be printed
	if(error /* not needed: && exhaustive */) STOP_ERROR_GLOBAL;
	destroyStackElementStack(stackOuter, processTrans);
	return error;
#else
	destroyStackElementStack(stackOuter, processTrans);
	if(_explored) (*_explored) += _nbStatesExplored;
	if(_reexplored) (*_reexplored) += _nbStatesReExplored;
	return ces;
#endif
}

byte innerDFS(std::stack<state*>& stackOuter, std::stack<state*>& stackInner) {

}