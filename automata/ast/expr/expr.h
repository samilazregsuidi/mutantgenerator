#ifndef EXPR_H
#define EXPR_H

#include <vector>
#include <memory>

#include "astNode.h"

class exprVarRef;
class exprArgList;

class expr : public astNode
{
protected:
	expr(Type type, int lineNb)
		: astNode(type, lineNb)
	{
		exprType = symbol::T_NA;
	}

	expr(const expr&) = default;
	expr(expr&&) = default;

public:
	virtual std::vector<expr*> getMutations(void) const {
		assert(false);
		return std::vector<expr*>();
	}

	virtual expr* deepCopy(void) const { assert(false); return nullptr; };

	virtual symbol::Type getExprType(void) const {
		return exprType;
	}

	void setExprType(symbol::Type exprType) {
		this->exprType = exprType;
	}

	virtual bool castToExprType(symbol::Type type) const {
		type = type;//keep compiler happt
		return false;
	}

	static symbol::Type getExprType(expr* left, expr* right) {
		if(left->getExprType() == right->getExprType())
			return left->getExprType();
		else if(left->castToExprType(right->getExprType()))
			return right->getExprType();
		else if(right->castToExprType(left->getExprType()))
			return left->getExprType();
		else
			assert(false);

		return symbol::T_NA;
	}

public:
	virtual void clearChildren() override {
		astNode::clearChildren();
	}

protected:
	symbol::Type exprType;
};

//E_EXPR_COND,		// child[0] = E_EXPR_* (the condition), child[1] = E_EXPR_* (then), child[2] = E_EXPR_* (else)
class exprCond : public expr
{
public:
	exprCond(expr *pcond, expr *pthen, expr *pelsE, int lineNb)
		: expr(astNode::E_EXPR_COND, lineNb), cond(nullptr), then(nullptr), elsE(nullptr)
	{
		setCond(pcond);
		setThen(pthen);
		setElse(pelsE);
	}

	virtual ~exprCond() {
		delete cond;
		delete then;
		delete elsE;
	}

	void setCond(expr* cond) {
		rmChild(this->cond);
		addChild(cond);
		this->cond = cond;
	}

	void setThen(expr* then) {
		rmChild(this->then);
		addChild(then);
		this->then = then;
	}

	void setElse(expr* elsE) {
		rmChild(this->elsE);
		addChild(elsE);
		this->elsE = elsE;
	}

	operator std::string() const override {
		return "(" + (cond ? std::string(*cond) : "nullptr" ) + "; " + (then ? std::string(*then) : "nullptr") + ": " + (elsE ? std::string(*elsE) : "nullptr") + ")";
	}

	std::string getTypeDescr(void) const override {
		return "Conditional expression (E_EXPR_COND)";
	}

	symbol::Type getExprType(void) const override {
		return expr::getExprType(then, elsE);
	}

	bool mutateMutable(unsigned int id) override {

		if(cond->getMId() == id) {
			auto mutations = cond->getMutations();
			assert(mutations.size());

			size_t i = rand() % mutations.size();
			auto tmp = mutations[i];
			setCond(tmp);
			mutations.erase(mutations.begin() + i);

			for(auto i : mutations) {
				i->clearChildren();
				delete i;
			}
			tmp->forceParentOnChildren();
			return true;
		}

		if(then->getMId() == id) {
			auto mutations = then->getMutations();
			assert(mutations.size());

			size_t i = rand() % mutations.size();
			auto tmp = mutations[i];
			setThen(tmp);
			mutations.erase(mutations.begin() + i);

			for(auto i : mutations) {
				i->clearChildren();
				delete i;
			}
			tmp->forceParentOnChildren();
			return true;
		}

		if(elsE->getMId() == id) {
			auto mutations = elsE->getMutations();
			assert(mutations.size());

			size_t i = rand() % mutations.size();
			auto tmp = mutations[i];
			setElse(tmp);
			mutations.erase(mutations.begin() + i);

			for(auto i : mutations) {
				i->clearChildren();
				delete i;
			}
			tmp->forceParentOnChildren();
			return true;
		}

		return false;

	}

	expr* deepCopy(void) const override {
		exprCond* copy = new exprCond(*this);
		copy->setCond(cond->deepCopy());
		copy->setThen(then->deepCopy());
		copy->setElse(elsE->deepCopy());
		return copy;
	}

public:
	virtual void clearChildren() override {
		setCond(nullptr);
		setThen(nullptr);
		setElse(nullptr);
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

	virtual ~exprRun();

	void setCard(exprVarRef* card);

	void setArgList(exprArgList* argList);

	operator std::string() const override;

	std::string getTypeDescr(void) const override {
		return "Run (E_EXPR_RUN)";
	}

	symbol::Type getExprType(void) const override {
		return symbol::T_BYTE;
	}

	expr* deepCopy(void) const override;

public:
	virtual void clearChildren() override {
		setCard(nullptr);
		setArgList(nullptr);
	}

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

	operator std::string() const override {
		return "timeout";
	}

	std::string getTypeDescr(void) const override {
		return "Timeout (E_EXPR_TIMEOUT)";
	}

	symbol::Type getExprType(void) const override {
		return symbol::T_BOOL;
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

	operator std::string() const override {
		return "skip";
	}

	std::string getTypeDescr(void) const override {
		return "Skip (E_EXPR_SKIP)";
	}

	symbol::Type getExprType(void) const override {
		return symbol::T_BOOL;
	}

	expr* deepCopy(void) const override {
		exprSkip* copy = new exprSkip(*this);
		return copy;
	}
};

#endif
