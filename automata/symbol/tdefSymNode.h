#include "symTabNode.h"

//T_TDEF
class tdefSymNode : public symTabNode{
public:
	tdefSymNode(const std::string& name,  varSymNode* child, int lineNb)
		: symTabNode(symTabNode::T_TDEF, name, lineNb)
	{
		this->child = child;
	}

	std::string getTypeName(void) const {
		return "typedef";
	}

	int getTypeSize(void) const {
		return 1;
	}

	varSymNode* getChild(void) const {
		return child;
	}

	unsigned int processVariables(symTabNode* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal);

	operator std::string(void) const ;

	void acceptVisitor(symTabVisitor* visitor) const ;

private:
	varSymNode* child;
};
