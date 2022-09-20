#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <list>

#include "symbols.hpp"

typedef char byte;
typedef unsigned char ubyte;

class scope;
class payload;
class process;

class expr;
class exprArgList;
class exprRArgList;

class variable {
public:
	friend class scope;

	variable(scope* sc, size_t offset, const varSymNode* sym, unsigned int index =  0);

	variable(scope* sc, variable* parent, size_t offset, const varSymNode* sym, unsigned int index =  0);

	variable(const variable& other);
	
	virtual variable* deepCopy(void) const;

	virtual ~variable();

	virtual std::string getName(void) const;

	virtual symbol::Type getType(void) const;

	bool isGlobal(void) const;
	
	virtual void print(void) const;

	virtual void printTexada(void) const;

	virtual void setValue(int value);
	
	virtual int getValue(void) const;

	virtual void init(void);

	virtual void assign(scope* sc);

	scope* getScope(void) const;

	void setParent(const variable* parent);

	variable* getParent(void) const;

	void addField(const std::string& name, variable* var);

	void addField(variable* subVar);

	void addPrivateField(variable* field);

	bool hasSubFields(void) const;

	std::list<variable*> getSubFields(void) const;

	void clearVariables(void);

	unsigned int getVariableId(void) const;

	virtual size_t getSizeOf(void) const;

	virtual size_t _getSizeOf(void) const;

	virtual int operator = (const variable& rvalue);

	virtual int operator ++ (void);

	virtual int operator -- (void);

	virtual int operator ++ (int);

	virtual int operator -- (int);

	virtual bool operator == (const variable& other) const;

	virtual bool operator != (const variable& other) const;

	/****************************************************/

	static unsigned int vidCounter; 

protected:
	std::string name;
	scope* sc;
	const varSymNode * const symType;
	unsigned int index;

	const variable* parent;

	size_t offset;

	unsigned int vid;
	size_t sizeOf;

	std::list<variable*> varList;

	bool isHidden;
};

class utypeVar : public variable {
public:
	utypeVar(scope* sc, size_t offset, const utypeSymNode* sym, unsigned int index =  0);

	utypeVar(scope* sc, variable* parent, size_t offset, const utypeSymNode* sym, unsigned int index =  0);

	~utypeVar() override {}

	variable* deepCopy(void) const override;

	int operator = (const variable& rvalue) override;

	int operator ++ (void) override;

	int operator -- (void) override;

	int operator ++ (int) override;

	int operator -- (int) override;

	bool operator == (const variable& other) const override;

	bool operator != (const variable& other) const override;

	void print(void) const override;

	void printTexada(void) const override;
};

class boolVar : public variable {
public:
	boolVar(scope* sc, size_t offset, const boolSymNode* sym, unsigned int index =  0);

	boolVar(scope* sc, variable* parent, size_t offset, const boolSymNode* sym, unsigned int index =  0);

	variable* deepCopy(void) const override;

	int operator ++ (void) override;

	int operator -- (void) override;

	int operator ++ (int) override;

	int operator -- (int) override;

	void print(void) const override;

	void printTexada(void) const override;
};

class constVar : public variable {
public:

	constVar(int value, symbol::Type type, int lineNb);

	variable* deepCopy(void) const override;

	symbol::Type getType(void) const override;

	int getValue(void) const override;

	void setValue(int value) override;

	int operator = (const variable& rvalue) override;

	int operator ++ (void) override;

	int operator -- (void) override;

	int operator ++ (int) override;

	int operator -- (int) override;

private:
	int value;
	symbol::Type type;
	int lineNb;

};

class mtypeVar : public variable {
public:
	mtypeVar(scope* sc, size_t offset, const mtypeSymNode* sym, unsigned int index =  0);

	mtypeVar(scope* sc, variable* parent, size_t offset, const mtypeSymNode* sym, unsigned int index =  0);

	variable* deepCopy(void) const override;

	virtual void init(void) override;

	int operator ++ (void) override;

	int operator -- (void) override;

	int operator ++ (int) override;

	int operator -- (int) override;

	void print(void) const override;

	void printTexada(void) const override;
};

class cmtypeVar : public variable {
public:
	cmtypeVar(scope* sc, const cmtypeSymNode* sym);

	void setValue(int value) override;
	
	virtual int getValue(void) const override;

	variable* deepCopy(void) const override;

	int operator = (const variable& rvalue) override;

	int operator ++ (void) override;

	int operator -- (void) override;

	int operator ++ (int) override;

	int operator -- (int) override;

	void print(void) const override;

	void printTexada(void) const override;
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

class PIDVar : public variable {
public:
	PIDVar(scope* sc, size_t offset, const pidSymNode* sym = nullptr, unsigned int bound =  0);

	variable* deepCopy(void) const override;

	process* getRefProcess(void) const;
	
	void setRefProcess(process* newRef);

	void assign(scope* sc) override;

private:
	process* ref;
};

#endif