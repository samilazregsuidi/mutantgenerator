#ifndef CHAN_SYM_NODE_H
#define CHAN_SYM_NODE_H

#include "varSymNode.h"

//T_CHAN
class chanSymNode : public varSymNode{
public:
	chanSymNode(int lineNb, const std::string& name, int bound, int capacity, varSymNode* child)
		: varSymNode(symTabNode::T_CHAN, lineNb, name, bound)
	{
		this->capacity = capacity;
		this->child = child;
	}

	~chanSymNode(void) override ;

	std::string getTypeName(void) const override {
		return "chan";
	}

	int getTypeSize(void) const override {
		return 0;
	}

	unsigned int processVariables(symTabNode* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal) override ;

	void acceptVisitor(symTabVisitor* visitor) const override;

private:
	varSymNode* child;
	int capacity;
};

#endif
