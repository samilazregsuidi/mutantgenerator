#ifndef ARG_EXPR_H
#define ARG_EXPR_H

#include "expr.hpp"

class exprRArg : public astNode
{
protected:
	exprRArg(Type type, int lineNb)
		: astNode(type, lineNb)
	{}
};

//E_RARG_VAR,		// child[0] = E_VARREF
class exprRArgVar : public exprRArg
{
public:
	exprRArgVar(exprVarRef *varRef, int lineNb);

	void setVarRef(exprVarRef* varRef);

	exprVarRef* getVarRef(void) const;
	
	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	astNode* deepCopy(void) const override;
};

//E_RARG_EVAL,	// child[0] = E_EXPR_*
class exprRArgEval : public exprRArg
{
public:
	exprRArgEval(expr *toEval, int lineNb);

	void setToEval(expr* toEval);

	expr* getToEval(void) const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	astNode* deepCopy(void) const override;
};

//E_RARG_CONST,	// iVal = the constant
class exprRArgConst : public exprRArg
{
public:
	exprRArgConst(int constant, int lineNb);

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	int getCstValue(void) const;

	astNode* deepCopy(void) const override;

private:
	int constant;
};

//E_RARGLIST,			// child[0] = E_EXPR_* or E_RARG_VAR or E_RARG_EVAL or E_RARG_CONST,
// child[1] = E_ARGLIST (next argument, or NULL)
class exprRArgList : public astNode
{
public:
	exprRArgList(exprRArg *node, exprRArgList *list, int lineNb);

	exprRArgList(exprRArg *node, int lineNb);

	void setRArg(exprRArg* node);

	void setRArgList(exprRArgList* list);

	exprRArg* getExprRArg(void) const;

	exprRArgList* getRArgList(void) const;

	unsigned int getSize(void) const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	astNode* deepCopy(void) const override;
};

//E_ARG,		// child[0] = E_EXPR_
class exprArg : public astNode
{
public:
	exprArg(expr *expr, int lineNb);

	void setExpr(expr* expr);

	expr* getExpr(void) const;
	
	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	astNode* deepCopy(void) const override;
};

//E_ARGLIST,			// child[0] = E_EXPR_* or E_RARG_VAR or E_RARG_EVAL or E_RARG_CONST,
// child[1] = E_ARGLIST (next argument, or NULL)
class exprArgList : public astNode {
public:
	exprArgList(exprArg *node, exprArgList *list, int lineNb);

	exprArgList(exprArg *node, int lineNb);

	void setArg(exprArg* node);

	void setArgList(exprArgList* list);

	exprArg* getExprArg(void) const;

	exprArgList* getArgList(void) const;

	unsigned int getSize(void) const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	astNode* deepCopy(void) const override;
};

#endif