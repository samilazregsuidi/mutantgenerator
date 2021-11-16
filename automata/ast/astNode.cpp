#include <assert.h>
#include <string>
#include <stack>

#include "astNode.h"
#include "symbol.h"
#include "symTable.h"
#include "varSymNode.h"
#include "utypeSymNode.h"
#include "tdefSymNode.h"
#include "mtypedefSymNode.h"

/**
 * Just creates a node with the given values.
 */
astNode::astNode(Type type, int lineNb)
	: type(type)
	, lineNb(lineNb)
	, parent(nullptr)
	, mId(0)
{

}

astNode::~astNode() {
	/*for(auto n : children)
		delete n;*/
}

astNode::Type astNode::getType(void) const {
	return type;
}

int astNode::getLineNb(void) const {
	return lineNb;
}

void astNode::setParent(astNode* parent) {
	this->parent = parent;
}

astNode* astNode::getParent(void) const {
	return parent;
}

unsigned int astNode::assignMutables(const Mask& mask, unsigned int id) {
	if(mask.isPresent(type)) {
		if(children.empty())
			mId = ++id;
		for(auto c : children)
			id = c->assignMutables(mask, id);
	}
	return id;
}

bool astNode::mutateMutable(unsigned int id) {
	id++;//keep compiler happy
	return false;
}

int astNode::tab_lvl = 0;

std::string astNode::_tab(int adjust) {
	std::string res = "";
	for(int i = 0; i < tab_lvl + adjust; ++i)
		res += "\t";
	return res;
}

astNode* astNode::mutate(astNode* ast, unsigned int id) {
	std::stack<astNode*> stack;
	stack.push(ast);

	while(!stack.empty()) {
		astNode* node = stack.top();
		stack.pop();
		if(node->mutateMutable(id))
			return ast;
		else
			for(auto c : node->children)
				stack.push(c);
	}
	return nullptr;
}