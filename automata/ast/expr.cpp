#include <assert.h>
#include <string>

#include "expr.h"
#include "varExpr.h"

#include "symbol.h"
#include "procSymNode.h"

exprRArgVar::exprRArgVar(exprVarRef *varRef, int lineNb)
	: exprRArg(astNode::E_RARG_VAR, lineNb)
{
	this->varRef = varRef;
}

symbol *exprRArgVar::symbolLookUpRight(void) const {
	return varRef->symbolLookUpRight();
}

symbol *exprRArgVar::symbolLookUpLeft(void) const {
	return varRef->symbolLookUpLeft();
}

/*void exprRArgVar::resolveVariables(symTable* globalSymTab) {
	varRef->resolveVariables(globalSymTab);
}*/


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

exprRun::operator std::string() const {
	return "run " + procName + (card ? "[" + std::string(*card) + "]" : "") + "(" + std::string(*argList) + ")";
}

/*void exprRun::resolveVariables(symTable *global) {

	if (global)
		procSym = static_cast<procSymNode*>(global->lookup(procName));

	assert(procSym && procSym->getType() == symbol::T_PROC);

	card->resolveVariables(global);
	argList->resolveVariables(global);
}*/