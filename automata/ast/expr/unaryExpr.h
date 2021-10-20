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

		this->expression->setParent(this);
	}

	~exprUnary() override {
		delete expression;
	}

	unsigned int assignMutables(const Mask& mask, unsigned int id = 0) override {
		if(mask.isPresent(type))
			id = expression->assignMutables(mask, id);
		return id;
	}

	void mutateMutable(unsigned int id) override {

		if(expression->getMId() == id) {
			auto mutations = expression->getMutations();
			assert(mutations.size());
			delete expression;
			expression = static_cast<exprVarRef*>(mutations[rand() % mutations.size()]); 
			return;
		}

		expression->mutateMutable(id);	

	}

	symbol::Type getExprType(void) const {
		return expression->getExprType();
	}

public:
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

	operator std::string() const override
	{
		return "(" + std::string(*expression) + ")";
	}

	std::string getTypeDescr(void) const override
	{
		return "Parentheses (E_EXPR_PAR)";
	}

	expr* deepCopy(void) const override {
		exprPar* copy = new exprPar(*this);
		copy->expression = expression->deepCopy();
		return copy;
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

	operator std::string() const override
	{
		return "count(" + std::string(*expression) + ") ";
	}

	std::string getTypeDescr(void) const override
	{
		return "Clones count (E_EXPR_COUNT)";
	}

	expr* deepCopy(void) const override {
		exprCount* copy = new exprCount(*this);
		copy->expression = expression->deepCopy();
		return copy;
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

	operator std::string() const override
	{
		return "-" + std::string(*expression);
	}

	std::string getTypeDescr(void) const override
	{
		return "Unary minus (E_EXPR_UMIN)";
	}

	expr* deepCopy(void) const override {
		exprUMin* copy = new exprUMin(*this);
		copy->expression = expression->deepCopy();
		return copy;
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

	operator std::string() const override
	{
		return "!" + std::string(*expression);
	}

	std::string getTypeDescr(void) const override
	{
		return "Negation (E_EXPR_NEG)";
	}

	expr* deepCopy(void) const override {
		exprNeg* copy = new exprNeg(*this);
		copy->expression = expression->deepCopy();
		return copy;
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

	operator std::string() const override
	{
		return "~" + std::string(*expression);
	}

	std::string getTypeDescr(void) const override
	{
		return "Bitwise neg (E_EXPR_BITWNEG)";
	}

	expr* deepCopy(void) const override {
		exprBitwNeg* copy = new exprBitwNeg(*this);
		copy->expression = expression->deepCopy();
		return copy;
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

	operator std::string() const override
	{
		return "len(" + std::string(*expression) + ")";
	}

	std::string getTypeDescr(void) const override
	{
		return "Length (E_EXPR_LEN)";
	}

	expr* deepCopy(void) const override {
		exprLen* copy = new exprLen(*this);
		copy->expression = expression->deepCopy();
		return copy;
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

	operator std::string() const override
	{
		return "full(" + std::string(*expression) + ")";
	}

	std::string getTypeDescr(void) const override
	{
		return "Full probe (E_EXPR_FULL)";
	}

	expr* deepCopy(void) const override {
		exprFull* copy = new exprFull(*this);
		copy->expression = expression->deepCopy();
		return copy;
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

	operator std::string() const override
	{
		return "nfull(" + std::string(*expression) + ")";
	}

	std::string getTypeDescr(void) const override
	{
		return "Not full probe (E_EXPR_NFULL)";
	}

	expr* deepCopy(void) const override {
		exprNFull* copy = new exprNFull(*this);
		copy->expression = expression->deepCopy();
		return copy;
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

	operator std::string() const override
	{
		return "empty(" + std::string(*expression) + ")";
	}

	std::string getTypeDescr(void) const override
	{
		return "Empty probe (E_EXPR_EMPTY)";
	}

	expr* deepCopy(void) const override {
		exprEmpty* copy = new exprEmpty(*this);
		copy->expression = expression->deepCopy();
		return copy;
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

	operator std::string() const override
	{
		return "nempty(" + std::string(*expression) + ")";
	}

	std::string getTypeDescr(void) const override
	{
		return "Not empty probe (E_EXPR_NEMPTY)";
	}

	expr* deepCopy(void) const override {
		exprNEmpty* copy = new exprNEmpty(*this);
		copy->expression = expression->deepCopy();
		return copy;
	}
};

#endif