#ifndef RENDEZ_VOUS_TRANSITION_H
#define RENDEZ_VOUS_TRANSITION_H

/*
 * Execution of FSMs
 * * * * * * * * * * * * * * * * * * * * * * * */

#include "programTransition.hpp"

// ProcessTransitions are returned by the executables() function
class RVTransition : public progTransition {
public:

	RVTransition(state* s, process* proc, const fsmEdge* trans, progTransition* response);

	//RVTransition(state* s, process* proc, const fsmEdge* trans, const ADD& featExpr, progTransition* response);
	
	~RVTransition() override;
	
	transition* deepCopy(void) const override;

	progTransition* getResponse(void) const;

public:		//
	progTransition* response;
};

#endif
