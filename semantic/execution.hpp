#ifndef EXECUTION_H
#define EXECUTION_H

/*
 * Execution of FSMs
 * * * * * * * * * * * * * * * * * * * * * * * */

#include <list>
#include <stack>

class state;
class fsmEdge;
class process;
class symTable;
class expr;

#define processTrans 0
#define directTrans 1

typedef unsigned char byte;

// ProcessTransitions are returned by the executables() function
class transition {
public:
	static transition* selectTransition(const std::list<transition*>& transList); // Choose a transition and returns it.
	static void destroyProcTransList(const std::list<transition*>& transList, byte process_or_direct);
	static void checkProcTransList(const std::list<transition*>& list);
	static byte isProbabilisticTransList(const std::list<transition*>& list);

	transition(process* proc, fsmEdge* trans, transition* response = nullptr);
	~transition();
	transition* copyProcessTransition(void);

	int eval(state* state, process* mask, expr* expression, byte flag); // Return true <=> transition 'trans' is executable on process 'mask'.


public:		//
	fsmEdge* trans;			//  - The transition that can be fired
	transition* response;		// 	- In case of a rendezvous request, this is the response transition.
	process* proc;		//	- The mask of the process to which the transition belongs (from the state that was given to executables())
	double prob;
};

// An element on the exploration stack (corresponds to a stack frame if the algorithm were implemented recursively).
// The (synchronous) product between the E_never and E transitions is calculated by iterating through the E list for
// each E_never element.  This means that if E_never is NULL, then the whole thing is done; if E is NULL, then the
// E_never list has to be advanced, and the E list reset to the beginning (E_save).
class stackElt {
public:
	stackElt(state* state, int nbErrors);
	~stackElt();
	
public:
	state* state;			// The state itself
	std::list<transition*> E_never_save;	// A list of ptFsmTrans: the list of executable transitions in the never claim.
	std::list<transition*> E_never;			// A list of ptFsmTrans: points to next transition in the E_never_save list.
	std::list<transition*> E_save;			// A list of transition*: the list of executable transitions of the FSMs.
	std::list<transition*> E;				// A list of transition*: points to next transition in the E_save list.
	unsigned char nbErrors;			// Number of errors encountered when the stack element was last updated.
    double prob;
};

class execution : public std::stack<stackElt*> {
public:
	void printStackElementStack(symTable* globalSymTab, std::stack<stackElt*>& stack, state* loopBegin, stackElt* prevTopElt);
	void destroyStackElementStack(std::stack<stackElt*>& stack, byte process_or_direct);
};

/*
 * API
 * * * * * * * * * * * * * * * * * * * * * * * */

// Expression evaluation
#define EVAL_EXECUTABILITY 0
#define EVAL_EXPRESSION 1

//byte checkEqualProps(ptList props, symTable* globalSymTab, mtypes, state* s, ptList props2, symTable* globalSymTab2, ptMTypeNode mtypes2, state* s2);

// Executable transitions in state
std::list<transition*> executables(symTable* globalSymTab, state* state, byte stutter, int nbErrors, byte* hasDeadlock, byte* resetExclusivity);
//std::list<transition*> executablesNonStutter(ptList props, symTable* globalSymTab, state* state, byte stutter, int nbErrors, byte* hasDeadlock);
std::list<transition*> executablesNever(symTable* globalSymTab, state* state);



// Applying statements
state* apply(symTable* globalSymTab, state* state, transition* procTrans, byte preserve, byte* assertViolation); // Execute a transition on a given process.
state* applyRepeated(symTable* globalSymTab, state* state, std::list<transition*> procTrans, byte preserve, byte* assertViolation);
state* applyNever(symTable* globalSymTab, state* state, fsmEdge* transition);

// Execution stack


// Normal execution, no verification
void launchExecution(symTable* globalSymTab);

#endif
