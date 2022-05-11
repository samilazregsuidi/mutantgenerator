#include "shortSymNode.hpp"
#include "symTabVisitor.hpp"

shortSymNode::shortSymNode(int lineNb, const std::string& name, int bound, expr* init)
	: varSymNode(symbol::T_SHORT, lineNb, name, bound, init)
{}

std::string shortSymNode::getTypeName(void) const {
	return "short"+ (getBound() > 1? "[" + std::to_string(getBound()) + "]": "");
}

int shortSymNode::getTypeSize(void) const {
	return 2;
}

void shortSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitShort(this);
}

void shortSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitShort(this);
}