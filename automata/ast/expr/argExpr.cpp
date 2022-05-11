#include <assert.h>
#include <string>

#include "argExpr.hpp"
#include "varExpr.hpp"

/****************************************************************
 * **************************************************************
 * *************************************************************/


/****************************************************************
 * **************************************************************
 * *************************************************************/

exprRArgVar::exprRArgVar(exprVarRef *varRef, int lineNb)
	: exprRArg(astNode::E_RARG_VAR, lineNb)
{
	assert(varRef);
	addChild("var_ref", varRef);
}

void exprRArgVar::setVarRef(exprVarRef* varRef) {
	eraseChild("var_ref", varRef);
}

exprVarRef* exprRArgVar::getVarRef(void) const {
	return dynamic_cast<exprVarRef*>(getChild("var_ref"));
}

exprRArgVar::operator std::string() const {
	return *getVarRef();
}

std::string exprRArgVar::getTypeDescr(void) const {
	return "Receive argument variable (E_RARG_VAR)";
}

astNode* exprRArgVar::deepCopy(void) const {
	exprRArgVar* copy = new exprRArgVar(*this);
	copy->copyChildren(*this);
	return copy;
}

/****************************************************************
 * **************************************************************
 * *************************************************************/

exprRArgEval::exprRArgEval(expr *toEval, int lineNb)
	: exprRArg(astNode::E_RARG_EVAL, lineNb)
{
	assert(toEval);
	addChild("to_eval", toEval);
}

void exprRArgEval::setToEval(expr* toEval) {
	eraseChild("to_eval", toEval);
}

expr* exprRArgEval::getToEval(void) const  {
	return dynamic_cast<expr*>(getChild("to_eval"));
}

exprRArgEval::operator std::string() const {
	assert(getToEval());
	return "eval(" + std::string(*getToEval()) + ")";
}

std::string exprRArgEval::getTypeDescr(void) const {
	return "Receive argument eval (E_RARG_EVAL)";
}

astNode* exprRArgEval::deepCopy(void) const {
	exprRArgEval* copy = new exprRArgEval(*this);
	copy->copyChildren(*this);
	return copy;
}

/****************************************************************
 * **************************************************************
 * *************************************************************/

exprRArgConst::exprRArgConst(int constant, int lineNb)
	: exprRArg(astNode::E_RARG_EVAL, lineNb)
	, constant(constant)
{}

exprRArgConst::operator std::string() const {
	return std::to_string(constant);
}

std::string exprRArgConst::getTypeDescr(void) const {
	return "Receive argument constant (E_RARG_CONST)";
}

int exprRArgConst::getCstValue(void) const {
	return constant;
}

astNode* exprRArgConst::deepCopy(void) const {
	exprRArgConst* copy = new exprRArgConst(*this);
	return copy;
}

/****************************************************************
 * **************************************************************
 * *************************************************************/

exprRArgList::exprRArgList(exprRArg *node, exprRArgList *list, int lineNb)
	: astNode(astNode::E_RARGLIST, lineNb)
{
	assert(node);
	assert(list);
	addChild("r_arg", node);
	addChild("r_arg_list", list);
}

exprRArgList::exprRArgList(exprRArg *node, int lineNb)
	: astNode(astNode::E_RARGLIST, lineNb)
{
	assert(node);
	addChild("r_arg", node);
}

void exprRArgList::setRArg(exprRArg* node) {
	eraseChild("r_arg", node);
}

void exprRArgList::setRArgList(exprRArgList* list) {
	eraseChild("r_arg_list", list);
}

exprRArg* exprRArgList::getExprRArg(void) const {
	return dynamic_cast<exprRArg*>(getChild("r_arg"));
}

exprRArgList* exprRArgList::getRArgList(void) const {
	return dynamic_cast<exprRArgList*>(getChild("r_arg_list"));
}

unsigned int exprRArgList::getSize(void) const {
	return 1 + (getRArgList()? getRArgList()->getSize() : 0);
}

exprRArgList::operator std::string() const {
	assert(getExprRArg());
	return std::string(*getExprRArg()) + (getRArgList() ? ", " + std::string(*getRArgList()) : "");
}

std::string exprRArgList::getTypeDescr(void) const {
	return "Argument list (E_RARGLIST)";
}

astNode* exprRArgList::deepCopy(void) const {
	exprRArgList* copy = new exprRArgList(*this);
	copy->copyChildren(*this);
	return copy;
}

/****************************************************************
 * **************************************************************
 * *************************************************************/

/****************************************************************
 * **************************************************************
 * *************************************************************/

exprArg::exprArg(expr* expr, int lineNb)
	: astNode(astNode::E_ARG, lineNb)
{
	assert(expr);
	addChild("expr", expr);
}

void exprArg::setExpr(expr* expr) {
	eraseChild("expr", expr);
}

expr* exprArg::getExpr(void) const {
	return dynamic_cast<expr*>(getChild("expr"));
}

exprArg::operator std::string() const {
	return *getExpr();
}

std::string exprArg::getTypeDescr(void) const {
	return "Send argument variable (E_ARG)";
}

astNode* exprArg::deepCopy(void) const {
	exprArg* copy = new exprArg(*this);
	copy->copyChildren(*this);
	return copy;
}

/****************************************************************
 * **************************************************************
 * *************************************************************/

exprArgList::exprArgList(exprArg *node, exprArgList *list, int lineNb)
	: astNode(astNode::E_ARGLIST, lineNb)
{
	assert(node);
	assert(list);
	addChild("arg", node);
	addChild("arg_list", list);
}

exprArgList::exprArgList(exprArg *node, int lineNb)
	: astNode(astNode::E_ARGLIST, lineNb)
{
	assert(node);
	addChild("arg", node);
}

void exprArgList::setArg(exprArg* node) {
	eraseChild("arg", node);
}

void exprArgList::setArgList(exprArgList* list) {
	eraseChild("arg_list", list);
}

exprArg* exprArgList::getExprArg(void) const {
	return dynamic_cast<exprArg*>(getChild("arg"));
}

exprArgList* exprArgList::getArgList(void) const {
	return dynamic_cast<exprArgList*>(getChild("arg_list"));
}

unsigned int exprArgList::getSize(void) const {
	return 1 + (getArgList()? getArgList()->getSize() : 0);
}

exprArgList::operator std::string() const {
	assert(getExprArg());
	return std::string(*getExprArg()) + (getArgList() ? ", " + std::string(*getArgList()) : "");
}

std::string exprArgList::getTypeDescr(void) const {
	return "Argument list (E_ARGLIST)";
}

astNode* exprArgList::deepCopy(void) const {
	exprArgList* copy = new exprArgList(*this);
	copy->copyChildren(*this);
	return copy;
}
