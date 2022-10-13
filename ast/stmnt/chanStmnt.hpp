#ifndef CHAN_STMNT_H
#define CHAN_STMNT_H

#include <iostream>

#include "stmnt.hpp"
#include "argExpr.hpp"

class stmntChan : public stmnt 
{
protected:
	stmntChan(Type type, exprVarRef *chan, int lineNb);

public:	
	void setChan(exprVarRef* chan);

	exprVarRef* getChan() const;
};

//E_STMNT_CHAN_RCV,	// child[0] = E_VARREF, child[1] = E_EXPR_*
class stmntChanRecv : public stmntChan
{
public:
	stmntChanRecv(exprVarRef *chan, exprRArgList *argList, int lineNb);

	void setRArgList(exprRArgList* argList);

	exprRArgList* getRArgList() const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;
};

//E_STMNT_CHAN_SND,	// child[0] = E_VARREF, child[1] = E_EXPR_*
class stmntChanSnd : public stmntChan
{
public:
	stmntChanSnd(exprVarRef *chan, exprArgList *argList, int lineNb);
	
	void setArgList(exprArgList* argList);

	exprArgList* getArgList() const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;
};

#endif