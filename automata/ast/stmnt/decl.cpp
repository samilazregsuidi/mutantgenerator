#include <assert.h>
#include <string>

#include "decl.hpp"
#include "constExpr.hpp"

#include "symbol.hpp"
#include "varSymNode.hpp"
#include "astVisitor.hpp"
#include "utypeSymNode.hpp"
#include "tdefSymNode.hpp"
#include "procSymNode.hpp"
#include "inlineSymNode.hpp"

varDecl::varDecl(std::list<varSymNode *> declSymTab, int lineNb)
	: stmnt(astNode::E_VAR_DECL, lineNb)
{

#ifdef DEBUG
	for(auto it : declSymTab)
		assert(it)
#endif
	
	this->declSymTab = declSymTab;
}

std::string varDecl::getTypeDescr(void) const {
	return "Variable declaration wrapper (E_VAR_DECL)";
}

stmnt* varDecl::deepCopy(void) const {
	varDecl* copy = new varDecl(*this);
	copy->prev = copy;
	copy->copyChildren(*this);
	//if(copy->getNext())
	//	return stmnt::merge(copy, getNext()->deepCopy());
	return copy;
}

unsigned int varDecl::assignMutables(const Mask& mask, unsigned int id) {
	if(mask.isPresent(type))
		for(auto it : declSymTab)
			if(it->getInitExpr())
				id = it->getInitExpr()->assignMutables(mask, id);
	id = stmnt::assignMutables(mask, id);
	return id;
}

bool varDecl::mutateMutable(unsigned int id){
	for(auto it : declSymTab) {
		auto init = it->getInitExpr();
		if(init && init->getMId() == id){
			auto mutations = init->getMutations();
			assert(mutations.size());
			size_t i = rand() % mutations.size();
			
			//std::cout << std::string(*mutations[i]) <<"\n";

			it->setInitExpr(dynamic_cast<expr*>(mutations[i]));
		
			mutations.erase(mutations.begin() + i);
			for(auto i : mutations) delete i;
			return true;
		}
	}
	return false;
}

varDecl::operator std::string() const {
	std::string res = declSymTab.front()->getTypeName() + " ";
	unsigned int count = 0; 
	for(auto sym : declSymTab) {
		res += sym->getName() + (sym->getBound() > 1 ? "[" + std::to_string(sym->getBound()) + "]" : "")
		+ (sym->getInitExpr()? " = " + std::string(*sym->getInitExpr()) : "") 
		+ (++count < declSymTab.size()? ", ": "");
	}
	return res + ";\n";
}

void varDecl::acceptVisitor(ASTConstVisitor* visitor) const {
	visitor->visit(this);
}

void varDecl::acceptVisitor(ASTVisitor* visitor) {
	visitor->visit(this);
}

/*******************************************************************************************************************************/

chanDecl::chanDecl(std::list<chanSymNode *> declSymTab, int lineNb)
	: stmnt(E_CHAN_DECL, lineNb)
{
#ifdef DEBUG
	for(auto it : declSymTab)
		assert(it)
#endif
	this->declSymTab = declSymTab;
}

chanDecl::chanDecl(std::list<varSymNode *> declSymTab, int lineNb)
	: stmnt(astNode::E_VAR_DECL, lineNb)
{
	for(auto s : declSymTab) {
		auto var = dynamic_cast<chanSymNode*>(s);
		assert(var);
		this->declSymTab.push_back(var);
	}
}

chanDecl::operator std::string() const {
	std::string res = "chan ";
	unsigned int count = 0;
	for(auto c : declSymTab) {
		res += c->getName() + (c->getBound() > 1 ? "[" + std::to_string(c->getBound()) + "]" : "")
		+ " = [" + std::to_string((c)->getCapacity()) + "] of {"; 
		unsigned int types = 0;
		for(auto t : c->getTypeList())
			res += t->getTypeName() + (++types < c->getTypeList().size()? ", ": "");
		res += "}";
		res += (++count < declSymTab.size()? ", ": ";\n");
	}
	return res;
}

std::list<chanSymNode*> chanDecl::getDeclSymTab(void) const {
	return declSymTab;
}

std::string chanDecl::getTypeDescr(void) const
{
	return "Variable declaration wrapper (E_CHAN_DECL)";
}

stmnt* chanDecl::deepCopy(void) const {
	chanDecl* copy = new chanDecl(*this);
	copy->prev = copy;
	copy->copyChildren(*this);
	//if(copy->getNext())
	//	return stmnt::merge(copy, getNext()->deepCopy());
	return copy;
}

void chanDecl::acceptVisitor(ASTConstVisitor* visitor) const {
	visitor->visit(this);
}

void chanDecl::acceptVisitor(ASTVisitor* visitor) {
	visitor->visit(this);
}

/******************************************************************************************************************************************/

mtypeDecl::mtypeDecl(mtypedefSymNode* decl, int lineNb)
	: stmnt(astNode::E_MTYPE_DECL, lineNb)
{
	assert(decl);
	this->decl = decl;
}

mtypeDecl::operator std::string() const {
	std::string res = "mtype = {";
	unsigned int count = 0;
	for(auto& mtype : decl->getMTypeList()){
		res += mtype.first + (++count < decl->getMTypeList().size()? ", " : "");
	}
	res += "}\n";
	return res;
}

mtypedefSymNode* mtypeDecl::getDeclSymTab(void) const {
	return decl;
}

std::string mtypeDecl::getTypeDescr(void) const
{
	return "MType declaration wrapper (E_MTYPE_DECL)";
}

stmnt* mtypeDecl::deepCopy(void) const {
	mtypeDecl* copy = new mtypeDecl(*this);
	copy->prev = copy;
	copy->copyChildren(*this);
	//if(copy->getNext())
	//	return stmnt::merge(copy, copy->getNext());
	return copy;
}

void mtypeDecl::acceptVisitor(ASTConstVisitor* visitor) const {
	visitor->visit(this);
}

void mtypeDecl::acceptVisitor(ASTVisitor* visitor) {
	visitor->visit(this);
}

/*********************************************************************************************************************************/

tdefDecl::tdefDecl(tdefSymNode *tdefSym, int lineNb)
	: stmnt(astNode::E_TDEF_DECL, lineNb) {
	assert(tdefSym);
	this->tdefSym = tdefSym;
}

tdefDecl::operator std::string() const {
	std::string res = "typedef " + tdefSym->getName() + " {\n";
	for(auto& f : tdefSym->getFields())
		res += "\t" + f->getTypeName() + " " + f->getName() + ";\n";
	return res + "}\n\n";
}

std::string tdefDecl::getTypeDescr(void) const {
	return "Type declaration wrapper (E_TYPE_DECL)";
}

stmnt* tdefDecl::deepCopy(void) const {
	tdefDecl* copy = new tdefDecl(*this);
	copy->prev = copy;
	copy->copyChildren(*this);
	//if(copy->getNext())
	//	return stmnt::merge(copy, getNext()->deepCopy());
	return copy;
}

void tdefDecl::acceptVisitor(ASTConstVisitor* visitor) const {
	visitor->visit(this);
}

void tdefDecl::acceptVisitor(ASTVisitor* visitor) {
	visitor->visit(this);
}

/********************************************************************************************************************************************/

stmntFct::stmntFct(Type type, stmnt* block, int lineNb)
	: stmntSeq(type, block, lineNb)
{}

void stmntFct::acceptVisitor(ASTConstVisitor* visitor) const {
	visitor->visit(this);
}

void stmntFct::acceptVisitor(ASTVisitor* visitor) {
	visitor->visit(this);
}

procDecl::procDecl(procSymNode *procSym, int lineNb)
	: stmntFct(astNode::E_PROC_DECL, procSym->getBlock(), lineNb)
	, name(procSym->getName())
	, args(procSym->getArgs())
	, active(procSym->getActiveExpr())
	, procSym(procSym)
{}

std::string procDecl::getFctName(void) const {
	return procSym->getName();
}

procDecl::operator std::string() const {
	assert(active);
	std::string res = "";
	if (active->getCstValue() >= 1){
		res += "active ";
	}
	if (active->getCstValue() > 1) {
		res += "[" + std::string(*active) + "] ";
	}

	res += "proctype " + name + "(";
	unsigned int i = 0;
	for(auto it : args)
		res += it->getTypeName() + " " + it->getName() + (++i != args.size() ? "; " : "");

	++tab_lvl; res += "){\n" + (getBlock()? stmnt::string(getBlock()) : "") + "}\n"; --tab_lvl;

	return res;
}

std::string procDecl::getTypeDescr(void) const {
	return "Proctype declaration wrapper (E_PROC_DECL)";
}

stmnt* procDecl::deepCopy(void) const {
	procDecl* copy = new procDecl(*this);
	copy->prev = copy;
	copy->copyChildren(*this);
	//if(copy->getNext())
	//	return stmnt::merge(copy, getNext()->deepCopy());
	return copy;
}

/**********************************************************************************************************************************************/

initDecl::initDecl(initSymNode *procSym, int lineNb)
	: stmntFct(astNode::E_INIT_DECL, procSym->getBlock(), lineNb)
{}

std::string initDecl::getFctName(void) const {
	return procSym->getName();
}

initDecl::operator std::string() const {
	return "\ninit " + stmntSeq::operator std::string();
}

std::string initDecl::getTypeDescr(void) const {
	return "Proctype declaration wrapper (E_PROC_DECL)";
}

stmnt* initDecl::deepCopy(void) const {
	initDecl* copy = new initDecl(*this);
	copy->prev = copy;
	copy->copyChildren(*this);
	//if(copy->getNext())
	//	return stmnt::merge(copy, getNext()->deepCopy());
	return copy;
}

/************************************************************************************************************************************************/

inlineDecl::inlineDecl(inlineSymNode* sym, int lineNb) 
	: stmntFct(astNode::E_INLINE_DECL, sym->getBlock(), lineNb)
	, name(sym->getName())
	, params(sym->getParams())
	, sym(sym)
{}

std::string inlineDecl::getFctName(void) const {
	return sym->getName();
}

inlineDecl::operator std::string() const {
	std::string res = "";

	res += "inline " + name + "(";
	unsigned int i = 0;
	for(auto it : params)
		res += it + (++i != params.size() ? ", " : "");

	
	++tab_lvl; res += "){\n" + (getBlock()? stmnt::string(getBlock()) : "") + "}\n"; --tab_lvl;

	return res;
}

std::string inlineDecl::getTypeDescr(void) const{
	return "Inline declaration wrapper (E_INLINE_DECL)";
}

stmnt* inlineDecl::deepCopy(void) const {
	inlineDecl* copy = new inlineDecl(*this);
	copy->prev = copy;
	copy->copyChildren(*this);
	//if(copy->getNext())
	//	return stmnt::merge(copy, getNext()->deepCopy());
	return copy;
}

