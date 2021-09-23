#include "varSymNode.h"
#include "symTabVisitor.h"
#include "expression.h"

#include "naSymNode.h"
#include "bitSymNode.h"
#include "boolSymNode.h"
#include "byteSymNode.h"
#include "shortSymNode.h"
#include "intSymNode.h"
#include "cidSymNode.h"
#include "pidSymNode.h"
#include "utypeSymNode.h"
#include "unsgnSymNode.h"
#include "mTypeSymNode.h"

varSymNode* varSymNode::merge(varSymNode* symTab, varSymNode* newNode){
	if (!symTab)
		return newNode;
	if (!newNode)
		return symTab;

	symTabNode *newlistTail = newNode->prev;
	newNode->prev = symTab->prev;
	newNode->prev->setNext(newNode);
	symTab->prev = newlistTail;
	return symTab;
}

varSymNode::~varSymNode(void) {
	if(init)
		delete init;
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
unsigned int varSymNode::processVariables(symTabNode *globalSymTab, const mTypeList *mTypes, unsigned int iOffset, bool bGlobal) {
	global = bGlobal;
	if (init && init->getType() != astNode::E_EXPR_CONST && init->getType() != astNode::E_EXPR_TRUE && init->getType() != astNode::E_EXPR_FALSE)
		assert(false);
	memSize = this->getTypeSize();
	memOffset = iOffset;
	unsigned int iMemSpace = memSize * bound;
	return !next ? iOffset + iMemSpace : next->processVariables(globalSymTab, mTypes, iOffset + iMemSpace, bGlobal);
}

varSymNode *varSymNode::createSymTabNode(Type type, const varSymNode &old) {
	assert(old.getType() == T_NA);
	return createSymTabNode(type, old.getLineNb(), old.getName(), old.getBound(), old.getInitExpr());
}

template<> varSymNode* varSymNode::createSymTabNode<symTabNode::T_BIT>(int lineNb, const std::string& name, int bound, expr* init) {
	return new bitSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymTabNode<symTabNode::T_BOOL>(int lineNb, const std::string& name, int bound, expr* init) {
	return new boolSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymTabNode<symTabNode::T_NA>(int lineNb, const std::string& name, int bound, expr* init) {
	return new naSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymTabNode<symTabNode::T_BYTE>(int lineNb, const std::string& name, int bound, expr* init) {
	return new byteSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymTabNode<symTabNode::T_CID>(int lineNb, const std::string& name, int bound, expr* init) {
	return new cidSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymTabNode<symTabNode::T_INT>(int lineNb, const std::string& name, int bound, expr* init) {
	return new intSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymTabNode<symTabNode::T_PID>(int lineNb, const std::string& name, int bound, expr* init) {
	return new pidSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymTabNode<symTabNode::T_SHORT>(int lineNb, const std::string& name, int bound, expr* init) {
	return new shortSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymTabNode<symTabNode::T_UNSGN>(int lineNb, const std::string& name, int bound, expr* init) {
	return new unsgnSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymTabNode<symTabNode::T_UTYPE>(int lineNb, const std::string& name, int bound, expr* init) {
	return new utypeSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymTabNode<symTabNode::T_MTYPE>(int lineNb, const std::string& name, int bound, expr* init) {
	return new mTypeSymNode(lineNb, name, bound, init);
}

varSymNode *varSymNode::createSymTabNode(Type type, int lineNb, const std::string& name, int bound, expr* init) {

	switch (type)
	{
	case T_NA:
		return createSymTabNode<T_NA>(lineNb, name, bound, init);
	case T_BIT:
		return createSymTabNode<T_BIT>(lineNb, name, bound, init);
	case T_BOOL:
		return createSymTabNode<T_BOOL>(lineNb, name, bound, init);
	case T_BYTE:
		return createSymTabNode<T_BYTE>(lineNb, name, bound, init);
	case T_SHORT:
		return createSymTabNode<T_SHORT>(lineNb, name, bound, init);
	case T_INT:
		return createSymTabNode<T_INT>(lineNb, name, bound, init);
	case T_UNSGN: // not supported yet
		return createSymTabNode<T_UNSGN>(lineNb, name, bound, init);
	case T_MTYPE:
		return createSymTabNode<T_MTYPE>(lineNb, name, bound, init);
	case T_CID: // Channel: capacity used; children denote message fields
		return createSymTabNode<T_CID>(lineNb, name, bound, init);
	case T_PID: // Channel: capacity used; children denote message fields
		return createSymTabNode<T_PID>(lineNb, name, bound, init);
	case T_UTYPE: // Type of variable is a user type (basically, a T_TDEF record is being used as the type): utype points to the type record
		return createSymTabNode<T_UTYPE>(lineNb, name, bound, init);
	default:
		assert(false);
	}

	return nullptr;
}
