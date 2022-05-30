#ifndef MTYPE_SYM_NODE_H
#define MTYPE_SYM_NODE_H

#include "varSymNode.hpp"

//T_MTYPE
class mtypeSymNode : public varSymNode {
public:
	mtypeSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr);

	~mtypeSymNode(void) override;

	std::string getTypeName(void) const override;

	int getTypeSize(void) const override;

	bool castTo(const symbol* sym) const override;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;
};

//T_CMTYPE
class cmtypeSymNode : public varSymNode {
public:
	cmtypeSymNode(int lineNb, const std::string& name, int value);

	std::string getTypeName(void) const override;

	int getTypeSize(void) const override;

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