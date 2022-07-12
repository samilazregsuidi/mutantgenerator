#include <assert.h>
#include <string>

#include "expr.hpp"
#include "argExpr.hpp"
#include "varExpr.hpp"

#include "procSymNode.hpp"

#include "astVisitor.hpp"

/****************************************************************
 * **************************************************************
 * *************************************************************/

expr::expr(Type type, int lineNb)
	: astNode(type, lineNb)
{
	exprType = symbol::T_NA;
}

symbol::Type expr::getExprType(void) const {
	return exprType;
}

void expr::setExprType(symbol::Type exprType) {
	this->exprType = exprType;
}

bool expr::castToExprType(symbol::Type type) const {
	type = type;//keep compiler happy
	return false;
}

symbol::Type expr::getExprType(expr* left, expr* right) {
	if(left->getExprType() == right->getExprType())
		return left->getExprType();
	else if(left->castToExprType(right->getExprType()))
		return right->getExprType();
	else if(right->castToExprType(left->getExprType()))
		return left->getExprType();

	return symbol::T_NA;
}

void expr::acceptVisitor(ASTConstVisitor* visitor) const {
	visitor->visit(this);
}

void expr::acceptVisitor(ASTVisitor* visitor) {
	visitor->visit(this);
}

int expr::acceptVisitor(ASTConstVisitorInt* visitor) const {
	return visitor->visit(this);
}

int expr::acceptVisitor(ASTVisitorInt* visitor) {
	return visitor->visit(this);
}

/****************************************************************
 * **************************************************************
 * *************************************************************/

exprCond::exprCond(expr *pcond, expr *pthen, expr *pelsE, int lineNb)
	: expr(astNode::E_EXPR_COND, lineNb)
{
	assert(pcond);
	assert(pthen);
	assert(pelsE);
	addChild("cond_expr", pcond);
	addChild("then_expr", pthen);
	addChild("else_expr", pelsE);
}

void exprCond::setCond(expr* cond) {
	eraseChild("cond_expr", cond);
}

void exprCond::setThen(expr* then) {
	eraseChild("then_expr", then);
}

void exprCond::setElse(expr* elsE) {
	eraseChild("else_expr", elsE);
}

expr* exprCond::getCond(void) const {
	return dynamic_cast<expr*>(getChild("cond_expr"));
}

expr* exprCond::getThen(void) const {
	return dynamic_cast<expr*>(getChild("then_expr"));
}

expr* exprCond::getElse(void) const {
	return dynamic_cast<expr*>(getChild("else_expr"));
}

exprCond::operator std::string() const {
	assert(getCond() && getThen() && getElse());
	return "(" + std::string(*getCond()) + "-> " + std::string(*getThen()) + ": " + std::string(*getElse())+ ")";
}

std::string exprCond::getTypeDescr(void) const {
	return "Conditional expression (E_EXPR_COND)";
}

symbol::Type exprCond::getExprType(void) const {
	return expr::getExprType(getThen(), getElse());
}

expr* exprCond::deepCopy(void) const {
	exprCond* copy = new exprCond(*this);
	copy->copyChildren(*this);
	return copy;
}

/****************************************************************
 * **************************************************************
 * *************************************************************/

exprRun::exprRun(const std::string& procName, exprArgList *argList, int lineNb)
	: expr(astNode::E_EXPR_RUN, lineNb)
	, procName(procName)
{
	//assert(argList);
	addChild("arg_list", argList);
}

void exprRun::setArgList(exprArgList* argList) {
	eraseChild("arg_list", argList);
}

exprArgList* exprRun::getArgList(void) const {
	return dynamic_cast<exprArgList*>(getChild("arg_list"));
}

std::string exprRun::getProcName(void) const {
	return procName;
}

procSymNode* exprRun::resolve(const symTable* symTab) {
	procSym = dynamic_cast<procSymNode*>(symTab->lookup(procName));
	assert(procSym);
	return procSym;
}

const procSymNode* exprRun::getProcType(void) const {
	return procSym;
}

exprRun::operator std::string() const {
	return "run " + procName + "(" + ( getArgList()? std::string(*getArgList()) : "" ) + ")";
}

std::string exprRun::getTypeDescr(void) const {
	return "Run (E_EXPR_RUN)";
}

symbol::Type exprRun::getExprType(void) const {
	return symbol::T_BYTE;
}

expr* exprRun::deepCopy(void) const {
	exprRun* copy = new exprRun(*this);
	copy->copyChildren(*this);
	return copy;
}

/****************************************************************
 * **************************************************************
 * *************************************************************/

exprTimeout::exprTimeout(int lineNb)
	: expr(astNode::E_EXPR_TIMEOUT, lineNb)
{
}

exprTimeout::operator std::string() const {
	return "timeout";
}

std::string exprTimeout::getTypeDescr(void) const {
	return "Timeout (E_EXPR_TIMEOUT)";
}

symbol::Type exprTimeout::getExprType(void) const {
	return symbol::T_BOOL;
}

expr* exprTimeout::deepCopy(void) const {
	exprTimeout* copy = new exprTimeout(*this);
	return copy;
}

/****************************************************************
 * **************************************************************
 * *************************************************************/

exprSkip::exprSkip(int lineNb)
	: expr(astNode::E_EXPR_SKIP, lineNb)
{
}

exprSkip::operator std::string() const {
	return "skip";
}

std::string exprSkip::getTypeDescr(void) const {
	return "Skip (E_EXPR_SKIP)";
}

symbol::Type exprSkip::getExprType(void) const {
	return symbol::T_BOOL;
}

expr* exprSkip::deepCopy(void) const {
	exprSkip* copy = new exprSkip(*this);
	return copy;
}