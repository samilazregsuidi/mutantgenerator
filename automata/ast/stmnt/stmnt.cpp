#include <assert.h>
#include <string>

#include "stmnt.hpp"
#include "varSymNode.hpp"
#include "utypeSymNode.hpp"
#include "tdefSymNode.hpp"
#include "procSymNode.hpp"

#include "astVisitor.hpp"

stmnt::stmnt(Type type, int lineNb)
	: astNode(type, lineNb)
	, local(nullptr)
	, prev(this)
{}

unsigned int stmnt::assignMutables(const Mask& mask, unsigned int id) {
	if(mask.isPresent(type))
		for(auto c : children)
			id = c.second->assignMutables(mask, id);
	else
		if(getNext())
			id = getNext()->assignMutables(mask, id);
	return id;
}

void stmnt::setLocalSymTab(symTable* local) {
	this->local = local;
	if(getNext())
		getNext()->setLocalSymTab(local);
}

symTable* stmnt::getLocalSymTab(void) const {
	return local;
}

void stmnt::setNext(stmnt* next) {
	eraseChild("next", next);
}

stmnt* stmnt::getNext(void) const {
	return getChild("next") ? dynamic_cast<stmnt*>(getChild("next")) : nullptr;
}

void stmnt::printSymTab(void) const {
	std::cout <<" line " << getLineNb() << "\t| " << getTypeDescr() << "\n"; 
	if(local)
		local->print();
	else 
		std::cout << "NULL\n";
	
	if(getNext())
		getNext()->printSymTab();
}

stmnt* stmnt::merge(stmnt* stmnts, stmnt* newStmnt) {

	//std::cout << "rest : "<< (stmnts ? std::string(*stmnts) : "null");

	//std::cout << "last : "<< (newStmnt ? std::string(*newStmnt) : "null");

	if (!stmnts)
		return newStmnt;
	if (!newStmnt)
		return stmnts;

	stmnts->prev->setNext(newStmnt);

	stmnt* newlistTail = newStmnt->prev;
	newStmnt->prev = stmnts->prev;
	//newStmnt->prev->setNext(newStmnt);
	stmnts->prev = newlistTail;

	return stmnts;
}

std::string stmnt::string(stmnt* list) {
	std::string res = "";
	auto cur = list;
	while (cur) {
		res += _tab() + std::string(*cur);
		cur = cur->getNext();
	}
	return res;
}

void stmnt::acceptVisitor(ASTConstVisitor* visitor) const {
	visitor->visit(this);
}

void stmnt::acceptVisitor(ASTVisitor* visitor) {
	visitor->visit(this);
}

/********************************************************************************/

stmntSeq::stmntSeq(Type type, stmnt* block, int lineNb)
	: stmnt(type, lineNb)
{
	assert(block);
	addChild("block", block);
	//std::cout << "SEQ : line " << lineNb << " _ " << std::string(*this) << "\n";
}

stmntSeq::stmntSeq(stmnt* block, int lineNb)
	: stmnt(astNode::E_STMNT_SEQ, lineNb)
{
	addChild("block", block);
}

void stmntSeq::setBlock(stmnt* block) {
	eraseChild("block", block);
}

stmnt* stmntSeq::getBlock() const {
	return dynamic_cast<stmnt*>(getChild("block"));
}

void stmntSeq::printSymTab(void) const {
	std::cout <<" line " << getLineNb() << "\t|\t" << getTypeDescr() << "\n"; 
	if(local)
			local->print();
	else 
		std::cout << "NULL\n";
	
	getBlock()->printSymTab();

	if(getNext())
		getNext()->printSymTab();
}

stmntSeq::operator std::string() const {
	assert(getBlock());
	std::string res = "{\n";
	tab_lvl++;

	auto cur = getBlock();
	while(cur) {
		res += _tab() + std::string(*cur);
		cur = cur->getNext();
	}
	
	tab_lvl--;
	res += _tab() + "};\n"; 
	return res;
}

std::string stmntSeq::getTypeDescr(void) const {
	return "Seq (E_STMNT_SEQ)";
}

stmnt* stmntSeq::deepCopy(void) const {
	stmntSeq* copy = new stmntSeq(*this);
	copy->prev = copy;
	copy->copyChildren(*this);
	//if(copy->getNext())
	//	return stmnt::merge(copy, getNext()->deepCopy());
	return copy;
}

void stmntSeq::acceptVisitor(ASTConstVisitor* visitor) const {
	visitor->visit(this);
}

void stmntSeq::acceptVisitor(ASTVisitor* visitor) {
	visitor->visit(this);
}

/***********************************************************************************************/

stmntAtomic::stmntAtomic(stmnt *block, int lineNb)
	: stmntSeq(astNode::E_STMNT_ATOMIC, block, lineNb)
{
	//std::cout << "ATOMIC : line " << lineNb << " _ " << std::string(*this) << "\n";
}

stmntAtomic::operator std::string() const{
	return "atomic " + stmntSeq::operator std::string();
}

std::string stmntAtomic::getTypeDescr(void) const{
	return "Atomic (E_STMNT_ATOMIC)";
}

stmnt* stmntAtomic::deepCopy(void) const {
	stmntAtomic* copy = new stmntAtomic(*this);
	copy->prev = copy;
	copy->copyChildren(*this);
	//if(copy->getNext())
	//	return stmnt::merge(copy, getNext()->deepCopy());
	return copy;
}

void stmntAtomic::acceptVisitor(ASTConstVisitor* visitor) const {
	visitor->visit(this);
}

void stmntAtomic::acceptVisitor(ASTVisitor* visitor) {
	visitor->visit(this);
}

/**************************************************************************************************/

stmntDStep::stmntDStep(stmnt *block, int lineNb)
	: stmntSeq(astNode::E_STMNT_DSTEP, block, lineNb)
{
	//std::cout << "ATOMIC : line " << lineNb << " _ " << std::string(*this) << "\n";
}

stmntDStep::operator std::string() const{
	return "d_step " + stmntSeq::operator std::string();
}

std::string stmntDStep::getTypeDescr(void) const{
	return "Deterministic (E_STMNT_DSTEP)";
}

stmnt* stmntDStep::deepCopy(void) const {
	stmntDStep* copy = new stmntDStep(*this);
	copy->prev = copy;
	copy->copyChildren(*this);
	//if(copy->getNext())
	//	return stmnt::merge(copy, getNext()->deepCopy());
	return copy;
}

void stmntDStep::acceptVisitor(ASTConstVisitor* visitor) const {
	visitor->visit(this);
}

void stmntDStep::acceptVisitor(ASTVisitor* visitor) {
	visitor->visit(this);
}

/******************************************************************************************************/

stmntAsgn::stmntAsgn(exprVarRef *varRef, expr *assign, int lineNb)
	: stmnt(astNode::E_STMNT_ASGN, lineNb)
{
	assert(varRef);
	assert(assign);
	addChild("var_ref", varRef);
	addChild("assign", assign);

	assign->setExprType(varRef->getExprType());
}

void stmntAsgn::setVarRef(exprVarRef* varRef) {
	eraseChild("var_ref", varRef);
}

exprVarRef* stmntAsgn::getVarRef() const {
	return dynamic_cast<exprVarRef*>(getChild("var_ref"));
}

void stmntAsgn::setAssign(expr* assign) {
	eraseChild("assign", assign);
}

expr* stmntAsgn::getAssign() const {
	return dynamic_cast<expr*>(getChild("assign"));
}

stmntAsgn::operator std::string() const {
	assert(getVarRef() && getAssign());
	return (getVarRef() ? std::string(*getVarRef()) : "nullptr") + " = " + (getAssign() ? std::string(*getAssign()) : "nullptr") + ";\n";
}

std::string stmntAsgn::getTypeDescr(void) const {
	return "Assignment (E_STMNT_ASGN)";
}

stmnt* stmntAsgn::deepCopy(void) const {
	stmntAsgn* copy = new stmntAsgn(*this);
	copy->prev = copy;
	copy->copyChildren(*this);
	//if(copy->getNext())
	//	return stmnt::merge(copy, getNext()->deepCopy());
	return copy;
}

/*******************************************************************************************************/

stmntIncr::stmntIncr(exprVarRef *varRef, int lineNb)
	: stmnt(astNode::E_STMNT_INCR, lineNb)
{
	assert(varRef);
	addChild("var_ref", varRef);
}

void stmntIncr::setVarRef(exprVarRef* varRef) {
	eraseChild("var_ref", varRef);
}

exprVarRef* stmntIncr::getVarRef() const {
	return dynamic_cast<exprVarRef*>(getChild("var_ref"));
}

stmntIncr::operator std::string() const {
	assert(getVarRef());
	return std::string(*getVarRef()) + "++;\n";
}

std::string stmntIncr::getTypeDescr(void) const {
	return "Increment (E_STMNT_INCR)";
}

stmnt* stmntIncr::deepCopy(void) const {
	stmntIncr* copy = new stmntIncr(*this);
	copy->prev = copy;
	copy->copyChildren(*this);
	//if(copy->getNext())
	//	return stmnt::merge(copy, getNext()->deepCopy());
	return copy;
}

/************************************************************************************/

stmntDecr::stmntDecr(exprVarRef *varRef, int lineNb)
	: stmnt(astNode::E_STMNT_DECR, lineNb)
{
	assert(varRef);
	addChild("var_ref", varRef);
}

void stmntDecr::setVarRef(exprVarRef* varRef) {
	eraseChild("var_ref", varRef);
}

exprVarRef* stmntDecr::getVarRef() const {
	return dynamic_cast<exprVarRef*>(getChild("var_ref"));
}

stmntDecr::operator std::string() const {
	assert(getVarRef());
	return std::string(*getVarRef()) + "--;\n";
}

std::string stmntDecr::getTypeDescr(void) const {
	return "Decrement (E_STMNT_DECR)";
}

stmnt* stmntDecr::deepCopy(void) const {
	stmntDecr* copy = new stmntDecr(*this);
	copy->prev = copy;
	copy->copyChildren(*this);
	//if(copy->getNext())
	//	return stmnt::merge(copy, getNext()->deepCopy());
	return copy;
}

/*****************************************************************************************/

stmntExpr::stmntExpr(expr *child, int lineNb)
	: stmnt(astNode::E_STMNT_EXPR, lineNb)
{
	assert(child);
	addChild("child", child);
}

void stmntExpr::setChild(expr* child) {
	eraseChild("child", child);
}

expr* stmntExpr::getChild() const{
	return dynamic_cast<expr*>(astNode::getChild("child"));
}

stmntExpr::operator std::string() const {
	assert(getChild());
	return std::string(*getChild()) + ";\n";
}

std::string stmntExpr::getTypeDescr(void) const {
	return "Expression wrapper (E_STMNT_EXPR)";
}

stmnt* stmntExpr::deepCopy(void) const {
	stmntExpr* copy = new stmntExpr(*this);
	copy->prev = copy;
	copy->copyChildren(*this);
	//if(copy->getNext())
	//	return stmnt::merge(copy, getNext()->deepCopy());
	return copy;
}

/*****************************************************************************************************/

stmntCall::stmntCall(const std::string& name, exprArgList* argList, int lineNb)
	: stmnt(astNode::E_STMNT_CALL, lineNb)
	, name(name)
{
	//assert(argList);
	addChild("arg_list", argList);
}

void stmntCall::setArgList(exprArgList* argList) {
	eraseChild("arg_list", argList);
}

exprArgList* stmntCall::getArgList() const {
	return dynamic_cast<exprArgList*>(getChild("arg_list"));
}

stmntCall::operator std::string() const {
	return name + "(" + ( getArgList()? std::string(*getArgList()) : "") + ")\n";
}

std::string stmntCall::getTypeDescr(void) const {
	return "Channel send (E_STMNT_CHAN_SND)";
}

stmnt* stmntCall::deepCopy(void) const {
	stmntCall* copy = new stmntCall(*this);
	copy->prev = copy;
	copy->copyChildren(*this);
	//if(copy->getNext())
	//	return stmnt::merge(copy, getNext()->deepCopy());
	return copy;
}