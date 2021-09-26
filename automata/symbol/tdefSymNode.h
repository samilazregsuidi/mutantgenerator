#ifndef TDEF_SYM_NODE_H
#define TDEF_SYM_NODE_H

#include "symTabNode.h"

//T_TDEF
class tdefSymNode : public symTabNode{
public:
	tdefSymNode(const std::string& name,  varSymNode* child, int lineNb)
		: symTabNode(symTabNode::T_TDEF, name, lineNb)
	{
		this->child = child;
	}

	~tdefSymNode(void) override ;

	std::string getTypeName(void) const override {
		return "typedef";
	}

	int getTypeSize(void) const override {
		return 1;
	}

	varSymNode* getChild(void) const {
		return child;
	}

	//unsigned int processVariables(symTabNode* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal) override ;

	operator std::string(void) const override ;

	void acceptVisitor(symTabVisitor* visitor) const override;

private:
	varSymNode* child;
};

#endif
