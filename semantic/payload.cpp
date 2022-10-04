#include "payload.hpp"

#include <string.h>
#include <string_view>

/*
 * ACCESS AND MODIFICATION OF VARIABLES
 * * * * * * * * * * * * * * * * * * * * * * * */

payload::payload(size_t size) 
	: ptr(nullptr)
	, size(size)
{
	ptr = reinterpret_cast<byte*>(calloc(1, size));
}

/*payload::payload(const payload& other)
	: ptr(nullptr)
	, size(other.size)
	, hash(other.hash)
{
	if(size > 0) {
		this->ptr = malloc(size);
		memcpy(ptr, other.ptr, size);
	}
}*/

payload::~payload() 
{
	if(ptr)
		free(ptr);
}


void payload::alloc(void) {
	assert(size > 0);
	if(ptr)
		free(ptr);
	ptr = reinterpret_cast<byte*>(calloc(1, size));
}

void payload::alloc(size_t size) {
	this->size = size;
	alloc();
}

void payload::reset(size_t offset, size_t _size) {
	assert(_size <= size);
	assert(offset < size);
	memset(ptr + offset, 0, (_size? _size : size - offset));
}

size_t payload::getSize(void) const {
	return size;
}

void payload::addSize(size_t add) {
	size += add;
}

unsigned long payload::hash(size_t offset, size_t end) const {
	if(end == 0)
		end = size;
	return std::hash<std::string_view>{}(std::string_view(ptr + offset, end));
}

payload* payload::copy(void) const {
	auto copy = new payload(size);
	assert(ptr && copy->ptr);
	memcpy(copy->ptr, ptr, size);
	return copy;
}

/**
 * Stores 'nb' bytes in a memory chunk, at offset 'offset'.
 * Those bytes are read from the byte array 'values'.
 * The array is not freed afterward.
 *
 * Does not change the payloadHash.
 */
/*void payload::storeValues(unsigned int offset, int nb, const byte * values) {
	byte* bytePtr = reinterpret_cast<byte*>(this->ptr);
	assert(bytePtr);
	bytePtr += offset;
	
	for(int i = 0; i < nb; i++) 
		*(bytePtr + i) = values[i];
}*/

/**
 * Reads 'nb' bytes in a memory chunk of the state,) const {
	auto old_hash = std::hash<std::string_view>{}(std::string_view(reinterpret_cast<byte*>(getPayloadPtr()), getSizeOf())); at offset 'offset', puts them in an array of byte and returns it.
 */
/*const byte* payload::readValues(unsigned int offset, int nb) const {
	byte* bytePtr = reinterpret_cast<byte*>(this->ptr);
	assert(bytePtr);
	bytePtr += offset;

	byte* values = (byte*) calloc(nb, sizeof(byte));
	for(int i = 0; i < nb; i++)
		values[i] = *(bytePtr + i);
	return values;
}*/

int payload::getValue(size_t offset, symbol::Type type) const {
	switch(type){
		case symbol::T_BIT:
		case symbol::T_BYTE:
		case symbol::T_PID:
		case symbol::T_CID:
		case symbol::T_MTYPE:
		case symbol::T_CMTYPE:
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

void payload::setValue(size_t offset, int value, symbol::Type type) {
	switch(type){
		case symbol::T_BIT:
		case symbol::T_BYTE:
		case symbol::T_PID:
		case symbol::T_CID:
		case symbol::T_MTYPE:
		//case symbol::T_CMTYPE:
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
/*void payload::initValues(size_t offset, int bytesNbr, byte value) {
	memset(reinterpret_cast<byte*>(ptr) + offset, value, bytesNbr);
}*/

bool payload::operator == (const payload& other) const {
	return size == other.size && memcmp(ptr, other.ptr, size) == 0;
}

void payload::printHexadecimal(size_t offset, size_t end) const {
	
	if(end == 0)
		end = size;

	auto hexPtr = reinterpret_cast<unsigned long*>(ptr + offset);
	auto nbHexBlocks = end / sizeof(unsigned long);
	auto restData = end % sizeof(unsigned long);
	
	printf("size = : %lu\n", end);

	for(size_t i = 0; i < nbHexBlocks; ++i, hexPtr++) {
		printf("0x%lx\n", *hexPtr);
	}

	while(restData){
		if(restData >= 4) {
			printf("0x%lx\n", *reinterpret_cast<unsigned int*>(hexPtr));
			restData -= 4;
		} else if (restData >= 2) {
			printf("0x%lx\n", *reinterpret_cast<unsigned short*>(hexPtr));
			restData -= 2;
		} else if (restData == 1) {
			printf("0x%lx\n", *reinterpret_cast<unsigned char*>(hexPtr));
			restData -= 1;
		}
	}

	printf("hash: 0x%lx\n", hash(offset, end));
	//printf("hash: 0x%lx\n", std::hash<std::string_view>{}(std::string_view(ptr + offset, end)));
}