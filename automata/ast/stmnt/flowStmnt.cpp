#include "flowStmnt.hpp"

#include "astVisitor.hpp"

stmntOpt::stmntOpt(stmnt* block, stmntOpt *nextOpt, int lineNb)
		: stmnt(astNode::E_STMNT_OPT, lineNb)
{
    assert(block);
    assert(nextOpt);
    addChild("block", block);
    addChild("next_opt", nextOpt);

    //std::cout << "OPT $1 $2 : line " << lineNb << " _ " << std::string(*this) << "\n";
}

stmntOpt::stmntOpt(stmnt* block, int lineNb)
    : stmnt(astNode::E_STMNT_OPT, lineNb)
{
    assert(block);
    addChild("block", block);

    //std::cout << "OPT $1 : line " << lineNb << " _ " << std::string(*this) << "\n";
}

void stmntOpt::setBlock(stmnt* block) {
    eraseChild("block", block);
}

stmnt* stmntOpt::getBlock() const {
    return dynamic_cast<stmnt*>(getChild("block"));
}

void stmntOpt::setNextOpt(stmntOpt* nextOpt) {
    eraseChild("next_opt", nextOpt);
}

stmntOpt* stmntOpt::getNextOpt() const {
    return dynamic_cast<stmntOpt*>(getChild("next_opt"));
}

stmntOpt::operator std::string() const {
    assert(getBlock());
    std::string res = _tab(-1) + "::\t" + std::string(*getBlock());

    auto cur = getBlock()->getNext();
    while(cur) {
        res += _tab() + std::string(*cur);
        cur = cur->getNext();
    }
    
    return res + (getNextOpt()? std::string(*getNextOpt()) : "");
}

std::string stmntOpt::getTypeDescr(void) const {
    return "Opt (E_STMNT_OPT)";
}

stmnt* stmntOpt::deepCopy(void) const {
    stmntOpt* copy = new stmntOpt(*this);
    copy->prev = copy;
    copy->copyChildren(*this);
    //if(copy->getNext())
    //	return stmnt::merge(copy, getNext()->deepCopy());
    return copy;
}

void stmntOpt::acceptVisitor(ASTConstVisitor* visitor) const {
	visitor->visit(this);
}

void stmntOpt::acceptVisitor(ASTVisitor* visitor) {
	visitor->visit(this);
}


/*****************************************************************************/

stmntFlow::stmntFlow(Type type, stmntOpt* opts, int lineNb)
		: stmnt(type, lineNb)
{
    assert(opts);
    addChild("opts", opts);
}

void stmntFlow::setOpts(stmntOpt* opts) {
    eraseChild("opts", opts);
}

stmntOpt* stmntFlow::getOpts() const {
    return dynamic_cast<stmntOpt*>(getChild("opts"));
}

/******************************************************************************/

stmntIf::stmntIf(stmntOpt *opts, int lineNb)
    : stmntFlow(astNode::E_STMNT_IF, opts, lineNb) {
    assert(opts);
    //std::cout << "IF : line " << lineNb << " _ " << std::string(*this) << "\n";
}

stmntIf::operator std::string() const {
    assert(getOpts());
    std::string res = "if\n";
    tab_lvl++;
    res += std::string(*getOpts());
    tab_lvl--;
    return res + _tab() + "fi;\n";
}

std::string stmntIf::getTypeDescr(void) const {
    return "If (E_STMNT_IF)";
}

stmnt* stmntIf::deepCopy(void) const {
    stmntIf* copy = new stmntIf(*this);
    copy->prev = copy;
    copy->copyChildren(*this);
    //f(copy->getNext())
    //	return stmnt::merge(copy, getNext()->deepCopy());
    return copy;
}

void stmntIf::acceptVisitor(ASTConstVisitor* visitor) const {
	visitor->visit(this);
}

void stmntIf::acceptVisitor(ASTVisitor* visitor) {
	visitor->visit(this);
}


/********************************************************************************/

stmntDo::stmntDo(stmntOpt *opts, int lineNb)
    : stmntFlow(astNode::E_STMNT_DO, opts, lineNb)
{
    assert(opts);
}

stmntDo::operator std::string() const {
    assert(getOpts());
    std::string res = "do\n"; 
    tab_lvl++;
    res += std::string(*getOpts()); 
    tab_lvl--;
    return res + _tab() +"od;\n";
}

std::string stmntDo::getTypeDescr(void) const {
    return "Do (E_STMNT_DO)";
}

stmnt* stmntDo::deepCopy(void) const {
    stmntDo* copy = new stmntDo(*this);
    copy->prev = copy;
    copy->copyChildren(*this);
    //if(copy->getNext())
    //	return stmnt::merge(copy, getNext()->deepCopy());
    return copy;
}

void stmntDo::acceptVisitor(ASTConstVisitor* visitor) const {
	visitor->visit(this);
}

void stmntDo::acceptVisitor(ASTVisitor* visitor) {
	visitor->visit(this);
}

/*************************************************************************************/

stmntBreak::stmntBreak(int lineNb)
    : stmnt(astNode::E_STMNT_BREAK, lineNb)
{
}

stmntBreak::operator std::string() const {
    return "break;\n";
}

std::string stmntBreak::getTypeDescr(void) const {
    return "Break (E_STMNT_BREAK)";
}

stmnt* stmntBreak::deepCopy(void) const {
    stmntBreak* copy = new stmntBreak(*this);
    copy->prev = copy;
    copy->copyChildren(*this);
    //if(copy->getNext())
    //	return stmnt::merge(copy, getNext()->deepCopy());
    return copy;
}

void stmntBreak::acceptVisitor(ASTConstVisitor* visitor) const {
	visitor->visit(this);
}

void stmntBreak::acceptVisitor(ASTVisitor* visitor) {
	visitor->visit(this);
}

/*****************************************************************************************/


stmntGoto::stmntGoto(const std::string& label, int lineNb)
    : stmnt(astNode::E_STMNT_GOTO, lineNb)
    , label(label)
{
}

stmntGoto::operator std::string() const {
    return "goto " + label + ";\n";
}

std::string stmntGoto::getTypeDescr(void) const {
    return "Goto (E_STMNT_GOTO)";
}
	
std::string stmntGoto::getLabel(void) const {
    return label;
}

stmnt* stmntGoto::deepCopy(void) const {
    stmntGoto* copy = new stmntGoto(*this);
    copy->prev = copy;
    copy->copyChildren(*this);
    //if(copy->getNext())
    //	return stmnt::merge(copy, getNext()->deepCopy());
    return copy;
}

void stmntGoto::acceptVisitor(ASTConstVisitor* visitor) const {
	visitor->visit(this);
}

void stmntGoto::acceptVisitor(ASTVisitor* visitor) {
	visitor->visit(this);
}

/**************************************************************************************/

stmntLabel::stmntLabel(const std::string& label, stmnt *labelled, int lineNb)
		: stmnt(astNode::E_STMNT_LABEL, lineNb)
		, label(label)
{
    assert(labelled);
    addChild("labelled", labelled);
}

void stmntLabel::setLabelled(stmnt* labelled) {
    eraseChild("labelled", labelled);
}

stmnt* stmntLabel::getLabelled() const {
    return dynamic_cast<stmnt*>(getChild("labelled"));
}

stmntLabel::operator std::string() const {
    assert(getLabelled());
    return label + ": \n" + std::string(*getLabelled());
}

std::string stmntLabel::getTypeDescr(void) const {
    return "Label (E_STMNT_LABEL)";
}

std::string stmntLabel::getLabel(void) const {
    return label;
}

stmnt* stmntLabel::deepCopy(void) const {
    stmntLabel* copy = new stmntLabel(*this);
    copy->prev = copy;
    copy->copyChildren(*this);
    //if(copy->getNext())
    //	return stmnt::merge(copy, getNext()->deepCopy());
    return copy;
}

void stmntLabel::acceptVisitor(ASTConstVisitor* visitor) const {
	visitor->visit(this);
}

void stmntLabel::acceptVisitor(ASTVisitor* visitor) {
	visitor->visit(this);
}

/********************************************************************************/

stmntElse::stmntElse(int lineNb)
		: stmnt(astNode::E_STMNT_ELSE, lineNb)
{
}

stmntElse::operator std::string() const{
    return "else;\n";
}

std::string stmntElse::getTypeDescr(void) const{
    return "Else (E_STMNT_ELSE)";
}

stmnt* stmntElse::deepCopy(void) const {
    stmntElse* copy = new stmntElse(*this);
    copy->prev = copy;
    copy->copyChildren(*this);
    //if(copy->getNext())
    //	return stmnt::merge(copy, getNext()->deepCopy());
    return copy;
}