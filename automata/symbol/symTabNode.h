#ifndef SYMBOLS_H
#define SYMBOLS_H
/*
 * SYMBOL TABLE
 * * * * * * * * * * * * * * * * * * * * * * * */

#include <cassert>
#include <string>

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

class mTypeList;

class symTabNode {
public:

	// Primitive types:
	enum Type {
		T_NA,
		T_BIT,
		T_BOOL,
		T_BYTE,
		T_PID,
		T_SHORT,
		T_INT,
		T_UNSGN, 	// not supported yet
		T_MTYPE,
		T_CLOCK ,	// dense time clock

		//T_FEAT,
		//T_UFEAT,

		// "Special" types:
		T_CHAN,		// Channel: capacity used; children denote message fields
		T_CID,		// Channel reference; capacity and children are not used.
		T_TDEF,		// Type definition: children denote fields of type
		T_INIT,
		T_PROC,		// ProcType: fsm field used; bound denotes the number of initially active processes
		T_UTYPE,	// Type of variable is a user type (basically, a T_TDEF record is being used as the type): utype points to the type record
		T_NEVER,	// Never claim
	};

protected:
	symTabNode(Type type, const std::string& name, int lineNb);
	symTabNode(Type type, int lineNb, const std::string& sVal = std::string());

public:

	virtual ~symTabNode();

	virtual void acceptVisitor(symTabVisitor* visitor) const = 0;

	virtual std::string getTypeName(void) const = 0;
	virtual int getTypeSize(void) const = 0;

	//static symTabNode* createSymTabNode(Type itype, const symTabNode& old);
	//static symTabNode* createSymTabNode(Type itype, int lineNb, const std::string& sVal = std::string());

	static symTabNode* merge(symTabNode* first, symTabNode* second);
	static void print(symTabNode* table);

	static symTabNode* deepcopy(symTabNode* symTab);

	//symTabNode* addToSymTab(symTabNode* newNode);
	//void remove(void);

	symTabNode* lookupInSymTab(const exprVarRefName* expr);
	symTabNode* lookupInSymTab(const exprVarRef* expr);
	symTabNode* lookupInSymTab(const exprVar* expr);
	symTabNode* lookupInSymTab(const std::string& name);

	const symTabNode* lookupInSymTab(const exprVarRefName* expr) const;
	const symTabNode* lookupInSymTab(const exprVarRef* expr) const;
	const symTabNode* lookupInSymTab(const exprVar* expr) const;
	const symTabNode* lookupInSymTab(const std::string& name) const;

	void makeNext(symTabNode* nextSym);
	void setNext(symTabNode* nextSym);
	void setPrev(symTabNode* prevSym);
	const symTabNode* cnextSym(void) const;
	symTabNode* nextSym(void) const;

	void detachPrev(void);
	void detachNext(void);
	//void detachAll(void);

	//bool isFeature(void) const;

    virtual unsigned int processVariables(symTabNode* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal) = 0;

	void printSymTab(int level, const std::string& title) const;
	Type getType(void) const;
	//int getBound(void) const;
	void setLineNb(int line) ;
	int getLineNb(void) const;
	std::string getName(void) const;
	bool isGlobal(void) const;
	void setGlobal(bool global);
	unsigned int getMemorySize(void) const;
	//symTabNode* getUType(void) const;
	//symTabNode* getChild(void) const;
	//expr* getInitExpr(void) const;
	//int getFeatureId(void) const;
	//int getChanCapacity(void) const;
	//stmnt* getStmnt(void) const;

	//void setUType(symTabNode* utype);

	virtual operator std::string(void) const;

protected:

	Type type;					// The type of the symbol, one of the above
	int	lineNb;					// The line at which the symbol is declared
	std::string name;			// The name of the symbol (variable name, type name, proctype name)
	bool global;				// 1 iff global variable, 0 otherwise
	//symTabNode* utype;	// For T_UTYPE, this points to the user type symbol.
	//int bound;					// Normally == 1; If > 1, the symbol denotes an array.
	//int capacity;				// For T_CHAN, this denotes its capacity.  For T_FEAT, this is the feature ID.
	int memSize;				// The size in memory of the symbol table node (in bits).
	unsigned int memOffset;		// The position of the variable in the memory block of a state (in bits).
	//expr* init;					// For variables, this denotes the initial value.
	//stmnt* childFsm;				// For T_PROC, this denotes the fsm corresponding to the proctype
	//symTabNode* child;			// For T_TDEF, this denotes the fields of the user type;							// For T_CHAN, it denotes the fields of the messages;
	symTabNode* next;			// Points to next node; the last node in a list has this pointer set to NULL.
	symTabNode* prev;			// Points to previous node; the first node in a list has this pointer pointing to the last node!
};

class varSymNode;

class dataTuple {
public:
	const char* sVal;
	int iVal;
	symTabNode::Type iType;
	varSymNode* symTabNodeVal;
	fsm* fsmVal;
};

#endif
