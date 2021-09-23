#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "astNode.h"

class exprVarRef;

class expr : public astNode
{
protected:
	expr(Type type, int lineNb)
		: astNode(type, lineNb)
	{}
};

//E_EXPR_COND,		// child[0] = E_EXPR_* (the condition), child[1] = E_EXPR_* (then), child[2] = E_EXPR_* (else)
class exprCond : public expr
{
public:
	exprCond(expr *cond, expr *then, expr *elsE)
		: expr(astNode::E_EXPR_COND, lineNb)
	{
		this->cond = cond;
		this->then = then;
		this->elsE = elsE;
	}

	operator std::string() const
	{
		return "( " + std::string(*cond) + " ? " + std::string(*then) + " : " + std::string(*elsE) + " )";
	}

	std::string getTypeDescr(void)
	{
		return "Conditional expression (E_EXPR_COND)";
	}

private:
	expr* cond;
	expr* then;
	expr* elsE;
};

class exprRArg : public expr
{
protected:
	exprRArg(Type type, int lineNb)
		: expr(type, lineNb)
	{}
};

//E_RARG_VAR,		// child[0] = E_VARREF
class exprRArgVar : public exprRArg
{
public:
	exprRArgVar(exprVarRef *child0, int lineNb);

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
		return "Receive argument variable (E_RARG_VAR)";
	}

private:
	exprVarRef* varRef;
};

//E_RARG_EVAL,	// child[0] = E_EXPR_*
class exprRArgEval : public exprRArg
{
public:
	exprRArgEval(expr *toEval, int lineNb)
		: exprRArg(astNode::E_RARG_EVAL, lineNb)
	{
		this->toEval = toEval;
	}

	operator std::string() const
	{
		return "eval( " + std::string(*toEval) + ")";
	}

	std::string getTypeDescr(void)
	{
		return "Receive argument eval (E_RARG_EVAL)";
	}

private:
	expr* toEval;
};

//E_RARG_CONST,	// iVal = the constant
class exprRArgConst : public exprRArg
{
public:
	exprRArgConst(int constant, int lineNb)
		: exprRArg(astNode::E_RARG_EVAL, lineNb)
	{
		this->constant = constant;
	}

	operator std::string() const
	{
		return std::to_string(constant);
	}

	std::string getTypeDescr(void)
	{
		return "Receive argument constant (E_RARG_CONST)";
	}

private:
	int constant;
};

//E_ARGLIST,			// child[0] = E_EXPR_* or E_RARG_VAR or E_RARG_EVAL or E_RARG_CONST,
// child[1] = E_ARGLIST (next argument, or NULL)
class exprArgList : public expr
{
public:
	exprArgList(exprRArg *node, exprArgList *list, int lineNb)
		: expr(astNode::E_ARGLIST, lineNb)
	{
		this->node = node;
		this->list = list;
	}

	exprArgList(exprRArg *child0, int lineNb)
		: expr(astNode::E_ARGLIST, lineNb)
	{
		this->node = node;
		this->list = nullptr;
	}

	operator std::string() const
	{
		return std::string(*node) + (list ? "," + std::string(*list) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Argument list (E_ARGLIST)";
	}

private:
	exprRArg* node;
	exprArgList* list;
};

//E_EXPR_RUN,			// child[0] = E_ARGLIST, sVal = the procType name, and after processing: symTab = node in symbol table that represents the proctype
class exprRun : public expr
{
public:
	exprRun(const std::string& procName, exprArgList *list, exprVarRef *card, int lineNb);

	exprRun(const std::string& procName, exprArgList *list, int lineNb);

	void resolveVariables(symTabNode *global, const mTypeList *mTypes, symTabNode *local, symTabNode *subField = nullptr);

	operator std::string() const
	{
		return "run " + procName + (card ? " [" + std::string(*card) + "]" : "") + "( " + std::string(*list) + " ) ";
	}

	std::string getTypeDescr(void)
	{
		return "Run (E_EXPR_RUN)";
	}
private:
	std::string procName;
	exprArgList* list;
	exprVarRef* card;
};

//E_EXPR_CONST,		// iVal = the value
class exprConst : public expr
{
public:
	exprConst(int constant, int lineNb)
		: expr(astNode::E_EXPR_CONST, lineNb)
	{
		this->constant = constant;
	}

	operator std::string() const
	{
		return std::to_string(constant);
	}

	std::string getTypeDescr(void)
	{
		return "Constant (E_EXPR_CONST)";
	}

private:
	int constant;
};

//E_EXPR_TIMEOUT,	// iVal = 0
class exprTimeout : public expr
{
public:
	exprTimeout(int lineNb)
		: expr(astNode::E_EXPR_TIMEOUT, lineNb)
	{
	}

	operator std::string() const
	{
		return "timeout";
	}

	std::string getTypeDescr(void)
	{
		return "Timeout (E_EXPR_TIMEOUT)";
	}
};

//E_EXPR_SKIP,		// iVal = 1
class exprSkip : public expr
{
public:
	exprSkip(int lineNb)
		: expr(astNode::E_EXPR_SKIP, lineNb)
	{
	}

	operator std::string() const
	{
		return "skip";
	}

	std::string getTypeDescr(void)
	{
		return "Skip (E_EXPR_SKIP)";
	}
};

//E_EXPR_TRUE,		// iVal = 1
class exprTrue : public expr
{
public:
	exprTrue(int lineNb)
		: expr(astNode::E_EXPR_TRUE, lineNb)
	{
	}

	operator std::string() const
	{
		return "true";
	}

	std::string getTypeDescr(void)
	{
		return "True (E_EXPR_TRUE)";
	}
};

//E_EXPR_FALSE,		// iVal = 0
class exprFalse : public expr
{
public:
	exprFalse(int lineNb)
		: expr(astNode::E_EXPR_FALSE, lineNb)
	{
	}

	operator std::string() const
	{
		return "false";
	}

	std::string getTypeDescr(void)
	{
		return "False (E_EXPR_FALSE)";
	}
};

#endif