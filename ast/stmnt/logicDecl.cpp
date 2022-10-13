#include <assert.h>
#include <string>

#include "logicDecl.hpp"
#include "fMultiLTLSymNode.hpp"
#include "constExpr.hpp"

#include "symbol.hpp"
#include "varSymNode.hpp"
#include "astVisitor.hpp"
#include "utypeSymNode.hpp"
#include "tdefSymNode.hpp"
#include "procSymNode.hpp"
#include "inlineSymNode.hpp"

fMultiLTLDecl::fMultiLTLDecl(fMultiLTLSymNode* sym, int lineNb)
	: stmnt(astNode::E_FMULTI_LTL_DECL, lineNb)
	, sym(sym)
{}

std::string fMultiLTLDecl::getTypeDescr(void) const {
	return "fMultiLTL declaration wrapper (E_FMULTI_LTL_DECL)";
}

stmnt* fMultiLTLDecl::deepCopy(void) const {
	fMultiLTLDecl* copy = new fMultiLTLDecl(*this);
	copy->prev = copy;
	copy->copyChildren(*this);
	//if(copy->getNext())
	//	return stmnt::merge(copy, getNext()->deepCopy());
	return copy;
}

unsigned int fMultiLTLDecl::assignMutables(const Mask& mask, unsigned int id) {
	assert(false);
	return id;
}

bool fMultiLTLDecl::mutateMutable(unsigned int id){
	assert(false);
	return false;
}

fMultiLTLDecl::operator std::string() const {
	return std::string(*sym);
}

void fMultiLTLDecl::acceptVisitor(ASTConstVisitor* visitor) const {}

void fMultiLTLDecl::acceptVisitor(ASTVisitor* visitor) {}
