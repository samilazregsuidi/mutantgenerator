#include "mtypeSymNode.hpp"

#include "mtypedefSymNode.hpp"
#include "symTabVisitor.hpp"

#include "symTable.hpp"

mtypeSymNode::mtypeSymNode(int lineNb, const std::string& name, int bound, expr* init)
	: varSymNode(symbol::T_MTYPE, lineNb, name, bound, init)
{}

mtypeSymNode::~mtypeSymNode() {}

std::string mtypeSymNode::getBasicTypeName(void) const {
	return "mtype";
}

void mtypeSymNode::setSymTable(symTable* parent) {
	this->parent = parent;
	auto mtypedefs = this->parent->getGlobalSymbols<mtypedefSymNode*>();
	assert(mtypedefs.size() == 1);
	def = *mtypedefs.begin();
}

int mtypeSymNode::getTypeSize(void) const {
	return 1;
}

const mtypedefSymNode* mtypeSymNode::getMTypeDef(void) const {
	return def;
}

int mtypeSymNode::getUpperBound(void) const {
	return def->getUpperBound();
}
	
int mtypeSymNode::getLowerBound(void) const {
	return 0;
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
	return sym->getType() == T_CMTYPE || sym->getType() == T_MTYPE;
}

cmtypeSymNode::cmtypeSymNode(int lineNb, mtypedefSymNode* def, const std::string& name, int value)
	: varSymNode(symbol::T_CMTYPE, lineNb, name)
	, value(value)
	, def(def)
{
	def->addCMType(this);
	mask = READ_ACCESS;
}

std::string cmtypeSymNode::getBasicTypeName(void) const {
	return "cmtype";
}

int cmtypeSymNode::getTypeSize(void) const {
	return 0;
}

int cmtypeSymNode::getUpperBound(void) const {
	return def->getUpperBound();
}
	
int cmtypeSymNode::getLowerBound(void) const {
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
