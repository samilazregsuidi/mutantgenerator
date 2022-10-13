#ifndef PID_SYM_NODE_H
#define PID_SYM_NODE_H

#include "varSymNode.hpp"

//T_PID
class pidSymNode : public varSymNode {
public:
	pidSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr);
	
	std::string getBasicTypeName(void) const override;

	int getTypeSize(void) const override;

	int getUpperBound(void) const override;
	
	int getLowerBound(void) const override;

	bool castTo(const symbol* sym) const override;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;
};

#endif