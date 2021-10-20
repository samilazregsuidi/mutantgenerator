#include "pidSymNode.h"
#include "symTabVisitor.h"

void pidSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitPid(this);
}

void pidSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitPid(this);
}