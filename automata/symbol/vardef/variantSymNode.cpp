#include "variantSymNode.hpp"
#include "expr.hpp"

variantSymNode::variantSymNode(int lineNb, const std::string& name, expr* feat_expr)
	: symbol(symbol::T_VARIANT, lineNb, name)
	, feat_expr(feat_expr)
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
	return "{" + name + "}[" + std::string(*feat_expr) + "]";
}
