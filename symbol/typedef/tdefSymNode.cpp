#include "symTable.hpp"
#include "tdefSymNode.hpp"
#include "varSymNode.hpp"
#include "symTabVisitor.hpp"

tdefSymNode::tdefSymNode(const std::string& name, symTable* st, const std::list<varSymNode*>& fields, int lineNb)
	: symbol(symbol::T_TDEF, name, lineNb)
	, symTable(name, st)
{
	for(auto field : fields)
		insert(field);
}

std::string tdefSymNode::getTypeName(void) const {
	return "typedef";
}

std::string tdefSymNode::getBasicTypeName(void) const {
	return "typedef";
}

int tdefSymNode::getTypeSize(void) const {
	return 0;
}

std::set<varSymNode*> tdefSymNode::getFields(void) const {
	std::set<varSymNode*> res;
	for(auto sym : getSymbols()){
		auto varSym = dynamic_cast<varSymNode*>(sym);
		assert(varSym);
		res.insert(varSym);
	}
	return res;
}

void tdefSymNode::setSymTable(symTable* symTab) {
	parent = symTab;
	setPrevSymTab(symTab);
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
	std::string res = getTypeName() + " " + symbol::name + "{\n";
	auto fields = getFields();
	for(auto it = fields.begin(); it != fields.end();){
		res += "\t" + std::string(*(*it)) + (++it != fields.end() ? ";" : "") + "\n";
	}
	res += "};";
	return res;
}