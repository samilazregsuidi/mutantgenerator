#ifndef TEMPORAL_EXPR_H
#define TEMPORAL_EXPR_H

#include "unaryExpr.hpp"
#include "binaryExpr.hpp"

class variantQuantifier : public exprUnary {
protected:
	variantQuantifier(Type type, expr *mExpr, int lineNb) 
		: exprUnary(type, mExpr, lineNb)
	{
	}
};

class exprUnaryTemporal : public exprUnary {
protected:
	exprUnaryTemporal(Type type, expr *mExpr, int lineNb) 
		: exprUnary(type, mExpr, lineNb)
	{
	}
};

class exprBinaryTemporal : public exprBinary {
protected:
	exprBinaryTemporal(Type type, expr* left, expr* right, int lineNb) 
		: exprBinary(type, left, right, lineNb)
	{
	}
};

//E_EXPR_GLOBALLY,	// child[0] = E_EXPR_*
class exprGlobally : public exprUnaryTemporal
{
public:
	exprGlobally(expr *mExpr, int lineNb)
		: exprUnaryTemporal(astNode::E_EXPR_GLOBALLY, mExpr, lineNb)
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
class exprFinally : public exprUnaryTemporal
{
public:
	exprFinally(expr *mExpr, int lineNb)
		: exprUnaryTemporal(astNode::E_EXPR_FINALLY, mExpr, lineNb)
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
class exprNext : public exprUnaryTemporal
{
public:
	exprNext(expr *mExpr, int lineNb)
		: exprUnaryTemporal(astNode::E_EXPR_NEXT, mExpr, lineNb)
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
class exprUntil : public exprBinaryTemporal
{
public:
	exprUntil(expr *left, expr *right, int lineNb)
		: exprBinaryTemporal(astNode::E_EXPR_UNTIL, left, right, lineNb)
	{
	}

	operator std::string() const override {
		return "("+ std::string(*getRightExpr())+")U(" + std::string(*getLeftExpr()) + ")";
	}

	std::string getTypeDescr(void) const override {
		return "Until temporal operator (E_EXPR_UNTIL)";
	}

	expr* deepCopy(void) const override {
		exprUntil* copy = new exprUntil(*this);
		copy->copyChildren(*this);
		return copy;
	}
};

//E_EXPR_ALWAYS,	// child[0] = E_EXPR_*
class exprAlways : public variantQuantifier
{
public:
	exprAlways(exprVarRefName *variant, int lineNb)
		: variantQuantifier(astNode::E_EXPR_ALWAYS, variant, lineNb)
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
class exprEventually : public variantQuantifier
{
public:
	exprEventually(exprVarRefName *variant, int lineNb)
		: variantQuantifier(astNode::E_EXPR_EVENTUALLY, variant, lineNb)
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