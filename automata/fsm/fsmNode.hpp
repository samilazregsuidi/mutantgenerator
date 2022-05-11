#ifndef NODE_H
#define NODE_H
/*
 * FINITE STATE MACHINES (FSMs)
 * * * * * * * * * * * * * * * * * * * * * * * */
#include <list>
#include <string>

class mTypeNode;
class symTabNode;
class astNode;

class fsm;
class fsmEdge;

class fsmNode
{
	friend fsm;

public:
	const static unsigned int N_ACCEPT = 1;
	const static unsigned int N_PROGRESS = 2;
	const static unsigned int N_END = 4;
	const static unsigned int N_ATOMIC = 8;
	const static unsigned int N_DETERMINISTIC = 16;
	// The inner nodes of an atomic block have this flag set; the semantics of execution is thus:
	// if a transition was chosen that leads to an N_ATOMIC node, then the outgoing transition of
	// that node must be fired, and so on.  An atomic node can only have one outgoing transition.
private:
	fsmNode(int flags, int lineNb, fsm *parent);

public:
	~fsmNode(void);
	fsmEdge *createfsmEdge(int lineNb, const astNode *expression = nullptr, fsmNode *target = nullptr);
	fsmEdge *copyfsmEdge(const fsmEdge *trans);
	void addTransition(fsmEdge *trans);
	void removeTransition(fsmEdge *trans);
	void addInputTransition(fsmEdge *trans);
	void removeInputTransition(fsmEdge *trans);
	void addFlags(unsigned int flags);

	fsm* getParent(void) const;
	void detachTransitions(void);

	void printFsmNode(const std::list<const fsmNode *> &printed, int level) const;
	unsigned int getFlags(void) const;
	void setLineNb(int lineNb);
	int getLineNb(void) const;
	std::list<fsmEdge *> getTransitions(void) const;
	std::list<fsmEdge *> getInputTransitions(void) const;
	void orderAcceptTransitions(void);

	operator std::string(void) const;

	unsigned long getID(void) const;

private:
	fsm *parent;
	int flags;
	int lineNb;
	std::list<fsmEdge *> trans;
	std::list<fsmEdge *> trans_in;
};

#endif
