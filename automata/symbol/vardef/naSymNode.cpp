#include "naSymNode.hpp"
#include "symTabVisitor.hpp"

naSymNode::naSymNode(int lineNb, const std::string& name, int bound, expr* init)
	: varSymNode(symbol::T_NA, lineNb, name, bound, init)
{}

std::string naSymNode::getTypeName(void) const {
	//assert(false);
	return "NA"+ (getBound() > 1? "[" + std::to_string(getBound()) + "]": "");
}

int naSymNode::getTypeSize(void) const {
	assert(false);
	return 0;
}

void naSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitNA(this);
}

void naSymNode::acceptVisitor(symTabConstVisitor *visitor) const {
	visitor->visitNA(this);
}

