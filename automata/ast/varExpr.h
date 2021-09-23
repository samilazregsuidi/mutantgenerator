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
	exprVarRefName(const std::string& symName, int lineNb)
		: expr(astNode::E_VARREF_NAME, 0, nullptr, nullptr, nullptr, lineNb)
	{
		this->symName = symName;
	}

	exprVarRefName(const std::string& symName, expr *child0, int lineNb)
		: expr(astNode::E_VARREF_NAME, 0, child0, nullptr, nullptr, lineNb)
	{
		this->symName = symName;
	}

	exprVarRefName(const std::string& symName, symTabNode *symTabChild, int lineNb)
		: expr(astNode::E_VARREF_NAME, 0, nullptr, nullptr, nullptr, lineNb, nullptr, symTabChild)
	{
		this->symName = symName;
	}

	void resolveVariables(symTabNode *global, const mTypeList *mTypes, symTabNode *local, symTabNode *subField = nullptr);

	symTabNode *symbolLookUpRight(void) const {
		return symTab;
	}

	symTabNode *symbolLookUpLeft(void) const {
		return symTab;
	}

	std::string getName(void) const;

	operator std::string() const;

	std::string getTypeDescr(void)
	{
		return "Variable or field name (E_VARREF_NAME)";
	}
private:
	std::string symName;
};

//E_VARREF,			// child[0] = E_VARREF_NAME, child[1] = E_VARREF (subfield, or NULL)
class exprVarRef : public expr
{
public:
	exprVarRef(exprVarRefName *child0, exprVarRef *child1, int lineNb)
		: expr(astNode::E_VARREF, 0, child0, child1, nullptr, lineNb)
	{
	}

	exprVarRef(exprVarRefName *child0, int lineNb)
		: expr(astNode::E_VARREF, 0, child0, nullptr, nullptr, lineNb)
	{
	}

	void resolveVariables(symTabNode *global, const mTypeList *mTypes, symTabNode *local, symTabNode *subField = nullptr);

	symTabNode *symbolLookUpRight() const
	{
		return child[1] ? child[1]->symbolLookUpRight() : child[0]->symbolLookUpRight();
	}

	symTabNode *symbolLookUpLeft(void) const
	{
		return child[0]->symbolLookUpLeft();
	}

	const exprVarRefName *getExprVarRefName() const
	{
		return static_cast<exprVarRefName *>(child[0]);
	}

	bool hasSubField(void) const
	{
		return child[1] != nullptr;
	}

	const exprVarRef *getSubField(void) const
	{
		return static_cast<exprVarRef *>(child[1]);
	}

	const exprVarRef *getField() const
	{
		return static_cast<exprVarRef *>(child[1]);
	}

	operator std::string() const
	{
		return std::string(*child[0]) + (child[1] ? "." + std::string(*child[1]) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Variable reference (E_VARREF)";
	}
};

//E_EXPR_VAR,			// child[0] = E_VARREF
class exprVar : public expr
{
public:
	exprVar(exprVarRef *child0, int lineNb)
		: expr(astNode::E_EXPR_VAR, 0, child0, nullptr, nullptr, lineNb)
	{
	}

	const exprVarRef *getExprVarRef(void) const
	{
		return static_cast<exprVarRef *>(child[0]);
	}

	const exprVarRefName *getExprVarRefName(void) const
	{
		return getExprVarRef()->getExprVarRefName();
	}

	/*bool varOccurs(const std::string &var, const symTabNode *globalSymTab, const symTabNode *processSymTab, const mTypeList *mtypes) const
	{
		return child[0]->var2String(globalSymTab, processSymTab, mtypes) == var;
	}*/

	symTabNode *symbolLookUpRight(void) const
	{
		return child[0]->symbolLookUpRight();
	}

	symTabNode *symbolLookUpLeft(void) const
	{
		return child[0]->symbolLookUpLeft();
	}

	operator std::string() const
	{
		return *child[0];
	}

	std::string getTypeDescr(void)
	{
		return "Variable reference wrapper (E_EXPR_VAR)";
	}
};

#endif