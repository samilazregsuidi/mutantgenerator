#include <assert.h>
#include <string>

#include "expression.h"
#include "symbol.h"
#include "symTable.h"
#include "varSymNode.h"
#include "utypeSymNode.h"
#include "tdefSymNode.h"
#include "mtypedefSymNode.h"
/**
 * Just creates a node with the given values.
 */
astNode::astNode(Type type, int lineNb) {
	this->type			= type;
	this->lineNb 		= lineNb;
}

astNode::Type astNode::getType(void) const {
	return type;
}

int astNode::getLineNb(void) const {
	return lineNb;
}

int astNode::tab_lvl = 0;

std::string astNode::_tab(int adjust) {
	std::string res = "";
	for(int i = 0; i < tab_lvl + adjust; ++i)
		res += "\t";
	return res;
}