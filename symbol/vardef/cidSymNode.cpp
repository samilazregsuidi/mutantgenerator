#include "cidSymNode.hpp"
#include "symTabVisitor.hpp"

#include <limits>

cidSymNode::cidSymNode(int lineNb, const std::string& name, int bound, expr* init)
	: varSymNode(symbol::T_CID, lineNb, name, bound, init)
{}

std::string cidSymNode::getBasicTypeName(void) const {
	return "cid";
}

int cidSymNode::getTypeSize(void) const {
	return 4;
}

int cidSymNode::getUpperBound(void) const {
	return std::numeric_limits<unsigned int>::max();
}
	
int cidSymNode::getLowerBound(void) const {
	return std::numeric_limits<unsigned int>::min();
}

void cidSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitCid(this);
}

void cidSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitCid(this);
}