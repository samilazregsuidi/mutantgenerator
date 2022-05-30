#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <list>

#include "symbols.hpp"

class variable {
public:
	variable(payload* payLoad, size_t offset, const varSymNode* sym, unsigned int index =  0);

	variable(variable* parent, size_t offset, const varSymNode* sym, unsigned int index =  0);
	
	virtual ~variable();

	virtual variable* deepCopy(void) const;

	std::string getName(void) const;

	symbol::Type getType(void) const;

	bool isGlobal(void) const;
	
	virtual void print(void) const;

	void setValue(int value);
	
	int getValue(void) const;

	void setPayload(payload* payLoad) const;
	
	payload* getPayload(void) const;

	virtual void init(void);
	
	void* getPayloadPtr(void) const;

	void setParent(const variable* parent);

	variable* getParent(void) const;
	
	const std::list<variable*>& getVars(void) const;

	std::string getVarName(const expr* varExpr) const;

	variable* getVar(const std::string& name) const;

	variable* getVar(const expr* varExpr) const;

	void addVar(const std::string& name, variable* var);

	void addVar(variable* subVar);

	virtual size_t getSizeOf(void) const;

protected:
	std::string name;
	const varSymNode* symType;
	unsigned int index;

	const variable* parent;

	size_t offset;
	payload* payLoad;

	std::map<std::string, variable*> varMap;
	std::list<variable*> varList;

	size_t sizeOf;
};

class channel : public variable {
public:
	channel(payload* playLoad, size_t offset, const chanSymNode* sym, unsigned int bound =  0);

	void print(void) const override;

	void send(const expr* e);

	void receive(const expr* e);

	bool isEmpty(void) const;

	bool isFull(void) const;
	
	unsigned int len(void) const;

	size_t getSizeOf(void) const override;
};

class messageField : public variable {
public:
	messageField(payload* payLoad, size_t offset, const varSymNode* sym, unsigned int fieldNumber, unsigned int messageIndex = 0, unsigned int index =  0);
};

#endif