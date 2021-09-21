#include "symTabNode.h"

//T_CID
class cidSymNode : public symTabNode{
public:
	cidSymNode(int lineNb, const std::string& sVal)
		: symTabNode(symTabNode::T_CID, lineNb, sVal)
	{}

	cidSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_CID, ref.getName(), ref.getLineNb())
	{}
	
	std::string getTypeName(void) const {
		return "cid";
	}

	int getTypeSize(void) const {
		return 0;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};
