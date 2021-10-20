#ifndef BYTE_SYM_NODE_H
#define BYTE_SYM_NODE_H

#include "varSymNode.h"

//T_BYTE
class byteSymNode : public varSymNode{
public:
	byteSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr)
		: varSymNode(symbol::T_BYTE, lineNb, name, bound, init)
	{}

	std::string getTypeName(void) const override {
		return "byte";
	}

	int getTypeSize(void) const override {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;
};

#endif