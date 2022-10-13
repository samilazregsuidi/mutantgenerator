#include "stdlibStmnt.hpp"

stmntPrint::stmntPrint(const std::string &toPrint, exprArgList *argList, int lineNb)
		: stmnt(astNode::E_STMNT_PRINT, lineNb)
		, toPrint(toPrint)
{
    addChild("argList", argList);
}

void stmntPrint::setArgList(exprArgList* argList) {
    eraseChild("argList", argList);
}

exprArgList* stmntPrint::getArgList() const {
    return dynamic_cast<exprArgList*>(getChild("argList"));
}

stmntPrint::operator std::string() const {
    return "printf(\"" + toPrint + "\""+ (getArgList()? ", " + std::string(*getArgList()) : "") + ");\n";
}

std::string stmntPrint::getTypeDescr(void) const {
    return "Print (E_STMNT_PRINT)";
}

stmnt* stmntPrint::deepCopy(void) const {
    stmntPrint* copy = new stmntPrint(*this);
    copy->prev = copy;
    copy->copyChildren(*this);
    //if(copy->getNext())
    //	return stmnt::merge(copy, getNext()->deepCopy());
    return copy;
}

/******************************************************************************************************/

stmntPrintm::stmntPrintm(exprVarRef *varRef, int lineNb)
    : stmnt(astNode::E_STMNT_PRINTM, lineNb)
{
    assert(varRef);
    addChild("var_ref", varRef);
}

stmntPrintm::stmntPrintm(int constant, int lineNb)
    : stmnt(astNode::E_STMNT_PRINTM,  lineNb)
{
    this->constant = constant;
}

void stmntPrintm::setVarRef(exprVarRef* varRef) {
    eraseChild("var_ref", varRef);
}

exprVarRef* stmntPrintm::getVarRef() const {
    return dynamic_cast<exprVarRef*>(getChild("var_ref"));
}

stmntPrintm::operator std::string() const {
    return "printm(\""+(getVarRef() ? std::string(*getVarRef()) : std::to_string(constant)) + "\");\n";
}

std::string stmntPrintm::getTypeDescr(void) const {
    return "PrintM (E_STMNT_PRINTM)";
}

stmnt* stmntPrintm::deepCopy(void) const {
    stmntPrintm* copy = new stmntPrintm(*this);
    copy->prev = copy;
    copy->copyChildren(*this);
    //if(copy->getNext())
    //	return stmnt::merge(copy, getNext()->deepCopy());
    return copy;
}

/******************************************************************************************************/

stmntAssert::stmntAssert(expr *toAssert, int lineNb)
    : stmnt(astNode::E_STMNT_ASSERT, lineNb)
{
    assert(toAssert);
    addChild("to_assert", toAssert);
}

void stmntAssert::setToAssert(expr* toAssert) {
    eraseChild("to_assert", toAssert);
}

expr* stmntAssert::getToAssert() const {
    return dynamic_cast<expr*>(getChild("to_assert"));
}

stmntAssert::operator std::string() const {
    assert(getToAssert());
    return "assert" + std::string(*getToAssert()) + ";\n";
}

std::string stmntAssert::getTypeDescr(void) const {
    return "Assertion (E_STMNT_ASSERT)";
}

stmnt* stmntAssert::deepCopy(void) const {
    stmntAssert* copy = new stmntAssert(*this);
    copy->prev = copy;
    copy->copyChildren(*this);
    //if(copy->getNext())
    //	return stmnt::merge(copy, getNext()->deepCopy());
    return copy;
}