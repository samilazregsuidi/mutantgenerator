#include "intSymNode.h"
#include "symTabVisitor.h"

void intSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitInt(this);
}
