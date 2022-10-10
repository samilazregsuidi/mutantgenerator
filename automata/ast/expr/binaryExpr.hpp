#ifndef BINARY_EXPR_H
#define BINARY_EXPR_H

#include "expr.hpp"

#include <vector>
#include <cstdlib>

class exprBinary : public expr
{
public:
	expr* getLeftExpr(void) const;

	expr* getRightExpr(void) const;

	symbol::Type getExprType(void) const;

protected:
	exprBinary(Type type, expr* left, expr* right, int lineNb);

	void setLeftExpr(expr* left);

	void setRightExpr(expr* right);

	unsigned int assignMutables(const Mask& mask = Mask(), unsigned int id = 0) override;
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
		assert(getLeftExpr() && getRightExpr());
		return std::string(*getLeftExpr()) + " + " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override {
		return "Plus (E_EXPR_PLUS)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprPlus* copy = new exprPlus(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) + getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) + getRightExpr()->acceptVisitor(visitor);
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
		return std::string(*getLeftExpr()) + " - " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override
	{
		return "Minus (E_EXPR_MINUS)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprMinus* copy = new exprMinus(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) - getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) - getRightExpr()->acceptVisitor(visitor);
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
		return std::string(*getLeftExpr()) + " * " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override
	{
		return "Times (E_EXPR_TIMES)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprTimes* copy = new exprTimes(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) * getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) * getRightExpr()->acceptVisitor(visitor);
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
		return std::string(*getLeftExpr()) + " / " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override
	{
		return "Divide (E_EXPR_DIV)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprDiv* copy = new exprDiv(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) / getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) / getRightExpr()->acceptVisitor(visitor);
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
		return std::string(*getLeftExpr()) + " % " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override
	{
		return "Modulo (E_EXPR_MOD)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprMod* copy = new exprMod(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) % getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) % getRightExpr()->acceptVisitor(visitor);
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
		return std::string(*getLeftExpr()) + " > " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override
	{
		return "Greater than (E_EXPR_GT)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprGT* copy = new exprGT(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) > getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) > getRightExpr()->acceptVisitor(visitor);
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
		return std::string(*getLeftExpr()) + " < " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override
	{
		return "Less than (E_EXPR_LT)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprLT* copy = new exprLT(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) < getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) < getRightExpr()->acceptVisitor(visitor);
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
		return std::string(*getLeftExpr()) + " >= " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override
	{
		return "Greater or equal than (E_EXPR_GE)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprGE* copy = new exprGE(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) >= getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) >= getRightExpr()->acceptVisitor(visitor);
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
		return std::string(*getLeftExpr()) + " <= " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override
	{
		return "Less or equal than (E_EXPR_LE)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprLE* copy = new exprLE(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) <= getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) <= getRightExpr()->acceptVisitor(visitor);
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
		return std::string(*getLeftExpr()) + " == " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override
	{
		return "Equal (E_EXPR_EQ)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprEQ* copy = new exprEQ(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) == getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) == getRightExpr()->acceptVisitor(visitor);
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
		return std::string(*getLeftExpr()) + " != " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override
	{
		return "Not equal (E_EXPR_NE)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprNE* copy = new exprNE(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) != getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) != getRightExpr()->acceptVisitor(visitor);
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
		return std::string(*getLeftExpr()) + " && " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override
	{
		return "Logical and (E_EXPR_AND)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprAnd* copy = new exprAnd(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) && getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) && getRightExpr()->acceptVisitor(visitor);
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
		return std::string(*getLeftExpr()) + " || " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override
	{
		return "Logical or (E_EXPR_OR)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprOr* copy = new exprOr(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) || getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) || getRightExpr()->acceptVisitor(visitor);
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
		return std::string(*getLeftExpr()) + " & " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override
	{
		return "Bitwise and (E_EXPR_BITWAND)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprBitwAnd* copy = new exprBitwAnd(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) & getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) & getRightExpr()->acceptVisitor(visitor);
	}
};

//E_EXPR_IMPLIES,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprImplies : public exprBinary
{
public:
	exprImplies(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_IMPLIES, left, right, lineNb)
	{
	}

	operator std::string() const override
	{
		return std::string(*getLeftExpr()) + " => " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override
	{
		return "implies (E_EXPR_IMPLIES)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprImplies* copy = new exprImplies(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) & getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) & getRightExpr()->acceptVisitor(visitor);
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
		return std::string(*getLeftExpr()) + " | " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override
	{
		return "Bitwise or (E_EXPR_BITWOR)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprBitwOr* copy = new exprBitwOr(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) | getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) | getRightExpr()->acceptVisitor(visitor);
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
		return std::string(*getLeftExpr()) + " ^ " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override
	{
		return "Bitwise xor (E_EXPR_BITWXOR)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprBitwXor* copy = new exprBitwXor(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) ^ getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) ^ getRightExpr()->acceptVisitor(visitor);
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

	operator std::string() const override {
		return std::string(*getLeftExpr()) + " << " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override {
		return "Left shift (E_EXPR_LSHIFT)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprLShift* copy = new exprLShift(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) << getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) << getRightExpr()->acceptVisitor(visitor);
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
		return std::string(*getLeftExpr()) + " >> " + std::string(*getRightExpr());
	}

	std::string getTypeDescr(void) const override
	{
		return "Right shift (E_EXPR_RSHIFT)";
	}

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprRShift* copy = new exprRShift(*this);
		copy->copyChildren(*this);
		return copy;
	}

	int acceptVisitor(ASTConstVisitorInt* visitor) const override {
		return getLeftExpr()->acceptVisitor(visitor) >> getRightExpr()->acceptVisitor(visitor);
	}

	int acceptVisitor(ASTVisitorInt* visitor) override {
		return getLeftExpr()->acceptVisitor(visitor) >> getRightExpr()->acceptVisitor(visitor);
	}
};

#endif
