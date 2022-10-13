#include "unsgnSymNode.hpp"
#include "symTabVisitor.hpp"

unsgnSymNode::unsgnSymNode(int lineNb, const std::string& name, int bound, expr* init)
	: varSymNode(symbol::T_UNSGN, lineNb, name, bound, init)
{}

std::string unsgnSymNode::getBasicTypeName(void) const {
	return "unsigned";
}

int unsgnSymNode::getTypeSize(void) const {
	return 2;
}

int unsgnSymNode::getUpperBound(void) const {
	assert(false);
}
	
int unsgnSymNode::getLowerBound(void) const {
	assert(false);
}

void unsgnSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitUnsgn(this);
}

void unsgnSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitUnsgn(this);
}