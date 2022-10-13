#include "varSymNode.hpp"
#include "symTabVisitor.hpp"
#include "expr.hpp"

#include "naSymNode.hpp"
#include "bitSymNode.hpp"
#include "boolSymNode.hpp"
#include "byteSymNode.hpp"
#include "shortSymNode.hpp"
#include "intSymNode.hpp"
#include "cidSymNode.hpp"
#include "pidSymNode.hpp"
#include "utypeSymNode.hpp"
#include "unsgnSymNode.hpp"
#include "mtypedefSymNode.hpp"

#include <limits>

varSymNode::varSymNode(Type type, int lineNb, const std::string& name, unsigned int bound, expr* init)
	: symbol(type, lineNb, name)
{
	/*if(init)
		assert(init->getType() == astNode::E_EXPR_CONST);*/

	this->init = init;
	this->bound = bound;
}

varSymNode::~varSymNode(void) {
	if(init)
		delete init;
}

void varSymNode::setInitExpr(expr* newInit) {
	
	assert(newInit->getType() == astNode::E_EXPR_CONST);

	if (init)
		delete init;
		
	init = newInit;
}

expr* varSymNode::getInitExpr(void) const {
	return init;
}

unsigned int varSymNode::getBound(void) const {
	return bound;
}

std::string varSymNode::getTypeName(void) const {
	return getBasicTypeName() + (getBound() > 1? "[" + std::to_string(getBound()) + "]": "");
}

int varSymNode::getUpperBound(void) const {
	assert(false);
}
	
int varSymNode::getLowerBound(void) const {
	assert(false);
}

bool varSymNode::castTo(const symbol* sym) const {
	//if(type == sym->getType() && bound == dynamic_cast<const varSymNode*>(sym)->getBound()){
	if(type == sym->getType()){
		//assert(dynamic_cast<const varSymNode*>(sym));
		assert(static_cast<const varSymNode*>(sym));
		return true;
	}
	return false;
}

unsigned int varSymNode::getSizeOf(void) const {
	return getTypeSize() * bound;
}

void varSymNode::printGraphViz(std::ofstream& file) const {
	file << "{ <" << getID() << "> " << getTypeName() << "|" << getName() + (init? " : " + std::string(*init) : "")  << "| " << getSizeOf() << " "<< ((getTypeSize() > 1)? "bytes" : "byte") <<" | "<< (getLineNb()!=0 ? "line " + std::to_string(getLineNb()) : "predef.") << " }";
}

varSymNode *varSymNode::createSymbol(symbol::Type type, const varSymNode &old) {
	assert(old.getType() == T_NA);
	return createSymbol(type, old.getLineNb(), old.getName(), old.getBound(), old.getInitExpr());
}

template<> varSymNode* varSymNode::createSymbol<symbol::T_BIT>(int lineNb, const std::string& name, unsigned int bound, expr* init) {
	return new bitSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymbol<symbol::T_BOOL>(int lineNb, const std::string& name, unsigned int bound, expr* init) {
	return new boolSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymbol<symbol::T_NA>(int lineNb, const std::string& name, unsigned int bound, expr* init) {
	return new naSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymbol<symbol::T_BYTE>(int lineNb, const std::string& name, unsigned int bound, expr* init) {
	return new byteSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymbol<symbol::T_CID>(int lineNb, const std::string& name, unsigned int bound, expr* init) {
	return new cidSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymbol<symbol::T_INT>(int lineNb, const std::string& name, unsigned int bound, expr* init) {
	return new intSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymbol<symbol::T_PID>(int lineNb, const std::string& name, unsigned int bound, expr* init) {
	return new pidSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymbol<symbol::T_SHORT>(int lineNb, const std::string& name, unsigned int bound, expr* init) {
	return new shortSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymbol<symbol::T_UNSGN>(int lineNb, const std::string& name, unsigned int bound, expr* init) {
	return new unsgnSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymbol<symbol::T_UTYPE>(int lineNb, const std::string& name, unsigned int bound, expr* init) {
	return new utypeSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymbol<symbol::T_MTYPE>(int lineNb, const std::string& name, unsigned int bound, expr* init) {
	return new mtypeSymNode(lineNb, name, bound, init);
}

template<> varSymNode* varSymNode::createSymbol<symbol::T_CHAN>(int lineNb, const std::string& name, unsigned int bound, expr* init) {
	return new chanSymNode(lineNb, name, bound, init);
}

varSymNode *varSymNode::createSymbol(Type type, int lineNb, const std::string& name, unsigned int bound, expr* init) {

	switch (type)
	{
	case T_NA:
		return createSymbol<T_NA>(lineNb, name, bound, init);
	case T_BIT:
		return createSymbol<T_BIT>(lineNb, name, bound, init);
	case T_BOOL:
		return createSymbol<T_BOOL>(lineNb, name, bound, init);
	case T_BYTE:
		return createSymbol<T_BYTE>(lineNb, name, bound, init);
	case T_SHORT:
		return createSymbol<T_SHORT>(lineNb, name, bound, init);
	case T_INT:
		return createSymbol<T_INT>(lineNb, name, bound, init);
	case T_UNSGN: // not supported yet
		return createSymbol<T_UNSGN>(lineNb, name, bound, init);
	case T_MTYPE:
		return createSymbol<T_MTYPE>(lineNb, name, bound, init);
	case T_CID: // Channel: capacity used; children denote message fields
		return createSymbol<T_CID>(lineNb, name, bound, init);
	case T_PID: // Channel: capacity used; children denote message fields
		return createSymbol<T_PID>(lineNb, name, bound, init);
	case T_UTYPE: // Type of variable is a user type (basically, a T_TDEF record is being used as the type): utype points to the type record
		return createSymbol<T_UTYPE>(lineNb, name, bound, init);
	case T_CHAN:
		return createSymbol<T_CHAN>(lineNb, name, bound, init);
	default:
		assert(false);
	}

	return nullptr;
}

template<> int varSymNode::getLowerBound<symbol::T_BIT>(void) {
	return 0;
}

template<> int varSymNode::getLowerBound<symbol::T_BOOL>(void) {
	return std::numeric_limits<bool>::min();
}

template<> int varSymNode::getLowerBound<symbol::T_BYTE>(void) {
	return std::numeric_limits<unsigned char>::min();
}

template<> int varSymNode::getLowerBound<symbol::T_SHORT>(void) {
	return std::numeric_limits<short>::min();
}

template<> int varSymNode::getLowerBound<symbol::T_INT>(void) {
	return std::numeric_limits<int>::min();
}

template<> int varSymNode::getLowerBound<symbol::T_UNSGN>(void) {
	assert(false);
	return 0;
}

template<> int varSymNode::getLowerBound<symbol::T_MTYPE>(void) {
	return std::numeric_limits<unsigned char>::min();
}

template<> int varSymNode::getLowerBound<symbol::T_CMTYPE>(void) {
	return std::numeric_limits<unsigned char>::min();
}

template<> int varSymNode::getLowerBound<symbol::T_CID>(void) {
	return std::numeric_limits<unsigned int>::min();
}

template<> int varSymNode::getLowerBound<symbol::T_PID>(void) {
	return std::numeric_limits<unsigned char>::min();
}

template<> int varSymNode::getLowerBound<symbol::T_UTYPE>(void) {
	assert(false);
	return 0;
}

template<> int varSymNode::getLowerBound<symbol::T_CHAN>(void) {
	assert(false);
	return 0;
}

int varSymNode::getLowerBound(Type type) {
	switch (type)
	{
	case T_NA:
		assert(false);
		//return getLowerBound<T_NA>();
	case T_BIT:
		return getLowerBound<T_BIT>();
	case T_BOOL:
		return getLowerBound<T_BOOL>();
	case T_BYTE:
		return getLowerBound<T_BYTE>();
	case T_SHORT:
		return getLowerBound<T_SHORT>();
	case T_INT:
		return getLowerBound<T_INT>();
	case T_UNSGN: // not supported yet
		assert(false);
		//return getLowerBound<T_UNSGN>();
	case T_MTYPE:
		return getLowerBound<T_MTYPE>();
	case T_CMTYPE:
		return getLowerBound<T_CMTYPE>();
	case T_CID: // Channel: capacity used; children denote message fields
		return getLowerBound<T_CID>();
	case T_PID: // Channel: capacity used; children denote message fields
		return getLowerBound<T_PID>();
	case T_UTYPE: // Type of variable is a user type (basically, a T_TDEF record is being used as the type): utype points to the type record
		assert(false);
		//return getLowerBound<T_UTYPE>();
	case T_CHAN:
		assert(false);
		//return getLowerBound<T_CHAN>();
	default:
		assert(false);
	}

	return 0;
}

/***************************************************************/

template<> int varSymNode::getUpperBound<symbol::T_BIT>(void) {
	return 1;
}

template<> int varSymNode::getUpperBound<symbol::T_BOOL>(void) {
	return std::numeric_limits<bool>::max();
}

template<> int varSymNode::getUpperBound<symbol::T_BYTE>(void) {
	return std::numeric_limits<unsigned char>::max();
}

template<> int varSymNode::getUpperBound<symbol::T_SHORT>(void) {
	return std::numeric_limits<short>::max();
}

template<> int varSymNode::getUpperBound<symbol::T_INT>(void) {
	return std::numeric_limits<int>::max();
}

template<> int varSymNode::getUpperBound<symbol::T_UNSGN>(void) {
	assert(false);
	return 0;
}

template<> int varSymNode::getUpperBound<symbol::T_MTYPE>(void) {
	return std::numeric_limits<unsigned char>::max();
}

template<> int varSymNode::getUpperBound<symbol::T_CMTYPE>(void) {
	return std::numeric_limits<unsigned char>::max();
}

template<> int varSymNode::getUpperBound<symbol::T_CID>(void) {
	return std::numeric_limits<unsigned int>::max();
}

template<> int varSymNode::getUpperBound<symbol::T_PID>(void) {
	return std::numeric_limits<unsigned char>::max();
}

template<> int varSymNode::getUpperBound<symbol::T_UTYPE>(void) {
	assert(false);
	return 0;
}

template<> int varSymNode::getUpperBound<symbol::T_CHAN>(void) {
	assert(false);
	return 0;
}

int varSymNode::getUpperBound(Type type) {
	switch (type)
	{
	case T_NA:
		assert(false);
		//return getUpperBound<T_NA>();
	case T_BIT:
		return getUpperBound<T_BIT>();
	case T_BOOL:
		return getUpperBound<T_BOOL>();
	case T_BYTE:
		return getUpperBound<T_BYTE>();
	case T_SHORT:
		return getUpperBound<T_SHORT>();
	case T_INT:
		return getUpperBound<T_INT>();
	case T_UNSGN: // not supported yet
		assert(false);
		//return getUpperBound<T_UNSGN>();
	case T_MTYPE:
		return getUpperBound<T_MTYPE>();
	case T_CMTYPE:
		return getUpperBound<T_CMTYPE>();
	case T_CID: // Channel: capacity used; children denote message fields
		return getUpperBound<T_CID>();
	case T_PID: // Channel: capacity used; children denote message fields
		return getUpperBound<T_PID>();
	case T_UTYPE: // Type of variable is a user type (basically, a T_TDEF record is being used as the type): utype points to the type record
		assert(false);
		//return getUpperBound<T_UTYPE>();
	case T_CHAN:
		assert(false);
		//return getUpperBound<T_CHAN>();
	default:
		assert(false);
	}

	return 0;
}