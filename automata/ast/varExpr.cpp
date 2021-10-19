#include <assert.h>
#include <string>
#include <iostream>
#include <cstdlib>

#include "varExpr.h"
#include "constExpr.h"

#include "symTable.h"
#include "varSymNode.h"
#include "utypeSymNode.h"
#include "tdefSymNode.h"
#include "mtypedefSymNode.h"

exprVarRefName::exprVarRefName(const std::string& symName, int lineNb)
	: expr(astNode::E_VARREF_NAME, lineNb)
{
	this->symName = symName;
	this->sym = nullptr;
	this->index = nullptr;
}

exprVarRefName::exprVarRefName(const std::string& symName, expr *index, int lineNb)
	: expr(astNode::E_VARREF_NAME, lineNb)
{
	this->symName = symName;
	this->sym = nullptr;
	this->index = index;
}

exprVarRefName::exprVarRefName(const std::string& symName, symbol *sym, int lineNb)
	: expr(astNode::E_VARREF_NAME, lineNb)
{
	this->symName = symName;
	this->index = nullptr;
	this->sym = sym;
}

exprVarRefName::~exprVarRefName() {
	//delete sym;
	delete index;
}

std::string exprVarRefName::getName(void) const {
	return sym->getName();
}

exprVarRefName::operator std::string() const {
	return sym->getName() + (index ? "[" + std::string(*index) + "]" : "");
}

void exprVarRefName::resolve(symTable *global, symTable *subField) {

	if (subField)
		sym = subField->lookup(symName);
	else if (global) {
		do {
			sym = global->lookup(symName);
			global = global->prevSymTab();
		} while(!sym && global);
	} 
	
	if(!sym) {
		std::cout<< "unknown symbol : "<< symName << "\n";
		assert(false);
	}

/*to add in global sym table 
	if (!sym) {
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
	}*/
}

symbol::Type exprVarRefName::getExprType(void) const {
	return sym->getType();
}

/*******************************************************************************************************************/

exprVarRef::exprVarRef(int lineNb, exprVarRefName *symRef, exprVarRef *subfieldsVar = nullptr)
	: expr(astNode::E_VARREF, lineNb)
{
	this->varRefName = symRef;
	this->subfieldsVar = subfieldsVar;
}

exprVarRef::~exprVarRef() {
	delete varRefName;
	delete subfieldsVar;
}

void exprVarRef::resolve(symTable *global, symTable* subField) {

	varRefName->resolve(global, subField);

	auto sym = varRefName->getSymbol();
	assert(sym);
	// Resolve subfields, but with the symbol table of the type
	if (subfieldsVar) {
		auto uSymbol = static_cast<utypeSymNode*>(sym);
		assert(uSymbol->getUType());
		subfieldsVar->resolve(global, uSymbol->getUType()->getSymTable());
	}
}

symbol::Type exprVarRef::getExprType(void) const {
	return subfieldsVar? subfieldsVar->getExprType() : varRefName->getExprType();
}

std::vector<expr*> exprVarRef::getMutations(void) const {
	std::list<symbol*> symList = varRefName->getSymbol()->getSymTable()->getSymbols(getExprType());
	symList.remove(varRefName->getSymbol());
	std::vector<expr*> mutations;
	for(auto& s: symList) {
		auto sCast = static_cast<varSymNode*>(s);
		assert(sCast);
		
		if(sCast->getBound() > 1)
			for(int i = 0; i < sCast->getBound(); i++) {
				exprVarRefName* newVar = new exprVarRefName(s->getName(), s, lineNb);
				newVar->setIndex(new exprConst(i, lineNb));
				mutations.push_back(newVar);
			}
		else
			mutations.push_back(new exprVarRefName(s->getName(), s, lineNb));
	}
	return mutations;
}

/**********************************************************************************************************/

exprVar::exprVar(exprVarRef *varRef, int lineNb)
		: expr(astNode::E_EXPR_VAR, lineNb)
{
	this->varRef = varRef;
}

exprVar::~exprVar() {
	delete varRef;
}