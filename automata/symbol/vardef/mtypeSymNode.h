#ifndef MTYPE_SYM_NODE_H
#define MTYPE_SYM_NODE_H

#include "varSymNode.h"

//T_MTYPE
class mtypeSymNode : public varSymNode{
public:
	mtypeSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr)
		: varSymNode(symbol::T_MTYPE, lineNb, name, bound, init)
	{}

	std::string getTypeName(void) const override {
		return "mtype";
	}

	int getTypeSize(void) const override {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;
};

#endif