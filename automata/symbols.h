#ifndef SYMBOLS_H
#define SYMBOLS_H
/*
 * SYMBOL TABLE
 * * * * * * * * * * * * * * * * * * * * * * * */

#include <cassert>
#include <string>

class astNode;
class expr;
class exprVar;
class exprVarRef;
class exprVarRefName;

class fsm;
class fsmNode;
class fsmTrans;

class symTabVisitor;

class mTypeNode {
public:
	mTypeNode(const std::string& name);
	void printMTypes(void);
	mTypeNode* addMType(const std::string& name);
	int getMTypeValue(const std::string& name) const;
	std::string getMTypeName(int value) const;
	std::string getName(void) const;

private:
	int value;					// Automatically incremented integer value
	std::string name;					// Name given by user
	mTypeNode* next;	// Points to next node; the last node in a list has this pointer set to NULL.
	mTypeNode* prev;	// Points to previous node; the first node in a list has this pointer pointing to the last node!

};

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
		T_PROC,		// ProcType: fsm field used; bound denotes the number of initially active processes
		T_UTYPE,	// Type of variable is a user type (basically, a T_TDEF record is being used as the type): utype points to the type record
		T_NEVER,	// Never claim
	};

protected:
	symTabNode(Type type, const std::string& name, int lineNb, int bound, int capacity, expr* init = nullptr, stmnt* fsmVal = nullptr, symTabNode* child = nullptr);
	symTabNode(Type type, int lineNb, const std::string& sVal = std::string(), expr* init = nullptr);

public:

	virtual ~symTabNode();

	virtual void acceptVisitor(symTabVisitor* visitor) const = 0;

	virtual std::string getTypeName(void) const = 0;
	virtual int getTypeSize(void) const = 0;

	static symTabNode* createSymTabNode(Type itype, const symTabNode& old);
	static symTabNode* createSymTabNode(Type itype, int lineNb, const std::string& sVal = std::string(), expr* init = nullptr);

	static symTabNode* merge(symTabNode* first, symTabNode* second);

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

	void setNext(symTabNode* nextSym);
	const symTabNode* cnextSym(void) const;
	symTabNode* nextSym(void) const;

	void detachPrev(void);
	void detachNext(void);
	void detachChildAndInitSymNodes(void);

	//bool isFeature(void) const;

    virtual unsigned int processVariables(symTabNode* global, const mTypeNode* mTypes, unsigned int offset, bool isGlobal);

	void printSymTab(int level, const std::string& title) const;
	Type getType(void) const;
	int getBound(void) const;
	void setLineNb(int line) ;
	int getLineNb(void) const;
	std::string getName(void) const;
	bool isGlobal(void) const;
	void setGlobal(bool global);
	unsigned int getMemorySize(void) const;
	symTabNode* getUType(void) const;
	symTabNode* getChild(void) const;
	expr* getInitExpr(void) const;
	//int getFeatureId(void) const;
	int getChanCapacity(void) const;
	stmnt* getFsm(void) const;

	void setUType(symTabNode* utype);

	virtual operator std::string(void) const;

protected:

	Type type;					// The type of the symbol, one of the above
	int	lineNb;					// The line at which the symbol is declared
	std::string name;			// The name of the symbol (variable name, type name, proctype name)
	bool global;				// 1 iff global variable, 0 otherwise
	symTabNode* utype;	// For T_UTYPE, this points to the user type symbol.
	int bound;					// Normally == 1; If > 1, the symbol denotes an array.
	int capacity;				// For T_CHAN, this denotes its capacity.  For T_FEAT, this is the feature ID.
	int memSize;				// The size in memory of the symbol table node (in bits).
	unsigned int memOffset;		// The position of the variable in the memory block of a state (in bits).
	expr* init;					// For variables, this denotes the initial value.
	stmnt* childFsm;				// For T_PROC, this denotes the fsm corresponding to the proctype
	symTabNode* child;			// For T_TDEF, this denotes the fields of the user type;							// For T_CHAN, it denotes the fields of the messages;
	symTabNode* next;			// Points to next node; the last node in a list has this pointer set to NULL.
	symTabNode* prev;			// Points to previous node; the first node in a list has this pointer pointing to the last node!
};

class naSymNode : public symTabNode{
public:
	naSymNode(int lineNb, const std::string& sVal, expr* init)
		: symTabNode(symTabNode::T_NA, lineNb, sVal, init)
	{}

	std::string getTypeName(void) const {
		assert(false);
		return "NA";
	}

	int getTypeSize(void) const {
		assert(false);
		return 0;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};

//T_BIT
class bitSymNode : public symTabNode{
public:
	bitSymNode(int lineNb, const std::string& sVal = std::string(), expr* init = nullptr)
		: symTabNode(symTabNode::T_BIT, lineNb, sVal, init)
	{}

	bitSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_BIT, ref.getName(), ref.getLineNb(), ref.getBound(), 0, ref.getInitExpr())
	{}

	std::string getTypeName(void) const {
		return "bit";
	}

	int getTypeSize(void) const {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};

//T_BOOL
class boolSymNode : public symTabNode{
public:
	boolSymNode(int lineNb, const std::string& sVal = std::string(), expr* init = nullptr)
		: symTabNode(symTabNode::T_BOOL, lineNb, sVal, init)
	{}

	boolSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_BOOL, ref.getName(), ref.getLineNb(), ref.getBound(), 0, ref.getInitExpr())
	{}

	std::string getTypeName(void) const {
		return "bool";
	}

	int getTypeSize(void) const {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};

//T_BYTE
class byteSymNode : public symTabNode{
public:
	byteSymNode(int lineNb, const std::string& sVal = std::string(), expr* init = nullptr)
		: symTabNode(symTabNode::T_BYTE, lineNb, sVal, init)
	{}

	byteSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_BYTE, ref.getName(), ref.getLineNb(), ref.getBound(), 0, ref.getInitExpr())
	{}

	std::string getTypeName(void) const {
		return "byte";
	}

	int getTypeSize(void) const {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};

//T_PIDSymNode

//T_SHORT
class shortSymNode : public symTabNode{
public:
	shortSymNode(int lineNb, const std::string& sVal = std::string(), expr* init = nullptr)
		: symTabNode(symTabNode::T_SHORT, lineNb, sVal, init)
	{}
	
	shortSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_SHORT, ref.getName(), ref.getLineNb(), ref.getBound(), 0, ref.getInitExpr())
	{}

	std::string getTypeName(void) const {
		return "short";
	}

	int getTypeSize(void) const {
		return 2;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};

//T_INT
class intSymNode : public symTabNode{
public:
	intSymNode(int lineNb, const std::string& sVal = std::string(), expr* init = nullptr)
		: symTabNode(symTabNode::T_INT, lineNb, sVal, init)
	{}
	
	intSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_INT, ref.getName(), ref.getLineNb(), ref.getBound(), 0, ref.getInitExpr())
	{}

	std::string getTypeName(void) const {
		return "int";
	}

	int getTypeSize(void) const {
		return 4;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};

//T_UTYPE
class utypeSymNode : public symTabNode{
public:
	utypeSymNode(int lineNb, const std::string& sVal = std::string(), expr* init = nullptr)
		: symTabNode(symTabNode::T_UTYPE, lineNb, sVal, init)
	{}

	utypeSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_UTYPE, ref.getName(), ref.getLineNb(), ref.getBound(), ref.getChanCapacity(), ref.getInitExpr(), ref.getFsm(), ref.getChild())
	{}
	
	utypeSymNode(symTabNode* utype, int lineNb)
		: symTabNode(symTabNode::T_UTYPE, std::string(), lineNb, 1, 0)
	{
		assert(utype != nullptr && utype->getType() == symTabNode::T_TDEF);
		this->utype = utype;
	}

	unsigned int processVariables(symTabNode* global, const mTypeNode* mTypes, unsigned int offset, bool isGlobal);

	std::string getTypeName(void) const {
		return "user";
	}

	int getTypeSize(void) const {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};

//T_UNSGN
class unsgnSymNode : public symTabNode{
public:
	unsgnSymNode(int lineNb, const std::string& sVal = std::string(), expr* init = nullptr)
		: symTabNode(symTabNode::T_UNSGN, lineNb, sVal, init)
	{}
	
	unsgnSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_UNSGN, ref.getName(), ref.getLineNb(), ref.getBound(), 0, ref.getInitExpr())
	{}

	std::string getTypeName(void) const {
		return "unsigned";
	}

	int getTypeSize(void) const {
		return 2;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};

//T_MTYPE
class mTypeSymNode : public symTabNode{
public:
	mTypeSymNode(int lineNb, const std::string& sVal = std::string(), expr* init = nullptr)
		: symTabNode(symTabNode::T_MTYPE, lineNb, sVal, init)
	{}
	
	mTypeSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_MTYPE, ref.getName(), ref.getLineNb(), ref.getBound(), 0, ref.getInitExpr())
	{}

	std::string getTypeName(void) const {
		return "mtype";
	}

	int getTypeSize(void) const {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};

//T_CLOCK
/*class clockSymNode : public symTabNode{
public:
	clockSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_CLOCK, ref.getName(), ref.getLineNb(), ref.getBound(), 0, ref.getInitExpr())
	{}
};*/

//T_FEAT
/*class featSymNode : public symTabNode{
public:
	featSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_FEAT, ref.getName(), ref.getLineNb(), ref.getBound(), 0, ref.getInitExpr())
	{}
};*/

//T_UFEAT
/*class ufeatSymNode : public symTabNode{
public:
	ufeatSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_UFEAT, ref.getName(), ref.getLineNb(), ref.getBound(), 0, ref.getInitExpr())
	{}
};*/

//T_CHAN
class chanSymNode : public symTabNode{
public:
	chanSymNode(int lineNb, const std::string& sVal = std::string(), expr* init = nullptr)
		: symTabNode(symTabNode::T_CHAN, lineNb, sVal, init)
	{}
	
	chanSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_CHAN, ref.getName(), ref.getLineNb(), ref.getBound(), ref.getChanCapacity(), ref.getInitExpr(), ref.getFsm(), ref.getChild())
	{}

	chanSymNode(const std::string& name, expr* init, stmnt* fsmVal, int lineNb)
		: symTabNode(symTabNode::T_CHAN, name, lineNb, 0, 0, init, fsmVal)
	{}

	chanSymNode(const std::string& name, stmnt* fsmVal, int lineNb)
		: symTabNode(symTabNode::T_CHAN, name, lineNb, 1, 0, nullptr, fsmVal)
	{}

	chanSymNode(const std::string& name, int bound, int capacity, symTabNode* childSymTab, int lineNb)
		: symTabNode(symTabNode::T_CHAN, name, lineNb, bound, capacity, nullptr, nullptr, childSymTab)
	{}

	std::string getTypeName(void) const {
		return "chan";
	}

	int getTypeSize(void) const {
		return 0;
	}

	unsigned int processVariables(symTabNode* global, const mTypeNode* mTypes, unsigned int offset, bool isGlobal);

	void acceptVisitor(symTabVisitor* visitor) const ;
};

//T_CID
class cidSymNode : public symTabNode{
public:
	cidSymNode(int lineNb, const std::string& sVal = std::string())
		: symTabNode(symTabNode::T_CID, lineNb, sVal)
	{}

	cidSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_CID, ref.getName(), ref.getLineNb(), ref.getBound(), ref.getChanCapacity(), ref.getInitExpr(), ref.getFsm(), ref.getChild())
	{}
	
	std::string getTypeName(void) const {
		return "cid";
	}

	int getTypeSize(void) const {
		return 0;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};

//T_CID
class pidSymNode : public symTabNode{
public:
	pidSymNode(int lineNb, const std::string& sVal = std::string())
		: symTabNode(symTabNode::T_PID, lineNb, sVal)
	{}

	pidSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_PID, ref.getName(), ref.getLineNb(), ref.getBound(), ref.getChanCapacity(), ref.getInitExpr(), ref.getFsm(), ref.getChild())
	{}
	
	std::string getTypeName(void) const {
		return "pid";
	}

	int getTypeSize(void) const {
		return 0;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};

//T_TDEF
class tdefSymNode : public symTabNode{
public:
	tdefSymNode(int lineNb, const std::string& sVal = std::string())
		: symTabNode(symTabNode::T_TDEF, lineNb, sVal)
	{}

	tdefSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_TDEF, ref.getName(), ref.getLineNb(), ref.getBound(), ref.getChanCapacity(), ref.getInitExpr(), ref.getFsm(), ref.getChild())
	{}
	
	tdefSymNode(const std::string& name,  symTabNode* child, int lineNb)
		: symTabNode(symTabNode::T_TDEF, name, lineNb, 1, 0, nullptr, nullptr, child)
	{}

	std::string getTypeName(void) const {
		return "typedef";
	}

	int getTypeSize(void) const {
		return 1;
	}

	unsigned int processVariables(symTabNode* global, const mTypeNode* mTypes, unsigned int offset, bool isGlobal);

	operator std::string(void) const ;

	void acceptVisitor(symTabVisitor* visitor) const ;
};

//T_PROC
class procSymNode : public symTabNode{
public:
	procSymNode(int lineNb, const std::string& sVal = std::string())
		: symTabNode(symTabNode::T_PROC, lineNb, sVal)
	{}

	procSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_PROC, ref.getName(), ref.getLineNb(), ref.getBound(), ref.getChanCapacity(), ref.getInitExpr(), ref.getFsm(), ref.getChild())
	{}
	
	procSymNode(const std::string& name, expr* child0, symTabNode* args, stmnt* childFsm, int lineNb)
		: symTabNode(symTabNode::T_PROC, name, lineNb, 0, 0, child0, childFsm, nullptr)
	{
		this->args = args;
	}

	procSymNode(const std::string& name, stmnt* childFsm, int lineNb)
		: symTabNode(symTabNode::T_PROC, name, lineNb, 0, 0, nullptr, childFsm, nullptr)
	{}

	std::string getTypeName(void) const {
		return "proctype";
	}

	int getTypeSize(void) const {
		return 1;
	}

	unsigned int processVariables(symTabNode* global, const mTypeNode* mTypes, unsigned int offset, bool isGlobal);

	operator std::string(void) const;

	void acceptVisitor(symTabVisitor* visitor) const ;

protected:
	procSymNode(Type type, const std::string& name, int lineNb, int bound, int capacity, expr* init, stmnt* fsmVal, symTabNode* child)
		: symTabNode(type, name, lineNb, bound, capacity, init, fsmVal, child)
	{}

	procSymNode(Type type, int lineNb, const std::string& sVal = std::string())
		: symTabNode(type, lineNb, sVal)
	{}

	procSymNode(Type type, const symTabNode& ref)
		: symTabNode(type, ref.getName(), ref.getLineNb(), ref.getBound(), ref.getChanCapacity(), ref.getInitExpr(), ref.getFsm(), ref.getChild())
	{}
private:
	symTabNode* args;
};

//T_NEVER
class neverSymNode : public procSymNode{
public:
	neverSymNode(int lineNb, const std::string& sVal = std::string())
		: procSymNode(symTabNode::T_NEVER, lineNb, sVal)
	{}

	neverSymNode(const symTabNode& ref)
		: procSymNode(symTabNode::T_NEVER, ref)
	{}
	
	neverSymNode(stmnt* fsmVal, int lineNb)
		: procSymNode(symTabNode::T_NEVER, "__never", lineNb, 1, 0, nullptr, fsmVal, nullptr)
	{}

	unsigned int processVariables(symTabNode* global, const mTypeNode* mTypes, unsigned int offset, bool isGlobal);

	std::string getTypeName(void) const {
		return "never";
	}

	int getTypeSize(void) const {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};

class symTabVisitor {
public:
	virtual void visitNA(const naSymNode* sym) = 0;
	virtual void visitBit(const bitSymNode* sym) = 0 ;
	virtual void visitBool(const boolSymNode* sym) = 0;
	virtual void visitByte(const byteSymNode* sym) = 0;
	virtual void visitPid(const pidSymNode* sym) = 0;
	virtual void visitShort(const shortSymNode* sym) = 0;
	virtual void visitInt(const intSymNode* sym) = 0;
	virtual void visitUnsgn(const unsgnSymNode* sym) = 0;
	virtual void visitMtype(const mTypeSymNode* sym) = 0;
	virtual void visitChan(const chanSymNode* sym) = 0;
	virtual void visitCid(const cidSymNode* sym) = 0;
	virtual void visitTdef(const tdefSymNode* sym) = 0;
	virtual void visitProc(const procSymNode* sym) = 0;
	virtual void visitUtype(const utypeSymNode* sym) = 0;
	virtual void visitNever(const neverSymNode* sym) = 0;
};

class symTabCopyVisitor : public symTabVisitor {
public:
	symTabNode* deepCopy(const symTabNode* toCopy);

	void visitNA(const naSymNode* sym);
	void visitBit(const bitSymNode* sym);
	void visitBool(const boolSymNode* sym);
	void visitByte(const byteSymNode* sym);
	void visitPid(const pidSymNode* sym);
	void visitShort(const shortSymNode* sym);
	void visitInt(const intSymNode* sym);
	void visitUnsgn(const unsgnSymNode* sym);
	void visitMtype(const mTypeSymNode* sym);
	void visitChan(const chanSymNode* sym);
	void visitCid(const cidSymNode* sym);
	void visitTdef(const tdefSymNode* sym);
	void visitProc(const procSymNode* sym);
	void visitUtype(const utypeSymNode* sym);
	void visitNever(const neverSymNode* sym);
private:
	symTabNode* tmp;
};

class dataTuple {
public:
	const char* sVal;
	int iVal;
	symTabNode::Type iType;
	symTabNode* symTabNodeVal;
	fsm* fsmVal;
};

#endif
