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

//E_STMNT_CHAN_RCV,	// child[0] = E_VARREF, child[1] = E_EXPR_*
class stmntChanRecv : public stmnt
{
public:
	stmntChanRecv(exprVarRef *chan, exprArgList *argList, int lineNb)
		: stmnt(astNode::E_STMNT_CHAN_RCV, lineNb)
	{
		this->chan = chan;
		this->argList = argList;
	}
	
	~stmntChanRecv() override {
		delete chan;
		delete argList;
		if(next)
			delete next;
	}

	/*void resolveVariables(symTable* globalSymTab = nullptr) override {
		chan->resolveVariables(local);
		argList->resolveVariables(local);
		if(next) next->resolveVariables(local);
	}*/

	/*std::list<std::string> getVars(const symTabNode *globalSymTab, const symTabNode *processSymTab, const mTypeList *mtypes) const
	{
		return child[1]->getVars(globalSymTab, processSymTab, mtypes);
	}*/

	operator std::string() const
	{
		return std::string(*chan) + " ? " + ( argList? std::string(*argList) : "") + ";\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void) const
	{
		return "Channel receive (E_STMNT_CHAN_RCV)";
	}

private:
	exprVarRef* chan;
	exprArgList* argList;
};

//E_STMNT_CHAN_SND,	// child[0] = E_VARREF, child[1] = E_EXPR_*
class stmntChanSnd : public stmnt
{
public:
	stmntChanSnd(exprVarRef *chan, exprArgList *argList, int lineNb)
		: stmnt(astNode::E_STMNT_CHAN_SND, lineNb)
	{
		this->chan = chan;
		this->argList = argList;
	}

	~stmntChanSnd() override {
		delete chan;
		delete argList;
		if(next)
			delete next;
	}

	/*void resolveVariables(symTable* globalSymTab = nullptr) override {
		chan->resolveVariables(local);
		argList->resolveVariables(local);
		if(next) next->resolveVariables(local);
	}*/

	operator std::string() const
	{
		return std::string(*chan) + " ! " + ( argList? std::string(*argList) : "") + ";\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void) const
	{
		return "Channel send (E_STMNT_CHAN_SND)";
	}

private:
	exprVarRef* chan;
	exprArgList* argList;
};

//E_STMNT_OPT,		// child[0] = E_STMNT_OPT (next option; or NULL), fsm = fsm of this option
class stmntOpt : public stmnt
{
public:
	stmntOpt(stmnt* block, stmntOpt *nextOpt, int lineNb)
		: stmnt(astNode::E_STMNT_OPT, lineNb)
	{
		this->block = block;
		this->nextOpt = nextOpt;
	}

	stmntOpt(stmnt* block, int lineNb)
		: stmnt(astNode::E_STMNT_OPT, lineNb)
	{
		this->block = block;
		this->nextOpt = nullptr;
	}

	~stmntOpt() override {
		delete block;
		if(nextOpt)
			delete nextOpt;
		if (next)
			delete next;
	}

	/*void resolveVariables(symTable* globalSymTab = nullptr) override {
		block->resolveVariables(local);
		nextOpt->resolveVariables(local);
		if(next) next->resolveVariables(local);
	}*/

	operator std::string() const
	{
		return "::" + std::string(*block) + (nextOpt? std::string(*nextOpt) : "") + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void) const
	{
		return "Opt (E_STMNT_OPT)";
	}

private:
	stmnt* block;
	stmntOpt* nextOpt;
};

//E_STMNT_IF,			// child[0] = E_STMNT_OPT (contains an fsm)
class stmntIf : public stmnt
{
public:
	stmntIf(stmntOpt *opts, int lineNb)
		: stmnt(astNode::E_STMNT_IF, lineNb)
	{
		this->opts = opts;
	}

	~stmntIf() override {
		if(opts)
			delete opts;
		if (next)
			delete next;
	}

	/*void resolveVariables(symTable* globalSymTab = nullptr) override {
		opts->resolveVariables(local);
		if(next) next->resolveVariables(local);
	}*/

	operator std::string() const
	{
		return "if\n" + std::string(*opts) + "\nfi;\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void) const
	{
		return "If (E_STMNT_IF)";
	}

private:
	stmntOpt* opts;
};

//E_STMNT_DO,			// child[0] = E_STMNT_OPT (contains an fsm)
class stmntDo : public stmnt
{
public:
	stmntDo(stmntOpt *opts, int lineNb)
		: stmnt(astNode::E_STMNT_DO, lineNb)
	{
		this->opts = opts;
	}

	~stmntDo() override {
		if(opts)
			delete opts;
		if (next)
			delete next;
	}

	/*void resolveVariables(symTable* globalSymTab = nullptr) override {
		opts->resolveVariables(local);
		if(next) next->resolveVariables(local);
	}*/

	operator std::string() const
	{
		return "do\n" + std::string(*opts) + "\nod;\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void) const
	{
		return "Do (E_STMNT_DO)";
	}

private:
	stmntOpt* opts;
};

//E_STMNT_BREAK,		// empty
class stmntBreak : public stmnt
{
public:
	stmntBreak(int lineNb)
		: stmnt(astNode::E_STMNT_BREAK, lineNb)
	{
	}

	operator std::string() const
	{
		return "break;\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void) const
	{
		return "Break (E_STMNT_BREAK)";
	}
};

//E_STMNT_GOTO,		// sVal = the label to go to
class stmntGoto : public stmnt
{
public:
	stmntGoto(const std::string& label, int lineNb)
		: stmnt(astNode::E_STMNT_GOTO, lineNb)
	{
		this->label = label;
	}

	operator std::string() const
	{
		return "goto " + label + ";\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void) const
	{
		return "Goto (E_STMNT_GOTO)";
	}
	
	std::string getLabel(void) const {
		return label;
	}

private:
	std::string label;
};

//E_STMNT_LABEL,		// child[0] = E_STMNT_*, sVal = the label of child[0]
class stmntLabel : public stmnt
{
public:
	stmntLabel(const std::string& label, stmnt *labelled, int lineNb)
		: stmnt(astNode::E_STMNT_LABEL, lineNb)
	{
		this->label = label;
		this->labelled = labelled;
	}

	~stmntLabel() override {
		delete labelled;
		if (next)
			delete next;
	}

	operator std::string() const
	{
		return label + ": \n" + std::string(*labelled) + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void) const
	{
		return "Label (E_STMNT_LABEL)";
	}

	std::string getLabel(void) const {
		return label;
	}

	stmnt* getLabelledStmnt(void) const {
		return labelled;
	}

private:
	std::string label;
	stmnt* labelled;
};

//E_STMNT_SEQ,		// fsm = fsm of this sequence
class stmntSeq : public stmnt
{
public:
	stmntSeq(stmnt* block, int lineNb)
		: stmnt(astNode::E_STMNT_SEQ, lineNb)
	{
		this->block = block;
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

	operator std::string() const
	{
		return "{\n" + std::string(*block) + "};\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void) const
	{
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

	operator std::string() const{
		std::string res = "atomic " + stmntSeq::operator std::string();
		return next? res + std::string(*next) : res; 
	}

	std::string getTypeDescr(void) const{
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

	operator std::string() const{
		return std::string(*varRef) + " = " + std::string(*assign) + ";\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void) const{
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

	operator std::string() const{
		return std::string(*varRef) + "++;\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void) const{
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

	operator std::string() const{
		return std::string(*varRef) + "--;\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void) const{
		return "Decrement (E_STMNT_DECR)";
	}

private:
	exprVarRef* varRef;
};

//E_STMNT_PRINT,		// child[0] = E_ARGLIST, sVal = the print string
class stmntPrint : public stmnt
{
public:
	stmntPrint(const std::string &toPrint, exprArgList *argList, int lineNb)
		: stmnt(astNode::E_STMNT_PRINT, lineNb)
	{
		this->toPrint = toPrint;
		this->argList = argList;
	}

	~stmntPrint() override {
		delete argList;
		if(next)
			delete next;
	}

	/*void resolveVariables(symTable* globalSymTab = nullptr) override {	
		argList->resolveVariables(local);
		if(next) next->resolveVariables(local);
	}*/

	operator std::string() const{
		return "printf(" + toPrint + (argList? std::string(*argList) : "") + ");\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void) const{
		return "Print (E_STMNT_PRINT)";
	}
private:
	std::string toPrint;
	exprArgList* argList;
};

//E_STMNT_PRINTM,		// child[0] = E_VARREF, or iVal = constant
class stmntPrintm : public stmnt
{
public:
	stmntPrintm(exprVarRef *varRef, int lineNb)
		: stmnt(astNode::E_STMNT_PRINTM, lineNb)
	{
		this->varRef = varRef;
	}

	stmntPrintm(int constant, int lineNb)
		: stmnt(astNode::E_STMNT_PRINTM,  lineNb)
	{
		this->varRef = nullptr;
		this->constant = constant;
	}

	~stmntPrintm() override {
		delete varRef;
		if(next)
			delete next;
	}

	/*void resolveVariables(symTable* globalSymTab = nullptr) override {
		varRef->resolveVariables(local);
		if(next) next->resolveVariables(local);
	}*/

	operator std::string() const{
		return "printm("+(varRef ? std::string(*varRef) : std::to_string(constant)) + ");\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void) const{
		return "PrintM (E_STMNT_PRINTM)";
	}

private:
	exprVarRef* varRef;
	int constant;
};

//E_STMNT_ASSERT,		// child[0] = E_EXPR_*
class stmntAssert : public stmnt
{
public:
	stmntAssert(expr *toAssert, int lineNb)
		: stmnt(astNode::E_STMNT_ASSERT, lineNb)
	{
		this->toAssert = toAssert;
	}

	~stmntAssert() override {
		delete toAssert;
		if(next)
			delete next;
	}

	/*void resolveVariables(symTable* globalSymTab = nullptr) override {	
		toAssert->resolveVariables(local);
		if(next) next->resolveVariables(local);
	}*/

	operator std::string() const{
		return "assert(" + std::string(*toAssert) + ");\n" + (next? std::string(*next) : "") ;
	}

	std::string getTypeDescr(void) const{
		return "Assertion (E_STMNT_ASSERT)";
	}

private:
	expr* toAssert;
};

//E_STMNT_EXPR,		// child[0] = E_EXPR_*
class stmntExpr : public stmnt
{
public:
	stmntExpr(expr *child, int lineNb)
		: stmnt(astNode::E_STMNT_CHAN_RCV, lineNb)
	{
		this->child = child;
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

	operator std::string() const{
		return *child;
	}

	std::string getTypeDescr(void) const{
		return "Expression wrapper (E_STMNT_EXPR)";
	}

private:
	expr* child;
};

//E_STMNT_ELSE,		// empty
class stmntElse : public stmnt
{
public:
	stmntElse(int lineNb)
		: stmnt(astNode::E_STMNT_ELSE, lineNb)
	{
	}

	operator std::string() const{
		return "else -> " + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void) const{
		return "Else (E_STMNT_ELSE)";
	}
};

//E_STMNT_WAIT,		// child[0] = E_EXPR_*
class stmntWait : public stmnt
{
public:
	stmntWait(expr *timer, int lineNb)
		: stmnt(astNode::E_STMNT_WAIT, lineNb)
	{
		this->timer = timer;
	}

	~stmntWait() override {
		delete timer;
		if(next)
			delete next;
	}

	/*void resolveVariables(symTable* globalSymTab = nullptr) override {	
		timer->resolveVariables(local);
		if(next) next->resolveVariables(local);
	}*/

	operator std::string() const{
		return "while ( " + std::string(*timer) + " ) wait;\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void) const{
		return "Time invariant (E_STMNT_WAIT)";
	}

private:
	expr* timer;
};

//E_STMNT_WHEN,		// child[0] = E_EXPR_*, child[1] = E_STMNT_* symTab = clock symbols
class stmntWhen : public stmnt
{
public:
	stmntWhen(expr *guard, stmnt *todo, int lineNb, std::list<symbol*> clocks)
		: stmnt(astNode::E_STMNT_WHEN, lineNb)
	{
		this->guard = guard;
		this->todo = todo;
		this->clocks = clocks;
	}

	~stmntWhen() override {
		delete guard;
		delete todo;
		if(next)
			delete next;
	}

	/*void resolveVariables(symTable* globalSymTab = nullptr) override {	
		guard->resolveVariables(local);
		todo->resolveVariables(local);
		if(next) next->resolveVariables(globalSymTab);
	}*/

	operator std::string() const{
		return "when ( " + std::string(*guard) + " ) do " + std::string(*todo) + "\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void) const{
		return "Time guard (E_STMNT_WHEN)";
	}

private:
	expr* guard;
	stmnt* todo;
	std::list<symbol*> clocks;
};

#endif