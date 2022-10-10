#ifndef VARIANT_SYM_NODE_H
#define VARIANT_SYM_NODE_H

#include "symbol.hpp"

//T_VARIANT
class variantSymNode : public symbol {
public:
	variantSymNode(int lineNb, const std::string& name, expr* feat_expr);

	std::string getBasicTypeName(void) const override;

	std::string getTypeName(void) const override;

	int getTypeSize(void) const override;

	operator std::string(void) const override;

	//void printGraphViz(std::ofstream& file) const;

private:
	expr* feat_expr;
};

#endif