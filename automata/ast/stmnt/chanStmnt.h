#ifndef CHAN_STMNT_H
#define CHAN_STMNT_H

#include <iostream>

#include "stmnt.h"
#include "argExpr.h"

class stmntChan : public stmnt 
{
protected:
	stmntChan(Type type, exprVarRef *chan, exprArgList *argList, int lineNb)
		: stmnt(type, lineNb)
	{
		setChan(chan);
		setArgList(argList);
	}

public:	
	void setChan(exprVarRef* chan) {
		rmChild(this->chan);
		addChild(chan);
		this->chan = chan;
	}

	void setArgList(exprArgList* argList) {
		rmChild(this->argList);
		addChild(argList);
		this->argList = argList;
	}

	unsigned int assignMutables(const Mask& mask = Mask(), unsigned int id = 0) override {
		if(mask.isPresent(type))
			id = chan->assignMutables(mask, id);
			id = argList->assignMutables(mask, id);
		return (next? next->assignMutables(mask, id) : id);
	}

	bool mutateMutable(unsigned int id) override {

		if(chan->getMId() == id) {
			auto mutations = chan->getMutations();
			assert(mutations.size());
			setChan(static_cast<exprVarRef*>(mutations[rand() % mutations.size()]));
			return true;
		}

		if(argList->getMId() == id) {
			auto mutations = argList->getMutations();
			assert(mutations.size());
			setArgList(static_cast<exprArgList*>(mutations[rand() % mutations.size()]));
			return true;
		}

		return false;

	}

protected:
	exprVarRef* chan;
	exprArgList* argList;
};

//E_STMNT_CHAN_RCV,	// child[0] = E_VARREF, child[1] = E_EXPR_*
class stmntChanRecv : public stmntChan
{
public:
	stmntChanRecv(exprVarRef *chan, exprArgList *argList, int lineNb)
		: stmntChan(astNode::E_STMNT_CHAN_RCV, chan, argList, lineNb)
	{}

	operator std::string() const override {
		return std::string(*chan) + "?" + ( argList? std::string(*argList) : "") + ";\n";
	}

	std::string getTypeDescr(void) const override {
		return "Channel receive (E_STMNT_CHAN_RCV)";
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
};

//E_STMNT_CHAN_SND,	// child[0] = E_VARREF, child[1] = E_EXPR_*
class stmntChanSnd : public stmntChan
{
public:
	stmntChanSnd(exprVarRef *chan, exprArgList *argList, int lineNb)
		: stmntChan(astNode::E_STMNT_CHAN_SND, chan, argList, lineNb)
	{}

	operator std::string() const override {
		return std::string(*chan) + "!" + ( argList? std::string(*argList) : "") + ";\n";
	}

	std::string getTypeDescr(void) const override {
		return "Channel send (E_STMNT_CHAN_SND)";
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
};

#endif