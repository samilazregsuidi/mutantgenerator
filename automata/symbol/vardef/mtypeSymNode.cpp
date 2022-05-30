#include "mtypeSymNode.hpp"
#include "symTabVisitor.hpp"

mtypeSymNode::mtypeSymNode(int lineNb, const std::string& name, int bound, expr* init)
	: varSymNode(symbol::T_MTYPE, lineNb, name, bound, init)
{}

mtypeSymNode::~mtypeSymNode() {}

std::string mtypeSymNode::getTypeName(void) const {
	return "mtype"+ (getBound() > 1? "[" + std::to_string(getBound()) + "]": "");
}

int mtypeSymNode::getTypeSize(void) const {
	return 1;
}

bool mtypeSymNode::castTo(const symbol* sym) const {
	return sym->getType() == T_MTYPE;
}

void mtypeSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitMtype(this);
}

void mtypeSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitMtype(this);
}

/*************************************************************************************************/

bool cmtypeSymNode::castTo(const symbol* sym) const {
	return sym->getType() == T_MTYPE;
}

cmtypeSymNode::cmtypeSymNode(int lineNb, const std::string& name, int value)
	: varSymNode(symbol::T_MTYPE, lineNb, name)
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

int cmtypeSymNode::getIntValue(void) const {
	return value;
}

void cmtypeSymNode::acceptVisitor(symTabVisitor* visitor) {
	visitor->visitCmtype(this);
}

void cmtypeSymNode::acceptVisitor(symTabConstVisitor* visitor) const {
	visitor->visitCmtype(this);
}
