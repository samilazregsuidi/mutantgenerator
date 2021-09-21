#include "procSymNode.h"
#include "symTabVisitor.h"
#include "expression.h"

void procSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitProc(this);
}

unsigned int procSymNode::processVariables(symTabNode *global, const mTypeList *mTypes, unsigned int iOffset, bool isGlobal) {
	childFsm->resolveVariables(global, mTypes, childFsm->getSymbol());
	if (init && init->getType() == astNode::E_EXPR_COUNT)
		init->resolveVariables(global, mTypes);
	memSize = childFsm->processVariables(global, mTypes, 0, 0);
	return !next ? iOffset : next->processVariables(global, mTypes, iOffset, isGlobal);
}

procSymNode::operator std::string(void) const {
	assert(init);
	std::string res = "";
	if (init->getIVal() >= 1)
	{
		res += "active";
	}
	if (init->getIVal() > 1)
	{
		res += " [" + std::to_string(init->getIVal()) + "]";
	}
	res += " proctype " + name + "(";
	const auto *arg = args;
	while (arg)
	{
		res += std::string(*arg) + (arg->cnextSym() ? ", " : "");
		arg = arg->cnextSym();
	}
	res += "){\n" + std::string(*childFsm) + "}\n";

	return res;
}
