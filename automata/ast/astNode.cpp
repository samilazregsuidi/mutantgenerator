#include <assert.h>
#include <string>

#include "expression.h"
#include "symTabNode.h"
#include "varSymNode.h"
#include "utypeSymNode.h"
#include "tdefSymNode.h"
#include "mTypeList.h"
/**
 * Just creates a node with the given values.
 */
astNode::astNode(Type type, int iVal, astNode* child0, astNode* child1, astNode* child2, int lineNb, stmnt* block, symTabNode* symTabChild) {
	this->type			= type;
	this->iVal			= iVal;
	this->childFsm		= block;
	this->symTab		= symTabChild;
	this->lineNb 		= lineNb;
	this->child[0]= child0;
	this->child[1]= child1;
	this->child[2]= child2;
}

/**
 * Destroys an ExpNode and all that's linked to it.
 */
astNode::~astNode() {
	if(childFsm) 
		delete(childFsm);
	if(symTab) 
		delete(symTab);
	for(int i = 0; i < 3; i++) 
		if(child[i]) 
			delete child[i];
}

symTabNode* astNode::symbolLookUpRight() const {
	return nullptr;
}


symTabNode* astNode::symbolLookUpLeft(void) const {
	return nullptr;
}

symTabNode* astNode::getSymbol(void) const {
	return symTab;
}

void astNode::setSymbol(symTabNode *sym) {
	symTab = sym;
	for(int i = 0; i < 3; ++i)
		if(child[i])
			child[i]->setSymbol(sym);
}

astNode::Type astNode::getType(void) const {
	return type;
}

int astNode::getLineNb(void) const {
	return lineNb;
}

void astNode::setGlobal(bool global) {
	this->global = global;
}

bool astNode::isGlobal(void) const {
	return global;
}

int astNode::getIVal(void) const {
	return iVal;
}

void astNode::setIVal(int ival) {
	this->iVal = ival;
}
//const symTabNode* getUType(void) const;
//virtual bool isTimeout(void) const;

astNode* astNode::getChild0(void) const{
	return child[0];
}

astNode* astNode::getChild1(void) const{
	return child[1];
}

astNode* astNode::getChild2(void) const{
	return child[2];
}

astNode* astNode::detachChild0(void) {
	astNode* child0 = child[0];
	child[0] = nullptr;
	return child0;
}

astNode* astNode::detachChild1(void) {
	astNode* child1 = child[1];
	child[1] = nullptr;
	return child1;
}

astNode* astNode::detachChild2(void) {
	astNode* child2 = child[2];
	child[2] = nullptr;
	return child2;
}

/*fsm* astNode::getChildFsm(void) const {
	return childFsm;
}*/

void astNode::resolveVariables(symTabNode* globalSymTab, const mTypeList* mTypes, symTabNode* localSymTab, symTabNode* subFieldSymTab) {
	for(int i = 0; i < 3; i++) 
		if(child[i] != nullptr) 
			child[i]->resolveVariables(globalSymTab, mTypes, localSymTab, subFieldSymTab);
}