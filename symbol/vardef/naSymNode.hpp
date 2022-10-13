#ifndef NA_SYM_NODE_H
#define NA_SYM_NODE_H

#include "varSymNode.hpp"

class naSymNode : public varSymNode{
public:
	naSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr);

	std::string getBasicTypeName(void) const override;

	int getTypeSize(void) const override;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;
};

#endif
