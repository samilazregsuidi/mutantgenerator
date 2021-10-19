#ifndef VAR_EXPR_H
#define VAR_EXPR_H

#include "expr.h"

//E_VARREF_NAME,		// child[0] = E_EXPR_* (index into the array, or NULL), sVal = the variable/field name
//The processing step resolves all symbol names in expressions.  After this was done:
//- If the symbol denotes a variable, then symTab is the node in the symbol table of that variable;
//- If the symbol denotes an mtype, then symTab is NULL, and iVal >= 0 is the mtype value.
//- If the symbol denotes a special variable, then iVal < 0 and is one of MVAR_*

class exprVarRefName : public expr
{
public:
	exprVarRefName(const std::string& symName, int lineNb);

	exprVarRefName(const std::string& symName, expr *index, int lineNb);

	exprVarRefName(const std::string& symName, symbol *sym, int lineNb);

	~exprVarRefName() override;

	void resolve(symTable *global);

	void resolve(symTable *global, symTable* subField);

	symbol *symbolLookUpRight(void) const {
		return sym;
	}

	symbol *symbolLookUpLeft(void) const {
		return sym;
	}

	symbol* getSymbol(void) const {
		return sym;
	}

	std::string getName(void) const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override {
		return "Variable or field name (E_VARREF_NAME)";
	}

	unsigned int assignMutables(const Mask& mask, unsigned int id = 0) override {
		if(mask.isPresent(type)){
			id = (index? index->assignMutables(mask, id) : id);
			mId = ++id;
		}
		return id;
	}

	std::list<expr*> getMutations(void) const;
	
private:
	std::string symName;
	expr* index;
	symbol* sym; 
};

//E_VARREF,			// child[0] = E_VARREF_NAME, child[1] = E_VARREF (subfield, or NULL)
class exprVarRef : public expr
{
public:
	exprVarRef(int lineNb, exprVarRefName *symRef, exprVarRef *subfieldsVar);

	~exprVarRef() override;

	void resolve(symTable *global, symTable* subField = nullptr);

	bool hasSubField(void) const
	{
		return subfieldsVar != nullptr;
	}

	const exprVarRef *getSubField(void) const
	{
		return subfieldsVar;
	}

	const exprVarRefName *getField() const {
		return varRefName;
	}

	operator std::string() const override {
		return std::string(*varRefName) + (subfieldsVar ? "." + std::string(*subfieldsVar) : "");
	}

	std::string getTypeDescr(void) const override {
		return "Variable reference (E_VARREF)";
	}

	unsigned int assignMutables(const Mask& mask, unsigned int id = 0) override {
		if(mask.isPresent(type)) {
			id = varRefName->assignMutables(mask, id);
			id = (subfieldsVar? subfieldsVar->assignMutables(mask, id) : id);
		}
		return id;
	}

private:
	exprVarRefName *varRefName;
	exprVarRef *subfieldsVar;
};

//E_EXPR_VAR,			// child[0] = E_VARREF
class exprVar : public expr
{
public:
	exprVar(exprVarRef *varRef, int lineNb);

	~exprVar() override;

	const exprVarRef *getVarRef(void) const {
		return varRef;
	}

	const exprVarRefName *getVarRefName(void) const {
		return getVarRef()->getField();
	}

	operator std::string() const override {
		return *varRef;
	}

	std::string getTypeDescr(void) const override {
		return "Variable reference wrapper (E_EXPR_VAR)";
	}

	unsigned int assignMutables(const Mask& mask, unsigned int id = 0) override {
		if(mask.isPresent(type))
			id = varRef->assignMutables(mask, id);
		return id;
	}

private:
	exprVarRef* varRef;
};

#endif