#ifndef FSM_H
#define FSM_H
/*
 * FINITE STATE MACHINES (FSMs)
 * * * * * * * * * * * * * * * * * * * * * * * */
#include <list>
#include <map>
#include <string>

#include <fstream>

#include "cuddObj.hh"

class symTable;

class fsmEdge;
class fsmNode;
class stmnt;

class fsm
{

public:
	fsm(const symTable* globalSymTab);

	virtual ~fsm();
	
	void destroySkeleton();
	
	fsmNode *createFsmNode(int flags, int lineNb);
	
	fsmNode *copyFsmNode(const fsmNode *node);
	
	//fsm *stmnt2fsm(astNode *stmnt, symTabNode *symTab);
	//void setSymTab(symTabNode *sym);
	//void merge(fsm *child);
	//void project(void);
	//bool hasLooseFeatures(void) const;
	//void orderAcceptTransitions(void);
	//void resolveVariables(symTabNode *globalSymTab, const mTypeNode *mTypes) const;
	//unsigned int processVariables(symTabNode *global, const mTypeNode *mTypes, unsigned int offset, bool isGlobal) const;
	//void printFsm(int level, const std::string &title) const;

	//symTabNode *getSymTab(void) const;
	//fsmNode *getInitNode(void) const;
	//void setInitNode(fsmNode *init);

	const symTable* getGlobalSymTab(void) const;

	void addTransition(fsmEdge* edge);
	
	void deleteTransition(fsmEdge* edge);
	
	void deleteNode(fsmNode* node);
	
	void connect(fsmNode* begin, fsmNode* end);

	std::list<fsmNode *> getNodes(void) const;
	
	std::list<fsmEdge *> getTransitions(void) const;

	std::list<fsmEdge*> getEndTransitions(void) const;

	const ADD& getFD(void) const;

	operator std::string(void) const;

	void addInitNode(const std::string& procName, fsmNode* node);
	
	std::map<std::string, fsmNode*> getInitNodes() const;
	
	fsmNode* getFsmWithName(const std::string& name) const;

	void printGraphVis(std::ofstream& file) const;

	void printGraphVisWithLocations(std::ofstream& file, const std::list<const fsmNode*>& locs, const std::list<const fsmEdge*>& edges) const;

private:
	std::map<std::string, fsmNode*> inits;											 // The initial node
	std::list<fsmNode*> ends;
	std::list<fsmNode *> nodes;								 // List of ptFsmNode	- This list contains all nodes of the FSM in an arbitrary order.
	std::list<fsmEdge *> trans;							 // List of fsmEdge	- This list contains all transitions of the FSM in an arbitrary order.

	const symTable* globalSymTab;
	ADD fd;
};

#endif
