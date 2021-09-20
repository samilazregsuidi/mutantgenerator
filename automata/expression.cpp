#include <assert.h>
#include <string>

#include "expression.h"
#include "symbols.h"
#include "automata.h"
/**
 * Just creates a node with the given values.
 */
astNode::astNode(Type type, int iVal, astNode* child0, astNode* child1, astNode* child2, int lineNb, stmnt* block, symTabNode* symTabChild) {
	this->type			= type;
	this->iVal			= iVal;
	this->childFsm		= block;
	this->symTab		= symTabChild;
	this->lineNb 		= lineNb;
	this->child[0]= child0;
	this->child[1]= child1;
	this->child[2]= child2;
}

decl::decl(symTabNode *symTabChild, int lineNb)
	: stmnt(astNode::E_DECL, 0, nullptr, nullptr, nullptr, lineNb, nullptr, symTabChild)
{
	declSym = symTabNode::createSymTabNode(symTabChild->getType(), *symTabChild);
}

/**
 * Destroys an ExpNode and all that's linked to it.
 */
astNode::~astNode() {
	if(childFsm) 
		delete(childFsm);
	if(symTab) 
		delete(symTab);
	for(int i = 0; i < 3; i++) 
		if(child[i]) 
			delete child[i];
}

/**
 * Returns the symbol corresponding with the far right name of an expression referencing a variable.
 * If the expression does not reference a variable, returns NULL.
 */
/*symTabNode* astNode::symbolLookUpRight() const {
	if(type == E_VARREF) {
		if (child[1]) {
			// If there is a child (of type E_VARREF), then continue
			return child[1]->symbolLookUpRight();
		} else {
			// Otherwise, go to the E_VARREF_NAME node
			return child[0]->symbolLookUpRight();
		}
	}
	if(type == E_RARG_VAR  || type == E_EXPR_VAR)
		return child[0]->symbolLookUpRight();
	if(type == E_VARREF_NAME)
		return symTab;
	return nullptr;
}*/

symTabNode* astNode::symbolLookUpRight() const {
	return nullptr;
}

/**
 * Returns the symbol corresponding with the far left name of an expression referencing a variable.
 * If the expression does not reference a variable, returns NULL.
 */
/*symTabNode* astNode::symbolLookUpLeft(void) const {
	if(type == E_EXPR_VAR)
		return child[0]->symbolLookUpLeft();
	if(type == E_VARREF)
		return child[0]->symbolLookUpLeft();
	if(type == E_RARG_VAR)
		return child[0]->symbolLookUpLeft();
	if(type == E_VARREF_NAME)
		return symTab;
	return nullptr;
}*/

symTabNode* astNode::symbolLookUpLeft(void) const {
	return nullptr;
}

/*bool astNode::isTimeout(void) const {
	return false;
}*/


/*bool astNode::varOccurs(const std::string& var, const symTabNode* globalSymTab, const symTabNode* processSymTab, const mTypeNode* mtypes) const {
	assert(globalSymTab);
	std::string path;
	//printf("Exp Type = %s\n", getExpTypeName(getType()));
	switch(getType()) {

		case(astNode::E_STMNT):
		case(astNode::E_STMNT_EXPR):
		case(astNode::E_EXPR_PAR):
		case(astNode::E_STMNT_INCR):
		case(astNode::E_STMNT_DECR):
		case(astNode::E_EXPR_UMIN):
		case(astNode::E_EXPR_NEG):
		case(astNode::E_EXPR_LEN):
		case(astNode::E_EXPR_FULL):
		case(astNode::E_EXPR_NFULL):
		case(astNode::E_EXPR_EMPTY):
		case(astNode::E_EXPR_NEMPTY):
		case(astNode::E_RARG_VAR):
		case(astNode::E_RARG_EVAL):
		{
			return child[0]->varOccurs(var, globalSymTab, processSymTab, mtypes);
		}
		case(astNode::E_STMNT_CHAN_RCV):
		case(astNode::E_STMNT_CHAN_SND):
		case(astNode::E_STMNT_ASGN):
		case(astNode::E_EXPR_PLUS):
		case(astNode::E_EXPR_MINUS):
		case(astNode::E_EXPR_TIMES):
		case(astNode::E_EXPR_DIV):
		case(astNode::E_EXPR_MOD):
		case(astNode::E_EXPR_GT):
		case(astNode::E_EXPR_GE):
		case(astNode::E_EXPR_LT):
		case(astNode::E_EXPR_LE):
		case(astNode::E_EXPR_EQ):
		case(astNode::E_EXPR_NE):
		case(astNode::E_EXPR_AND):
		case(astNode::E_EXPR_OR):
		case(astNode::E_EXPR_LSHIFT):
		case(astNode::E_EXPR_RSHIFT):
		case(astNode::E_EXPR_BITWAND):
		case(astNode::E_EXPR_BITWOR):
		case(astNode::E_EXPR_BITWXOR):
		case(astNode::E_ARGLIST):
		{
			return child[0]->varOccurs(var, globalSymTab, processSymTab, mtypes)
					|| child[1]->varOccurs(var, globalSymTab, processSymTab, mtypes);
		}
		case(astNode::E_EXPR_COND):
		{
			return child[0]->varOccurs(var, globalSymTab, processSymTab, mtypes)
					|| child[1]->varOccurs(var, globalSymTab, processSymTab, mtypes)
						|| child[2]->varOccurs(var, globalSymTab, processSymTab, mtypes);
		}
		case(astNode::E_EXPR_RUN):
			//break;

		/*case(astNode::E_EXPR_VAR):
		{//case(astNode::E_VARREF):
		//case(astNode::E_VARREF_NAME):
			//printf("Exp type = %s\n", getExpTypeName(getType()));
			//printf("Child0 exp type = %s\n", getExpTypeName(child[0]->type));
			//printf("Child1 exp type = %s\n", child[1] ? getExpTypeName(child[1]->type) : "(null)");
			path = child[0]->var2String(globalSymTab, processSymTab, mtypes);
			//if(path) printf("\t Found var: %s (line %d)\n", path, getLineNb());
			return var == path;
		}
		default:
			break;
	}
	return false;
}*/

/*bool astNode::varOccurs(const std::string& var, const symTabNode* globalSymTab, const symTabNode* processSymTab, const mTypeNode* mtypes) const {
	assert(globalSymTab);
	return (child[0] && child[0]->varOccurs(var, globalSymTab, processSymTab, mtypes))
			|| (child[1] && child[1]->varOccurs(var, globalSymTab, processSymTab, mtypes))
				|| (child[2] && child[2]->varOccurs(var, globalSymTab, processSymTab, mtypes));
}*/

/*std::list<std::string> astNode::getVars(const symTabNode* globalSymTab, const symTabNode* processSymTab, const mTypeNode* mtypes) const {
	assert(globalSymTab);
	std::string path = NULL;
	switch(getType()) {
		case(astNode::E_STMNT):
		case(astNode::E_STMNT_EXPR):
		case(astNode::E_EXPR_PAR):
		case(astNode::E_STMNT_INCR):
		case(astNode::E_STMNT_DECR):
		case(astNode::E_EXPR_UMIN):
		case(astNode::E_EXPR_NEG):
		case(astNode::E_EXPR_LEN):
		case(astNode::E_EXPR_FULL):
		case(astNode::E_EXPR_NFULL):
		case(astNode::E_EXPR_EMPTY):
		case(astNode::E_EXPR_NEMPTY):
		case(astNode::E_RARG_VAR):
		case(astNode::E_RARG_EVAL):
			return child[0]->getVars(globalSymTab, processSymTab, mtypes);
			break;

		case(astNode::E_STMNT_CHAN_RCV):
		case(astNode::E_STMNT_CHAN_SND):
			return child[1]->getVars(globalSymTab, processSymTab, mtypes);

		case(astNode::E_STMNT_ASGN):
		case(astNode::E_EXPR_PLUS):
		case(astNode::E_EXPR_MINUS):
		case(astNode::E_EXPR_TIMES):
		case(astNode::E_EXPR_DIV):
		case(astNode::E_EXPR_MOD):
		case(astNode::E_EXPR_GT):
		case(astNode::E_EXPR_GE):
		case(astNode::E_EXPR_LT):
		case(astNode::E_EXPR_LE):
		case(astNode::E_EXPR_EQ):
		case(astNode::E_EXPR_NE):
		case(astNode::E_EXPR_AND):
		case(astNode::E_EXPR_OR):
		case(astNode::E_EXPR_LSHIFT):
		case(astNode::E_EXPR_RSHIFT):
		case(astNode::E_EXPR_BITWAND):
		case(astNode::E_EXPR_BITWOR):
		case(astNode::E_EXPR_BITWXOR):
		case(astNode::E_ARGLIST):
		{
			auto left = child[0]->getVars(globalSymTab, processSymTab, mtypes);
			auto right = child[1]->getVars(globalSymTab, processSymTab, mtypes);
			left.splice(left.begin(), right);
			return left;
		}
		case(astNode::E_EXPR_COND):
		{
			auto left = child[0]->getVars(globalSymTab, processSymTab, mtypes);
		    auto right = child[1]->getVars(globalSymTab, processSymTab, mtypes);
			auto cond = child[2]->getVars(globalSymTab, processSymTab, mtypes);
			left.splice(left.begin(), right);
			left.splice(left.begin(), cond);
			return left;
		}
		case(astNode::E_EXPR_RUN):
			
			break;

		case(astNode::E_EXPR_VAR):
		case(astNode::E_VARREF):
		case(astNode::E_VARREF_NAME):
		{
			std::list<std::string> res;
			res.push_back(var2String(globalSymTab, processSymTab, mtypes));
			return res;
		}
		default:
			break;
	}
}*/

/*std::list<std::string>  astNode::getReadVars(const symTabNode* globalSymTab, const symTabNode* processSymTab, const mTypeNode* mtypes, std::list<const astNode*>& expressions, std::list<const symTabNode*>& symbols) const {
	assert(globalSymTab);
	std::string path;
	switch(getType()) {
		case(astNode::E_STMNT):
		case(astNode::E_STMNT_EXPR):
		case(astNode::E_EXPR_PAR):
		case(astNode::E_STMNT_INCR):
		case(astNode::E_STMNT_DECR):
		case(astNode::E_EXPR_UMIN):
		case(astNode::E_EXPR_NEG):
		case(astNode::E_EXPR_LEN):
		case(astNode::E_EXPR_FULL):
		case(astNode::E_EXPR_NFULL):
		case(astNode::E_EXPR_EMPTY):
		case(astNode::E_EXPR_NEMPTY):
		case(astNode::E_RARG_VAR):
		case(astNode::E_RARG_EVAL):
			return child[0]->getReadVars(globalSymTab, processSymTab, mtypes, expressions, symbols);

		case(astNode::E_STMNT_CHAN_SND):
		case(astNode::E_STMNT_ASGN):
			if(child[1])
				return child[1]->getReadVars(globalSymTab, processSymTab, mtypes, expressions, symbols);

		case(astNode::E_EXPR_PLUS):
		case(astNode::E_EXPR_MINUS):
		case(astNode::E_EXPR_TIMES):
		case(astNode::E_EXPR_DIV):
		case(astNode::E_EXPR_MOD):
		case(astNode::E_EXPR_GT):
		case(astNode::E_EXPR_GE):
		case(astNode::E_EXPR_LT):
		case(astNode::E_EXPR_LE):
		case(astNode::E_EXPR_EQ):
		case(astNode::E_EXPR_NE):
		case(astNode::E_EXPR_AND):
		case(astNode::E_EXPR_OR):
		case(astNode::E_EXPR_LSHIFT):
		case(astNode::E_EXPR_RSHIFT):
		case(astNode::E_EXPR_BITWAND):
		case(astNode::E_EXPR_BITWOR):
		case(astNode::E_EXPR_BITWXOR):
		case(astNode::E_ARGLIST):
		{
			auto left = child[0]->getReadVars(globalSymTab, processSymTab, mtypes, expressions, symbols);
		    auto right = child[1]->getReadVars(globalSymTab, processSymTab, mtypes, expressions, symbols);
			left.splice(left.begin(), right);
			return left;
		}
		case(astNode::E_EXPR_COND):
		{
			auto left = child[0]->getReadVars(globalSymTab, processSymTab, mtypes, expressions, symbols);
		    auto right = child[1]->getReadVars(globalSymTab, processSymTab, mtypes, expressions, symbols);
			auto cond = child[2]->getReadVars(globalSymTab, processSymTab, mtypes, expressions, symbols);
			left.splice(left.begin(), right);
			left.splice(left.begin(), cond);
			return left;
		}
		case(astNode::E_EXPR_RUN):
	
			break;

		case(astNode::E_EXPR_VAR):
		case(astNode::E_VARREF):
		case(astNode::E_VARREF_NAME):
		{
			expressions.push_back(this);
			symbols.push_back(symbolLookUpRight());
			std::list<std::string> res;
			res.push_back(var2String(globalSymTab, processSymTab, mtypes));
			return res;
		}
		default:
			break;
	}
}*/

symTabNode* astNode::getSymbol(void) const {
	return symTab;
}

void astNode::setSymbol(symTabNode *sym) {
	symTab = sym;
	for(int i = 0; i < 3; ++i)
		if(child[i])
			child[i]->setSymbol(sym);
}

astNode::Type astNode::getType(void) const {
	return type;
}

int astNode::getLineNb(void) const {
	return lineNb;
}

/*std::string astNode::getName(void) const {
	return sVal;
}

void astNode::setName(const std::string& sVal) {
	this->sVal = sVal;
}*/

void astNode::setGlobal(bool global) {
	this->global = global;
}

bool astNode::isGlobal(void) const {
	return global;
}

int astNode::getIVal(void) const {
	return iVal;
}

void astNode::setIVal(int ival) {
	this->iVal = ival;
}
//const symTabNode* getUType(void) const;
//virtual bool isTimeout(void) const;

astNode* astNode::getChild0(void) const{
	return child[0];
}

astNode* astNode::getChild1(void) const{
	return child[1];
}

astNode* astNode::getChild2(void) const{
	return child[2];
}

astNode* astNode::detachChild0(void) {
	astNode* child0 = child[0];
	child[0] = nullptr;
	return child0;
}

astNode* astNode::detachChild1(void) {
	astNode* child1 = child[1];
	child[1] = nullptr;
	return child1;
}

astNode* astNode::detachChild2(void) {
	astNode* child2 = child[2];
	child[2] = nullptr;
	return child2;
}

/*fsm* astNode::getChildFsm(void) const {
	return childFsm;
}*/

stmnt* stmnt::merge(stmnt* stmnts, stmnt* newStmnt) {
	if (!stmnts)
		return newStmnt;
	if (!newStmnt)
		return stmnts;

	stmnt* newlistTail = newStmnt->prev;
	newStmnt->prev = stmnts->prev;
	newStmnt->prev->next = newStmnt;
	stmnts->prev = newlistTail;
	return stmnts;
}

unsigned int stmnt::processVariables(symTabNode* global, const mTypeNode* mTypes, unsigned int offset, bool isGlobal) const {
	offset += symTab ? symTab->processVariables(global, mTypes, offset, isGlobal) : 0;
	return offset + (next? next->processVariables(global, mTypes, offset, isGlobal) : 0);
}

std::string exprVarRefName::getName(void) const {
	return symTab->getName();
}

exprVarRefName::operator std::string() const {
	return symTab->getName() + (child[0] ? "[" + std::string(*child[0]) + "]" : "");
}

decl::operator std::string() const {
	return std::string(*declSym) + (declSym->getInitExpr()? " = " + std::string(*(declSym->getInitExpr())) : "") + ";\n" + (next? std::string(*next) : "");
}

void astNode::resolveVariables(symTabNode* globalSymTab, const mTypeNode* mTypes, symTabNode* localSymTab, symTabNode* subFieldSymTab) {
	for(int i = 0; i < 3; i++) 
		if(child[i] != nullptr) 
			child[i]->resolveVariables(globalSymTab, mTypes, localSymTab, subFieldSymTab);
}

void stmnt::resolveVariables(symTabNode* globalSymTab, const mTypeNode* mTypes, symTabNode* localSymTab, symTabNode* subFieldSymTab) {
	astNode::resolveVariables(globalSymTab, mTypes, localSymTab, subFieldSymTab);
	if(next)
		next->resolveVariables(globalSymTab, mTypes, localSymTab, subFieldSymTab);
}

void decl::resolveVariables(symTabNode* globalSymTab, const mTypeNode* mTypes, symTabNode* localSymTab, symTabNode* subFieldSymTab) {
	if(declSym->getInitExpr())
		declSym->getInitExpr()->resolveVariables(globalSymTab, mTypes, localSymTab, subFieldSymTab);
	stmnt::resolveVariables(globalSymTab, mTypes, localSymTab, subFieldSymTab);
}


void exprVarRefName::resolveVariables(symTabNode *global, const mTypeNode *mTypes, symTabNode *local, symTabNode *subField) {

	if (subField)
		symTab = subField->lookupInSymTab(symName);
	else if (local)
		symTab = local->lookupInSymTab(symName);
	else
		symTab = global->lookupInSymTab(symName);

	if (symTab) {
		if(child[0]) 
			child[0]->resolveVariables(global, mTypes, local, subField);
	} else {
		// First check if its a magic variable
		int mvar = 0;
		if (mvar == 0 && symName == MVARID_LAST)
			mvar = MVAR_LAST;
		if (mvar == 0 && symName == MVARID_NRPR)
			mvar = MVAR_NRPR;
		if (mvar == 0 && symName == MVARID_PID)
			mvar = MVAR_PID;
		if (mvar == 0 && symName == MVARID_SCRATCH)
			mvar = MVAR_SCRATCH;

		if (mvar < 0)
		{
			// MVar IDs are negative!
			iVal = mvar;
		}
		else
		{
			// Then check if it's an mtype
			int value = mTypes? mTypes->getMTypeValue(symName) : -1;
			assert(!(value == -1 && !iVal));
			iVal = value;
		}
	}
}

void exprVarRef::resolveVariables(symTabNode *global, const mTypeNode *mTypes, symTabNode *local, symTabNode *subField) {

	child[0]->resolveVariables(global, mTypes, local, subField);
	auto symbol = child[0]->getSymbol();

	if (symbol)
	{
		// Resolve subfields, but with the symbol table of the type
		if (child[1])
		{
			assert(symbol->getUType());
			child[1]->resolveVariables(global, mTypes, local, symbol->getUType()->getChild());
		}
	}
	else
		assert(!child[1]);
}

void exprRun::resolveVariables(symTabNode *global, const mTypeNode *mTypes, symTabNode *local, symTabNode *subField) {

	if (subField)
		symTab = subField->lookupInSymTab(procName);
	else if (local)
		symTab = local->lookupInSymTab(procName);
	else
		symTab = global->lookupInSymTab(procName);

	assert(symTab && symTab->getType() == symTabNode::T_PROC);

	child[0]->resolveVariables(global, mTypes, local, subField);
}