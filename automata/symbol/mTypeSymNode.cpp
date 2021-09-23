#include "mTypeSymNode.h"
#include "symTabVisitor.h"

void mTypeSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitMtype(this);
}
