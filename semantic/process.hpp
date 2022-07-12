#ifndef PROCESS_H
#define PROCESS_H

#include <list>
#include <map>
#include <tuple>
#include <cassert>

#include "scope.hpp"

typedef char byte;

class transition;

#include "symbols.hpp"

class astNode;
class expr;

class fsm;
class fsmNode;
class fsmEdge;

class state;
class payload;

class variable;
class channel;

class exprArgList;
class exprRArgList;


// A state mask gives for every process the pid, a pointer to its symtab node
// and its offset in the payload
class process : public scope {
public:
	process(state* s, const seqSymNode* sym, const fsmNode* start, byte pid, unsigned int index = 0);

	process(state* s, const seqSymNode* sym, const fsmNode* start, byte pid, const std::list<const variable*>& args);

	//process(const process& p);

	//process* deepCopy(void) const;

	std::string getName(void) const;

	symbol::Type getType(void) const;

	void init(void) override;

	byte getPid(void) const;

	void print(void) const override;

	std::list<transition*> transitions(void) const;

	const fsmNode* getFsmNodePointer(void) const;

	void setFsmNodePointer(const fsmNode* pointer);

	bool nullstate(void) const;

	bool endstate(void) const;

	std::list<transition*> executables(void) const;

	//trans or state, signature can be optimized!
	int eval(const fsmEdge* edge, byte flag) const; // Return true <=> transition 'trans' is executable on process 'mask'.

	int eval(const astNode* exp, byte flag) const;

	state* apply(const transition* trans);

	bool isAccepting(void) const;

	bool isAtomic(void) const;
	
	std::string getVarName(const expr* varExpr) const;

	variable* getVariable(const expr* varExpr) const;

	std::list<variable*> getVariables(const exprArgList* args) const;

	std::list<const variable*> getConstVariables(const exprArgList* args) const;

	std::list<variable*> getVariables(const exprRArgList* rargs) const;

	std::list<const variable*> getConstVariables(const exprRArgList* rargs) const;

	channel* getChannel(const expr* varExpr) const;

	template <typename T> T* getTVar(const expr* varExpr, const process* proc) const {
		return dynamic_cast<T*>(getVariable(varExpr));
	}

	void setState(state* newS);

private:
	const seqSymNode* symType;
	unsigned int index;

	state* s;
	byte pid;
	const fsmNode* start;

	mutable bool _else;
};

#endif