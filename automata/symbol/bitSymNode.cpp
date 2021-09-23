#include "bitSymNode.h"
#include "symTabVisitor.h"

void bitSymNode::acceptVisitor(symTabVisitor *visitor) const {
	visitor->visitBit(this);
}

