#ifndef SCOPE_H
#define SCOPE_H

#include <list>
#include <map>
#include <string>

#include "symbols.hpp"

class payload;
class variable;
class channel;
class process;
class cmtypeVar;
// A state mask gives for every process the pid, a pointer to its symtab node
// and its offset in the payload
class scope {

public:
	scope(const std::string& name, scope* parent = nullptr);

	virtual scope* deepCopy(void) const;

	virtual ~scope();

	std::list<scope*> getSubScopes(void) const;

	scope* getSubScope(const std::string& name) const;

	std::string getName(void) const;

	size_t getOffset(void) const;

	size_t getEndOffset(void) const;

	void setPayload(payload* payLoad);
	
	payload* getPayload(void) const;

	virtual void init(void);

	size_t _getSizeOf(void) const;

	size_t getSizeOf(void) const;

	virtual void print(void) const;

	virtual void printTexada(void) const;

	virtual void printHexadecimal(void) const;

	void addRawBytes(size_t size);

	std::list<variable*> addVariables(const varSymNode* sym);

	std::list<variable*> createVariables(const varSymNode* sym);

	//variable* addVariable(const varSymNode* varSym);

	void _addVariable(variable* var);

	variable* getVariable(const std::string& name) const;

	channel* getChannel(const std::string& name) const;

	process* getProcess(const std::string& name) const;

	std::list<process*> getProcesses(void) const;

	std::list<variable*> getVariablesList(void) const;

	std::map<std::string, variable*> getVariablesMap(void) const;

	void clearVariables(void);

	void rmSubScope(scope* sc);

	void addSubScope(scope* sc);

	unsigned long hash(void) const;

protected:
	std::string name;
	scope* parent;
	std::list<scope*> subScopes;

	size_t offset;
	payload* payLoad;

	size_t rawBytes;
	std::map<std::string, variable*> varMap;
	std::list<variable*> varList;

	size_t sizeOf;
};

#endif