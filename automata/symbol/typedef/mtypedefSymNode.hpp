#ifndef MTYPE_LIST_H
#define MTYPE_LIST_H

#include <string>
#include <map>

#include "symbol.hpp"

class cmtypeSymNode;

class mtypedefSymNode : public symbol {
public:
	mtypedefSymNode(const std::unordered_map<std::string, cmtypeSymNode*>& mtypes, int lineNb);

	mtypedefSymNode(int lineNb);

	std::string getTypeName(void) const override;

	std::string getBasicTypeName(void) const override;

	int getTypeSize(void) const override;

	int getUpperBound(void) const;
	
	int getLowerBound(void) const;

	void addCMType(cmtypeSymNode* mtype);

	const std::unordered_map<std::string, cmtypeSymNode*>& getMTypeList(void) const;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;

	std::string getCmtypeSymNodeName(int value) const;

	//void printGraphViz(std::ofstream& file) const;

private:
	 std::unordered_map<std::string, cmtypeSymNode*> mtypes;
};


#endif