#include "varSymNode.h"

//T_UNSGN
class unsgnSymNode : public varSymNode{
public:
	unsgnSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr)
		: varSymNode(symTabNode::T_UNSGN, lineNb, name, bound, init)
	{}

	std::string getTypeName(void) const override {
		return "unsigned";
	}

	int getTypeSize(void) const override {
		return 2;
	}

	void acceptVisitor(symTabVisitor* visitor) const override ;
};
