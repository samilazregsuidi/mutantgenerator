#ifndef VAR_EXPR_H
#define VAR_EXPR_H

#include <iostream>

#include "expr.hpp"

class varSymNode;
class variantSymNode;

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

	exprVarRefName(const std::string& symName, varSymNode *sym, int lineNb);

	void setIndex(expr* index);

	expr* getIndex(void) const;

	varSymNode* resolve(symTable *global, symTable* subField = nullptr);

	varSymNode* getSymbol(void) const;

	std::string getName(void) const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	expr* deepCopy(void) const override;

protected:
	std::string symName;
	varSymNode* sym;
};

//E_VARREF,			// child[0] = E_VARREF_NAME, child[1] = E_VARREF (subfield, or NULL)

class exprVarRef : public expr
{
public:
	exprVarRef(int lineNb, exprVarRefName *varRefName, exprVarRef *subfieldsVar);

	void setVarRefName(exprVarRefName* varRefName);

	exprVarRefName* getVarRefName(void) const;

	void setSubField(exprVarRef* subField);

	varSymNode* resolve(symTable *global, symTable* subField = nullptr) const;

	bool hasSubField(void) const;

	const exprVarRef *getSubField(void) const;

	const exprVarRefName *getField(void) const;

	varSymNode* getFinalSymbol(void) const;

	varSymNode* getFirstSymbol(void) const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	unsigned int assignMutables(const Mask& mask, unsigned int id) override;

	std::vector<astNode*> getMutations(void) const override;

	symbol::Type getExprType(void) const override;

	bool castToExprType(symbol::Type type) const override;

	expr* deepCopy(void) const override;

};

//E_EXPR_VAR,			// child[0] = E_VARREF
class exprVar : public expr
{
public:
	exprVar(exprVarRef *varRef, int lineNb);

	const exprVarRef *getVarRef(void) const;

	const exprVarRefName *getVarRefName(void) const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	symbol::Type getExprType(void) const override;

	bool castToExprType(symbol::Type type) const override;

	varSymNode* getFinalSymbol(void) const;

	varSymNode* getFirstSymbol(void) const;

	expr* deepCopy(void) const override;

protected:
	exprVar(astNode::Type type, exprVarRef *varRef, int lineNb);
};

//E_EXPR_PROJ_VAR,			// child[0] = E_VARREF, child[1] = E_VARREF
class exprProjVar : public exprVar
{
public:
	exprProjVar(exprVarRef *varRef, exprVarRef* variant, int lineNb);

	const exprVarRef *getProjVarRef(void) const;

	const exprVarRefName *getProjVarRefName(void) const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	variantSymNode* getVariantSymbol(void) const;

	expr* deepCopy(void) const override;
};

#endif
