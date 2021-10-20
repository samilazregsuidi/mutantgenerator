#include "intSymNode.h"
#include "symTabVisitor.h"

void intSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitInt(this);
}

void intSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitInt(this);
}

