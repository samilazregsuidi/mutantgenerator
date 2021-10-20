#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <assert.h>

#include "symTable.h"
#include "symbol.h"
#include "symTabVisitor.h"
#include "intSymNode.h"
#include "pidSymNode.h"
#include "boolSymNode.h"

symTable::symTable(const std::string& name, symTable* prev) {
	this->name = name;
	this->prev = prev;
}

symTable* symTable::createSubTable(const std::string& name) {
	symTable* neww = new symTable(name, this);
	next.push_back(neww);
	//neww->parentNameSpace = this->parentNameSpace + this->name;
	return neww;
}

symTable::~symTable() {
	for(const auto& s : syms) {
		delete s.second;
	}
	for(auto& n : next)
		delete n;
}

std::string symTable::getNameSpace(void) const {
	return name;
}

symTable* symTable::prevSymTab(void) const {
	return prev;
}

void symTable::print(int tab) const {
	
	for(const auto& s : syms) {
		for(int i = 0; i < tab; ++i)
			std::cout << "\t";
		std::cout << "[\t" << s.second->getName() << "\t;\t" << s.second->getTypeName() << "\t]\n";
	}

	for(const auto& n : next) {
		n->print(tab+1);
	}
}

symbol* symTable::lookup(const std::string& name) const {
	const auto& res = syms.find(name);
	return res == syms.cend()? nullptr : res->second;
}

std::list<symbol*> symTable::getSymbols(symbol::Type type, unsigned int mask) const {
	
	auto res = prev? prev->getSymbols(type, mask): std::list<symbol*>();

	for(auto& s : syms)
		if(s.second->getType() == type && s.second->getMask() == mask)
			res.push_back(s.second);

	return res;
}

void symTable::insert(symbol* sym) {
	assert(syms.find(sym->getName()) == syms.end());
	syms[sym->getName()] = sym;
	sym->setSymTable(this);
}

void symTable::setBlock(stmnt* block) {
	this->block = block;
}
	
stmnt* symTable::getBlock(void) const {
	return block;
}
	
void symTable::addPredefinedSym(symTable* tab) {
	symbol* predef = new intSymNode(0, "_");
	predef->setMask(symbol::WRITE_ACCESS | symbol::PREDEFINED); tab->insert(predef);
	
	predef = new intSymNode(0, "_nr_pr");
	predef->setMask(symbol::READ_ACCESS | symbol::PREDEFINED); tab->insert(predef);

	predef = new pidSymNode(0, "_pid");
	predef->setMask(symbol::READ_ACCESS | symbol::PREDEFINED); tab->insert(predef);

	predef = new pidSymNode(0, "_last");
	predef->setMask(symbol::READ_ACCESS | symbol::PREDEFINED); tab->insert(predef);

	predef = new boolSymNode(0, "np_");
	predef->setMask(symbol::READ_ACCESS | symbol::PREDEFINED); tab->insert(predef);
}

void symTable::acceptVisitor(symTabVisitor* visitor){
	visitor->visitTab(this);
}

void symTable::acceptVisitor(symTabConstVisitor* visitor) const {
	visitor->visitTab(this);
}
