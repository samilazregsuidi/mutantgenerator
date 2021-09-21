#include "procSymNode.h"

//T_NEVER
class neverSymNode : public procSymNode{
public:
	neverSymNode(int lineNb, const std::string& sVal)
		: procSymNode(symTabNode::T_NEVER, lineNb, sVal)
	{}

	neverSymNode(const symTabNode& ref)
		: procSymNode(symTabNode::T_NEVER, ref)
	{}
	
	neverSymNode(stmnt* fsmVal, int lineNb)
		: procSymNode(symTabNode::T_NEVER, "__never", lineNb, 1, 0, nullptr, fsmVal, nullptr)
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
