#include "symTabNode.h"

//T_PID
class pidSymNode : public symTabNode{
public:
	pidSymNode(int lineNb, const std::string& sVal)
		: symTabNode(symTabNode::T_PID, lineNb, sVal)
	{}

	pidSymNode(const symTabNode& ref)
		: symTabNode(symTabNode::T_PID, ref.getName(), ref.getLineNb(), ref.getBound(), ref.getChanCapacity(), ref.getInitExpr(), ref.getStmnt(), ref.getChild())
	{}
	
	std::string getTypeName(void) const {
		return "pid";
	}

	int getTypeSize(void) const {
		return 0;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};
