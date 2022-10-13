#include "fMultiLTLSymNode.hpp"

#include "temporalExpr.hpp"
#include "expr.hpp"

fMultiLTLSymNode::fMultiLTLSymNode(const std::string& name, const std::list<variantQuantifier*>& variants, expr* formula, int lineNb)
	: symbol(symbol::T_FMULTI_LTL, name, lineNb)
	, variants(variants)
	, formula(formula)
{
}

std::string fMultiLTLSymNode::getTypeName(void) const {
	return "fMultiLTL";
}

std::string fMultiLTLSymNode::getBasicTypeName(void) const {
	return "fMultiLTL";
}

int fMultiLTLSymNode::getTypeSize(void) const {
	return 0;
}

fMultiLTLSymNode::operator std::string(void) const {
	std::string res = "";

	res += getBasicTypeName() + name + "{\n";
	for(auto it : variants)
		res += std::string(*it);

	res += "){\n" + std::string(*formula) + "}\n";

	return res;
}

void fMultiLTLSymNode::acceptVisitor(symTabVisitor* visitor) {}

void fMultiLTLSymNode::acceptVisitor(symTabConstVisitor* visitor) const {}
