#ifndef STDLIB_STMNT_H
#define STDLIB_STMNT_H

#include <iostream>

#include "stmnt.h"
#include "argExpr.h"

//E_STMNT_PRINT,		// child[0] = E_ARGLIST, sVal = the print string
class stmntPrint : public stmnt
{
public:
	stmntPrint(const std::string &toPrint, exprArgList *argList, int lineNb)
		: stmnt(astNode::E_STMNT_PRINT, lineNb)
	{
		this->toPrint = toPrint;
		this->argList = argList;

		this->argList->setParent(this);
	}

	~stmntPrint() override {
		delete argList;
		if(next)
			delete next;
	}

	operator std::string() const override{
		return "printf(" + '\"' + toPrint + '\"' + (argList? std::string(*argList) : ", ") + ");\n" 
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override{
		return "Print (E_STMNT_PRINT)";
	}

	stmnt* deepCopy(void) const {
		stmntPrint* copy = new stmntPrint(*this);
		copy->prev = copy;
		copy->argList = static_cast<exprArgList*>(argList->deepCopy());

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
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

		this->varRef->setParent(this);
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

	operator std::string() const override{
		return "printm("+(varRef ? std::string(*varRef) : std::to_string(constant)) + ");\n" 
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override{
		return "PrintM (E_STMNT_PRINTM)";
	}

	stmnt* deepCopy(void) const {
		stmntPrintm* copy = new stmntPrintm(*this);
		copy->prev = copy;
		copy->varRef = static_cast<exprVarRef*>(varRef->deepCopy());

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
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

		this->toAssert->setParent(this);
	}

	~stmntAssert() override {
		delete toAssert;
		if(next)
			delete next;
	}

	operator std::string() const override{
		return "assert(" + std::string(*toAssert) + ");\n" 
		+ (next? _tab() + std::string(*next) : "") ;
	}

	std::string getTypeDescr(void) const override{
		return "Assertion (E_STMNT_ASSERT)";
	}

	stmnt* deepCopy(void) const {
		stmntAssert* copy = new stmntAssert(*this);
		copy->prev = copy;
		copy->toAssert = toAssert->deepCopy();

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	expr* toAssert;
};

#endif