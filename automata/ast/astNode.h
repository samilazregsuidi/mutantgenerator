#ifndef AST_NODE_H
#define AST_NODE_H

#include <list>
#include <set>
#include <string>

#include "symbols.h"

class ASTVisitor;
class ASTConstVisitor;

class fsm;
class fsmNode;
class fsmTrans;

class stmnt;

class Mutation {

public:
	virtual void apply(void) = 0;

	virtual void undo(void) = 0;
};

template <typename T, typename U> class MutationImpl : public Mutation {
public:
	MutationImpl(T* toMutate, U* T::* ptr, U* mutant)
		: toMutate(toMutate)
		, ptr(ptr)
		, initial(toMutate->*ptr)
		, mutant(mutant)
	{}

	void apply(void) override {
		toMutate->*ptr = mutant;
	}

	void undo(void) override {
		toMutate->*ptr = initial;
	}

private:
	T* toMutate;
	U* T::* ptr;
	U* initial;
	U* mutant;
};

class astNode
{

public:
	enum Type
	{
		/*
	* SYNTAX TREE FOR STATEMENTS
	* * * * * * * * * * * * * * * * * * * * * * * */

		E_VAR_DECL,	 // symTab = declaration.
		E_TDEF_DECL,
		E_MTYPE_DECL,
		E_CHAN_DECL,
		E_PROC_DECL,
		E_INIT_DECL,
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

	class Mask {
	public:
		Mask() 
			: mask {
				E_PROC_DECL,
				E_INIT_DECL,

				E_STMNT,

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
				//E_STMNT_PRINT,	// child[0] = E_ARGLIST, sVal = the print string
				//E_STMNT_PRINTM, // child[0] = E_VARREF, or iVal = constant
				//E_STMNT_ASSERT, // child[0] = E_EXPR_*
				E_STMNT_EXPR,	// child[0] = E_EXPR_*
				E_STMNT_ELSE,	// empty

				//E_STMNT_WAIT, //
				//E_STMNT_WHEN, // symTab = clock symbols

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
				//E_EXPR_RUN,		// child[0] = E_ARGLIST, sVal = the procType name, and after processing: symTab = node in symbol table that represents the proctype
				E_EXPR_LEN,		// child[0] = E_VARREF
				E_EXPR_VAR,		// child[0] = E_VARREF
				E_EXPR_CONST,	// iVal = the value
				//E_EXPR_TIMEOUT, // empty
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
				E_RARG_CONST // iVal = the constant
				
				} 
		{}

		void reset(const std::set<Type>& newMask = {}) {
			mask = newMask;
		}

		void remove(Type type) {
			mask.erase(type);
		}

		void remove(const std::set<Type>& types) {
			for(auto& t : types)
				remove(t);
		}

		void add(Type type) {
			mask.insert(type);
		}

		void add(const std::set<Type>& types) {
			for(auto& t : types)
				add(t);
		}

		bool isPresent(Type type) const {
			return mask.find(type) != mask.end();
		}

	private:
		std::set<Type> mask;
	};

	//astNode(Type type, int iVal, astNode *child0, astNode *child1, astNode *child2, int lineNb, stmnt *block = nullptr, symTabNode *symTabChild = nullptr);
	astNode(Type type, int lineNb);
	virtual ~astNode() {}

	/**
	 * Goes through the expression and all its children and looks up all references to
	 * MTypes, variables or proctypes (expressions of type STMNT* BLOCK or E_EXPR_RUN)
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
	
	//virtual void resolveVariables(symTable* global = nullptr) = 0;
	
	Type getType(void) const;

	int getLineNb(void) const;

	void setLineNb(int lineNb) {
		this->lineNb = lineNb;
	}

	virtual std::string getTypeDescr(void) const = 0;

	virtual operator std::string() const = 0;

	//virtual void accept(ASTConstVisitor* visitor) const = 0;

	//virtual void accept(ASTVisitor* visitor) = 0;

	//virtual void accept(ASTMutator* visitor) = 0;

	virtual unsigned int assignMutables(const Mask& mask = Mask(), unsigned int id = 0);

	virtual void mutateMutable(unsigned int id) = 0;

	static int tab_lvl;

	static std::string _tab(int adjust = 0);

	void setParent(astNode* parent);

	astNode* getParent(void) const;

	unsigned int getMId(void) const {
		return mId;
	}

protected:
	Type type;
	int lineNb;
	astNode* parent;
	unsigned int mId;
};

#endif