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

	setArgList(argList);
	setCard(card);
}

exprRun::exprRun(const std::string& procName, exprArgList *argList, int lineNb)
	: expr(astNode::E_EXPR_RUN, lineNb)
{
	this->procName = procName;
	this->procSym = nullptr;

	setArgList(argList);
	setCard(nullptr);
}

void exprRun::setCard(exprVarRef* card) {
	rmChild(this->card);
	addChild(card);
	this->card = card;
}

void exprRun::setArgList(exprArgList* argList) {
	rmChild(this->argList);
	addChild(argList);
	this->argList = argList;
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