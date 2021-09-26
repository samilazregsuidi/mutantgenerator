#ifndef VAR_SYM_NODE_H
#define VAR_SYM_NODE_H

#include "symTabNode.h"

class expr;

class varSymNode : public symTabNode{
public:
	varSymNode(Type type, int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr)
		: symTabNode(type, lineNb, name)
	{
		this->init = init;
		this->bound = bound;
	}

	~varSymNode() override ;

	static varSymNode* merge(varSymNode* list, varSymNode* newSym);

	static varSymNode *createSymTabNode(Type type, int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr);
	static varSymNode *createSymTabNode(Type type, const varSymNode &old);
	template<Type type> static varSymNode* createSymTabNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr);

	//unsigned int processVariables(symTabNode* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal) override;
	
	expr* getInitExpr(void) const {
		return init;
	}
	
	int getBound(void) const {
		return bound;
	}

protected:
	expr* init;
	int bound;
};

#endif