#include "varSymNode.h"

//T_MTYPE
class mTypeSymNode : public varSymNode{
public:
	mTypeSymNode(const varSymNode& ref)
		: varSymNode(symTabNode::T_MTYPE, ref.getLineNb(), ref.getName(), ref.getBound(), ref.getInitExpr())
	{}

	std::string getTypeName(void) const {
		return "mtype";
	}

	int getTypeSize(void) const {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;
};