#include "varSymNode.h"

//T_BYTE
class byteSymNode : public varSymNode{
public:
	byteSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr)
		: varSymNode(symTabNode::T_BYTE, lineNb, name, bound, init)
	{}

	std::string getTypeName(void) const override {
		return "byte";
	}

	int getTypeSize(void) const override {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const override;
};