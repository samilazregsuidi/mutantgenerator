#include "pidSymNode.hpp"
#include "symTabVisitor.hpp"

pidSymNode::pidSymNode(int lineNb, const std::string& name, int bound, expr* init)
	: varSymNode(symbol::T_PID, lineNb, name, bound, init)
{}

std::string pidSymNode::getBasicTypeName(void) const {
	return "pid";
}

int pidSymNode::getTypeSize(void) const {
	return 1;
}

int pidSymNode::getUpperBound(void) const {
	return 255;
}
	
int pidSymNode::getLowerBound(void) const {
	return 0;
}

bool pidSymNode::castTo(const symbol* sym) const {
 	switch(sym->getType()){
		 case T_PID:
		 case T_BYTE:
		 case T_INT:
		 case T_SHORT:
		 	return true;
		 default:
			return false;
	}
	return false;
}

void pidSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitPid(this);
}

void pidSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitPid(this);
}