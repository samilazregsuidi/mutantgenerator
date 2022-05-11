#include "bitSymNode.hpp"
#include "symTabVisitor.hpp"

bitSymNode::bitSymNode(int lineNb, const std::string& name, int bound, expr* init)
	: varSymNode(symbol::T_BIT, lineNb, name, bound, init)
{}

std::string bitSymNode::getTypeName(void) const {
	return "bit" + (getBound() > 1? "[" + std::to_string(getBound()) + "]": "");
}

int bitSymNode::getTypeSize(void) const {
	return 1;
}

void bitSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitBit(this);
}

void bitSymNode::acceptVisitor(symTabConstVisitor *visitor) const {
	visitor->visitBit(this);
}

