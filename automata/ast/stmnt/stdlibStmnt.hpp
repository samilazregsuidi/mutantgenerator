#ifndef STDLIB_STMNT_H
#define STDLIB_STMNT_H

#include <iostream>

#include "stmnt.hpp"
#include "argExpr.hpp"

//E_STMNT_PRINT,		// child[0] = E_ARGLIST, sVal = the print string
class stmntPrint : public stmnt
{
public:
	stmntPrint(const std::string &toPrint, exprArgList *argList, int lineNb);

	void setArgList(exprArgList* argList);

	exprArgList* getArgList() const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;

private:
	std::string toPrint;
};

//E_STMNT_PRINTM,		// child[0] = E_VARREF, or iVal = constant
class stmntPrintm : public stmnt
{
public:
	stmntPrintm(exprVarRef *varRef, int lineNb);

	stmntPrintm(int constant, int lineNb);

	void setVarRef(exprVarRef* varRef);

	exprVarRef* getVarRef() const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;

private:
	int constant;
};

//E_STMNT_ASSERT,		// child[0] = E_EXPR_*
class stmntAssert : public stmnt
{
public:
	stmntAssert(expr *toAssert, int lineNb);

	void setToAssert(expr* toAssert);

	expr* getToAssert() const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;
};

#endif