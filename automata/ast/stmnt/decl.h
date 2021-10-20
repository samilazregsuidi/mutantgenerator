#ifndef DECL_H
#define DECL_H

#include "stmnt.h"
#include "varExpr.h"
#include "mtypedefSymNode.h"

//E_VAR_DECL,				// symTab = declaration.
class varDecl : public stmnt
{
public:
	varDecl(std::list<varSymNode *> declSymTab, int lineNb);

	~varDecl() override ;

	std::list<varSymNode*> getDeclSymTab(void) const {
		return declSymTab;
	}

	operator std::string() const;

	std::string getTypeDescr(void) const
	{
		return "Variable declaration wrapper (E_VAR_DECL)";
	}

	stmnt* deepCopy(void) const {
		varDecl* copy = new varDecl(*this);
		copy->prev = copy;
		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	std::list<varSymNode*> declSymTab;
};

/**************************************************************************************************************************/

//E_CHAN_DECL,				// symTab = declaration.
class chanDecl : public stmnt
{
public:
	chanDecl(std::list<chanSymNode *> declSymTab, int lineNb);

	chanDecl(std::list<varSymNode*> declSymTab, int lineNb);

	//void resolveVariables(symTable* parent) override ;

	std::list<chanSymNode*> getDeclSymTab(void) const {
		return declSymTab;
	}

	operator std::string() const override;

	std::string getTypeDescr(void) const
	{
		return "Variable declaration wrapper (E_CHAN_DECL)";
	}

	stmnt* deepCopy(void) const {
		chanDecl* copy = new chanDecl(*this);
		copy->prev = copy;

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	std::list<chanSymNode*> declSymTab;
};

/*************************************************************************************************************************/

//E_MTYPE_DECL,				// symTab = declaration.
class mtypeDecl : public stmnt
{
public:
	mtypeDecl(mtypedefSymNode* decl, int lineNb);

	~mtypeDecl() override ;

	mtypedefSymNode* getDeclSymTab(void) const {
		return decl;
	}

	operator std::string() const override;

	std::string getTypeDescr(void) const
	{
		return "MType declaration wrapper (E_MTYPE_DECL)";
	}

	stmnt* deepCopy(void) const {
		mtypeDecl* copy = new mtypeDecl(*this);
		copy->prev = copy;

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	mtypedefSymNode * decl;
};

class tdefDecl : public stmnt {
public:
	tdefDecl(tdefSymNode *declSymTab, int lineNb);

	~tdefDecl() override ;

	operator std::string() const;

	std::string getTypeDescr(void) const
	{
		return "Type declaration wrapper (E_TYPE_DECL)";
	}

	stmnt* deepCopy(void) const {
		tdefDecl* copy = new tdefDecl(*this);

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	tdefSymNode* tdefSym;
};

//E_PROC_DECL
class procDecl : public stmnt
{
public:
	procDecl(procSymNode *procSym, int lineNb);

	~procDecl() override ;

	operator std::string() const override;

	std::string getTypeDescr(void) const override
	{
		return "Proctype declaration wrapper (E_PROC_DECL)";
	}

	unsigned int assignMutables(const Mask& mask = Mask(), unsigned int id = 0) override;

	virtual void printSymTab(void) const {
		std::cout <<" line " << getLineNb() << "\t|\t" << getTypeDescr() << "\n"; 
		if(local)
			 local->print();
		else 
			std::cout << "NULL\n";
		
		block->printSymTab();

		if(next)
			next->printSymTab();
	}

	void mutateMutable(unsigned int id) override {
		block->mutateMutable(id);
		if (next) next->mutateMutable(id);
	}

	stmnt* deepCopy(void) const {
		procDecl* copy = new procDecl(*this);
		copy->prev = copy;
		copy->block = block->deepCopy();
		
		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	procSymNode* procSym;
	stmnt* block;
};

//E_INIT_DECL
class initDecl : public stmnt
{
public:
	initDecl(initSymNode *procSym, int lineNb);

	~initDecl() override ;

	//void resolveVariables(symTable* parent) override ;

	operator std::string() const;

	std::string getTypeDescr(void) const {
		return "Proctype declaration wrapper (E_PROC_DECL)";
	}

	stmnt* deepCopy(void) const {
		initDecl* copy = new initDecl(*this);
		copy->prev = copy;

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	initSymNode* procSym;
};

#endif