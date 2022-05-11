#include "symTable.hpp"
#include "tdefSymNode.hpp"
#include "varSymNode.hpp"
#include "symTabVisitor.hpp"

tdefSymNode::tdefSymNode(const std::string& name,  const std::list<varSymNode*>& fields, int lineNb)
	: symbol(symbol::T_TDEF, name, lineNb)
{
	for(auto field : fields)
		this->fields.insert(field);

	symTab = new symTable(name);
	for(auto f : this->fields)
		symTab->insert(f);
}

tdefSymNode::~tdefSymNode(void) {
	for(auto f: fields)
		delete f;
}

std::string tdefSymNode::getTypeName(void) const {
	return "typedef";
}

int tdefSymNode::getTypeSize(void) const {
	return 0;
}

const std::set<varSymNode*>& tdefSymNode::getFields(void) const {
	return fields;
}

symTable* tdefSymNode::getSymTable(void) const {
	return symTab;
}

void tdefSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitTdef(this);
}

void tdefSymNode::acceptVisitor(symTabVisitor *visitor) {
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