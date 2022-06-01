#include "payload.hpp"

#include <string.h>

/*
 * ACCESS AND MODIFICATION OF VARIABLES
 * * * * * * * * * * * * * * * * * * * * * * * */

payload::payload(const payload& other)
	: ptr(nullptr)
	, size(other.size)
	, hash(other.hash)
{
	if(size > 0) {
		this->ptr = malloc(size);
		memcpy(ptr, other.ptr, size);
	}
}

/**
 * Stores 'nb' bytes in a memory chunk, at offset 'offset'.
 * Those bytes are read from the byte array 'values'.
 * The array is not freed afterward.
 *
 * Does not change the payloadHash.
 */
void payload::storeValues(unsigned int offset, int nb, const byte * values) {
	byte* bytePtr = reinterpret_cast<byte*>(this->ptr);
	assert(bytePtr);
	bytePtr += offset;
	
	for(int i = 0; i < nb; i++) 
		*(bytePtr + i) = values[i];
}

/**
 * Reads 'nb' bytes in a memory chunk of the state, at offset 'offset', puts them in an array of byte and returns it.
 */
const byte* payload::readValues(unsigned int offset, int nb) const {
	byte* bytePtr = reinterpret_cast<byte*>(this->ptr);
	assert(bytePtr);
	bytePtr += offset;

	byte* values = (byte*) calloc(nb, sizeof(byte));
	for(int i = 0; i < nb; i++)
		values[i] = *(bytePtr + i);
	return values;
}

int payload::getValue(unsigned int offset, symbol::Type type) const {
	switch(type){
		case symbol::T_BIT:
		case symbol::T_BYTE:
		case symbol::T_PID:
		case symbol::T_CID:
		case symbol::T_MTYPE:
			return getValue<byte>(offset);
		case symbol::T_BOOL:
			return getValue<bool>(offset);
		case symbol::T_SHORT:
			return getValue<short>(offset);
		case symbol::T_INT:
			return getValue<int>(offset);
		default:
			assert(false);
			return -1;
	}
	assert(false);
	return -1;
}

void payload::setValue(unsigned int offset, int value, symbol::Type type) {
	switch(type){
		case symbol::T_BIT:
		case symbol::T_BYTE:
		case symbol::T_PID:
		case symbol::T_CID:
		case symbol::T_MTYPE:
			setValue<byte>(offset, value);
			return;
		case symbol::T_BOOL:
			setValue<bool>(offset, value);
			return;
		case symbol::T_SHORT:
			setValue<short>(offset, value);
			return;
		case symbol::T_INT:
			setValue<int>(offset, value);
			return;
		default:
			assert(false);
	}
	assert(false);
}

/**
 * Helper for addProctype
 *
 * Initiate the bytes stored in a given chunk of memory.
 * Offset must be counted in bytes.
 */
void payload::initValues(unsigned int offset, int bytesNbr, byte value) {
	memset(reinterpret_cast<byte*>(ptr) + offset, value, bytesNbr);
}

bool payload::operator == (const payload& other) const {
	return size == other.size && memcmp(ptr, other.ptr, size) == 0;
}