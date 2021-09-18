#include <assert.h>
#include <string>

#include "expression.h"
#include "symbols.h"
#include "automata.h"
/**
 * Just creates a node with the given values.
 */
astNode::astNode(Type type, const std::string& sVal, int iVal, astNode* child0, astNode* child1, astNode* child2, int lineNb, const fsm* fsmChild = nullptr, symTabNode* symTabChild = nullptr) {
	this->type			= type;
	this->sVal   		= sVal;
	this->iVal			= iVal;
	this->childFsm		= fsmChild;
	this->symTab		= symTabChild;
	this->lineNb 		= lineNb;
	this->child[0]= child0;
	this->child[1]= child1;
	this->child[2]= child2;
	this->prob = 1;
}

/**
 * Destroys an ExpNode and all that's linked to it.
 */
astNode::~astNode() {
	if(childFsm) delete(childFsm);
	if(symTab) delete(symTab);
	for(int i = 0; i < 3; i++) 
		if(child[i]) 
			delete child[i];
}

void astNode::resolveVariables(symTabNode* globalSymTab, const mTypeNode* mTypes, symTabNode* localSymTab = nullptr, symTabNode* subFieldSymTab = nullptr) {
	for(int i = 0; i < 3; i++) 
		if(child[i] != nullptr) 
			child[i]->resolveVariables(globalSymTab, mTypes, localSymTab);
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
			/* Ignored */
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

bool astNode::varOccurs(const std::string& var, const symTabNode* globalSymTab, const symTabNode* processSymTab, const mTypeNode* mtypes) const {
	assert(globalSymTab);
	return (child[0] && child[0]->varOccurs(var, globalSymTab, processSymTab, mtypes))
			|| (child[1] && child[1]->varOccurs(var, globalSymTab, processSymTab, mtypes))
				|| (child[2] && child[2]->varOccurs(var, globalSymTab, processSymTab, mtypes));
}

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