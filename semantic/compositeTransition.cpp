#include "compositeTransition.hpp"
#include "transition.hpp"

#include "state.hpp"

compTransition::compTransition(state* s, const std::list<const transition*>& Ts)
	: transition(s)
	, Ts(Ts)
{}

compTransition::~compTransition(){
	
}
	
transition* compTransition::deepCopy(void) const {
	return nullptr;
}