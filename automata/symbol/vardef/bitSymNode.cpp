#include "bitSymNode.hpp"
#include "symTabVisitor.hpp"

bitSymNode::bitSymNode(int lineNb, const std::string& name, int bound, expr* init)
	: varSymNode(symbol::T_BIT, lineNb, name, bound, init)
{}

std::string bitSymNode::getBasicTypeName(void) const {
	return "bit";
}

int bitSymNode::getTypeSize(void) const {
	return 1;
}

int bitSymNode::getUpperBound(void) const {
	return 1;
}
	
int bitSymNode::getLowerBound(void) const {
	return 0;
}

void bitSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitBit(this);
}

void bitSymNode::acceptVisitor(symTabConstVisitor *visitor) const {
	visitor->visitBit(this);
}

