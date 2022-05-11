#ifndef VAR_SYM_NODE_H
#define VAR_SYM_NODE_H

#include "symbol.hpp"

class expr;

class varSymNode : public symbol{
public:
	varSymNode(Type type, int lineNb, const std::string& name = std::string(), unsigned int bound = 1, expr* init = nullptr);

	//TODO: deep copy required for decl mutations

	~varSymNode() override ;

	static varSymNode *createSymbol(Type type, int lineNb, const std::string& name = std::string(), unsigned int bound = 1, expr* init = nullptr);
	
	static varSymNode *createSymbol(Type type, const varSymNode &old);
	
	template<Type type> static varSymNode* createSymbol(int lineNb, const std::string& name = std::string(), unsigned int bound = 1, expr* init = nullptr);

	//unsigned int processVariables(symbol* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal) override;

	expr* getInitExpr(void) const;

	void setInitExpr(expr* newInit);
	
	unsigned int getBound(void) const;

	unsigned int getSizeOf(void) const override; 

	bool castTo(const symbol* sym) const override;

	void printGraphViz(std::ofstream& file) const override;

protected:
	expr* init;
	unsigned int bound;
};

#endif