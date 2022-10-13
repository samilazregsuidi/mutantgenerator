#include "shortSymNode.hpp"
#include "symTabVisitor.hpp"

#include <limits>

shortSymNode::shortSymNode(int lineNb, const std::string& name, int bound, expr* init)
	: varSymNode(symbol::T_SHORT, lineNb, name, bound, init)
{}

std::string shortSymNode::getBasicTypeName(void) const {
	return "short";
}

int shortSymNode::getTypeSize(void) const {
	return 2;
}

int shortSymNode::getUpperBound(void) const {
	return std::numeric_limits<short>::max();
}
	
int shortSymNode::getLowerBound(void) const {
	return std::numeric_limits<short>::min();
}

void shortSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitShort(this);
}

void shortSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitShort(this);
}