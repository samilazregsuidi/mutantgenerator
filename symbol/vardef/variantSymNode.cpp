#include "variantSymNode.hpp"
#include "expr.hpp"

variantSymNode::variantSymNode(int lineNb, const std::string& name, expr* init)
	: varSymNode(symbol::T_VARIANT, lineNb, name)
	, init(init)
{}

std::string variantSymNode::getBasicTypeName(void) const {
	return "variant";
}

std::string variantSymNode::getTypeName(void) const {
	return getBasicTypeName();
}

int variantSymNode::getTypeSize(void) const {
	return 0;
}

variantSymNode::operator std::string(void) const {
	return "{" + name + "}[" + std::string(*init) + "]";
}

void variantSymNode::acceptVisitor(symTabVisitor* visitor) {

}

void variantSymNode::acceptVisitor(symTabConstVisitor* visitor) const {
	
}
