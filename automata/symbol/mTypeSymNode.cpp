#include "mTypeSymNode.h"
#include "symTabVisitor.h"

template<> varSymNode* varSymNode::createSymTabNode<symTabNode::T_MTYPE>(const varSymNode &old) {
	return new mTypeSymNode(old);
}

void mTypeSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitMtype(this);
}
