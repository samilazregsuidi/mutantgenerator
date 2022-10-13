#ifndef VARIANT_SYM_NODE_H
#define VARIANT_SYM_NODE_H

#include "varSymNode.hpp"

//T_VARIANT
class variantSymNode : public varSymNode {
public:
	variantSymNode(int lineNb, const std::string& name, expr* init);

	std::string getBasicTypeName(void) const override;

	std::string getTypeName(void) const override;

	int getTypeSize(void) const override;

	operator std::string(void) const override;

	//void printGraphViz(std::ofstream& file) const;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;

private:
	expr* init;
};

#endif