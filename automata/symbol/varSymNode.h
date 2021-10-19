#ifndef VAR_SYM_NODE_H
#define VAR_SYM_NODE_H

#include "symbol.h"

class expr;

class varSymNode : public symbol{
public:
	varSymNode(Type type, int lineNb, const std::string& name = std::string(), unsigned int bound = 1, expr* init = nullptr)
		: symbol(type, lineNb, name)
	{
		this->init = init;
		this->bound = bound;
	}

	~varSymNode() override ;

	static varSymNode *createSymbol(Type type, int lineNb, const std::string& name = std::string(), unsigned int bound = 1, expr* init = nullptr);
	static varSymNode *createSymbol(Type type, const varSymNode &old);
	template<Type type> static varSymNode* createSymbol(int lineNb, const std::string& name = std::string(), unsigned int bound = 1, expr* init = nullptr);

	//unsigned int processVariables(symbol* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal) override;
	
	expr* getInitExpr(void) const {
		return init;
	}
	
	int getBound(void) const {
		return bound;
	}

protected:
	expr* init;
	unsigned int bound;
};

#endif