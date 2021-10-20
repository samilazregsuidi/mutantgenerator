#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <assert.h>

#include "symbol.h"

#include "naSymNode.h"
#include "bitSymNode.h"
#include "boolSymNode.h"
#include "byteSymNode.h"
#include "shortSymNode.h"
#include "intSymNode.h"
#include "unsgnSymNode.h"
#include "mtypedefSymNode.h"
#include "utypeSymNode.h"
#include "pidSymNode.h"
#include "cidSymNode.h"
#include "tdefSymNode.h"
#include "chanSymNode.h"
#include "procSymNode.h"

#include "symTable.h"



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
	this->global = false;
	this->lineNb = lineNb;
	this->memOffset = 0;
	this->memSize = 0;
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
	return global;
}

void symbol::setGlobal(bool global)
{
	this->global = global;
}

unsigned int symbol::getMemorySize(void) const
{
	return memSize;
}

symbol::operator std::string(void) const
{
	std::string res = getTypeName() + " " + getName();
	return res;
}

























