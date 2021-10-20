#ifndef UTYPE_SYM_NODE_H
#define UTYPE_SYM_NODE_H

#include "varSymNode.h"

class tdefSymNode;

//T_UTYPE
class utypeSymNode : public varSymNode{
public:
	utypeSymNode(tdefSymNode* utype, int lineNb);

	utypeSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr)
		: varSymNode(symbol::T_UTYPE, lineNb, name, bound, init)
	{}

	//unsigned int processVariables(symbol* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal) override ;

	tdefSymNode* getUType(void) const {
		return utype;
	}

	void setUType(tdefSymNode* utype) {
		this->utype = utype;
	}

	std::string getTypeName(void) const override {
		return "user";
	}

	int getTypeSize(void) const override {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;

private:
	tdefSymNode* utype;
};

#endif