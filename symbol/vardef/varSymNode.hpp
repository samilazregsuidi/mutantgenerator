#ifndef VAR_SYM_NODE_H
#define VAR_SYM_NODE_H

#include "symbol.hpp"

class expr;

class varSymNode : public symbol{
public:
	static varSymNode *createSymbol(Type type, int lineNb, const std::string& name = std::string(), unsigned int bound = 1, expr* init = nullptr);
	
	static varSymNode *createSymbol(Type type, const varSymNode &old);
	
	template<Type type> static varSymNode* createSymbol(int lineNb, const std::string& name = std::string(), unsigned int bound = 1, expr* init = nullptr);

	static int getLowerBound(Type type);

	static int getUpperBound(Type type);
	
	template<Type type> static int getLowerBound(void);

	template<Type type> static int getUpperBound(void);
	
public:
	varSymNode(Type type, int lineNb, const std::string& name = std::string(), unsigned int bound = 1, expr* init = nullptr);

	//TODO: deep copy required for decl mutations

	~varSymNode() override ;

	expr* getInitExpr(void) const;

	void setInitExpr(expr* newInit);
	
	unsigned int getBound(void) const;

	std::string getTypeName(void) const override;

	virtual int getUpperBound(void) const;
	
	virtual int getLowerBound(void) const;

	unsigned int getSizeOf(void) const override; 

	bool castTo(const symbol* sym) const override;

	void printGraphViz(std::ofstream& file) const override;

protected:
	expr* init;
	unsigned int bound;
};

#endif