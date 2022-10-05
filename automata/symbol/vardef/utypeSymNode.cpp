#include "utypeSymNode.hpp"
#include "symTabVisitor.hpp"
#include "tdefSymNode.hpp"

utypeSymNode::utypeSymNode(tdefSymNode* utype, int lineNb)
	: varSymNode(symbol::T_UTYPE, lineNb, std::string())
{
	assert(utype != nullptr && utype->getType() == symbol::T_TDEF);
	this->utype = utype;
}

utypeSymNode::utypeSymNode(int lineNb, const std::string& name, int bound, expr* init)
		: varSymNode(symbol::T_UTYPE, lineNb, name, bound, init)
		, utype(nullptr)
{}

//unsigned int processVariables(symbol* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal) override ;

tdefSymNode* utypeSymNode::getUType(void) const {
	return utype;
}

void utypeSymNode::setUType(tdefSymNode* utype) {
	assert(utype);
	this->utype = utype;
}

int utypeSymNode::getTypeSize(void) const {
	assert(utype);
	unsigned int res = 0;
	for(auto field : utype->getFields()) {
		res += field->getSizeOf();
	}
	return res;
}

std::string utypeSymNode::getBasicTypeName(void) const {
	return utype->getName();
}

void utypeSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitUtype(this);
}

void utypeSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitUtype(this);
}

/*unsigned int utypeSymNode::processVariables(symbol *global, const mTypeList *mTypes, unsigned int iOffset, bool isGlobal) {
	memSize = utype->getMemorySize();
	memOffset = iOffset;
	unsigned int iMemSpace = memSize * bound;
	return !next ? iOffset + iMemSpace : next->processVariables(global, mTypes, iOffset + iMemSpace, isGlobal);
}*/