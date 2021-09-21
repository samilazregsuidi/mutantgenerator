#include "tdefSymNode.h"
#include "symTabVisitor.h"

void tdefSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitTdef(this);
}

unsigned int tdefSymNode::processVariables(symTabNode *global, const mTypeList *mTypes, unsigned int iOffset, bool isGlobal) {
	memSize = child->processVariables(global, mTypes, 0, false);
	return !next ? iOffset : next->processVariables(global, mTypes, iOffset, isGlobal);
}

tdefSymNode::operator std::string(void) const {
	std::string res = getTypeName() + " " + name + "{\n";
	const auto *children = child;
	while (children)
	{
		res += "\t" + std::string(*children) + (children->cnextSym() ? ";" : "") + "\n";
		children = children->cnextSym();
	}
	res += "};";
	return res;
}