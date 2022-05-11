#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <assert.h>
#include <limits>


#include "symbol.hpp"

#include "naSymNode.hpp"
#include "bitSymNode.hpp"
#include "boolSymNode.hpp"
#include "byteSymNode.hpp"
#include "shortSymNode.hpp"
#include "intSymNode.hpp"
#include "unsgnSymNode.hpp"
#include "mtypedefSymNode.hpp"
#include "utypeSymNode.hpp"
#include "pidSymNode.hpp"
#include "cidSymNode.hpp"
#include "tdefSymNode.hpp"
#include "chanSymNode.hpp"
#include "procSymNode.hpp"

#include "symTable.hpp"

int symbol::getUpperBound(Type type) {
	switch(type) {
		case symbol::T_BIT:
			return 1;
		case symbol::T_BYTE:
			return std::numeric_limits<char>::max();
		case symbol::T_SHORT:
			return std::numeric_limits<short>::max();
		case symbol::T_UNSGN:
			assert(false);
			return std::numeric_limits<unsigned int>::max();
		case symbol::T_INT:
			return std::numeric_limits<int>::max();
		case symbol::T_MTYPE:
			return 8;
		default:
			assert(false);
			return 0;
	}
}

int symbol::getLowerBound(Type type) {
	switch(type) {
		case symbol::T_BIT:
			return 0;
		case symbol::T_BYTE:
			return std::numeric_limits<char>::min();
		case symbol::T_SHORT:
			return std::numeric_limits<short>::min();
		case symbol::T_UNSGN:
			assert(false);
			return std::numeric_limits<unsigned int>::min();
		case symbol::T_INT:
			return std::numeric_limits<int>::min();
		case symbol::T_MTYPE:
			return 0;
		default:
			assert(false);
			return 0;
	}
}

/*
 * SYMBOL TABLE
 * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * Just creates a node with the given values.
 */
symbol::symbol(Type type, const std::string &name, int lineNb)
{
	this->parent = nullptr;
	this->type = type;
	this->name = name;
	this->lineNb = lineNb;
	//this->memOffset = 0;
	//this->memSize = 0;
	this->mask = READ_ACCESS | WRITE_ACCESS;
}

symbol::symbol(Type type, int lineNb, const std::string &sVal)
	: symbol(type, sVal, lineNb)
{
}

symbol::~symbol() {}
/**
 * Destroys a symTab and all that's linked to it (except for the utype).
 */

symbol::Type symbol::getType(void) const
{
	return type;
}

/*int symbol::getBound(void) const
{
	return bound;
}*/

void symbol::setLineNb(int line)
{
	lineNb = line;
}

int symbol::getLineNb(void) const
{
	return lineNb;
}

std::string symbol::getName(void) const
{
	return name;
}

bool symbol::isGlobal(void) const
{
	return parent->isGlobal();
}

unsigned int symbol::getSizeOf(void) const
{
	return 0;
}

bool symbol::operator < (const symbol* other) {
	return other->getLineNb() < getLineNb();
}

unsigned long symbol::getID(void) const {
	return (unsigned long)this;
}

symTable* symbol::getSymTable(void) const {
	return parent;
}

void symbol::setSymTable(symTable* parent) {
	this->parent = parent;
}

void symbol::addToMask(unsigned int mask) {
	this->mask |= mask; 
}

void symbol::setMask(unsigned int mask) {
	this->mask = mask;
}

void symbol::removeToMask(unsigned int mask) {
	this->mask -= mask;
}

unsigned int symbol::getMask(void) const {
	return mask;
}

bool symbol::castTo(const symbol* sym) const {
	sym = sym;
	return false;
}

symbol::operator std::string(void) const
{
	std::string res = getTypeName() + " " + getName();
	return res;
}

void symbol::printGraphViz(std::ofstream& file) const {
	file << "{ <" << getID() << "> " << getTypeName() << "|" << getName() << "| " << getSizeOf() << " "<< ((getTypeSize() > 1)? "bytes" : "byte") <<" | "<< (getLineNb()!=0 ? "line " + std::to_string(getLineNb()) : "predef.") << " }";
}

























