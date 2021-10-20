#ifndef PID_SYM_NODE_H
#define PID_SYM_NODE_H

#include "varSymNode.h"

//T_PID
class pidSymNode : public varSymNode{
public:
	pidSymNode(int lineNb, const std::string& name, int bound = 1, expr* init = nullptr)
		: varSymNode(symbol::T_PID, lineNb, name, bound, init)
	{}
	
	std::string getTypeName(void) const override {
		return "pid";
	}

	int getTypeSize(void) const override {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;
};

#endif