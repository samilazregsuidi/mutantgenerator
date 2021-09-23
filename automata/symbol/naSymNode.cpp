#include "naSymNode.h"
#include "symTabVisitor.h"

void naSymNode::acceptVisitor(symTabVisitor *visitor) const {
	visitor->visitNA(this);
}

