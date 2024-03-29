#ifndef UTYPE_SYM_NODE_H
#define UTYPE_SYM_NODE_H

#include "varSymNode.hpp"

class tdefSymNode;

//T_UTYPE
class utypeSymNode : public varSymNode{
public:
	utypeSymNode(tdefSymNode* utype, int lineNb);

	utypeSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr);

	//unsigned int processVariables(symbol* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal) override ;

	tdefSymNode* getUType(void) const;

	void setUType(tdefSymNode* utype);

	std::string getBasicTypeName(void) const override;

	int getTypeSize(void) const override;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;

private:
	tdefSymNode* utype;
};

#endif