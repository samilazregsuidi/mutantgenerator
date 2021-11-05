#ifndef STMNT_H
#define STMNT_H

#include <iostream>

#include "astNode.h"
#include "varExpr.h"

//E_STMNT, 			// child[0] = E_STMNT_*
class stmnt : public astNode
{

protected:
	stmnt(Type type, int lineNb)
		: astNode(type, lineNb)
	{
		this->local = nullptr;
		this->next = nullptr;
		this->prev = this;
	}

public:

	static stmnt* merge(stmnt* list, stmnt* node);

	static std::string string(stmnt* list);

	//called for non mutable stmnts (e.g., vardecl)
	unsigned int assignMutables(const Mask& mask = Mask(), unsigned int id = 0) override {
		if(mask.isPresent(type))
			for(auto c : children)
				id = c->assignMutables(mask, id);

		else if (next)
			id = next->assignMutables(mask, id);
		return id;
	}

	void setLocalSymTab(symTable* local) {
		this->local = local;
		if(next)
			next->setLocalSymTab(local);
	}

	symTable* getLocalSymTab(void) const {
		return local;
	}

	void setNext(stmnt* next) {
		rmChild(this->next);
		addChild(next);
		this->next = next;
	}

	stmnt* getNext(void) const {
		return next;
	}

	virtual void printSymTab(void) const {
		std::cout <<" line " << getLineNb() << "\t| " << getTypeDescr() << "\n"; 
		if(local)
			local->print();
		else 
			std::cout << "NULL\n";
		
		if(next)
			next->printSymTab();
	}

	virtual stmnt* deepCopy(void) const = 0;

protected:
	symTable* local;
	stmnt* next;
	stmnt* prev;
};

//E_STMNT_SEQ,		// fsm = fsm of this sequence
class stmntSeq : public stmnt
{
protected:
	stmntSeq(Type type, stmnt* block, int lineNb)
		: stmnt(type, lineNb)
	{
		setBlock(block);
		//std::cout << "SEQ : line " << lineNb << " _ " << std::string(*this) << "\n";
	}

public:
	stmntSeq(stmnt* block, int lineNb)
		: stmnt(astNode::E_STMNT_SEQ, lineNb)
	{
		setBlock(block);
	}

public:

	void setBlock(stmnt* block) {
		rmChild(this->block);
		addChild(block);
		this->block = block;
	}

	operator std::string() const override {
		std::string res = "{\n";
		tab_lvl++;

		auto cur = block;
		while(cur) {
			res += _tab() + std::string(*cur);
			cur = cur->getNext();
		}
		
		tab_lvl--;
		res += _tab() + "};\n"; 
		return res;
	}

	std::string getTypeDescr(void) const override {
		return "Seq (E_STMNT_SEQ)";
	}

	stmnt* deepCopy(void) const override {
		stmntSeq* copy = new stmntSeq(*this);
		copy->prev = copy;
		copy->setBlock(block->deepCopy());
		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

protected:
	stmnt* block;
};

//E_STMNT_ATOMIC,		// fsm = fsm of the atomic sequence
class stmntAtomic : public stmntSeq
{
public:
	stmntAtomic(stmnt *block, int lineNb)
		: stmntSeq(astNode::E_STMNT_ATOMIC, block, lineNb)
	{
		//std::cout << "ATOMIC : line " << lineNb << " _ " << std::string(*this) << "\n";
	}

	operator std::string() const override {
		return "atomic " + stmntSeq::operator std::string();
	}

	std::string getTypeDescr(void) const override {
		return "Atomic (E_STMNT_ATOMIC)";
	}

	stmnt* deepCopy(void) const override {
		stmntAtomic* copy = new stmntAtomic(*this);
		copy->prev = copy;
		copy->setBlock(block->deepCopy());
		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}
};

//E_STMNT_ASGN,		// child[0] = E_VARREF, child[1] = E_EXPR_*
class stmntAsgn : public stmnt
{
public:
	stmntAsgn(exprVarRef *varRef, expr *assign, int lineNb)
		: stmnt(astNode::E_STMNT_ASGN, lineNb)
	{
		setVarRef(varRef);
		setAssign(assign);

		assign->setExprType(varRef->getExprType());
	}

	void setVarRef(exprVarRef* varRef) {
		rmChild(this->varRef);
		addChild(varRef);
		this->varRef = varRef;
	}

	void setAssign(expr* assign) {
		rmChild(this->assign);
		addChild(assign);
		this->assign = assign;
	}

	operator std::string() const override{
		return std::string(*varRef) + " = " + std::string(*assign) + ";\n";
	}

	std::string getTypeDescr(void) const override{
		return "Assignment (E_STMNT_ASGN)";
	}

	bool mutateMutable(unsigned int id) override {

		if(varRef->getMId() == id) {
			auto mutations = varRef->getMutations();
			assert(mutations.size());
			int debug = rand() % mutations.size();
			auto ddebug = static_cast<exprVarRef*>(mutations[debug]);
			setVarRef(ddebug);
			return true;
		}

		if(assign->getMId() == id) {
			auto mutations = assign->getMutations();
			assert(mutations.size());
			setAssign(mutations[rand() % mutations.size()]); 
			return true;
		}

		return false;
	}

	stmnt* deepCopy(void) const override {
		stmntAsgn* copy = new stmntAsgn(*this);
		copy->prev = copy;
		copy->setVarRef(static_cast<exprVarRef*>(varRef->deepCopy()));
		copy->setAssign(assign->deepCopy());

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	exprVarRef* varRef;
	expr* assign;
};

//E_STMNT_INCR,		// child[0] = E_VARREF
class stmntIncr : public stmnt
{
public:
	stmntIncr(exprVarRef *varRef, int lineNb)
		: stmnt(astNode::E_STMNT_INCR, lineNb)
	{
		setVarRef(varRef);
	}

	void setVarRef(exprVarRef* varRef) {
		rmChild(this->varRef);
		addChild(varRef);
		this->varRef = varRef;
	}

	operator std::string() const override {
		return std::string(*varRef) + "++;\n";
	}

	std::string getTypeDescr(void) const override {
		return "Increment (E_STMNT_INCR)";
	}

	bool mutateMutable(unsigned int id) override {

		if(varRef->getMId() == id) {
			auto mutations = varRef->getMutations();
			assert(mutations.size());
			setVarRef(static_cast<exprVarRef*>(mutations[rand() % mutations.size()]));
			return true;
		}

		return false;

	}
	
	stmnt* deepCopy(void) const override {
		stmntIncr* copy = new stmntIncr(*this);
		copy->prev = copy;
		copy->setVarRef(static_cast<exprVarRef*>(varRef->deepCopy()));

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	exprVarRef* varRef;
};

//E_STMNT_DECR,		// child[0] = E_VARREF
class stmntDecr : public stmnt
{
public:
	stmntDecr(exprVarRef *varRef, int lineNb)
		: stmnt(astNode::E_STMNT_DECR, lineNb)
	{
		setVarRef(varRef);
	}

	void setVarRef(exprVarRef* varRef) {
		rmChild(this->varRef);
		addChild(varRef);
		this->varRef = varRef;
	}

	operator std::string() const override {
		return std::string(*varRef) + "--;\n";
	}

	std::string getTypeDescr(void) const override {
		return "Decrement (E_STMNT_DECR)";
	}

	bool mutateMutable(unsigned int id) override {

		if(varRef->getMId() == id) {
			auto mutations = varRef->getMutations();
			assert(mutations.size());
			varRef = static_cast<exprVarRef*>(mutations[rand() % mutations.size()]); 
			return true;
		}

		return false;

	}

	stmnt* deepCopy(void) const override {
		stmntDecr* copy = new stmntDecr(*this);
		copy->prev = copy;
		copy->setVarRef(static_cast<exprVarRef*>(varRef->deepCopy()));

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	exprVarRef* varRef;
};

//E_STMNT_EXPR,		// child[0] = E_EXPR_*
class stmntExpr : public stmnt
{
public:
	stmntExpr(expr *child, int lineNb)
		: stmnt(astNode::E_STMNT_EXPR, lineNb)
	{
		this->child = nullptr;
		setChild(child);
	}

	void setChild(expr* child) {
		rmChild(this->child);
		addChild(child);
		this->child = child;
	}

	operator std::string() const override {
		return std::string(*child) + ";\n";
	}

	std::string getTypeDescr(void) const override {
		return "Expression wrapper (E_STMNT_EXPR)";
	}

	bool mutateMutable(unsigned int id) override {

		if(child->getMId() == id) {
			auto mutations = child->getMutations();
			assert(mutations.size());
			setChild(static_cast<exprVarRef*>(mutations[rand() % mutations.size()]));
			return true;
		}

		return false;

	}

	stmnt* deepCopy(void) const override {
		stmntExpr* copy = new stmntExpr(*this);
		copy->prev = copy;
		copy->setChild(child->deepCopy());

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	expr* child;
};

#endif