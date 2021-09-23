#include "procSymNode.h"
#include "symTabVisitor.h"
#include "expression.h"

seqSymNode::~seqSymNode(void) {
	delete block;
}

procSymNode::~procSymNode(void) {
	if(args) 
		delete args;
	delete active;
}

void neverSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitNever(this);
}

void initSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitInit(this);
}

void procSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitProc(this);
}

void seqSymNode::resolveVariables(symTabNode* globalSymTab, const mTypeList* mTypes, varSymNode* localSymTab, symTabNode* subFieldSymTab)  {
	block->resolveVariables(globalSymTab, mTypes, block->getLocalSymTab(), subFieldSymTab);
	if(next)
		next->resolveVariables(globalSymTab, mTypes, localSymTab, subFieldSymTab);
}

unsigned int seqSymNode::processVariables(symTabNode *global, const mTypeList *mTypes, unsigned int iOffset, bool isGlobal) {
	memSize = block->processVariables(global, mTypes, 0, 0);
	return !next ? iOffset : next->processVariables(global, mTypes, iOffset, isGlobal);
}

void procSymNode::resolveVariables(symTabNode* globalSymTab, const mTypeList* mTypes, varSymNode* localSymTab, symTabNode* subFieldSymTab) {
	block->resolveVariables(globalSymTab, mTypes, block->getLocalSymTab(), subFieldSymTab);
	active->resolveVariables(globalSymTab, mTypes, localSymTab, subFieldSymTab);
	if(next)
		next->resolveVariables(globalSymTab, mTypes, localSymTab, subFieldSymTab);
}
	

unsigned int procSymNode::processVariables(symTabNode *global, const mTypeList *mTypes, unsigned int iOffset, bool isGlobal) {
	if (active && active->getType() == astNode::E_EXPR_COUNT)
		active->resolveVariables(global, mTypes);
	memSize = block->processVariables(global, mTypes, 0, 0);
	return !next ? iOffset : next->processVariables(global, mTypes, iOffset, isGlobal);
}

seqSymNode::operator std::string(void) const {
	return name + "{\n" + (block? std::string(*block) : "") + "\n}";
}

procSymNode::operator std::string(void) const {
	assert(active);
	std::string res = "";
	if (active->getCstValue() >= 1){
		res += "active";
	}
	if (active->getCstValue() > 1) {
		res += " [" + std::string(*active) + "]";
	}

	res += " proctype " + name + "(";
	const auto *arg = args;
	while (arg) {
		res += std::string(*arg) + (arg->cnextSym() ? ", " : "");
		arg = arg->cnextSym();
	}
	res += "){\n" + (block? std::string(*block) : "") + "}\n";

	return res;
}
