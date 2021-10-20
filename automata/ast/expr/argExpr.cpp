#include <assert.h>
#include <string>

#include "argExpr.h"
#include "varExpr.h"

exprRArgVar::exprRArgVar(exprVarRef *varRef, int lineNb)
	: exprRArg(astNode::E_RARG_VAR, lineNb)
{
	this->varRef = varRef;

	this->varRef->setParent(this);
}

exprRArgVar::operator std::string() const {
	return *varRef;
}

expr* exprRArgVar::deepCopy(void) const {
	exprRArgVar* copy = new exprRArgVar(*this);
	copy->varRef = static_cast<exprVarRef*>(varRef->deepCopy());
	return copy;
}