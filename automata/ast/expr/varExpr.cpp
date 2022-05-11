#include <assert.h>
#include <string>
#include <iostream>
#include <cstdlib>

#include "varExpr.hpp"
#include "constExpr.hpp"

#include "symTable.hpp"
#include "varSymNode.hpp"
#include "utypeSymNode.hpp"
#include "tdefSymNode.hpp"
#include "mtypedefSymNode.hpp"

exprVarRefName::exprVarRefName(const std::string& symName, int lineNb)
	: expr(astNode::E_VARREF_NAME, lineNb)
	, symName(symName)
	, sym(nullptr)
{
}

exprVarRefName::exprVarRefName(const std::string& symName, expr *index, int lineNb)
	: expr(astNode::E_VARREF_NAME, lineNb)
	, symName(symName)
	, sym(nullptr)
{
	assert(index);
	addChild("index", index);
}

exprVarRefName::exprVarRefName(const std::string& symName, symbol *sym, int lineNb)
	: expr(astNode::E_VARREF_NAME, lineNb)
	, symName(symName)
	, sym(sym)
{
}

std::string exprVarRefName::getName(void) const {
	assert(!sym || (symName == sym->getName()));
	return symName;
}

void exprVarRefName::setIndex(expr* index) {
	eraseChild("index", index);
}

exprVarRefName::operator std::string() const {
	return symName + (getIndex() ? "[" + std::string(*getIndex()) + "]" : "");
}

std::string exprVarRefName::getTypeDescr(void) const {
	return "Variable or field name (E_VARREF_NAME)";
}

symbol* exprVarRefName::exprVarRefName::getSymbol(void) const {
	return sym;
}

expr* exprVarRefName::getIndex(void) const {
	return dynamic_cast<expr*>(getChild("index"));
}

symbol* exprVarRefName::resolve(symTable *global, symTable *subField) {

	if (subField)
		sym = subField->lookup(symName);
	else if (global) {
		do {
			sym = global->lookup(symName);
			global = global->prevSymTab();
		} while(!sym && global);
	} 
	
	if(!sym) {
		std::cout<< "unknown symbol : "<< symName << " at line "<<lineNb<<"\n";
		//assert(false);
	}

	return sym;
}

symbol::Type exprVarRefName::getExprType(void) const {
	return sym->getType();
}

expr* exprVarRefName::deepCopy(void) const {
	exprVarRefName* copy = new exprVarRefName(*this);
	copy->copyChildren(*this);
	return copy;
}

/*******************************************************************************************************************/

exprVarRef::exprVarRef(int lineNb, exprVarRefName *symRef, exprVarRef *subfieldsVar = nullptr)
	: expr(astNode::E_VARREF, lineNb)
{
	assert(symRef);
	//assert(subfieldsVar);
	addChild("field", symRef);
	addChild("sub_field", subfieldsVar);
}

void exprVarRef::setVarRefName(exprVarRefName* varRefName) {
	eraseChild("field", varRefName);
}

exprVarRefName* exprVarRef::getVarRefName(void) const {
	return dynamic_cast<exprVarRefName*>(getChild("field"));
}

void exprVarRef::setSubField(exprVarRef* subField) {
	eraseChild("sub_field", subField);
}

bool exprVarRef::hasSubField(void) const {
	return getSubField() != nullptr;
}

const exprVarRef *exprVarRef::getSubField(void) const {
	return dynamic_cast<exprVarRef*>(getChild("sub_field"));
}

const exprVarRefName *exprVarRef::getField() const {
	return dynamic_cast<exprVarRefName*>(getChild("field"));;
}

symbol* exprVarRef::getFinalSymbol(void) const {
	return getSubField()? getSubField()->getFinalSymbol() : getField()->getSymbol();
}

symbol* exprVarRef::getFirstSymbol(void) const {
	return getField()->getSymbol();
}

exprVarRef::operator std::string() const {
	auto varRefName = getVarRefName();
	auto subfieldsVar = getSubField();
	assert(getVarRefName() /*&& getSubField()*/);
	return std::string(*varRefName) + (subfieldsVar ? "." + std::string(*subfieldsVar) : "");
}

unsigned int exprVarRef::assignMutables(const Mask& mask, unsigned int id) {
	if(mask.isPresent(type) && hasMutations()) 
		mId = ++id;
	return id;
}


std::string exprVarRef::getTypeDescr(void) const {
	return "Variable reference (E_VARREF)";
}

symbol* exprVarRef::resolve(symTable *global, symTable* subField) const {

	auto varRefName = getVarRefName();
	auto sym = varRefName->resolve(global, subField);

	//assert(sym);
	// Resolve subfields, but with the symbol table of the type
	if (sym && getSubField()) {
		auto uSymbol = dynamic_cast<utypeSymNode*>(sym);
		assert(uSymbol->getUType());
		getSubField()->resolve(global, uSymbol->getUType()->getSymTable());
	}

	return sym;
}

symbol::Type exprVarRef::getExprType(void) const {
	if(!getVarRefName()->getSymbol())
		return symbol::T_NA;
	return getSubField()? getSubField()->getExprType() : getVarRefName()->getExprType();
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

std::vector<astNode*> exprVarRef::getMutations(void) const {
	auto sym = static_cast<varSymNode*>(getFinalSymbol());
	
	//std::cout << "expr var ref name : " << getVarRefName()->getName() << "\n";

	if(!sym || (!sym->getInitExpr() && sym->getMask() & symbol::WRITE_ACCESS))
		return std::vector<astNode*>();

	auto symList = getVarRefName()->getSymbol()->getSymTable()->getSymbols(getFinalSymbol());
	symList.erase(getVarRefName()->getSymbol());
	std::vector<astNode*> mutations;
	for(symbol* s: symList) {
		
		varSymNode* sCast = static_cast<varSymNode*>(s);
		//CAST BUG
		//varSymNode* sCast = dynamic_cast<varSymNode*>(s);
		//TODO : actual fix
		//assert(sCast);
		
		if(sCast) {
			if(sCast->getBound() > 1)
				for(unsigned int i = 0; i < sCast->getBound(); i++) {
					exprVarRefName* symRef = new exprVarRefName(s->getName(), s, lineNb);
					exprVarRef* newVar = new exprVarRef(lineNb, symRef);
					symRef->setIndex(new exprConst(i, lineNb));
					mutations.push_back(newVar);
				}
			else
				mutations.push_back(new exprVarRef(lineNb, new exprVarRefName(s->getName(), s, lineNb)));
		}
	}
	return mutations;
}

expr* exprVarRef::deepCopy(void) const {
	exprVarRef* copy = new exprVarRef(*this);
	copy->copyChildren(*this);
	return copy;
}

/**********************************************************************************************************/

exprVar::exprVar(exprVarRef *varRef, int lineNb)
		: expr(astNode::E_EXPR_VAR, lineNb)
{
	assert(varRef);
	addChild("var_ref", varRef);
}

const exprVarRef *exprVar::getVarRef(void) const {
	return dynamic_cast<exprVarRef*>(getChild("var_ref"));
}

const exprVarRefName *exprVar::getVarRefName(void) const {
	return dynamic_cast<exprVarRef*>(getChild("var_ref"))->getVarRefName();
}

exprVar::operator std::string() const {
	return *dynamic_cast<exprVarRef*>(getChild("var_ref"));
}

std::string exprVar::getTypeDescr(void) const {
	return "Variable reference wrapper (E_EXPR_VAR)";
}

symbol::Type exprVar::getExprType(void) const {
	return getVarRef()->getExprType();
}

bool exprVar::castToExprType(symbol::Type type) const {
	return getVarRef()->castToExprType(type);
}

symbol* exprVar::getFinalSymbol(void) const {
	return getVarRef()->getFinalSymbol();
}

symbol* exprVar::getFirstSymbol(void) const {
	return getVarRef()->getFirstSymbol();
}

expr* exprVar::deepCopy(void) const {
	exprVar* copy = new exprVar(*this);
	copy->copyChildren(*this);
	return copy;
}