#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <assert.h>

#include "symbols.h"
#include "expression.h"
#include "automata.h"

#define LEVEL_STEP 10


symTabNode* symTabNode::createSymTabNode(Type itype, int lineNb, const std::string& sVal, expr* init){
	switch(itype){
		case T_NA:
			assert(false);
		case T_BIT:
			return new bitSymNode(lineNb, sVal, init);
		case T_BOOL:
			return new boolSymNode(lineNb, sVal, init);
		case T_BYTE:
			return new byteSymNode(lineNb, sVal, init);
		case T_PID:
			assert(false);
		case T_SHORT:
			return new shortSymNode(lineNb, sVal, init);
		case T_INT:
			return new intSymNode(lineNb, sVal, init);
		case T_UNSGN: 	// not supported yet
			assert(false);
		case T_MTYPE:
			return new mTypeSymNode(lineNb, sVal, init);
		case T_CLOCK:	// dense time clock
			assert(false);
		case T_FEAT:
			assert(false);
		case T_UFEAT:
			assert(false);

		// "Special" types:
		case T_CHAN:		// Channel: capacity used; children denote message fields
			return new chanSymNode(lineNb, sVal, init);
		case T_CID:		// Channel reference; capacity and children are not used.
			assert(false);
		case T_TDEF:		// Type definition: children denote fields of type
			assert(false);
		case T_PROC:		// ProcType: fsm field used; bound denotes the number of initially active processes
			assert(false);
		case T_UTYPE:	// Type of variable is a user type (basically, a T_TDEF record is being used as the type): utype points to the type record
			return new utypeSymNode(lineNb, sVal, init);
		case T_NEVER:	// Never claim
			assert(false);
	}
	assert(false);
	return nullptr;	
}

symTabNode* symTabNode::createSymTabNode(Type itype, const symTabNode& old){
	switch(itype){
		case T_NA:
			assert(false);
		case T_BIT:
			return new bitSymNode(old);
		case T_BOOL:
			return new boolSymNode(old);
		case T_BYTE:
			return new byteSymNode(old);
		case T_PID:
			return new pidSymNode(old);
		case T_SHORT:
			return new shortSymNode(old);
		case T_INT:
			return new intSymNode(old);
		case T_UNSGN: 	// not supported yet
			assert(false);
		case T_MTYPE:
			return new mTypeSymNode(old);
		case T_CLOCK:	// dense time clock
			assert(false);
		case T_FEAT:
			assert(false);
		case T_UFEAT:
			assert(false);

		// "Special" types:
		case T_CHAN:		// Channel: capacity used; children denote message fields
			return new chanSymNode(old);
		case T_CID:		// Channel reference; capacity and children are not used.
			return new cidSymNode(old);
		case T_TDEF:		// Type definition: children denote fields of type
			return new procSymNode(old);
		case T_PROC:		// ProcType: fsm field used; bound denotes the number of initially active processes
			return new procSymNode(old);
		case T_UTYPE:	// Type of variable is a user type (basically, a T_TDEF record is being used as the type): utype points to the type record
			return new utypeSymNode(old);
		case T_NEVER:	// Never claim
			return new neverSymNode(old);
	}
	assert(false);
	return nullptr;
}

/*
 * SYMBOL TABLE
 * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * Just creates a node with the given values.
 */
symTabNode::symTabNode(Type type, const std::string& name, int lineNb, int bound, int capacity, expr* init, fsm* childFsm, symTabNode* child) {
	this->type	= type;
	this->name	= name;
	this->global = false;
	this->lineNb = lineNb;
	this->bound	= bound;
	this->capacity=capacity;
	this->memOffset= 0;
	this->memSize= 0;
	this->init	= init;
	this->childFsm  = childFsm;
	this->child	= child;
	this->prev	= this;
	this->next	= nullptr;
	this->utype	= nullptr;
}

symTabNode::symTabNode(Type type, int lineNb, const std::string& sVal, expr* init) 
	: symTabNode(type, sVal, lineNb, 0, 0, init)
{}

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
symTabNode::~symTabNode(){
	if(child) delete child;
	if(init) delete init;
	delete next;
}

/**
 * Concatenates two symTabs (the second symTab is usually a single node).
 * The arguments can be NULL (if both are NULL, the function returns NULL).
 * Returns a pointer to the new symTab.
 */
symTabNode* symTabNode::addToSymTab(symTabNode* newNode) /*non const*/{
	assert(newNode);
	symTabNode* newlistTail = newNode->prev;
	newNode->prev = prev;
	newNode->prev->next = newNode;
	prev = newlistTail;
	return this;
}

symTabNode* symTabNode::lookupInSymTab(const exprVarRefName* expr) {
	return lookupInSymTab(expr->getName());
}

const symTabNode* symTabNode::lookupInSymTab(const exprVarRefName* expr) const {
	return lookupInSymTab(expr->getName());
}

symTabNode* symTabNode::lookupInSymTab(const exprVarRef* expr) {
	symTabNode* sym = lookupInSymTab(expr->getExprVarRefName());
	assert(sym);
	if(expr->hasSubField() && (sym = sym->getUType()) && (sym = sym->getUType()->getChild()))
		return sym->lookupInSymTab(expr->getSubField());
	return nullptr;
}

const symTabNode* symTabNode::lookupInSymTab(const exprVarRef* expr) const {
	const symTabNode* sym = lookupInSymTab(expr->getExprVarRefName());
	assert(sym);
	if(expr->hasSubField() && (sym = sym->getUType()) && (sym = sym->getUType()->getChild()))
		return sym->lookupInSymTab(expr->getSubField());
	return nullptr;
}

symTabNode* symTabNode::lookupInSymTab(const exprVar* expr) {
	return lookupInSymTab(expr->getExprVarRef());
}

const symTabNode* symTabNode::lookupInSymTab(const exprVar* expr) const {
	return lookupInSymTab(expr->getExprVarRef());
}

/**
 * Returns the symbol with the given name or NULL if there is no such symbol in the symTab.
 */
symTabNode* symTabNode::lookupInSymTab(const std::string& name) {
	return name == getName()? this : next->lookupInSymTab(name);
}

const symTabNode* symTabNode::lookupInSymTab(const std::string& name) const {
	return name == getName()? this : next->lookupInSymTab(name);
}


/*bool symTabNode::isFeature(void) const {
	return type == T_FEAT;
}*/

void symTabNode::setNext(symTabNode* newNext){
	symTabNode* prevNext = this->next;
	prevNext->prev = nullptr;
	assert(!newNext->prev && !newNext->next);
	this->next = newNext;
	newNext->prev = this;
	newNext->next = prevNext;
}

const symTabNode* symTabNode::cnextSym(void) const {
	return next;
}

symTabNode* symTabNode::nextSym(void) const {
	return next;
}

symTabNode::Type symTabNode::getType(void) const {
	return type;
}

int symTabNode::getBound(void) const {
	return bound;
}

void symTabNode::setLineNb(int line) {
	lineNb = line;
}

int symTabNode::getLineNb(void) const {
	return lineNb;
}

std::string symTabNode::getName(void) const {
	return name;
}

bool symTabNode::isGlobal(void) const {
	return global;
}

void symTabNode::setGlobal(bool global) {
	this->global = global;
}

unsigned int symTabNode::getMemorySize(void) const {
	return memSize;
}

symTabNode* symTabNode::getUType(void) const {
	assert(type == T_UTYPE);
	return utype;
}

void symTabNode::setUType(symTabNode* utype) {
	assert(type == T_UTYPE);
	this->utype = utype;
}

symTabNode* symTabNode::getChild(void) const {
	return child;
}

expr* symTabNode::getInitExpr(void) const {
	return init;
}

int symTabNode::getChanCapacity(void) const {
	assert(type == T_CHAN);
	return capacity;
}

fsm* symTabNode::getFsm(void) const {
	assert(type == T_PROC || type == T_NEVER);
	return childFsm;
}


/**
 * Initialises the values of memSize and memOffset of all variables
 * in the symTab and its descendants and starts with the node given
 * as the first parameter.  The initial memory offset is given as
 * a parameter (usually 0).
 *
 * The function will also lookup all variable references and replace
 * them by pointers.  If a variable cannot be found, execution aborts.
 *
 * The return value is the next offset to be used after the variables
 * of the symtab were added.
 */
unsigned int symTabNode::processVariables(symTabNode* globalSymTab, const mTypeNode* mTypes, unsigned int iOffset, bool bGlobal) {
	global = bGlobal;
	if(init && init->getType() != astNode::E_EXPR_CONST && init->getType() != astNode::E_EXPR_TRUE && init->getType() != astNode::E_EXPR_FALSE) 
		assert(false);
	memSize = this->getTypeSize();
	memOffset = iOffset;
	unsigned int iMemSpace = memSize * bound;
	return next->processVariables(globalSymTab, mTypes, iOffset + iMemSpace, bGlobal);
}

unsigned int chanSymNode::processVariables(symTabNode* global, const mTypeNode* mTypes, unsigned int offset, bool isGlobal) {
	assert(init);
	unsigned int memSpace = 0;
	this->memOffset = offset;
	this->memSize = child->processVariables(global, mTypes, 0, 0);
	if((memSpace = memSize * capacity * bound + bound));
	else memSpace = memSize * bound + bound;
	return next->processVariables(global, mTypes, offset + memSpace, isGlobal);
}

unsigned int tdefSymNode::processVariables(symTabNode* global, const mTypeNode* mTypes, unsigned int offset, bool isGlobal) {
	memSize = child->processVariables(global, mTypes, 0, false);
	return next->processVariables(global, mTypes, offset, isGlobal);
}

unsigned int procSymNode::processVariables(symTabNode* global, const mTypeNode* mTypes, unsigned int offset, bool isGlobal) {
	childFsm->resolveVariables(global, mTypes);
	if(init && init->getType() == astNode::E_EXPR_COUNT)
		init->resolveVariables(global, mTypes);
	memSize = childFsm->processVariables(global, mTypes, 0, 0);
	return next->processVariables(global, mTypes, offset, isGlobal);
}

unsigned int neverSymNode::processVariables(symTabNode* global, const mTypeNode* mTypes, unsigned int offset, bool isGlobal) {
	childFsm->resolveVariables(global, mTypes);
	if(init && init->getType() == astNode::E_EXPR_COUNT)
		init->resolveVariables(global, mTypes);
	//childFsm->orderAcceptTransitions();
	memSize = childFsm->processVariables(global, mTypes, 0, 0);
	return next->processVariables(global, mTypes, offset, isGlobal);
}

unsigned int utypeSymNode::processVariables(symTabNode* global, const mTypeNode* mTypes, unsigned int offset, bool isGlobal) {
	memSize = utype->getMemorySize();
	memOffset = offset;
	unsigned int iMemSpace = memSize * bound;
	return next->processVariables(global, mTypes, offset + iMemSpace, isGlobal); 
}

/**
 * Helper function, prints "count" spaces and at each levelStep a >.
 */
void spaces(int count) {
	int i;
	for(i=0; i <= count; i++) {
		if((i % LEVEL_STEP) == 0) printf(">");
		printf(" ");
	}
}

/**
 * Prints the content of the symTab to stdout (recursively).
 *  - level denotes the number of spaces to be used to indent the output.
 *  - title is the title of the symTab.
 */
void symTabNode::printSymTab(int level, const std::string& title) const {
	
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
																			(childFsm  ? "yes" : "no"));
	if((type == symTabNode::T_TDEF || type == symTabNode::T_CHAN) && child != NULL) {
		child->printSymTab(level + LEVEL_STEP, name);
		spaces(level);
		printf("\n");
	}
	if(type == symTabNode::T_PROC || type == symTabNode::T_NEVER) {
		assert(childFsm);
		childFsm->getSymTab()->printSymTab(level + LEVEL_STEP, name);
		spaces(level);
		printf("\n");
	}
	if(next) next->printSymTab(level, nullptr);
}


/*
 * MTYPES
 * * * * * * * * * * * * * * * * * * * * * * * */

mTypeNode::mTypeNode(const std::string& name){

	this->name = name;
	this->next = nullptr;
	this->prev = this;
}

mTypeNode* mTypeNode::addMType(const std::string& name){

	mTypeNode* newNode = new mTypeNode(name);
	newNode->value = this->prev->value + 1;
	newNode->prev = this->prev;
	this->prev->next = newNode;
	this->prev = newNode;
	return newNode;
}

/**
 * Adds an MType to the list (automatically assigns it a value).
 */

/**
 * Gets the value of an MType based on the name.
 * If the MType does not exist, it will return -1.
 */
int mTypeNode::getMTypeValue(const std::string& name) const {
	
	if(name == getName())
		return value;
	else if(this->next)
		return next->getMTypeValue(name);
	else
		return -1;
}

/**
 * Gets the name of the MType based on its value.
 * If the value does not exist, it will return NULL.
 */
std::string mTypeNode::getMTypeName(int value) const {
	const mTypeNode* it = this;
	if(this->value == value) 
		return name;
	
	if(prev && this->value < prev->value / 2) {
		while((it = it->next))
			if(it->value == value) 
				return it->getName();
	} else {
		while((it = it->prev))
			if(it->value == value) 
				return it->getName();
	}
	assert(false);
	return std::string();
}

/**
 * Prints a list of MTypes to stdout.
 */
void mTypeNode::printMTypes() {
	printf("MTypes:");
	mTypeNode* it = this;
	while(it != nullptr) {
		printf(" %s (%d)", it->getName().c_str(), it->value);
		it = it->next;
	}
	printf("\n");
}

std::string mTypeNode::getName(void) const {
	return name;
}