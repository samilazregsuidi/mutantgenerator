#include "varSymNode.h"

//T_BIT
class bitSymNode : public varSymNode{
public:
	bitSymNode(const varSymNode& ref)
		: varSymNode(symTabNode::T_BIT, ref.getLineNb(), ref.getName(), ref.getBound(), ref.getInitExpr())
	{}

	std::string getTypeName(void) const {
		return "bit";
	}

	int getTypeSize(void) const {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};
