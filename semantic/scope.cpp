#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "scope.hpp"

#include "payload.hpp"
#include "variable.hpp"
#include "channel.hpp"
#include "process.hpp"

scope::scope(const std::string& name, scope* parent)
	: name(name)
	, parent(parent)
	, offset(0)
	, payLoad(nullptr)
	, rawBytes(0)
	, sizeOf(0)
{
	if(parent) {
		offset = parent->getEndOffset();
		payLoad = parent->getPayload();
		parent->addSubScope(this);
	}
}

scope::~scope() {
	for(auto var : varList)
		delete var;
	
	for(auto sub : subScopes)
		delete sub;

	if(parent)
		parent->rmSubScope(this);
}

scope* scope::deepCopy(void) const {
	auto copy = new scope(*this);
	copy->payLoad = nullptr;

	copy->subScopes.clear();
	for(auto subsc : subScopes)
		copy->addSubScope(subsc->deepCopy());

	copy->varMap.clear();
	copy->varList.clear();

	for(auto var : varList)
		copy->_addVariable(var->deepCopy());

	for(auto var : varList)
		var->assign(copy);

	return copy;
}

std::string scope::getName(void) const {
	return name;
}

void scope::setPayload(payload* newPayLoad) {
	assert(!payLoad);
	payLoad = newPayLoad;

	for(auto sub : subScopes)
		sub->setPayload(newPayLoad);
}

payload* scope::getPayload(void) const {
	return payLoad;
}

unsigned long scope::hash(void) const {
	return payLoad->hash(offset, getSizeOf());
}

size_t scope::getOffset(void) const {
	return offset;
}

size_t scope::getEndOffset(void) const {
	auto subSize = 0;
	for(auto sc : subScopes)
		subSize += sc->getSizeOf();
	return offset + sizeOf + subSize;
}

void scope::init(void) {
	if(!payLoad) {
		setPayload(new payload(getSizeOf()));
	}

	for(auto var : varList)
		var->init();

	for(auto sub : subScopes)
		sub->init();
}

void scope::addRawBytes(size_t size) {
	rawBytes += size;
	sizeOf += size;
}

void scope::_addVariable(variable* var) {
	var->sc = this;
	auto varName = var->getName();
	varMap[varName] = var;
	varList.push_back(var);
	sizeOf += var->getSizeOf();
}

std::list<variable*> scope::addVariables(const varSymNode* sym) {
	assert(sym);

	std::list<variable*> res;

	switch(sym->getType())
	{
	case symbol::T_NA:
		assert(false);
	case symbol::T_BOOL:
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i) {
			auto var = new boolVar(this, this->getEndOffset(), dynamic_cast<const boolSymNode*>(sym), i);
			_addVariable(var);
			res.push_back(var);
		}
		return res;
	}
	case symbol::T_BIT:
	case symbol::T_BYTE:
	case symbol::T_SHORT:
	case symbol::T_INT:
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i) {
			auto var = new variable(this, this->getEndOffset(), sym, i);
			_addVariable(var);
			res.push_back(var);
		}
		return res;
	}
	case symbol::T_UNSGN: 	// not supported yet
		assert(false);
	case symbol::T_MTYPE:
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i) {
			auto var = new mtypeVar(this, this->getEndOffset(), dynamic_cast<const mtypeSymNode*>(sym), i);
			_addVariable(var);
			res.push_back(var);
		}
		return res;
	}
	case symbol::T_CLOCK:	// dense time clock
	case symbol::T_MTYPE_DEF:
		assert(false);
	case symbol::T_CMTYPE:
	{
		auto var = new cmtypeVar(this, dynamic_cast<const cmtypeSymNode*>(sym));
		_addVariable(var);
		res.push_back(var);
		return res;
	}
	//case symbol::T_FEAT,
	//case symbol::T_UFEAT,
	case symbol::T_UTYPE:	// Type of variable is a user type (basically, a case symbol::T_TDEF record is being used as the type): utype points to the type record
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i) {
			auto var = new utypeVar(this, this->getEndOffset(), dynamic_cast<const utypeSymNode*>(sym), i);
			_addVariable(var);
			res.push_back(var);
		}
		return res;
	}
		// "Special" types:
	case symbol::T_CHAN:		// Channel: capacity used; children denote message fields
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i) {
			auto var = new channel(this, this->getEndOffset(), dynamic_cast<const chanSymNode*>(sym), i);
			_addVariable(var);
			res.push_back(var);
		}
		return res;
	}
	case symbol::T_CID:		// Channel reference; capacity and children are not used.
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i) {
			auto var = new CIDVar(this, this->getEndOffset(), dynamic_cast<const cidSymNode*>(sym), i);
			_addVariable(var);
			res.push_back(var);
		}
		return res;
	}
	case symbol::T_PID:
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i) {
			auto var = new PIDVar(this, this->getEndOffset(), dynamic_cast<const pidSymNode*>(sym), i);
			_addVariable(var);
			res.push_back(var);
		}
		return res;
	}
	case symbol::T_TDEF:		// Type definition: children denote fields of type
	case symbol::T_INIT:
	case symbol::T_PROC:		// ProcType: fsm field used; bound denotes the number of initially active processes
	case symbol::T_INLINE:
	case symbol::T_NEVER:	// Never claim
		assert(false);
	}
	return res;
}

std::list<variable*> scope::createVariables(const varSymNode* sym) {
	assert(sym);

	std::list<variable*> res;

	switch(sym->getType())
	{
	case symbol::T_NA:
		assert(false);
	case symbol::T_BOOL:
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i) {
			auto var = new boolVar(this, this->getEndOffset(), dynamic_cast<const boolSymNode*>(sym), i);
			res.push_back(var);
		}
		return res;
	}
	case symbol::T_BIT:
	case symbol::T_BYTE:
	case symbol::T_SHORT:
	case symbol::T_INT:
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i) {
			auto var = new variable(this, this->getEndOffset(), sym, i);
			res.push_back(var);
		}
		return res;
	}
	case symbol::T_UNSGN: 	// not supported yet
		assert(false);
	case symbol::T_MTYPE:
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i) {
			auto var = new mtypeVar(this, this->getEndOffset(), dynamic_cast<const mtypeSymNode*>(sym), i);
			res.push_back(var);
		}
		return res;
	}
	case symbol::T_CLOCK:	// dense time clock
	case symbol::T_MTYPE_DEF:
		assert(false);
	case symbol::T_CMTYPE:
	{
		auto var = new cmtypeVar(this, dynamic_cast<const cmtypeSymNode*>(sym));
		res.push_back(var);
		return res;
	}
	//case symbol::T_FEAT,
	//case symbol::T_UFEAT,
	case symbol::T_UTYPE:	// Type of variable is a user type (basically, a case symbol::T_TDEF record is being used as the type): utype points to the type record
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i) {
			auto var = new utypeVar(this, this->getEndOffset(), dynamic_cast<const utypeSymNode*>(sym), i);
			res.push_back(var);
		}
		return res;
	}
		// "Special" types:
	case symbol::T_CHAN:		// Channel: capacity used; children denote message fields
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i) {
			auto var = new channel(this, this->getEndOffset(), dynamic_cast<const chanSymNode*>(sym), i);
			res.push_back(var);
		}
		return res;
	}
	case symbol::T_CID:		// Channel reference; capacity and children are not used.
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i) {
			auto var = new CIDVar(this, this->getEndOffset(), dynamic_cast<const cidSymNode*>(sym), i);
			res.push_back(var);
		}
		return res;
	}
	case symbol::T_PID:
	{
		for(unsigned int i = 0; i < sym->getBound(); ++i) {
			auto var = new PIDVar(this, this->getEndOffset(), dynamic_cast<const pidSymNode*>(sym), i);
			res.push_back(var);
		}
		return res;
	}
	case symbol::T_TDEF:		// Type definition: children denote fields of type
	case symbol::T_INIT:
	case symbol::T_PROC:		// ProcType: fsm field used; bound denotes the number of initially active processes
	case symbol::T_INLINE:
	case symbol::T_NEVER:	// Never claim
		assert(false);
	}
	return res;
}

variable* scope::getVariable(const std::string& name) const {
	std::map<std::string, variable*>::const_iterator resIt = varMap.find(name);
	if(resIt != varMap.cend())
		return resIt->second;
	
	return parent? parent->getVariable(name) : nullptr;
}

channel* scope::getChannel(const std::string& name) const {
	
	auto var = getVariable(name);
	
	if(!var) return nullptr;

	channel* chan = nullptr;
	if(var->getType() == symbol::T_CID){
		chan = dynamic_cast<CIDVar*>(var)->getRefChannel();
		assert(chan);
	} else {
		assert(var->getType() == symbol::T_CHAN);
		chan = dynamic_cast<channel*>(var);
	}
	assert(chan);
	return chan;
}

process* scope::getProcess(const std::string& name) const {
	for(auto subSc : subScopes)
		if(subSc->getName() == name)
			return dynamic_cast<process*>(subSc);
	return nullptr;
}

std::list<process*> scope::getProcesses(void) const {
	std::list<process*> res;
	for(auto sc : subScopes){
		auto proc = dynamic_cast<process*>(sc);
		if(proc)
			res.push_back(proc);
	}
	return res;
}

std::list<variable*> scope::getVariablesList(void) const {
	return varList;
}

std::map<std::string, variable*> scope::getVariablesMap(void) const {
	return varMap;
}


size_t scope::_getSizeOf(void) const {
	size_t size = rawBytes;
	
	for(auto var : varList)
		size += var->getSizeOf();

	for(auto sub : subScopes)
		size += sub->getSizeOf();

	return size;
}

size_t scope::getSizeOf(void) const {
	//printf("%u == %u\n", _getSizeOf( ), sizeOf);
	size_t subSize = 0;
	for(auto sub : subScopes)
		subSize += sub->getSizeOf();

	auto __getSizeOf = _getSizeOf();
	assert(_getSizeOf() == sizeOf + subSize);
	return sizeOf + subSize;
}

void scope::clearVariables(void) {
	varList.clear();
	varMap.clear();

	for(auto sub : subScopes)
		sub->clearVariables();
}

void scope::rmSubScope(scope* sc) {
	subScopes.remove(sc);
}

void scope::addSubScope(scope* sc) {
	sc->parent = this;
	subScopes.push_back(sc);
}

std::list<scope*> scope::getSubScopes(void) const {
	return subScopes;
}

scope* scope::getSubScope(const std::string& name) const {
	for(auto subSc : subScopes)
		if(subSc->getName() == name)
			return subSc;
	return nullptr;
}

void scope::print(void) const {

	for(auto var : varList)
		var->print();

	for(auto sc : subScopes)
		sc->print();
}

void scope::printTexada(void) const {
	
	for(auto var : varList)
		var->printTexada();

	for(auto sc : subScopes)
		sc->printTexada();
}

void scope::printHexadecimal(void) const {
	payLoad->printHexadecimal(offset, getSizeOf());
}