#include "bitSymNode.h"
#include "symTabVisitor.h"

template<> varSymNode* varSymNode::createSymTabNode<symTabNode::T_BIT>(const varSymNode &old) {
	return new bitSymNode(old);
}

void bitSymNode::acceptVisitor(symTabVisitor *visitor) const {
	visitor->visitBit(this);
}