#include "rendezVousTransition.hpp"

#include "state.hpp"
#include "process.hpp"
#include "fsmEdge.hpp"

#include <assert.h>
#include <iterator>

RVTransition::RVTransition(state* s, process* proc, const fsmEdge* edge, progTransition* response) 
	: progTransition(s, proc, edge)
	, response(response)
{
	assert(response);
	prob = edge->getProbability() * response->getEdge()->getProbability();
}

/*RVTransition::RVTransition(state* s, process* proc, const fsmEdge* edge, const ADD& featExpr, progTransition* response)
	: progTransition(s, proc, edge, featExpr)
	, response(response)
{
	assert(response);
	prob = edge->getProbability() * response->getEdge()->getProbability();
}*/

RVTransition::~RVTransition() {
	assert(response);
	delete response;
}

transition* RVTransition::deepCopy(void) const {
	return nullptr;
}

progTransition* RVTransition::getResponse(void) const {
	return response;
}