#include "varSymNode.h"

//T_BOOL
class boolSymNode : public varSymNode{
public:
	boolSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr)
		: varSymNode(symTabNode::T_BOOL, lineNb, name, bound, init)
	{}

	std::string getTypeName(void) const override {
		return "bool";
	}

	int getTypeSize(void) const override {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const override;
};
