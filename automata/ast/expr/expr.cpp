#include <assert.h>
#include <string>

#include "expr.h"
#include "argExpr.h"
#include "varExpr.h"

#include "procSymNode.h"

exprRun::exprRun(const std::string& procName, exprArgList *argList, exprVarRef *card, int lineNb)
	: expr(astNode::E_EXPR_RUN, lineNb)
{
	this->procName = procName;
	this->procSym = nullptr;
	this->card = card;
	this->argList = argList;
	
	this->card->setParent(this);
	this->argList->setParent(this);
}

exprRun::exprRun(const std::string& procName, exprArgList *argList, int lineNb)
	: expr(astNode::E_EXPR_RUN, lineNb)
{
	this->procName = procName;
	this->procSym = nullptr;
	this->card = nullptr;
	this->argList = argList;

	this->argList->setParent(this);
}

exprRun::operator std::string() const {
	return "run " + procName + (card ? "[" + std::string(*card) + "]" : "") + "(" + std::string(*argList) + ")";
}


expr* exprRun::deepCopy(void) const {
	exprRun* copy = new exprRun(*this);
	copy->argList = static_cast<exprArgList*>(argList->deepCopy());
	copy->card = static_cast<exprVarRef*>(card->deepCopy());
	return copy;
}