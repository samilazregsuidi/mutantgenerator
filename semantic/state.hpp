#ifndef STATE_H
#define STATE_H
/*
 * ENCODING OF STATES
 * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * A state consists of a set of active processes and of the values of the
 * variables of these processes.  It is thus represented by two elements:
 *
 *  - A list of active processes, and for each a pointer to its symbol table.
 *
 *  - A block of memory containing the variables of these processes.  This is
 *    more efficient than a linked list of values and basically corresponds to
 *    a run-time struct.
 *
 *    The block is divided into sub-blocks, one for each process.  The
 *    list of processes contains the offsets of the sub-block of each process.
 *    One sub-block holds all variable values in the order in which they
 *    were declared in the symbol table of the process.  For each variable, a
 *    predefined chunk of memory is allocated (all variable types are finite
 *    and cannot grow).
 *
 *
 * To test equivalence of two states, it is sufficient to test equivalence of
 * payloadSize, and if equivalent, the whole blocks.
 */

// Bytes needed to record the system variables: exclusive and handshake.
// For any channel, its offset is positive. Thus, we use the value -1 to specify the absence of rendezvous request.
#define NO_HANDSHAKE (int)0
#define HANDSHAKE_VAR (int)0 //T_INT
#define OFFSET_HANDSHAKE_VAR 0
#define SIZE_HANDSHAKE_VAR (sizeof(OFFSET_HANDSHAKE_VAR))

// For any process, its pid is between 0 and 254. Thus, we use the value 255 to specify absence of a process
#define NO_PROCESS (ubyte)255 // T_BYTE
#define MAX_PROCESS (ubyte)254 // T_BYTE
#define EXCLUSIVITY_VAR (ubyte)0 //T_BYTE
#define OFFSET_EXCLUSIVITY_VAR SIZE_HANDSHAKE_VAR
#define SIZE_EXCLUSIVITY_VAR (sizeof(EXCLUSIVITY_VAR))

#include <list>
#include <map>
#include <tuple>
#include <cassert>

#include "cuddObj.hh"

class transition;

#include "symbols.hpp"

class astNode;
class expr;

class fsm;
class fsmNode;
class fsmEdge;

class payload;
class scope;
class process;

class variable;
class channel;

// State
class state {
public:

	friend class process;

	state(const fsm* stateMachine); // Creates the initial state by setting all variables' value in the payload. Does not set the payloadHash.

	//state(const state& s) = default;

	state* deepCopy(void) const;
	/**
	 * Frees the memory used by a given state. It does NOT free any symbol tables, FSM or mtypes list.
	 * However, it DOES free:
	 *  - the memory chunk,
	 *  - all state masks of active processes,
	 *  - the state mask of the never claim (if any),
	 *  - all channel references,
	 *
	 * If the keepPayloadAndFeatures parameter is false, it also frees:
	 *  - boolean formula and
	 *  - the state structure itself.
	 *
	 * This parameter is only true when destroying a stack element where the payload and boolean function
	 * are still used in the visited states hashtable.
	 */
	~state();

	// Executable transitions in state
	std::list<transition*> executables(byte stutter, int nbErrors, byte* hasDeadlock, byte* resetExclusivity) const;

	//std::list<transition*> executablesNonStutter(ptList props, symTable* globalSymTab, state* state, byte stutter, int nbErrors, byte* hasDeadlock);
	
	std::list<transition*> executablesNever(void) const;

		// Expression evaluation (flag)
	#define EVAL_EXECUTABILITY 0
	#define EVAL_EXPRESSION 1

	std::list<transition*> executables(void) const;

	std::list<transition*> executables(process* proc) const;

	std::list<transition*> executables(byte pid) const;

	std::map<process*, std::list<transition*>> executablesMap(void) const;

	std::list<state*> post(void) const;

	bool hasDeadlock(void) const;

	unsigned int getErrors(void) const;

	void addError(void);

	// Applying statements

	state* apply(const transition* trans);
	
	state* applyRepeated(const std::list<transition*>& procTrans, byte preserve, byte* assertViolation);

	static state* apply(const state* s, const transition* t);

	static state* applyRepeated(const state* s, const std::list<transition*>& procTrans, byte preserve, byte* assertViolation);
	
	//state* applyNever(const transition* trans);

	process* getProc(int pid) const; // Returns the stateMask with pid 'pid'.

	process* getNeverClaim(void) const;

	const process* getExclusiveProc(void) const;

	byte getExclusiveProcId(void) const;

	bool hasExclusivity(void) const;

	void resetExclusivity(void) const;

	void setExclusivity(const process* proc) const;

	void setExclusivity(byte pid) const;

	//void initSym(unsigned int preOffset, const varSymNode* sym);

	//void initSymTab(unsigned int preOffset, const symTable* symTab);

	//void initGlobalVariables(void);

	//void initVariables(const process* mask);

	bool requestHandShake(const std::pair<const channel*, const process*>& handShake) const;

	void setHandShake(const std::pair<const channel*, const process*>& handShake) const;

	//void setHandShake(unsigned int cid) const;

	std::pair<const channel*, const process*> getHandShakeRequest(void) const;

	const channel* getHandShakeRequestChan(void) const;

	const process* getHandShakeRequestProc(void) const;

	unsigned int getHandShakeRequestId(void) const;

	bool hasHandShakeRequest(void) const;

	void resetHandShake(void) const;

	bool getTimeoutStatus(void) const;

	/*
	* Gets the symbol table of a channel by giving its offset in the memory chunk.
	* The structure contained in state->chanRefs is used to get the table.
	* If no channel exists at the given offset, returns NULL.
	*/

	/*
	* Creates a new process and returns its pid.
	* Reserves some memory for the proctype variables in the memory chunk and initializes the value of these variables.
	* Does not change the payloadHash.
	*/
	process* addProctype(const procSymNode* proctype, int i = 0);

	process* addProctype(const procSymNode* proctype, const std::list<const variable*>& args);

	/*
	* Defines the never claim of the execution.
	* Set its initial FSM node in the payload.
	* Does not change the payloadHash.
	*/
	process* addNever(const neverSymNode* neverSym);

	size_t _getSizeOf(void) const;

	size_t getSizeOf(void) const;

	/*
	* If the pid of the last process is 'pid' then:
	*  - the stateMask of the process is removed
	*  - the number of processes in the states updated
	*  - the chunk of memory of the process is removed from the state's payload.
	* Does not change the payloadHash.
	*/
	//void killProctype(int pid);

	//void clean(void); // Applies stateKillProctype while this latter function succeeds.

	// State printing
	void print(const state* diffState) const;

	// State comparison. Returns:
	#define STATES_DIFF 0				// if s1 and s2 are totally different states, meaning s1 is fresh.
	#define STATES_SAME_S1_VISITED 1	// if s1 and s2 are identical but s2 is reachable by more products; hence, s1 adds nothing new
	#define STATES_SAME_S1_FRESH 2		// if s1 and s2 are identical but s1 has products that were not explored with s2; hence, s1 is fresh
	
	byte compare(const state& s2) const;

	void print(void) const;

	void printGraphViz(unsigned long i) const;

	void printTexada(void) const;

	static state* Post(const transition* trans, const state* s);

	static std::list<state*> Post(const state* s);

	unsigned long hash(void) const;

	const ADD& getFeatures(void) const;

private:
	void setPayload(payload* payLoad);

	void assign(scope* sc);

public:
	const symTable* const globalSymTab;
	const fsm* const stateMachine;

	ADD features;

	std::list<process*> procs;
	process* never; 	// If f is an LTL formula to be checked, never is the stateMask conversion of ~f.
								//	Furthermore, never->node returns the current node in this FSM. Note that pid and offset have no importance here.
								//	Also, never->next is supposed to be NULL.

	unsigned int pidCounter;
	int nbProcesses; 			// Number of running processes.
	int nbNeverClaim;			// Number of neverClaim
	int lastStepPid; 			// pid of the process that fired transition that got us into this state. (NOT part of the actual state of the system, just a helper)
	
	scope* global;

	mutable const channel* handShakeChan;
	mutable const process* handShakeProc;
	mutable const process* exclusiveProc;
	mutable bool timeout;

	double prob;

	const transition* trans;
};

template<> struct std::hash<state*> {
	size_t operator()(const state* s) const noexcept {
		return s->hash();
	}
};

#endif