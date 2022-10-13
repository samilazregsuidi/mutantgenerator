#ifndef STMNT_H
#define STMNT_H

#include <iostream>

#include "astNode.hpp"
#include "varExpr.hpp"
#include "argExpr.hpp"

//E_STMNT, 			// child[0] = E_STMNT_*
class stmnt : public astNode
{
protected:
	stmnt(Type type, int lineNb);

public:
	static stmnt* merge(stmnt* list, stmnt* node);

	static std::string string(stmnt* list);

	//called for non mutable stmnts (e.g., vardecl)
	unsigned int assignMutables(const Mask& mask = Mask(), unsigned int id = 0) override;

	void setLocalSymTab(symTable* local);

	symTable* getLocalSymTab(void) const;

	void setNext(stmnt* next);

	stmnt* getNext(void) const;

	virtual void printSymTab(void) const;

	//virtual void printGraphViz(std::ofstream& graphVis) = 0;

	virtual stmnt* deepCopy(void) const = 0;

	void acceptVisitor(ASTConstVisitor* visitor) const override;

	void acceptVisitor(ASTVisitor* visitor) override;

	void setProb(double newProb);

	double getProb(void) const;

protected:
	symTable* local;
	stmnt* prev;
	double prob;
};

//E_STMNT_SEQ,		// fsm = fsm of this sequence
class stmntSeq : public stmnt
{
protected:
	stmntSeq(Type type, stmnt* block, int lineNb);

public:
	stmntSeq(stmnt* block, int lineNb);

public:
	void setBlock(stmnt* block);

	stmnt* getBlock() const;

	virtual void printSymTab(void) const;

	operator std::string() const;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;

	void acceptVisitor(ASTConstVisitor* visitor) const override;

	void acceptVisitor(ASTVisitor* visitor) override;
};

//E_STMNT_ATOMIC,		// fsm = fsm of the atomic sequence
class stmntAtomic : public stmntSeq
{
public:
	stmntAtomic(stmnt *block, int lineNb);

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;

	void acceptVisitor(ASTConstVisitor* visitor) const override;

	void acceptVisitor(ASTVisitor* visitor) override;
};

//E_STMNT_DSTEP,		// fsm = fsm of the deterministic sequence
class stmntDStep : public stmntSeq
{
public:
	stmntDStep(stmnt *block, int lineNb);

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;

	void acceptVisitor(ASTConstVisitor* visitor) const override;

	void acceptVisitor(ASTVisitor* visitor) override;
};

//E_STMNT_ASGN,		// child[0] = E_VARREF, child[1] = E_EXPR_*
class stmntAsgn : public stmnt
{
public:
	stmntAsgn(exprVarRef *varRef, expr *assign, int lineNb);

	void setVarRef(exprVarRef* varRef);

	//getRValue?
	exprVarRef* getVarRef() const;

	void setAssign(expr* assign);

	//getLeftValue?
	expr* getAssign() const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;
};

//E_STMNT_INCR,		// child[0] = E_VARREF
class stmntIncr : public stmnt
{
public:
	stmntIncr(exprVarRef *varRef, int lineNb);

	void setVarRef(exprVarRef* varRef);

	exprVarRef* getVarRef() const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;
	
	stmnt* deepCopy(void) const;
};

//E_STMNT_DECR,		// child[0] = E_VARREF
class stmntDecr : public stmnt
{
public:
	stmntDecr(exprVarRef *varRef, int lineNb);

	void setVarRef(exprVarRef* varRef);

	exprVarRef* getVarRef() const;

	operator std::string() const override; 

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;
};

//E_STMNT_EXPR,		// child[0] = E_EXPR_*
class stmntExpr : public stmnt
{
public:
	stmntExpr(expr *child, int lineNb);

	void setChild(expr* child);

	expr* getChild() const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;
};

//E_STMNT_CALL
class stmntCall : public stmnt 
{
public:
	stmntCall(const std::string& name, exprArgList* argList, int lineNb);
	
	void setArgList(exprArgList* argList);

	exprArgList* getArgList() const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;

private:
	std::string name;
};

#endif
