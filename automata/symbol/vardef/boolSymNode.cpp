#include "boolSymNode.hpp"
#include "symTabVisitor.hpp"

boolSymNode::boolSymNode(int lineNb, const std::string& name, int bound, expr* init)
	: varSymNode(symbol::T_BOOL, lineNb, name, bound, init)
{}

std::string boolSymNode::getTypeName(void) const {
	return "bool" + (getBound() > 1? "[" + std::to_string(getBound()) + "]": "");
}

int boolSymNode::getTypeSize(void) const {
	return 1;
}

int boolSymNode::getUpperBound(void) const {
	return std::numeric_limits<bool>::max();
}
	
int boolSymNode::getLowerBound(void) const {
	return std::numeric_limits<bool>::min();
}

void boolSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitBool(this);
}

void boolSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitBool(this);
}