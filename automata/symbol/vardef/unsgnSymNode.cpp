#include "unsgnSymNode.hpp"
#include "symTabVisitor.hpp"

unsgnSymNode::unsgnSymNode(int lineNb, const std::string& name, int bound, expr* init)
	: varSymNode(symbol::T_UNSGN, lineNb, name, bound, init)
{}

std::string unsgnSymNode::getTypeName(void) const {
	return "unsigned"+ (getBound() > 1? "[" + std::to_string(getBound()) + "]": "");
}

int unsgnSymNode::getTypeSize(void) const {
	return 2;
}

void unsgnSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitUnsgn(this);
}

void unsgnSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitUnsgn(this);
}