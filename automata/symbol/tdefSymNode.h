#include "symTabNode.h"

//T_TDEF
class tdefSymNode : public symTabNode{
public:
	tdefSymNode(int lineNb, const std::string& sVal)
		: symTabNode(symTabNode::T_TDEF, lineNb, sVal)
	{}

	tdefSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_TDEF, ref.getName(), ref.getLineNb(), ref.getBound(), ref.getChanCapacity(), ref.getInitExpr(), ref.getStmnt(), ref.getChild())
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

	unsigned int processVariables(symTabNode* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal);

	operator std::string(void) const ;

	void acceptVisitor(symTabVisitor* visitor) const ;
};
