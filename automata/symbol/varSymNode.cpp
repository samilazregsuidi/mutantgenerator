#include "varSymNode.h"
#include "symTabVisitor.h"
#include "expression.h"

/*varSymNode *varSymNode::createSymTabNode(Type itype, int lineNb, const std::string &sVal, int bound, expr *init)
{
	switch (itype)
	{
	case T_NA:
		return new naSymNode(lineNb, sVal, bound, init);
	case T_BIT:
		return new bitSymNode(lineNb, sVal, bound, init);
	case T_BOOL:
		return new boolSymNode(lineNb, sVal, bound, init);
	case T_BYTE:
		return new byteSymNode(lineNb, sVal, bound, init);
	case T_PID:
		assert(false);
	case T_SHORT:
		return new shortSymNode(lineNb, sVal, bound, init);
	case T_INT:
		return new intSymNode(lineNb, sVal, bound, init);
	case T_UNSGN: // not supported yet
		assert(false);
	case T_MTYPE:
		return new mTypeSymNode(lineNb, sVal, bound, init);
	case T_CLOCK:	// dense time clock
		assert(false);

	// "Special" types:
	case T_CHAN: // Channel: capacity used; children denote message fields
		assert(false);
	case T_CID: // Channel reference; capacity and children are not used.
		assert(false);
	case T_TDEF: // Type definition: children denote fields of type
		assert(false);
	case T_PROC: // ProcType: fsm field used; bound denotes the number of initially active processes
		assert(false);
	case T_UTYPE: // Type of variable is a user type (basically, a T_TDEF record is being used as the type): utype points to the type record
		assert(false);
	case T_NEVER: // Never claim
		assert(false);
	}
	assert(false);
	return nullptr;
}

varSymNode *varSymNode::createSymTabNode(Type itype, const symTabNode &old)
{
	switch (itype)
	{
	case T_NA:
		assert(false);
	case T_BIT:
		return new bitSymNode(old);
	case T_BOOL:
		return new boolSymNode(old);
	case T_BYTE:
		return new byteSymNode(old);
	case T_PID:
		return new pidSymNode(old);
	case T_SHORT:
		return new shortSymNode(old);
	case T_INT:
		return new intSymNode(old);
	case T_UNSGN: // not supported yet
		assert(false);
	case T_MTYPE:
		return new mTypeSymNode(old);
	// "Special" types:
	case T_CHAN: // Channel: capacity used; children denote message fields
		return new chanSymNode(old);
	case T_CID: // Channel reference; capacity and children are not used.
		return new cidSymNode(old);
	case T_TDEF: // Type definition: children denote fields of type
		return new procSymNode(old);
	case T_PROC: // ProcType: fsm field used; bound denotes the number of initially active processes
		return new procSymNode(old);
	case T_UTYPE: // Type of variable is a user type (basically, a T_TDEF record is being used as the type): utype points to the type record
		return new utypeSymNode(old);
	case T_NEVER: // Never claim
		return new neverSymNode(old);
	}
	assert(false);
	return nullptr;
}*/

/**
 * Initialises the values of memSize and memOffset of all variables
 * in the symTab and its descendants and starts with the node given
 * as the first parameter.  The initial memory offset is given as
 * a parameter (usually 0).
 *
 * The function will also lookup all variable references and replace
 * them by pointers.  If a variable cannot be found, execution aborts.
 *
 * The return value is the next offset to be used after the variables
 * of the symtab were added.
 */
unsigned int varSymNode::processVariables(symTabNode *globalSymTab, const mTypeList *mTypes, unsigned int iOffset, bool bGlobal)
{
	global = bGlobal;
	if (init && init->getType() != astNode::E_EXPR_CONST && init->getType() != astNode::E_EXPR_TRUE && init->getType() != astNode::E_EXPR_FALSE)
		assert(false);
	memSize = this->getTypeSize();
	memOffset = iOffset;
	unsigned int iMemSpace = memSize * bound;
	return !next ? iOffset + iMemSpace : next->processVariables(globalSymTab, mTypes, iOffset + iMemSpace, bGlobal);
}