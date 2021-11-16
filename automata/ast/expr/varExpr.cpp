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
	, symName(symName)
	, sym(nullptr)
	, index(nullptr)
{

}

exprVarRefName::exprVarRefName(const std::string& symName, expr *index, int lineNb)
	: expr(astNode::E_VARREF_NAME, lineNb)
	, symName(symName)
	, sym(nullptr)
	, index(nullptr)
{
	setIndex(index);
}

exprVarRefName::exprVarRefName(const std::string& symName, symbol *sym, int lineNb)
	: expr(astNode::E_VARREF_NAME, lineNb)
	, symName(symName)
	, sym(sym)
	, index(nullptr)
{

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
}

symbol::Type exprVarRefName::getExprType(void) const {
	return sym->getType();
}

expr* exprVarRefName::deepCopy(void) const {
	exprVarRefName* copy = new exprVarRefName(*this);
	copy->setIndex(index ? index->deepCopy() : nullptr);
	return copy;
}

/*******************************************************************************************************************/

exprVarRef::exprVarRef(int lineNb, exprVarRefName *symRef, exprVarRef *subfieldsVar = nullptr)
	: expr(astNode::E_VARREF, lineNb)
	, varRefName(nullptr)
	, subfieldsVar(nullptr)
{
	setVarRefName(symRef);
	setSubField(subfieldsVar);
}

void exprVarRef::resolve(symTable *global, symTable* subField) {

	varRefName->resolve(global, subField);

	auto sym = varRefName->getSymbol();
	assert(sym);
	// Resolve subfields, but with the symbol table of the type
	if (subfieldsVar) {
		auto uSymbol = dynamic_cast<utypeSymNode*>(sym);
		assert(uSymbol->getUType());
		subfieldsVar->resolve(global, uSymbol->getUType()->getSymTable());
	}
}

symbol::Type exprVarRef::getExprType(void) const {
	return subfieldsVar? subfieldsVar->getExprType() : varRefName->getExprType();
}

bool exprVarRef::castToExprType(symbol::Type type) const {
	auto exprType = getExprType();
	switch(exprType){
		case symbol::T_BIT:
		case symbol::T_BYTE:
		case symbol::T_SHORT:
		case symbol::T_INT:
		case symbol::T_UNSGN:
			if(type == symbol::T_BIT
			|| type == symbol::T_BYTE
			|| type == symbol::T_SHORT
			|| type == symbol::T_INT
			|| type == symbol::T_UNSGN)
				return true;
			return false;
		case symbol::T_BOOL:
			if(type == symbol::T_BOOL)
				return true;
			return false;
		default:
			break;
	}
	return false;
}

std::vector<expr*> exprVarRef::getMutations(void) const {
	std::list<symbol*> symList = varRefName->getSymbol()->getSymTable()->getSymbols(getExprType(), varRefName->getSymbol()->getMask());
	if(symList.size() > 1)
		symList.remove(varRefName->getSymbol());
	std::vector<expr*> mutations;
	for(auto& s: symList) {
		auto sCast = dynamic_cast<varSymNode*>(s);
		assert(sCast);
		
		if(sCast->getBound() > 1)
			for(int i = 0; i < sCast->getBound(); i++) {
				exprVarRefName* symRef = new exprVarRefName(s->getName(), s, lineNb);
				exprVarRef* newVar = new exprVarRef(lineNb, symRef);
				symRef->setIndex(new exprConst(i, lineNb));
				mutations.push_back(newVar);
			}
		else
			mutations.push_back(new exprVarRef(lineNb, new exprVarRefName(s->getName(), s, lineNb)));
	}
	return mutations;
}

expr* exprVarRef::deepCopy(void) const {
	exprVarRef* copy = new exprVarRef(*this);
	copy->setVarRefName(dynamic_cast<exprVarRefName*>(varRefName->deepCopy()));
	copy->setSubField(subfieldsVar? dynamic_cast<exprVarRef*>(subfieldsVar->deepCopy()) : nullptr);
	return copy;
}

/**********************************************************************************************************/

exprVar::exprVar(exprVarRef *varRef, int lineNb)
		: expr(astNode::E_EXPR_VAR, lineNb)
		, varRef(nullptr)
{
	setVarRef(varRef);
}

expr* exprVar::deepCopy(void) const {
	exprVar* copy = new exprVar(*this);
	copy->setVarRef(dynamic_cast<exprVarRef*>(varRef->deepCopy()));
	return copy;
}