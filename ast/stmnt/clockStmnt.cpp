#include "clockStmnt.hpp"

stmntWait::stmntWait(expr *timer, int lineNb)
		: stmnt(astNode::E_STMNT_WAIT, lineNb)
{
    assert(timer);
    addChild("timer", timer);
}

void stmntWait::setTimer(expr* timer) {
    eraseChild("timer", timer);
}

expr* stmntWait::getTimer() const {
    return dynamic_cast<expr*>(getChild("timer"));
}

stmntWait::operator std::string() const {
    assert(getTimer());
    return "while ( " + std::string(*getTimer()) + " ) wait;\n";
}

std::string stmntWait::getTypeDescr(void) const {
    return "Time invariant (E_STMNT_WAIT)";
}

stmnt* stmntWait::deepCopy(void) const {
    stmntWait* copy = new stmntWait(*this);
    copy->prev = copy;
    copy->copyChildren(*this);
    if(copy->getNext())
        return stmnt::merge(copy, getNext()->deepCopy());
    return copy;
}

/*********************************************************************************/

stmntWhen::stmntWhen(expr *guard, stmnt *todo, std::list<varSymNode*> clocks, int lineNb)
		: stmnt(astNode::E_STMNT_WHEN, lineNb)
		, clocks(clocks)
{
    assert(guard);
    assert(todo);
    addChild("guard", guard);
    addChild("todo", todo);
}

stmntWhen::stmntWhen(expr *guard, stmnt *todo, int lineNb)
    : stmnt(astNode::E_STMNT_WHEN, lineNb)
{
    assert(guard);
    assert(todo);
    addChild("guard", guard);
    addChild("todo", todo);
}

void stmntWhen::setGuard(expr* guard) {
    eraseChild("guard", guard);
}

expr* stmntWhen::getGuard() const {
    return dynamic_cast<expr*>(getChild("guard"));
}

void stmntWhen::setTodo(stmnt* todo) {
    eraseChild("todo", todo);
}

expr* stmntWhen::getTodo() const {
    return dynamic_cast<expr*>(getChild("todo"));
}

stmntWhen::operator std::string() const {
    assert(getGuard() && getTodo());
    return "when ( " + std::string(*getGuard()) + " ) do " + std::string(*getTodo()) + "\n";
}

std::string stmntWhen::getTypeDescr(void) const {
    return "Time guard (E_STMNT_WHEN)";
}

stmnt* stmntWhen::deepCopy(void) const {
    stmntWhen* copy = new stmntWhen(*this);
    copy->prev = copy;
    copy->copyChildren(*this);
    if(copy->getNext())
        return stmnt::merge(copy, getNext()->deepCopy());
    return copy;
}