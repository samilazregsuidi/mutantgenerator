#include "shortSymNode.h"
#include "symTabVisitor.h"

template<> varSymNode* varSymNode::createSymTabNode<symTabNode::T_SHORT>(const varSymNode &old) {
	return new shortSymNode(old);
}

void shortSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitShort(this);
}