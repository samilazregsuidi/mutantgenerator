#ifndef CID_SYM_NODE_H
#define CID_SYM_NODE_H

#include "varSymNode.h"

//T_CID
class cidSymNode : public varSymNode{
public:
	cidSymNode(int lineNb, const std::string& name, int bound = 1, expr* init = nullptr)
		: varSymNode(symbol::T_CID, lineNb, name, bound, init)
	{}
	
	std::string getTypeName(void) const override {
		return "cid";
	}

	int getTypeSize(void) const override {
		return 4;
	}

	void acceptVisitor(symTabVisitor* visitor) const override;
};

#endif
