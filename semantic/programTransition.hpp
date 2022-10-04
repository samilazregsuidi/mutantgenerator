#ifndef PROGRAM_TRANSITION_H
#define PROGRAM_TRANSITION_H

/*
 * Execution of FSMs
 * * * * * * * * * * * * * * * * * * * * * * * */

#include "transition.hpp"

//#include "cuddObj.hh"

class fsmEdge;
class process;

// ProcessTransitions are returned by the executables() function
class progTransition : public transition {
public:
	progTransition(state* s, process* proc, const fsmEdge* trans);

	//progTransition(state* s, process* proc, const fsmEdge* trans, const ADD& featExpr);
	
	~progTransition() override;
	
	transition* deepCopy(void) const override;

	process* getProc(void) const;

	const fsmEdge* getEdge(void) const;

public:		//
	process* proc;		//	- The mask of the process to which the transition belongs (from the state that was given to executables())
	const fsmEdge* const edge;			//  - The transition that can be fired
	//ADD features;
};

#endif
