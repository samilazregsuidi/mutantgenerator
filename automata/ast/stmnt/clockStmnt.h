#ifndef CLOCK_STMNT_H
#define CLOCK_STMNT_H

#include <iostream>

#include "stmnt.h"

//E_STMNT_WAIT,		// child[0] = E_EXPR_*
class stmntWait : public stmnt
{
public:
	stmntWait(expr *timer, int lineNb)
		: stmnt(astNode::E_STMNT_WAIT, lineNb)
	{
		setTimer(timer);
	}

	void setTimer(expr* timer) {
		rmChild(this->timer);
		addChild(timer);
		this->timer = timer;
	}

	operator std::string() const override{
		return "while ( " + std::string(*timer) + " ) wait;\n";
	}

	std::string getTypeDescr(void) const override{
		return "Time invariant (E_STMNT_WAIT)";
	}

	stmnt* deepCopy(void) const {
		stmntWait* copy = new stmntWait(*this);
		copy->prev = copy;
		copy->setTimer(timer->deepCopy());

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	expr* timer;
};

//E_STMNT_WHEN,		// child[0] = E_EXPR_*, child[1] = E_STMNT_* symTab = clock symbols
class stmntWhen : public stmnt
{
public:
	stmntWhen(expr *guard, stmnt *todo, std::list<varSymNode*> clocks, int lineNb)
		: stmnt(astNode::E_STMNT_WHEN, lineNb)
	{
		this->clocks = clocks;

		setGuard(guard);
		setTodo(todo);
	}
	
	stmntWhen(expr *guard, stmnt *todo, int lineNb)
		: stmnt(astNode::E_STMNT_WHEN, lineNb)
	{
		setGuard(guard);
		setTodo(todo);
	}

	void setGuard(expr* guard) {
		rmChild(this->guard);
		addChild(guard);
		this->guard = guard;
	}

	void setTodo(stmnt* todo) {
		rmChild(this->todo);
		addChild(todo);
		this->todo = todo;
	}

	operator std::string() const override {
		return "when ( " + std::string(*guard) + " ) do " + std::string(*todo) + "\n";
	}

	std::string getTypeDescr(void) const override{
		return "Time guard (E_STMNT_WHEN)";
	}

	stmnt* deepCopy(void) const {
		stmntWhen* copy = new stmntWhen(*this);
		copy->prev = copy;
		copy->setGuard(guard->deepCopy());
		copy->setTodo(todo->deepCopy());

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	expr* guard;
	stmnt* todo;
	std::list<varSymNode*> clocks;
};

#endif
