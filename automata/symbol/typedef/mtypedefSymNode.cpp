#include "mtypedefSymNode.hpp"
#include "mtypeSymNode.hpp"

#include <cassert>

#include "symTabVisitor.hpp"

/***********************************************************************************************/

void mtypedefSymNode::acceptVisitor(symTabVisitor* visitor) {
	visitor->visitMtypedef(this);
}

void mtypedefSymNode::acceptVisitor(symTabConstVisitor* visitor) const {
	visitor->visitMtypedef(this);
}

mtypedefSymNode::mtypedefSymNode(const std::unordered_map<std::string, cmtypeSymNode*>& mtypes, int lineNb)
	: symbol(symbol::T_MTYPE_DEF, "mtype", lineNb)
{
	assert(mtypes.size() != 0);

	this->mtypes = mtypes;
	for(auto mtype : mtypes)
		mtype.second->def = this;
}

mtypedefSymNode::mtypedefSymNode(int lineNb)
	: symbol(symbol::T_MTYPE_DEF, "mtype", lineNb)
{}

std::string mtypedefSymNode::getTypeName(void) const {
	return "mtypedef";
}

std::string mtypedefSymNode::getBasicTypeName(void) const {
	return "mtypedef";
}

int mtypedefSymNode::getTypeSize(void) const {
	return 0;
}

int mtypedefSymNode::getUpperBound(void) const {
	assert(mtypes.size() > 0);
	return mtypes.size() - 1;
}
	
int mtypedefSymNode::getLowerBound(void) const {
	return 0;
}

const std::unordered_map<std::string, cmtypeSymNode*>& mtypedefSymNode::getMTypeList(void) const {
	return mtypes;
}

void mtypedefSymNode::addCMType(cmtypeSymNode* mtype) {
	//assert(mtypes.at(mtype->getName()) == nullptr);
	mtypes[mtype->getName()] = mtype;
}

std::string mtypedefSymNode::getCmtypeSymNodeName(int value) const {
	for(auto cmtype : mtypes) {
		if(cmtype.second->getIntValue() == value)
			return cmtype.second->getName();
	}
	assert(false);
	return "";
}