#include "intSymNode.h"
#include "symTabVisitor.h"

template<> varSymNode* varSymNode::createSymTabNode<symTabNode::T_INT>(const varSymNode &old) {
	return new intSymNode(old);
}

void intSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitInt(this);
}
