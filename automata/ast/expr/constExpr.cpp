#include "constExpr.h"

std::vector<std::unique_ptr<expr>> exprConst::getMutations(void) const {
    
    std::vector<std::unique_ptr<expr>> res;
    if(!exceed_limits(- 1))
        res.push_back(std::unique_ptr<exprConst>(new exprConst(constant - 1, lineNb)));
    if(!exceed_limits(+ 1))
        res.push_back(std::unique_ptr<exprConst>(new exprConst(constant + 1, lineNb)));

    return res;
}

std::vector<std::unique_ptr<expr>> exprTrue::getMutations(void) const {
    return { std::unique_ptr<exprFalse>(new exprFalse(lineNb)) };
}

std::vector<std::unique_ptr<expr>> exprFalse::getMutations(void) const {
    return { std::unique_ptr<exprTrue>(new exprTrue(lineNb)) };
}