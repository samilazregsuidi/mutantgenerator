#ifndef SYM_COPY_VISITOR_H
#define SYM_COPY_VISITOR_H

#include "symTabVisitor.h"

class symTabCopyVisitor : public symTabVisitor {
public:
	symTabNode* deepCopy(const symTabNode* toCopy);

	void visitNA(const naSymNode* sym);
	void visitBit(const bitSymNode* sym);
	void visitBool(const boolSymNode* sym);
	void visitByte(const byteSymNode* sym);
	void visitShort(const shortSymNode* sym);
	void visitInt(const intSymNode* sym);
	void visitUnsgn(const unsgnSymNode* sym);
	void visitMtype(const mTypeSymNode* sym);
	void visitChan(const chanSymNode* sym);
	void visitCid(const cidSymNode* sym);
	void visitPid(const pidSymNode* sym);
	void visitTdef(const tdefSymNode* sym);
	void visitProc(const procSymNode* sym);
	void visitUtype(const utypeSymNode* sym);
	void visitNever(const neverSymNode* sym);
	void visitInit(const initSymNode* sym);
	
private:
	symTabNode* tmp;
};

#endif
