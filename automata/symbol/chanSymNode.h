#include "symTabNode.h"

//T_CHAN
class chanSymNode : public symTabNode{
public:
	chanSymNode(int lineNb, const std::string& sVal, expr* init = nullptr)
		: symTabNode(symTabNode::T_CHAN, lineNb, sVal, 0, init)
	{}
	
	chanSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_CHAN, ref.getName(), ref.getLineNb())
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

	unsigned int processVariables(symTabNode* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal);

	void acceptVisitor(symTabVisitor* visitor) const ;

private:
	int capacity;
};
