#include "procSymNode.h"
#include "symTabVisitor.h"
#include "expression.h"

seqSymNode::~seqSymNode(void) {
	delete block;
}

procSymNode::~procSymNode(void) {
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

/*unsigned int seqSymNode::processVariables(symTabNode *global, const mTypeList *mTypes, unsigned int iOffset, bool isGlobal) {
	//memSize = block->processVariables(global, mTypes, 0, 0);
	return !next ? iOffset : next->processVariables(global, mTypes, iOffset, isGlobal);
}

unsigned int procSymNode::processVariables(symTabNode *global, const mTypeList *mTypes, unsigned int iOffset, bool isGlobal) {
	if (active && active->getType() == astNode::E_EXPR_COUNT)
		active->resolveVariables(global, mTypes);
	//memSize = block->processVariables(global, mTypes, 0, 0);
	return !next ? iOffset : next->processVariables(global, mTypes, iOffset, isGlobal);
}*/

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
	for(auto it = args.cbegin(); it != args.cend(); )
		res += (*it)->getTypeName() + (*it)->getName() + (++it != args.cend() ? "; " : "");

	res += "){\n" + (block? std::string(*block) : "") + "}\n";

	return res;
}
