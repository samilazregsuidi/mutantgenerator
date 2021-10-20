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
		this->timer = timer;
		this->timer->setParent(this);
	}

	~stmntWait() override {
		delete timer;
		if(next)
			delete next;
	}

	operator std::string() const override{
		return "while ( " + std::string(*timer) + " ) wait;\n" 
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override{
		return "Time invariant (E_STMNT_WAIT)";
	}

	stmnt* deepCopy(void) const {
		stmntWait* copy = new stmntWait(*this);
		copy->prev = copy;
		copy->timer = timer->deepCopy();

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
	stmntWhen(expr *guard, stmnt *todo, int lineNb, std::list<symbol*> clocks)
		: stmnt(astNode::E_STMNT_WHEN, lineNb)
	{
		this->guard = guard;
		this->todo = todo;
		this->clocks = clocks;

		this->guard->setParent(this);
		this->todo->setParent(this);
	}

	~stmntWhen() override {
		delete guard;
		delete todo;
		if(next)
			delete next;
	}

	operator std::string() const override{
		return "when ( " + std::string(*guard) + " ) do " + std::string(*todo) + "\n" 
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override{
		return "Time guard (E_STMNT_WHEN)";
	}

	stmnt* deepCopy(void) const {
		stmntWhen* copy = new stmntWhen(*this);
		copy->prev = copy;
		copy->guard = guard->deepCopy();
		copy->todo = todo->deepCopy();

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	expr* guard;
	stmnt* todo;
	std::list<symbol*> clocks;
};

#endif