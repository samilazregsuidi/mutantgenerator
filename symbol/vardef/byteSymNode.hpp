#ifndef BYTE_SYM_NODE_H
#define BYTE_SYM_NODE_H

#include "varSymNode.hpp"

//T_BYTE
class byteSymNode : public varSymNode{
public:
	byteSymNode(int lineNb, const std::string& name = std::string(), int bound = 1, expr* init = nullptr);

	std::string getBasicTypeName(void) const override;

	int getTypeSize(void) const override;

	int getUpperBound(void) const override;
	
	int getLowerBound(void) const override;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;

	//void printGraphViz(std::ofstream& file) const;
};

#endif