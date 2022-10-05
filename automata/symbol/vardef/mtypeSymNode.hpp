#ifndef MTYPE_SYM_NODE_H
#define MTYPE_SYM_NODE_H

#include "varSymNode.hpp"

class mtypedefSymNode;

//T_MTYPE
class mtypeSymNode : public varSymNode {
public:
	mtypeSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr);

	~mtypeSymNode(void) override;

	void setSymTable(symTable* parent) override;

	std::string getBasicTypeName(void) const override;

	int getTypeSize(void) const override;

	int getUpperBound(void) const override;
	
	int getLowerBound(void) const override;

	bool castTo(const symbol* sym) const override;

	const mtypedefSymNode* getMTypeDef(void) const;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;

private:
	mtypedefSymNode* def;
};

//T_CMTYPE
class cmtypeSymNode : public varSymNode {
public:
	cmtypeSymNode(int lineNb, mtypedefSymNode* def, const std::string& name, int value);

	std::string getBasicTypeName(void) const override;

	int getTypeSize(void) const override;

	int getUpperBound(void) const override;
	
	int getLowerBound(void) const override;

	bool castTo(const symbol* sym) const override;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;

	int getIntValue(void) const;

	friend class mtypedefSymNode;

	//void printGraphViz(std::ofstream& file) const;

private:
	int value;
	mtypedefSymNode* def;
};

#endif