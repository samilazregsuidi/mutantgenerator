#include "shortSymNode.h"
#include "symTabVisitor.h"

void shortSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitShort(this);
}

void shortSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitShort(this);
}