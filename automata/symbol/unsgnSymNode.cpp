#include "unsgnSymNode.h"
#include "symTabVisitor.h"

void unsgnSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitUnsgn(this);
}

void unsgnSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitUnsgn(this);
}