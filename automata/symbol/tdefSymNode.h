#ifndef TDEF_SYM_NODE_H
#define TDEF_SYM_NODE_H

#include <list>

#include "symbol.h"

class symTable;

//T_TDEF
class tdefSymNode : public symbol{
public:
	tdefSymNode(const std::string& name,  std::list<varSymNode*> fields, int lineNb);

	~tdefSymNode(void) override ;

	std::string getTypeName(void) const override {
		return "typedef";
	}

	int getTypeSize(void) const override {
		return 1;
	}

	const std::list<varSymNode*>& getFields(void) const {
		return fields;
	}

	symTable* getSymTable(void) const {
		return symTab;
	}

	//unsigned int processVariables(symbol* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal) override ;

	operator std::string(void) const override ;

	void acceptVisitor(symTabVisitor* visitor) const override;

private:
	std::list<varSymNode*> fields;
	symTable* symTab;
};

#endif
