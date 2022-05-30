#include "variable.hpp"

#include "payload.hpp"

unsigned int padding(const varSymNode* varSym){
	switch(varSym->getType()){
		case symbol::T_BIT:
		case symbol::T_BOOL:
		case symbol::T_BYTE:
		case symbol::T_CID:
		case symbol::T_CHAN:
		case symbol::T_MTYPE:
		case symbol::T_PID:
			return 1;
		
		case symbol::T_SHORT:
			return 2;

		case symbol::T_INT:
			return 4;
		
		case symbol::T_UTYPE:
			return padding(*dynamic_cast<const utypeSymNode*>(varSym)->getUType()->getFields().cbegin());

		default:
			assert(false);
			return -1;
	}
	return -1;
}

variable::variable(payload* payLoad, size_t _offset, const varSymNode* varSym, unsigned int index)
	: symType(varSym)
	, index(index)
	, parent(nullptr)
	, offset(_offset)
	, payLoad(payLoad)
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
			printf("   %-35s = %d(mtype)\n", symType->getName(), value);
		else 	
			printf("   %-35s = %d\n", symType->getName(), value);
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
		sizeOf = 1;
		_offset += 1;
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

	for(auto msgField : varList)
		sizeOf += msgField->getSizeOf();
}

channel::channel(payload* playLoad, size_t offset, const chanSymNode* chanSym, unsigned int bound)
	: variable(payLoad, offset, chanSym, bound)
{
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