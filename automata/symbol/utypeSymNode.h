#include "varSymNode.h"

class tdefSymNode;

//T_UTYPE
class utypeSymNode : public varSymNode{
public:
	utypeSymNode(tdefSymNode* utype, int lineNb);

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
