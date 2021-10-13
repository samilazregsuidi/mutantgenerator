#include "chanSymNode.h"
#include "symTabVisitor.h"

chanSymNode::~chanSymNode(){
	for(auto it : types)
		delete it;
}

void chanSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitChan(this);
}

void chanSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitChan(this);
}

/*unsigned int chanSymNode::processVariables(symTabNode *global, const mTypeList *mTypes, unsigned int iOffset, bool isGlobal) {
	assert(init);
	unsigned int iMemSpace = 0;
	this->memOffset = iOffset;
	this->memSize = child->processVariables(global, mTypes, 0, 0);
	if ((iMemSpace = memSize * capacity * bound + bound))
		;
	else
		iMemSpace = memSize * bound + bound;
	return !next ? iOffset + iMemSpace : next->processVariables(global, mTypes, iOffset + iMemSpace, isGlobal);
}*/