#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <string>
#include <assert.h>
#include <iostream>

#include "fsm.hpp"
#include "fsmNode.hpp"
#include "fsmEdge.hpp"

#include "symbols.hpp"
#include "ast.hpp"

/*
 * FINITE STATE MACHINES (FSMs)
 * * * * * * * * * * * * * * * * * * * * * * * */

fsm::fsm(const symTable* globalSymTab)
	: globalSymTab(globalSymTab)
{}

/**
 * Destroys an FSM and all that's linked to it.
 */
fsm::~fsm(){
	for(fsmNode* node : nodes) delete node;
	for(fsmEdge* trans : trans) delete trans;
}

const symTable* fsm::getGlobalSymTab(void) const {
	return globalSymTab;
}

/**
 * Creates a node and adds it to the node list of the fsm.
 * The node has to be manually attached to a transition.
 */

fsmNode* fsm::createFsmNode(int flags, int lineNb) {
	fsmNode* node = new fsmNode(flags, lineNb, this);
	nodes.push_back(node);
	return node;
}

/**
 * Copies and FSM node and add it to the node list of an FSM.
 */
fsmNode* fsm::copyFsmNode(const fsmNode* node) {
	return createFsmNode(node->getFlags(), node->getLineNb());
}

std::list<fsmNode *> fsm::getNodes(void) const {
	return nodes;
}

void fsm::deleteTransition(fsmEdge* edge) {
	assert(std::find(this->trans.begin(), this->trans.end(), edge) != this->trans.end());
	
	auto source = edge->getSourceNode();
	if(source)
		source->removeTransition(edge);
	auto dest = edge->getTargetNode();
	if(dest)
		dest->removeInputTransition(edge);

	trans.remove(edge);
	delete edge;
}

void fsm::deleteNode(fsmNode* node) {
	assert(std::find(this->nodes.begin(), this->nodes.end(), node) != this->nodes.end());
	
	for(auto t : node->getEdges())
		deleteTransition(t);
	for(auto t : node->getInputEdges())
		deleteTransition(t);
	
	nodes.remove(node);
	delete node;
}

void fsm::connect(fsmNode* begin, fsmNode* end) {
	assert(std::find(nodes.begin(), nodes.end(), begin) != nodes.end());
	assert(std::find(nodes.begin(), nodes.end(), end) != nodes.end());

	std::list<fsmEdge*> endEdges;
	std::stack<fsmNode*> beginNodes;
	beginNodes.push(begin);

	while(!beginNodes.empty()){
		
		auto n = beginNodes.top();
		beginNodes.pop();

		for(auto t : n->getEdges()){
			if(t->getTargetNode() == nullptr)
				endEdges.push_back(t);
			else
				beginNodes.push(t->getTargetNode());
		}
	}

	for(auto t : endEdges)
		t->setTargetNode(end);
}

void fsm::addInitNode(const std::string& procName, fsmNode* node) {
	inits[procName] = node;
}

std::map<std::string, fsmNode*> fsm::getInitNodes() const {
	return inits;
}

fsmNode* fsm::getFsmWithName(const std::string& name) const {
	return inits.at(name);
}

std::list<fsmEdge*> fsm::getEndTransitions(void) const {
	std::list<fsmEdge*> res;
	for (auto t : trans)
        if(t->getTargetNode() == nullptr)
            res.push_back(t);
	return res;
}

void fsm::addTransition(fsmEdge* edge){
	trans.push_back(edge);
}

void fsm::printGraphVis(std::ofstream& file) const {
	file << "digraph finite_state_machine {\n";
	file << "\trankdir=LR\n";
	file << "\tsize=\"8,5\"\n";

	for(auto init : inits) {
		file << "\t" << init.second->getID() << " [label = "<< init.second->getLineNb() <<", shape = doublecircle, fixedsize = true]; \n";
		file << "\ts" << init.second->getID() << " [shape = point];\n";
	}
	
	for(auto end : getEndTransitions())
		file << "\te" << end->getSourceNode()->getID() << " [shape = doublecircle, fixedsize = true, style = filled, fillcolor = black, fontcolor = white, label = end];\n";
	
	for(auto node : nodes) {
		if(!node->getInputEdges().empty())
			file << "\t "<< node->getID() <<" [label = "<< node->getLineNb() <<", shape = circle, fixedsize = true "<< ((node->getFlags() & fsmNode::N_ATOMIC)? ", style = dotted" : "") << "];\n";
	}

	for(auto init : inits)
		file << "\ts" <<  init.second->getID() << " -> " << init.second->getID() << ";\n";
	
	for(auto t : trans){
		auto exprStr = std::string(*t->getExpression());
		std::replace(exprStr.begin(), exprStr.end(), '\"', ' ');
		std::replace(exprStr.begin(), exprStr.end(), '\n', ' ');
		if(t->getTargetNode()) {
			file << "\t" <<  t->getSourceNode()->getID() <<" -> "<< t->getTargetNode()->getID() <<" [label = \""<< exprStr << "\"];\n";
		}
		else
			file << "\t" <<  t->getSourceNode()->getID() <<" -> e" << t->getSourceNode()->getID() <<" [label = \""<< exprStr << "\"];\n";
		
	}


	file << "}";
}

/*
void fsm::printGraphVis(std::ofstream& file) const {
	file << "digraph finite_state_machine {\n";
	file << "\trankdir=LR\n";
	file << "\tsize=\"8,5\"\n";

	for(auto init : inits) {
		file << "\t" << init.second->getID() << " [label = "<< init.second->getLineNb() <<", shape = doublecircle, fixedsize = true]; \n";
		file << "\ts" << init.second->getID() << " [shape = point];\n";
	}
	
	for(auto end : getEndTransitions())
		file << "\te" << end->getSourceNode()->getID() << " [shape = doublecircle, fixedsize = true, style = filled, fillcolor = black, fontcolor = white, label = end];\n";
	
	for(auto node : nodes) {
		if(!node->getInputTransitions().empty())
			file << "\t "<< node->getID() <<" [label = "<< node->getLineNb() <<", shape = circle, fixedsize = true "<< ((node->getFlags() & fsmNode::N_ATOMIC)? ", style = dotted" : "") << "];\n";
	}

	for(auto init : inits)
		file << "\ts" <<  init.second->getID() << " -> " << init.second->getID() << ";\n";
	
	for(auto t : trans){
		auto exprStr = std::string(*t->getExpression());
		std::replace(exprStr.begin(), exprStr.end(), '\"', ' ');
		std::replace(exprStr.begin(), exprStr.end(), '\n', ' ');
		if(t->getTargetNode()) {
			file << "\t" <<  t->getSourceNode()->getID() <<" -> "<< t->getTargetNode()->getID() <<" [label = \""<< exprStr << "\" "<< ((t->getTargetNode()->getFlags() & fsmNode::N_ATOMIC)? ", style = dotted" : "") << "];\n";
		}
		else
			file << "\t" <<  t->getSourceNode()->getID() <<" -> e" << t->getSourceNode()->getID() <<" [label = \""<< exprStr << "\"];\n";
		
	}


	file << "}";
}*/