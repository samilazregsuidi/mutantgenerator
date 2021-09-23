#include <assert.h>
#include <string>

#include "stmnt.h"
#include "symTabNode.h"
#include "varSymNode.h"
#include "utypeSymNode.h"
#include "tdefSymNode.h"
#include "mTypeList.h"


decl::decl(varSymNode *symTabChild, int lineNb)
	: stmnt(astNode::E_DECL, 0, nullptr, nullptr, nullptr, lineNb, nullptr, symTabChild)
{
	declSym = symTabChild;
}

stmnt* stmnt::merge(stmnt* stmnts, stmnt* newStmnt) {
	if (!stmnts)
		return newStmnt;
	if (!newStmnt)
		return stmnts;

	stmnt* newlistTail = newStmnt->prev;
	newStmnt->prev = stmnts->prev;
	newStmnt->prev->next = newStmnt;
	stmnts->prev = newlistTail;
	return stmnts;
}

unsigned int stmnt::processVariables(symTabNode* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal) const {
	offset += symTab ? symTab->processVariables(global, mTypes, offset, isGlobal) : 0;
	return offset + (next? next->processVariables(global, mTypes, offset, isGlobal) : 0);
}

void stmnt::resolveVariables(symTabNode* globalSymTab, const mTypeList* mTypes, symTabNode* localSymTab, symTabNode* subFieldSymTab) {
	astNode::resolveVariables(globalSymTab, mTypes, localSymTab, subFieldSymTab);
	if(next)
		next->resolveVariables(globalSymTab, mTypes, localSymTab, subFieldSymTab);
}

void decl::resolveVariables(symTabNode* globalSymTab, const mTypeList* mTypes, symTabNode* localSymTab, symTabNode* subFieldSymTab) {
	if(declSym->getInitExpr())
		declSym->getInitExpr()->resolveVariables(globalSymTab, mTypes, localSymTab, subFieldSymTab);
	stmnt::resolveVariables(globalSymTab, mTypes, localSymTab, subFieldSymTab);
}

decl::operator std::string() const {
	return std::string(*declSym) + (declSym->getInitExpr()? " = " + std::string(*(declSym->getInitExpr())) : "") + ";\n" + (next? std::string(*next) : "");
}
