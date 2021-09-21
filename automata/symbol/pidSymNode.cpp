#include "pidSymNode.h"
#include "symTabVisitor.h"

void pidSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitPid(this);
}