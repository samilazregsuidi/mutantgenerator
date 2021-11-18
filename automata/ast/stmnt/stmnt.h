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
		, local(nullptr)
		, next(nullptr)
		, prev(this)
	{}

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
		, block(nullptr)
	{
		setBlock(block);
		//std::cout << "SEQ : line " << lineNb << " _ " << std::string(*this) << "\n";
	}

	virtual ~stmntSeq() {
		delete block;
	}

public:
	stmntSeq(stmnt* block, int lineNb)
		: stmnt(astNode::E_STMNT_SEQ, lineNb)
		, block(nullptr)
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
		, varRef(nullptr)
		, assign(nullptr)
	{
		setVarRef(varRef);
		setAssign(assign);

		assign->setExprType(varRef->getExprType());
	}

	virtual ~stmntAsgn() {
		delete varRef;
		delete assign;
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
		return (varRef ? std::string(*varRef) : "nullptr") + " = " + (assign ? std::string(*assign) : "nullptr") + ";\n";
	}

	std::string getTypeDescr(void) const override{
		return "Assignment (E_STMNT_ASGN)";
	}

	bool mutateMutable(unsigned int id) override {

		if(varRef->getMId() == id) {
			auto mutations = varRef->getMutations();
			assert(mutations.size());
			int debug = rand() % mutations.size();
			auto ddebug = dynamic_cast<exprVarRef*>(mutations[debug]);
			mutations.erase(mutations.begin() + debug);
			for(auto i : mutations) delete i;
			setVarRef(ddebug);
			return true;
		}

		if(assign->getMId() == id) {
			auto mutations = assign->getMutations();
			if(mutations.size() == 0){
				assert(mutations.size());
			}
			size_t i = rand() % mutations.size();
			setAssign(mutations[i]);
			mutations.erase(mutations.begin() + i);
			for(auto i : mutations) delete i;
			return true;
		}

		return false;
	}

	stmnt* deepCopy(void) const override {
		stmntAsgn* copy = new stmntAsgn(*this);
		copy->prev = copy;
		copy->setVarRef(dynamic_cast<exprVarRef*>(varRef->deepCopy()));
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
		, varRef(nullptr)
	{
		setVarRef(varRef);
	}

	virtual ~stmntIncr(void) {
		delete varRef;
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
			size_t i = rand() % mutations.size();
			setVarRef(dynamic_cast<exprVarRef*>(mutations[i]));
			mutations.erase(mutations.begin() + i);
			for(auto i : mutations) delete i;
			return true;
		}

		return false;

	}
	
	stmnt* deepCopy(void) const override {
		stmntIncr* copy = new stmntIncr(*this);
		copy->prev = copy;
		copy->setVarRef(dynamic_cast<exprVarRef*>(varRef->deepCopy()));

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
		, varRef(nullptr)
	{
		setVarRef(varRef);
	}

	virtual ~stmntDecr() {
		delete varRef;
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
			size_t i = rand() % mutations.size();
			varRef = dynamic_cast<exprVarRef*>(mutations[i]); 
			mutations.erase(mutations.begin() + i);
			for(auto i : mutations) delete i;
			return true;
		}

		return false;

	}

	stmnt* deepCopy(void) const override {
		stmntDecr* copy = new stmntDecr(*this);
		copy->prev = copy;
		copy->setVarRef(dynamic_cast<exprVarRef*>(varRef->deepCopy()));

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
		, child(nullptr)
	{
		setChild(child);
	}

	virtual ~stmntExpr() {
		delete child;
	}

	void setChild(expr* child) {
		rmChild(this->child);
		addChild(child);
		this->child = child;
	}

	operator std::string() const override {
		return (child ? std::string(*child) : "nullptr") + ";\n";
	}

	std::string getTypeDescr(void) const override {
		return "Expression wrapper (E_STMNT_EXPR)";
	}

	bool mutateMutable(unsigned int id) override {

		if(child->getMId() == id) {
			auto mutations = child->getMutations();
			assert(mutations.size());
			size_t i = rand() % mutations.size();
			auto tmp = mutations[i];
			auto mutation = dynamic_cast<exprVarRef*>(tmp);
			mutations.erase(mutations.begin() + i);
			for(auto i : mutations) {
				i->clearChildren();
				delete i;
			}
			setChild(mutation);
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
