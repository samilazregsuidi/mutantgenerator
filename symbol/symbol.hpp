#ifndef SYMBOLS_H
#define SYMBOLS_H
/*
 * SYMBOL TABLE
 * * * * * * * * * * * * * * * * * * * * * * * */

#include <cassert>
#include <string>
#include <unordered_map>

typedef char byte;
typedef unsigned char ubyte;

class astNode;
class stmnt;
class expr;
class exprVar;
class exprVarRef;
class exprVarRefName;

class fsm;
class fsmNode;
class fsmTrans;

class symTable;
class varSymNode;
class symTabVisitor;
class symTabConstVisitor;


class symbol {
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
		T_MTYPE_DEF,
		T_CMTYPE,

		//T_FEAT,
		//T_UFEAT,

		// "Special" types:
		T_CHAN,		// Channel: capacity used; children denote message fields
		T_CID,		// Channel reference; capacity and children are not used.
		T_TDEF,		// Type definition: children denote fields of type
		T_INIT,
		T_PROC,		// ProcType: fsm field used; bound denotes the number of initially active processes
		T_INLINE,
		T_UTYPE,	// Type of variable is a user type (basically, a T_TDEF record is being used as the type): utype points to the type record
		T_NEVER,	// Never claim

		T_VARIANT,
		T_FMULTI_LTL
	};

	static const unsigned int READ_ACCESS = 0x1;
	static const unsigned int WRITE_ACCESS = 0x2;
	static const unsigned int PREDEFINED = 0x4;

protected:
	symbol(Type type, const std::string& name, int lineNb);

	symbol(Type type, int lineNb, const std::string& sVal = std::string());

public:
	virtual ~symbol();
	
	virtual void acceptVisitor(symTabVisitor* visitor) = 0;

	virtual void acceptVisitor(symTabConstVisitor* visitor) const = 0;

	virtual std::string getTypeName(void) const = 0;

	virtual std::string getBasicTypeName(void) const = 0;
	
	//getBasicTypeSize
	virtual int getTypeSize(void) const = 0;

	static symbol* merge(symbol* first, symbol* second);
	
	static void print(symbol* table);

	void printSymTab(int level, const std::string& title) const;
	
	Type getType(void) const;
	
	void setLineNb(int line) ;
	
	int getLineNb(void) const;
	
	std::string getName(void) const;
	
	bool isGlobal(void) const;
	
	void setGlobal(bool global);

	bool isPredefined(void) const;

	bool isHidden(void) const;

	virtual unsigned int getSizeOf(void) const;

	virtual void printGraphViz(std::ofstream& file) const;

	virtual operator std::string(void) const;
	
	bool operator < (const symbol* other);

	unsigned long getID(void) const;

	symTable* getSymTable(void) const;

	virtual void setSymTable(symTable* parent);

	void addToMask(unsigned int mask);

	void setMask(unsigned int mask);

	void removeToMask(unsigned int mask);

	unsigned int getMask(void) const;

	virtual bool castTo(const symbol* sym) const;

protected:

	symTable* parent;
	Type type;					// The type of the symbol, one of the above
	int	lineNb;					// The line at which the symbol is declared
	std::string name;			// The name of the symbol (variable name, type name, proctype name)
	unsigned int mask;
};

class dataTuple {
public:
	char* sVal;
	int iVal;
	symbol::Type iType;
	fsm* fsmVal;
};

#endif
