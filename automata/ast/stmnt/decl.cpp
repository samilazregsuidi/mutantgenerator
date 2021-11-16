#include <assert.h>
#include <string>

#include "decl.h"
#include "constExpr.h"

#include "symbol.h"
#include "varSymNode.h"
#include "utypeSymNode.h"
#include "tdefSymNode.h"
#include "procSymNode.h"

varDecl::varDecl(std::list<varSymNode *> declSymTab, int lineNb)
	: stmnt(astNode::E_VAR_DECL, lineNb)
{
	this->declSymTab = declSymTab;
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

/*******************************************************************************************************************************/

chanDecl::chanDecl(std::list<chanSymNode *> declSymTab, int lineNb)
	: stmnt(E_CHAN_DECL, lineNb)
{
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

/******************************************************************************************************************************************/

mtypeDecl::mtypeDecl(mtypedefSymNode* decl, int lineNb)
	: stmnt(astNode::E_MTYPE_DECL, lineNb)
{
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

/*********************************************************************************************************************************/

tdefDecl::tdefDecl(tdefSymNode *tdefSym, int lineNb)
	: stmnt(astNode::E_TDEF_DECL, lineNb)
{
	this->tdefSym = tdefSym;
}

tdefDecl::operator std::string() const {
	std::string res = "typedef " + tdefSym->getName() + " {\n";
	for(auto& f : tdefSym->getFields())
		res += "\t" + f->getTypeName() + " " + f->getName() + ";\n";
	return res + "}\n\n";
}

/********************************************************************************************************************************************/

procDecl::procDecl(procSymNode *procSym, int lineNb)
	: stmntSeq(astNode::E_PROC_DECL, procSym->getBlock(), lineNb)
{
	this->procSym = procSym;
}

procDecl::operator std::string() const {
	std::string res = "\n";
	if (procSym->getActiveExpr()->getCstValue() >= 1){
		res += "active";
	}
	if (procSym->getActiveExpr()->getCstValue() > 1) {
		res += " [" + std::string(*procSym->getActiveExpr()) + "]";
	}

	res += " proctype " + procSym->getName() + "(";
	for(auto& arg : procSym->getArgs())
		res += arg->getTypeName() + arg->getName() +  "; ";

	res += ")";

	res += stmntSeq::operator std::string();

	return res;
}

/**********************************************************************************************************************************************/

initDecl::initDecl(initSymNode *procSym, int lineNb)
	: stmntSeq(astNode::E_INIT_DECL, procSym->getBlock(), lineNb)
{}

initDecl::operator std::string() const {
	return "\ninit " + stmntSeq::operator std::string();
}
