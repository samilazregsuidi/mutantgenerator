#include "shortSymNode.h"
#include "symTabVisitor.h"

void shortSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitShort(this);
}