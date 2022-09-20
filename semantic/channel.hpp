#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include <list>

#include "variable.hpp"

class channel : public variable {
public:
	channel(scope* sc, size_t offset, const chanSymNode* sym, unsigned int bound =  0);

	~channel() override;

	variable* deepCopy(void) const override;

	int operator = (const variable& rvalue) override;

	int operator ++ (void) override;

	int operator -- (void) override;

	int operator ++ (int) override;

	int operator -- (int) override;

	bool operator == (const variable& other) const override;

	bool operator != (const variable& other) const override;

	void send(const std::list<const variable*>& args);

	void reset(void);

	void receive(const std::list<variable*>& rargs);

	bool isRendezVous(void) const;

	bool isEmpty(void) const;

	bool isFull(void) const;

	variable* getField(unsigned int index) const;
	
	byte len(void) const;

	byte getCapacity(void) const;

	size_t _getSizeOf(void) const override;

	void print(void) const override;

	void printTexada(void) const override;

private:
	void len(byte newLen);

private:
	scope* localScope;
};

class channelField : public variable {
public:
	channelField(scope* sc, variable* parent, size_t offset, const varSymNode* sym, unsigned int fieldNumber, unsigned int messageIndex = 0, unsigned int index =  0);

	variable* deepCopy(void) const override;
};
/*
class message : public std::list<int> {
};
*/
class CIDVar : public variable {
public:
	CIDVar(scope* sc, size_t offset, const cidSymNode* sym, unsigned int bound =  0);

	variable* deepCopy(void) const override;

	channel* getRefChannel(void) const;
	
	void setRefChannel(channel* newRef);

	void assign(scope* sc) override;

private:
	channel* ref;
};

#endif