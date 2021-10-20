#ifndef AST_VISITOR_H
#define AST_VISITOR_H

class stmntChanRecv;
class stmntChanSnd;
class stmntOpt;
class stmntIf;
class stmntDo;
class stmntBreak;
class stmntGoto;
class stmntLabel;
class stmntSeq;
class stmntAtomic;
class stmntAsgn;
class stmntIncr;
class stmntDecr;
class stmntPrint;
class stmntPrintm;
class stmntAssert;
class stmntExpr;
class stmntElse;
class stmntWait;
class stmntWhen;
class exprCond;
class exprRArg;
class exprRArgVar;
class exprRArgEval;
class exprRArgConst;
class exprArgList;
class exprRun;
class exprConst;
class exprTimeout;
class exprSkip;
class exprTrue;
class exprFalse;
class exprPlus;
class exprMinus;
class exprTimes;
class exprDiv;
class exprMod;
class exprGT;
class exprLT;
class exprGE;
class exprLE;
class exprEQ;
class exprNE;
class exprAnd;
class exprOr;
class exprBitwAnd;
class exprBitwOr;
class exprBitwXor;
class exprLShift;
class exprRShift;
class exprPar;
class exprCount;
class exprUMin;
class exprNeg;
class exprBitwNeg;
class exprLen;
class exprFull;
class exprNFull;
class exprEmpty;
class exprNEmpty;

class ASTConstVisitor {
public:
	
	virtual void visitChanRecv(const stmntChanRecv* node) = 0;
	virtual void visitChanSnd(const stmntChanSnd* node) = 0;
	virtual void visitOpt(const stmntOpt* node) = 0;
	virtual void visitIf(const stmntIf* node) = 0;
	virtual void visitDo(const stmntDo* node) = 0;
	virtual void visitBreak(const stmntBreak* node) = 0;
	virtual void visitGoto(const stmntGoto* node) = 0;
	virtual void visitLabel(const stmntLabel* node) = 0;
	virtual void visitSeq(const stmntSeq* node) = 0;
	virtual void visitAtomic(const stmntAtomic* node) = 0;
	virtual void visitAsgn(const stmntAsgn* node) = 0;
	virtual void visitIncr(const stmntIncr* node) = 0;
	virtual void visitDecr(const stmntDecr* node) = 0;
	virtual void visitPrint(const stmntPrint* node) = 0;
	virtual void visitPrintm(const stmntPrintm* node) = 0;
	virtual void visitAssert(const stmntAssert* node) = 0;
	virtual void visitExpr(const stmntExpr* node) = 0;
	virtual void visitElse(const stmntElse* node) = 0;
	virtual void visitWait(const stmntWait* node) = 0;
	virtual void visitWhen(const stmntWhen* node) = 0;
	virtual void visitCond(const exprCond* node) = 0;
	virtual void visitRArg(const exprRArg* node) = 0;
	virtual void visitRArgVar(const exprRArgVar* node) = 0;
	virtual void visitRArgEval(const exprRArgEval* node) = 0;
	virtual void visitRArgConst(const exprRArgConst* node) = 0;
	virtual void visitArgList(const exprArgList* node) = 0;
	virtual void visitRun(const exprRun* node) = 0;
	virtual void visitConst(const exprConst* node) = 0;
	virtual void visitTimeout(const exprTimeout* node) = 0;
	virtual void visitSkip(const exprSkip* node) = 0;
	virtual void visitTrue(const exprTrue* node) = 0;
	virtual void visitFalse(const exprFalse* node) = 0;
	virtual void visitPlus(const exprPlus* node) = 0;
	virtual void visitMinus(const exprMinus* node) = 0;
	virtual void visitTimes(const exprTimes* node) = 0;
	virtual void visitDiv(const exprDiv* node) = 0;
	virtual void visitMod(const exprMod* node) = 0;
	virtual void visitGT(const exprGT* node) = 0;
	virtual void visitLT(const exprLT* node) = 0;
	virtual void visitGE(const exprGE* node) = 0;
	virtual void visitLE(const exprLE* node) = 0;
	virtual void visitEQ(const exprEQ* node) = 0;
	virtual void visitNE(const exprNE* node) = 0;
	virtual void visitAnd(const exprAnd* node) = 0;
	virtual void visitOr(const exprOr* node) = 0;
	virtual void visitBitwAnd(const exprBitwAnd* node) = 0;
	virtual void visitBitwOr(const exprBitwOr* node) = 0;
	virtual void visitBitwXor(const exprBitwXor* node) = 0;
	virtual void visitLShift(const exprLShift* node) = 0;
	virtual void visitRShift(const exprRShift* node) = 0;
	virtual void visitPar(const exprPar* node) = 0;
	virtual void visitCount(const exprCount* node) = 0;
	virtual void visitUMin(const exprUMin* node) = 0;
	virtual void visitNeg(const exprNeg* node) = 0;
	virtual void visitBitwNeg(const exprBitwNeg* node) = 0;
	virtual void visitLen(const exprLen* node) = 0;
	virtual void visitFull(const exprFull* node) = 0;
	virtual void visitNFull(const exprNFull* node) = 0;
	virtual void visitEmpty(const exprEmpty* node) = 0;
	virtual void visitNEmpty(const exprNEmpty* node) = 0;
	
};

class ASTVisitor {
public:

	virtual void visitChanRecv(stmntChanRecv* node) = 0;
	virtual void visitChanSnd(stmntChanSnd* node) = 0;
	virtual void visitOpt(stmntOpt* node) = 0;
	virtual void visitIf(stmntIf* node) = 0;
	virtual void visitDo(stmntDo* node) = 0;
	virtual void visitBreak(stmntBreak* node) = 0;
	virtual void visitGoto(stmntGoto* node) = 0;
	virtual void visitLabel(stmntLabel* node) = 0;
	virtual void visitSeq(stmntSeq* node) = 0;
	virtual void visitAtomic(stmntAtomic* node) = 0;
	virtual void visitAsgn(stmntAsgn* node) = 0;
	virtual void visitIncr(stmntIncr* node) = 0;
	virtual void visitDecr(stmntDecr* node) = 0;
	virtual void visitPrint(stmntPrint* node) = 0;
	virtual void visitPrintm(stmntPrintm* node) = 0;
	virtual void visitAssert(stmntAssert* node) = 0;
	virtual void visitExpr(stmntExpr* node) = 0;
	virtual void visitElse(stmntElse* node) = 0;
	virtual void visitWait(stmntWait* node) = 0;
	virtual void visitWhen(stmntWhen* node) = 0;
	virtual void visitCond(exprCond* node) = 0;
	virtual void visitRArg(exprRArg* node) = 0;
	virtual void visitRArgVar(exprRArgVar* node) = 0;
	virtual void visitRArgEval(exprRArgEval* node) = 0;
	virtual void visitRArgConst(exprRArgConst* node) = 0;
	virtual void visitArgList(exprArgList* node) = 0;
	virtual void visitRun(exprRun* node) = 0;
	virtual void visitConst(exprConst* node) = 0;
	virtual void visitTimeout(exprTimeout* node) = 0;
	virtual void visitSkip(exprSkip* node) = 0;
	virtual void visitTrue(exprTrue* node) = 0;
	virtual void visitFalse(exprFalse* node) = 0;
	virtual void visitPlus(exprPlus* node) = 0;
	virtual void visitMinus(exprMinus* node) = 0;
	virtual void visitTimes(exprTimes* node) = 0;
	virtual void visitDiv(exprDiv* node) = 0;
	virtual void visitMod(exprMod* node) = 0;
	virtual void visitGT(exprGT* node) = 0;
	virtual void visitLT(exprLT* node) = 0;
	virtual void visitGE(exprGE* node) = 0;
	virtual void visitLE(exprLE* node) = 0;
	virtual void visitEQ(exprEQ* node) = 0;
	virtual void visitNE(exprNE* node) = 0;
	virtual void visitAnd(exprAnd* node) = 0;
	virtual void visitOr(exprOr* node) = 0;
	virtual void visitBitwAnd(exprBitwAnd* node) = 0;
	virtual void visitBitwOr(exprBitwOr* node) = 0;
	virtual void visitBitwXor(exprBitwXor* node) = 0;
	virtual void visitLShift(exprLShift* node) = 0;
	virtual void visitRShift(exprRShift* node) = 0;
	virtual void visitPar(exprPar* node) = 0;
	virtual void visitCount(exprCount* node) = 0;
	virtual void visitUMin(exprUMin* node) = 0;
	virtual void visitNeg(exprNeg* node) = 0;
	virtual void visitBitwNeg(exprBitwNeg* node) = 0;
	virtual void visitLen(exprLen* node) = 0;
	virtual void visitFull(exprFull* node) = 0;
	virtual void visitNFull(exprNFull* node) = 0;
	virtual void visitEmpty(exprEmpty* node) = 0;
	virtual void visitNEmpty(exprNEmpty* node) = 0;
	
};

class ASTMutator {
public:

	virtual void visit(stmntChanRecv*& node) = 0;
	virtual void visit(stmntChanSnd*& node) = 0;
	virtual void visit(stmntOpt*& node) = 0;
	virtual void visit(stmntIf*& node) = 0;
	virtual void visit(stmntDo*& node) = 0;
	virtual void visit(stmntBreak*& node) = 0;
	virtual void visit(stmntGoto*& node) = 0;
	virtual void visit(stmntLabel*& node) = 0;
	virtual void visit(stmntSeq*& node) = 0;
	virtual void visit(stmntAtomic*& node) = 0;
	virtual void visit(stmntAsgn*& node) = 0;
	virtual void visit(stmntIncr*& node) = 0;
	virtual void visit(stmntDecr*& node) = 0;
	virtual void visit(stmntPrint*& node) = 0;
	virtual void visit(stmntPrintm*& node) = 0;
	virtual void visit(stmntAssert*& node) = 0;
	virtual void visit(stmntExpr*& node) = 0;
	virtual void visit(stmntElse*& node) = 0;
	virtual void visit(stmntWait*& node) = 0;
	virtual void visit(stmntWhen*& node) = 0;
	virtual void visit(exprCond*& node) = 0;
	virtual void visit(exprRArg*& node) = 0;
	virtual void visit(exprRArgVar*& node) = 0;
	virtual void visit(exprRArgEval*& node) = 0;
	virtual void visit(exprRArgConst*& node) = 0;
	virtual void visit(exprArgList*& node) = 0;
	virtual void visit(exprRun*& node) = 0;
	virtual void visit(exprConst*& node) = 0;
	virtual void visit(exprTimeout*& node) = 0;
	virtual void visit(exprSkip*& node) = 0;
	virtual void visit(exprTrue*& node) = 0;
	virtual void visit(exprFalse*& node) = 0;
	virtual void visit(exprPlus*& node) = 0;
	virtual void visit(exprMinus*& node) = 0;
	virtual void visit(exprTimes*& node) = 0;
	virtual void visit(exprDiv*& node) = 0;
	virtual void visit(exprMod*& node) = 0;
	virtual void visit(exprGT*& node) = 0;
	virtual void visit(exprLT*& node) = 0;
	virtual void visit(exprGE*& node) = 0;
	virtual void visit(exprLE*& node) = 0;
	virtual void visit(exprEQ*& node) = 0;
	virtual void visit(exprNE*& node) = 0;
	virtual void visit(exprAnd*& node) = 0;
	virtual void visit(exprOr*& node) = 0;
	virtual void visit(exprBitwAnd*& node) = 0;
	virtual void visit(exprBitwOr*& node) = 0;
	virtual void visit(exprBitwXor*& node) = 0;
	virtual void visit(exprLShift*& node) = 0;
	virtual void visit(exprRShift*& node) = 0;
	virtual void visit(exprPar*& node) = 0;
	virtual void visit(exprCount*& node) = 0;
	virtual void visit(exprUMin*& node) = 0;
	virtual void visit(exprNeg*& node) = 0;
	virtual void visit(exprBitwNeg*& node) = 0;
	virtual void visit(exprLen*& node) = 0;
	virtual void visit(exprFull*& node) = 0;
	virtual void visit(exprNFull*& node) = 0;
	virtual void visit(exprEmpty*& node) = 0;
	virtual void visit(exprNEmpty*& node) = 0;
	
};

#endif