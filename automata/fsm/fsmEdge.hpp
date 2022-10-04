#ifndef EDGE_H
#define EDGE_H
/*
 * FINITE STATE MACHINES (FSMs)
 * * * * * * * * * * * * * * * * * * * * * * * */

#include <string>
//#include "cuddObj.hh"

class astNode;

class fsm;
class fsmNode;

class fsmEdge
{

public:
	fsmEdge(fsmNode *source, const astNode *expression, int lineNb);
	~fsmEdge();
	fsmNode* setTargetNode(fsmNode *target);
	fsmNode* setSourceNode(fsmNode *source);
	//void resolveVariables(symTabNode *global, symTabNode *local, const mTypeNode *mTypes) const;
	int getLineNb(void) const;
	void setLineNb(int line);
	//bool hasFeatures(void) const;
	//const ADD& getFeatures(void) const;
	//void setFeatures(const ADD& features);
	//byte getFeaturesValue(void) const;
	
	bool project(void);
	//getExpr?
	
	const astNode *getExpression(void) const;
	double getProbability(void) const;
	void setExpression(const astNode *expression);
	fsmNode *getSourceNode(void) const;
	fsmNode *getTargetNode(void) const;

	operator std::string(void) const;

private:
	fsm* parent;
	int lineNb;
	//bool hasFeat;
	//ADD features;
	fsmNode *source;
	const astNode *expression;
	fsmNode *target;
	double prob;
};

#endif
