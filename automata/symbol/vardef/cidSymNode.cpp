#include "cidSymNode.h"
#include "symTabVisitor.h"

void cidSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitCid(this);
}

void cidSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitCid(this);
}