#ifndef SHORT_SYM_NODE_H
#define SHORT_SYM_NODE_H

#include "varSymNode.h"

//T_SHORT
class shortSymNode : public varSymNode{
public:
	shortSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr)
		: varSymNode(symTabNode::T_SHORT, lineNb, name, bound, init)
	{}

	std::string getTypeName(void) const override {
		return "short";
	}

	int getTypeSize(void) const override {
		return 2;
	}

	void acceptVisitor(symTabVisitor* visitor) const override;
};

#endif
