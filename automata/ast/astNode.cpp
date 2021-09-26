#include <assert.h>
#include <string>

#include "expression.h"
#include "symTabNode.h"
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