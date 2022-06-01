#include "variable.hpp"

#include "payload.hpp"
#include "process.hpp"
#include "argExpr.hpp"

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

variable::variable(payload* payLoad, size_t _offset, const varSymNode* varSym, unsigned int index)
	: symType(varSym)
	, index(index)
	, parent(nullptr)
	, offset(_offset)
	, payLoad(payLoad)
	, vid(++vidCounter)
	, sizeOf(0)
{
	assert(varSym);

	name = varSym->getName();

	if(varSym->getBound() > 1)
		name += "["+std::to_string(index)+"]";

	unsigned int pad = _offset % padding(varSym);
	offset = _offset + pad;
	sizeOf += pad;
		
	if(varSym->getType() == symbol::T_UTYPE){
		auto utype = dynamic_cast<const utypeSymNode*>(varSym)->getUType();
		for(auto field : utype->getFields()) {
			for(int i = 0; i < field->getBound(); ++i) {
				auto sub_var = new variable(payLoad, _offset, field, i);
				_offset += sub_var->getSizeOf();
				this->addVar(sub_var);
				sizeOf += sub_var->getSizeOf();
			}
		}
		
	} else 
		sizeOf += varSym->getTypeSize();
}

void variable::init(void) {

	auto initExpr = symType->getInitExpr();

	if(initExpr)
		payLoad->setValue(offset, dynamic_cast<exprConst*>(initExpr)->getCstValue, symType->getType());

	for(auto var : varList)
		var->init();

}

std::string variable::getName(void) const {
	return parent? parent->getName() + "." + name : name;
}

void variable::addVar(variable* field) {
	field->setParent(this);
	varMap[field->getName()] = field;
	varList.push_back(field);
}

void variable::print(void) const {
		
	if(symType->getType() != symbol::T_UTYPE){
		auto value = payLoad->getValue(offset, symType->getType());

		if(symType->getType() == symbol::T_MTYPE) 
			printf("   %-35s = %d(mtype)\n", getName(), value);
		else 	
			printf("   %-35s = %d\n", getName(), value);
	}

	for(auto var : varList)
		var->print();
}

/*************************************************************************************************/

channel::channel(payload* payLoad, size_t _offset, const chanSymNode* chanSym, unsigned int index)
	: variable(payLoad, _offset, chanSym, index)
{
	if(chanSym->getBound() > 1)
		name += "["+std::to_string(index)+"]";

	if(chanSym->getCapacity() != 0) {
		sizeOf += 1;
		_offset += 1;
	} else {
		payLoad = new payload();
	}

	for(int i = 0; i < chanSym->getCapacity(); ++i){
		unsigned int fieldIndex = 0;
		for(auto typeSym: chanSym->getTypeList()){
			for(auto j = 0; j < typeSym->getBound(); ++j){
				auto msgField = new messageField(payLoad, _offset, typeSym, fieldIndex++, i, j);
				addVar(msgField);
				_offset += msgField->getSizeOf();
			}
		}
	}

	if(chanSym->getCapacity() > 0)
		for(auto msgField : varList)
			sizeOf += msgField->getSizeOf();
}

channel::channel(payload* playLoad, size_t offset, const chanSymNode* chanSym, unsigned int bound)
	: variable(payLoad, offset, chanSym, bound ) 
{}

channel::~channel() {
	if(isRendezVous())
		delete payLoad;
}



void channel::send(const std::list<const variable*>& args) {
	
	auto argIt = args.cbegin();

	for(auto field : varList) {

		field->setValue((*argIt)->getValue());
		
		argIt++;
	}

	len(len()+1);
}

void channel::receive(const std::list<variable*>& args) {

	auto argIt = args.begin();

	for(auto field : varList) {

		(*argIt)->setValue(field->getValue());
		
		argIt++;
	}

	len(len()-1);
}

variable* channel::getField(unsigned int index) const {
	assert(0 < index && index < varList.size());
	return std::advance(varList.begin(), index);
}

bool channel::isRendezVous(void) const {
	getCapacity() == 0;
}

bool channel::isFull(void) const {
	return len() == getCapacity();
}

bool channel::isEmpty(void) const {
	return len() == 0;
}

byte channel::len(void) const {
	if(isRendezVous())
		return 0;
	return payLoad->getValue<byte>(offset);
}

void channel::len(byte newLen) const {
	if(!isRendezVous()) {
		assert(newLen < getCapacity());
		payLoad->setValue<byte>(offset, newLen);
	}
}

byte channel::getCapacity(void) const {
	return dynamic_cast<const chanSymNode*>(symType)->getCapacity());
}

void channel::print(void) const {
	
	for(auto msgField : varList)
		msgField->print();
}

/**************************************************************************************************/

messageField::messageField(payload* playLoad, size_t offset, const varSymNode* sym, unsigned int fieldNumber, unsigned int messageIndex, unsigned int index)
	: variable(payLoad, offset, sym, index)
{
	name = ".("+sym->getTypeName()+")m" + std::to_string(messageIndex) + ".f" + std::to_string(fieldNumber) + name;
}

/**************************************************************************************************/

CIDVariable::CIDVariable(payload* playLoad, size_t offset, const varSymNode* sym, unsigned int bound =  0) 
	: variable(payLoad, offset, sym, bound)
{}

channel* CIDVariable::getRefChannel(void) const {
	return ref;
}
	
void CIDVariable::setRefChannel(channel* newRef) const {
	ref = newRef;
	payload->setValue<channel*>(offset, newRef);
}

/******************************************************************************************************/

PIDVariable::PIDVariable(payload* playLoad, size_t offset, const varSymNode* sym, unsigned int bound =  0) 
	: variable(payLoad, offset, sym, bound)
{}

process* PIDVariable::getRefProcess(void) const {
	return ref;
}
	
void PIDVariable::setRefProcess(process* newRef) const {
	ref = newRef;
	payload->setValue(offset, newRef->getPid(), sym->getType());
}

