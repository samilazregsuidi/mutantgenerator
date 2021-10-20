/*#include "unaryExpr.h"
#include "constExpr.h"

expr* initial = new exprConst(3, 0);
expr* mutant = new exprConst(4, 0);

exprUnary* toMutate = new exprUMin(initial, 0);
expr* exprUnary::* ptr = &exprUnary::expression;

MutationImpl<exprUnary, expr> mutation(toMutate, ptr, mutant);*/