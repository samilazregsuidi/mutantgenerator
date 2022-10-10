#ifndef F_MULTI_LTL_H
#define F_MULTI_LTL_H

#include <list>

#include "symbol.hpp"

class variantSymNode;

//T_INLINE
class fMultiLTL : public symbol {
public:
	fMultiLTL(const std::string& name, const std::list<std::string>& params, stmnt* block, int lineNb);

	std::string getTypeName(void) const override;

	std::string getBasicTypeName(void) const override;

	int getTypeSize(void) const override;

	const std::list<std::string>& getParams(void) const;

	operator std::string(void) const override;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;

	//void printGraphViz(std::ofstream& file) const;

private:
	std::list<variantSymNode*> variants;
	expr* 
};

#endif
