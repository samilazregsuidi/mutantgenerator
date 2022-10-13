#ifndef DECL_H
#define DECL_H

#include "stmnt.hpp"
#include "varExpr.hpp"
#include "mtypedefSymNode.hpp"

//E_VAR_DECL,				// symTab = declaration.
class varDecl : public stmnt
{
public:
	varDecl(std::list<varSymNode *> declSymTab, int lineNb);

	std::list<varSymNode*> getDeclSymTab(void) const;

	operator std::string() const;

	std::string getTypeDescr(void) const;

	unsigned int assignMutables(const Mask& mask = Mask(), unsigned int id = 0) override;

	bool mutateMutable(unsigned int id);

	stmnt* deepCopy(void) const;

	void acceptVisitor(ASTConstVisitor* visitor) const override;

	void acceptVisitor(ASTVisitor* visitor) override;

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

	std::list<chanSymNode*> getDeclSymTab(void) const;

	operator std::string() const override;

	std::string getTypeDescr(void) const;

	stmnt* deepCopy(void) const;

	void acceptVisitor(ASTConstVisitor* visitor) const override;

	void acceptVisitor(ASTVisitor* visitor) override;

private:
	std::list<chanSymNode*> declSymTab;
};

/*************************************************************************************************************************/

//E_MTYPE_DECL,				// symTab = declaration.
class mtypeDecl : public stmnt
{
public:
	mtypeDecl(mtypedefSymNode* decl, int lineNb);

	mtypedefSymNode* getDeclSymTab(void) const;

	operator std::string() const override;

	std::string getTypeDescr(void) const;

	stmnt* deepCopy(void) const;

	void acceptVisitor(ASTConstVisitor* visitor) const override;

	void acceptVisitor(ASTVisitor* visitor) override;

private:
	mtypedefSymNode * decl;
};

class tdefDecl : public stmnt {
public:
	tdefDecl(tdefSymNode *declSymTab, int lineNb);

	operator std::string() const;

	std::string getTypeDescr(void) const;

	stmnt* deepCopy(void) const;

	void acceptVisitor(ASTConstVisitor* visitor) const override;

	void acceptVisitor(ASTVisitor* visitor) override;

private:
	tdefSymNode* tdefSym;
};

class stmntFct : public stmntSeq {
public:
	stmntFct(Type type, stmnt* block, int lineNb);

	virtual std::string getFctName(void) const = 0;

	void acceptVisitor(ASTConstVisitor* visitor) const override;
	
	void acceptVisitor(ASTVisitor* visitor) override;
};

//E_INLINE_DECL
class inlineDecl : public stmntFct
{
public:
	inlineDecl(inlineSymNode* sym, int lineNb);

	std::string getFctName(void) const override;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;

private:
	std::string name;
	std::list<std::string> params;
	inlineSymNode* sym;
};

//E_PROC_DECL
class procDecl : public stmntFct
{
public:
	procDecl(procSymNode *procSym, int lineNb);

	std::string getFctName(void) const override;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;

private:
	std::string name;
	std::list<varSymNode*> args;//?
	exprConst* active;
	procSymNode* procSym;
};

//E_INIT_DECL
class initDecl : public stmntFct
{
public:
	initDecl(initSymNode *procSym, int lineNb);

	std::string getFctName(void) const override;

	operator std::string() const;

	std::string getTypeDescr(void) const;

	stmnt* deepCopy(void) const;

private:
	initSymNode* procSym;
};

#endif