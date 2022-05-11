#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <assert.h>
#include <iostream>

#include "fsmNode.hpp"
#include "fsmEdge.hpp"
#include "automata.hpp"

#include "symbols.hpp"
#include "ast.hpp"

fsmNode::~fsmNode(void){
}

/**
 * Creates a transition and adds it to the node list of the fsm.
 */
fsmEdge* fsmNode::createfsmEdge(int lineNb, const astNode* expression, fsmNode* target) {
	fsmEdge* newTrans = new fsmEdge(this, expression, lineNb);
	if(target)
		newTrans->setTargetNode(target);
	this->trans.push_back(newTrans);
	parent->addTransition(newTrans);
	return newTrans;
}

/**
 * Copies and FSM transition and add it to the transition list of an FSM and of the transition list of the corresponding source node in this FSM.
 */
fsmEdge* fsmNode::copyfsmEdge(const fsmEdge* trans) {
	return createfsmEdge(trans->getLineNb(), trans->getExpression());
}

fsmNode::fsmNode(int flags, int lineNb, fsm* parent) {
	this->parent = parent;
	this->flags = flags;
	this->lineNb = lineNb;
}

void fsmNode::addTransition(fsmEdge* trans) {
	//assert(std::find(this->trans.begin(), this->trans.end(), trans) == this->trans.end());
	this->trans.push_back(trans);
}

void fsmNode::removeTransition(fsmEdge* trans) {
	assert(std::find(this->trans.begin(), this->trans.end(), trans) != this->trans.end());
	this->trans.remove(trans);
}

void fsmNode::detachTransitions(void) {
	trans.clear();
}


void fsmNode::addInputTransition(fsmEdge* trans_in) {
	assert(std::find(this->trans_in.begin(), this->trans_in.end(), trans_in) == this->trans_in.end());
	this->trans_in.push_back(trans_in);
}

void fsmNode::removeInputTransition(fsmEdge* trans_in) {
	assert(std::find(this->trans_in.begin(), this->trans_in.end(), trans_in) != this->trans_in.end());
	this->trans_in.remove(trans_in);
}

std::list<fsmEdge *> fsmNode::getTransitions(void) const {
	return trans;
}

std::list<fsmEdge *> fsmNode::getInputTransitions(void) const {
	return trans_in;
}

void fsmNode::addFlags(unsigned int flags) {
	this->flags |= flags;
}

unsigned int fsmNode::getFlags(void) const {
	return flags;
}

void fsmNode::setLineNb(int line) {
	lineNb = line;
}

int fsmNode::getLineNb(void) const {
	return lineNb;
}

fsm* fsmNode::getParent(void) const {
	return parent;
}

void fsmNode::orderAcceptTransitions(void) {
	
}

fsmNode::operator std::string(void) const {
	std::string res = "";
	for(auto t : trans)
		res += std::string(*t);
	return res;
}

unsigned long fsmNode::getID(void) const {
	unsigned long id = (unsigned long)this;
	return id;
}

/*
void fsmNode::printFsmNode(ptList printed, int level) {
	printed = listAdd(printed, this);
	spaces(level);
	printf("NL%03d", lineNb);
	if(flags != 0) printf(", flags:%s%s%s%s.", (flags & N_ACCEPT) == N_ACCEPT ? " accept" : "", (flags & N_END) == N_END ? " end" : "", (flags & N_PROGRESS) == N_PROGRESS ? " progress" : "", (flags & N_ATOMIC) == N_ATOMIC ? " atomic" : "");
	ptList tmp = trans_in;
	printf("   [in:");
	while(tmp) {
		printf("  %03d", ((fsmEdge*)tmp->value)->lineNb);
		tmp = tmp->next;
	}
	printf("]\n");
	ptList lTrans = trans;
	fsmEdge* trans;
	while(lTrans != nullptr) {
		trans = (fsmEdge*) lTrans->value;
		spaces(level);
		printf("  ----(TL%03d, %s, %s", trans->lineNb, trans->expression ? expNode::getExpTypeName(trans->expression->type) : "no expression", trans->hasFeatures ? "" : "no feature expression");
		//printBool(trans->features);
#ifdef STOCHASTIC
		printf(", %f", trans->expression ? trans->expression->prob : 1);
#endif
#ifdef CEGARTRANS
		printf(" (originally: ");
		//printBool(trans->origFeatures);
		printf(")");
#endif
		printf(")---> ");
		if(trans->target) {
			if(!listFind(printed, trans->target)) {
				printf("\n");
				trans->target->printFsmNode(printed, level + LEVEL_STEP);
			} else {
				printf("NL%03d\n", trans->target->lineNb);
			}
		} else {
			printf("(loose end)\n");
		}
		lTrans = lTrans->next;
	}
}*/