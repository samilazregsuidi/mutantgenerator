#ifndef SYM_COPY_VISITOR_H
#define SYM_COPY_VISITOR_H

#include "symTabVisitor.h"

class symTabCopyVisitor : public symTabVisitor {
public:
	symTabNode* deepCopy(const symTabNode* toCopy);

	void visitNA(const naSymNode* sym) override;
	void visitBit(const bitSymNode* sym) override;
	void visitBool(const boolSymNode* sym) override;
	void visitByte(const byteSymNode* sym) override;
	void visitShort(const shortSymNode* sym) override;
	void visitInt(const intSymNode* sym) override;
	void visitUnsgn(const unsgnSymNode* sym) override;
	void visitMtype(const mtypeSymNode* sym) override;
	void visitChan(const chanSymNode* sym) override;
	void visitCid(const cidSymNode* sym) override;
	void visitPid(const pidSymNode* sym) override;
	void visitTdef(const tdefSymNode* sym) override;
	void visitProc(const procSymNode* sym) override;
	void visitUtype(const utypeSymNode* sym) override;
	void visitNever(const neverSymNode* sym) override;
	void visitInit(const initSymNode* sym) override;
	void visitMtypedef(const mtypedefSymNode* sym) override;
	
private:
	symTabNode* tmp;
};

#endif
