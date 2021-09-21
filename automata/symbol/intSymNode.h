#include "varSymNode.h"

//T_INT
class intSymNode : public varSymNode{
public:
	intSymNode(const varSymNode& ref)
		: varSymNode(symTabNode::T_INT, ref.getLineNb(), ref.getName(), ref.getBound(), ref.getInitExpr())
	{}

	std::string getTypeName(void) const {
		return "int";
	}

	int getTypeSize(void) const {
		return 4;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};
