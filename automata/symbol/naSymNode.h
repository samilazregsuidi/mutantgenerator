#ifndef NA_SYM_NODE_H
#define NA_SYM_NODE_H

#include "varSymNode.h"

class naSymNode : public varSymNode{
public:
	naSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr)
		: varSymNode(symbol::T_NA, lineNb, name, bound, init)
	{}

	std::string getTypeName(void) const override {
		assert(false);
		return "NA";
	}

	int getTypeSize(void) const override {
		assert(false);
		return 0;
	}

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;
};

#endif
