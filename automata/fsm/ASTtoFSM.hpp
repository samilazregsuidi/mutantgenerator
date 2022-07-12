#ifndef AST_TO_FSM_H
#define AST_TO_FSM_H

#include "astVisitor.hpp"

#include <stack>
#include <list>
#include <map>

class symTable;

class fsm;
class fsmNode;
class fsmEdge;

class ASTtoFSM : public ASTConstVisitor {
public:
	ASTtoFSM();
	fsm* astToFsm(const symTable* symTab, const stmnt* program);

	void visit(const stmnt* node) override;
	void visit(const stmntChanRecv* node) override;
	void visit(const stmntChanSnd* node) override;
	void visit(const stmntOpt* node) override;
	void visit(const stmntIf* node) override;
	void visit(const stmntDo* node) override;
	void visit(const stmntBreak* node) override;
	void visit(const stmntGoto* node) override;
	void visit(const stmntLabel* node) override;
	void visit(const stmntSeq* node) override;
	void visit(const stmntFct* node) override;
	void visit(const stmntAtomic* node) override;
	void visit(const stmntDStep* node) override;
	void visit(const stmntAsgn* node) override;
	void visit(const stmntIncr* node) override;
	void visit(const stmntDecr* node) override;
	void visit(const stmntPrint* node) override;
	void visit(const stmntPrintm* node) override;
	void visit(const stmntAssert* node) override;
	void visit(const stmntExpr* node) override;
	void visit(const stmntElse* node) override;
	void visit(const stmntWait* node) override;
	void visit(const stmntWhen* node) override;
	void visit(const varDecl* node) override;
	void visit(const chanDecl* node) override;
	void visit(const tdefDecl* node) override;
	void visit(const mtypeDecl* node) override;
	void visit(const inlineDecl* node) override;
	void visit(const procDecl* node) override;
	void visit(const initDecl* node) override;
	void visit(const expr* node) override;
	void visit(const exprCond* node) override;
	void visit(const exprRArg* node) override;
	void visit(const exprRArgVar* node) override;
	void visit(const exprRArgEval* node) override;
	void visit(const exprRArgConst* node) override;
	void visit(const exprArgList* node) override;
	void visit(const exprRun* node) override;
	void visit(const exprConst* node) override;
	void visit(const exprTimeout* node) override;
	void visit(const exprSkip* node) override;
	void visit(const exprTrue* node) override;
	void visit(const exprFalse* node) override;
	void visit(const exprPlus* node) override;
	void visit(const exprMinus* node) override;
	void visit(const exprTimes* node) override;
	void visit(const exprDiv* node) override;
	void visit(const exprMod* node) override;
	void visit(const exprGT* node) override;
	void visit(const exprLT* node) override;
	void visit(const exprGE* node) override;
	void visit(const exprLE* node) override;
	void visit(const exprEQ* node) override;
	void visit(const exprNE* node) override;
	void visit(const exprAnd* node) override;
	void visit(const exprOr* node) override;
	void visit(const exprBitwAnd* node) override;
	void visit(const exprBitwOr* node) override;
	void visit(const exprBitwXor* node) override;
	void visit(const exprLShift* node) override;
	void visit(const exprRShift* node) override;
	void visit(const exprPar* node) override;
	void visit(const exprCount* node) override;
	void visit(const exprUMin* node) override;
	void visit(const exprNeg* node) override;
	void visit(const exprBitwNeg* node) override;
	void visit(const exprLen* node) override;
	void visit(const exprFull* node) override;
	void visit(const exprNFull* node) override;
	void visit(const exprEmpty* node) override;
	void visit(const exprNEmpty* node) override;

private:
	void _connect(std::list<fsmEdge*>& edges, fsmNode* target);
	void _label(fsmNode* node);
	void _looseEnd(const stmnt* node);
	void _looseBreak(const stmnt* node);

private:
	unsigned int flags;
	fsm* res;
	fsmNode *init;											 // The initial node
	fsmNode * current;
	//fsmNode *next;
	fsmNode* newNode;
	std::map<const stmnt*, fsmNode *> nodes;								 // List of ptFsmNode	- This list contains all nodes of the FSM in an arbitrary order.
	std::list<std::string> labels;
	std::map<std::string, fsmNode *> labeledNodes;			 // List of ptFsmNode	- This list is indexed by label and contains for each label the labelled node.
	std::list<fsmEdge *> trans;							 // List of fsmEdge	- This list contains all transitions of the FSM in an arbitrary order.
	std::list<fsmEdge *> looseEnds;						 // List of fsmEdge	- For model construction: contains those transitions that do not have an end state.
	std::list<fsmNode *> looseStarts;
	fsmEdge* prev;
	std::map<std::string, std::list<fsmEdge *>> looseGotos; // List of fsmEdge	- For model construction: contains those transitions (indexed by label name) that have yet to be connected to a state with this label.
	std::list<fsmEdge *> looseBreaks;						 // List of fsmEdge	- For model construction: contains those transitions that were generated because of a break statement and are waiting to be matched to a DO.
	//std::list<fsmEdge*> flowLooseEnds;
	//std::list<fsmEdge*> flowLooseBreaks;
	bool skip;
};

#endif
