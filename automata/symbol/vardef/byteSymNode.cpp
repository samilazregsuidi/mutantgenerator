#include "byteSymNode.h"
#include "symTabVisitor.h"

void byteSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitByte(this);
}

void byteSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitByte(this);
}