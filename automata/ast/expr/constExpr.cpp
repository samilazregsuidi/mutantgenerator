#include "constExpr.h"

std::vector<expr*> exprConst::getMutations(void) const {
    
    std::vector<expr*> res;
    if(!exceed_limits(- 1))
        res.push_back(new exprConst(constant - 1, lineNb));
    if(!exceed_limits(+ 1))
        res.push_back(new exprConst(constant + 1, lineNb));

    return res;
}

std::vector<expr*> exprTrue::getMutations(void) const {
    return { new exprFalse(lineNb) };
}

std::vector<expr*> exprFalse::getMutations(void) const {
    return { new exprTrue(lineNb) };
}