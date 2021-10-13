#include "naSymNode.h"
#include "symTabVisitor.h"

void naSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitNA(this);
}

void naSymNode::acceptVisitor(symTabConstVisitor *visitor) const {
	visitor->visitNA(this);
}

