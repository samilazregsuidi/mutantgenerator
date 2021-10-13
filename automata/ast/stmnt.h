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

	//virtual unsigned int processVariables(symTable* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal) const;

	/*void resolveVariables(symTable* global = nullptr) override {
		if(next) next->resolveVariables(global);
	}*/

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
	/*void resolveVariables(symTable* globalSymTab = nullptr) override {	
		block->resolveVariables(local);
		if(next) next->resolveVariables(local);
	}*/

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

	operator std::string() const override{
		return "atomic " + stmntSeq::operator std::string()
		+ (next? _tab() + std::string(*next) : ""); 
	}

	std::string getTypeDescr(void) const override{
		return "Atomic (E_STMNT_ATOMIC)";
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

	/*void resolveVariables(symTable* globalSymTab = nullptr) override {
		varRef->resolveVariables(local);
		assign->resolveVariables(local);
		if(next) next->resolveVariables(globalSymTab);
	}*/

	operator std::string() const override{
		return std::string(*varRef) + " = " + std::string(*assign) + ";\n" 
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override{
		return "Assignment (E_STMNT_ASGN)";
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

	/*void resolveVariables(symTable* globalSymTab = nullptr) override {	
		varRef->resolveVariables(local);
		if(next) next->resolveVariables(local);
	}*/

	operator std::string() const override{
		return std::string(*varRef) + "++;\n" 
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override{
		return "Increment (E_STMNT_INCR)";
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

	/*void resolveVariables(symTable* globalSymTab = nullptr) override {	
		varRef->resolveVariables(local);
		if(next) next->resolveVariables(local);
	}*/

	operator std::string() const override{
		return std::string(*varRef) + "--;\n" 
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override{
		return "Decrement (E_STMNT_DECR)";
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

	/*void resolveVariables(symTable* globalSymTab = nullptr) override {
		child->resolveVariables(local);
		if(next) next->resolveVariables(local);
	}*/

	operator std::string() const override{
		return std::string(*child) + ";\n"
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override{
		return "Expression wrapper (E_STMNT_EXPR)";
	}

private:
	expr* child;
};

#endif