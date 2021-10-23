#ifndef BINARY_EXPR_H
#define BINARY_EXPR_H

#include "expr.h"

#include <vector>
#include <cstdlib>

class exprBinary : public expr
{
protected:
	exprBinary(Type type, expr* left, expr* right, int lineNb)
		: expr(type, lineNb)
	{
		setLeft(left);
		setRight(right);
	}

	void setLeft(expr* left) {
		rmChild(this->left);
		addChild(left);
		this->left = left;
	}

	void setRight(expr* right) {
		rmChild(this->right);
		addChild(right);
		this->right = right;
	}

	symbol::Type getExprType(void) const {
		assert(left->getExprType() == right->getExprType());
		return left->getExprType();
	}

	unsigned int assignMutables(const Mask& mask = Mask(), unsigned int id = 0) override {
		if(mask.isPresent(type)) {
			id = left->assignMutables(mask, id);
			mId = ++id;//operator Id;
			id = right->assignMutables(mask, id);
		}
		return id; 
	}

	bool mutateMutable(unsigned int id) override {

		if(left->getMId() == id) {
			auto mutations = left->getMutations();
			assert(mutations.size());
			delete left;
			setLeft(mutations[rand() % mutations.size()]); 
			return true;
		}

		if(right->getMId() == id) {
			auto mutations = right->getMutations();
			assert(mutations.size());
			delete right;
			setRight(mutations[rand() % mutations.size()]); 
			return true;
		}

		return false;
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

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprPlus* copy = new exprPlus(*this);
		copy->left = left->deepCopy();
		copy->right = right->deepCopy();
		return copy;
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

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprMinus* copy = new exprMinus(*this);
		copy->left = left->deepCopy();
		copy->right = right->deepCopy();
		return copy;
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

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprTimes* copy = new exprTimes(*this);
		copy->left = left->deepCopy();
		copy->right = right->deepCopy();
		return copy;
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

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprDiv* copy = new exprDiv(*this);
		copy->left = left->deepCopy();
		copy->right = right->deepCopy();
		return copy;
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

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprMod* copy = new exprMod(*this);
		copy->left = left->deepCopy();
		copy->right = right->deepCopy();
		return copy;
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

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprGT* copy = new exprGT(*this);
		copy->left = left->deepCopy();
		copy->right = right->deepCopy();
		return copy;
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

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprLT* copy = new exprLT(*this);
		copy->left = left->deepCopy();
		copy->right = right->deepCopy();
		return copy;
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

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprGE* copy = new exprGE(*this);
		copy->left = left->deepCopy();
		copy->right = right->deepCopy();
		return copy;
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

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprLE* copy = new exprLE(*this);
		copy->left = left->deepCopy();
		copy->right = right->deepCopy();
		return copy;
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

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprEQ* copy = new exprEQ(*this);
		copy->left = left->deepCopy();
		copy->right = right->deepCopy();
		return copy;
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

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprNE* copy = new exprNE(*this);
		copy->left = left->deepCopy();
		copy->right = right->deepCopy();
		return copy;
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

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprAnd* copy = new exprAnd(*this);
		copy->left = left->deepCopy();
		copy->right = right->deepCopy();
		return copy;
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

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprOr* copy = new exprOr(*this);
		copy->left = left->deepCopy();
		copy->right = right->deepCopy();
		return copy;
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

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprBitwAnd* copy = new exprBitwAnd(*this);
		copy->left = left->deepCopy();
		copy->right = right->deepCopy();
		return copy;
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

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprBitwOr* copy = new exprBitwOr(*this);
		copy->left = left->deepCopy();
		copy->right = right->deepCopy();
		return copy;
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

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprBitwXor* copy = new exprBitwXor(*this);
		copy->left = left->deepCopy();
		copy->right = right->deepCopy();
		return copy;
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

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprLShift* copy = new exprLShift(*this);
		copy->left = left->deepCopy();
		copy->right = right->deepCopy();
		return copy;
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

	std::vector<expr*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprRShift* copy = new exprRShift(*this);
		copy->left = left->deepCopy();
		copy->right = right->deepCopy();
		return copy;
	}
};

#endif