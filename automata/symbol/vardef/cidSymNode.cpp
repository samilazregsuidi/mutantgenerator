#include "cidSymNode.hpp"
#include "symTabVisitor.hpp"

cidSymNode::cidSymNode(int lineNb, const std::string& name, int bound, expr* init)
	: varSymNode(symbol::T_CID, lineNb, name, bound, init)
{}

std::string cidSymNode::getTypeName(void) const {
	return "cid"+ (getBound() > 1? "[" + std::to_string(getBound()) + "]": "");
}

int cidSymNode::getTypeSize(void) const {
	return 4;
}

void cidSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitCid(this);
}

void cidSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitCid(this);
}