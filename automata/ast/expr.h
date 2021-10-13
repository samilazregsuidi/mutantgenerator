#ifndef EXPR_H
#define EXPR_H

#include "astNode.h"

class exprVarRef;
class exprArgList;

class expr : public astNode
{
protected:
	expr(Type type, int lineNb)
		: astNode(type, lineNb)
	{}

public:
	/*void resolveVariables(symTable* globalSymTab) override {
		globalSymTab = globalSymTab;
	}*/
};

//E_EXPR_COND,		// child[0] = E_EXPR_* (the condition), child[1] = E_EXPR_* (then), child[2] = E_EXPR_* (else)
class exprCond : public expr
{
public:
	exprCond(expr *cond, expr *then, expr *elsE, int lineNb)
		: expr(astNode::E_EXPR_COND, lineNb)
	{
		this->cond = cond;
		this->then = then;
		this->elsE = elsE;

		this->cond->setParent(this);
		this->then->setParent(this);
		this->elsE->setParent(this);
	}

	operator std::string() const override
	{
		return "(" + std::string(*cond) + "? " + std::string(*then) + ": " + std::string(*elsE) + ")";
	}

	std::string getTypeDescr(void) const override
	{
		return "Conditional expression (E_EXPR_COND)";
	}

private:
	expr* cond;
	expr* then;
	expr* elsE;
};

class procSymNode;

//E_EXPR_RUN,			// child[0] = E_ARGLIST, sVal = the procType name, and after processing: symTab = node in symbol table that represents the proctype
class exprRun : public expr
{
public:
	exprRun(const std::string& procName, exprArgList *argList, exprVarRef *card, int lineNb);

	exprRun(const std::string& procName, exprArgList *argList, int lineNb);

	//void resolveVariables(symTable *global = nullptr) override;

	operator std::string() const override;

	std::string getTypeDescr(void) const override
	{
		return "Run (E_EXPR_RUN)";
	}

private:
	std::string procName;
	procSymNode* procSym;
	exprArgList* argList;
	exprVarRef* card;
};

//E_EXPR_TIMEOUT,	// iVal = 0
class exprTimeout : public expr
{
public:
	exprTimeout(int lineNb)
		: expr(astNode::E_EXPR_TIMEOUT, lineNb)
	{
	}

	operator std::string() const override
	{
		return "timeout";
	}

	std::string getTypeDescr(void) const override
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

	operator std::string() const override
	{
		return "skip";
	}

	std::string getTypeDescr(void) const override
	{
		return "Skip (E_EXPR_SKIP)";
	}
};

#endif