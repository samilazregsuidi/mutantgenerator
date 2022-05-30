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

mtypedefSymNode::mtypedefSymNode(std::unordered_map<std::string, cmtypeSymNode*> mtypes, int lineNb)
	: symbol(symbol::T_MTYPE_DEF, "mtype", lineNb)
{
	this->mtypes = mtypes;
	for(auto mtype : mtypes)
		mtype.second->def = this;
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

std::string mtypedefSymNode::getCmtypeSymNodeName(int value) const {
	for(auto cmtype : mtypes) {
		if(cmtype.second->getIntValue() == value)
			return cmtype.second->getName();
	}
}