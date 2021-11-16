#include "binaryExpr.h"

std::vector<std::unique_ptr<expr>> exprPlus::getMutations(void) const {
    
    return { 
        std::make_unique<exprMinus>(left, right, lineNb), 
        std::make_unique<exprTimes>(left, right, lineNb),
        std::make_unique<exprDiv>(left, right, lineNb),
        std::make_unique<exprMod>(left, right, lineNb)
        };

}

std::vector<std::unique_ptr<expr>> exprMinus::getMutations(void) const {
    return { 
        std::make_unique<exprPlus>(new exprPlus(left, right, lineNb)), 
        std::make_unique<exprTimes>(new exprTimes(left, right, lineNb)),
        std::make_unique<exprDiv>(new exprDiv(left, right, lineNb)),
        std::make_unique<exprMod>(new exprMod(left, right, lineNb))
        };
}

std::vector<std::unique_ptr<expr>> exprTimes::getMutations(void) const {
    return { 
        std::make_unique<exprPlus>(new exprPlus(left, right, lineNb)), 
        std::make_unique<exprMinus>(new exprMinus(left, right, lineNb)),
        std::make_unique<exprDiv>(new exprDiv(left, right, lineNb)),
        std::make_unique<exprMod>(new exprMod(left, right, lineNb))
        };
}

std::vector<std::unique_ptr<expr>> exprDiv::getMutations(void) const {
    return { 
        std::make_unique<exprPlus>(new exprPlus(left, right, lineNb)), 
        std::make_unique<exprMinus>(new exprMinus(left, right, lineNb)),
        std::make_unique<exprTimes>(new exprTimes(left, right, lineNb)),
        std::make_unique<exprMod>(new exprMod(left, right, lineNb))
        };
}

std::vector<std::unique_ptr<expr>> exprMod::getMutations(void) const {
    return { 
        std::make_unique<exprPlus>(new exprPlus(left, right, lineNb)), 
        std::make_unique<exprMinus>(new exprMinus(left, right, lineNb)),
        std::make_unique<exprTimes>(new exprTimes(left, right, lineNb)),
        std::make_unique<exprDiv>(new exprDiv(left, right, lineNb))
        };
}

std::vector<std::unique_ptr<expr>> exprGT::getMutations(void) const {
    
    return {
        //new exprGT(left, right, lineNb),
        std::make_unique<exprLT>(new exprLT(left, right, lineNb)), 
        std::make_unique<exprGE>(new exprGE(left, right, lineNb)),
        std::make_unique<exprLE>(new exprLE(left, right, lineNb)),
        std::make_unique<exprEQ>(new exprEQ(left, right, lineNb)),
        std::make_unique<exprNE>(new exprNE(left, right, lineNb))
        };
}

std::vector<std::unique_ptr<expr>> exprLT::getMutations(void) const {
    return { 
        std::make_unique<exprGT>(new exprGT(left, right, lineNb)),
        //new exprLT(left, right, lineNb), 
        std::make_unique<exprGE>(new exprGE(left, right, lineNb)),
        std::make_unique<exprLE>(new exprLE(left, right, lineNb)),
        std::make_unique<exprEQ>(new exprEQ(left, right, lineNb)),
        std::make_unique<exprNE>(new exprNE(left, right, lineNb))
        };
}

std::vector<std::unique_ptr<expr>> exprGE::getMutations(void) const {
    return { 
        std::make_unique<exprLT>(new exprLT(left, right, lineNb)), 
        std::make_unique<exprGT>(new exprGT(left, right, lineNb)),
        //new exprGE(left, right, lineNb),
        std::make_unique<exprLE>(new exprLE(left, right, lineNb)),
        std::make_unique<exprEQ>(new exprEQ(left, right, lineNb)),
        std::make_unique<exprNE>(new exprNE(left, right, lineNb))
        };
}

std::vector<std::unique_ptr<expr>> exprLE::getMutations(void) const {
    return { 
        std::make_unique<exprLT>(new exprLT(left, right, lineNb)), 
        std::make_unique<exprGT>(new exprGT(left, right, lineNb)),
        std::make_unique<exprGE>(new exprGE(left, right, lineNb)),
        //new exprLE(left, right, lineNb),
        std::make_unique<exprEQ>(new exprEQ(left, right, lineNb)),
        std::make_unique<exprNE>(new exprNE(left, right, lineNb))
        };
}

std::vector<std::unique_ptr<expr>> exprEQ::getMutations(void) const {
    
    symbol::Type type = getExprType();

    if(type != symbol::T_BOOL && type != symbol::T_MTYPE)

        return { 
            std::make_unique<exprLT>(new exprLT(left, right, lineNb)), 
            std::make_unique<exprGT>(new exprGT(left, right, lineNb)),
            std::make_unique<exprGE>(new exprGE(left, right, lineNb)),
            std::make_unique<exprLE>(new exprLE(left, right, lineNb)),
            //new exprEQ(left, right, lineNb),
            std::make_unique<exprNE>(new exprNE(left, right, lineNb))
            };

    else

        return { 
            //new exprEQ(left, right, lineNb)
            std::make_unique<exprNE>(new exprNE(left, right, lineNb))
        };
}

std::vector<std::unique_ptr<expr>> exprNE::getMutations(void) const {
    
    symbol::Type type = getExprType();

    if(type != symbol::T_BOOL && type != symbol::T_MTYPE)
    
        return { 
            std::make_unique<exprLT>(new exprLT(left, right, lineNb)), 
            std::make_unique<exprGT>(new exprGT(left, right, lineNb)),
            std::make_unique<exprGE>(new exprGE(left, right, lineNb)),
            std::make_unique<exprLE>(new exprLE(left, right, lineNb)),
            std::make_unique<exprEQ>(new exprEQ(left, right, lineNb))
            //new exprNE(left, right, lineNb)
            };

    else

        return { 
            std::make_unique<exprEQ>(new exprEQ(left, right, lineNb))
            //new exprNE(left, right, lineNb)
            };

    
}

std::vector<std::unique_ptr<expr>> exprAnd::getMutations(void) const {
    return { 
        //new exprAnd(left, right, lineNb), 
        std::make_unique<exprOr>(new exprOr(left, right, lineNb))
        };
}

std::vector<std::unique_ptr<expr>> exprOr::getMutations(void) const {
    return { 
        std::make_unique<exprAnd>(new exprAnd(left, right, lineNb)) 
        //new exprOr(left, right, lineNb)
        };
}

std::vector<std::unique_ptr<expr>> exprBitwAnd::getMutations(void) const {
    return { 
        //new exprBitwAnd(left, right, lineNb), 
        std::make_unique<exprBitwOr>(new exprBitwOr(left, right, lineNb)),
        std::make_unique<exprBitwXor>(new exprBitwXor(left, right, lineNb)), 
        std::make_unique<exprLShift>(new exprLShift(left, right, lineNb)),
        std::make_unique<exprRShift>(new exprRShift(left, right, lineNb))
        };
}

std::vector<std::unique_ptr<expr>> exprBitwOr::getMutations(void) const {
    return { 
        std::make_unique<exprBitwAnd>(new exprBitwAnd(left, right, lineNb)), 
        //new exprBitwOr(left, right, lineNb),
        std::make_unique<exprBitwXor>(new exprBitwXor(left, right, lineNb)), 
        std::make_unique<exprLShift>(new exprLShift(left, right, lineNb)),
        std::make_unique<exprRShift>(new exprRShift(left, right, lineNb))
        };
}

std::vector<std::unique_ptr<expr>> exprBitwXor::getMutations(void) const {
    return { 
        std::make_unique<exprBitwAnd>(new exprBitwAnd(left, right, lineNb)), 
        std::make_unique<exprBitwOr>(new exprBitwOr(left, right, lineNb)),
        //new exprBitwXor(left, right, lineNb), 
        std::make_unique<exprLShift>(new exprLShift(left, right, lineNb)),
        std::make_unique<exprRShift>(new exprRShift(left, right, lineNb))
        };
}

std::vector<std::unique_ptr<expr>> exprLShift::getMutations(void) const {
    return { 
        std::make_unique<exprBitwAnd>(new exprBitwAnd(left, right, lineNb)), 
        std::make_unique<exprBitwOr>(new exprBitwOr(left, right, lineNb)),
        std::make_unique<exprBitwXor>(new exprBitwXor(left, right, lineNb)), 
        //new exprLShift(left, right, lineNb),
        std::make_unique<exprRShift>(new exprRShift(left, right, lineNb))
        };
}

std::vector<std::unique_ptr<expr>> exprRShift::getMutations(void) const {
    return { 
        std::make_unique<exprBitwAnd>(new exprBitwAnd(left, right, lineNb)), 
        std::make_unique<exprBitwOr>(new exprBitwOr(left, right, lineNb)),
        std::make_unique<exprBitwXor>(new exprBitwXor(left, right, lineNb)), 
        std::make_unique<exprLShift>(new exprLShift(left, right, lineNb))
        //new exprRShift(left, right, lineNb)
        };
}