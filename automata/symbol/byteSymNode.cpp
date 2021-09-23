#include "byteSymNode.h"
#include "symTabVisitor.h"

void byteSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitByte(this);
}