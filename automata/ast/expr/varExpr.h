#ifndef VAR_EXPR_H
#define VAR_EXPR_H

#include "expr.h"

//E_VARREF_NAME,		// child[0] = E_EXPR_* (index into the array, or NULL), sVal = the variable/field name
//The processing step resolves all symbol names in expressions.  After this was done:
//- If the symbol denotes a variable, then symTab is the node in the symbol table of that variable;
//- If the symbol denotes an mtype, then symTab is NULL, and iVal >= 0 is the mtype value.
//- If the symbol denotes a special variable, then iVal < 0 and is one of MVAR_*

class exprVarRefName : public expr
{
public:
	exprVarRefName(const std::string& symName, int lineNb);

	exprVarRefName(const std::string& symName, expr *index, int lineNb);

	exprVarRefName(const std::string& symName, symbol *sym, int lineNb);

	virtual ~exprVarRefName() {
		delete index;
	}

	void setIndex(expr* index) {
		rmChild(this->index);
		addChild(index);
		this->index = index;
	}

	void resolve(symTable *global);

	void resolve(symTable *global, symTable* subField);

	symbol *symbolLookUpRight(void) const {
		return sym;
	}

	symbol *symbolLookUpLeft(void) const {
		return sym;
	}

	symbol* getSymbol(void) const {
		return sym;
	}

	expr* getIndex(void) const {
		return index;
	}

	std::string getName(void) const;

	operator std::string() const override;

	std::string getTypeDescr(void) const override {
		return "Variable or field name (E_VARREF_NAME)";
	}

	symbol::Type getExprType(void) const;

	expr* deepCopy(void) const override;

private:
	std::string symName;
	symbol* sym;
	expr* index;
};

//E_VARREF,			// child[0] = E_VARREF_NAME, child[1] = E_VARREF (subfield, or NULL)
class exprVarRef : public expr
{
public:
	exprVarRef(int lineNb, exprVarRefName *varRefName, exprVarRef *subfieldsVar);

	virtual ~exprVarRef() {
		delete varRefName;
		delete subfieldsVar;
	}

	void setVarRefName(exprVarRefName* varRefName) {
		rmChild(this->varRefName);
		addChild(varRefName);
		this->varRefName = varRefName;
	}

	void setSubField(exprVarRef* subField) {
		rmChild(this->subfieldsVar);
		addChild(subField);
		this->subfieldsVar = subField;
	}

	void resolve(symTable *global, symTable* subField = nullptr);

	bool hasSubField(void) const
	{
		return subfieldsVar != nullptr;
	}

	const exprVarRef *getSubField(void) const
	{
		return subfieldsVar;
	}

	const exprVarRefName *getField() const {
		return varRefName;
	}

	operator std::string() const override {
		return std::string(*varRefName) + (subfieldsVar ? "." + std::string(*subfieldsVar) : "");
	}

	std::string getTypeDescr(void) const override {
		return "Variable reference (E_VARREF)";
	}

	unsigned int assignMutables(const Mask& mask, unsigned int id) override {
		if(mask.isPresent(type)) 
			mId = ++id;
		return id;
	}

	std::vector<expr*> getMutations(void) const override;

	symbol::Type getExprType(void) const override;

	bool castToExprType(symbol::Type type) const override;

	expr* deepCopy(void) const override;
	
private:
	exprVarRefName *varRefName;
	exprVarRef *subfieldsVar;
};

//E_EXPR_VAR,			// child[0] = E_VARREF
class exprVar : public expr
{
public:
	exprVar(exprVarRef *varRef, int lineNb);

	virtual ~exprVar() {
		delete varRef;
	}

	void setVarRef(exprVarRef* varRef) {
		if(this->varRef)
			rmChild(this->varRef);
		if(varRef)
			addChild(varRef);
		this->varRef = varRef;
	}

	const exprVarRef *getVarRef(void) const {
		return varRef;
	}

	const exprVarRefName *getVarRefName(void) const {
		return getVarRef()->getField();
	}

	operator std::string() const override {
		return *varRef;
	}

	std::string getTypeDescr(void) const override {
		return "Variable reference wrapper (E_EXPR_VAR)";
	}

	symbol::Type getExprType(void) const override {
		return varRef->getExprType();
	}

	bool castToExprType(symbol::Type type) const override {
		return varRef->castToExprType(type);
	}

	bool mutateMutable(unsigned int id) override {
		if(varRef->getMId() == id){
			auto mutations = varRef->getMutations();
			//assert(mutations.size());
			size_t i = rand() % mutations.size();
			setVarRef(dynamic_cast<exprVarRef*>(mutations[i])); 
			mutations.erase(mutations.begin() + i);
			for(auto i : mutations) delete i;
			return true;
		}
		return false;
	}

	expr* deepCopy(void) const override;

private:
	exprVarRef* varRef;
};

#endif