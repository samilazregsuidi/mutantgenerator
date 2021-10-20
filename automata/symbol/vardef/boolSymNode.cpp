#include "boolSymNode.h"
#include "symTabVisitor.h"

void boolSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitBool(this);
}

void boolSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitBool(this);
}