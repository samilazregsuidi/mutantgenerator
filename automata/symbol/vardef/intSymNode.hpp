#ifndef INT_SYM_NODE_H
#define INT_SYM_NODE_H

#include "varSymNode.hpp"

//T_INT
class intSymNode : public varSymNode{
public:
	intSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr);

	std::string getBasicTypeName(void) const override;

	int getTypeSize(void) const override;

	int getUpperBound(void) const override;
	
	int getLowerBound(void) const override;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;
};

#endif
