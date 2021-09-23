#include "mTypeList.h"

#include <cassert>

/*
 * MTYPES
 * * * * * * * * * * * * * * * * * * * * * * * */

mTypeList::mTypeList(const std::string &name)
{

	this->name = name;
	this->next = nullptr;
	this->prev = this;
}

mTypeList *mTypeList::addMType(const std::string &name)
{

	mTypeList *newNode = new mTypeList(name);
	newNode->value = this->prev->value + 1;
	newNode->prev = this->prev;
	this->prev->next = newNode;
	this->prev = newNode;
	return newNode;
}

/**
 * Adds an MType to the list (automatically assigns it a value).
 */

/**
 * Gets the value of an MType based on the name.
 * If the MType does not exist, it will return -1.
 */
int mTypeList::getMTypeValue(const std::string &name) const
{

	if (name == getName())
		return value;
	else if (this->next)
		return next->getMTypeValue(name);
	else
		return -1;
}

/**
 * Gets the name of the MType based on its value.
 * If the value does not exist, it will return NULL.
 */
std::string mTypeList::getMTypeName(int value) const
{
	const mTypeList *it = this;
	if (this->value == value)
		return name;

	if (prev && this->value < prev->value / 2)
	{
		while ((it = it->next))
			if (it->value == value)
				return it->getName();
	}
	else
	{
		while ((it = it->prev))
			if (it->value == value)
				return it->getName();
	}
	assert(false);
	return std::string();
}

/**
 * Prints a list of MTypes to stdout.
 */
void mTypeList::printMTypes()
{
	printf("MTypes:");
	mTypeList *it = this;
	while (it != nullptr)
	{
		printf(" %s (%d)", it->getName().c_str(), it->value);
		it = it->next;
	}
	printf("\n");
}

std::string mTypeList::getName(void) const
{
	return name;
}