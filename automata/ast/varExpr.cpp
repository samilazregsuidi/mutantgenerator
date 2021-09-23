#include <assert.h>
#include <string>

#include "varExpr.h"
#include "symTabNode.h"
#include "varSymNode.h"
#include "utypeSymNode.h"
#include "tdefSymNode.h"
#include "mTypeList.h"

std::string exprVarRefName::getName(void) const {
	return sym->getName();
}

exprVarRefName::operator std::string() const {
	return sym->getName() + (index ? "[" + std::string(*index) + "]" : "");
}

void exprVarRefName::resolveVariables(symTabNode *global, const mTypeList *mTypes, symTabNode *local, symTabNode *subField) {

	if (subField)
		sym = subField->lookupInSymTab(symName);
	else if (local)
		sym = local->lookupInSymTab(symName);
	else
		sym = global->lookupInSymTab(symName);

	if (sym) {
		if(index) 
			index->resolveVariables(global, mTypes, local, subField);
	} else {
		// First check if its a magic variable
		int mvar = 0;
		if (mvar == 0 && symName == MVARID_LAST)
			mvar = MVAR_LAST;
		if (mvar == 0 && symName == MVARID_NRPR)
			mvar = MVAR_NRPR;
		if (mvar == 0 && symName == MVARID_PID)
			mvar = MVAR_PID;
		if (mvar == 0 && symName == MVARID_SCRATCH)
			mvar = MVAR_SCRATCH;

		if (mvar < 0)
		{
			// MVar IDs are negative!
			//iVal = mvar;
			assert(false);
		}
		else
		{
			// Then check if it's an mtype
			//int value = mTypes? mTypes->getMTypeValue(symName) : -1;
			//assert(!(value == -1 && !iVal));
			//iVal = value;
			assert(false);
		}
	}
}

void exprVarRef::resolveVariables(symTabNode *global, const mTypeList *mTypes, symTabNode *local, symTabNode *subField) {

	varRef->resolveVariables(global, mTypes, local, subField);
	auto symbol = varRef->getSymbol();

	if (symbol) {
		// Resolve subfields, but with the symbol table of the type
		if (subfieldsVar) {
			auto uSymbol = static_cast<utypeSymNode*>(symbol);
			assert(uSymbol->getUType());
			subfieldsVar->resolveVariables(global, mTypes, local, uSymbol->getUType()->getChild());
		}
	}
	else
		assert(!subfieldsVar);
}