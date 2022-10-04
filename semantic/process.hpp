#ifndef PROCESS_STATE_H
#define PROCESS_STATE_H

#include <list>
#include <map>
#include <tuple>
#include <cassert>

#include "state.hpp"

#include "scope.hpp"

typedef char byte;

class progState;
class transition;
class RVTransition;

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
class process : public scope, public state {
public:
	friend class state;

	process(progState* s, const seqSymNode* sym, const fsmNode* start, byte pid, unsigned int index = 0);

	process(progState* s, const seqSymNode* sym, const fsmNode* start, byte pid, const std::list<const variable*>& args);

	process* deepCopy(void) const override;

	symbol::Type getType(void) const;

	void init(void) override;

	byte getPid(void) const;

	void print(void) const override;

	std::list<transition*> transitions(void) const;

	const fsmNode* getFsmNodePointer(void) const;

	void setFsmNodePointer(const fsmNode* pointer);

	void setProgState(progState* newS);

	bool nullstate(void) const override;

	bool endstate(void) const override;

	std::list<transition*> executables(void) const override;

	state* apply(const transition* trans) override;

	// Expression evaluation (flag)
	#define EVAL_EXECUTABILITY 0
	#define EVAL_EXPRESSION 1
	
	//trans or state, signature can be optimized!
	int eval(const fsmEdge* edge, byte flag) const; // Return true <=> transition 'trans' is executable on process 'mask'.

	int eval(const astNode* exp, byte flag) const;

	std::string getName(void) const;

	bool isAccepting(void) const override;

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

	//byte compare(const state& s2) const override;

	void printGraphViz(unsigned long i) const override;

	void printTexada(void) const override;

	void printHexadecimal(void) const override;

	unsigned long hash(void) const override;

private:
	const seqSymNode* symType;
	unsigned int index;

	progState* s;
	const fsmNode* const start;

	mutable bool _else;

	byte pid;
};

#endif