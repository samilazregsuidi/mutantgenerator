#include "intSymNode.hpp"
#include "symTabVisitor.hpp"

#include <limits>

intSymNode::intSymNode(int lineNb, const std::string& name, int bound, expr* init)
	: varSymNode(symbol::T_INT, lineNb, name, bound, init)
{}

std::string intSymNode::getBasicTypeName(void) const {
	return "int";
}

int intSymNode::getTypeSize(void) const {
	return 4;
}

int intSymNode::getUpperBound(void) const {
	return std::numeric_limits<int>::max();
}
	
int intSymNode::getLowerBound(void) const {
	return std::numeric_limits<int>::min();
}

void intSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitInt(this);
}

void intSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitInt(this);
}

