#ifndef STMNT_H
#define STMNT_H

#include "astNode.h"
#include "varExpr.h"

//E_STMNT, 			// child[0] = E_STMNT_*
class stmnt : public astNode
{

protected:
	stmnt(Type type, int iVal, astNode *child0, astNode *child1, astNode *child2, int lineNb, stmnt *block = nullptr, symTabNode *symTabChild = nullptr)
		: astNode(type, iVal, child0, child1, child2, lineNb, block, symTabChild)
	{
		this->next = nullptr;
		this->prev = this;
	}

public:
	stmnt(stmnt *node, int lineNb)
		: astNode(astNode::E_STMNT, 0, node, nullptr, nullptr, lineNb)
	{
		this->next = nullptr;
		this->prev = this;
	}

	static stmnt* merge(stmnt* list, stmnt* node);

	unsigned int processVariables(symTabNode* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal) const;

	void resolveVariables(symTabNode* globalSymTab, const mTypeList* mTypes, symTabNode* localSymTab = nullptr, symTabNode* subFieldSymTab = nullptr);

	/*std::list<std::string> getVars(const symTabNode *globalSymTab, const symTabNode *processSymTab, const mTypeList *mtypes) const
	{
		return child[0]->getVars(globalSymTab, processSymTab, mtypes);
		;
	}*/

	operator std::string() const
	{
		return std::string(*child[0]) + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Statement wrapper (E_STMNT)";
	}
protected:
	stmnt* next;
	stmnt* prev;
};


//E_DECL,				// symTab = declaration.
class decl : public stmnt
{
public:
	decl(varSymNode *symTabChild, int lineNb);

	void resolveVariables(symTabNode* globalSymTab, const mTypeList* mTypes, symTabNode* localSymTab = nullptr, symTabNode* subFieldSymTab = nullptr);

	operator std::string() const;

	std::string getTypeDescr(void)
	{
		return "Declaration wrapper (E_DECL)";
	}

private:
	varSymNode* declSym;
};

//E_STMNT_CHAN_RCV,	// child[0] = E_VARREF, child[1] = E_EXPR_*
class stmntChanRecv : public stmnt
{
public:
	stmntChanRecv(exprVarRef *child0, expr *child1, int lineNb)
		: stmnt(astNode::E_STMNT_CHAN_RCV, 0, child0, child1, nullptr, lineNb)
	{
	}

	/*std::list<std::string> getVars(const symTabNode *globalSymTab, const symTabNode *processSymTab, const mTypeList *mtypes) const
	{
		return child[1]->getVars(globalSymTab, processSymTab, mtypes);
	}*/

	operator std::string() const
	{
		return std::string(*child[0]) + " ? " + std::string(*child[1]) + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Channel receive (E_STMNT_CHAN_RCV)";
	}
};

//E_STMNT_CHAN_SND,	// child[0] = E_VARREF, child[1] = E_EXPR_*
class stmntChanSnd : public stmnt
{
public:
	stmntChanSnd(exprVarRef *child0, expr *child1, int lineNb)
		: stmnt(astNode::E_STMNT_CHAN_SND, 0, child0, child1, nullptr, lineNb)
	{
	}

	/*bool varOccurs(const std::string &var, const symTabNode *globalSymTab, const symTabNode *processSymTab, const mTypeList *mtypes) const
	{
		return child[0]->varOccurs(var, globalSymTab, processSymTab, mtypes) || child[1]->varOccurs(var, globalSymTab, processSymTab, mtypes);
	}

	std::list<std::string> getVars(const symTabNode *globalSymTab, const symTabNode *processSymTab, const mTypeList *mtypes) const
	{
		return child[1]->getVars(globalSymTab, processSymTab, mtypes);
		;
	}*/

	operator std::string() const
	{
		return std::string(*child[0]) + " ! " + std::string(*child[1]) + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Channel send (E_STMNT_CHAN_SND)";
	}
};

//E_STMNT_OPT,		// child[0] = E_STMNT_OPT (next option; or NULL), fsm = fsm of this option
class stmntOpt : public stmnt
{
public:
	stmntOpt(stmnt* block, stmntOpt *child0, int lineNb)
		: stmnt(astNode::E_STMNT_OPT, 0, child0, nullptr, nullptr, lineNb, block)
	{
	}

	stmntOpt(stmnt* block, int lineNb)
		: stmnt(astNode::E_STMNT_OPT, 0, nullptr, nullptr, nullptr, lineNb, block)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Opt (E_STMNT_OPT)";
	}
};

//E_STMNT_IF,			// child[0] = E_STMNT_OPT (contains an fsm)
class stmntIf : public stmnt
{
public:
	stmntIf(stmntOpt *child0, int lineNb)
		: stmnt(astNode::E_STMNT_IF, 0, child0, nullptr, nullptr, lineNb)
	{
	}

	operator std::string() const
	{
		return "if\n" + std::string(*child[0]) + "\nfi;\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void)
	{
		return "If (E_STMNT_IF)";
	}
};

//E_STMNT_DO,			// child[0] = E_STMNT_OPT (contains an fsm)
class stmntDo : public stmnt
{
public:
	stmntDo(stmntOpt *child0, int lineNb)
		: stmnt(astNode::E_STMNT_DO, 0, child0, nullptr, nullptr, lineNb)
	{
	}

	operator std::string() const
	{
		return "do\n" + std::string(*child[0]) + "\nod;\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Do (E_STMNT_DO)";
	}
};

//E_STMNT_BREAK,		// empty
class stmntBreak : public stmnt
{
public:
	stmntBreak(int lineNb)
		: stmnt(astNode::E_STMNT_BREAK, 0, nullptr, nullptr, nullptr, lineNb)
	{
	}

	operator std::string() const
	{
		return "break;\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Break (E_STMNT_BREAK)";
	}
};

//E_STMNT_GOTO,		// sVal = the label to go to
class stmntGoto : public stmnt
{
public:
	stmntGoto(const std::string& label, int lineNb)
		: stmnt(astNode::E_STMNT_GOTO, 0, nullptr, nullptr, nullptr, lineNb)
	{
		this->label = label;
	}

	operator std::string() const
	{
		return "goto " + label + ";\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Goto (E_STMNT_GOTO)";
	}
	
	std::string getLabel(void) const {
		return label;
	}

private:
	std::string label;
};

//E_STMNT_LABEL,		// child[0] = E_STMNT_*, sVal = the label of child[0]
class stmntLabel : public stmnt
{
public:
	stmntLabel(const std::string& label, stmnt *child0, int lineNb)
		: stmnt(astNode::E_STMNT_LABEL, 0, child0, nullptr, nullptr, lineNb)
	{
		this->label = label;
	}

	operator std::string() const
	{
		return label + ": \n" + std::string(*child[0]) + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Label (E_STMNT_LABEL)";
	}

	std::string getLabel(void) const {
		return label;
	}

private:
	std::string label;
};

//E_STMNT_SEQ,		// fsm = fsm of this sequence
class stmntSeq : public stmnt
{
public:
	stmntSeq(stmnt* block, int lineNb)
		: stmnt(astNode::E_STMNT_SEQ, 0, nullptr, nullptr, nullptr, lineNb, block)
	{
	}

	operator std::string() const
	{
		return "null" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Seq (E_STMNT_SEQ)";
	}
};

//E_STMNT_ATOMIC,		// fsm = fsm of the atomic sequence
class stmntAtomic : public stmnt
{
public:
	stmntAtomic(stmnt *block, int lineNb)
		: stmnt(astNode::E_STMNT_ATOMIC, 0, nullptr, nullptr, nullptr, lineNb, block)
	{
	}

	operator std::string() const
	{
		std::string res = "atomic {\n";
		res += std::string(*childFsm);
		res += "\n};";
		return next? res + std::string(*next) : res; 
	}

	std::string getTypeDescr(void)
	{
		return "Atomic (E_STMNT_ATOMIC)";
	}
};

//E_STMNT_ASGN,		// child[0] = E_VARREF, child[1] = E_EXPR_*
class stmntAsgn : public stmnt
{
public:
	stmntAsgn(exprVarRef *child0, expr *child1, int lineNb)
		: stmnt(astNode::E_STMNT_ASGN, 0, child0, child1, nullptr, lineNb)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " = " + std::string(*child[1]) + ";\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Assignment (E_STMNT_ASGN)";
	}
};

//E_STMNT_INCR,		// child[0] = E_VARREF
class stmntIncr : public stmnt
{
public:
	stmntIncr(exprVarRef *child0, int lineNb)
		: stmnt(astNode::E_STMNT_INCR, 0, child0, nullptr, nullptr, lineNb)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + "++;\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Increment (E_STMNT_INCR)";
	}
};

//E_STMNT_DECR,		// child[0] = E_VARREF
class stmntDecr : public stmnt
{
public:
	stmntDecr(exprVarRef *child0, int lineNb)
		: stmnt(astNode::E_STMNT_DECR, 0, child0, nullptr, nullptr, lineNb)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + "--;\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Decrement (E_STMNT_DECR)";
	}
};

//E_STMNT_PRINT,		// child[0] = E_ARGLIST, sVal = the print string
class stmntPrint : public stmnt
{
public:
	stmntPrint(const std::string &toPrint, exprArgList *child0, int lineNb)
		: stmnt(astNode::E_STMNT_PRINT, 0, child0, nullptr, nullptr, lineNb)
	{
		this->toPrint = toPrint;
	}

	operator std::string() const
	{
		return "printf(" + toPrint + (child[0]? std::string(*child[0]) : "") + ");\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Print (E_STMNT_PRINT)";
	}
private:
	std::string toPrint;
};

//E_STMNT_PRINTM,		// child[0] = E_VARREF, or iVal = constant
class stmntPrintm : public stmnt
{
public:
	stmntPrintm(exprVarRef *child0, int lineNb)
		: stmnt(astNode::E_STMNT_PRINTM, 0, child0, nullptr, nullptr, lineNb)
	{
	}

	stmntPrintm(int iVal, int lineNb)
		: stmnt(astNode::E_STMNT_PRINTM, iVal, nullptr, nullptr, nullptr, lineNb)
	{
	}

	operator std::string() const
	{
		return "printm("+(child[0] ? std::string(*child[0]) : std::to_string(iVal)) + ");\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void)
	{
		return "PrintM (E_STMNT_PRINTM)";
	}
};

//E_STMNT_ASSERT,		// child[0] = E_EXPR_*
class stmntAssert : public stmnt
{
public:
	stmntAssert(expr *child0, int lineNb)
		: stmnt(astNode::E_STMNT_ASSERT, 0, child0, nullptr, nullptr, lineNb)
	{
	}

	operator std::string() const
	{
		return "assert(" + std::string(*child[0]) + ");\n" + (next? std::string(*next) : "") ;
	}

	std::string getTypeDescr(void)
	{
		return "Assertion (E_STMNT_ASSERT)";
	}
};

//E_STMNT_EXPR,		// child[0] = E_EXPR_*
class stmntExpr : public stmnt
{
public:
	stmntExpr(expr *child0, int lineNb)
		: stmnt(astNode::E_STMNT_CHAN_RCV, 0, child0, nullptr, nullptr, lineNb)
	{
	}

	operator std::string() const
	{
		return *child[0];
	}

	std::string getTypeDescr(void)
	{
		return "Expression wrapper (E_STMNT_EXPR)";
	}
};

//E_STMNT_ELSE,		// empty
class stmntElse : public stmnt
{
public:
	stmntElse(int lineNb)
		: stmnt(astNode::E_STMNT_ELSE, 0, nullptr, nullptr, nullptr, lineNb)
	{
	}

	operator std::string() const
	{
		return "else -> " + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Else (E_STMNT_ELSE)";
	}
};

//E_STMNT_WAIT,		// child[0] = E_EXPR_*
class stmntWait : public stmnt
{
public:
	stmntWait(expr *child0, int lineNb)
		: stmnt(astNode::E_STMNT_WAIT, 0, child0, nullptr, nullptr, lineNb)
	{
	}

	operator std::string() const
	{
		return "while ( " + std::string(*child[0]) + " ) wait;\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Time invariant (E_STMNT_WAIT)";
	}
};

//E_STMNT_WHEN,		// child[0] = E_EXPR_*, child[1] = E_STMNT_* symTab = clock symbols
class stmntWhen : public stmnt
{
public:
	stmntWhen(expr *child0, stmnt *child1, int lineNb)
		: stmnt(astNode::E_STMNT_WHEN, 0, child0, child1, nullptr, lineNb)
	{
	}

	stmntWhen(expr *child0, stmnt *child1, symTabNode *childSymNode, int lineNb)
		: stmnt(astNode::E_STMNT_WHEN, 0, child0, child1, nullptr, lineNb, nullptr, childSymNode)
	{
	}

	operator std::string() const
	{
		return "when ( " + std::string(*child[0]) + " ) do " + std::string(*child[1]) + "\n" + (next? std::string(*next) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Time guard (E_STMNT_WHEN)";
	}
};

#endif