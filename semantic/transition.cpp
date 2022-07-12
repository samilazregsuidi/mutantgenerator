#include "transition.hpp"

#include <assert.h>
#include <iterator>

transition* transition::sample(const std::list<transition*>& transList) {
	if(transList.size() == 0)
		return nullptr;
	auto it = transList.begin();
	std::advance(it, rand() % transList.size());
	return *it;
}

transition::transition(process* proc, const fsmEdge* edge, transition* response) 
	: proc(proc)
	, edge(edge)
	, response(response)
	, prob(1.)
{
	assert(proc && edge);
}

transition::~transition() {
	if(response)
		delete response;
}
	
transition* transition::deepCopy(void) const {
	return nullptr;
}

process* transition::getProc(void) const {
	return proc;
}

const fsmEdge* transition::getEdge(void) const {
	return edge;
}

transition* transition::getResponse(void) const {
	return response;
}