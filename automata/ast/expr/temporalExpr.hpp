#ifndef TEMPORAL_EXPR_H
#define TEMPORAL_EXPR_H

#include "unaryExpr.hpp"
#include "binaryExpr.hpp"

//E_EXPR_ALWAYS,	// child[0] = E_EXPR_*
class exprGlobally : public exprUnary
{
public:
	exprGlobally(expr *mExpr, int lineNb)
		: exprUnary(astNode::E_EXPR_PAR, mExpr, lineNb)
	{
	}

	operator std::string() const override {
		assert(getExpr());
		return "[](" + std::string(*getExpr()) + ")";
	}

	std::string getTypeDescr(void) const override {
		return "Globally temporal operator (E_EXPR_GLOBALLY)";
	}

	expr* deepCopy(void) const override {
		exprGlobally* copy = new exprGlobally(*this);
		copy->copyChildren(*this);
		return copy;
	}
};

//E_EXPR_EVENTUALLY,	// child[0] = E_EXPR_*
class exprFinally : public exprUnary
{
public:
	exprFinally(expr *mExpr, int lineNb)
		: exprUnary(astNode::E_EXPR_PAR, mExpr, lineNb)
	{
	}

	operator std::string() const override {
		assert(getExpr());
		return "<>(" + std::string(*getExpr()) + ")";
	}

	std::string getTypeDescr(void) const override {
		return "Finally temporal operator (E_EXPR_FINALLY)";
	}

	expr* deepCopy(void) const override {
		exprFinally* copy = new exprFinally(*this);
		copy->copyChildren(*this);
		return copy;
	}
};

//E_EXPR_NEXT,	// child[0] = E_EXPR_*
class exprNext : public exprUnary
{
public:
	exprNext(expr *mExpr, int lineNb)
		: exprUnary(astNode::E_EXPR_PA, mExpr, lineNb)
	{
	}

	operator std::string() const override {
		assert(getExpr());
		return "X(" + std::string(*getExpr()) + ")";
	}

	std::string getTypeDescr(void) const override {
		return "Next temporal operator (E_EXPR_NEXT)";
	}

	expr* deepCopy(void) const override {
		exprNext* copy = new exprNext(*this);
		copy->copyChildren(*this);
		return copy;
	}
};

//E_EXPR_UNTIL,	// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprUntil : public exprBinary
{
public:
	exprUntil(expr *left, expr *right, int lineNb)
		: exprBinary(astNode::E_EXPR_PAR, left, right, lineNb)
	{
	}

	operator std::string() const override {
		return "("+ std::string(*getRightExpr())+")U(" + std::string(*getLeftExpr()) + ")";
	}

	std::string getTypeDescr(void) const override {
		return "Until temporal operator (E_EXPR_NEXT)";
	}

	expr* deepCopy(void) const override {
		exprUntil* copy = new exprUntil(*this);
		copy->copyChildren(*this);
		return copy;
	}
};

//E_EXPR_ALWAYS,	// child[0] = E_EXPR_*
class exprAlways : public exprUnary
{
public:
	exprAlways(expr *mExpr, int lineNb)
		: exprUnary(astNode::E_EXPR_PAR, mExpr, lineNb)
	{
	}

	operator std::string() const override {
		assert(getExpr());
		return "A(" + std::string(*getExpr()) + ")";
	}

	std::string getTypeDescr(void) const override {
		return "Always temporal operator (E_EXPR_ALWAYS)";
	}

	expr* deepCopy(void) const override {
		exprAlways* copy = new exprAlways(*this);
		copy->copyChildren(*this);
		return copy;
	}
};

//E_EXPR_EVENTUALLY,	// child[0] = E_EXPR_*
class exprEventually : public exprUnary
{
public:
	exprEventually(expr *mExpr, int lineNb)
		: exprUnary(astNode::E_EXPR_PAR, mExpr, lineNb)
	{
	}

	operator std::string() const override {
		assert(getExpr());
		return "E(" + std::string(*getExpr()) + ")";
	}

	std::string getTypeDescr(void) const override {
		return "Eventually temporal operator (E_EXPR_EVENTUALLY)";
	}

	expr* deepCopy(void) const override {
		exprEventually* copy = new exprEventually(*this);
		copy->copyChildren(*this);
		return copy;
	}
};

#endif