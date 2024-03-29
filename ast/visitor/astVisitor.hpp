#ifndef AST_VISITOR_H
#define AST_VISITOR_H

class stmnt;
class stmntChanRecv;
class stmntChanSnd;
class stmntOpt;
class stmntIf;
class stmntDo;
class stmntBreak;
class stmntGoto;
class stmntLabel;
class stmntSeq;
class stmntFct;
class stmntAtomic;
class stmntDStep;
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
class varDecl;
class chanDecl;
class mtypeDecl;
class tdefDecl;
class inlineDecl;
class procDecl;
class initDecl;
class expr;
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
	virtual void visit(const stmnt* node) = 0;
	virtual void visit(const stmntChanRecv* node) = 0;
	virtual void visit(const stmntChanSnd* node) = 0;
	virtual void visit(const stmntOpt* node) = 0;
	virtual void visit(const stmntIf* node) = 0;
	virtual void visit(const stmntDo* node) = 0;
	virtual void visit(const stmntBreak* node) = 0;
	virtual void visit(const stmntGoto* node) = 0;
	virtual void visit(const stmntLabel* node) = 0;
	virtual void visit(const stmntSeq* node) = 0;
	virtual void visit(const stmntFct* node) = 0;
	virtual void visit(const stmntAtomic* node) = 0;
	virtual void visit(const stmntDStep* node) = 0;
	virtual void visit(const stmntAsgn* node) = 0;
	virtual void visit(const stmntIncr* node) = 0;
	virtual void visit(const stmntDecr* node) = 0;
	virtual void visit(const stmntPrint* node) = 0;
	virtual void visit(const stmntPrintm* node) = 0;
	virtual void visit(const stmntAssert* node) = 0;
	virtual void visit(const stmntExpr* node) = 0;
	virtual void visit(const stmntElse* node) = 0;
	virtual void visit(const stmntWait* node) = 0;
	virtual void visit(const stmntWhen* node) = 0;
	virtual void visit(const varDecl* node) = 0;
	virtual void visit(const chanDecl* node) = 0;
	virtual void visit(const tdefDecl* node) = 0;
	virtual void visit(const mtypeDecl* node) = 0;
	virtual void visit(const inlineDecl* node) = 0;
	virtual void visit(const procDecl* node) = 0;
	virtual void visit(const initDecl* node) = 0;
	virtual void visit(const expr* node) = 0;
	virtual void visit(const exprCond* node) = 0;
	virtual void visit(const exprRArg* node) = 0;
	virtual void visit(const exprRArgVar* node) = 0;
	virtual void visit(const exprRArgEval* node) = 0;
	virtual void visit(const exprRArgConst* node) = 0;
	virtual void visit(const exprArgList* node) = 0;
	virtual void visit(const exprRun* node) = 0;
	virtual void visit(const exprConst* node) = 0;
	virtual void visit(const exprTimeout* node) = 0;
	virtual void visit(const exprSkip* node) = 0;
	virtual void visit(const exprTrue* node) = 0;
	virtual void visit(const exprFalse* node) = 0;
	virtual void visit(const exprPlus* node) = 0;
	virtual void visit(const exprMinus* node) = 0;
	virtual void visit(const exprTimes* node) = 0;
	virtual void visit(const exprDiv* node) = 0;
	virtual void visit(const exprMod* node) = 0;
	virtual void visit(const exprGT* node) = 0;
	virtual void visit(const exprLT* node) = 0;
	virtual void visit(const exprGE* node) = 0;
	virtual void visit(const exprLE* node) = 0;
	virtual void visit(const exprEQ* node) = 0;
	virtual void visit(const exprNE* node) = 0;
	virtual void visit(const exprAnd* node) = 0;
	virtual void visit(const exprOr* node) = 0;
	virtual void visit(const exprBitwAnd* node) = 0;
	virtual void visit(const exprBitwOr* node) = 0;
	virtual void visit(const exprBitwXor* node) = 0;
	virtual void visit(const exprLShift* node) = 0;
	virtual void visit(const exprRShift* node) = 0;
	virtual void visit(const exprPar* node) = 0;
	virtual void visit(const exprCount* node) = 0;
	virtual void visit(const exprUMin* node) = 0;
	virtual void visit(const exprNeg* node) = 0;
	virtual void visit(const exprBitwNeg* node) = 0;
	virtual void visit(const exprLen* node) = 0;
	virtual void visit(const exprFull* node) = 0;
	virtual void visit(const exprNFull* node) = 0;
	virtual void visit(const exprEmpty* node) = 0;
	virtual void visit(const exprNEmpty* node) = 0;
	
};

class ASTConstVisitorInt {
public:
	virtual int visit(const stmnt* node) = 0;
	virtual int visit(const stmntChanRecv* node) = 0;
	virtual int visit(const stmntChanSnd* node) = 0;
	virtual int visit(const stmntOpt* node) = 0;
	virtual int visit(const stmntIf* node) = 0;
	virtual int visit(const stmntDo* node) = 0;
	virtual int visit(const stmntBreak* node) = 0;
	virtual int visit(const stmntGoto* node) = 0;
	virtual int visit(const stmntLabel* node) = 0;
	virtual int visit(const stmntSeq* node) = 0;
	virtual int visit(const stmntFct* node) = 0;
	virtual int visit(const stmntAtomic* node) = 0;
	virtual int visit(const stmntDStep* node) = 0;
	virtual int visit(const stmntAsgn* node) = 0;
	virtual int visit(const stmntIncr* node) = 0;
	virtual int visit(const stmntDecr* node) = 0;
	virtual int visit(const stmntPrint* node) = 0;
	virtual int visit(const stmntPrintm* node) = 0;
	virtual int visit(const stmntAssert* node) = 0;
	virtual int visit(const stmntExpr* node) = 0;
	virtual int visit(const stmntElse* node) = 0;
	virtual int visit(const stmntWait* node) = 0;
	virtual int visit(const stmntWhen* node) = 0;
	virtual int visit(const varDecl* node) = 0;
	virtual int visit(const chanDecl* node) = 0;
	virtual int visit(const tdefDecl* node) = 0;
	virtual int visit(const mtypeDecl* node) = 0;
	virtual int visit(const inlineDecl* node) = 0;
	virtual int visit(const procDecl* node) = 0;
	virtual int visit(const initDecl* node) = 0;
	virtual int visit(const expr* node) = 0;
	virtual int visit(const exprCond* node) = 0;
	virtual int visit(const exprRArg* node) = 0;
	virtual int visit(const exprRArgVar* node) = 0;
	virtual int visit(const exprRArgEval* node) = 0;
	virtual int visit(const exprRArgConst* node) = 0;
	virtual int visit(const exprArgList* node) = 0;
	virtual int visit(const exprRun* node) = 0;
	virtual int visit(const exprConst* node) = 0;
	virtual int visit(const exprTimeout* node) = 0;
	virtual int visit(const exprSkip* node) = 0;
	virtual int visit(const exprTrue* node) = 0;
	virtual int visit(const exprFalse* node) = 0;
	virtual int visit(const exprPlus* node) = 0;
	virtual int visit(const exprMinus* node) = 0;
	virtual int visit(const exprTimes* node) = 0;
	virtual int visit(const exprDiv* node) = 0;
	virtual int visit(const exprMod* node) = 0;
	virtual int visit(const exprGT* node) = 0;
	virtual int visit(const exprLT* node) = 0;
	virtual int visit(const exprGE* node) = 0;
	virtual int visit(const exprLE* node) = 0;
	virtual int visit(const exprEQ* node) = 0;
	virtual int visit(const exprNE* node) = 0;
	virtual int visit(const exprAnd* node) = 0;
	virtual int visit(const exprOr* node) = 0;
	virtual int visit(const exprBitwAnd* node) = 0;
	virtual int visit(const exprBitwOr* node) = 0;
	virtual int visit(const exprBitwXor* node) = 0;
	virtual int visit(const exprLShift* node) = 0;
	virtual int visit(const exprRShift* node) = 0;
	virtual int visit(const exprPar* node) = 0;
	virtual int visit(const exprCount* node) = 0;
	virtual int visit(const exprUMin* node) = 0;
	virtual int visit(const exprNeg* node) = 0;
	virtual int visit(const exprBitwNeg* node) = 0;
	virtual int visit(const exprLen* node) = 0;
	virtual int visit(const exprFull* node) = 0;
	virtual int visit(const exprNFull* node) = 0;
	virtual int visit(const exprEmpty* node) = 0;
	virtual int visit(const exprNEmpty* node) = 0;
};

class ASTVisitor {
public:
	virtual void visit(stmnt* node) = 0;
	virtual void visit(stmntChanRecv* node) = 0;
	virtual void visit(stmntChanSnd* node) = 0;
	virtual void visit(stmntOpt* node) = 0;
	virtual void visit(stmntIf* node) = 0;
	virtual void visit(stmntDo* node) = 0;
	virtual void visit(stmntBreak* node) = 0;
	virtual void visit(stmntGoto* node) = 0;
	virtual void visit(stmntLabel* node) = 0;
	virtual void visit(stmntSeq* node) = 0;
	virtual void visit(stmntFct* node) = 0;
	virtual void visit(stmntAtomic* node) = 0;
	virtual void visit(stmntDStep* node) = 0;
	virtual void visit(stmntAsgn* node) = 0;
	virtual void visit(stmntIncr* node) = 0;
	virtual void visit(stmntDecr* node) = 0;
	virtual void visit(stmntPrint* node) = 0;
	virtual void visit(stmntPrintm* node) = 0;
	virtual void visit(stmntAssert* node) = 0;
	virtual void visit(stmntExpr* node) = 0;
	virtual void visit(stmntElse* node) = 0;
	virtual void visit(stmntWait* node) = 0;
	virtual void visit(stmntWhen* node) = 0;
	virtual void visit(varDecl* node) = 0;
	virtual void visit(chanDecl* node) = 0;
	virtual void visit(tdefDecl* node) = 0;
	virtual void visit(mtypeDecl* node) = 0;
	virtual void visit(inlineDecl* node) = 0;
	virtual void visit(procDecl* node) = 0;
	virtual void visit(initDecl* node) = 0;
	virtual void visit(expr* node) = 0;
	virtual void visit(exprCond* node) = 0;
	virtual void visit(exprRArg* node) = 0;
	virtual void visit(exprRArgVar* node) = 0;
	virtual void visit(exprRArgEval* node) = 0;
	virtual void visit(exprRArgConst* node) = 0;
	virtual void visit(exprArgList* node) = 0;
	virtual void visit(exprRun* node) = 0;
	virtual void visit(exprConst* node) = 0;
	virtual void visit(exprTimeout* node) = 0;
	virtual void visit(exprSkip* node) = 0;
	virtual void visit(exprTrue* node) = 0;
	virtual void visit(exprFalse* node) = 0;
	virtual void visit(exprPlus* node) = 0;
	virtual void visit(exprMinus* node) = 0;
	virtual void visit(exprTimes* node) = 0;
	virtual void visit(exprDiv* node) = 0;
	virtual void visit(exprMod* node) = 0;
	virtual void visit(exprGT* node) = 0;
	virtual void visit(exprLT* node) = 0;
	virtual void visit(exprGE* node) = 0;
	virtual void visit(exprLE* node) = 0;
	virtual void visit(exprEQ* node) = 0;
	virtual void visit(exprNE* node) = 0;
	virtual void visit(exprAnd* node) = 0;
	virtual void visit(exprOr* node) = 0;
	virtual void visit(exprBitwAnd* node) = 0;
	virtual void visit(exprBitwOr* node) = 0;
	virtual void visit(exprBitwXor* node) = 0;
	virtual void visit(exprLShift* node) = 0;
	virtual void visit(exprRShift* node) = 0;
	virtual void visit(exprPar* node) = 0;
	virtual void visit(exprCount* node) = 0;
	virtual void visit(exprUMin* node) = 0;
	virtual void visit(exprNeg* node) = 0;
	virtual void visit(exprBitwNeg* node) = 0;
	virtual void visit(exprLen* node) = 0;
	virtual void visit(exprFull* node) = 0;
	virtual void visit(exprNFull* node) = 0;
	virtual void visit(exprEmpty* node) = 0;
	virtual void visit(exprNEmpty* node) = 0;
	
};

class ASTVisitorInt {
public:
	virtual int visit(stmnt* node) = 0;
	virtual int visit(stmntChanRecv* node) = 0;
	virtual int visit(stmntChanSnd* node) = 0;
	virtual int visit(stmntOpt* node) = 0;
	virtual int visit(stmntIf* node) = 0;
	virtual int visit(stmntDo* node) = 0;
	virtual int visit(stmntBreak* node) = 0;
	virtual int visit(stmntGoto* node) = 0;
	virtual int visit(stmntLabel* node) = 0;
	virtual int visit(stmntSeq* node) = 0;
	virtual int visit(stmntFct* node) = 0;
	virtual int visit(stmntAtomic* node) = 0;
	virtual int visit(stmntDStep* node) = 0;
	virtual int visit(stmntAsgn* node) = 0;
	virtual int visit(stmntIncr* node) = 0;
	virtual int visit(stmntDecr* node) = 0;
	virtual int visit(stmntPrint* node) = 0;
	virtual int visit(stmntPrintm* node) = 0;
	virtual int visit(stmntAssert* node) = 0;
	virtual int visit(stmntExpr* node) = 0;
	virtual int visit(stmntElse* node) = 0;
	virtual int visit(stmntWait* node) = 0;
	virtual int visit(stmntWhen* node) = 0;
	virtual int visit(varDecl* node) = 0;
	virtual int visit(chanDecl* node) = 0;
	virtual int visit(tdefDecl* node) = 0;
	virtual int visit(mtypeDecl* node) = 0;
	virtual int visit(inlineDecl* node) = 0;
	virtual int visit(procDecl* node) = 0;
	virtual int visit(initDecl* node) = 0;
	virtual int visit(expr* node) = 0;
	virtual int visit(exprCond* node) = 0;
	virtual int visit(exprRArg* node) = 0;
	virtual int visit(exprRArgVar* node) = 0;
	virtual int visit(exprRArgEval* node) = 0;
	virtual int visit(exprRArgConst* node) = 0;
	virtual int visit(exprArgList* node) = 0;
	virtual int visit(exprRun* node) = 0;
	virtual int visit(exprConst* node) = 0;
	virtual int visit(exprTimeout* node) = 0;
	virtual int visit(exprSkip* node) = 0;
	virtual int visit(exprTrue* node) = 0;
	virtual int visit(exprFalse* node) = 0;
	virtual int visit(exprPlus* node) = 0;
	virtual int visit(exprMinus* node) = 0;
	virtual int visit(exprTimes* node) = 0;
	virtual int visit(exprDiv* node) = 0;
	virtual int visit(exprMod* node) = 0;
	virtual int visit(exprGT* node) = 0;
	virtual int visit(exprLT* node) = 0;
	virtual int visit(exprGE* node) = 0;
	virtual int visit(exprLE* node) = 0;
	virtual int visit(exprEQ* node) = 0;
	virtual int visit(exprNE* node) = 0;
	virtual int visit(exprAnd* node) = 0;
	virtual int visit(exprOr* node) = 0;
	virtual int visit(exprBitwAnd* node) = 0;
	virtual int visit(exprBitwOr* node) = 0;
	virtual int visit(exprBitwXor* node) = 0;
	virtual int visit(exprLShift* node) = 0;
	virtual int visit(exprRShift* node) = 0;
	virtual int visit(exprPar* node) = 0;
	virtual int visit(exprCount* node) = 0;
	virtual int visit(exprUMin* node) = 0;
	virtual int visit(exprNeg* node) = 0;
	virtual int visit(exprBitwNeg* node) = 0;
	virtual int visit(exprLen* node) = 0;
	virtual int visit(exprFull* node) = 0;
	virtual int visit(exprNFull* node) = 0;
	virtual int visit(exprEmpty* node) = 0;
	virtual int visit(exprNEmpty* node) = 0;
};


#endif
