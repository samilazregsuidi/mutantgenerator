#include "boolSymNode.h"
#include "symTabVisitor.h"

void boolSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitBool(this);
}