#include "naSymNode.h"
#include "symTabVisitor.h"

template<> varSymNode* varSymNode::createSymTabNode<symTabNode::T_NA>(const varSymNode &old) {
	return new naSymNode(old);
}

void naSymNode::acceptVisitor(symTabVisitor *visitor) const {
	visitor->visitNA(this);
}

