#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <list>

class mTypeNode;
class symTabNode;

class fsm;
class fsmNode;
class fsmTrans;

// These constants are used to identify magic (predefined) variables inside an E_VARREF_NAME (to avoid strcmp).
#define MVAR_SCRATCH -1
#define MVARID_SCRATCH "_" // A write-only variable that can be used to destroy a field read from a channel
#define MVAR_PID -2
#define MVARID_PID "_pid" // The pid of the currently executing proctype
#define MVAR_LAST -3
#define MVARID_LAST "_last" // The pid of the proctype that executed the last step in the current execution
#define MVAR_NRPR -4
#define MVARID_NRPR "_nr_pr" // The number of running proctypes

class astNode
{

public:
	enum Type
	{
		/*
	* SYNTAX TREE FOR STATEMENTS
	* * * * * * * * * * * * * * * * * * * * * * * */

		E_DECL,	 // symTab = declaration.
		E_STMNT, // child[0] = E_STMNT_*

		E_STMNT_CHAN_RCV, // child[0] = E_VARREF, child[1] = E_EXPR_*
		E_STMNT_CHAN_SND, // child[0] = E_VARREF, child[1] = E_EXPR_*
		E_STMNT_IF,		  // child[0] = E_STMNT_OPT (contains an fsm)
		E_STMNT_DO,		  // child[0] = E_STMNT_OPT (contains an fsm)
		E_STMNT_BREAK,	  // empty
		E_STMNT_GOTO,	  // sVal = the label to go to
		E_STMNT_LABEL,	  // child[0] = E_STMNT_*, sVal = the label of child[0]
		E_STMNT_OPT,	  // child[0] = E_STMNT_OPT (next option; or NULL), fsm = fsm of this option
		E_STMNT_SEQ,	  // fsm = fsm of this sequence
		E_STMNT_ATOMIC,	  // fsm = fsm of the atomic sequence

		E_STMNT_ASGN,	// child[0] = E_VARREF, child[1] = E_EXPR_*
		E_STMNT_INCR,	// child[0] = E_VARREF
		E_STMNT_DECR,	// child[0] = E_VARREF
		E_STMNT_PRINT,	// child[0] = E_ARGLIST, sVal = the print string
		E_STMNT_PRINTM, // child[0] = E_VARREF, or iVal = constant
		E_STMNT_ASSERT, // child[0] = E_EXPR_*
		E_STMNT_EXPR,	// child[0] = E_EXPR_*
		E_STMNT_ELSE,	// empty

		E_STMNT_WAIT, //
		E_STMNT_WHEN, // symTab = clock symbols

		E_EXPR_PAR,		// child[0] = E_EXPR_*
		E_EXPR_PLUS,	// child[0] = E_EXPR_*, child[1] = E_EXPR_*
		E_EXPR_MINUS,	// child[0] = E_EXPR_*, child[1] = E_EXPR_*
		E_EXPR_TIMES,	// child[0] = E_EXPR_*, child[1] = E_EXPR_*
		E_EXPR_DIV,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
		E_EXPR_MOD,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
		E_EXPR_GT,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
		E_EXPR_LT,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
		E_EXPR_GE,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
		E_EXPR_LE,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
		E_EXPR_EQ,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
		E_EXPR_NE,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
		E_EXPR_AND,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
		E_EXPR_OR,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
		E_EXPR_COUNT,	// child[0] = E_EXPR_*
		E_EXPR_UMIN,	// child[0] = E_EXPR_*
		E_EXPR_NEG,		// child[0] = E_EXPR_*
		E_EXPR_BITWAND, // child[0] = E_EXPR_*, child[1] = E_EXPR_*
		E_EXPR_BITWOR,	// child[0] = E_EXPR_*, child[1] = E_EXPR_*
		E_EXPR_BITWXOR, // child[0] = E_EXPR_*, child[1] = E_EXPR_*
		E_EXPR_BITWNEG, // child[0] = E_EXPR_*
		E_EXPR_LSHIFT,	// child[0] = E_EXPR_*, child[1] = E_EXPR_*
		E_EXPR_RSHIFT,	// child[0] = E_EXPR_*, child[1] = E_EXPR_*
		E_EXPR_COND,	// child[0] = E_EXPR_* (the condition), child[1] = E_EXPR_* (then), child[2] = E_EXPR_* (else)
		E_EXPR_RUN,		// child[0] = E_ARGLIST, sVal = the procType name, and after processing: symTab = node in symbol table that represents the proctype
		E_EXPR_LEN,		// child[0] = E_VARREF
		E_EXPR_VAR,		// child[0] = E_VARREF
		E_EXPR_CONST,	// iVal = the value
		E_EXPR_TIMEOUT, // empty
		E_EXPR_FULL,	// child[0] = E_VARREF
		E_EXPR_NFULL,	// child[0] = E_VARREF
		E_EXPR_EMPTY,	// child[0] = E_VARREF
		E_EXPR_NEMPTY,	// child[0] = E_VARREF
		E_EXPR_SKIP,	//
		E_EXPR_TRUE,	//
		E_EXPR_FALSE,	//

		E_ARGLIST,	   // child[0] = E_EXPR_* or E_RARG_VAR or E_RARG_EVAL or E_RARG_CONST, E_ARGLIST (next argument, or NULL)
		E_VARREF,	   // child[0] = E_VARREF_NAME, child[1] = E_VARREF (subfield, or NULL)
		E_VARREF_NAME, // child[0] = E_EXPR_* (index into the array, or NULL), sVal = the variable/field name

		//The processing step resolves all symbol names in expressions.  After this was done:
		//- If the symbol denotes a variable, then symTab is the node in the symbol table of that variable;
		//- If the symbol denotes an mtype, then symTab is NULL, and iVal >= 0 is the mtype value.
		//- If the symbol denotes a special variable, then iVal < 0 and is one of MVAR_*

		E_RARG_VAR,	  // child[0] = E_VARREF
		E_RARG_EVAL,  // child[0] = E_EXPR_*
		E_RARG_CONST, // iVal = the constant
	};

	astNode(Type type, const std::string &sVal, int iVal, astNode *child0, astNode *child1, astNode *child2, int lineNb, fsm *fsmChild = nullptr, symTabNode *symTabChild = nullptr);
	virtual ~astNode();

	/**
	 * Goes through the expression and all its children and looks up all references to
	 * MTypes, variables or proctypes (expressions of type E_VARREF_NAME or E_EXPR_RUN)
	 * and stores a pointer to the actual symTab record of the variable in the symTab
	 * field of the expression; or the MType value (>=0) in the iVal field; or the magic
	 * variable identifier (MVAR_* < 0) in the iVal field.
	 *
	 * If a variable is not found, execution aborts.
	 *
	 * The globalSymTab should contain all globally visible symbols, while the localSymTab
	 * contains additional symbols.  Lookups are first made in the localSymTab.
	 * The subFieldSymTab parameter is only set if the expression designates a subfield of
	 * a user type.  If the parameter is not NULL, the lookup will be performed on it only.
	 * Subsequent lookups, such as the array index, will use the other two symTabs just as
	 * before.
	 */
	virtual void resolveVariables(symTabNode *globalSymTab, const mTypeNode *mTypes, symTabNode *localSymTab = nullptr, symTabNode *subFieldSymTab = nullptr);
	symTabNode *getSymbol(void) const;
	void setSymbol(symTabNode *sym);

	virtual symTabNode *symbolLookUpRight(void) const;
	virtual symTabNode *symbolLookUpLeft(void) const;

	Type getType(void) const;
	int getLineNb(void) const;
	std::string getName(void) const;
	void setName(const std::string& sVal);
	bool isGlobal(void) const;
	void setGlobal(bool global);
	int getIVal(void) const;
	//const symTabNode* getUType(void) const;
	//virtual bool isTimeout(void) const;

	astNode* getChild0(void) const;
	astNode* getChild1(void) const;
	astNode* getChild2(void) const;

	astNode* detachChild0(void);
	astNode* detachChild1(void);
	astNode* detachChild2(void);

	fsm* getChildFsm(void) const;

	//virtual ADD expNode2Bool(const symTabNode* symTab) const;
	void setIVal(int ival);

	//std::string var2String(const symTabNode *globalSymTab, const symTabNode *processSymTab, const mTypeNode *mtypes) const;
	//virtual bool varOccurs(const std::string &var, const symTabNode *globalSymTab, const symTabNode *processSymTab, const mTypeNode *mtypes) const;
	//virtual std::list<std::string> getVars(const symTabNode *globalSymTab, const symTabNode *processSymTab, const mTypeNode *mtypes) const;
	//virtual std::list<std::string> getReadVars(const symTabNode* globalSymTab, const symTabNode* processSymTab, const mTypeNode* mtypes, std::list<const astNode*>& expressions, std::list<const symTabNode*>& symbols) const;

	virtual std::string getTypeDescr(void) = 0;

	virtual operator std::string() const = 0;

protected:
	Type type;
	std::string sVal;
	int iVal;
	int lineNb; // The line at which the symbol is declared
	double prob;
	bool global;

	astNode *child[3];
	fsm *childFsm;
	symTabNode *symTab;
};

//E_STMNT, 			// child[0] = E_STMNT_*
class stmnt : public astNode
{

protected:
	stmnt(Type type, const std::string &sVal, int iVal, astNode *child0, astNode *child1, astNode *child2, int lineNb, fsm *fsmChild = nullptr, symTabNode *symTabChild = nullptr)
		: astNode(type, sVal, iVal, child0, child1, child2, lineNb, fsmChild, symTabChild)
	{
	}

public:
	stmnt(stmnt *node, int lineNb)
		: astNode(astNode::E_STMNT, std::string(), 0, node, nullptr, nullptr, lineNb)
	{
	}

	/*std::list<std::string> getVars(const symTabNode *globalSymTab, const symTabNode *processSymTab, const mTypeNode *mtypes) const
	{
		return child[0]->getVars(globalSymTab, processSymTab, mtypes);
		;
	}*/

	operator std::string() const
	{
		return std::string(*child[0]);
	}

	std::string getTypeDescr(void)
	{
		return "Statement wrapper (E_STMNT)";
	}
};

//E_DECL,				// symTab = declaration.
class decl : public stmnt
{
public:
	decl(symTabNode *symTabChild, int lineNb)
		: stmnt(astNode::E_DECL, std::string(), 0, nullptr, nullptr, nullptr, lineNb, nullptr, symTabChild)
	{
	}

	operator std::string() const
	{
		return "TODO";
	}

	std::string getTypeDescr(void)
	{
		return "Declaration wrapper (E_DECL)";
	}
};

class expr : public astNode
{
protected:
	expr(Type type, const std::string &sVal, int iVal, astNode *child0, astNode *child1, astNode *child2, int lineNb, fsm *fsmChild = nullptr, symTabNode *symTabChild = nullptr)
		: astNode(type, sVal, iVal, child0, child1, child2, lineNb, fsmChild, symTabChild)
	{
	}
};

//E_VARREF_NAME,		// child[0] = E_EXPR_* (index into the array, or NULL), sVal = the variable/field name
//The processing step resolves all symbol names in expressions.  After this was done:
//- If the symbol denotes a variable, then symTab is the node in the symbol table of that variable;
//- If the symbol denotes an mtype, then symTab is NULL, and iVal >= 0 is the mtype value.
//- If the symbol denotes a special variable, then iVal < 0 and is one of MVAR_*

class exprVarRefName : public expr
{
public:
	exprVarRefName(const std::string &sVal, int lineNb)
		: expr(astNode::E_VARREF_NAME, sVal, 0, nullptr, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	exprVarRefName(const std::string &sVal, expr *child0, int lineNb)
		: expr(astNode::E_VARREF_NAME, sVal, 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	exprVarRefName(const std::string &sVal, symTabNode *symTabChild, int lineNb)
		: expr(astNode::E_VARREF_NAME, sVal, 0, nullptr, nullptr, nullptr, lineNb, nullptr, symTabChild)
	{
	}

	void resolveVariables(symTabNode *global, const mTypeNode *mTypes, symTabNode *local, symTabNode *subField = nullptr);

	symTabNode *symbolLookUpRight(void) const
	{
		return symTab;
	}

	symTabNode *symbolLookUpLeft(void) const
	{
		return symTab;
	}

	operator std::string() const
	{
		return sVal + (child[0] ? "[" + std::string(*child[0]) + "]" : "");
	}

	std::string getTypeDescr(void)
	{
		return "Variable or field name (E_VARREF_NAME)";
	}
};

//E_VARREF,			// child[0] = E_VARREF_NAME, child[1] = E_VARREF (subfield, or NULL)
class exprVarRef : public expr
{
public:
	exprVarRef(exprVarRefName *child0, exprVarRef *child1, int lineNb)
		: expr(astNode::E_VARREF, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	exprVarRef(exprVarRefName *child0, int lineNb)
		: expr(astNode::E_VARREF, std::string(), 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	void resolveVariables(symTabNode *global, const mTypeNode *mTypes, symTabNode *local, symTabNode *subField = nullptr);

	symTabNode *symbolLookUpRight() const
	{
		return child[1] ? child[1]->symbolLookUpRight() : child[0]->symbolLookUpRight();
	}

	symTabNode *symbolLookUpLeft(void) const
	{
		return child[0]->symbolLookUpLeft();
	}

	const exprVarRefName *getExprVarRefName() const
	{
		return static_cast<exprVarRefName *>(child[0]);
	}

	bool hasSubField(void) const
	{
		return child[1] != nullptr;
	}

	const exprVarRef *getSubField(void) const
	{
		return static_cast<exprVarRef *>(child[1]);
	}

	const exprVarRef *getField() const
	{
		return static_cast<exprVarRef *>(child[1]);
	}

	operator std::string() const
	{
		return std::string(*child[0]) + (child[1] ? "." + std::string(*child[1]) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Variable reference (E_VARREF)";
	}
};

//E_EXPR_VAR,			// child[0] = E_VARREF
class exprVar : public expr
{
public:
	exprVar(exprVarRef *child0, int lineNb)
		: expr(astNode::E_EXPR_VAR, std::string(), 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	const exprVarRef *getExprVarRef(void) const
	{
		return static_cast<exprVarRef *>(child[0]);
	}

	const exprVarRefName *getExprVarRefName(void) const
	{
		return getExprVarRef()->getExprVarRefName();
	}

	/*bool varOccurs(const std::string &var, const symTabNode *globalSymTab, const symTabNode *processSymTab, const mTypeNode *mtypes) const
	{
		return child[0]->var2String(globalSymTab, processSymTab, mtypes) == var;
	}*/

	symTabNode *symbolLookUpRight(void) const
	{
		return child[0]->symbolLookUpRight();
	}

	symTabNode *symbolLookUpLeft(void) const
	{
		return child[0]->symbolLookUpLeft();
	}

	operator std::string() const
	{
		return *child[0];
	}

	std::string getTypeDescr(void)
	{
		return "Variable reference wrapper (E_EXPR_VAR)";
	}
};

class exprBinary : public expr
{
protected:
	exprBinary(Type type, const std::string &sVal, int iVal, astNode *child0, astNode *child1, astNode *child2, int lineNb, fsm *fsmChild = nullptr, symTabNode *symTabChild = nullptr)
		: expr(type, sVal, iVal, child0, child1, child2, lineNb, fsmChild, symTabChild)
	{
	}

	/*std::list<std::string> getVars(const symTabNode *globalSymTab, const symTabNode *processSymTab, const mTypeNode *mtypes) const
	{
		auto left = child[0]->getVars(globalSymTab, processSymTab, mtypes);
		auto right = child[1]->getVars(globalSymTab, processSymTab, mtypes);
		left.splice(left.begin(), right);
		return left;
	}*/
};

class exprUnary : public expr
{
protected:
	exprUnary(Type type, const std::string &sVal, int iVal, astNode *child0, astNode *child1, astNode *child2, int lineNb, fsm *fsmChild = nullptr, symTabNode *symTabChild = nullptr)
		: expr(type, sVal, iVal, child0, child1, child2, lineNb, fsmChild, symTabChild)
	{
	}

	/*std::list<std::string> getVars(const symTabNode *globalSymTab, const symTabNode *processSymTab, const mTypeNode *mtypes) const
	{
		return child[0]->getVars(globalSymTab, processSymTab, mtypes);
		;
	}*/
};

//E_EXPR_PAR,			// child[0] = E_EXPR_*
class exprPar : public exprUnary
{
public:
	exprPar(expr *child0, int lineNb)
		: exprUnary(astNode::E_EXPR_PAR, std::string(), 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "( " + std::string(*child[0]) + " )";
	}

	std::string getTypeDescr(void)
	{
		return "Parentheses (E_EXPR_PAR)";
	}
};

//E_EXPR_PLUS,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprPlus : public exprBinary
{
public:
	exprPlus(expr *child0, expr *child1, int lineNb)
		: exprBinary(astNode::E_EXPR_PLUS, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " + " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Plus (E_EXPR_PLUS)";
	}
};

//E_EXPR_MINUS,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprMinus : public exprBinary
{
public:
	exprMinus(expr *child0, expr *child1, int lineNb)
		: exprBinary(astNode::E_EXPR_MINUS, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " - " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Minus (E_EXPR_MINUS)";
	}
};

//E_EXPR_TIMES,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprTimes : public exprBinary
{
public:
	exprTimes(expr *child0, expr *child1, int lineNb)
		: exprBinary(astNode::E_EXPR_TIMES, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " * " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Times (E_EXPR_TIMES)";
	}
};

//E_EXPR_DIV,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprDiv : public exprBinary
{
public:
	exprDiv(expr *child0, expr *child1, int lineNb)
		: exprBinary(astNode::E_EXPR_DIV, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " / " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Divide (E_EXPR_DIV)";
	}
};

//E_EXPR_MOD,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprMod : public exprBinary
{
public:
	exprMod(expr *child0, expr *child1, int lineNb)
		: exprBinary(astNode::E_EXPR_MOD, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " % " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Modulo (E_EXPR_MOD)";
	}
};

//E_EXPR_GT,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprGT : public exprBinary
{
public:
	exprGT(expr *child0, expr *child1, int lineNb)
		: exprBinary(astNode::E_EXPR_GT, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " > " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Greater than (E_EXPR_GT)";
	}
};

//E_EXPR_LT,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprLT : public exprBinary
{
public:
	exprLT(expr *child0, expr *child1, int lineNb)
		: exprBinary(astNode::E_EXPR_LT, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " < " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Less than (E_EXPR_LT)";
	}
};

//E_EXPR_GE,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprGE : public exprBinary
{
public:
	exprGE(expr *child0, expr *child1, int lineNb)
		: exprBinary(astNode::E_EXPR_GE, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " >= " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Greater or equal than (E_EXPR_GE)";
	}
};

//E_EXPR_LE,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprLE : public exprBinary
{
public:
	exprLE(expr *child0, expr *child1, int lineNb)
		: exprBinary(astNode::E_EXPR_LE, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " <= " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Less or equal than (E_EXPR_LE)";
	}
};

//E_EXPR_EQ,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprEQ : public exprBinary
{
public:
	exprEQ(expr *child0, expr *child1, int lineNb)
		: exprBinary(astNode::E_EXPR_EQ, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " == " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Equal (E_EXPR_EQ)";
	}
};

//E_EXPR_NE,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprNE : public exprBinary
{
public:
	exprNE(expr *child0, expr *child1, int lineNb)
		: exprBinary(astNode::E_EXPR_NE, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " != " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Not equal (E_EXPR_NE)";
	}
};

//E_EXPR_AND,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprAnd : public exprBinary
{
public:
	exprAnd(expr *child0, expr *child1, int lineNb)
		: exprBinary(astNode::E_EXPR_AND, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " && " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Logical and (E_EXPR_AND)";
	}
};

//E_EXPR_OR,			// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprOr : public exprBinary
{
public:
	exprOr(expr *child0, expr *child1, int lineNb)
		: exprBinary(astNode::E_EXPR_OR, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " || " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Logical or (E_EXPR_OR)";
	}
};

//E_EXPR_COUNT,		// child[0] = E_EXPR_*
class exprCount : public exprUnary
{
public:
	exprCount(expr *child0, int lineNb)
		: exprUnary(astNode::E_EXPR_COUNT, std::string(), 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "count( " + std::string(*child[0]) + " ) ";
	}

	std::string getTypeDescr(void)
	{
		return "Clones count (E_EXPR_COUNT)";
	}
};

//E_EXPR_UMIN,		// child[0] = E_EXPR_*
class exprUMin : public exprUnary
{
public:
	exprUMin(expr *child0, int lineNb)
		: exprUnary(astNode::E_EXPR_UMIN, std::string(), 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "-" + std::string(*child[0]);
	}

	std::string getTypeDescr(void)
	{
		return "Unary minus (E_EXPR_UMIN)";
	}
};

//E_EXPR_NEG,			// child[0] = E_EXPR_*
class exprNeg : public exprUnary
{
public:
	exprNeg(expr *child0, int lineNb)
		: exprUnary(astNode::E_EXPR_NEG, std::string(), 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "!" + std::string(*child[0]);
	}

	std::string getTypeDescr(void)
	{
		return "Negation (E_EXPR_NEG)";
	}
};

//E_EXPR_BITWAND,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprBitwAnd : public exprBinary
{
public:
	exprBitwAnd(expr *child0, expr *child1, int lineNb)
		: exprBinary(astNode::E_EXPR_BITWAND, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " & " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Bitwise and (E_EXPR_BITWAND)";
	}
};

//E_EXPR_BITWOR,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprBitwOr : public exprBinary
{
public:
	exprBitwOr(expr *child0, expr *child1, int lineNb)
		: exprBinary(astNode::E_EXPR_BITWOR, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " | " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Bitwise or (E_EXPR_BITWOR)";
	}
};

//E_EXPR_BITWXOR,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprBitwXor : public exprBinary
{
public:
	exprBitwXor(expr *child0, expr *child1, int lineNb)
		: exprBinary(astNode::E_EXPR_BITWXOR, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " ^ " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Bitwise xor (E_EXPR_BITWXOR)";
	}
};

//E_EXPR_BITWNEG,		// child[0] = E_EXPR_*
class exprBitwNeg : public exprUnary
{
public:
	exprBitwNeg(expr *child0, int lineNb)
		: exprUnary(astNode::E_EXPR_BITWNEG, std::string(), 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " ~ " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Bitwise neg (E_EXPR_BITWNEG)";
	}
};

//E_EXPR_LSHIFT,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprLShift : public exprBinary
{
public:
	exprLShift(expr *child0, expr *child1, int lineNb)
		: exprBinary(astNode::E_EXPR_LSHIFT, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " << " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Left shift (E_EXPR_LSHIFT)";
	}
};

//E_EXPR_RSHIFT,		// child[0] = E_EXPR_*, child[1] = E_EXPR_*
class exprRShift : public exprBinary
{
public:
	exprRShift(expr *child0, expr *child1, int lineNb)
		: exprBinary(astNode::E_EXPR_RSHIFT, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " >> " + std::string(*child[1]);
	}

	std::string getTypeDescr(void)
	{
		return "Right shift (E_EXPR_RSHIFT)";
	}
};

//E_EXPR_COND,		// child[0] = E_EXPR_* (the condition), child[1] = E_EXPR_* (then), child[2] = E_EXPR_* (else)
class exprCond : public expr
{
public:
	exprCond(expr *child0, expr *child1, expr *child2, int lineNb)
		: expr(astNode::E_EXPR_COND, std::string(), 0, child0, child1, child2, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "( " + std::string(*child[0]) + " ? " + std::string(*child[1]) + " : " + std::string(*child[3]) + " )";
	}

	std::string getTypeDescr(void)
	{
		return "Conditional expression (E_EXPR_COND)";
	}
};

class exprRArg : public expr
{
protected:
	exprRArg(Type type, const std::string &sVal, int iVal, astNode *child0, astNode *child1, astNode *child2, int lineNb, fsm *fsmChild = nullptr, symTabNode *symTabChild = nullptr)
		: expr(type, sVal, iVal, child0, child1, child2, lineNb, fsmChild, symTabChild)
	{
	}
};

//E_RARG_VAR,		// child[0] = E_VARREF
class exprRArgVar : public exprRArg
{
public:
	exprRArgVar(exprVarRef *child0, int lineNb)
		: exprRArg(astNode::E_RARG_VAR, std::string(), 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	symTabNode *symbolLookUpRight(void) const
	{
		return child[0]->symbolLookUpRight();
	}

	symTabNode *symbolLookUpLeft(void) const
	{
		return child[0]->symbolLookUpLeft();
	}

	operator std::string() const
	{
		return *child[0];
	}

	std::string getTypeDescr(void)
	{
		return "Receive argument variable (E_RARG_VAR)";
	}
};

//E_RARG_EVAL,	// child[0] = E_EXPR_*
class exprRArgEval : public exprRArg
{
public:
	exprRArgEval(expr *child0, int lineNb)
		: exprRArg(astNode::E_RARG_EVAL, std::string(), 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "eval( " + std::string(*child[0]) + ")";
	}

	std::string getTypeDescr(void)
	{
		return "Receive argument eval (E_RARG_EVAL)";
	}
};

//E_RARG_CONST,	// iVal = the constant
class exprRArgConst : public exprRArg
{
public:
	exprRArgConst(int iVal, int lineNb)
		: exprRArg(astNode::E_RARG_EVAL, std::string(), iVal, nullptr, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::to_string(iVal);
	}

	std::string getTypeDescr(void)
	{
		return "Receive argument constant (E_RARG_CONST)";
	}
};

//E_ARGLIST,			// child[0] = E_EXPR_* or E_RARG_VAR or E_RARG_EVAL or E_RARG_CONST,
// child[1] = E_ARGLIST (next argument, or NULL)
class exprArgList : public expr
{
public:
	exprArgList(exprRArg *child0, exprArgList *child1, int lineNb)
		: expr(astNode::E_ARGLIST, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	exprArgList(exprRArg *child0, int lineNb)
		: expr(astNode::E_ARGLIST, std::string(), 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + (child[1] ? "," + std::string(*child[1]) : "");
	}

	std::string getTypeDescr(void)
	{
		return "Argument list (E_ARGLIST)";
	}
};

//E_EXPR_RUN,			// child[0] = E_ARGLIST, sVal = the procType name, and after processing: symTab = node in symbol table that represents the proctype
class exprRun : public expr
{
public:
	exprRun(exprArgList *child0, exprVarRef *child1, const std::string &sVal, int lineNb)
		: expr(astNode::E_EXPR_RUN, sVal, 0, child0, child1, nullptr, lineNb)
	{
	}

	exprRun(exprArgList *child0, const std::string &sVal, int lineNb)
		: expr(astNode::E_EXPR_RUN, sVal, 0, child0, nullptr, nullptr, lineNb)
	{
	}

	void resolveVariables(symTabNode *global, const mTypeNode *mTypes, symTabNode *local, symTabNode *subField = nullptr);

	operator std::string() const
	{
		return "run " + (child[1] ? "[" + std::string(*child[1]) + "]" : "") + "( " + std::string(*child[0]) + " ) ";
	}

	std::string getTypeDescr(void)
	{
		return "Run (E_EXPR_RUN)";
	}
};

//E_EXPR_LEN,			// child[0] = E_VARREF
class exprLen : public exprUnary
{
public:
	exprLen(exprVarRef *child0, int lineNb)
		: exprUnary(astNode::E_EXPR_LEN, std::string(), 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "len( " + std::string(*child[0]) + " )";
	}

	std::string getTypeDescr(void)
	{
		return "Length (E_EXPR_LEN)";
	}
};

//E_EXPR_CONST,		// iVal = the value
class exprConst : public expr
{
public:
	exprConst(int iVal, int lineNb)
		: expr(astNode::E_EXPR_CONST, std::string(), iVal, nullptr, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return std::to_string(iVal);
	}

	std::string getTypeDescr(void)
	{
		return "Constant (E_EXPR_CONST)";
	}
};

//E_EXPR_TIMEOUT,	// iVal = 0
class exprTimeout : public expr
{
public:
	exprTimeout(int lineNb)
		: expr(astNode::E_EXPR_TIMEOUT, std::string(), 0, nullptr, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "timeout";
	}

	std::string getTypeDescr(void)
	{
		return "Timeout (E_EXPR_TIMEOUT)";
	}
};

//E_EXPR_FULL,		// child[0] = E_VARREF
class exprFull : public exprUnary
{
public:
	exprFull(exprVarRef *child0, int lineNb)
		: exprUnary(astNode::E_EXPR_FULL, std::string(), 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "full( " + std::string(*child[0]) + ")";
	}

	std::string getTypeDescr(void)
	{
		return "Full probe (E_EXPR_FULL)";
	}
};

//E_EXPR_NFULL,		// child[0] = E_VARREF
class exprNFull : public exprUnary
{
public:
	exprNFull(exprVarRef *child0, int lineNb)
		: exprUnary(astNode::E_EXPR_NFULL, std::string(), 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "nfull( " + std::string(*child[0]) + ")";
	}

	std::string getTypeDescr(void)
	{
		return "Not full probe (E_EXPR_NFULL)";
	}
};

//E_EXPR_EMPTY,		// child[0] = E_VARREF
class exprEmpty : public exprUnary
{
public:
	exprEmpty(exprVarRef *child0, int lineNb)
		: exprUnary(astNode::E_EXPR_EMPTY, std::string(), 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "empty( " + std::string(*child[0]) + ")";
	}

	std::string getTypeDescr(void)
	{
		return "Empty probe (E_EXPR_EMPTY)";
	}
};

//E_EXPR_NEMPTY,		// child[0] = E_VARREF
class exprNEmpty : public exprUnary
{
public:
	exprNEmpty(exprVarRef *child0, int lineNb)
		: exprUnary(astNode::E_EXPR_NEMPTY, std::string(), 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "nempty( " + std::string(*child[0]) + ")";
	}

	std::string getTypeDescr(void)
	{
		return "Not empty probe (E_EXPR_NEMPTY)";
	}
};

//E_EXPR_SKIP,		// iVal = 1
class exprSkip : public expr
{
public:
	exprSkip(int lineNb)
		: expr(astNode::E_EXPR_SKIP, std::string(), 1, nullptr, nullptr, nullptr, lineNb)
	{
	}

	operator std::string() const
	{
		return "skip";
	}

	std::string getTypeDescr(void)
	{
		return "Skip (E_EXPR_SKIP)";
	}
};

//E_EXPR_TRUE,		// iVal = 1
class exprTrue : public expr
{
public:
	exprTrue(int lineNb)
		: expr(astNode::E_EXPR_TRUE, std::string(), 1, nullptr, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "true";
	}

	std::string getTypeDescr(void)
	{
		return "True (E_EXPR_TRUE)";
	}
};

//E_EXPR_FALSE,		// iVal = 0
class exprFalse : public expr
{
public:
	exprFalse(int lineNb)
		: expr(astNode::E_EXPR_FALSE, std::string(), 0, nullptr, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "false";
	}

	std::string getTypeDescr(void)
	{
		return "False (E_EXPR_FALSE)";
	}
};

//E_STMNT_CHAN_RCV,	// child[0] = E_VARREF, child[1] = E_EXPR_*
class stmntChanRecv : public stmnt
{
public:
	stmntChanRecv(exprVarRef *child0, expr *child1, int lineNb)
		: stmnt(astNode::E_STMNT_CHAN_RCV, std::string(), 0, child0, child1, nullptr, lineNb)
	{
	}

	/*std::list<std::string> getVars(const symTabNode *globalSymTab, const symTabNode *processSymTab, const mTypeNode *mtypes) const
	{
		return child[1]->getVars(globalSymTab, processSymTab, mtypes);
	}*/

	operator std::string() const
	{
		return std::string(*child[0]) + " ? " + std::string(*child[1]);
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
		: stmnt(astNode::E_STMNT_CHAN_SND, std::string(), 0, child0, child1, nullptr, lineNb)
	{
	}

	/*bool varOccurs(const std::string &var, const symTabNode *globalSymTab, const symTabNode *processSymTab, const mTypeNode *mtypes) const
	{
		return child[0]->varOccurs(var, globalSymTab, processSymTab, mtypes) || child[1]->varOccurs(var, globalSymTab, processSymTab, mtypes);
	}

	std::list<std::string> getVars(const symTabNode *globalSymTab, const symTabNode *processSymTab, const mTypeNode *mtypes) const
	{
		return child[1]->getVars(globalSymTab, processSymTab, mtypes);
		;
	}*/

	operator std::string() const
	{
		return std::string(*child[0]) + " ! " + std::string(*child[1]);
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
	stmntOpt(fsm *fsmChild, stmntOpt *child0, int lineNb)
		: stmnt(astNode::E_STMNT_OPT, std::string(), 0, child0, nullptr, nullptr, lineNb, fsmChild, nullptr)
	{
	}

	stmntOpt(fsm *fsmChild, int lineNb)
		: stmnt(astNode::E_STMNT_OPT, std::string(), 0, nullptr, nullptr, nullptr, lineNb, fsmChild, nullptr)
	{
	}

	operator std::string() const
	{
		return *child[0];
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
		: stmnt(astNode::E_STMNT_IF, std::string(), 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "if\n" + std::string(*child[0]) + "\nfi;\n";
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
		: stmnt(astNode::E_STMNT_DO, std::string(), 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "do\n" + std::string(*child[0]) + "\nod;\n";
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
		: stmnt(astNode::E_STMNT_BREAK, std::string(), 0, nullptr, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "break;\n";
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
	stmntGoto(const std::string &sVal, int lineNb)
		: stmnt(astNode::E_STMNT_GOTO, sVal, 0, nullptr, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "goto " + sVal + ";\n";
	}

	std::string getTypeDescr(void)
	{
		return "Goto (E_STMNT_GOTO)";
	}
};

//E_STMNT_LABEL,		// child[0] = E_STMNT_*, sVal = the label of child[0]
class stmntLabel : public stmnt
{
public:
	stmntLabel(const std::string &sVal, stmnt *child0, int lineNb)
		: stmnt(astNode::E_STMNT_LABEL, sVal, 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return sVal + ": \n" + std::string(*child[0]);
	}

	std::string getTypeDescr(void)
	{
		return "Label (E_STMNT_LABEL)";
	}
};

//E_STMNT_SEQ,		// fsm = fsm of this sequence
class stmntSeq : public stmnt
{
public:
	stmntSeq(fsm *fsmChild, int lineNb)
		: stmnt(astNode::E_STMNT_SEQ, std::string(), 0, nullptr, nullptr, nullptr, lineNb, fsmChild, nullptr)
	{
	}

	operator std::string() const
	{
		return "null";
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
	stmntAtomic(fsm *fsmChild, int lineNb)
		: stmnt(astNode::E_STMNT_ATOMIC, std::string(), 0, nullptr, nullptr, nullptr, lineNb, fsmChild, nullptr)
	{
	}

	operator std::string() const
	{
		return "null";
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
		: stmnt(astNode::E_STMNT_ASGN, std::string(), 0, child0, child1, nullptr, lineNb)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + " = " + std::string(*child[1]) + ";\n";
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
		: stmnt(astNode::E_STMNT_INCR, std::string(), 0, child0, nullptr, nullptr, lineNb)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + "++;\n";
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
		: stmnt(astNode::E_STMNT_DECR, std::string(), 0, child0, nullptr, nullptr, lineNb)
	{
	}

	operator std::string() const
	{
		return std::string(*child[0]) + "--;\n";
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
		: stmnt(astNode::E_STMNT_PRINT, toPrint, 0, child0, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "printf(" + sVal + std::string(*child[0]) + ");\n";
	}

	std::string getTypeDescr(void)
	{
		return "Print (E_STMNT_PRINT)";
	}
};

//E_STMNT_PRINTM,		// child[0] = E_VARREF, or iVal = constant
class stmntPrintm : public stmnt
{
public:
	stmntPrintm(exprVarRef *child0, int lineNb)
		: stmnt(astNode::E_STMNT_PRINTM, std::string(), 0, child0, nullptr, nullptr, lineNb)
	{
	}

	stmntPrintm(int iVal, int lineNb)
		: stmnt(astNode::E_STMNT_PRINTM, std::string(), iVal, nullptr, nullptr, nullptr, lineNb, nullptr, nullptr)
	{
	}

	operator std::string() const
	{
		return "printm(" + sVal + (child[0] ? std::string(*child[0]) : std::to_string(iVal)) + ");\n";
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
		: stmnt(astNode::E_STMNT_ASSERT, std::string(), 0, child0, nullptr, nullptr, lineNb)
	{
	}

	operator std::string() const
	{
		return "assert(" + std::string(*child[0]) + ");\n";
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
		: stmnt(astNode::E_STMNT_CHAN_RCV, std::string(), 0, child0, nullptr, nullptr, lineNb)
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
		: stmnt(astNode::E_STMNT_ELSE, std::string(), 0, nullptr, nullptr, nullptr, lineNb)
	{
	}

	operator std::string() const
	{
		return "else -> ";
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
		: stmnt(astNode::E_STMNT_WAIT, std::string(), 0, child0, nullptr, nullptr, lineNb)
	{
	}

	operator std::string() const
	{
		return "while ( " + std::string(*child[0]) + " ) wait;\n";
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
		: stmnt(astNode::E_STMNT_WHEN, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, nullptr)
	{
	}

	stmntWhen(expr *child0, stmnt *child1, symTabNode *childSymNode, int lineNb)
		: stmnt(astNode::E_STMNT_WHEN, std::string(), 0, child0, child1, nullptr, lineNb, nullptr, childSymNode)
	{
	}

	operator std::string() const
	{
		return "when ( " + std::string(*child[0]) + " ) do " + std::string(*child[1]) + "\n";
	}

	std::string getTypeDescr(void)
	{
		return "Time guard (E_STMNT_WHEN)";
	}
};

#endif