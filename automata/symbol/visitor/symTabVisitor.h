#ifndef SYM_VISITOR_H
#define SYM_VISITOR_H

class symTabNode;
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

class symTabVisitor {
public:
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
};

#endif