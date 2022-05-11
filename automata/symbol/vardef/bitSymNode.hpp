#ifndef BIT_SYM_NODE_H
#define BIT_SYM_NODE_H

#include "varSymNode.hpp"

//T_BIT
class bitSymNode : public varSymNode {
public:
	bitSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr);

	std::string getTypeName(void) const override;

	int getTypeSize(void) const override;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;

	//void printGraphViz(std::ofstream& file) const;
};

#endif