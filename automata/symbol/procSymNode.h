#ifndef PROC_SYM_NODE_H
#define PROC_SYM_NODE_H

#include <list>

#include "symbol.h"

class seqSymNode : public symbol{
protected:
	seqSymNode(Type type, const std::string& name, int lineNb, stmnt* block)
		: symbol(type, name, lineNb)
	{
		this->block = block;
	}

public:
	~seqSymNode(void) override ;

	//void resolveVariables(symbol* globalSymTab, const mTypeList* mTypes, varSymNode* localSymTab = nullptr, symbol* subFieldSymTab = nullptr) override ;

	stmnt* getBlock(void) const {
		return block;
	}

	//unsigned int processVariables(symbol *global, const mTypeList *mTypes, unsigned int iOffset, bool isGlobal) override ;

	operator std::string(void) const override ;

protected:
	stmnt* block;
};

class initSymNode : public seqSymNode {
public:
	initSymNode(int lineNb, stmnt* block)
		: seqSymNode(symbol::T_INIT, "init", lineNb, block)
	{}

	std::string getTypeName(void) const override {
		return "never";
	}

	int getTypeSize(void) const override {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};

class neverSymNode : public seqSymNode {
public:
	neverSymNode(int lineNb, stmnt* block)
		: seqSymNode(symbol::T_INIT, "__never", lineNb, block)
	{}

	std::string getTypeName(void) const override {
		return "init";
	}

	int getTypeSize(void) const override {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};

class exprConst;

//T_PROC
class procSymNode : public seqSymNode {
public:
	procSymNode(const std::string& name, exprConst* active, std::list<varSymNode*> args, stmnt* block, int lineNb)
		: seqSymNode(symbol::T_PROC, name, lineNb, block)
	{
		this->args = args;
		this->active = active;
	}

	~procSymNode() override ;

	std::string getTypeName(void) const override {
		return "proctype";
	}

	int getTypeSize(void) const override {
		return 1;
	}

	//void resolveVariables(symbol* globalSymTab, const mTypeList* mTypes, varSymNode* localSymTab = nullptr, symbol* subFieldSymTab = nullptr) override ;
	exprConst* getActiveExpr(void) const {
		return active;
	}

	const std::list<varSymNode*>& getArgs(void) const {
		return args;
	}

	//unsigned int processVariables(symbol* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal) override ;

	operator std::string(void) const override;

	void acceptVisitor(symTabVisitor* visitor) const override;

private:
	std::list<varSymNode*> args;
	exprConst* active;
};

#endif
