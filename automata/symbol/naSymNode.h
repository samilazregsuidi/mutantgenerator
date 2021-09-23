#include "varSymNode.h"

class naSymNode : public varSymNode{
public:
	naSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr)
		: varSymNode(symTabNode::T_NA, lineNb, name, bound, init)
	{}

	std::string getTypeName(void) const override {
		assert(false);
		return "NA";
	}

	int getTypeSize(void) const override {
		assert(false);
		return 0;
	}

	void acceptVisitor(symTabVisitor* visitor) const override;
};
