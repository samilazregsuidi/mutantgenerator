#include "utypeSymNode.h"
#include "symTabVisitor.h"
#include "tdefSymNode.h"

utypeSymNode::utypeSymNode(tdefSymNode* utype, int lineNb)
	: varSymNode(symbol::T_UTYPE, lineNb, std::string())
{
	assert(utype != nullptr && utype->getType() == symbol::T_TDEF);
	this->utype = utype;
}

void utypeSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitUtype(this);
}

/*unsigned int utypeSymNode::processVariables(symbol *global, const mTypeList *mTypes, unsigned int iOffset, bool isGlobal) {
	memSize = utype->getMemorySize();
	memOffset = iOffset;
	unsigned int iMemSpace = memSize * bound;
	return !next ? iOffset + iMemSpace : next->processVariables(global, mTypes, iOffset + iMemSpace, isGlobal);
}*/