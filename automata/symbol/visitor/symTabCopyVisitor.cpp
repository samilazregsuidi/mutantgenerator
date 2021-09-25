#include "symTabCopyVisitor.h"

#include "naSymNode.h"
#include "bitSymNode.h"
#include "boolSymNode.h"
#include "byteSymNode.h"
#include "shortSymNode.h"
#include "intSymNode.h"
#include "unsgnSymNode.h"
#include "mTypeSymNode.h"
#include "utypeSymNode.h"
#include "pidSymNode.h"
#include "cidSymNode.h"
#include "tdefSymNode.h"
#include "chanSymNode.h"
#include "procSymNode.h"

symTabNode *symTabCopyVisitor::deepCopy(const symTabNode *toCopy) {
	if (!toCopy)
		return nullptr;

	symTabNode *res = nullptr;
	const symTabNode* cur = toCopy; 

	cur->acceptVisitor(this);
	res = tmp;
	res->setPrev(res);
	
	cur = cur->cnextSym();
	while(cur) {
		cur->acceptVisitor(this);
		
		tmp->setPrev(tmp);
		res->setNext(tmp);
		
		cur = cur->cnextSym();
	}

	return res;
}

void symTabCopyVisitor::visitNA(const naSymNode *sym) {
	tmp = new naSymNode(*sym);
}

void symTabCopyVisitor::visitBit(const bitSymNode *sym){
	tmp = new bitSymNode(*sym);
}

void symTabCopyVisitor::visitBool(const boolSymNode *sym){
	tmp = new boolSymNode(*sym);
}

void symTabCopyVisitor::visitByte(const byteSymNode *sym){
	tmp = new byteSymNode(*sym);
}

void symTabCopyVisitor::visitPid(const pidSymNode *sym){
	tmp = new pidSymNode(*sym);
}

void symTabCopyVisitor::visitShort(const shortSymNode *sym){
	tmp = new shortSymNode(*sym);
}

void symTabCopyVisitor::visitInt(const intSymNode *sym){
	tmp = new intSymNode(*sym);
}

void symTabCopyVisitor::visitUnsgn(const unsgnSymNode *sym){
	tmp = new unsgnSymNode(*sym);
}

void symTabCopyVisitor::visitMtype(const mTypeSymNode *sym){
	tmp = new mTypeSymNode(*sym);
}

void symTabCopyVisitor::visitChan(const chanSymNode *sym){
	tmp = new chanSymNode(*sym);
}

void symTabCopyVisitor::visitCid(const cidSymNode *sym){
	tmp = new cidSymNode(*sym);
}

void symTabCopyVisitor::visitTdef(const tdefSymNode *sym){
	tmp = new tdefSymNode(*sym);
}

void symTabCopyVisitor::visitProc(const procSymNode *sym){
	tmp = new procSymNode(*sym);
}

void symTabCopyVisitor::visitUtype(const utypeSymNode *sym){
	tmp = new utypeSymNode(*sym);
}

void symTabCopyVisitor::visitNever(const neverSymNode *sym){
	tmp = new neverSymNode(*sym);
}

void symTabCopyVisitor::visitInit(const initSymNode *sym){
	tmp = new initSymNode(*sym);
}