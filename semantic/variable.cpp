#include "variable.hpp"

#include <iterator>

#include "scope.hpp"
#include "payload.hpp"
#include "process.hpp"

#include "argExpr.hpp"
#include "constExpr.hpp"
#include "varExpr.hpp"

unsigned int padding(const varSymNode* varSym){
	switch(varSym->getType()){
		case symbol::T_BIT:
		case symbol::T_BOOL:
		case symbol::T_BYTE:
		case symbol::T_CHAN:
		case symbol::T_MTYPE:
		case symbol::T_PID:
			return 1;
		
		case symbol::T_SHORT:
			return 2;

		case symbol::T_CID:
		case symbol::T_INT:
			return 4;
		
		case symbol::T_UTYPE:
			return padding(*dynamic_cast<const utypeSymNode*>(varSym)->getUType()->getFields().cbegin());

		default:
			assert(false);
			return -1;
	}
	assert(false);
	return -1;
}

unsigned int variable::vidCounter = 0;

variable::variable(scope* sc, size_t _offset, const varSymNode* varSym, unsigned int index)
	: variable(sc, nullptr, _offset, varSym, index)
{}

variable::variable(scope* sc, variable* parent, size_t _offset, const varSymNode* varSym, unsigned int index)
	: sc(sc)
	, symType(varSym)
	, index(index)
	, parent(parent)
	, offset(_offset)
	, vid(++vidCounter)
	, sizeOf(0)
{
	//assert(varSym);

	//assert(varSym->getType() == symbol::T_INT || varSym->getType() == symbol::T_BIT || varSym->getType() == symbol::T_BYTE || varSym->getType() == symbol::T_SHORT);

	if(varSym) {
		name = varSym->getName();

		if(varSym->getBound() > 1)
			name += "["+std::to_string(index)+"]";

		sizeOf += varSym->getTypeSize();
	
	}

}

variable::variable(const variable& other)
	: name(other.name)
	, sc(other.sc)
	, symType(other.symType)
	, index(other.index)
	, parent(other.parent)
	, offset(other.offset)
	, vid(other.vid)
	, sizeOf(other.sizeOf)
{
}

variable* variable::deepCopy(void) const {
	variable* copy = new variable(*this);
	return copy;
}

variable::~variable() {
}

symbol::Type variable::getType(void) const {
	return symType->getType();
}

void variable::assign(scope* sc) {
	this->sc = sc;
	if(parent) {
		parent = sc->getVariable(parent->getName());
		assert(parent);
	}

	if(hasSubFields()){
		std::list<variable*> newFields;
		for(auto varSubField : getSubFields()) {
			auto field = sc->getVariable(varSubField->getName());
			assert(field);
			newFields.push_back(field);
		}
		varList = newFields;
	}
	
}

scope* variable::getScope(void) const {
	return sc;
}

void variable::init(void) {

	auto initExpr = symType->getInitExpr();

	if(initExpr) {
		auto initExprConst = dynamic_cast<exprConst*>(initExpr);
		//init expr should be const and const only!
		assert(initExprConst);
		setValue(initExprConst->getCstValue());
	}
}

int variable::operator = (const variable& rvalue) {
	int res = rvalue.getValue(); 
	setValue(res);
	return res;
}

int variable::operator ++ (void) {
	setValue(getValue()+1);
	return getValue();
}

int variable::operator -- (void) {
	setValue(getValue()-1);
	return getValue();
}

int variable::operator ++ (int) {
	auto temp = getValue();
	setValue(getValue()+1);
	return temp;
}

int variable::operator -- (int) {
	auto temp = getValue();
	setValue(getValue()-1);
	return temp;
}

bool variable::operator == (const variable& other) const {
	return getValue() == other.getValue();
}

bool variable::operator != (const variable& other) const {
	return getValue() == other.getValue();
}

void variable::setParent(const variable* parent) {
	this->parent = parent;
}

std::string variable::getName(void) const {
	return parent? parent->getName() + "." + name : name;
}

unsigned int variable::getVariableId(void) const {
	return vid;
}

void variable::addField(variable* field) {
	field->setParent(this);
	sc->_addVariable(field);
	varList.push_back(field);
	sizeOf += field->getSizeOf();
}

void variable::addPrivateField(variable* field) {
	field->setParent(this);
	//sc->_addVariable(field);
	varList.push_back(field);
	sizeOf += field->getSizeOf();
}

bool variable::hasSubFields(void) const {
	return getSubFields().size() > 0;
}

std::list<variable*> variable::getSubFields(void) const {
	return varList;
}

void variable::clearVariables(void) {
	varList.clear();
}

size_t variable::getSizeOf(void) const {
	return sizeOf;
}

size_t variable::_getSizeOf(void) const {
	return sizeOf;
}

void variable::setValue(int value) {
	assert(value >= varSymNode::getLowerBound(symType->getType()) && value <= varSymNode::getUpperBound(symType->getType()));
	sc->getPayload()->setValue(offset, value, symType->getType());
}
	
int variable::getValue(void) const {
	auto value = sc->getPayload()->getValue(offset, symType->getType());
	assert(value >= varSymNode::getLowerBound(symType->getType()) && value <= varSymNode::getUpperBound(symType->getType()));
	return value;
}

void variable::print(void) const {
	auto value = sc->getPayload()->getValue(offset, symType->getType());
	printf("0x%-4lx:   %-23s = %d\n", offset, getName().c_str(), value);
}

void variable::printTexada(void) const {
	auto value = sc->getPayload()->getValue(offset, symType->getType());
	printf("%s = %d\n", getName().c_str(), value);
}

/*************************************************************************************************/

utypeVar::utypeVar(scope* sc, variable* parent, size_t offset, const utypeSymNode* sym, unsigned int index)
	: variable(sc, parent, offset, sym, index)
{
	for(auto field : sym->getUType()->getFields()) {
		for(auto var : sc->createVariables(field)) {
			addField(var);
		}
	}
}

utypeVar::utypeVar(scope* sc, size_t offset, const utypeSymNode* sym, unsigned int index)
	: utypeVar(sc, nullptr, offset, sym, index)
{}

int utypeVar::operator = (const variable& rvalue) {
	assert(false);
}

int utypeVar::operator ++ (void) {
	assert(false);
}

int utypeVar::operator -- (void) {
	assert(false);
}

int utypeVar::operator ++ (int) {
	assert(false);
}

int utypeVar::operator -- (int) {
	assert(false);
}

bool utypeVar::operator == (const variable& other) const {
	assert(false);
}

bool utypeVar::operator != (const variable& other) const {
	assert(false);
}

variable* utypeVar::deepCopy(void) const {
	utypeVar* copy = new utypeVar(*this);
	//warning shared payload! 
	return copy;
}

void utypeVar::print(void) const {

}

void utypeVar::printTexada(void) const {
}

/*************************************************************************************************/

boolVar::boolVar(scope* sc, size_t offset, const boolSymNode* sym, unsigned int index)
	: boolVar(sc, nullptr, offset, sym, index)
{}

boolVar::boolVar(scope* sc, variable* parent, size_t offset, const boolSymNode* sym, unsigned int index)
	: variable(sc, parent, offset, sym, index)
{}

variable* boolVar::deepCopy(void) const {
	return new boolVar(*this);
}

int boolVar::operator ++ (void) {
	assert(false);
}

int boolVar::operator -- (void) {
	assert(false);
}

int boolVar::operator ++ (int) {
	assert(false);
}

int boolVar::operator -- (int) {
	assert(false);
}

void boolVar::print(void) const {
	
	if(getValue() == 1)
		printf("0x%-4lx:   %-23s = true\n", offset, getName().c_str());
	else
		printf("0x%-4lx:   %-23s = false\n", offset, getName().c_str());
}

void boolVar::printTexada(void) const {
	
	if(getValue() == 1)
		printf("%s = true\n", getName().c_str());
	else
		printf("%s = false\n", getName().c_str());
}

/************************************************************************************************/

constVar::constVar(int value, symbol::Type type, int lineNb)
	: variable(nullptr, 0, nullptr)
	, value(value)
	, type(type)
	, lineNb(lineNb)
{
	assert(false);//sizeOf += 
}

symbol::Type constVar::getType(void) const {
	return type;
}

void constVar::setValue(int value) {
	assert(false);
}

int constVar::getValue(void) const {
	return value;
}

int constVar::operator = (const variable& rvalue) {
	assert(false);
}

int constVar::operator ++ (void) {
	assert(false);
}

int constVar::operator -- (void) {
	assert(false);
}

int constVar::operator ++ (int) {
	assert(false);
}

int constVar::operator -- (int) {
	assert(false);
}

variable* constVar::deepCopy(void) const {
	constVar* copy = new constVar(*this);
	//warning shared payload! 
	return copy;
}

/******************************************************************************************************/

mtypeVar::mtypeVar(scope* sc, variable* parent, size_t offset, const mtypeSymNode* sym, unsigned int index)
	: variable(sc, parent, offset, sym, index)
{}

mtypeVar::mtypeVar(scope* sc, size_t offset, const mtypeSymNode* sym, unsigned int index) 
	: mtypeVar(sc, nullptr, offset, sym, index)
{}


void mtypeVar::init(void) {

	auto initExpr = symType->getInitExpr();

	if(initExpr) {
		
		//its a cmtype value...
		assert(initExpr->getType() == astNode::E_EXPR_VAR);

		auto sym = dynamic_cast<exprVar*>(initExpr)->getFinalSymbol();
		assert(sym && sym->getType() == symbol::T_CMTYPE);

		setValue(dynamic_cast<const cmtypeSymNode*>(sym)->getIntValue());
	}
}


int mtypeVar::operator ++ (void) {
	assert(false);
}

int mtypeVar::operator -- (void) {
	assert(false);
}

int mtypeVar::operator ++ (int) {
	assert(false);
}

int mtypeVar::operator -- (int) {
	assert(false);
}

variable* mtypeVar::deepCopy(void) const {
	mtypeVar* copy = new mtypeVar(*this);
	//warning shared payload! 
	return copy;
}

void mtypeVar::print(void) const {
	auto value = getValue();
	if(value) {
		auto def = dynamic_cast<const mtypeSymNode*>(symType)->getMTypeDef();
		auto mtypestr = def->getCmtypeSymNodeName(value);
		printf("0x%-4lx:   %-23s = %s\n", offset, getName().c_str(), mtypestr.c_str());
	} else {
		printf("0x%-4lx:   %-23s = nil\n", offset, getName().c_str());
	}
}

void mtypeVar::printTexada(void) const {
	auto value = getValue();
	if(value) {
		auto def = dynamic_cast<const mtypeSymNode*>(symType)->getMTypeDef();
		auto mtypestr = def->getCmtypeSymNodeName(value);
		printf("%s = %s\n", getName().c_str(), mtypestr.c_str());
	} else {
		printf("%s = nil\n", getName().c_str());
	}
}

/******************************************************************************************************/

cmtypeVar::cmtypeVar(scope* sc, const cmtypeSymNode* sym) 
	: variable(sc, 0, sym)
{}

void cmtypeVar::setValue(int value) {
	assert(false);
}
	
int cmtypeVar::getValue(void) const {
	return dynamic_cast<const cmtypeSymNode*>(symType)->getIntValue();
}

variable* cmtypeVar::deepCopy(void) const {
	cmtypeVar* copy = new cmtypeVar(*this);
	//warning shared payload! 
	return copy;
}

int cmtypeVar::operator = (const variable& rvalue) {
	assert(false);
}

int cmtypeVar::operator ++ (void) {
	assert(false);
}

int cmtypeVar::operator -- (void) {
	assert(false);
}

int cmtypeVar::operator ++ (int) {
	assert(false);
}

int cmtypeVar::operator -- (int) {
	assert(false);
}

void cmtypeVar::print(void) const {
	//assert(false);
}

void cmtypeVar::printTexada(void) const {
}

/******************************************************************************************************/

PIDVar::PIDVar(scope* sc, size_t offset, const pidSymNode* sym, unsigned int bound) 
	: variable(sc, offset, sym, bound)
	, ref(nullptr)
{}

variable* PIDVar::deepCopy(void) const{
	variable* copy = new PIDVar(*this);
	return copy;
}

process* PIDVar::getRefProcess(void) const {
	return ref;
}
	
void PIDVar::setRefProcess(process* newRef) {
	ref = newRef;
	sc->getPayload()->setValue<byte>(offset, newRef->getPid());
}

void PIDVar::assign(scope* sc) {
	variable::assign(sc);
	if(ref) {
		ref = dynamic_cast<process*>(sc->getVariable(ref->getName()));
		assert(ref);
	}
}
