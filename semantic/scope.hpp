#ifndef SCOPE_H
#define SCOPE_H

#include <list>
#include <map>
#include <string>

#include "symbols.hpp"

class payload;
class variable;
class channel;
class cmtypeVar;
// A state mask gives for every process the pid, a pointer to its symtab node
// and its offset in the payload
class scope {

public:
	scope(const std::string& name, scope* parent = nullptr);

	virtual ~scope();

	std::list<const scope*> getSubScopes(void) const;

	size_t getOffset(void) const;

	size_t getEndOffset(void) const;

	void setPayload(payload* payLoad);
	
	payload* getPayload(void) const;

	void* getPayloadPtr(void) const;

	virtual void init(void);

	size_t _getSizeOf(void) const;

	size_t getSizeOf(void) const;

	virtual void print(void) const;

	void addRawBytes(size_t size);

	std::list<variable*> addVariables(const varSymNode* sym);

	std::list<variable*> createVariables(const varSymNode* sym);

	//variable* addVariable(const varSymNode* varSym);

	void _addVariable(variable* var);

	variable* getVariable(const std::string& name) const;

	channel* getChannel(const std::string& name) const;

	std::list<variable*> getVariablesList(void) const;

	void clearVariables(void);

	void rmSubScope(scope* sc);

	void addSubScope(scope* sc);

private:
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