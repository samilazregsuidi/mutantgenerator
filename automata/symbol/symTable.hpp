#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
/*
 * SYMBOL TABLE
 * * * * * * * * * * * * * * * * * * * * * * * */

#include <cassert>
#include <string>
#include <unordered_map>
#include <list>
#include <set>
#include <fstream>

#include "symbol.hpp"

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

	//std::list<symbol*> getSymbols(symbol::Type type, unsigned int mask) const;

	std::set<symbol*> getSymbols(const symbol* left) const;

	std::set<symbol*> getSymbols(void) const;

	template <typename T> std::set<T> getSymbols() const {
		std::set<T> res;
		for(auto sym : syms) {
			if(dynamic_cast<T>(sym.second) != nullptr)
				res.insert(dynamic_cast<T>(sym.second));
		}
		return res;
	}

	void insert(symbol* sym);
	
	void remove(const std::string& name);

	void setBlock(stmnt* block);

	stmnt* getBlock(void) const;

	symTable* prevSymTab(void) const;

	symTable* getSubSymTab(const std::string& name) const;
	
	void printSymTab(int level, const std::string& title) const;

	bool isGlobal(void) const;

	unsigned int getMemorySize(void) const;

	operator std::string(void) const;

	static void addPredefinedSym(symTable* tab);

	void acceptVisitor(symTabVisitor* visitor);

	void acceptVisitor(symTabConstVisitor* visitor) const;

	void printGraphViz(std::ofstream& file) const;

protected:

	std::string name;
	std::string parentNameSpace;
	stmnt* block;
	symTable* prev;			// Points to previous node; the first node in a list has this pointer pointing to the last node!
	std::list<symTable*> nexts;
	std::unordered_map<std::string, symbol*> syms;
};

#endif
