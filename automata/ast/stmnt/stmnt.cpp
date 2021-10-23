#include <assert.h>
#include <string>

#include "stmnt.h"
#include "varSymNode.h"
#include "utypeSymNode.h"
#include "tdefSymNode.h"
#include "procSymNode.h"

stmnt* stmnt::merge(stmnt* stmnts, stmnt* newStmnt) {

	//std::cout << "PROG : "<< (stmnts ? std::string(*stmnts) : "null") << "\n";

	//std::cout << "NEWS : "<< (newStmnt? std::string(*newStmnt) : "null") << "\n";

	if (!stmnts)
		return newStmnt;
	if (!newStmnt)
		return stmnts;

	stmnts->prev->addChild(newStmnt);

	stmnt* newlistTail = newStmnt->prev;
	newStmnt->prev = stmnts->prev;
	newStmnt->prev->next = newStmnt;
	stmnts->prev = newlistTail;

	return stmnts;
}

stmnt* stmnt::print(stmnt* list) {
	std::string res = "";
	auto cur = list;
	while (cur) {
		res += _tab() + std::string(*cur);
		cur = cur->next;
	}
}