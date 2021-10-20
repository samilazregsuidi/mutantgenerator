#include "mtypeSymNode.h"
#include "symTabVisitor.h"

void mtypeSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitMtype(this);
}

void mtypeSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitMtype(this);
}
