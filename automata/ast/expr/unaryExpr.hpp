#ifndef UNARY_EXPR_H
#define UNARY_EXPR_H

#include "expr.hpp"
#include "varExpr.hpp"

class exprUnary : public expr
{
public:
	expr* getExpr(void) const;

protected:
	exprUnary(Type type, expr* mExpr, int lineNb);

	void setExpr(expr* mExpr);

	symbol::Type getExprType(void) const override;
};

//E_EXPR_PAR,			// child[0] = E_EXPR_*
class exprPar : public exprUnary
{
public:
	exprPar(expr *mExpr, int lineNb)
		: exprUnary(astNode::E_EXPR_PAR, mExpr, lineNb)
	{
	}

	operator std::string() const override {
		assert(getExpr());
		return "(" + std::string(*getExpr()) + ")";
	}

	std::string getTypeDescr(void) const override {
		return "Parentheses (E_EXPR_PAR)";
	}

	expr* deepCopy(void) const override {
		exprPar* copy = new exprPar(*this);
		copy->copyChildren(*this);
		return copy;
	}
};

//E_EXPR_COUNT,		// child[0] = E_EXPR_*
class exprCount : public exprUnary
{
public:
	exprCount(expr *mExpr, int lineNb)
		: exprUnary(astNode::E_EXPR_COUNT, mExpr, lineNb)
	{
	}

	operator std::string() const override {
		assert(getExpr());
		return "count(" + std::string(*getExpr()) + ") ";
	}

	std::string getTypeDescr(void) const override {
		return "Clones count (E_EXPR_COUNT)";
	}

	symbol::Type getExprType(void) const {
		return symbol::T_BYTE;
	}

	expr* deepCopy(void) const override {
		exprCount* copy = new exprCount(*this);
		copy->copyChildren(*this);
		return copy;
	}
};

//E_EXPR_UMIN,		// child[0] = E_EXPR_*
class exprUMin : public exprUnary
{
public:
	exprUMin(expr *mExpr, int lineNb)
		: exprUnary(astNode::E_EXPR_UMIN, mExpr, lineNb)
	{
	}

	operator std::string() const override {
		assert(getExpr());
		return "-" + std::string(*getExpr());
	}

	std::string getTypeDescr(void) const override {
		return "Unary minus (E_EXPR_UMIN)";
	}

	expr* deepCopy(void) const override {
		exprUMin* copy = new exprUMin(*this);
		copy->copyChildren(*this);
		return copy;
	}
};

//E_EXPR_NEG,			// child[0] = E_EXPR_*
class exprNeg : public exprUnary
{
public:
	exprNeg(expr *mExpr, int lineNb)
		: exprUnary(astNode::E_EXPR_NEG, mExpr, lineNb)
	{
	}

	operator std::string() const override {
		assert(getExpr());
		return "!" + std::string(*getExpr());
	}

	std::string getTypeDescr(void) const override {
		return "Negation (E_EXPR_NEG)";
	}

	unsigned int assignMutables(const Mask& mask = Mask(), unsigned int id = 0) override;

	std::vector<astNode*> getMutations(void) const override;

	expr* deepCopy(void) const override {
		exprNeg* copy = new exprNeg(*this);
		copy->copyChildren(*this);
		return copy;
	}
};

//E_EXPR_BITWNEG,		// child[0] = E_EXPR_*
class exprBitwNeg : public exprUnary
{
public:
	exprBitwNeg(expr *mExpr, int lineNb)
		: exprUnary(astNode::E_EXPR_BITWNEG, mExpr, lineNb)
	{
	}

	operator std::string() const override {
		assert(getExpr());
		return "~" + std::string(*getExpr());
	}

	std::string getTypeDescr(void) const override {
		return "Bitwise neg (E_EXPR_BITWNEG)";
	}

	expr* deepCopy(void) const override {
		exprBitwNeg* copy = new exprBitwNeg(*this);
		copy->copyChildren(*this);
		return copy;
	}
};

//E_EXPR_LEN,			// child[0] = E_VARREF
class exprLen : public exprUnary
{
public:
	exprLen(exprVarRef *mExpr, int lineNb)
		: exprUnary(astNode::E_EXPR_LEN, mExpr, lineNb)
	{
	}

	operator std::string() const override {
		assert(getExpr());
		return "len(" + std::string(*getExpr()) + ")";
	}

	std::string getTypeDescr(void) const override {
		return "Length (E_EXPR_LEN)";
	}

	symbol::Type getExprType(void) const override {
		return symbol::T_BYTE;
	}

	exprVarRef* getVarRef(void) const {
		return dynamic_cast<exprVarRef*>(getExpr());
	}

	expr* deepCopy(void) const override {
		exprLen* copy = new exprLen(*this);
		copy->copyChildren(*this);
		return copy;
	}
};

//E_EXPR_FULL,		// child[0] = E_VARREF
class exprFull : public exprUnary
{
public:
	exprFull(exprVarRef *mExpr, int lineNb)
		: exprUnary(astNode::E_EXPR_FULL, mExpr, lineNb)
	{
	}

	operator std::string() const override {
		assert(getExpr());
		return "full(" + std::string(*getExpr()) + ")";
	}

	std::string getTypeDescr(void) const override {
		return "Full probe (E_EXPR_FULL)";
	}

	symbol::Type getExprType(void) const override {
		return symbol::T_BOOL;
	}

	exprVarRef* getVarRef(void) const {
		return dynamic_cast<exprVarRef*>(getExpr());
	}

	expr* deepCopy(void) const override {
		exprFull* copy = new exprFull(*this);
		copy->copyChildren(*this);
		return copy;
	}
};

//E_EXPR_NFULL,		// child[0] = E_VARREF
class exprNFull : public exprUnary
{
public:
	exprNFull(exprVarRef *mExpr, int lineNb)
		: exprUnary(astNode::E_EXPR_NFULL, mExpr, lineNb)
	{
	}

	operator std::string() const override {
		assert(getExpr());
		return "nfull(" + std::string(*getExpr()) + ")";
	}

	std::string getTypeDescr(void) const override {
		return "Not full probe (E_EXPR_NFULL)";
	}

	symbol::Type getExprType(void) const override {
		return symbol::T_BOOL;
	}

	exprVarRef* getVarRef(void) const {
		return dynamic_cast<exprVarRef*>(getExpr());
	}

	expr* deepCopy(void) const override {
		exprNFull* copy = new exprNFull(*this);
		copy->copyChildren(*this);
		return copy;
	}
};

//E_EXPR_EMPTY,		// child[0] = E_VARREF
class exprEmpty : public exprUnary
{
public:
	exprEmpty(exprVarRef *mExpr, int lineNb)
		: exprUnary(astNode::E_EXPR_EMPTY, mExpr, lineNb)
	{
	}

	operator std::string() const override {
		assert(getExpr());
		return "empty(" + std::string(*getExpr()) + ")";
	}

	std::string getTypeDescr(void) const override {
		return "Empty probe (E_EXPR_EMPTY)";
	}

	symbol::Type getExprType(void) const override {
		return symbol::T_BOOL;
	}

	exprVarRef* getVarRef(void) const {
		return dynamic_cast<exprVarRef*>(getExpr());
	}

	expr* deepCopy(void) const override {
		exprEmpty* copy = new exprEmpty(*this);
		copy->copyChildren(*this);
		return copy;
	}
};

//E_EXPR_NEMPTY,		// child[0] = E_VARREF
class exprNEmpty : public exprUnary
{
public:
	exprNEmpty(exprVarRef *mExpr, int lineNb)
		: exprUnary(astNode::E_EXPR_NEMPTY, mExpr, lineNb)
	{
	}

	operator std::string() const override {
		assert(getExpr());
		return "nempty(" + std::string(*getExpr()) + ")";
	}

	std::string getTypeDescr(void) const override {
		return "Not empty probe (E_EXPR_NEMPTY)";
	}

	symbol::Type getExprType(void) const override {
		return symbol::T_BOOL;
	}

	exprVarRef* getVarRef(void) const {
		return dynamic_cast<exprVarRef*>(getExpr());
	}

	expr* deepCopy(void) const override {
		exprNEmpty* copy = new exprNEmpty(*this);
		copy->copyChildren(*this);
		return copy;
	}
};

#endif
