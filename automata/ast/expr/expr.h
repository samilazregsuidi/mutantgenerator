#ifndef EXPR_H
#define EXPR_H

#include <vector>

#include "astNode.h"

class exprVarRef;
class exprArgList;

class expr : public astNode
{
protected:
	expr(Type type, int lineNb)
		: astNode(type, lineNb)
	{}

public:

	void mutateMutable(unsigned int id) override {
		id++;//keep compiler happy
		return;
	}

	virtual std::vector<expr*> getMutations(void) const {
		assert(false);
		return std::vector<expr*>();
	}

	virtual expr* deepCopy(void) const = 0;

	virtual symbol::Type getExprType(void) const {
		return symbol::T_NA;
	}
};

//E_EXPR_COND,		// child[0] = E_EXPR_* (the condition), child[1] = E_EXPR_* (then), child[2] = E_EXPR_* (else)
class exprCond : public expr
{
public:
	exprCond(expr *cond, expr *then, expr *elsE, int lineNb)
		: expr(astNode::E_EXPR_COND, lineNb)
	{
		this->cond = cond;
		this->then = then;
		this->elsE = elsE;

		this->cond->setParent(this);
		this->then->setParent(this);
		this->elsE->setParent(this);
	}

	operator std::string() const override
	{
		return "(" + std::string(*cond) + "? " + std::string(*then) + ": " + std::string(*elsE) + ")";
	}

	std::string getTypeDescr(void) const override
	{
		return "Conditional expression (E_EXPR_COND)";
	}

	unsigned int assignMutables(const Mask& mask, unsigned int id = 0) override {
		if(mask.isPresent(type)){
			id = cond->assignMutables(mask, id);
			id = then->assignMutables(mask, id);
			id = elsE->assignMutables(mask, id);
		}
		return id;
	}

	void mutateMutable(unsigned int id) override {

		if(cond->getMId() == id) {
			auto mutations = cond->getMutations();
			assert(mutations.size());
			delete cond;
			cond = mutations[rand() % mutations.size()]; 
			return;
		}

		if(then->getMId() == id) {
			auto mutations = then->getMutations();
			assert(mutations.size());
			delete then;
			then = mutations[rand() % mutations.size()]; 
			return;
		}

		if(elsE->getMId() == id) {
			auto mutations = elsE->getMutations();
			assert(mutations.size());
			delete elsE;
			elsE = mutations[rand() % mutations.size()]; 
			return;
		}

		cond->mutateMutable(id);
		then->mutateMutable(id);
		elsE->mutateMutable(id);	

	}

	expr* deepCopy(void) const override {
		exprCond* copy = new exprCond(*this);
		copy->cond = cond->deepCopy();
		copy->then = then->deepCopy();
		copy->elsE = elsE->deepCopy();
		return copy;
	}

private:
	expr* cond;
	expr* then;
	expr* elsE;
};

class procSymNode;

//E_EXPR_RUN,			// child[0] = E_ARGLIST, sVal = the procType name, and after processing: symTab = node in symbol table that represents the proctype
class exprRun : public expr
{
public:
	exprRun(const std::string& procName, exprArgList *argList, exprVarRef *card, int lineNb);

	exprRun(const std::string& procName, exprArgList *argList, int lineNb);

	operator std::string() const override;

	std::string getTypeDescr(void) const override
	{
		return "Run (E_EXPR_RUN)";
	}

	expr* deepCopy(void) const override;

private:
	std::string procName;
	procSymNode* procSym;
	exprArgList* argList;
	exprVarRef* card;
};

//E_EXPR_TIMEOUT,	// iVal = 0
class exprTimeout : public expr
{
public:
	exprTimeout(int lineNb)
		: expr(astNode::E_EXPR_TIMEOUT, lineNb)
	{
	}

	operator std::string() const override
	{
		return "timeout";
	}

	std::string getTypeDescr(void) const override
	{
		return "Timeout (E_EXPR_TIMEOUT)";
	}

	expr* deepCopy(void) const override {
		exprTimeout* copy = new exprTimeout(*this);
		return copy;
	}
};

//E_EXPR_SKIP,		// iVal = 1
class exprSkip : public expr
{
public:
	exprSkip(int lineNb)
		: expr(astNode::E_EXPR_SKIP, lineNb)
	{
	}

	operator std::string() const override
	{
		return "skip";
	}

	std::string getTypeDescr(void) const override
	{
		return "Skip (E_EXPR_SKIP)";
	}

	expr* deepCopy(void) const override {
		exprSkip* copy = new exprSkip(*this);
		return copy;
	}
};

#endif