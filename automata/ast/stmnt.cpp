#include <assert.h>
#include <string>

#include "stmnt.h"
#include "symTabNode.h"
#include "varSymNode.h"
#include "utypeSymNode.h"
#include "tdefSymNode.h"
#include "procSymNode.h"

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

/*unsigned int stmnt::processVariables(symTabNode* global, const mTypeList* mTypes, unsigned int offset, bool isGlobal) const {
	offset += local ? local->processVariables(global, mTypes, offset, isGlobal) : 0;
	return offset + (next? next->processVariables(global, mTypes, offset, isGlobal) : 0);
}*/
