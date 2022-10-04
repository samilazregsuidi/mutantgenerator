#ifndef PAYLOAD_H
#define PAYLOAD_H

#include "symbols.hpp"

typedef char byte;
typedef unsigned char ubyte;

class process;

//never return the real payload ptr

class payload {

public:
	payload(void);

	payload(size_t size);

	//payload(const payload& other);

	~payload();

	void setSize(size_t size);

	void addSize(size_t size);

	size_t getSize(void) const;

	void alloc(void);

	void alloc(size_t size);

	void reset(size_t offset = 0, size_t end = 0);

	payload* copy(void) const;

	unsigned long hash(size_t offset = 0, size_t end = 0) const;

	/*
	* Returns the offset of the variable referenced by 'expression' in 'process' and 'state'.
	* Parameters:
	*    - 'state' is necessary to evaluate the index of an array expression.
	*    - process is the environment in which the variable is ANALYZED, NOT in the one the variable is DEFINED.
	*    - On first call, preOffset must have the same value as the offset of its environment (i.e. global or process).
	*/
	//size_t getVarOffset(const process* varProc, const expr* varExpr) const;

	/*
	* Reads 'nb' bytes in a memory chunk of the state, at offset 'offset', puts them in an array of byte and returns it.
	*/
	//const byte* readValues(unsigned int offset, int nb) const;

	/*
	* Stores 'nb' bytes in a memory chunk, at offset 'offset'.
	* Those bytes are read from the byte array 'values'.
	* The array is not freed afterward.
	*
	* Does not change the payloadHash.
	*/
	//void storeValues(unsigned int offset, int nb, const byte* values);

	// Returns the value stored in 'chunk' at offset 'offset'. The number of read bytes depends on 'type'.
	/*
	* Gets the value of ONE cells in a memory chunk of the state.
	*/
	template <typename T> T getValue(size_t offset) const {
		T* tPtr = (reinterpret_cast<T*>(ptr + offset));
		assert(tPtr);
		return *tPtr;
	}

	template <typename T> T& getValue(size_t offset) {
		T* tPtr = (reinterpret_cast<T*>(ptr + offset));
		assert(tPtr);
		return *tPtr;
	}

	//int& getValue(unsigned int offset, symbol::Type type);

	int getValue(size_t offset, symbol::Type type) const;
	
	// Set the value stored in 'chunk' at offset 'offset' to 'value'. The number of read bytes depends on 'type'.
	
	
	/**
	 * Sets the value of ONE cells in the memory chunk.
	 *
	 * Does not change the payloadHash.
	 */
	template <typename T> void setValue(size_t offset, const T& value) {
		T* tPtr = (reinterpret_cast<T*>(ptr + offset));
		assert(tPtr);
		*tPtr = value;
	}

	void setValue(size_t offset, int value, symbol::Type type);

	//void initValues(unsigned int offset, int bytesNbr, byte value);

	bool operator == (const payload& other) const;

	void printHexadecimal(size_t offset = 0, size_t end = 0) const;

private:
	byte* ptr;
	size_t size;
};

#endif