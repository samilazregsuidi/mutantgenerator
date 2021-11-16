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
		, toPrint(toPrint)
		, argList(nullptr)
	{
		setArgList(argList);
	}

	virtual ~stmntPrint() {
		delete argList;
	}

	void setArgList(exprArgList* argList) {
		rmChild(this->argList);
		addChild(argList);
		this->argList = argList;
	}

	operator std::string() const override{
		return "printf(" + '\"' + toPrint + '\"' + (argList? std::string(*argList) : ", ") + ");\n";
	}

	std::string getTypeDescr(void) const override{
		return "Print (E_STMNT_PRINT)";
	}

	stmnt* deepCopy(void) const {
		stmntPrint* copy = new stmntPrint(*this);
		copy->prev = copy;
		copy->setArgList(dynamic_cast<exprArgList*>(argList->deepCopy()));

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
		, varRef(nullptr)
	{
		setVarRef(varRef);
	}

	stmntPrintm(int constant, int lineNb)
		: stmnt(astNode::E_STMNT_PRINTM,  lineNb)
	{
		this->constant = constant;
	}

	virtual ~stmntPrintm() {
		delete varRef;
	}

	void setVarRef(exprVarRef* varRef) {
		rmChild(this->varRef);
		addChild(varRef);
		this->varRef = varRef;
	}

	operator std::string() const override{
		return "printm("+(varRef ? std::string(*varRef) : std::to_string(constant)) + ");\n";
	}

	std::string getTypeDescr(void) const override{
		return "PrintM (E_STMNT_PRINTM)";
	}

	stmnt* deepCopy(void) const {
		stmntPrintm* copy = new stmntPrintm(*this);
		copy->prev = copy;
		copy->setVarRef(dynamic_cast<exprVarRef*>(varRef->deepCopy()));

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
		, toAssert(nullptr)
	{
		setToAssert(toAssert);
	}

	virtual ~stmntAssert() {
		delete toAssert;
	}
	
	void setToAssert(expr* toAssert) {
		rmChild(this->toAssert);
		addChild(toAssert);
		this->toAssert = toAssert;
	}

	operator std::string() const override {
		return "assert(" + std::string(*toAssert) + ");\n";
	}

	std::string getTypeDescr(void) const override{
		return "Assertion (E_STMNT_ASSERT)";
	}

	stmnt* deepCopy(void) const {
		stmntAssert* copy = new stmntAssert(*this);
		copy->prev = copy;
		copy->setToAssert(toAssert->deepCopy());

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	expr* toAssert;
};

#endif