#include "chanSymNode.h"
#include "symTabVisitor.h"

chanSymNode::~chanSymNode(void){
	delete child;
}

void chanSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitChan(this);
}

unsigned int chanSymNode::processVariables(symTabNode *global, const mTypeList *mTypes, unsigned int iOffset, bool isGlobal) {
	assert(init);
	unsigned int iMemSpace = 0;
	this->memOffset = iOffset;
	this->memSize = child->processVariables(global, mTypes, 0, 0);
	if ((iMemSpace = memSize * capacity * bound + bound))
		;
	else
		iMemSpace = memSize * bound + bound;
	return !next ? iOffset + iMemSpace : next->processVariables(global, mTypes, iOffset + iMemSpace, isGlobal);
}