#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
/*
 * SYMBOL TABLE
 * * * * * * * * * * * * * * * * * * * * * * * */

#include <cassert>
#include <string>
#include <unordered_map>
#include <list>

#include "symbol.h"

class astNode;
class stmnt;
class expr;
class exprVar;
class exprVarRef;
class exprVarRefName;

class fsm;
class fsmNode;
class fsmTrans;

class varSymNode;
class symTabVisitor;
class symTabConstVisitor;


class symTable {
public:

	symTable(const std::string& name, symTable* prev = nullptr);

	symTable* createSubTable(const std::string& name = "");

	virtual ~symTable();

	std::string getNameSpace(void) const;

	void print(int tab = 0) const;
	symbol* lookup(const std::string& name) const;
	std::list<symbol*> getSymbols(symbol::Type type, unsigned int mask) const;
	void insert(symbol* sym);

	void setBlock(stmnt* block);
	stmnt* getBlock(void) const;

	symTable* prevSymTab(void) const;
	
	void printSymTab(int level, const std::string& title) const;
	bool isGlobal(void) const;
	unsigned int getMemorySize(void) const;
	operator std::string(void) const;

	static void addPredefinedSym(symTable* tab);

	void acceptVisitor(symTabVisitor* visitor);

	void acceptVisitor(symTabConstVisitor* visitor) const;

protected:

	std::string name;
	std::string parentNameSpace;
	stmnt* block;
	symTable* prev;			// Points to previous node; the first node in a list has this pointer pointing to the last node!
	std::list<symTable*> next;
	std::unordered_map<std::string, symbol*> syms;
};

#endif
