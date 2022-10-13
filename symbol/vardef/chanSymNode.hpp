#ifndef CHAN_SYM_NODE_H
#define CHAN_SYM_NODE_H

#include <list>

#include "varSymNode.hpp"

//T_CHAN
class chanSymNode : public varSymNode{
public:
	chanSymNode(int lineNb, const std::string& name, int bound, int capacity, const std::list<varSymNode*>& types);

	chanSymNode(int lineNb, const std::string& name, int bound, expr* init);

	~chanSymNode(void) override ;

	std::string getBasicTypeName(void) const override;

	int getTypeSize(void) const override;

	const std::list<varSymNode*>& getTypeList(void) const;

	int getCapacity(void) const;

	bool castTo(const symbol* sym) const override;
	
	void acceptVisitor(symTabVisitor* visitor) override;

	void acceptVisitor(symTabConstVisitor* visitor) const override;
	

private:
	std::list<varSymNode*> types;
	int capacity;
};

#endif
