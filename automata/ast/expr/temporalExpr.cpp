#include "unaryExpr.hpp"

/****************************************************************
 * **************************************************************
 * *************************************************************/

exprUnary::exprUnary(Type type, expr* mExpr, int lineNb)
    : expr(type, lineNb)
{
    assert(mExpr);
    addChild("expr", mExpr);
}

void exprUnary::setExpr(expr* mExpr) {
    eraseChild("expr", mExpr);
}

expr* exprUnary::getExpr(void) const {
    return dynamic_cast<expr*>(getChild("expr"));
}

symbol::Type exprUnary::getExprType(void) const {
    return getExpr()->getExprType();
}

/****************************************************************
 * **************************************************************
 * *************************************************************/

/****************************************************************
 * **************************************************************
 * *************************************************************/

unsigned int exprNeg::assignMutables(const Mask& mask, unsigned int id) {
	if(mask.isPresent(type)) {
		mId = ++id;
		for(auto c : children)
			id = c.second->assignMutables(mask, id);
	}
	return id;
}

std::vector<astNode*> exprNeg::getMutations(void) const {
    return { new exprPar(dynamic_cast<expr*>(getExpr()->deepCopy()), lineNb) };
}