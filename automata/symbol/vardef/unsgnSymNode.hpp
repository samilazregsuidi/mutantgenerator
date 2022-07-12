#ifndef UNSGN_SYM_NODE_H
#define UNSGN_SYM_NODE_H

#include "varSymNode.hpp"

//T_UNSGN
class unsgnSymNode : public varSymNode{
public:
	unsgnSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr);

	std::string getTypeName(void) const override;

	int getTypeSize(void) const override;

	int getUpperBound(void) const override;
	
	int getLowerBound(void) const override;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;
};

#endif