#include "symTable.h"
#include "tdefSymNode.h"
#include "varSymNode.h"
#include "symTabVisitor.h"

tdefSymNode::tdefSymNode(const std::string& name,  std::list<varSymNode*> fields, int lineNb)
	: symbol(symbol::T_TDEF, name, lineNb)
{
	this->fields = fields;
	symTab = new symTable(name);
	for(auto f : this->fields)
		symTab->insert(f);
}

tdefSymNode::~tdefSymNode(void) {
	for(auto f: fields)
		delete f;
}

void tdefSymNode::acceptVisitor(symTabVisitor *visitor) const{
	visitor->visitTdef(this);
}

/*unsigned int tdefSymNode::processVariables(symbol *global, const mTypeList *mTypes, unsigned int iOffset, bool isGlobal) {
	memSize = child->processVariables(global, mTypes, 0, false);
	return !next ? iOffset : next->processVariables(global, mTypes, iOffset, isGlobal);
}*/

tdefSymNode::operator std::string(void) const {
	std::string res = getTypeName() + " " + name + "{\n";
	for(auto it = fields.begin(); it != fields.end();){
		res += "\t" + std::string(*(*it)) + (++it != fields.end() ? ";" : "") + "\n";
	}
	res += "};";
	return res;
}