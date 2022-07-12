#include "ASTtoFSM.hpp"

#include "symbols.hpp"
#include "ast.hpp"
#include "automata.hpp"

ASTtoFSM::ASTtoFSM() 
    : skip(false)
{}

fsm* ASTtoFSM::astToFsm(const symTable* symTab, const stmnt* program) {
    
    res = new fsm(symTab);
    
    program->acceptVisitor(this);
    //assert(current.size() == 1);
    return res;
}

void ASTtoFSM::_connect(std::list<fsmEdge*>& edges, fsmNode* target){
    for(auto edge : edges) {
        assert(edge->getTargetNode() == nullptr);
        edge->setTargetNode(target);
    }
    edges.clear();
}

void ASTtoFSM::_label(fsmNode* node){
    for(auto label : labels)
        labeledNodes[label] = node;
    labels.clear();
}

void ASTtoFSM::_looseEnd(const stmnt* node) {
    looseEnds.push_back(current->createfsmEdge(node->getLineNb(), node));
}

void ASTtoFSM::_looseBreak(const stmnt* node) {
    looseBreaks.push_back(current->createfsmEdge(node->getLineNb(), node));
}

void ASTtoFSM::visit(const stmnt* node)  {

        current = (res->createFsmNode(flags, node->getLineNb()));
        
        if(!init) init = current;

        _label(current);
        
        _connect(looseEnds, current);

        _looseEnd(node);


    node = node->getNext();
    if(node) {
        node->acceptVisitor(this);
    }
}

void ASTtoFSM::visit(const stmntOpt* node)  {

    node->getBlock()->acceptVisitor(this);
    auto next = node->getNext();
    if(next) {
        next->acceptVisitor(this);
    }
}

void ASTtoFSM::visit(const stmntIf* node)  {
    
    std::list<fsmEdge*> flowLooseEnds;
    std::list<fsmEdge*> flowLooseBreaks;
    
    auto start = res->createFsmNode(flags, node->getLineNb());
    
    current = start;
    
    if(!init) init = current;

    _connect(looseEnds, current);

    auto opt = node->getOpts();
    while(opt){
        //opt->getBlock()->getType() == astNode::E_STMNT_ATOMIC? dynamic_cast<stmntAtomic*>(opt->getBlock())->getBlock() : opt->getBlock();
        auto trans = start->createfsmEdge(node->getLineNb(), new stmntExpr(new exprSkip(node->getLineNb()), node->getLineNb()));
        looseEnds.push_back(trans);
        
        skip = true;

        opt->acceptVisitor(this);

        assert(trans->getTargetNode());
        for(auto t : trans->getTargetNode()->getEdges()) {
            t->setSourceNode(start);
        }
        res->deleteNode(trans->getTargetNode());
    
        
        
        flowLooseEnds.merge(looseEnds);
        looseEnds.clear();
        flowLooseBreaks.merge(looseBreaks);
        looseBreaks.clear();

        opt = opt->getNextOpt();
    }

    looseEnds.merge(flowLooseEnds);
    looseBreaks.merge(flowLooseBreaks);

    auto next = node->getNext();
    if(next) {
        next->acceptVisitor(this);
    }
}

void ASTtoFSM::visit(const stmntDo* node)  {
    
    std::list<fsmEdge*> flowLooseEnds;
    std::list<fsmEdge*> flowLooseBreaks;

    auto start = res->createFsmNode(flags, node->getLineNb());
    current = start;
    if(!init) init = current;

    _connect(looseEnds, start);

    auto opt = node->getOpts();
    while(opt){
        //auto block = opt->getBlock()->getType() == astNode::E_STMNT_ATOMIC? dynamic_cast<stmntAtomic*>(opt->getBlock())->getBlock() : opt->getBlock();
        auto trans = start->createfsmEdge(node->getLineNb(), new stmntExpr(new exprSkip(node->getLineNb()), node->getLineNb()));
        looseEnds.push_back(trans);
        
        opt->acceptVisitor(this);

        assert(trans->getTargetNode());
        for(auto t : trans->getTargetNode()->getEdges()) {
            t->setSourceNode(start);
        }
        res->deleteNode(trans->getTargetNode());
        
        
        flowLooseEnds.merge(looseEnds);
        looseEnds.clear();
        flowLooseBreaks.merge(looseBreaks);
        looseBreaks.clear();

        opt = opt->getNextOpt();
    }

    _connect(flowLooseEnds, start);
    looseEnds.merge(looseBreaks);


    auto next = node->getNext();
    if(next) {
        next->acceptVisitor(this);
    }
}

void ASTtoFSM::visit(const stmntBreak* node)  {
    

        current = (res->createFsmNode(flags, node->getLineNb()));

        if(!init) init = current;
        
        _label(current);

        _connect(looseEnds, current);

        _looseBreak(node);


    auto next = node->getNext();
    if(next) {
        next->acceptVisitor(this);
    }
}

void ASTtoFSM::visit(const stmntGoto* node)  {

    current = (res->createFsmNode(flags, node->getLineNb()));

    if(!init) init = current;

    _connect(looseEnds, current);

    looseGotos[node->getLabel()].push_back(current->createfsmEdge(node->getLineNb(), node));

    auto next = node->getNext();
    if(next) {
        next->acceptVisitor(this);
    }
}

void ASTtoFSM::visit(const stmntLabel* node)  {
    std::string label = node->getLabel();
    if(label == "accept") 		flags |= fsmNode::N_ACCEPT;
    if(label == "end") 			flags |= fsmNode::N_END;
    if(label == "progress") 	flags |= fsmNode::N_PROGRESS;
    labels.push_back(label);
    labels.push_back(node->getLabel());

    node->getLabelled()->acceptVisitor(this);

    auto next = node->getNext();
    if(next) {
        next->acceptVisitor(this);
    }
}

void ASTtoFSM::visit(const stmntFct* decl)  {
    init = nullptr;
    auto curStmnt = decl->getBlock();
    curStmnt->acceptVisitor(this);
    res->addInitNode(decl->getFctName(), init);

    for(auto looseGotoList : looseGotos){
        auto labelledNode = labeledNodes[looseGotoList.first];
        assert(labelledNode);
        for(auto looseGoto : looseGotoList.second)
            looseGoto->setTargetNode(labelledNode);
    }
    looseGotos.clear();

    //assert(looseEnds.size() == 1);
    assert(looseGotos.size() == 0);
    assert(looseBreaks.size() == 0);
    looseEnds.clear();
    looseBreaks.clear();
    looseGotos.clear();


    auto next = decl->getNext();
    if(next) {
        next->acceptVisitor(this);
    }
}

void ASTtoFSM::visit(const varDecl* node) {
    auto next = node->getNext();
    if(next) {
        next->acceptVisitor(this);
    }
}

void ASTtoFSM::visit(const chanDecl* node) {
    auto next = node->getNext();
    if(next) {
        next->acceptVisitor(this);
    }
}

void ASTtoFSM::visit(const tdefDecl* node) {
    auto next = node->getNext();
    if(next) {
        next->acceptVisitor(this);
    }
}

void ASTtoFSM::visit(const mtypeDecl* node) {
    auto next = node->getNext();
    if(next) {
        next->acceptVisitor(this);
    }
}

void ASTtoFSM::visit(const stmntAtomic* node)  {
    flags |= fsmNode::N_ATOMIC;
    node->getBlock()->acceptVisitor(this);
    flags &= ~fsmNode::N_ATOMIC;
    auto next = node->getNext();
    if(next)
        next->acceptVisitor(this);
}

void ASTtoFSM::visit(const stmntDStep* node)  {
    flags |= fsmNode::N_DETERMINISTIC;
    node->getBlock()->acceptVisitor(this);
    flags &= ~fsmNode::N_DETERMINISTIC;
    auto next = node->getNext();
    if(next)
        next->acceptVisitor(this);
}

/*************************************************************/

void ASTtoFSM::visit(const stmntSeq* node) {
    node = node; assert(false);
}

void ASTtoFSM::visit(const inlineDecl* node) {
    node = node; assert(false);
}

void ASTtoFSM::visit(const procDecl* decl) {
    decl = decl; assert(false);
}

void ASTtoFSM::visit(const initDecl* node) {
    node = node; assert(false);
}

void ASTtoFSM::visit(const stmntChanRecv* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const stmntChanSnd* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const stmntAsgn* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const stmntIncr* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const stmntDecr* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const stmntPrint* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const stmntPrintm* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const stmntAssert* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const stmntExpr* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const stmntElse* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const stmntWait* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const stmntWhen* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const expr* node) {
    node = node;//expr will be attached to edges
}

void ASTtoFSM::visit(const exprCond* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprRArg* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprRArgVar* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprRArgEval* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprRArgConst* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprArgList* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprRun* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprConst* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprTimeout* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprSkip* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprTrue* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprFalse* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprPlus* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprMinus* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprTimes* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprDiv* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprMod* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprGT* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprLT* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprGE* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprLE* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprEQ* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprNE* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprAnd* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprOr* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprBitwAnd* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprBitwOr* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprBitwXor* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprLShift* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprRShift* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprPar* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprCount* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprUMin* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprNeg* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprBitwNeg* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprLen* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprFull* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprNFull* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprEmpty* node)  {
    node = node; assert(false);
}

void ASTtoFSM::visit(const exprNEmpty* node)  {
    node = node; assert(false);
}