#ifndef INT_SYM_NODE_H
#define INT_SYM_NODE_H

#include "varSymNode.h"

//T_INT
class intSymNode : public varSymNode{
public:
	intSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr)
		: varSymNode(symbol::T_INT, lineNb, name, bound, init)
	{}

	std::string getTypeName(void) const override {
		return "int";
	}

	int getTypeSize(void) const override {
		return 4;
	}

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;
};

#endif
