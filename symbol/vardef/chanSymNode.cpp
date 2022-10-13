#include "chanSymNode.hpp"
#include "symTabVisitor.hpp"

chanSymNode::chanSymNode(int lineNb, const std::string& name, int bound, int capacity, const std::list<varSymNode*>& types)
	: varSymNode(symbol::T_CHAN, lineNb, name, bound)
{
	this->capacity = capacity;
	this->types = types;
}

chanSymNode::chanSymNode(int lineNb, const std::string& name, int bound, expr* init)
	: varSymNode(symbol::T_CHAN, lineNb, name, bound, init)
{
	this->capacity = 0;
}

chanSymNode::~chanSymNode(){
	for(auto it : types)
		delete it;
}

std::string chanSymNode::getBasicTypeName(void) const {
	return "chan";
}

int chanSymNode::getTypeSize(void) const {
	int res = 0;
	for (auto t : types) 
		res += t->getSizeOf();
	return res * capacity;
}

const std::list<varSymNode*>& chanSymNode::getTypeList(void) const {
	return types;
}

int chanSymNode::getCapacity(void) const {
	return capacity;
}

bool chanSymNode::castTo(const symbol* sym) const {
	if(type == sym->getType()) { 
		auto other = dynamic_cast<const chanSymNode*>(sym);
		assert(other);
		
		if(types.size() != other->getTypeList().size())
			return false;

		auto it = types.cbegin();
		auto itt = other->getTypeList().cbegin();
		for(; it != types.cend(), itt != other->getTypeList().cend(); ++it, ++itt) {
			if(!(*it)->castTo(*itt))
				return false;
		}

		return capacity == other->getCapacity();
		//return bound == other->getBound() && capacity == other->getCapacity();
	}
	return false;
}

void chanSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitChan(this);
}

void chanSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitChan(this);
}

/*unsigned int chanSymNode::processVariables(symTabNode *global, const mTypeList *mTypes, unsigned int iOffset, bool isGlobal) {
	assert(init);
	unsigned int iMemSpace = 0;
	this->memOffset = iOffset;
	this->memSize = child->processVariables(global, mTypes, 0, 0);
	if ((iMemSpace = memSize * capacity * bound + bound))
		;
	else
		iMemSpace = memSize * bound + bound;
	return !next ? iOffset + iMemSpace : next->processVariables(global, mTypes, iOffset + iMemSpace, isGlobal);
}*/