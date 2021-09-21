#include "varSymNode.h"

//T_UTYPE
class utypeSymNode : public varSymNode{
public:
	utypeSymNode(const varSymNode& ref)
		: varSymNode(symTabNode::T_UTYPE, ref.getLineNb(), ref.getName(), ref.getBound(), ref.getInitExpr())
	{}
	
	utypeSymNode(tdefSymNode* utype, int lineNb)
		: varSymNode(symTabNode::T_UTYPE, lineNb, std::string())
	{
		assert(type != nullptr && type->getType() == symTabNode::T_TDEF);
		this->type = type;
	}

	unsigned int processVariables(symTabNode* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal);

	tdefSymNode* getUType(void) const {
		return type;
	}

	std::string getTypeName(void) const {
		return "user";
	}

	int getTypeSize(void) const {
		return 1;
	}

	void acceptVisitor(symTabVisitor* visitor) const ;

private:
	tdefSymNode* type;
};
