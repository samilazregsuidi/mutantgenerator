#include "utypeSymNode.h"
#include "symTabVisitor.h"
#include "tdefSymNode.h"

template<> varSymNode* varSymNode::createSymTabNode<symTabNode::T_UTYPE>(const varSymNode &old) {
	return new utypeSymNode(static_cast<const utypeSymNode&>(old));
}

utypeSymNode::utypeSymNode(tdefSymNode* utype, int lineNb)
	: varSymNode(symTabNode::T_UTYPE, lineNb, std::string())
{
	assert(type != nullptr && type->getType() == symTabNode::T_TDEF);
	this->type = type;
}

void utypeSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitUtype(this);
}

unsigned int utypeSymNode::processVariables(symTabNode *global, const mTypeList *mTypes, unsigned int iOffset, bool isGlobal) {
	memSize = type->getMemorySize();
	memOffset = iOffset;
	unsigned int iMemSpace = memSize * bound;
	return !next ? iOffset + iMemSpace : next->processVariables(global, mTypes, iOffset + iMemSpace, isGlobal);
}