#ifndef UNARY_EXPR_H
#define UNARY_EXPR_H

#include "expr.h"
#include "varExpr.h"

class exprUnary : public expr
{
protected:
	exprUnary(Type type, expr* expression, int lineNb)
		: expr(type, lineNb)
	{
		this->expression = expression;
	}

	~exprUnary() override {
		delete expression;
	}

	void resolveVariables(symTabNode* globalSymTab) override {
		expression->resolveVariables(globalSymTab);
	}

protected:
	expr* expression;
};

//E_EXPR_PAR,			// child[0] = E_EXPR_*
class exprPar : public exprUnary
{
public:
	exprPar(expr *expression, int lineNb)
		: exprUnary(astNode::E_EXPR_PAR, expression, lineNb)
	{
	}

	operator std::string() const
	{
		return "( " + std::string(*expression) + " )";
	}

	std::string getTypeDescr(void) const
	{
		return "Parentheses (E_EXPR_PAR)";
	}
};

//E_EXPR_COUNT,		// child[0] = E_EXPR_*
class exprCount : public exprUnary
{
public:
	exprCount(expr *expression, int lineNb)
		: exprUnary(astNode::E_EXPR_COUNT, expression, lineNb)
	{
	}

	operator std::string() const
	{
		return "count( " + std::string(*expression) + " ) ";
	}

	std::string getTypeDescr(void) const
	{
		return "Clones count (E_EXPR_COUNT)";
	}
};

//E_EXPR_UMIN,		// child[0] = E_EXPR_*
class exprUMin : public exprUnary
{
public:
	exprUMin(expr *expression, int lineNb)
		: exprUnary(astNode::E_EXPR_UMIN, expression, lineNb)
	{
	}

	operator std::string() const
	{
		return "-" + std::string(*expression);
	}

	std::string getTypeDescr(void) const
	{
		return "Unary minus (E_EXPR_UMIN)";
	}
};

//E_EXPR_NEG,			// child[0] = E_EXPR_*
class exprNeg : public exprUnary
{
public:
	exprNeg(expr *expression, int lineNb)
		: exprUnary(astNode::E_EXPR_NEG, expression, lineNb)
	{
	}

	operator std::string() const
	{
		return "!" + std::string(*expression);
	}

	std::string getTypeDescr(void) const
	{
		return "Negation (E_EXPR_NEG)";
	}
};

//E_EXPR_BITWNEG,		// child[0] = E_EXPR_*
class exprBitwNeg : public exprUnary
{
public:
	exprBitwNeg(expr *expression, int lineNb)
		: exprUnary(astNode::E_EXPR_BITWNEG, expression, lineNb)
	{
	}

	operator std::string() const
	{
		return " ~ " + std::string(*expression);
	}

	std::string getTypeDescr(void) const
	{
		return "Bitwise neg (E_EXPR_BITWNEG)";
	}
};

//E_EXPR_LEN,			// child[0] = E_VARREF
class exprLen : public exprUnary
{
public:
	exprLen(exprVarRef *expression, int lineNb)
		: exprUnary(astNode::E_EXPR_LEN, expression, lineNb)
	{
	}

	operator std::string() const
	{
		return "len( " + std::string(*expression) + " )";
	}

	std::string getTypeDescr(void) const
	{
		return "Length (E_EXPR_LEN)";
	}
};

//E_EXPR_FULL,		// child[0] = E_VARREF
class exprFull : public exprUnary
{
public:
	exprFull(exprVarRef *expression, int lineNb)
		: exprUnary(astNode::E_EXPR_FULL, expression, lineNb)
	{
	}

	operator std::string() const
	{
		return "full( " + std::string(*expression) + ")";
	}

	std::string getTypeDescr(void) const
	{
		return "Full probe (E_EXPR_FULL)";
	}
};

//E_EXPR_NFULL,		// child[0] = E_VARREF
class exprNFull : public exprUnary
{
public:
	exprNFull(exprVarRef *expression, int lineNb)
		: exprUnary(astNode::E_EXPR_NFULL, expression, lineNb)
	{
	}

	operator std::string() const
	{
		return "nfull( " + std::string(*expression) + ")";
	}

	std::string getTypeDescr(void) const
	{
		return "Not full probe (E_EXPR_NFULL)";
	}
};

//E_EXPR_EMPTY,		// child[0] = E_VARREF
class exprEmpty : public exprUnary
{
public:
	exprEmpty(exprVarRef *expression, int lineNb)
		: exprUnary(astNode::E_EXPR_EMPTY, expression, lineNb)
	{
	}

	operator std::string() const
	{
		return "empty( " + std::string(*expression) + ")";
	}

	std::string getTypeDescr(void) const
	{
		return "Empty probe (E_EXPR_EMPTY)";
	}
};

//E_EXPR_NEMPTY,		// child[0] = E_VARREF
class exprNEmpty : public exprUnary
{
public:
	exprNEmpty(exprVarRef *expression, int lineNb)
		: exprUnary(astNode::E_EXPR_NEMPTY, expression, lineNb)
	{
	}

	operator std::string() const
	{
		return "nempty( " + std::string(*expression) + ")";
	}

	std::string getTypeDescr(void) const
	{
		return "Not empty probe (E_EXPR_NEMPTY)";
	}
};

#endif