#ifndef MTYPE_LIST_H
#define MTYPE_LIST_H

#include <string>
#include <map>

#include "symbol.h"

//T_CMTYPE
class cmtypeSymNode : public symbol{
public:
	cmtypeSymNode(int lineNb, const std::string& name, int value)
		: symbol(symbol::T_MTYPE, lineNb, name)
	{
		this->value = value;
		this->mask = READ_ACCESS;
	}

	std::string getTypeName(void) const override {
		return "cmtype";
	}

	int getTypeSize(void) const override {
		return 0;
	}

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;

private:
	int value;
};

class mtypedefSymNode : public symbol {
public:
	mtypedefSymNode(std::unordered_map<std::string, cmtypeSymNode*> mtypes, int lineNb)
		: symbol(symbol::T_MTYPE_DEF, "mtype", lineNb)
	{
		this->mtypes = mtypes;
	}

	std::string getTypeName(void) const override {
		return "mtypedef";
	}

	int getTypeSize(void) const override {
		return 0;
	}

	const std::unordered_map<std::string, cmtypeSymNode*>& getMTypeList(void) const {
		return mtypes;
	}

	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;

private:
	 std::unordered_map<std::string, cmtypeSymNode*> mtypes;
};


#endif