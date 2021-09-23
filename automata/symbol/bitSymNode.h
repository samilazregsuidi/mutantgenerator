#include "varSymNode.h"

//T_BIT
class bitSymNode : public varSymNode{
public:
	bitSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr)
		: varSymNode(symTabNode::T_BIT, lineNb, name, bound, init)
	{}

	std::string getTypeName(void) const override {
		return "bit";
	}

	int getTypeSize(void) const override{
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const override;
};
