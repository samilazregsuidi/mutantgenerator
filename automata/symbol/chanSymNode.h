#ifndef CHAN_SYM_NODE_H
#define CHAN_SYM_NODE_H

#include <list>

#include "varSymNode.h"

//T_CHAN
class chanSymNode : public varSymNode{
public:
	chanSymNode(int lineNb, const std::string& name, int bound, int capacity, std::list<symbol*> types)
		: varSymNode(symbol::T_CHAN, lineNb, name, bound)
	{
		this->capacity = capacity;
		this->types = types;
	}

	~chanSymNode(void) override ;

	std::string getTypeName(void) const override {
		return "chan";
	}

	int getTypeSize(void) const override {
		return 0;
	}

	const std::list<symbol*>& getTypeList(void) const {
		return types;
	}

	int getCapacity(void) const {
		return capacity;
	}
	//unsigned int processVariables(symbol* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal) override ;

	void acceptVisitor(symTabVisitor* visitor) const override;

private:
	std::list<symbol*> types;
	int capacity;
};

#endif
