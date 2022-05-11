#ifndef MTYPE_LIST_H
#define MTYPE_LIST_H

#include <string>
#include <map>

#include "symbol.hpp"

//T_CMTYPE
class cmtypeSymNode : public symbol{
public:
	cmtypeSymNode(int lineNb, const std::string& name, int value);

	std::string getTypeName(void) const override;

	int getTypeSize(void) const override;

	bool castTo(const symbol* sym) const override;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;

	//void printGraphViz(std::ofstream& file) const;

private:
	int value;
};

class mtypedefSymNode : public symbol {
public:
	mtypedefSymNode(std::unordered_map<std::string, cmtypeSymNode*> mtypes, int lineNb);

	std::string getTypeName(void) const override;

	int getTypeSize(void) const override;

	const std::unordered_map<std::string, cmtypeSymNode*>& getMTypeList(void) const;

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;

	//void printGraphViz(std::ofstream& file) const;

private:
	 std::unordered_map<std::string, cmtypeSymNode*> mtypes;
};


#endif