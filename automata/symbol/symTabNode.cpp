#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <assert.h>

#include "symTabNode.h"
#include "expression.h"

#include "naSymNode.h"
#include "bitSymNode.h"
#include "boolSymNode.h"
#include "byteSymNode.h"
#include "shortSymNode.h"
#include "intSymNode.h"
#include "unsgnSymNode.h"
#include "mTypeSymNode.h"
#include "utypeSymNode.h"
#include "pidSymNode.h"
#include "cidSymNode.h"
#include "tdefSymNode.h"
#include "chanSymNode.h"
#include "procSymNode.h"

#include "symTabCopyVisitor.h"

#define LEVEL_STEP 10



/*
 * SYMBOL TABLE
 * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * Just creates a node with the given values.
 */
symTabNode::symTabNode(Type type, const std::string &name, int lineNb)
{
	this->type = type;
	this->name = name;
	this->global = false;
	this->lineNb = lineNb;
	//this->bound = bound;
	//this->capacity = capacity;
	this->memOffset = 0;
	this->memSize = 0;
	//this->init = init;
	//this->childFsm = childFsm;
	//this->child = child;
	this->prev = this;
	this->next = nullptr;
	//this->utype = nullptr;
}

symTabNode::symTabNode(Type type, int lineNb, const std::string &sVal)
	: symTabNode(type, sVal, lineNb)
{
}

/**
 * Creates a node with a user-defined type (based on the type name).
 *  - It therefore needs a symbol table to look up that type.
 *  - It will return NULL if no type of this name exists!
 */
/*symTabNode::symTabNode(symTabNode* symbols, const std::string& type, const std::string& name, int lineNb, int bound, int capacity, expr* init, fsm* childFsm, symTabNode* child) {
	const symTabNode* pType = symbols->lookupInSymTab(type);
	if(pType == NULL || pType->type != symTabNode::T_TDEF) 
		assert(false);
	
	this->type	= symTabNode::T_UTYPE;
	this->utype	= pType;
	this->name	= name;
	this->global = 0;
	this->lineNb = lineNb;
	this->bound	= bound;
	this->capacity=capacity;
	this->memOffset= 0;
	this->memSize= 0;
	this->init	= init;
	this->childFsm = childFsm;
	this->child	= child;
	this->prev	= this;
	this->next	= nullptr;
}*/

/**
 * Destroys a symTab and all that's linked to it (except for the utype).
 */
symTabNode::~symTabNode()
{
	delete next;
}

/**
 * Concatenates two symTabs (the second symTab is usually a single node).
 * The arguments can be NULL (if both are NULL, the function returns NULL).
 * Returns a pointer to the new symTab.
 */

symTabNode *symTabNode::merge(symTabNode *symTab, symTabNode *newNode) {
	if (!symTab)
		return newNode;
	if (!newNode)
		return symTab;

	symTabNode *newlistTail = newNode->prev;
	newNode->prev = symTab->prev;
	newNode->prev->next = newNode;
	symTab->prev = newlistTail;
	return symTab;
}

symTabNode *symTabNode::deepcopy(symTabNode *symTab)
{
	symTabCopyVisitor visitor;
	return visitor.deepCopy(symTab);
}

/*symTabNode* symTabNode::addToSymTab(symTabNode* newNode){
	assert(newNode);
	symTabNode* newlistTail = newNode->prev;
	newNode->prev = prev;
	newNode->prev->next = newNode;
	prev = newlistTail;
	return this;
}*/

symTabNode *symTabNode::lookupInSymTab(const exprVarRefName *expr)
{
	return lookupInSymTab(expr->getName());
}

const symTabNode *symTabNode::lookupInSymTab(const exprVarRefName *expr) const
{
	return lookupInSymTab(expr->getName());
}

symTabNode *symTabNode::lookupInSymTab(const exprVarRef *expr) {
	symTabNode *sym = lookupInSymTab(expr->getExprVarRefName());
	assert(sym);
	//if (expr->hasSubField() && (uSym = sym->getUType()) && (uSym = uSym->getUType()->getChild()))
	if(expr->hasSubField()) {
		utypeSymNode* utype = static_cast<utypeSymNode*>(sym);
		tdefSymNode* tdef = utype? utype->getUType() : nullptr;
		varSymNode* child = tdef ? tdef->getChild() : nullptr;
		return child->lookupInSymTab(expr->getSubField());
	}
	return nullptr;
}

const symTabNode *symTabNode::lookupInSymTab(const exprVarRef *expr) const {
	const symTabNode *sym = lookupInSymTab(expr->getExprVarRefName());
	assert(sym);
	//if (expr->hasSubField() && (uSym = sym->getUType()) && (uSym = uSym->getUType()->getChild()))
	if(expr->hasSubField()) {
		const utypeSymNode* utype = static_cast<const utypeSymNode*>(sym);
		const tdefSymNode* tdef = utype? utype->getUType() : nullptr;
		const varSymNode* child = tdef ? tdef->getChild() : nullptr;
		return child->lookupInSymTab(expr->getSubField());
	}
	return nullptr;
}

symTabNode *symTabNode::lookupInSymTab(const exprVar *expr)
{
	return lookupInSymTab(expr->getExprVarRef());
}

const symTabNode *symTabNode::lookupInSymTab(const exprVar *expr) const
{
	return lookupInSymTab(expr->getExprVarRef());
}

/**
 * Returns the symbol with the given name or NULL if there is no such symbol in the symTab.
 */
symTabNode *symTabNode::lookupInSymTab(const std::string &name)
{
	return name == getName() ? this : next->lookupInSymTab(name);
}

const symTabNode *symTabNode::lookupInSymTab(const std::string &name) const
{
	return name == getName() ? this : next->lookupInSymTab(name);
}

/*bool symTabNode::isFeature(void) const {
	return type == T_FEAT;
}*/

void symTabNode::detachPrev(void) {
	prev = nullptr;
}

void symTabNode::detachNext(void) {
	next = nullptr;
}

/*void symTabNode::detachChildAndInitSymNodes(void){
	child = nullptr;
	init = nullptr;
}*/

void symTabNode::makeNext(symTabNode *newNext) {
	this->next = newNext;
	newNext->prev = this;
	newNext->detachNext();
}

void symTabNode::setNext(symTabNode* next) {
	this->next = next;
}

const symTabNode *symTabNode::cnextSym(void) const
{
	return next;
}

symTabNode *symTabNode::nextSym(void) const
{
	return next;
}

symTabNode::Type symTabNode::getType(void) const
{
	return type;
}

/*int symTabNode::getBound(void) const
{
	return bound;
}*/

void symTabNode::setLineNb(int line)
{
	lineNb = line;
}

int symTabNode::getLineNb(void) const
{
	return lineNb;
}

std::string symTabNode::getName(void) const
{
	return name;
}

bool symTabNode::isGlobal(void) const
{
	return global;
}

void symTabNode::setGlobal(bool global)
{
	this->global = global;
}

unsigned int symTabNode::getMemorySize(void) const
{
	return memSize;
}

/*symTabNode *symTabNode::getUType(void) const
{
	assert(type == T_UTYPE);
	return utype;
}

void symTabNode::setUType(symTabNode *utype)
{
	assert(type == T_UTYPE);
	this->utype = utype;
}

symTabNode *symTabNode::getChild(void) const
{
	return child;
}

expr *symTabNode::getInitExpr(void) const
{
	return init;
}

int symTabNode::getChanCapacity(void) const
{
	assert(type == T_CHAN);
	return capacity;
}

stmnt *symTabNode::getStmnt(void) const
{
	assert(type == T_PROC || type == T_NEVER);
	return childFsm;
}*/

symTabNode::operator std::string(void) const
{
	std::string res = getTypeName() + " " + getName();
	return res;
}

/**
 * Helper function, prints "count" spaces and at each levelStep a >.
 */
void spaces(int count)
{
	int i;
	for (i = 0; i <= count; i++)
	{
		if ((i % LEVEL_STEP) == 0)
			printf(">");
		printf(" ");
	}
}

/**
 * Prints the content of the symTab to stdout (recursively).
 *  - level denotes the number of spaces to be used to indent the output.
 *  - title is the title of the symTab.
 */
/*void symTabNode::printSymTab(int level, const std::string &title) const
{

	spaces(level);
	printf("SymTab of [%s].\n", title.c_str());
	spaces(level);
	printf("name         | lineNb |     type | bound | capacity | mOffs | mSize | init? | fsm? \n");
	spaces(level);
	printf(" %-11s | % 6d | %8s | % 5d | % 8d | % 5d | % 5d | %5s | %4s\n", name.c_str(),
		   lineNb,
		   type == symTabNode::T_UTYPE ? (utype ? utype->getName().c_str() : "") : this->getTypeName().c_str(),
		   bound,
		   capacity,
		   memOffset,
		   memSize,
		   (init ? "yes" : "no"),
		   (childFsm ? "yes" : "no"));
	if ((type == symTabNode::T_TDEF || type == symTabNode::T_CHAN) && child != NULL)
	{
		child->printSymTab(level + LEVEL_STEP, name);
		spaces(level);
		printf("\n");
	}
	if (type == symTabNode::T_PROC || type == symTabNode::T_NEVER)
	{
		assert(childFsm);
		childFsm->getSymbol()->printSymTab(level + LEVEL_STEP, name);
		spaces(level);
		printf("\n");
	}
	if (next)
		next->printSymTab(level, nullptr);
}*/



























