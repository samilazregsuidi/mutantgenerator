#include "varSymNode.h"

//T_BOOL
class boolSymNode : public varSymNode{
public:
	boolSymNode(const varSymNode& ref)
		: varSymNode(symTabNode::T_BOOL, ref.getLineNb(), ref.getName(), ref.getBound(), ref.getInitExpr())
	{}

	std::string getTypeName(void) const {
		return "bool";
	}

	int getTypeSize(void) const {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};
