#include "symTabNode.h"

//T_INIT
class initProcSymNode : public symTabNode{
public:
	initProcSymNode(stmnt* block, int lineNb)
		: symTabNode(symTabNode::T_INIT, "init", lineNb)
	{
		this->block = block;
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
	stmnt* block;
};
