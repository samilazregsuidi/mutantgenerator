#include <assert.h>
#include <string>

#include "expr.h"
#include "varExpr.h"

#include "symTabNode.h"
#include "procSymNode.h"
#include "mTypeList.h"

exprRArgVar::exprRArgVar(exprVarRef *varRef, int lineNb)
	: exprRArg(astNode::E_RARG_VAR, lineNb)
{
	this->varRef = varRef;
}

symTabNode *exprRArgVar::symbolLookUpRight(void) const {
	return varRef->symbolLookUpRight();
}

symTabNode *exprRArgVar::symbolLookUpLeft(void) const {
	return varRef->symbolLookUpLeft();
}

void exprRArgVar::resolveVariables(symTabNode* globalSymTab, const mTypeList* mTypes, symTabNode* localSymTab, symTabNode* subFieldSymTab) {
	varRef->resolveVariables(globalSymTab, mTypes, localSymTab, subFieldSymTab);
}


exprRArgVar::operator std::string() const {
	return *varRef;
}

exprRun::exprRun(const std::string& procName, exprArgList *argList, exprVarRef *card, int lineNb)
	: expr(astNode::E_EXPR_RUN, lineNb)
{
	this->procName = procName;
	this->procSym = nullptr;
	this->card = card;
	this->argList = argList;
}

exprRun::exprRun(const std::string& procName, exprArgList *argList, int lineNb)
	: expr(astNode::E_EXPR_RUN, lineNb)
{
	this->procName = procName;
	this->procSym = nullptr;
	this->card = nullptr;
	this->argList = argList;
}

exprRun::operator std::string() const
{
	return "run " + procName + (card ? " [" + std::string(*card) + "]" : "") + "( " + std::string(*argList) + " ) ";
}

void exprRun::resolveVariables(symTabNode *global, const mTypeList *mTypes, symTabNode *local, symTabNode *subField) {

	if (subField)
		procSym = static_cast<procSymNode*>(subField->lookupInSymTab(procName));
	else if (local)
		procSym = static_cast<procSymNode*>(local->lookupInSymTab(procName));
	else
		procSym = static_cast<procSymNode*>(global->lookupInSymTab(procName));

	assert(procSym && procSym->getType() == symTabNode::T_PROC);

	card->resolveVariables(global, mTypes, local, subField);
	argList->resolveVariables(global, mTypes, local, subField);
}