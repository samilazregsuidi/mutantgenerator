#include "channel.hpp"

#include "scope.hpp"
#include "payload.hpp"

channel::channel(scope* sc, size_t _offset, const chanSymNode* chanSym, unsigned int index)
	: variable(sc, _offset, chanSym, index)
{
	if(chanSym->getBound() > 1)
		name += "["+std::to_string(index)+"]";

	if(chanSym->getCapacity() > 0) {
		sizeOf += 1;

		for(int i = 0; i < chanSym->getCapacity(); ++i){
			unsigned int fieldIndex = 0;
			for(auto typeSym: chanSym->getTypeList()){
				for(unsigned int j = 0; j < typeSym->getBound(); ++j){
					auto msgField = new channelField(sc, this, sizeOf, typeSym, fieldIndex++, i, j);
					addField(msgField);
					sizeOf += msgField->getSizeOf();
				}
			}
		}

	} else {
		_offset = 0;
		//rendez channel have their own local scope to exchange variables 
		localScope = new scope(name);

		unsigned int fieldIndex = 0;
		for(auto typeSym: chanSym->getTypeList()){
			for(unsigned int j = 0; j < typeSym->getBound(); ++j){
				auto field = new channelField(localScope, this, sizeOf, typeSym, fieldIndex++, 0, j);
				addPrivateField(field);
				localScope->_addVariable(field);
			}
		}
		
		localScope->init();
	}		
}

channel::channel(const channel& other) 
	: variable(other)
{}

variable* channel::deepCopy(void) const{
	variable* copy = new channel(*this);
	return copy;
}

channel::~channel() {
	if(isRendezVous()) {
		delete localScope;
	}
}

void channel::reset(void) {
	if(isRendezVous())
		localScope->getPayload()->reset();
	else
		sc->getPayload()->reset();
}

//int return type for executability check?
void channel::send(const std::list<const variable*>& args) {
	
	auto argIt = args.cbegin();

	for(auto field : varList) {
		
		//field->print();
		//(*argIt)->print();

		*field = **argIt++;

		//field->print();
	
	}

	if(!isRendezVous())
		len(len()+1);
}

void channel::receive(const std::list<variable*>& rargs) {

	auto rargIt = rargs.begin();

	for(auto field : varList) {
		
		//(*rargIt)->print();
		//field->print();

		**rargIt++ = *field;
	}

	if(isRendezVous())
		reset();
	else 
		len(len()-1);
	
}

variable* channel::getField(unsigned int index) const {
	assert(0 < index && index < varList.size());
	auto it = varList.begin();
	std::advance(it, index);
	return *it;
}

bool channel::isRendezVous(void) const {
	return getCapacity() == 0;
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
	return sc->getPayload()->getValue<byte>(offset);
}

void channel::len(byte newLen) {
	if(!isRendezVous()) {
		assert(newLen < getCapacity());
		sc->getPayload()->setValue<byte>(offset, newLen);
	}
}

byte channel::getCapacity(void) const {
	return dynamic_cast<const chanSymNode*>(symType)->getCapacity();
}

size_t channel::_getSizeOf(void) const {
	return isRendezVous()? 0 : 1 + sizeOf;
}

int channel::operator = (const variable& rvalue) {
	assert(false);
}

int channel::operator ++ (void) {
	assert(false);
}

int channel::operator -- (void) {
	assert(false);
}

int channel::operator ++ (int) {
	assert(false);
}

int channel::operator -- (int) {
	assert(false);
}

bool channel::operator == (const variable& other) const {
	assert(false);
}

bool channel::operator != (const variable& other) const {
	assert(false);
}

void channel::print(void) const {

}

/**************************************************************************************************/

channelField::channelField(scope* sc, variable* parent, size_t offset, const varSymNode* sym, unsigned int fieldNumber, unsigned int messageIndex, unsigned int index)
	: variable(sc, parent, offset, sym, index)
{
	name = ".("+sym->getTypeName()+")m" + std::to_string(messageIndex) + ".f" + std::to_string(fieldNumber) + name;
}

channelField::channelField(const channelField& other) 
	: variable(other)
{}

variable* channelField::deepCopy(void) const{
	variable* copy = new channelField(*this);
	return copy;
}

/**************************************************************************************************/

CIDVar::CIDVar(scope* sc, size_t offset, const cidSymNode* sym, unsigned int bound) 
	: variable(sc, offset, sym, bound)
	, ref(nullptr)
{}

CIDVar::CIDVar(const CIDVar& other) 
	: variable(other)
	, ref(other.ref)
{}

variable* CIDVar::deepCopy(void) const{
	variable* copy = new CIDVar(*this);
	return copy;
}

channel* CIDVar::getRefChannel(void) const {
	return ref;
}
	
void CIDVar::setRefChannel(channel* newRef) {
	ref = newRef;
	sc->getPayload()->setValue<channel*>(offset, newRef);
}

