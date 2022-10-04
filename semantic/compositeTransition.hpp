#ifndef COMPOSITE_TRANSITION_H
#define COMPOSITE_TRANSITION_H

/*
 * Execution of FSMs
 * * * * * * * * * * * * * * * * * * * * * * * */

#include <list>

#include "transition.hpp"

class state;

// ProcessTransitions are returned by the executables() function
class compTransition : public transition {
public:
	compTransition(state* s, const std::list<const transition*>& ts);
	
	~compTransition() override;
	
	transition* deepCopy(void) const override;

public:		//
	std::list<const transition*> Ts;
};

#endif
