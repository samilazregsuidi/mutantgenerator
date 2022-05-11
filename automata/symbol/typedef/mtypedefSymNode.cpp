#include "mtypedefSymNode.hpp"

#include <cassert>

#include "symTabVisitor.hpp"

bool cmtypeSymNode::castTo(const symbol* sym) const {
	return sym->getType() == T_MTYPE;
}

cmtypeSymNode::cmtypeSymNode(int lineNb, const std::string& name, int value)
	: symbol(symbol::T_MTYPE, lineNb, name)
{
	this->value = value;
	this->mask = READ_ACCESS;
}

std::string cmtypeSymNode::getTypeName(void) const {
	return "cmtype";
}

int cmtypeSymNode::getTypeSize(void) const {
	return 0;
}

void cmtypeSymNode::acceptVisitor(symTabVisitor* visitor) {
	visitor->visitCmtype(this);
}

void cmtypeSymNode::acceptVisitor(symTabConstVisitor* visitor) const {
	visitor->visitCmtype(this);
}

/***********************************************************************************************/

void mtypedefSymNode::acceptVisitor(symTabVisitor* visitor) {
	visitor->visitMtypedef(this);
}

void mtypedefSymNode::acceptVisitor(symTabConstVisitor* visitor) const {
	visitor->visitMtypedef(this);
}

mtypedefSymNode::mtypedefSymNode(std::unordered_map<std::string, cmtypeSymNode*> mtypes, int lineNb)
	: symbol(symbol::T_MTYPE_DEF, "mtype", lineNb)
{
	this->mtypes = mtypes;
}

std::string mtypedefSymNode::getTypeName(void) const {
	return "mtypedef";
}

int mtypedefSymNode::getTypeSize(void) const {
	return 0;
}

const std::unordered_map<std::string, cmtypeSymNode*>& mtypedefSymNode::getMTypeList(void) const {
	return mtypes;
}