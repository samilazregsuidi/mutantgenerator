#include "inlineSymNode.hpp"
#include "symTabVisitor.hpp"
#include "constExpr.hpp"
#include "stmnt.hpp"

inlineSymNode::inlineSymNode(const std::string& name, const std::list<std::string>& params, stmnt* block, int lineNb)
	: seqSymNode(symbol::T_INLINE, name, lineNb, block) {
	this->params = params;
}

std::string inlineSymNode::getTypeName(void) const {
	return "inline";
}

std::string inlineSymNode::getBasicTypeName(void) const {
	return "inline";
}

int inlineSymNode::getTypeSize(void) const {
	return 0;
}

const std::list<std::string>& inlineSymNode::getParams(void) const {
	return params;
}

void inlineSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitInline(this);
}

void inlineSymNode::acceptVisitor(symTabConstVisitor *visitor) const {
	visitor->visitInline(this);
}

inlineSymNode::operator std::string(void) const {
	std::string res = "";

	res += "inline " + name + "(";
	unsigned int i = 0;
	for(auto it : params)
		res += it + (++i != params.size() ? ", " : "");

	res += "){\n" + (block? stmnt::string(block) : "") + "}\n";

	return res;
}
