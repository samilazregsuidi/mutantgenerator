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
#define SYS_VARS_SIZE 5 + sizeof(void *)
#define OFFSET_EXCLUSIVE (char)0 // T_BYTE
#define OFFSET_HANDSHAKE (int)1 // T_INT
#define OFFSET_NEVERNODE (int)5

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

class symTable;
class symbol;
class chanSymNode;
class seqSymNode;
class procSymNode;
class neverSymNode;
class varSymNode;
class chanSymNode;

class astNode;
class expr;

class fsm;
class fsmNode;
class fsmEdge;

// A state mask gives for every process the pid, a pointer to its symtab node
// and its offset in the payload
class process {
public:
	process(void);

	process(const process& p);

	~process();

public:
	const seqSymNode* sym;
	int pid;					// List of processes and their offset in the state
	unsigned int varOffset; 		// Offset of the process in the chunk of memory.
								// The address of the process current node can be found in the payload at offset 'offset - sizeof(void *)'.
	process* next;
};

// A channel ref gives for every channel the offset.
class channelRef {
public:
	channelRef(void);

	channelRef(const channelRef& c);

	~channelRef();
public:
	unsigned int channelOffset;
	const chanSymNode* chanSym;
	channelRef* next;
};

// State
class state {
public:
	state(const symTable* globalSymTab, const fsm* stateMachine); // Creates the initial state by setting all variables' value in the payload. Does not set the payloadHash.

	state(const state& s);
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

	//trans or state, signature can be optimized!
	int eval(unsigned int procOffset, const astNode* node, byte flag) const; // Return true <=> transition 'trans' is executable on process 'mask'.

	// Applying statements
	state* apply(const transition* procTrans, byte preserve, byte* assertViolation); // Execute a transition on a given process.
	
	state* applyRepeated(const std::list<transition*>& procTrans, byte preserve, byte* assertViolation);
	
	state* applyNever(const fsmEdge* transition);

	// Access and modification of variables
	const fsmNode* getNodePointer(const process* mask) const; // Returns the current FSM node of process 'mask' in 'state'.
	
	void storeNodePointer(process* mask, const fsmNode* pointer); // Set the current FSM node of process 'mask' in 'state' as 'pointer'.

	/*
	* Returns the offset of the variable referenced by 'expression' in 'process' and 'state'.
	* Parameters:
	*    - 'state' is necessary to evaluate the index of an array expression.
	*    - process is the environment in which the variable is ANALYZED, NOT in the one the variable is DEFINED.
	*    - On first call, preOffset must have the same value as the offset of its environment (i.e. global or process).
	*/
	unsigned int getVarOffset(const symbol* sym, unsigned int preOffset, const expr* expression) const;

	/*
	* Reads 'nb' bytes in a memory chunk of the state, at offset 'offset', puts them in an array of byte and returns it.
	*/
	const byte* readValues(unsigned int offset, int nb) const;

	/*
	* Stores 'nb' bytes in a memory chunk, at offset 'offset'.
	* Those bytes are read from the byte array 'values'.
	* The array is not freed afterward.
	*
	* Does not change the payloadHash.
	*/
	void storeValues(unsigned int offset, int nb, const byte* values);

	// Returns the value stored in 'chunk' at offset 'offset'. The number of read bytes depends on 'type'.
	/*
	* Gets the value of ONE cells in a memory chunk of the state.
	*/
	template <typename T> T& getValue(unsigned int offset) const {
		byte* bytePtr = reinterpret_cast<byte*>(payload);
		assert(bytePtr);
		bytePtr += offset;

		T* tPtr = (reinterpret_cast<T*>(bytePtr));
		assert(tPtr);
		return *tPtr;
	}
	
	// Set the value stored in 'chunk' at offset 'offset' to 'value'. The number of read bytes depends on 'type'.
	
	
	/**
	 * Sets the value of ONE cells in the memory chunk.
	 *
	 * Does not change the payloadHash.
	 */
	template <typename T> void setValue(unsigned int offset, const T& value) {
		byte* bytePtr = reinterpret_cast<byte*>(payload);
		assert(bytePtr);
		bytePtr += offset;

		T* tPtr = (reinterpret_cast<T*>(bytePtr));
		assert(tPtr);
		*tPtr = value;
	}

	/**
	 * Returns a given channel 'len' (i.e. the number of messages stored in the channel).
	 * EFFECTS: None.
	 */
	byte channelLen(unsigned int procOffset, expr* channelVar) const;

	/**
	 * Gets the first message in the channel.
	 *
	 * EFFECTS:
	 * 	- Modifies the payload by changing the value of some variable passed as argument for the reception.
	 * WARNING:
	 * 	This function does NOT check if there really is a message stored in the channel
	 * 	and if the arguments of the polling respects the size and type of the parameters.
	 */
	void channelPoll(unsigned int procOffset, expr* expression);

	/**
	 * Stores a message in a given channel.
	 *
	 * EFFECTS:
	 * 	- Modifies the state payload OR _handshake_transit by storing the message field.
	 * 	- Modifies the state payload by incrementing the 'len' value of the concerned channel (EVEN in the
	 * 	handshake case).
	 * WARNING:
	 * 	The message is supposed to fit the type and capacity constraints.
	 * 	channelVar must refer to an ExpNode of type E_VARREF or E_VAR_NAME that
	 * 	itself refers to a channel.
	 */
	void channelSend(unsigned int procOffset, expr* expression);

	/**
	 * Gets AND removes the first message of the channel.
	 *
	 * EFFECTS:
	 * 	- Modifies the payload by changing the value of some variable passed as argument for the reception.
	 * 	- Modifies the payload by decrementing the 'len' value of the channel (EVEN in the handshake case).
	 * WARNING:
	 * 	This function does NOT check if there really is a message stored in the channel.
	 * 	channelVar must refer to an ExpNode of type E_VARREF or E_VAR_NAME that
	 * 	itself refers to a channel.
	 */
	void channelReceive(unsigned int procOffset, expr* expression);

	/**
	 * Returns 0 iff a given channel has no message stored.
	 * EFFECTS: None.
	 */
	byte channelIsEmpty(unsigned int procOffset, expr* channel) const;

	/**
	 * Returns 0 iff a given channel has its buffer full.
	 * EFFECTS: None.
	 */
	byte channelIsFull(unsigned int procOffset, expr* channelVar) const;
	
	process* getProc(int pid) const; // Returns the stateMask with pid 'pid'.

	void setSymOffset(const varSymNode* varSym, unsigned int preOffset);

	void initSym(unsigned int preOffset, const varSymNode* sym);

	void initSymTab(unsigned int preOffset, const symTable* symTab);

	void initGlobalVariables(void);

	void initVariables(const process* mask);
	/*
	* Gets the symbol table of a channel by giving its offset in the memory chunk.
	* The structure contained in state->chanRefs is used to get the table.
	* If no channel exists at the given offset, returns NULL.
	*/
	const chanSymNode* getChannelSymTab(unsigned int chanOffset) const;

	void removeChannelRefs(unsigned int infBound, unsigned int supBound);

	// Access and modification of large state chunks
	/*
	* Creates a new process and returns its pid.
	* Reserves some memory for the proctype variables in the memory chunk and initializes the value of these variables.
	* Does not change the payloadHash.
	*/
	int addProctype(const procSymNode* proctype);

	/*
	* Defines the never claim of the execution.
	* Set its initial FSM node in the payload.
	* Does not change the payloadHash.
	*/
	void addNever(const neverSymNode* neverSym);

	/*
	* If the pid of the last process is 'pid' then:
	*  - the stateMask of the process is removed
	*  - the number of processes in the states updated
	*  - the chunk of memory of the process is removed from the state's payload.
	* Does not change the payloadHash.
	*/
	void killProctype(int pid);

	void clean(void); // Applies stateKillProctype while this latter function succeeds.

	// State printing
	void printState(const state* diffState) const;

	void printPayload(void) const;

	// State comparison. Returns:
	#define STATES_DIFF 0				// if s1 and s2 are totally different states, meaning s1 is fresh.
	#define STATES_SAME_S1_VISITED 1	// if s1 and s2 are identical but s2 is reachable by more products; hence, s1 adds nothing new
	#define STATES_SAME_S1_FRESH 2		// if s1 and s2 are identical but s1 has products that were not explored with s2; hence, s1 is fresh
	byte compare(const void* s2Payload) const;
	#endif
	
private:
	void addChannel(const chanSymNode* chan, const process* proc = nullptr);
	void addVariable(const varSymNode* var, const process* proc = nullptr);

public:
	const symTable* globalSymTab;
	const fsm* stateMachine;

	process* first; 	// Points to the global (first) stateMask.
	process* last; 	// Points to the last stateMask.
	process* never; 	// If f is an LTL formula to be checked, never is the stateMask conversion of ~f.
								//	Furthermore, never->node returns the current node in this FSM. Note that pid and offset have no importance here.
								//	Also, never->next is supposed to be NULL.

	channelRef* chanRefs;		// References of the channel declared in a process or as a global variable.

	int nbProcesses; 			// Number of running processes.
	int lastStepPid; 			// pid of the process that fired transition that got us into this state. (NOT part of the actual state of the system, just a helper)
	void* payload; 				// Chunk of memory containing the data.
	std::map<std::tuple<const process*, const symbol*, unsigned int>, unsigned int> varOffset;
	unsigned int payloadSize;	// Number of bytes currently allocated to payload.
	unsigned int payloadHash;	// Hash of the state, used to avoid memcmp() when comparing states on the stack.  This hash is NOT maintained by
								// by the functions that change states, it is only updated in checking.c.
};

