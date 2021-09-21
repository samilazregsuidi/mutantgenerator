#include "varSymNode.h"

//T_UNSGN
class unsgnSymNode : public varSymNode{
public:
	unsgnSymNode(const varSymNode& ref)
		: varSymNode(symTabNode::T_UNSGN, ref.getLineNb(), ref.getName(), ref.getBound(), ref.getInitExpr())
	{}

	std::string getTypeName(void) const {
		return "unsigned";
	}

	int getTypeSize(void) const {
		return 2;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};
