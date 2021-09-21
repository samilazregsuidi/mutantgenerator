#include "symTabNode.h"

class seqSymNode : public symTabNode{
protected:
	seqSymNode(Type type, const std::string& sVal, int lineNb, stmnt* block)
		: symTabNode(type, sVal, lineNb)
	{
		this->block = block;
	}

	unsigned int processVariables(symTabNode *global, const mTypeList *mTypes, unsigned int iOffset, bool isGlobal);

	operator std::string(void) const;

protected:
	stmnt* block;
};

class initSymNode : public seqSymNode {
public:
	initSymNode(int lineNb, stmnt* block)
		: seqSymNode(symTabNode::T_INIT, "init", lineNb, block)
	{}

	unsigned int processVariables(symTabNode* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal);

	std::string getTypeName(void) const {
		return "never";
	}

	int getTypeSize(void) const {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};

class neverSymNode : public seqSymNode {
public:
	neverSymNode(int lineNb, stmnt* block)
		: seqSymNode(symTabNode::T_INIT, "__never", lineNb, block)
	{}

	unsigned int processVariables(symTabNode* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal);

	std::string getTypeName(void) const {
		return "init";
	}

	int getTypeSize(void) const {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};

//T_PROC
class procSymNode : public seqSymNode {
public:
	procSymNode(const std::string& name, expr* child0, symTabNode* args, stmnt* block, int lineNb)
		: seqSymNode(symTabNode::T_PROC, name, lineNb, block)
	{
		this->args = args;
		this->active = child0;
	}

	std::string getTypeName(void) const {
		return "proctype";
	}

	int getTypeSize(void) const {
		return 1;
	}

	unsigned int processVariables(symTabNode* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal);

	operator std::string(void) const;

	void acceptVisitor(symTabVisitor* visitor) const ;

private:
	symTabNode* args;
	expr* active;
};
