#ifndef VAR_SYM_NODE_H
#define VAR_SYM_NODE_H

#include "symTabNode.h"

class expr;

class varSymNode : public symTabNode{
protected:
	varSymNode(Type type, int lineNb, const std::string& sVal = std::string(), int bound = 1, expr* init = nullptr)
		: symTabNode(type, lineNb, name)
	{
		this->init = init;
		this->bound = bound;
	}

public:
	//static varSymNode *createSymTabNode(Type itype, const varSymNode &old);
	//static varSymNode *createSymTabNode(Type itype, int lineNb, const std::string &sVal, int bound, expr *init);
	
	template<Type type> static varSymNode* createSymTabNode(const varSymNode &old);

	unsigned int processVariables(symTabNode* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal);
	expr* getInitExpr(void) const;
	int getBound(void) const;

protected:
	expr* init;
	int bound;
};

#endif