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

	/*void resolveVariables(symTable* globalSymTab = nullptr) override {
		cond->resolveVariables(globalSymTab);
		then->resolveVariables(globalSymTab);
		elsE->resolveVariables(globalSymTab);
	}*/

	operator std::string() const override
	{
		return "(" + std::string(*cond) + "? " + std::string(*then) + ": " + std::string(*elsE) + ")";
	}

	std::string getTypeDescr(void) const override
	{
		return "Conditional expression (E_EXPR_COND)";
	}

	void accept(ASTVisitor* visitor) override;

	void accept(ASTConstVisitor* visitor) const override;

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
	exprRArgVar(exprVarRef *varRef, int lineNb);

	symbol *symbolLookUpRight(void) const;

	symbol *symbolLookUpLeft(void) const;

	//void resolveVariables(symTable* globalSymTab = nullptr) override;

	operator std::string() const override;

	std::string getTypeDescr(void) const override
	{
		return "Receive argument variable (E_RARG_VAR)";
	}

	void accept(ASTVisitor* visitor) override;

	void accept(ASTConstVisitor* visitor) const override;

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

		this->toEval->setParent(this);
	}

	/*void resolveVariables(symTable* globalSymTab = nullptr) override {
		toEval->resolveVariables(globalSymTab);
	}*/

	operator std::string() const override
	{
		return "eval(" + std::string(*toEval) + ")";
	}

	std::string getTypeDescr(void) const override
	{
		return "Receive argument eval (E_RARG_EVAL)";
	}

	void accept(ASTVisitor* visitor) override;

	void accept(ASTConstVisitor* visitor) const override;

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

	operator std::string() const override
	{
		return std::to_string(constant);
	}

	std::string getTypeDescr(void) const override
	{
		return "Receive argument constant (E_RARG_CONST)";
	}

	void accept(ASTVisitor* visitor) override;

	void accept(ASTConstVisitor* visitor) const override;

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

		this->node->setParent(this);
		this->list->setParent(this);
	}

	exprArgList(exprRArg *node, int lineNb)
		: expr(astNode::E_ARGLIST, lineNb)
	{
		this->node = node;
		this->list = nullptr;

		this->node->setParent(this);
	}

	/*void resolveVariables(symTable* globalSymTab = nullptr) override {
		node->resolveVariables(globalSymTab);
		list->resolveVariables(globalSymTab);
	}*/

	operator std::string() const override
	{
		return std::string(*node) + (list ? ", " + std::string(*list) : "");
	}

	std::string getTypeDescr(void) const override
	{
		return "Argument list (E_ARGLIST)";
	}

	void accept(ASTVisitor* visitor) override;

	void accept(ASTConstVisitor* visitor) const override;

private:
	exprRArg* node;
	exprArgList* list;
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

	void accept(ASTVisitor* visitor) override;

	void accept(ASTConstVisitor* visitor) const override;

private:
	std::string procName;
	procSymNode* procSym;
	exprArgList* argList;
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
	
	int getCstValue(void) const {
		return constant;
	}
	
	void setCstValue(int constant) {
		this->constant = constant;
	}

	operator std::string() const override
	{
		return std::to_string(constant);
	}

	std::string getTypeDescr(void) const override
	{
		return "Constant (E_EXPR_CONST)";
	}

	void accept(ASTVisitor* visitor) override;

	void accept(ASTConstVisitor* visitor) const override;

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

	operator std::string() const override
	{
		return "timeout";
	}

	std::string getTypeDescr(void) const override
	{
		return "Timeout (E_EXPR_TIMEOUT)";
	}

	void accept(ASTVisitor* visitor) override;

	void accept(ASTConstVisitor* visitor) const override;
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

	void accept(ASTVisitor* visitor) override;

	void accept(ASTConstVisitor* visitor) const override;
};

//E_EXPR_TRUE,		// iVal = 1
class exprTrue : public expr
{
public:
	exprTrue(int lineNb)
		: expr(astNode::E_EXPR_TRUE, lineNb)
	{
	}

	operator std::string() const override
	{
		return "true";
	}

	std::string getTypeDescr(void) const override
	{
		return "True (E_EXPR_TRUE)";
	}

	void accept(ASTVisitor* visitor) override;

	void accept(ASTConstVisitor* visitor) const override;
};

//E_EXPR_FALSE,		// iVal = 0
class exprFalse : public expr
{
public:
	exprFalse(int lineNb)
		: expr(astNode::E_EXPR_FALSE, lineNb)
	{
	}

	operator std::string() const override
	{
		return "false";
	}

	std::string getTypeDescr(void) const override
	{
		return "False (E_EXPR_FALSE)";
	}

	void accept(ASTVisitor* visitor) override;

	void accept(ASTConstVisitor* visitor) const override;
};

#endif