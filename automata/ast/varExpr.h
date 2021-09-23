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

	exprVarRefName(const std::string& symName, symTabNode *sym, int lineNb);

	~exprVarRefName() override;

	void resolveVariables(symTabNode *global, const mTypeList *mTypes, varSymNode *local, symTabNode *subField = nullptr);

	symTabNode *symbolLookUpRight(void) const {
		return sym;
	}

	symTabNode *symbolLookUpLeft(void) const {
		return sym;
	}

	symTabNode* getSymbol(void) const {
		return sym;
	}

	std::string getName(void) const;

	operator std::string() const;

	std::string getTypeDescr(void)
	{
		return "Variable or field name (E_VARREF_NAME)";
	}
private:
	std::string symName;
	expr* index;
	symTabNode* sym; 
};

//E_VARREF,			// child[0] = E_VARREF_NAME, child[1] = E_VARREF (subfield, or NULL)
class exprVarRef : public expr
{
public:
	exprVarRef(int lineNb, exprVarRefName *symRef, exprVarRef *subfieldsVar);

	~exprVarRef() override;

	void resolveVariables(symTabNode *global, const mTypeList *mTypes, varSymNode *local, symTabNode *subField = nullptr) override;

	symTabNode *symbolLookUpRight() const
	{
		return subfieldsVar ? subfieldsVar->symbolLookUpRight() : varRefName->symbolLookUpRight();
	}

	symTabNode *symbolLookUpLeft(void) const
	{
		return varRefName->symbolLookUpLeft();
	}

	bool hasSubField(void) const
	{
		return subfieldsVar != nullptr;
	}

	const exprVarRef *getSubField(void) const
	{
		return subfieldsVar;
	}

	const exprVarRefName *getField() const
	{
		return varRefName;
	}

	operator std::string() const
	{
		return std::string(*varRefName) + (subfieldsVar ? "." + std::string(*subfieldsVar) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Variable reference (E_VARREF)";
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

	void resolveVariables(symTabNode *global, const mTypeList *mTypes, varSymNode *local, symTabNode *subField = nullptr) override;

	const exprVarRef *getVarRef(void) const
	{
		return varRef;
	}

	const exprVarRefName *getVarRefName(void) const
	{
		return getVarRef()->getField();
	}

	/*bool varOccurs(const std::string &var, const symTabNode *globalSymTab, const symTabNode *processSymTab, const mTypeList *mtypes) const
	{
		return child[0]->var2String(globalSymTab, processSymTab, mtypes) == var;
	}*/

	symTabNode *symbolLookUpRight(void) const
	{
		return varRef->symbolLookUpRight();
	}

	symTabNode *symbolLookUpLeft(void) const
	{
		return varRef->symbolLookUpLeft();
	}

	operator std::string() const
	{
		return *varRef;
	}

	std::string getTypeDescr(void)
	{
		return "Variable reference wrapper (E_EXPR_VAR)";
	}

private:
	exprVarRef* varRef;
};

#endif