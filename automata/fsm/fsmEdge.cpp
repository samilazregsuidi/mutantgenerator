#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <assert.h>
#include <iostream>

#include "fsm.hpp"
#include "fsmEdge.hpp"
#include "fsmNode.hpp"
#include "symbols.hpp"
#include "ast.hpp"

fsmEdge::fsmEdge(fsmNode* source, const astNode* expression, int lineNb){
	this->parent = source->getParent();
	this->source = source;
	this->target = nullptr;
	this->expression = expression;
	this->lineNb = lineNb;
	this->prob = 1.0;
}

/**
 * Destroys a transition; but not the attached nodes.
 */
fsmEdge::~fsmEdge(){
}

fsmNode* fsmEdge::setTargetNode(fsmNode* target) {
	assert(!this->target);
	assert(target);
	
	if(this->target) {
		this->target->removeInputTransition(this);
	}

	auto old = this->target;
	this->target = target;
	this->target->addInputTransition(this);

	return old;
}

fsmNode * fsmEdge::getTargetNode(void) const {
	return target;
}

fsmNode* fsmEdge::setSourceNode(fsmNode *source) {
	//assert(!this->source);
	assert(source);
	
	if(this->source) {
		this->source->removeTransition(this);
	}

	auto old = this->source;
	this->source = source;
	if(this->source)
		this->source->addTransition(this);

	return old;
}

fsmNode * fsmEdge::getSourceNode(void) const {
	return source;
}

const astNode * fsmEdge::getExpression(void) const {
	return this->expression;
}

void fsmEdge::setExpression(const astNode *expression) {
	this->expression = expression;
}

void fsmEdge::setLineNb(int line) {
	lineNb = line;
}

int fsmEdge::getLineNb(void) const {
	return lineNb;
}

/*void fsmEdge::resolveVariables(symTabNode* global, symTabNode* local, const mTypeNode* mTypes) const{
	assert(false);
	//if(expression) 
		//expression->resolveVariables(global, mTypes, local);
}*/

fsmEdge::operator std::string(void) const {
	return expression? std::string(*expression) : "";
}