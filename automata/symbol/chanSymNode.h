#include "varSymNode.h"

//T_CHAN
class chanSymNode : public varSymNode{
public:
	chanSymNode(int lineNb, const std::string& sVal, int bound, int capacity, varSymNode* child)
		: varSymNode(symTabNode::T_CHAN, lineNb, sVal, bound)
	{
		this->child = child;
	}

	std::string getTypeName(void) const {
		return "chan";
	}

	int getTypeSize(void) const {
		return 0;
	}

	unsigned int processVariables(symTabNode* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal);

	void acceptVisitor(symTabVisitor* visitor) const ;

private:
	varSymNode* child;
	int capacity;
};
