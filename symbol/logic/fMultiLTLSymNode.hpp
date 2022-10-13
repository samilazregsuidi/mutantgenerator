#ifndef F_MULTI_LTL_H
#define F_MULTI_LTL_H

#include <list>

#include "symbol.hpp"

class variantQuantifier;

//T_FMULTI_LTL
class fMultiLTLSymNode : public symbol {
public:
	fMultiLTLSymNode(const std::string& name, const std::list<variantQuantifier*>& variants, expr* formula, int lineNb);

	std::string getTypeName(void) const override;

	std::string getBasicTypeName(void) const override;

	int getTypeSize(void) const override;

	const std::list<std::string>& getParams(void) const;

	operator std::string(void) const override;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;

	//void printGraphViz(std::ofstream& file) const;

private:
	std::list<variantQuantifier*> variants;
	expr* formula;
};

#endif
