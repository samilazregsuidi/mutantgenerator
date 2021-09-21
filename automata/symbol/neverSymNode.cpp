#include "neverSymNode.h"
#include "symTabVisitor.h"
#include "expression.h"

void neverSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitNever(this);
}

unsigned int neverSymNode::processVariables(symTabNode *global, const mTypeList *mTypes, unsigned int iOffset, bool isGlobal) {
	childFsm->resolveVariables(global, mTypes);
	if (init && init->getType() == astNode::E_EXPR_COUNT)
		init->resolveVariables(global, mTypes);
	//childFsm->orderAcceptTransitions();
	memSize = childFsm->processVariables(global, mTypes, 0, 0);
	return !next ? iOffset : next->processVariables(global, mTypes, iOffset, isGlobal);
}