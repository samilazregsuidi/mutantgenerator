#ifndef EXPR_H
#define EXPR_H

#include <vector>
#include <memory>

#include "astNode.hpp"

class exprVarRef;
class exprArgList;

class expr : public astNode
{
protected:
	expr(Type type, int lineNb);

public:
	virtual symbol::Type getExprType(void) const;

	void setExprType(symbol::Type exprType);

	virtual bool castToExprType(symbol::Type type) const;

	static symbol::Type getExprType(expr* left, expr* right);

	void acceptVisitor(ASTConstVisitor* visitor) const override;

	void acceptVisitor(ASTVisitor* visitor) override;

	int acceptVisitor(ASTConstVisitorInt* visitor) const override;

	int acceptVisitor(ASTVisitorInt* visitor) override;
	
protected:
	symbol::Type exprType;
};

//E_EXPR_COND,		// child[0] = E_EXPR_* (the condition), child[1] = E_EXPR_* (then), child[2] = E_EXPR_* (else)
class exprCond : public expr
{
public:
	exprCond(expr *pcond, expr *pthen, expr *pelsE, int lineNb);

	void setCond(expr* cond);

	void setThen(expr* then);

	void setElse(expr* elsE);

	expr* getCond(void) const;

	expr* getThen(void) const;

	expr* getElse(void) const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	symbol::Type getExprType(void) const override;

	expr* deepCopy(void) const override;
};

class procSymNode;

//E_EXPR_RUN,			// child[0] = E_ARGLIST, sVal = the procType name, and after processing: symTab = node in symbol table that represents the proctype
class exprRun : public expr
{
public:
	exprRun(const std::string& procName, exprArgList *argList, exprVarRef *card, int lineNb);

	exprRun(const std::string& procName, exprArgList *argList, int lineNb);

	void setCard(exprVarRef* card);

	exprVarRef* getCard(void) const;

	void setArgList(exprArgList* argList);

	exprArgList* getArgList(void) const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	symbol::Type getExprType(void) const override;

	expr* deepCopy(void) const override;

private:
	std::string procName;
	procSymNode* procSym;
};

//E_EXPR_TIMEOUT,	// iVal = 0
class exprTimeout : public expr
{
public:
	exprTimeout(int lineNb);

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	symbol::Type getExprType(void) const override;

	expr* deepCopy(void) const override;
};

//E_EXPR_SKIP,		// iVal = 1
class exprSkip : public expr
{
public:
	exprSkip(int lineNb);

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	symbol::Type getExprType(void) const override;

	expr* deepCopy(void) const override;
};

#endif
