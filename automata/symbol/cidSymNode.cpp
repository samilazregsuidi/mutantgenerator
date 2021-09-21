#include "cidSymNode.h"
#include "symTabVisitor.h"

void cidSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitCid(this);
}