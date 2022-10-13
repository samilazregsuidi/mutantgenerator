#ifndef CLOCK_STMNT_H
#define CLOCK_STMNT_H

#include <iostream>

#include "stmnt.hpp"

//E_STMNT_WAIT,		// child[0] = E_EXPR_*
class stmntWait : public stmnt
{
public:
	stmntWait(expr *timer, int lineNb);

	void setTimer(expr* timer);

	expr* getTimer() const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;
};

//E_STMNT_WHEN,		// child[0] = E_EXPR_*, child[1] = E_STMNT_* symTab = clock symbols
class stmntWhen : public stmnt
{
public:
	stmntWhen(expr *guard, stmnt *todo, std::list<varSymNode*> clocks, int lineNb);
	
	stmntWhen(expr *guard, stmnt *todo, int lineNb);

	void setGuard(expr* guard);

	expr* getGuard() const;

	void setTodo(stmnt* todo);

	expr* getTodo() const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;

private:
	std::list<varSymNode*> clocks;
};

#endif
