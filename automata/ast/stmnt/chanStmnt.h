#ifndef CHAN_STMNT_H
#define CHAN_STMNT_H

#include <iostream>

#include "stmnt.h"
#include "argExpr.h"

//E_STMNT_CHAN_RCV,	// child[0] = E_VARREF, child[1] = E_EXPR_*
class stmntChanRecv : public stmnt
{
public:
	stmntChanRecv(exprVarRef *chan, exprArgList *argList, int lineNb)
		: stmnt(astNode::E_STMNT_CHAN_RCV, lineNb)
	{
		this->chan = chan; 
		this->argList = argList; 

		this->chan->setParent(this); 
		this->argList->setParent(this);
	}
	
	~stmntChanRecv() override {
		delete chan;
		delete argList;
		if(next)
			delete next;
	}

	operator std::string() const override
	{
		return std::string(*chan) + "?" + ( argList? std::string(*argList) : "") + ";\n" 
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override
	{
		return "Channel receive (E_STMNT_CHAN_RCV)";
	}

	unsigned int assignMutables(const Mask& mask = Mask(), unsigned int id = 0) override {
		if(mask.isPresent(type))
			id = chan->assignMutables(mask, id);
			id = argList->assignMutables(mask, id);
		return (next? next->assignMutables(mask, id) : id);
	}

	void mutateMutable(unsigned int id) override {

		if(chan->getMId() == id) {
			auto mutations = chan->getMutations();
			assert(mutations.size());
			delete chan;
			chan = static_cast<exprVarRef*>(mutations[rand() % mutations.size()]); 
			return;
		}

		if(argList->getMId() == id) {
			auto mutations = argList->getMutations();
			assert(mutations.size());
			delete argList;
			argList = static_cast<exprArgList*>(mutations[rand() % mutations.size()]); 
			return;
		}

		chan->mutateMutable(id);
		argList->mutateMutable(id);		

	}

	stmnt* deepCopy(void) const {
		stmntChanRecv* copy = new stmntChanRecv(*this);
		copy->prev = copy;
		copy->chan = static_cast<exprVarRef*>(chan->deepCopy());
		copy->argList = static_cast<exprArgList*>(argList->deepCopy());

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	exprVarRef* chan;
	exprArgList* argList;
};

//E_STMNT_CHAN_SND,	// child[0] = E_VARREF, child[1] = E_EXPR_*
class stmntChanSnd : public stmnt
{
public:
	stmntChanSnd(exprVarRef *chan, exprArgList *argList, int lineNb)
		: stmnt(astNode::E_STMNT_CHAN_SND, lineNb)
	{
		this->chan = chan; 
		this->argList = argList;

		this->chan->setParent(this); 
		this->argList->setParent(this);
	}

	~stmntChanSnd() override {
		delete chan;
		delete argList;
		if(next)
			delete next;
	}

	operator std::string() const override
	{
		return std::string(*chan) + "!" + ( argList? std::string(*argList) : "") + ";\n" 
		+ (next? _tab() + std::string(*next) : "");
	}

	std::string getTypeDescr(void) const override
	{
		return "Channel send (E_STMNT_CHAN_SND)";
	}

	unsigned int assignMutables(const Mask& mask = Mask(), unsigned int id = 0) override {
		if(mask.isPresent(type))
			id = chan->assignMutables(mask, id);
			id = argList->assignMutables(mask, id);
		return (next? next->assignMutables(mask, id) : id);
	}

	void mutateMutable(unsigned int id) override {

		if(chan->getMId() == id) {
			auto mutations = chan->getMutations();
			assert(mutations.size());
			delete chan;
			chan = static_cast<exprVarRef*>(mutations[rand() % mutations.size()]); 
			return;
		}

		if(argList->getMId() == id) {
			auto mutations = argList->getMutations();
			assert(mutations.size());
			delete argList;
			argList = static_cast<exprArgList*>(mutations[rand() % mutations.size()]); 
			return;
		}

		chan->mutateMutable(id);
		argList->mutateMutable(id);		

	}

	stmnt* deepCopy(void) const {
		stmntChanSnd* copy = new stmntChanSnd(*this);
		copy->prev = copy;
		copy->chan = static_cast<exprVarRef*>(chan->deepCopy());
		copy->argList = static_cast<exprArgList*>(argList->deepCopy());

		if(next)
			return stmnt::merge(copy, next->deepCopy());
		return copy;
	}

private:
	exprVarRef* chan;
	exprArgList* argList;
};

#endif