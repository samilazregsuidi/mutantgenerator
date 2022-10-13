#include "binaryExpr.hpp"

/****************************************************************
 * **************************************************************
 * *************************************************************/

exprBinary::exprBinary(Type type, expr* left, expr* right, int lineNb)
		: expr(type, lineNb)
{
    assert(left);
    assert(right);
    addChild("left_expr", left);
    addChild("right_expr", right);
}

void exprBinary::setLeftExpr(expr* left) {
    eraseChild("left_expr", left);
}

void exprBinary::setRightExpr(expr* right) {
    eraseChild("right_expr", right);
}

expr* exprBinary::getLeftExpr(void) const {
    return dynamic_cast<expr*>(getChild("left_expr"));
}

expr* exprBinary::getRightExpr(void) const {
    return dynamic_cast<expr*>(getChild("right_expr"));
}

symbol::Type exprBinary::getExprType(void) const {
    return expr::getExprType(getLeftExpr(), getRightExpr());
}

unsigned int exprBinary::assignMutables(const Mask& mask, unsigned int id) {
    if(mask.isPresent(type)) {
        id = getLeftExpr()->assignMutables(mask, id);
        mId = ++id;//operator Id;
        id = getRightExpr()->assignMutables(mask, id);
    }
    return id; 
}

/****************************************************************
 * **************************************************************
 * *************************************************************/

std::vector<astNode*> exprPlus::getMutations(void) const {
    
    return { 
        new exprMinus(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb), 
        new exprTimes(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprDiv(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprMod(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        };

}

std::vector<astNode*> exprMinus::getMutations(void) const {
    
    return { 
        new exprPlus(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprTimes(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprDiv(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprMod(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        };
}

std::vector<astNode*> exprTimes::getMutations(void) const {
    
    return { 
        new exprPlus(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprMinus(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprDiv(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprMod(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        };
}

std::vector<astNode*> exprDiv::getMutations(void) const {
    
    return { 
        new exprPlus(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb), 
        new exprMinus(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprTimes(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprMod(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        };
}

std::vector<astNode*> exprMod::getMutations(void) const {
    
    return { 
        new exprPlus(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb), 
        new exprMinus(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprTimes(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprDiv(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        };
}

std::vector<astNode*> exprGT::getMutations(void) const {
    
    return {
        //new exprGT(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprLT(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb), 
        new exprGE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprLE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprEQ(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprNE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        };
}

std::vector<astNode*> exprLT::getMutations(void) const {
    
    return { 
        new exprGT(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        //new exprLT(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb), 
        new exprGE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprLE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprEQ(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprNE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        };
}

std::vector<astNode*> exprGE::getMutations(void) const {
    
    return { 
        new exprLT(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb), 
        new exprGT(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        //new exprGE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprLE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprEQ(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprNE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        };
}

std::vector<astNode*> exprLE::getMutations(void) const {
    
    return { 
        new exprLT(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb), 
        new exprGT(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprGE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        //new exprLE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprEQ(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprNE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        };
}

std::vector<astNode*> exprEQ::getMutations(void) const {
    
    symbol::Type type = getExprType();

    if(type != symbol::T_BOOL && type != symbol::T_MTYPE)

        return { 
            new exprLT(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb), 
            new exprGT(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
            new exprGE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
            new exprLE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
            //new exprEQ(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
            new exprNE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
            };

    else

        return { 
            //new exprEQ(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
            new exprNE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        };
}

std::vector<astNode*> exprNE::getMutations(void) const {
    
    symbol::Type type = getExprType();

    if(type != symbol::T_BOOL && type != symbol::T_MTYPE)
    
        return { 
            new exprLT(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
            new exprGT(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
            new exprGE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
            new exprLE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
            new exprEQ(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
            //new exprNE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
            };

    else

        return { 
            new exprEQ(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
            //new exprNE(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
            };

    
}

std::vector<astNode*> exprAnd::getMutations(void) const {
    
    return { 
        //new exprAnd(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb), 
        new exprOr(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        };
}

std::vector<astNode*> exprOr::getMutations(void) const {
    
    return { 
        new exprAnd(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        //new exprOr(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        };
}

std::vector<astNode*> exprBitwAnd::getMutations(void) const {
    
    return { 
        //new exprBitwAnd(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb), 
        new exprBitwOr(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprBitwXor(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb), 
        new exprLShift(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprRShift(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        };
}

std::vector<astNode*> exprBitwOr::getMutations(void) const {
    
    return { 
        new exprBitwAnd(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        //new exprBitwOr(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprBitwXor(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb), 
        new exprLShift(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprRShift(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        };
}

std::vector<astNode*> exprBitwXor::getMutations(void) const {
    
    return { 
        new exprBitwAnd(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb), 
        new exprBitwOr(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        //new exprBitwXor(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb), 
        new exprLShift(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprRShift(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        };
}

std::vector<astNode*> exprLShift::getMutations(void) const {
    
    return { 
        new exprBitwAnd(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb), 
        new exprBitwOr(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprBitwXor(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb), 
        //new exprLShift(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprRShift(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        };
}

std::vector<astNode*> exprRShift::getMutations(void) const {
    
    return { 
        new exprBitwAnd(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb), 
        new exprBitwOr(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb),
        new exprBitwXor(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb), 
        new exprLShift(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        //new exprRShift(dynamic_cast<expr*>(getLeftExpr()->deepCopy()), dynamic_cast<expr*>(getRightExpr()->deepCopy()), lineNb)
        };
}