#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <list>

#include "symbols.hpp"

class expr;
class exprArgList;
class exprRArgList;

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

	unsigned int getVariableId(void) const;

	virtual size_t getSizeOf(void) const;

	static unsigned int vidCounter; 

protected:
	std::string name;
	const varSymNode * const symType;
	unsigned int index;

	const variable* parent;

	size_t offset;
	payload* payLoad;

	std::map<std::string, variable*> varMap;
	std::list<variable*> varList;

	unsigned int vid;
	size_t sizeOf;
};

class constVar : public variable {
public:
	constVar(payload* playLoad, size_t offset, const varSymNode* sym, unsigned int bound =  0);

};

class channel : public variable {
public:
	channel(payload* playLoad, size_t offset, const chanSymNode* sym, unsigned int bound =  0);

	void print(void) const override;

	void send(const std::list<const variable*>& args);

	void receive(const std::list<variable*>& rargs);

	bool isRendezVous(void) const;

	bool isEmpty(void) const;

	bool isFull(void) const;

	variable* getField(unsigned int index) const;
	
	byte len(void) const;

	byte getCapacity(void) const;

	size_t getSizeOf(void) const override;

private:
	void len(byte newLen);
};

class channel : public variable {
public:
	channel(payload* playLoad, size_t offset, const chanSymNode* sym, unsigned int bound =  0);

	~channel() override;

	void print(void) const override;

	void send(const std::list<const variable*>& args);

	void receive(const std::list<variable*>& rargs);

	variable* getField(unsigned int index) const;

	bool isRendezVous(void) const;

	bool isEmpty(void) const;

	bool isFull(void) const;
	
	byte len(void) const;

	byte getCapacity(void) const;

	size_t getSizeOf(void) const override;

private:
	void len(byte newLen);
};

class messageField : public variable {
public:
	messageField(payload* payLoad, size_t offset, const varSymNode* sym, unsigned int fieldNumber, unsigned int messageIndex = 0, unsigned int index =  0);
};

/*
template <typename T> class refVariable : public variable {
public:
	refVariable(payload* playLoad, size_t offset, const varSymNode* sym, unsigned int bound =  0) 
		: variable(payLoad, offset, sym, bound)
		, ref(nullptr)
	{}

	T* getRefVariable(void) const {
		return ref;
	}

	void setRefVariable(T* newRef) const {
		ref = newRef;
		payload->setValue(offset, sym->getType());
	}

private:
	T* ref;
}*/

class CIDVariable : public variable {
public:
	CIDVariable(payload* playLoad, size_t offset, const varSymNode* sym, unsigned int bound =  0);

	channel* getRefChannel(void) const;
	
	void setRefChannel(channel* newRef) const;
};

class PIDVariable : public variable {
public:
	PIDVariable(payload* playLoad, size_t offset, const varSymNode* sym, unsigned int bound =  0);

	process* getRefProcess(void) const;
	
	void setRefProcess(process* newRef) const;
};

#endif