#ifndef PROCESS_H
#define PROCESS_H

// Bytes needed to record the system variables: exclusive and handshake.
#define OFFSET_EXCLUSIVE (char)0 // T_BYTE
#define OFFSET_HANDSHAKE (int)1 // T_INT

#define SYS_VARS_SIZE sizeof(OFFSET_EXCLUSIVE) + sizeof(OFFSET_HANDSHAKE)

// For any channel, its offset is positive. Thus, we use the value -1 to specify the absence of rendezvous request.
#define NO_HANDSHAKE (int)0

// For any process, its pid is between 0 and 254. Thus, we use the value 255 to specify absence of a process
#define NO_PROCESS (char)255 // T_BYTE
#define MAX_PROCESS (char)254 // T_BYTE

#include <list>
#include <map>
#include <tuple>
#include <cassert>

typedef unsigned char byte;

class transition;

#include "symbols.hpp"

class astNode;
class expr;

class fsm;
class fsmNode;
class fsmEdge;

class state;

// A state mask gives for every process the pid, a pointer to its symtab node
// and its offset in the payload
class process {
public:
	process(state* s, size_t offset, const seqSymNode* sym, const fsmNode* start, byte pid, unsigned int index = 0);

	process(const process& p);

	process* deepCopy(void) const;

	~process();

	std::string getName(void) const;

	symbol::Type getType(void) const;

	void setPayload(payload* payLoad) const;
	
	payload* getPayload(void) const;

	void* getPayloadPtr(void) const;

	void init(void);

	byte getPid(void) const;

	size_t getSizeOf(void) const;

	void print(void) const;

	const fsmNode* getNodePointer(void) const;

	void storeNodePointer(const fsmNode* pointer);

	bool isAccepting(void) const;

	bool isAtomic(void) const;

	variable* addVariable(const varSymNode* varSym);

	variable* addChannel(const chanSymNode* chanSym);

	const std::list<variable*>& getVars(void) const;

	std::string getVarName(const expr* varExpr) const;

	variable* getVar(const std::string& name) const;

	variable* getVar(const expr* varExpr) const;

	channel* getChannelVar(const expr* varExpr) const;

	void addVar(const std::string& name, variable* var);

	void addVar(variable* subVar);

public:
	std::string name;
	const seqSymNode* symType;
	unsigned int index;

	const variable* parent;

	size_t offset;
	payload* payLoad;

	std::map<std::string, variable*> varMap;
	std::list<variable*> varList;

	size_t sizeOf;

	state* s;
	byte pid;
	const fsmNode* start;
};

#endif