#include <assert.h>
#include <string>
#include <stack>
#include <vector>

#include "astNode.hpp"
#include "symbol.hpp"
#include "symTable.hpp"
#include "varSymNode.hpp"
#include "utypeSymNode.hpp"
#include "tdefSymNode.hpp"
#include "mtypedefSymNode.hpp"

#include <iostream>

/**
 * Just creates a node with the given values.
 */
astNode::astNode(Type type, int lineNb)
	: type(type)
	, lineNb(lineNb)
	, mId(0)
{}

astNode::~astNode() {
	for(auto n : children)
		delete n.second;
}

void astNode::copyChildren(const astNode& node){
	children.clear();
	for(auto n : node.children)
		children[n.first] = n.second->deepCopy();
}

astNode::Type astNode::getType(void) const {
	return type;
}

int astNode::getLineNb(void) const {
	return lineNb;
}

void astNode::addChild(const std::string& name, astNode* child) {
	if(child) {
		children[name] = child;
	}
}

/*void astNode::moveChild(const std::string& node, astNode* child) {
	detachChild(node);
	addChild(node, child);
}*/

void astNode::deleteChild(const std::string& node) {
	auto res = detachChild(node);
	if (res) delete res;
}

void astNode::eraseChild(const std::string& node, astNode* child) {
	deleteChild(node);
	addChild(node, child);
}

astNode* astNode::detachChild(const std::string& node) {
	if (children.find(node) == children.end())
		return nullptr;
	
	auto res = children.find(node)->second;
	children.erase(node);
	return res;
}

astNode* astNode::getChild(const std::string& node) const {
	return children.find(node) != children.end() ? children.find(node)->second : nullptr;
}

std::list<astNode*> astNode::getChildren(void) const {
	std::list<astNode*> res;
	for(auto c : children)
		res.push_back(c.second);
	return res;
}

std::vector<astNode*> astNode::getMutations(void) const{
	assert(false);
	return std::vector<astNode*>();
}

unsigned int astNode::assignMutables(const Mask& mask, unsigned int id) {
	if(mask.isPresent(type)) {
		if(children.empty() && hasMutations())
			mId = ++id;
		for(auto c : children)
			id = c.second->assignMutables(mask, id);
	}
	return id;
}

bool astNode::mutateMutable(unsigned int id) {
	for(auto n : children) {
		if(n.second->getMId() == id){
			auto mutations = n.second->getMutations();
			assert(mutations.size());
			size_t i = rand() % mutations.size();

			//std::cout << std::string(*mutations[i]) << "\n";

			eraseChild(n.first, mutations[i]);
			mutations.erase(mutations.begin() + i);
			for(auto i : mutations) delete i;
			return true;
		}
	}
	return false;
}

unsigned int astNode::getMId(void) const {
	return mId;
}

bool astNode::hasMutations(void) const {
	auto mutations = getMutations();
	bool res = mutations.size() > 0;
	for(auto it : mutations)
		delete it;
	return res;
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
				stack.push(c.second);
	}
	return nullptr;
}

void astNode::acceptVisitor(ASTConstVisitor* visitor) const {
	visitor = visitor;
	assert(false);
}

void astNode::acceptVisitor(ASTVisitor* visitor) {
	visitor = visitor;
	assert(false);
}

int astNode::acceptVisitor(ASTConstVisitorInt* visitor) const {
	visitor = visitor;
	assert(false);
}

int astNode::acceptVisitor(ASTVisitorInt* visitor) {
	visitor = visitor;
	assert(false);
}