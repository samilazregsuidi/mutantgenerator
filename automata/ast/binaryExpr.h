#ifndef BINARY_EXPR_H
#define BINARY_EXPR_H

#include "expr.h"

class exprBinary : public expr
{
protected:
	exprBinary(Type type, expr* left, expr* right, int lineNb)
		: expr(type, lineNb)
	{
		this->left = left;
		this->right = right;

		this->left->setParent(this);
		this->right->setParent(this);
	}

	~exprBinary() override {
		delete right;
		delete left;
	}


protected:
	expr* left;
	expr* right;
};

//E_EXPR_PLUS,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprPlus : public exprBinary
{
public:
	exprPlus(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_PLUS, left, right, lineNb)
	{
	}

	operator std::string() const override {
		return std::string(*left) + " + " + std::string(*right);
	}

	std::string getTypeDescr(void) const override {
		return "Plus (E_EXPR_PLUS)";
	}
};

//E_EXPR_MINUS,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprMinus : public exprBinary
{
public:
	exprMinus(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_MINUS, left, right, lineNb)
	{
	}

	operator std::string() const override
	{
		return std::string(*left) + " - " + std::string(*right);
	}

	std::string getTypeDescr(void) const override
	{
		return "Minus (E_EXPR_MINUS)";
	}
};

//E_EXPR_TIMES,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprTimes : public exprBinary
{
public:
	exprTimes(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_TIMES, left, right, lineNb)
	{
	}

	operator std::string() const override
	{
		return std::string(*left) + " * " + std::string(*right);
	}

	std::string getTypeDescr(void) const override
	{
		return "Times (E_EXPR_TIMES)";
	}
};

//E_EXPR_DIV,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprDiv : public exprBinary
{
public:
	exprDiv(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_DIV, left, right, lineNb)
	{
	}

	operator std::string() const override
	{
		return std::string(*left) + " / " + std::string(*right);
	}

	std::string getTypeDescr(void) const override
	{
		return "Divide (E_EXPR_DIV)";
	}
};

//E_EXPR_MOD,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprMod : public exprBinary
{
public:
	exprMod(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_MOD, left, right, lineNb)
	{
	}

	operator std::string() const override
	{
		return std::string(*left) + " % " + std::string(*right);
	}

	std::string getTypeDescr(void) const override
	{
		return "Modulo (E_EXPR_MOD)";
	}
};

//E_EXPR_GT,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprGT : public exprBinary
{
public:
	exprGT(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_GT, left, right, lineNb)
	{
	}

	operator std::string() const override
	{
		return std::string(*left) + " > " + std::string(*right);
	}

	std::string getTypeDescr(void) const override
	{
		return "Greater than (E_EXPR_GT)";
	}
};

//E_EXPR_LT,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprLT : public exprBinary
{
public:
	exprLT(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_LT, left, right, lineNb)
	{
	}

	operator std::string() const override
	{
		return std::string(*left) + " < " + std::string(*right);
	}

	std::string getTypeDescr(void) const override
	{
		return "Less than (E_EXPR_LT)";
	}
};

//E_EXPR_GE,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprGE : public exprBinary
{
public:
	exprGE(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_GE, left, right, lineNb)
	{
	}

	operator std::string() const override
	{
		return std::string(*left) + " >= " + std::string(*right);
	}

	std::string getTypeDescr(void) const override
	{
		return "Greater or equal than (E_EXPR_GE)";
	}
};

//E_EXPR_LE,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprLE : public exprBinary
{
public:
	exprLE(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_LE, left, right, lineNb)
	{
	}

	operator std::string() const override
	{
		return std::string(*left) + " <= " + std::string(*right);
	}

	std::string getTypeDescr(void) const override
	{
		return "Less or equal than (E_EXPR_LE)";
	}
};

//E_EXPR_EQ,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprEQ : public exprBinary
{
public:
	exprEQ(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_EQ, left, right, lineNb)
	{
	}

	operator std::string() const override
	{
		return std::string(*left) + " == " + std::string(*right);
	}

	std::string getTypeDescr(void) const override
	{
		return "Equal (E_EXPR_EQ)";
	}
};

//E_EXPR_NE,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprNE : public exprBinary
{
public:
	exprNE(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_NE, left, right, lineNb)
	{
	}

	operator std::string() const override
	{
		return std::string(*left) + " != " + std::string(*right);
	}

	std::string getTypeDescr(void) const override
	{
		return "Not equal (E_EXPR_NE)";
	}
};

//E_EXPR_AND,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprAnd : public exprBinary
{
public:
	exprAnd(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_AND, left, right, lineNb)
	{
	}

	operator std::string() const override
	{
		return std::string(*left) + " && " + std::string(*right);
	}

	std::string getTypeDescr(void) const override
	{
		return "Logical and (E_EXPR_AND)";
	}

	void mutate(void) {
		left->getMutations();
	}
};

//E_EXPR_OR,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprOr : public exprBinary
{
public:
	exprOr(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_OR, left, right, lineNb)
	{
	}

	operator std::string() const override
	{
		return std::string(*left) + " || " + std::string(*right);
	}

	std::string getTypeDescr(void) const override
	{
		return "Logical or (E_EXPR_OR)";
	}
};

//E_EXPR_BITWAND,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprBitwAnd : public exprBinary
{
public:
	exprBitwAnd(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_BITWAND, left, right, lineNb)
	{
	}

	operator std::string() const override
	{
		return std::string(*left) + " & " + std::string(*right);
	}

	std::string getTypeDescr(void) const override
	{
		return "Bitwise and (E_EXPR_BITWAND)";
	}
};

//E_EXPR_BITWOR,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprBitwOr : public exprBinary
{
public:
	exprBitwOr(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_BITWOR, left, right, lineNb)
	{
	}

	operator std::string() const override
	{
		return std::string(*left) + " | " + std::string(*right);
	}

	std::string getTypeDescr(void) const override
	{
		return "Bitwise or (E_EXPR_BITWOR)";
	}
};

//E_EXPR_BITWXOR,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprBitwXor : public exprBinary
{
public:
	exprBitwXor(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_BITWXOR, left, right, lineNb)
	{
	}

	operator std::string() const override
	{
		return std::string(*left) + " ^ " + std::string(*right);
	}

	std::string getTypeDescr(void) const override
	{
		return "Bitwise xor (E_EXPR_BITWXOR)";
	}
};

//E_EXPR_LSHIFT,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprLShift : public exprBinary
{
public:
	exprLShift(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_LSHIFT, left, right, lineNb)
	{
	}

	operator std::string() const override
	{
		return std::string(*left) + " << " + std::string(*right);
	}

	std::string getTypeDescr(void) const override
	{
		return "Left shift (E_EXPR_LSHIFT)";
	}
};

//E_EXPR_RSHIFT,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprRShift : public exprBinary
{
public:
	exprRShift(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_RSHIFT, left, right, lineNb)
	{
	}

	operator std::string() const override
	{
		return std::string(*left) + " >> " + std::string(*right);
	}

	std::string getTypeDescr(void) const override
	{
		return "Right shift (E_EXPR_RSHIFT)";
	}
};

#endif