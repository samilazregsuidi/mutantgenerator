#include "programTransition.hpp"

#include "state.hpp"
#include "fsmEdge.hpp"
#include "process.hpp"

#include <assert.h>
#include <iterator>

progTransition::progTransition(state* s, process* proc, const fsmEdge* edge) 
	: transition(s)
	, proc(proc)
	, edge(edge)
	//, features(ADD())
{
	prob = edge->getProbability();
}

/*progTransition::progTransition(state* s, process* proc, const fsmEdge* trans, const ADD& featExpr)
	: transition(s)
	, proc(proc)
	, edge(edge)
	//, features(featExpr)
{
	assert(proc && edge);
	prob = edge->getProbability();
}*/

progTransition::~progTransition() {

}
	
transition* progTransition::deepCopy(void) const {
	return nullptr;
}

process* progTransition::getProc(void) const {
	return proc;
}

const fsmEdge* progTransition::getEdge(void) const {
	return edge;
}