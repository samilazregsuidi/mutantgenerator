#include "binaryExpr.h"

std::vector<expr*> exprPlus::getMutations(void) const {
    
    return { 
        new exprMinus(left, right, lineNb), 
        new exprTimes(left, right, lineNb),
        new exprDiv(left, right, lineNb),
        new exprMod(left, right, lineNb)
        };

}

std::vector<expr*> exprMinus::getMutations(void) const {
    return { 
        new exprPlus(left, right, lineNb), 
        new exprTimes(left, right, lineNb),
        new exprDiv(left, right, lineNb),
        new exprMod(left, right, lineNb)
        };
}

std::vector<expr*> exprTimes::getMutations(void) const {
    return { 
        new exprPlus(left, right, lineNb), 
        new exprMinus(left, right, lineNb),
        new exprDiv(left, right, lineNb),
        new exprMod(left, right, lineNb)
        };
}

std::vector<expr*> exprDiv::getMutations(void) const {
    return { 
        new exprPlus(left, right, lineNb), 
        new exprMinus(left, right, lineNb),
        new exprTimes(left, right, lineNb),
        new exprMod(left, right, lineNb)
        };
}

std::vector<expr*> exprMod::getMutations(void) const {
    return { 
        new exprPlus(left, right, lineNb), 
        new exprMinus(left, right, lineNb),
        new exprTimes(left, right, lineNb),
        new exprDiv(left, right, lineNb)
        };
}

std::vector<expr*> exprGT::getMutations(void) const {
    
    return {
        //new exprGT(left, right, lineNb),
        new exprLT(left, right, lineNb), 
        new exprGE(left, right, lineNb),
        new exprLE(left, right, lineNb),
        new exprEQ(left, right, lineNb),
        new exprNE(left, right, lineNb)
        };
}

std::vector<expr*> exprLT::getMutations(void) const {
    return { 
        new exprGT(left, right, lineNb),
        //new exprLT(left, right, lineNb), 
        new exprGE(left, right, lineNb),
        new exprLE(left, right, lineNb),
        new exprEQ(left, right, lineNb),
        new exprNE(left, right, lineNb)
        };
}

std::vector<expr*> exprGE::getMutations(void) const {
    return { 
        new exprLT(left, right, lineNb), 
        new exprGT(left, right, lineNb),
        //new exprGE(left, right, lineNb),
        new exprLE(left, right, lineNb),
        new exprEQ(left, right, lineNb),
        new exprNE(left, right, lineNb)
        };
}

std::vector<expr*> exprLE::getMutations(void) const {
    return { 
        new exprLT(left, right, lineNb), 
        new exprGT(left, right, lineNb),
        new exprGE(left, right, lineNb),
        //new exprLE(left, right, lineNb),
        new exprEQ(left, right, lineNb),
        new exprNE(left, right, lineNb)
        };
}

std::vector<expr*> exprEQ::getMutations(void) const {
    
    symbol::Type type = getExprType();

    if(type != symbol::T_BOOL && type != symbol::T_MTYPE)

        return { 
            new exprLT(left, right, lineNb), 
            new exprGT(left, right, lineNb),
            new exprGE(left, right, lineNb),
            new exprLE(left, right, lineNb),
            //new exprEQ(left, right, lineNb),
            new exprNE(left, right, lineNb)
            };

    else

        return { 
            //new exprEQ(left, right, lineNb)
            new exprNE(left, right, lineNb)
        };
}

std::vector<expr*> exprNE::getMutations(void) const {
    
    symbol::Type type = getExprType();

    if(type != symbol::T_BOOL && type != symbol::T_MTYPE)
    
        return { 
            new exprLT(left, right, lineNb), 
            new exprGT(left, right, lineNb),
            new exprGE(left, right, lineNb),
            new exprLE(left, right, lineNb),
            new exprEQ(left, right, lineNb)
            //new exprNE(left, right, lineNb)
            };

    else

        return { 
            new exprEQ(left, right, lineNb)
            //new exprNE(left, right, lineNb)
            };

    
}

std::vector<expr*> exprAnd::getMutations(void) const {
    return { 
        //new exprAnd(left, right, lineNb), 
        new exprOr(left, right, lineNb)
        };
}

std::vector<expr*> exprOr::getMutations(void) const {
    return { 
        new exprAnd(left, right, lineNb), 
        //new exprOr(left, right, lineNb)
        };
}

std::vector<expr*> exprBitwAnd::getMutations(void) const {
    return { 
        //new exprBitwAnd(left, right, lineNb), 
        new exprBitwOr(left, right, lineNb),
        new exprBitwXor(left, right, lineNb), 
        new exprLShift(left, right, lineNb),
        new exprRShift(left, right, lineNb)
        };
}

std::vector<expr*> exprBitwOr::getMutations(void) const {
    return { 
        new exprBitwAnd(left, right, lineNb), 
        //new exprBitwOr(left, right, lineNb),
        new exprBitwXor(left, right, lineNb), 
        new exprLShift(left, right, lineNb),
        new exprRShift(left, right, lineNb)
        };
}

std::vector<expr*> exprBitwXor::getMutations(void) const {
    return { 
        new exprBitwAnd(left, right, lineNb), 
        new exprBitwOr(left, right, lineNb),
        //new exprBitwXor(left, right, lineNb), 
        new exprLShift(left, right, lineNb),
        new exprRShift(left, right, lineNb)
        };
}

std::vector<expr*> exprLShift::getMutations(void) const {
    return { 
        new exprBitwAnd(left, right, lineNb), 
        new exprBitwOr(left, right, lineNb),
        new exprBitwXor(left, right, lineNb), 
        //new exprLShift(left, right, lineNb),
        new exprRShift(left, right, lineNb)
        };
}

std::vector<expr*> exprRShift::getMutations(void) const {
    return { 
        new exprBitwAnd(left, right, lineNb), 
        new exprBitwOr(left, right, lineNb),
        new exprBitwXor(left, right, lineNb), 
        new exprLShift(left, right, lineNb)
        //new exprRShift(left, right, lineNb)
        };
}