#ifndef AUTOMATA_H
#define AUTOMATA_H
/*
 * FINITE STATE MACHINES (FSMs)
 * * * * * * * * * * * * * * * * * * * * * * * */
#include <list>
#include <map>
#include <string>

class mTypeNode;
class symTabNode;
class astNode;

class fsmTrans;

class fsmNode {

public:

	const static unsigned int N_ACCEPT = 1;
	const static unsigned int N_PROGRESS = 2;
	const static unsigned int N_END = 4;
	const static unsigned int N_ATOMIC = 8;
	// The inner nodes of an atomic block have this flag set; the semantics of execution is thus:
	// if a transition was chosen that leads to an N_ATOMIC node, then the outgoing transition of
	// that node must be fired, and so on.  An atomic node can only have one outgoing transition.

	fsmNode(int flags, int lineNb);

	fsmTrans* createFsmTrans(astNode* expression, int lineNb);
	fsmTrans* copyFsmTrans(const fsmTrans* trans);
	void addTransition(const fsmTrans* trans);
	void addInputTransition(const fsmTrans* trans);
	void addFlags(unsigned int flags);

	void detachTransitions(void);

	void printFsmNode(const std::list<const fsmNode*>& printed, int level) const;
	int getFlags(void) const;
	int getLineNb(void) const;
	const std::list<fsmTrans*>& getTransitions(void) const;
	const std::list<fsmTrans*>& getInTransitions(void) const;
	void project(void);
	void orderAcceptTransitions(void);
	symTabNode* getSymTab(void) const;
	
private:	
	int flags;
	int lineNb;
	std::list<const fsmTrans*> trans;
	std::list<const fsmTrans*> trans_in;
};

class fsmTrans {

public:
	fsmTrans(fsmNode* source, astNode* expression, int lineNb);
	~fsmTrans();
	void setTargetNode(fsmNode* target);
	void setSourceNode(fsmNode* source);
	void resolveVariables(symTabNode* global, symTabNode* local, const mTypeNode* mTypes) const;
	int getLineNb(void) const;
	//bool hasFeatures(void) const;
	//const ADD& getFeatures(void) const;
	//void setFeatures(const ADD& features);
	//byte getFeaturesValue(void) const;
	bool project(void);
	astNode* getExpression(void) const;
	void setExpression(astNode* expression);
	const fsmNode* getSourceNode(void) const;
	const fsmNode* getTargetNode(void) const;

private:
	int lineNb;
	//bool hasFeat;
	//ADD features;
	fsmNode* source;
	astNode* expression;
	fsmNode* target;
};

//#define NBLABELS 2

class fsm {

public:
	fsm();
	~fsm();
	void destroySkeleton();
	fsmNode* createFsmNode(int flags, int lineNb, const std::list<std::string>& labels);
	fsmNode* createFsmNode(int flags, int lineNb);
	fsmNode* copyFsmNode(const fsmNode* node);
	fsm* stmnt2fsm(astNode* stmnt, symTabNode* symTab);
	void setSymTab(symTabNode* sym);
	void merge(fsm* child);
	void project(void);
	bool hasLooseFeatures(void) const;
	void orderAcceptTransitions(void);
	void resolveVariables(symTabNode* globalSymTab, const mTypeNode* mTypes) const;
	unsigned int processVariables(symTabNode* global, const mTypeNode* mTypes, unsigned int offset, bool isGlobal) const;
	void printFsm(int level, const std::string& title) const;

	symTabNode* getSymTab(void) const;
	fsmNode* getInitNode(void) const;
	std::list<fsmNode*> getNodes(void) const;

private:
	symTabNode* symTab;
	fsmNode* init;	// The initial node
	std::list<fsmNode*> nodes;			// List of ptFsmNode	- This list contains all nodes of the FSM in an arbitrary order.
	std::map<std::string, fsmNode*> labeledNodes;			// List of ptFsmNode	- This list is indexed by label and contains for each label the labelled node.
	std::list<fsmTrans*> transitions;		// List of ptFsmTrans	- This list contains all transitions of the FSM in an arbitrary order.
	std::list<fsmTrans*> looseEnds;		// List of ptFsmTrans	- For model construction: contains those transitions that do not have an end state.
	std::map<std::string, std::list<fsmTrans*>> looseGotos; 	// List of ptFsmTrans	- For model construction: contains those transitions (indexed by label name) that have yet to be connected to a state with this label.
	std::list<fsmTrans*> looseBreaks;		// List of ptFsmTrans	- For model construction: contains those transitions that were generated because of a break statement and are waiting to be matched to a DO.
	//ADD looseFeatures;// 						- For model construction: a feature expression that was previously read and has to be attached to the next transition
};

#endif
