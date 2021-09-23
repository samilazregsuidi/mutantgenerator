#include <assert.h>
#include <string>

#include "varExpr.h"
#include "symTabNode.h"
#include "varSymNode.h"
#include "utypeSymNode.h"
#include "tdefSymNode.h"
#include "mTypeList.h"

std::string exprVarRefName::getName(void) const {
	return symTab->getName();
}

exprVarRefName::operator std::string() const {
	return symTab->getName() + (child[0] ? "[" + std::string(*child[0]) + "]" : "");
}

void exprVarRefName::resolveVariables(symTabNode *global, const mTypeList *mTypes, symTabNode *local, symTabNode *subField) {

	if (subField)
		symTab = subField->lookupInSymTab(symName);
	else if (local)
		symTab = local->lookupInSymTab(symName);
	else
		symTab = global->lookupInSymTab(symName);

	if (symTab) {
		if(child[0]) 
			child[0]->resolveVariables(global, mTypes, local, subField);
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
			iVal = mvar;
		}
		else
		{
			// Then check if it's an mtype
			int value = mTypes? mTypes->getMTypeValue(symName) : -1;
			assert(!(value == -1 && !iVal));
			iVal = value;
		}
	}
}

void exprVarRef::resolveVariables(symTabNode *global, const mTypeList *mTypes, symTabNode *local, symTabNode *subField) {

	child[0]->resolveVariables(global, mTypes, local, subField);
	auto symbol = child[0]->getSymbol();

	if (symbol) {
		// Resolve subfields, but with the symbol table of the type
		if (child[1]) {
			auto uSymbol = static_cast<utypeSymNode*>(symbol);
			assert(uSymbol->getUType());
			child[1]->resolveVariables(global, mTypes, local, uSymbol->getUType()->getChild());
		}
	}
	else
		assert(!child[1]);
}