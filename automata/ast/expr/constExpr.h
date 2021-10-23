#ifndef CONST_EXPR_H
#define CONST_EXPR_H

#include "expr.h"

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

	operator std::string() const override {
		return std::to_string(constant);
	}

	std::string getTypeDescr(void) const override {
		return "Constant (E_EXPR_CONST)";
	}

	symbol::Type getExprType(void) const {
		return symbol::T_INT;
	}

	std::vector<expr*> getMutations(void) const override ;

	expr* deepCopy(void) const override {
		exprConst* copy = new exprConst(*this);
		return copy;
	}

private:
	int constant;
};

//E_EXPR_TRUE,		// iVal = 1
class exprTrue : public expr
{
public:
	exprTrue(int lineNb)
		: expr(astNode::E_EXPR_TRUE, lineNb)
	{
	}

	operator std::string() const override {
		return "true";
	}

	std::string getTypeDescr(void) const override {
		return "True (E_EXPR_TRUE)";
	}

	symbol::Type getExprType(void) const {
		return symbol::T_BOOL;
	}

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprTrue* copy = new exprTrue(*this);
		return copy;
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

	operator std::string() const override {
		return "false";
	}

	std::string getTypeDescr(void) const override {
		return "False (E_EXPR_FALSE)";
	}

	symbol::Type getExprType(void) const {
		return symbol::T_BOOL;
	}

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprFalse* copy = new exprFalse(*this);
		return copy;
	}
	
};

#endif