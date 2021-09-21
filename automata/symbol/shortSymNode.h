#include "varSymNode.h"

//T_SHORT
class shortSymNode : public varSymNode{
public:
	shortSymNode(const varSymNode& ref)
		: varSymNode(symTabNode::T_SHORT, ref.getLineNb(), ref.getName(), ref.getBound(), ref.getInitExpr())
	{}

	std::string getTypeName(void) const {
		return "short";
	}

	int getTypeSize(void) const {
		return 2;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};
