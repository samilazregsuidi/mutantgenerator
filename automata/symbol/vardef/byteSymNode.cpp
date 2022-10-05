#include "byteSymNode.hpp"
#include "symTabVisitor.hpp"

#include <limits>

byteSymNode::byteSymNode(int lineNb, const std::string& name, int bound, expr* init)
	: varSymNode(symbol::T_BYTE, lineNb, name, bound, init)
{}

std::string byteSymNode::getBasicTypeName(void) const {
	return "byte";
}

int byteSymNode::getTypeSize(void) const {
	return 1;
}

int byteSymNode::getUpperBound(void) const {
	return std::numeric_limits<unsigned char>::max();
}
	
int byteSymNode::getLowerBound(void) const {
	return std::numeric_limits<unsigned char>::min();
}

void byteSymNode::acceptVisitor(symTabVisitor *visitor) {
	visitor->visitByte(this);
}

void byteSymNode::acceptVisitor(symTabConstVisitor *visitor) const{
	visitor->visitByte(this);
}