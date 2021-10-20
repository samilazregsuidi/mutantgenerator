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
	~stmnt() override {
		if(next)
			delete next;
	}

	static stmnt* merge(stmnt* list, stmnt* node);

	//called for non mutable stmnts (e.g., vardecl)
	unsigned int assignMutables(const Mask& mask = Mask(), unsigned int id = 0) override {
		return (next? next->assignMutables(mask, id) : id);
	}

	void mutateMutable(unsigned int id) override {
		if (next)
			next->mutateMutable(id);
	}

	void setLocalSymTab(symTable* local) {
		this->local = local;
		if(next)
			next->setLocalSymTab(local);
	}

	symTable* getLocalSymTab(void) const {
		return local;
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
public:
	stmntSeq(stmnt* block, int lineNb)
		: stmnt(astNode::E_STMNT_SEQ, lineNb)
	{
		this->block = block;

		this->block->setParent(this);
	}

	~stmntSeq() override {
		delete block;
		if(next)
			delete next;
	}

protected:
	stmntSeq(Type type, stmnt* block, int lineNb)
		: stmnt(type, lineNb)
	{
		this->block = block;
	}

public:

	operator std::string() const override {
		std::string res = "{\n";
		tab_lvl++;
		res += _tab() + std::string(*block);
		tab_lvl--;
		res += _tab() + "};\n"; 
		return res + (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override {
		return "Seq (E_STMNT_SEQ)";
	}

	unsigned int assignMutables(const Mask& mask, unsigned int id = 0) override {
		if(mask.isPresent(type))
			id = block->assignMutables(mask, id);
		return (next? next->assignMutables(mask, id) : id);
	}

	void mutateMutable(unsigned int id) override {

		block->mutateMutable(id);

		if(next) 
			next->mutateMutable(id);

	}

	stmnt* deepCopy(void) const {
		stmntSeq* copy = new stmntSeq(*this);
		copy->prev = copy;
		copy->block = block->deepCopy();
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
	{}

	operator std::string() const override {
		return "atomic " + stmntSeq::operator std::string()
		+ (next? _tab() + std::string(*next) : ""); 
	}

	std::string getTypeDescr(void) const override {
		return "Atomic (E_STMNT_ATOMIC)";
	}

	stmnt* deepCopy(void) const {
		stmntAtomic* copy = new stmntAtomic(*this);
		copy->prev = copy;
		copy->block = block->deepCopy();
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
		this->varRef = varRef;
		this->assign = assign;

		this->varRef->setParent(this);
		this->assign->setParent(this);
	}

	~stmntAsgn() override {
		delete varRef;
		delete assign;
		if(next)
			delete next;
	}

	operator std::string() const override{
		return std::string(*varRef) + " = " + std::string(*assign) + ";\n" 
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override{
		return "Assignment (E_STMNT_ASGN)";
	}

	unsigned int assignMutables(const Mask& mask, unsigned int id = 0) override {
		if(mask.isPresent(type)) {
			id = varRef->assignMutables(mask, id);
			id = assign->assignMutables(mask, id);
		}
		return + (next? next->assignMutables(mask, id) : id);
	}

	void mutateMutable(unsigned int id) override {

		if(varRef->getMId() == id) {
			auto mutations = varRef->getMutations();
			assert(mutations.size());
			delete varRef;
			int debug = rand() % mutations.size();
			auto ddebug = static_cast<exprVarRef*>(mutations[debug]);
			varRef = ddebug;
			return;
		}

		if(assign->getMId() == id) {
			auto mutations = assign->getMutations();
			assert(mutations.size());
			delete assign;
			assign = mutations[rand() % mutations.size()]; 
			return;
		}

		varRef->mutateMutable(id);
		assign->mutateMutable(id);

		if(next) 
			next->mutateMutable(id);	

	}

	stmnt* deepCopy(void) const {
		stmntAsgn* copy = new stmntAsgn(*this);
		copy->prev = copy;
		copy->varRef = static_cast<exprVarRef*>(varRef->deepCopy());
		copy->assign = assign->deepCopy();

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
		this->varRef = varRef;

		this->varRef->setParent(this);
	}

	~stmntIncr() override {
		delete varRef;
		if(next)
			delete next;
	}

	operator std::string() const override {
		return std::string(*varRef) + "++;\n" 
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override {
		return "Increment (E_STMNT_INCR)";
	}

	unsigned int assignMutables(const Mask& mask, unsigned int id = 0) override {
		if(mask.isPresent(type))
			id = varRef->assignMutables(mask, id);
		return (next? next->assignMutables(mask, id) : id);
	}

	void mutateMutable(unsigned int id) override {

		if(varRef->getMId() == id) {
			auto mutations = varRef->getMutations();
			assert(mutations.size());
			delete varRef;
			varRef = static_cast<exprVarRef*>(mutations[rand() % mutations.size()]); 
			return;
		}

		varRef->mutateMutable(id);

		if(next) 
			next->mutateMutable(id);

	}
	
	stmnt* deepCopy(void) const {
		stmntIncr* copy = new stmntIncr(*this);
		copy->prev = copy;
		copy->varRef = static_cast<exprVarRef*>(varRef->deepCopy());

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
		this->varRef = varRef;

		this->varRef->setParent(this);
	}

	~stmntDecr() override {
		delete varRef;
		if(next)
			delete next;
	}

	operator std::string() const override {
		return std::string(*varRef) + "--;\n" 
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override {
		return "Decrement (E_STMNT_DECR)";
	}

	unsigned int assignMutables(const Mask& mask, unsigned int id = 0) override {
		if(mask.isPresent(type))
			id = varRef->assignMutables(mask, id);
		return (next? next->assignMutables(mask, id) : id);
	}

	void mutateMutable(unsigned int id) override {

		if(varRef->getMId() == id) {
			auto mutations = varRef->getMutations();
			assert(mutations.size());
			delete varRef;
			varRef = static_cast<exprVarRef*>(mutations[rand() % mutations.size()]); 
			return;
		}

		varRef->mutateMutable(id);

		if(next) 
			next->mutateMutable(id);

	}

	stmnt* deepCopy(void) const {
		stmntDecr* copy = new stmntDecr(*this);
		copy->prev = copy;
		copy->varRef = static_cast<exprVarRef*>(varRef->deepCopy());

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
		this->child = child;
		this->child->setParent(this);
	}

	~stmntExpr() override {
		delete child;
		if(next)
			delete next;
	}

	operator std::string() const override{
		return std::string(*child) + ";\n"
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override{
		return "Expression wrapper (E_STMNT_EXPR)";
	}

	unsigned int assignMutables(const Mask& mask, unsigned int id = 0) override {
		if(mask.isPresent(type))
			id = child->assignMutables(mask, id);
		return (next? next->assignMutables(mask, id) : id);
	}

	void mutateMutable(unsigned int id) override {

		if(child->getMId() == id) {
			auto mutations = child->getMutations();
			assert(mutations.size());
			delete child;
			child = static_cast<exprVarRef*>(mutations[rand() % mutations.size()]); 
			return;
		}

		child->mutateMutable(id);

		if(next) 
			next->mutateMutable(id);

	}

	stmnt* deepCopy(void) const {
		stmntExpr* copy = new stmntExpr(*this);
		copy->prev = copy;
		copy->child = child->deepCopy();

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	expr* child;
};

#endif