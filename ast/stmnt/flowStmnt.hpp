#ifndef FLOW_STMNT_H
#define FLOW_STMNT_H

#include <iostream>

#include "stmnt.hpp"

//E_STMNT_OPT,		// child[0] = E_STMNT_OPT (next option; or NULL), fsm = fsm of this option
class stmntOpt : public stmnt
{
public:
	stmntOpt(stmnt* block, stmntOpt *nextOpt, int lineNb);

	stmntOpt(stmnt* block, int lineNb);

	void setBlock(stmnt* block);

	stmnt* getBlock() const;

	void setNextOpt(stmntOpt* nextOpt);

	stmntOpt* getNextOpt() const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;

	void acceptVisitor(ASTConstVisitor* visitor) const override;

	void acceptVisitor(ASTVisitor* visitor) override;

	
};

class stmntFlow : public stmnt
{
public:
	stmntFlow(Type type, stmntOpt* opts, int lineNb);

	void setOpts(stmntOpt* opts);

	stmntOpt* getOpts() const;
};

//E_STMNT_IF,			// child[0] = E_STMNT_OPT (contains an fsm)
class stmntIf : public stmntFlow
{
public:
	stmntIf(stmntOpt *opts, int lineNb);

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;

	void acceptVisitor(ASTConstVisitor* visitor) const override;

	void acceptVisitor(ASTVisitor* visitor) override;
};

//E_STMNT_DO,			// child[0] = E_STMNT_OPT (contains an fsm)
class stmntDo : public stmntFlow
{
public:
	stmntDo(stmntOpt *opts, int lineNb);

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;

	void acceptVisitor(ASTConstVisitor* visitor) const override;

	void acceptVisitor(ASTVisitor* visitor) override;
};

//E_STMNT_BREAK,		// empty
class stmntBreak : public stmnt
{
public:
	stmntBreak(int lineNb);

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const override;

	void acceptVisitor(ASTConstVisitor* visitor) const override;

	void acceptVisitor(ASTVisitor* visitor) override;
};

//E_STMNT_GOTO,		// sVal = the label to go to
class stmntGoto : public stmnt
{
public:
	stmntGoto(const std::string& label, int lineNb);

	operator std::string() const override;

	std::string getTypeDescr(void) const override;
	
	std::string getLabel(void) const;

	stmnt* deepCopy(void) const;

	void acceptVisitor(ASTConstVisitor* visitor) const override;

	void acceptVisitor(ASTVisitor* visitor) override;

private:
	std::string label;
};

//E_STMNT_LABEL,		// child[0] = E_STMNT_*, sVal = the label of child[0]
class stmntLabel : public stmnt
{
public:
	stmntLabel(const std::string& label, stmnt *labelled, int lineNb);

	void setLabelled(stmnt* labelled);

	stmnt* getLabelled() const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	std::string getLabel(void) const;

	stmnt* deepCopy(void) const;

	void acceptVisitor(ASTConstVisitor* visitor) const override;

	void acceptVisitor(ASTVisitor* visitor) override;

private:
	std::string label;
};

//E_STMNT_ELSE,		// empty
class stmntElse : public stmnt
{
public:
	stmntElse(int lineNb);

	operator std::string() const override;

	std::string getTypeDescr(void) const override;

	stmnt* deepCopy(void) const;
};

#endif