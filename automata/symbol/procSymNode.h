#include "symTabNode.h"

//T_PROC
class procSymNode : public symTabNode{
public:
	procSymNode(int lineNb, const std::string& sVal)
		: symTabNode(symTabNode::T_PROC, lineNb, sVal)
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

	unsigned int processVariables(symTabNode* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal);

	operator std::string(void) const;

	void acceptVisitor(symTabVisitor* visitor) const ;

protected:
	procSymNode(Type type, const std::string& name, int lineNb, int bound, int capacity, expr* init, stmnt* fsmVal, symTabNode* child)
		: symTabNode(type, name, lineNb, bound, capacity, init, fsmVal, child)
	{}

	procSymNode(Type type, int lineNb, const std::string& sVal)
		: symTabNode(type, lineNb, sVal)
	{}

	procSymNode(Type type, const symTabNode& ref)
		: symTabNode(type, ref.getName(), ref.getLineNb(), ref.getBound(), ref.getChanCapacity(), ref.getInitExpr(), ref.getStmnt(), ref.getChild())
	{}
private:
	symTabNode* args;
	stmnt* block;
	expr* active;
};
