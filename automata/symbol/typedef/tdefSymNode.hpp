#ifndef TDEF_SYM_NODE_H
#define TDEF_SYM_NODE_H

#include <list>
#include <set>

#include "symbol.hpp"
#include "symTable.hpp"

//T_TDEF
class tdefSymNode : public symbol, public symTable {
public:
	tdefSymNode(const std::string& name, symTable* st, const std::list<varSymNode*>& fields, int lineNb);

	std::string getTypeName(void) const override;

	std::string getBasicTypeName(void) const override;

	int getTypeSize(void) const override;

	std::set<varSymNode*> getFields(void) const;

	void setSymTable(symTable* symTab) override;

	operator std::string(void) const override;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;
};

#endif
