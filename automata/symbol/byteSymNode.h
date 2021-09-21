#include "varSymNode.h"

//T_BYTE
class byteSymNode : public varSymNode{
public:
	byteSymNode(const varSymNode& ref)
		: varSymNode(symTabNode::T_BYTE, ref.getLineNb(), ref.getName(), ref.getBound(), ref.getInitExpr())
	{}

	std::string getTypeName(void) const {
		return "byte";
	}

	int getTypeSize(void) const {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};