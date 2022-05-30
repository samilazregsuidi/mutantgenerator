#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "error.h"

#include "process.hpp"
#include "ast.hpp"
#include "automata.hpp"

#include "payload.hpp"
#include "state.hpp"
#include "variable.hpp"

process::process(state* s, size_t _offset, const seqSymNode* sym, const fsmNode* start, int pid, unsigned int index)
	: payLoad(s->payLoad)
	, offset(_offset)
	, symType(sym)
	, index(index)
	, s(s)
	, pid(pid)
	, start(start)
{
	payLoad->addSize(sizeof(const fsmNode*));

	for (auto s : sym->getSymTable()->getSymbols<const varSymNode*>()) {
		addVariable(s);
	}
}

process::~process() {
	for(auto var : varList)
		delete var;
}

void process::init(void) {
	
	storeNodePointer(start);

	for(auto var : varList)
		var->init();
}

const fsmNode* process::getNodePointer(void) const {
	return s->payLoad->getValue<const fsmNode*>(offset);
}

void process::storeNodePointer(const fsmNode* pointer) {
	assert(pointer);
	s->payLoad->setValue<const fsmNode*>(offset, pointer);
}

bool process::isAccepting(void) const {
	return getNodePointer()->getFlags() & fsmNode::N_ACCEPT;
}

bool process::isAtomic(void) const {
	return getNodePointer()->getFlags() & fsmNode::N_ATOMIC;
}

void process::print(void) const {
	
	auto node = getNodePointer();
	if(symType->getType() == symbol::T_NEVER) {
		if(node)	printf("   never                               @ NL%02d %s\n", node->getLineNb(), node->getFlags() & fsmNode::N_ACCEPT ? " (accepting)" : "");
		else 		printf("   never                               @ end\n");
	
	} else {

		if(node) 	printf("   pid %02d, %-27s @ NL%02d\n", pid, symType->getName(), node->getLineNb());
		else 		printf("   pid %02d, %-27s @ end\n", 	pid, symType->getName());
		
		for(auto var : varList)
			var->print();
	}

}