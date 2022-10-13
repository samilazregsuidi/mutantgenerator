#ifndef SYM_VISITOR_H
#define SYM_VISITOR_H

class symTable;
class symbol;
class naSymNode;
class bitSymNode;
class boolSymNode;
class byteSymNode;
class shortSymNode;
class intSymNode;
class unsgnSymNode;
class mtypeSymNode;
class chanSymNode;
class cidSymNode;
class pidSymNode;
class tdefSymNode;
class procSymNode;
class utypeSymNode;
class neverSymNode;
class initSymNode;
class mtypedefSymNode;
class cmtypeSymNode;
class inlineSymNode;

class symTabConstVisitor {
public:
	virtual void visitTab(const symTable* tab) = 0;
	virtual void visitNA(const naSymNode* sym) = 0;
	virtual void visitBit(const bitSymNode* sym) = 0 ;
	virtual void visitBool(const boolSymNode* sym) = 0;
	virtual void visitByte(const byteSymNode* sym) = 0;
	virtual void visitShort(const shortSymNode* sym) = 0;
	virtual void visitInt(const intSymNode* sym) = 0;
	virtual void visitUnsgn(const unsgnSymNode* sym) = 0;
	virtual void visitMtype(const mtypeSymNode* sym) = 0;
	virtual void visitChan(const chanSymNode* sym) = 0;
	virtual void visitCid(const cidSymNode* sym) = 0;
	virtual void visitPid(const pidSymNode* sym) = 0;
	virtual void visitTdef(const tdefSymNode* sym) = 0;
	virtual void visitProc(const procSymNode* sym) = 0;
	virtual void visitUtype(const utypeSymNode* sym) = 0;
	virtual void visitNever(const neverSymNode* sym) = 0;
	virtual void visitInit(const initSymNode* sym) = 0;
	virtual void visitMtypedef(const mtypedefSymNode* sym) = 0;
	virtual void visitCmtype(const cmtypeSymNode* sym) = 0;
	virtual void visitInline(const inlineSymNode* sym) = 0;
};

class symTabVisitor {
public:
	virtual void visitTab(symTable* tab) = 0;
	virtual void visitNA(naSymNode* sym) = 0;
	virtual void visitBit(bitSymNode* sym) = 0 ;
	virtual void visitBool(boolSymNode* sym) = 0;
	virtual void visitByte(byteSymNode* sym) = 0;
	virtual void visitShort(shortSymNode* sym) = 0;
	virtual void visitInt(intSymNode* sym) = 0;
	virtual void visitUnsgn(unsgnSymNode* sym) = 0;
	virtual void visitMtype(mtypeSymNode* sym) = 0;
	virtual void visitChan(chanSymNode* sym) = 0;
	virtual void visitCid(cidSymNode* sym) = 0;
	virtual void visitPid(pidSymNode* sym) = 0;
	virtual void visitTdef(tdefSymNode* sym) = 0;
	virtual void visitProc(procSymNode* sym) = 0;
	virtual void visitUtype(utypeSymNode* sym) = 0;
	virtual void visitNever(neverSymNode* sym) = 0;
	virtual void visitInit(initSymNode* sym) = 0;
	virtual void visitMtypedef(mtypedefSymNode* sym) = 0;
	virtual void visitCmtype(cmtypeSymNode* sym) = 0;
	virtual void visitInline(inlineSymNode* sym) = 0;
};

#endif
