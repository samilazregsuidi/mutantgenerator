#include "bitSymNode.h"
#include "symTabVisitor.h"

void bitSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitBit(this);
}

void bitSymNode::acceptVisitor(symTabConstVisitor *visitor) const {
	visitor->visitBit(this);
}

