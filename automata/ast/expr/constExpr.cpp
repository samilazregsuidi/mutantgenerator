#include "constExpr.h"

std::vector<expr*> exprConst::getMutations(void) const {
    return { 
        new exprConst(constant - 1, lineNb), 
        new exprConst(constant + 1, lineNb) 
    };
}

std::vector<expr*> exprTrue::getMutations(void) const {
    return { new exprFalse(lineNb) };
}

std::vector<expr*> exprFalse::getMutations(void) const {
    return { new exprTrue(lineNb) };
}