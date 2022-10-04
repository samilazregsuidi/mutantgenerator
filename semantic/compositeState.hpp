#ifndef COMPOSITE_STATE_H
#define COMPOSITE_STATE_H
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

#include "state.hpp"

typedef char byte;
typedef unsigned char ubyte;

// State
class compState : public state {
public:

	compState(void); // Creates the initial state by setting all variables' value in the payload. Does not set the payloadHash.

	//state(const state& s) = default;

	compState* deepCopy(void) const;
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
	~compState() override;

	std::list<transition*> executables(void) const override;

	std::list<transition*> executables(state* state) const;

	std::list<transition*> executables(byte state_id) const;

	std::map<state*, std::list<transition*>> executablesMap(void) const;

	unsigned int getErrors(void) const;

	void addError(void);

	// Applying statements

	state* apply(const transition* trans) override;
	
	//state* applyNever(const transition* trans);

	state* getState(const std::string& name) const; // Returns the stateMask with pid 'pid'.

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
	void addState(state* s);

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
	//void print(const state* diffState) const;

	//byte compare(const state& s2) const override;

	void print(void) const override;

	void printGraphViz(unsigned long i) const override;

	void printTexada(void) const override;

	void printHexadecimal(void) const override;

	unsigned long hash(void) const override;

	bool nullstate(void) const override;

	bool endstate(void) const override;

	bool isAccepting(void) const override;

public:

	std::map<std::string, state*> subStates;

	double prob;

	const transition* trans;
};

#endif