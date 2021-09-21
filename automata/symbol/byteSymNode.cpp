#include "byteSymNode.h"
#include "symTabVisitor.h"

template<> varSymNode* varSymNode::createSymTabNode<symTabNode::T_BYTE>(const varSymNode &old) {
	return new byteSymNode(old);
}

void byteSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitByte(this);
}