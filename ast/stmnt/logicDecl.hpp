#ifndef LOGIC_DECL_H
#define LOGIC_DECL_H

#include "stmnt.hpp"

class fMultiLTLSymNode;

//E_fMultiLTLDecl,				// symTab = declaration.
class fMultiLTLDecl : public stmnt
{
public:
	fMultiLTLDecl(fMultiLTLSymNode* sym, int lineNb);

	fMultiLTLSymNode* getDeclSymTab(void) const;

	operator std::string() const;

	std::string getTypeDescr(void) const;

	unsigned int assignMutables(const Mask& mask = Mask(), unsigned int id = 0) override;

	bool mutateMutable(unsigned int id);

	stmnt* deepCopy(void) const;

	void acceptVisitor(ASTConstVisitor* visitor) const override;

	void acceptVisitor(ASTVisitor* visitor) override;

private:
	fMultiLTLSymNode* sym;
};

#endif