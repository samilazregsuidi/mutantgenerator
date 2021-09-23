#include "varSymNode.h"

//T_MTYPE
class mTypeSymNode : public varSymNode{
public:
	mTypeSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr)
		: varSymNode(symTabNode::T_MTYPE, lineNb, name, bound, init)
	{}

	std::string getTypeName(void) const override {
		return "mtype";
	}

	int getTypeSize(void) const override {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const override;
};