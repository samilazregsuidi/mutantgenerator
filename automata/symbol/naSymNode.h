#include "varSymNode.h"

class naSymNode : public varSymNode{
public:
	naSymNode(const varSymNode& ref)
		: varSymNode(symTabNode::T_NA, ref.getLineNb(), ref.getName(), ref.getBound(), ref.getInitExpr())
	{}

	std::string getTypeName(void) const {
		assert(false);
		return "NA";
	}

	int getTypeSize(void) const {
		assert(false);
		return 0;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};
