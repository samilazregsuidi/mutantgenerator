#include "mtypedefSymNode.h"

#include <cassert>

#include "symTabVisitor.h"

void cmtypeSymNode::acceptVisitor(symTabVisitor* visitor) {
	visitor->visitCmtype(this);
}

void cmtypeSymNode::acceptVisitor(symTabConstVisitor* visitor) const {
	visitor->visitCmtype(this);
}

void mtypedefSymNode::acceptVisitor(symTabVisitor* visitor) {
	visitor->visitMtypedef(this);
}

void mtypedefSymNode::acceptVisitor(symTabConstVisitor* visitor) const {
	visitor->visitMtypedef(this);
}