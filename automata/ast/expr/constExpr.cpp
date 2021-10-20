#include "constExpr.h"

std::vector<expr*> exprTrue::getMutations(void) const {
    return { new exprFalse(lineNb) };
}

std::vector<expr*> exprFalse::getMutations(void) const {
    return { new exprTrue(lineNb) };
}