#include "utypeSymNode.h"
#include "symTabVisitor.h"
#include "tdefSymNode.h"

utypeSymNode::utypeSymNode(tdefSymNode* utype, int lineNb)
	: varSymNode(symTabNode::T_UTYPE, lineNb, std::string())
{
	assert(utype != nullptr && utype->getType() == symTabNode::T_TDEF);
	this->utype = utype;
}

void utypeSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitUtype(this);
}

unsigned int utypeSymNode::processVariables(symTabNode *global, const mTypeList *mTypes, unsigned int iOffset, bool isGlobal) {
	memSize = utype->getMemorySize();
	memOffset = iOffset;
	unsigned int iMemSpace = memSize * bound;
	return !next ? iOffset + iMemSpace : next->processVariables(global, mTypes, iOffset + iMemSpace, isGlobal);
}