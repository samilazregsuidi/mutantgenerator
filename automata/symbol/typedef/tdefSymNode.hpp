#ifndef TDEF_SYM_NODE_H
#define TDEF_SYM_NODE_H

#include <list>
#include <set>

#include "symbol.hpp"

class symTable;

//T_TDEF
class tdefSymNode : public symbol{
public:
	tdefSymNode(const std::string& name,  const std::list<varSymNode*>& fields, int lineNb);

	~tdefSymNode(void) override ;

	std::string getTypeName(void) const override;

	int getTypeSize(void) const override;

	const std::set<varSymNode*>& getFields(void) const;

	symTable* getSymTable(void) const;

	operator std::string(void) const override ;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;
	
private:
	std::set<varSymNode*> fields;
	symTable* symTab;
};

#endif
