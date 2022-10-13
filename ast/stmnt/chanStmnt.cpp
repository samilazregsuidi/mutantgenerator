#include "chanStmnt.hpp"

stmntChan::stmntChan(Type type, exprVarRef *chan, int lineNb)
    : stmnt(type, lineNb)
{
    assert(chan);
    addChild("chan", chan);
}

void stmntChan::setChan(exprVarRef* chan) {
    eraseChild("chan", chan);
}

exprVarRef* stmntChan::getChan() const {
    return dynamic_cast<exprVarRef*>(getChild("chan"));
}

/**********************************************************************/

stmntChanRecv::stmntChanRecv(exprVarRef *chan, exprRArgList *argList, int lineNb)
		: stmntChan(astNode::E_STMNT_CHAN_RCV, chan, lineNb)
{
    assert(argList);
    addChild("r_arg_list", argList);
}

void stmntChanRecv::setRArgList(exprRArgList* argList) {
    eraseChild("r_arg_list", argList);
}

exprRArgList* stmntChanRecv::getRArgList() const {
    exprRArgList* test = dynamic_cast<exprRArgList*>(getChild("r_arg_list"));
    assert(test);
    return dynamic_cast<exprRArgList*>(getChild("r_arg_list"));
}

stmntChanRecv::operator std::string() const {
    assert(getRArgList());
    return std::string(*getChan()) + "?" + ( getRArgList()? std::string(*getRArgList()) : "") + ";\n";
}

std::string stmntChanRecv::getTypeDescr(void) const {
    return "Channel receive (E_STMNT_CHAN_RCV)";
}

stmnt* stmntChanRecv::deepCopy(void) const {
    stmntChanRecv* copy = new stmntChanRecv(*this);
    copy->prev = copy;
    copy->copyChildren(*this);
    //if(copy->getNext())
    //	return stmnt::merge(copy, getNext()->deepCopy());
    return copy;
}

/*************************************************************************************/

stmntChanSnd::stmntChanSnd(exprVarRef *chan, exprArgList *argList, int lineNb)
    : stmntChan(astNode::E_STMNT_CHAN_SND, chan, lineNb)
{
    assert(argList);
    addChild("arg_list", argList);
}

void stmntChanSnd::setArgList(exprArgList* argList) {
    eraseChild("arg_list", argList);
}

exprArgList* stmntChanSnd::getArgList() const {
    exprArgList* test = dynamic_cast<exprArgList*>(getChild("arg_list"));
    assert(test);
    return dynamic_cast<exprArgList*>(getChild("arg_list"));
}

stmntChanSnd::operator std::string() const {
    assert(getArgList());
    return std::string(*getChan()) + "!" + ( getArgList()? std::string(*getArgList()) : "") + ";\n";
}

std::string stmntChanSnd::getTypeDescr(void) const {
    return "Channel send (E_STMNT_CHAN_SND)";
}

stmnt* stmntChanSnd::deepCopy(void) const {
    stmntChanSnd* copy = new stmntChanSnd(*this);
    copy->prev = copy;
    copy->copyChildren(*this);
    //if(copy->getNext())
    //	return stmnt::merge(copy, getNext()->deepCopy());
    return copy;
}