#include "unsgnSymNode.h"
#include "symTabVisitor.h"

void unsgnSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitUnsgn(this);
}