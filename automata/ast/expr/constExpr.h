#ifndef CONST_EXPR_H
#define CONST_EXPR_H

#include <limits>

#include "expr.h"

//E_EXPR_CONST,		// iVal = the value
class exprConst : public expr
{
public:
	exprConst(int constant, int lineNb)
		: expr(astNode::E_EXPR_CONST, lineNb)
		, constant(constant)
	{
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

	symbol::Type getExprType(void) const override {
		return exprType == symbol::T_NA? symbol::T_INT : exprType;
	}

	bool castToExprType(symbol::Type type) const {
		switch(type) {
			case symbol::T_BIT:
				if(constant != 1 && constant != 0)
					break;
				return true;
			case symbol::T_BYTE:
				if(constant < static_cast<int>(std::numeric_limits<char>::min()) 
				|| constant > static_cast<int>(std::numeric_limits<char>::max()))
					break;
				return true;
			case symbol::T_SHORT:
				if(constant < static_cast<int>(std::numeric_limits<short>::min())
				|| constant > static_cast<int>(std::numeric_limits<short>::max()))
					break;
				return true;
			case symbol::T_UNSGN:
				//if(constant < std::numeric_limits<unsigned int>::min() 
				//|| constant > std::numeric_limits<unsigned int>::max())
					break;
				return true;
			case symbol::T_INT:
				if(constant < std::numeric_limits<int>::min() 
				|| constant > std::numeric_limits<int>::max())
					break;
				return true;
			default:
				assert(false);
				break;
		}
		return false;
	}

	std::vector<std::unique_ptr<expr>> getMutations(void) const override ;

	expr* deepCopy(void) const override {
		exprConst* copy = new exprConst(*this);
		return copy;
	}

private:
	bool exceed_limits(int add) const {
		return (constant + add > symbol::getUpperBound(getExprType()) 
		|| constant + add < symbol::getLowerBound(getExprType()));
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

	std::vector<std::unique_ptr<expr>> getMutations(void) const override;

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

	std::vector<std::unique_ptr<expr>> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprFalse* copy = new exprFalse(*this);
		return copy;
	}
	
};

#endif