#include <assert.h>
#include <string>

#include "expr.h"
#include "varExpr.h"

#include "symTabNode.h"
#include "mTypeList.h"

exprRArgVar::exprRArgVar(exprVarRef *child0, int lineNb)
	: exprRArg(astNode::E_RARG_VAR, 0, child0, nullptr, nullptr, lineNb)
{
}

exprRun::exprRun(const std::string& procName, exprArgList *child0, exprVarRef *child1, int lineNb)
	: expr(astNode::E_EXPR_RUN, 0, child0, child1, nullptr, lineNb)
{
	this->procName = procName;
}

exprRun::exprRun(const std::string& procName, exprArgList *child0, int lineNb)
	: expr(astNode::E_EXPR_RUN, 0, child0, nullptr, nullptr, lineNb)
{
	this->procName = procName;
}

void exprRun::resolveVariables(symTabNode *global, const mTypeList *mTypes, symTabNode *local, symTabNode *subField) {

	if (subField)
		symTab = subField->lookupInSymTab(procName);
	else if (local)
		symTab = local->lookupInSymTab(procName);
	else
		symTab = global->lookupInSymTab(procName);

	assert(symTab && symTab->getType() == symTabNode::T_PROC);

	child[0]->resolveVariables(global, mTypes, local, subField);
}