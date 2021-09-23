#include <assert.h>
#include <string>

#include "stmnt.h"
#include "symTabNode.h"
#include "varSymNode.h"
#include "utypeSymNode.h"
#include "tdefSymNode.h"
#include "mTypeList.h"

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

decl::decl(varSymNode *declSymTab, int lineNb)
	: stmnt(astNode::E_DECL, lineNb)
{
	this->declSymTab = declSymTab;
}

unsigned int stmnt::processVariables(symTabNode* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal) const {
	offset += local ? local->processVariables(global, mTypes, offset, isGlobal) : 0;
	return offset + (next? next->processVariables(global, mTypes, offset, isGlobal) : 0);
}

void decl::resolveVariables(symTabNode* globalSymTab, const mTypeList* mTypes, symTabNode* localSymTab, symTabNode* subFieldSymTab) {
	if(declSymTab->getInitExpr())
		declSymTab->getInitExpr()->resolveVariables(globalSymTab, mTypes, localSymTab, subFieldSymTab);
	if(next) next->resolveVariables(globalSymTab, mTypes, localSymTab, subFieldSymTab);
}

decl::operator std::string() const {
	return std::string(*declSymTab) + (declSymTab->getInitExpr()? " = " + std::string(*(declSymTab->getInitExpr())) : "") + ";\n" + (next? std::string(*next) : "");
}
