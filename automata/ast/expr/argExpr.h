#ifndef ARG_EXPR_H
#define ARG_EXPR_H

#include "expr.h"

class exprRArg : public expr
{
protected:
	exprRArg(Type type, int lineNb)
		: expr(type, lineNb)
	{}

	unsigned int assignMutables(const Mask& mask = Mask(), unsigned int id = 0) override {
		mask.isPresent(type);
		return id;
	}
};

//E_RARG_VAR,		// child[0] = E_VARREF
class exprRArgVar : public exprRArg
{
public:
	exprRArgVar(exprVarRef *varRef, int lineNb);

	virtual ~exprRArgVar();

	void setVarRef(exprVarRef* varRef);
	
	operator std::string() const override;

	std::string getTypeDescr(void) const override {
		return "Receive argument variable (E_RARG_VAR)";
	}

	expr* deepCopy(void) const override;

private:
	exprVarRef* varRef;
};

//E_RARG_EVAL,	// child[0] = E_EXPR_*
class exprRArgEval : public exprRArg
{
public:
	exprRArgEval(expr *toEval, int lineNb)
		: exprRArg(astNode::E_RARG_EVAL, lineNb)
		, toEval(nullptr)
	{
		setToEval(toEval);
	}

	virtual ~exprRArgEval() {
		delete toEval;
	}

	void setToEval(expr* toEval) {
		rmChild(this->toEval);
		addChild(toEval);
		this->toEval = toEval;
	}

	operator std::string() const override {
		return "eval(" + std::string(*toEval) + ")";
	}

	std::string getTypeDescr(void) const override {
		return "Receive argument eval (E_RARG_EVAL)";
	}

	expr* deepCopy(void) const override {
		exprRArgEval* copy = new exprRArgEval(*this);
		copy->setToEval(toEval->deepCopy());
		return copy;
	}

private:
	expr* toEval;
};

//E_RARG_CONST,	// iVal = the constant
class exprRArgConst : public exprRArg
{
public:
	exprRArgConst(int constant, int lineNb)
		: exprRArg(astNode::E_RARG_EVAL, lineNb)
		, constant(constant)
	{
	}

	operator std::string() const override {
		return std::to_string(constant);
	}

	std::string getTypeDescr(void) const override {
		return "Receive argument constant (E_RARG_CONST)";
	}

	expr* deepCopy(void) const override {
		exprRArgConst* copy = new exprRArgConst(*this);
		return copy;
	}

private:
	int constant;
};

//E_ARGLIST,			// child[0] = E_EXPR_* or E_RARG_VAR or E_RARG_EVAL or E_RARG_CONST,
// child[1] = E_ARGLIST (next argument, or NULL)
class exprArgList : public expr
{
public:
	exprArgList(exprRArg *node, exprArgList *list, int lineNb)
		: expr(astNode::E_ARGLIST, lineNb)
		, node(nullptr)
		, list(list)
	{
		
		setRArg(node);
		setArgList(list);
	}

	exprArgList(exprRArg *node, int lineNb)
		: expr(astNode::E_ARGLIST, lineNb)
	{
		setRArg(node);
		setArgList(nullptr);
	}

	virtual ~exprArgList() {
		delete node;
		delete list;
	}

	void setRArg(exprRArg* node) {
		rmChild(this->node);
		addChild(node);
		this->node = node;
	}

	void setArgList(exprArgList* list) {
		rmChild(this->list);
		addChild(list);
		this->list = list;
	}

	operator std::string() const override {
		//TODO : check nullptr
		return (node ? std::string(*node) : "nullptr") + (list ? ", " + std::string(*list) : "");
	}

	std::string getTypeDescr(void) const override {
		return "Argument list (E_ARGLIST)";
	}

	expr* deepCopy(void) const override {
		exprArgList* copy = new exprArgList(*this);
		copy->setRArg(dynamic_cast<exprRArg*>(node->deepCopy()));
		copy->setArgList(list? dynamic_cast<exprArgList*>(list->deepCopy()) : nullptr);
		return copy;
	}

private:
	exprRArg* node;
	exprArgList* list;
};

#endif