#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <assert.h>
#include <iostream>

#include "automata.h"
#include "symbols.h"
#include "expression.h"


/**
 * Creates a transition and adds it to the node list of the fsm.
 */
fsmTrans* fsmNode::createFsmTrans(astNode* expression, int lineNb) {
	fsmTrans* newTrans = new fsmTrans(this, expression, lineNb);
	this->trans.push_back(newTrans);
	parent->trans.push_back(newTrans);
	return newTrans;
}

fsmTrans* fsmNode::createFsmTrans(astNode* expression, fsmNode* target, int lineNb) {
	fsmTrans* newTrans = createFsmTrans(expression, lineNb);
	newTrans->setTargetNode(target);
	return newTrans;
}

/**
 * Copies and FSM transition and add it to the transition list of an FSM and of the transition list of the corresponding source node in this FSM.
 */
fsmTrans* fsmNode::copyFsmTrans(const fsmTrans* trans) {
	return createFsmTrans(trans->getExpression(), trans->getLineNb());
}

fsmNode::fsmNode(int flags, int lineNb, fsm* parent) {
	this->parent = parent;
	this->flags = flags;
	this->lineNb = lineNb;
}

void fsmNode::addTransition(fsmTrans* trans) {
	assert(std::find(this->trans.begin(), this->trans.end(), trans) == this->trans.end());
	this->trans.push_back(trans);
}

void fsmNode::removeTransition(fsmTrans* trans) {
	assert(std::find(this->trans.begin(), this->trans.end(), trans) != this->trans.end());
	this->trans.remove(trans);
}

void fsmNode::detachTransitions(void) {
	trans.clear();
}


void fsmNode::addInputTransition(fsmTrans* trans_in) {
	assert(std::find(this->trans_in.begin(), this->trans_in.end(), trans_in) == this->trans_in.end());
	this->trans_in.push_back(trans_in);
}

void fsmNode::removeInputTransition(fsmTrans* trans_in) {
	assert(std::find(this->trans_in.begin(), this->trans_in.end(), trans_in) != this->trans_in.end());
	this->trans_in.remove(trans_in);
}

const std::list<fsmTrans *> & fsmNode::getTransitions(void) const {
	return trans;
}

const std::list<fsmTrans *> & fsmNode::getInputTransitions(void) const {
	return trans_in;
}

void fsmNode::addFlags(unsigned int flags) {
	this->flags |= flags;
}

unsigned int fsmNode::getFlags(void) const {
	return flags;
}

void fsmNode::setLineNb(int line) {
	lineNb = line;
}

int fsmNode::getLineNb(void) const {
	return lineNb;
}

void fsmNode::orderAcceptTransitions(void) {
	
}

fsmNode::operator std::string(void) const {
	std::string res = "";
	for(auto t : trans)
		res += std::string(*t);
	return res;
}

/*
void fsmNode::printFsmNode(ptList printed, int level) {
	printed = listAdd(printed, this);
	spaces(level);
	printf("NL%03d", lineNb);
	if(flags != 0) printf(", flags:%s%s%s%s.", (flags & N_ACCEPT) == N_ACCEPT ? " accept" : "", (flags & N_END) == N_END ? " end" : "", (flags & N_PROGRESS) == N_PROGRESS ? " progress" : "", (flags & N_ATOMIC) == N_ATOMIC ? " atomic" : "");
	ptList tmp = trans_in;
	printf("   [in:");
	while(tmp) {
		printf("  %03d", ((fsmTrans*)tmp->value)->lineNb);
		tmp = tmp->next;
	}
	printf("]\n");
	ptList lTrans = trans;
	fsmTrans* trans;
	while(lTrans != nullptr) {
		trans = (fsmTrans*) lTrans->value;
		spaces(level);
		printf("  ----(TL%03d, %s, %s", trans->lineNb, trans->expression ? expNode::getExpTypeName(trans->expression->type) : "no expression", trans->hasFeatures ? "" : "no feature expression");
		//printBool(trans->features);
#ifdef STOCHASTIC
		printf(", %f", trans->expression ? trans->expression->prob : 1);
#endif
#ifdef CEGARTRANS
		printf(" (originally: ");
		//printBool(trans->origFeatures);
		printf(")");
#endif
		printf(")---> ");
		if(trans->target) {
			if(!listFind(printed, trans->target)) {
				printf("\n");
				trans->target->printFsmNode(printed, level + LEVEL_STEP);
			} else {
				printf("NL%03d\n", trans->target->lineNb);
			}
		} else {
			printf("(loose end)\n");
		}
		lTrans = lTrans->next;
	}
}*/

fsmTrans::fsmTrans(fsmNode* source, astNode* expression, int lineNb){
	this->source = source;
	this->target = nullptr;
	this->expression = expression;
	this->lineNb = lineNb;
}

/**
 * Destroys a transition; but not the attached nodes.
 */
fsmTrans::~fsmTrans(){
	if(expression) 
		delete expression;
}

void fsmTrans::setTargetNode(fsmNode* target) {
	assert(!this->target);
	assert(target);
	
	if(this->target) {
		this->target->removeInputTransition(this);
	}

	this->target = target;
	this->target->addInputTransition(this);
}

fsmNode * fsmTrans::getTargetNode(void) const {
	return target;
}

void fsmTrans::setSourceNode(fsmNode *source) {
	assert(!this->source);
	assert(source);
	
	if(this->source) {
		this->source->removeTransition(this);
	}

	this->source = source;
	this->source->addTransition(this);
}

fsmNode * fsmTrans::getSourceNode(void) const {
	return source;
}

astNode * fsmTrans::getExpression(void) const {
	return this->expression;
}

void fsmTrans::setExpression(astNode *expression) {
	this->expression = expression;
}

void fsmTrans::setLineNb(int line) {
	lineNb = line;
}

int fsmTrans::getLineNb(void) const {
	return lineNb;
}

void fsmTrans::resolveVariables(symTabNode* global, symTabNode* local, const mTypeNode* mTypes) const{
	if(expression) 
		expression->resolveVariables(global, mTypes, local);
}

fsmTrans::operator std::string(void) const {
	return expression? std::string(*expression) : "";
}

/*
 * FINITE STATE MACHINES (FSMs)
 * * * * * * * * * * * * * * * * * * * * * * * */



fsm::fsm(){
	init = nullptr;
	symTab = nullptr;
}

/**
 * Destroys an FSM and all that's linked to it.
 */
fsm::~fsm(){
	for(fsmNode* node : nodes) delete node;
	for(fsmTrans* trans : trans) delete trans;
	if(init) delete init;
	if(symTab) delete symTab;
}

/**
 * Destroys the FSM, but not the invidivual nodes transitions or the symtab.
 */
void fsm::destroySkeleton() {
	nodes.clear();
	trans.clear();
	looseEnds.clear();
	looseBreaks.clear();
	looseGotos.clear();
	labeledNodes.clear();
}

void fsm::merge(fsm* child) {
	nodes.merge(child->nodes);
	trans.merge(child->trans);
	looseBreaks.merge(child->looseBreaks);
	looseEnds.merge(child->looseEnds);
	
	for(auto& elem : child->labeledNodes) 
		labeledNodes.insert(elem);
	for(auto& elem : child->looseGotos) 
		looseGotos[elem.first].merge(elem.second);

	child->destroySkeleton();

	// Add the info of the statement FSM to the global one
	symTab = symTabNode::merge(symTab, child->symTab);
	child->symTab = nullptr;

	if(!init)
		init = child->init;
	child->init = nullptr;
}


/**
 * Creates a node and adds it to the node list of the fsm.
 * The node has to be manually attached to a transition.
 */
fsmNode* fsm::createFsmNode(int flags, int lineNb, const std::list<std::string>& labels) {
	fsmNode* node = new fsmNode(flags, lineNb, this);
	for(std::string l : labels)
		this->labeledNodes[l] = node;
	nodes.push_back(node);
	return node;
}

fsmNode* fsm::createFsmNode(int flags, int lineNb) {
	fsmNode* node = new fsmNode(flags, lineNb, this);
	nodes.push_back(node);
	return node;
}

/**
 * Copies and FSM node and add it to the node list of an FSM.
 */
fsmNode* fsm::copyFsmNode(const fsmNode* node) {
	return createFsmNode(node->getFlags(), node->getLineNb());
}

void fsm::setSymTab(symTabNode *sym) {
	symTab = sym;
}

symTabNode * fsm::getSymTab(void) const {
	return symTab;
}

void fsm::setInitNode(fsmNode* init) {
	this->init = init;
}

fsmNode * fsm::getInitNode(void) const {
	return init;
}

const std::list<fsmNode *> & fsm::getNodes(void) const {
	return nodes;
}

/**
 * Removes transitions for which the featureValue is false.
 */
/*
void fsm::project(void) {
	for(auto node : nodes){
		(node)->filterTransitionLists();
	}
}*/

/**
 * For states with several transitions leaving, those leading to accepting
 * states will be placed on top of the list.
 */
/*
void fsm::orderAcceptTransitions(void) {
	ptList node = nodes;
	ptList trans = nullptr;
	ptList newTrans = nullptr;
	while(node) {
		trans = ((fsmNode*) node->value)->trans;
		newTrans = nullptr;
		while(trans) {
			if(((fsmTrans*) trans->value)->target && ((fsmTrans*) trans->value)->target->flags & fsmNode::N_ACCEPT == fsmNode::N_ACCEPT) {
				newTrans = listAddHead(newTrans, trans->value);
			} else {
				newTrans = listAdd(newTrans, trans->value);
			}
			trans = trans->next;
		}

		listDestroy(((fsmNode*) node->value)->trans);
		((fsmNode*) node->value)->trans = newTrans;
		node = node->next;
	}

	for(auto node : nodes)
		node->orderAcceptTransitions();
}*/

/**
 * Resolves variable names in all expressions of an fsm.  See
 * resolveVariableNamesInExpression() for more info.
 */
void fsm::resolveVariables(symTabNode* global, const mTypeNode* mTypes) const {
	for(auto trans : trans)
		trans->resolveVariables(global, symTab, mTypes);
}

unsigned int fsm::processVariables(symTabNode* global, const mTypeNode* mTypes, unsigned int offset, bool isGlobal) const {
	return symTab->processVariables(global, mTypes, offset, isGlobal);
}

/*
void fsm::printFsm(int level, const std::string& title)  {
	spaces(level);
	int nbnodes = listCount(nodes);
	int nbtrans = listCount(transitions);
	if(title) printf("FSM [%s], %d node(s), %d transition(s):\n", title, nbnodes, nbtrans);
	if(symTab) symTab->printSymTab(level, title);
	if(labels) {
		spaces(level);
		printf("Labels:\n");
		ptLList node = labels;
		while(node) {
			spaces(level);
			printf(" - NL%03d <-- %s\n", ((fsmNode*) node->value)->lineNb, node->label);
			node = node->next;
		}
	}
	if(looseEnds) {
		spaces(level);
		printf("Loose ends:\n");
		ptList node = looseEnds;
		while(node) {
			spaces(level);
			printf(" - TL%03d\n", ((fsmTrans*) node->value)->lineNb);
			node = node->next;
		}
	}
	if(looseBreaks) {
		spaces(level);
		printf("Loose breaks:\n");
		ptList node = looseBreaks;
		while(node) {
			spaces(level);
			printf(" - TL%03d\n", ((fsmTrans*) node->value)->lineNb);
			node = node->next;
		}
	}
	if(looseGotos) {
		spaces(level);
		printf("Loose GOTOs:\n");
		ptLList node = looseGotos;
		while(node) {
			spaces(level);
			printf(" - NL%03d --> %s\n", ((fsmTrans*) node->value)->lineNb, node->label);
			node = node->next;
		}
	}
	spaces(level);
	printf("Transitions:\n");
	ptList printed = listAdd(nullptr, nullptr);
	if(init) init->printFsmNode(printed, level);
	listDestroy(printed);
	return;
}*/

fsm::operator std::string(void) const {
	//std::string res = symTab? std::string(*symTab) : "";
	return std::string(*init);
}

/**
 * The input is an fsm prefix!! This prefix has some loose ends (outgoing transitions) that
 * have to be
 */
fsm* fsm::stmnt2fsm(astNode* stmnt, symTabNode* symTab) {

	//formula.boolFctResult = false;

	// Test whether feature expression.
	// When in spin mode, then the feature variables will be of type BOOL, not FEATURE.  The function
	//   will thus always return !.isFeatureExpression.
	// When in optimised spin mode, the feature variables will be of type FEATURE, and
	if(stmnt->getType() == astNode::E_STMNT_EXPR){
		delete stmnt;
		return this;
	} 
	else 
	{
		// First unwrap the statement if its in a label statement
		std::list<std::string> labels;
		unsigned int flag = 0;		// Flags are determined by labels
		// child[0] = expNode::E_STMNT_*, sVal = the label of child[0]
		while(stmnt->getType() == astNode::E_STMNT_LABEL) { 
			std::string label = static_cast<stmntGoto*>(stmnt)->getLabel();
			if(label == "accept") 		flag |= fsmNode::N_ACCEPT;
			if(label == "end") 			flag |= fsmNode::N_END;
			if(label == "progress") 	flag |= fsmNode::N_PROGRESS;
			labels.push_back(label);
			astNode* temp = stmnt->detachChild0();
			delete stmnt;
			stmnt = temp;
		}

		// Most statements will create a new node to which the loose ends of the global FSM are attached.
		// When a new node is created, it will be labelled, and loose gotos have to be connected to this.
		// The other statements will have to deal with the loose ends themselves.
		fsmNode* newNode;
		if(stmnt->getType() != astNode::E_STMNT_BREAK && stmnt->getType() != astNode::E_STMNT_SEQ && 
		stmnt->getType() != astNode::E_STMNT_ATOMIC && stmnt->getType() != astNode::E_STMNT_GOTO) {
			// Create the node for this statement.
			newNode = createFsmNode(flag, stmnt->getLineNb(), labels);
			// If the fsm has not yet an init state, the new node will become it.
			if(!init) init = newNode;
			// Connect the loose ends of the prefix to the new node.
			for(auto looseEnd : looseEnds) {
				assert(looseEnd->getTargetNode() == nullptr);
				looseEnd->setTargetNode(newNode);
			}

			// Connect the loose GOTOs of the prefix to the new node
			//iterate over the label of the node
			for(std::string& label : labels) {
				//get the goto transitions that lead to the label
				const std::list<fsmTrans*>& looseGoto = looseGotos[label];
				//connect the goto transitions and the labelled node
				for(fsmTrans* elem : looseGoto)
					elem->setTargetNode(newNode);
				//erase the goto (they have been connected to the labelled node)
				looseGotos.erase(label);
			}
		}

		// The above code as well as the code in the GOTO case will be able to deal
		// with goto/labels that are within a single sequence.  It will not connect
		// gotos and labels spread over several (as in: IF..FI, DO..OD and {..}).
		// So all new labels or GOTOs created in subsequences will be put into these
		// two lists, which are then treated at the end.
		std::map<std::string, fsmNode*> newLabeledNodes;
		std::map<std::string, std::list<fsmTrans*>> newGotos;

		// Figure out which transitions will originate in the newNode (based on the current statement).
		switch(stmnt->getType()) {
			case astNode::E_STMNT_CHAN_RCV:	// child[0] = expNode::E_VARREF, child[1] = expNode::E_EXPR_*
			case astNode::E_STMNT_CHAN_SND:	// child[0] = expNode::E_VARREF, child[1] = expNode::E_EXPR_*
			case astNode::E_STMNT_ASGN:		// child[0] = expNode::E_VARREF, child[1] = expNode::E_EXPR_*
			case astNode::E_STMNT_INCR:		// child[0] = expNode::E_VARREF
			case astNode::E_STMNT_DECR:		// child[0] = expNode::E_VARREF
			case astNode::E_STMNT_PRINT:	// child[0] = expNode::E_ARGLIST, sVal = the print string
			case astNode::E_STMNT_PRINTM:	// child[0] = expNode::E_VARREF
			case astNode::E_STMNT_EXPR:		// child[0] = expNode::E_EXPR_*
			case astNode::E_STMNT_ASSERT:	// child[0] = expNode::E_EXPR_*
			case astNode::E_STMNT_ELSE:		// empty											// The SPIN parser makes sure that an ELSE is properly placed!
			case astNode::E_STMNT_WAIT:
				{	// A transition leaves the new node and is labelled with the statement itself.  Becomes a loose end.
					fsmTrans* t = newNode->createFsmTrans(stmnt, stmnt->getLineNb());
					looseEnds.push_back(t);

				} break;

			/*case astNode::E_STMNT_WHEN:
				{	// A transition leaves the new node and is labelled with the statement itself.  Becomes a loose end.
					fsmTrans* t = newNode->createFsmTrans(stmnt, stmnt->getLineNb());
					looseEnds.push_back(t);
					stmnt2fsm(stmnt->getChild1(), symTab);
				} break;
*/
			case astNode::E_STMNT_ATOMIC:	// fsm = fsm of this sequence
			case astNode::E_STMNT_SEQ:		// fsm = fsm of this sequence
				{	// Feature-related checks

					fsm* childFsm = stmnt->getChildFsm();
					fsmNode* init = childFsm->getInitNode();
					
					// Sanity check; a sequence must at least have a statement and the initial one cannot be labelled
					//assert(!childFsm->hasLooseFeatures() && childFsm->getInitNode());
					// if( stmnt->childFsm->init->labels[0]) failure("Remove the label '%s' at line %d.  The first statement in block cannot be labelled (label the block instead).\n", stmnt->childFsm->init->labels[0], stmnt->childFsm->init->lineNb);

					// The labels we calculated before have to be added to the (unlabelled) initial state of the block.
					for(auto label : labels) this->labeledNodes[label] = init;

					// In case of an atomic sequence, the inner nodes (excl. the initial) of the sequence have to be flagged as such
					if(stmnt->getType() == astNode::E_STMNT_ATOMIC) {
					//if(stmnt->childFsm->looseBreaks) failure("Problem at line %d: there can be no break statements in atomic blocks\n", stmnt->getLineNb());
						std::list<fsmNode*> nodes = childFsm->getNodes();
						nodes.remove(init);
						for(auto node : nodes) {
							node->addFlags(fsmNode::N_ATOMIC);
							// if(!((fsmNode*) node->value)->trans || ((fsmNode*) node->value)->trans->next) failure("Problem at line %d: atomic blocks cannot have control flow statements.\n", stmnt->getLineNb());
							// if(((fsmTrans*) ((fsmNode*) node->value)->trans->value)->features) failure("Problem at line %d: atomic blocks cannot contain feature expressions.\n", stmnt->getLineNb());
						}
					}

					for(auto& elem : childFsm->labeledNodes) newLabeledNodes.insert(elem);
					for(auto& elem : childFsm->looseGotos) newGotos[elem.first].merge(elem.second);
					// The loose ends of the global FSM are connected to the init state of the sequence FSM.
					for(auto looseEnd : looseEnds)
						looseEnd->setTargetNode(childFsm->init);
					looseEnds.clear();

					merge(childFsm);
					delete stmnt;

				} break;

			case astNode::E_STMNT_GOTO:		// sVal = the label to go to
				{	// If there are no loose ends, then the goto node is alone in an option, and we
					// have to create a node (with a loose end) for it after all.
					if(looseEnds.empty()) {
						assert(!init && !nodes.empty() && !trans.empty());
						init = createFsmNode(flag, stmnt->getLineNb());
						looseEnds.push_back(init->createFsmTrans(new exprSkip(stmnt->getLineNb()), stmnt->getLineNb()));
					}

					// The GOTO statement could not be labelled.
					assert(labels.empty());
					// Connect the GOTO to its target (if its known)
					fsmNode* labeledNode = this->labeledNodes[static_cast<stmntGoto*>(stmnt)->getLabel()];
					for(auto looseEnd : looseEnds) {
						// When the label already exists, we connect the loose ends to that label.
						if(labeledNode) looseEnd->setTargetNode(labeledNode);
						// If not, then we add the to the list of loose GOTOs.
						else looseGotos[static_cast<stmntGoto*>(stmnt)->getLabel()].push_back(looseEnd);
					}

					looseEnds.clear();
					delete stmnt;
				} break;

			case astNode::E_STMNT_BREAK:		// empty
				{	// If there are no loose ends, then the break node is alone in an option, and we
					// have to create a node for it after all.
					if(looseEnds.empty()) {
						// Check whether the global fsm is really empty
						assert(!init && !nodes.empty() && !trans.empty());
						init = createFsmNode(flag, stmnt->getLineNb());
						looseBreaks.push_back(init->createFsmTrans(new exprSkip(stmnt->getLineNb()), stmnt->getLineNb()));
					// Otherwise, the loose ends will have to be redirected so that they end up
					// pointing to the end state of the outermost DO..OD.  This is done by
					// removing them from the loose ends list and adding them to the loose breaks list
					} else {
						// The BREAK statement could be labelled!  While this is permitted by SPIN,
						// for the time being we will not support this.
						assert(labels.empty());

						looseBreaks.merge(looseEnds);
					}
					delete stmnt;
				} break;

			case astNode::E_STMNT_IF:		// child[0] = expNode::E_STMNT_OPT (contains an fsm)
			case astNode::E_STMNT_DO:		// child[0] = expNode::E_STMNT_OPT (contains an fsm)
									// Difference between DO and IF:
									// -> The loose ends of the DO option FSMs will point back to the newNode instead of becoming new loose ends
									// -> The actual loose ends will be obtained by searching for the break statement inside
									//    the option FSMs

				{	// When the whole if/do is annotated, we create a separate startNode
					// and the transition from the newNode leads there, labelled with the
					// annotation features.  Otherwise, the startNode is the newNode
					fsmNode* startNode = newNode;

					// In the case of a DO..OD, we create a second node, the end node.
					// A "skip" transition leads from there as a new loose end.
					fsmNode* endNode = nullptr;
					astNode::Type type = stmnt->getType();
					if(type == astNode::E_STMNT_DO) {
						endNode = createFsmNode(0, stmnt->getLineNb());
						fsmTrans* t = endNode->createFsmTrans(new exprSkip(stmnt->getLineNb()), stmnt->getLineNb());
						looseEnds.push_back(t);
					}

					//short int hasFeatureExp = -1; // -1 == undecided; 0 = no label; 1 = hasLabel
					//fsmTrans* elseTrans = nullptr;
					//bool elseVal = true;
					
					//bool elseSet = false;

					// The option block is a list of fsms
					astNode* option = stmnt;
/*#ifdef STOCHASTIC
					int option_nbr = 0;
					expNode* option_iter = option;
					while(option_iter) {
						option_nbr++;
						option_iter = option_iter->children[0];
					}
#endif*/
					fsm* childFsm = nullptr;
					while(option && (childFsm = option->getChildFsm())) { // expNode::E_STMNT_OPT: child[0] = expNode::E_STMNT_OPT (next option; or nullptr), fsm = fsm of this option
						// Sanity checks
						// There cannot be a feature expression
						// The FSM should have an init state, but without labels (the firs statement in an option block should not be labelled)
						// if(childFsm->init->labels[0]) failure("Remove the label '%s' at line %d.  The first statement in an 'if' or in a 'do' cannot be labelled (label the if instead).\n", childFsm->init->labels[0], childFsm->init->lineNb);
						// There should be exactly one transition from the init state
						// Restriction loosened and handeled by subsequent code: if( childFsm->init->trans->next) failure("Bug: the initial state of FSM of the option node at line %d (statement line %d) has two leaving transitions.\n", option->lineNb, stmnt->getLineNb());
						
						// Keep the transition leaving the init state and remove the init state
						const std::list<fsmTrans*>& initTransList = childFsm->init->getTransitions();
						fsmTrans* initTrans = initTransList.front();
/*#ifdef STOCHASTIC
						if(!initTrans->hasFeatures && !hasFeatureExp && initTrans->expression && initTrans->expression->prob == 1)
							initTrans->expression->prob = initTrans->expression->prob / option_nbr;
#endif*/
						// If there are multiple transitions, initTransList contains them
						if(!initTransList.empty()) childFsm->init->detachTransitions(); // do not destroy this list, it will be reused
						childFsm->nodes.remove(childFsm->init);
						delete childFsm->init;
						childFsm->init = nullptr;

						// Check whether this transition has a feature expression
						//if(hasFeatureExp == -1) hasFeatureExp = initTrans->hasFeatures() ? 1 : 0;

						// In case of an else, we perform some basic checks and store the 'else' transition for use later
						/*if(initTrans->getExpression()->getType() == astNode::E_STMNT_ELSE) {
							//assert(!initTransList.empty() && !initTrans->hasFeatures() && elseTrans == nullptr);
							elseTrans = initTrans;

						// If its not an else then we accumulate it's feature expression (if there is one) for use later
						} else {*/

							/*if(!initTrans->hasFeatures()) assert(hasFeatureExp == 0);
							else {
								assert(hasFeatureExp == 1);
								if(initTrans->hasFeatures()) 
									elseBF *= ~initTrans->getFeatures();
								elseVal &= ~initTrans->hasFeatures();
								elseSet = true;
							}*/
						//}

						// This transition (or these transitions) will be connected to the startNode (the IF or DO node).
						if(initTransList.empty()) 
							initTrans->setSourceNode(startNode);
						else 
							for(auto trans : initTransList) trans->setSourceNode(startNode);

						// The option FSM nodes/transitions are added to those of the global FSM
						assert(init);

						for(auto& elem : childFsm->labeledNodes) newLabeledNodes.insert(elem);
						for(auto& elem : childFsm->looseGotos) newGotos[elem.first].merge(elem.second);
				

						if(stmnt->getType() == astNode::E_STMNT_DO) {
							
							// The loose ends of the global FSM are connected to the init state of the sequence FSM.
							for(auto looseEnd : childFsm->looseEnds)
								looseEnd->setTargetNode(startNode);
							childFsm->looseEnds.clear();

							for(auto looseBreak : childFsm->looseBreaks)
								looseBreak->setTargetNode(endNode);
							childFsm->looseBreaks.clear();
						}

						merge(childFsm);

						// The option is no longer needed and can be freed
						astNode* temp = option->getChild0();
						option->detachChild0();
						delete option;
						option = temp;
					} // end while (iterating over the option blocks)

					// If all transitions were labelled by features, and there is an else transition;
					// it will be labelled with the negation of the other feature expressions.
					// This is only done if the labels are individual, meaning not in the case where the
					// whole if/do is labelled (in which case all transitions, even the else get this label).
					/*if(hasFeatureExp == 1 && elseTrans) {
						assert(elseSet);

						//elseTrans->setFeatures(elseBF);

						// Furthermore, the transition cannot be an else anymore, since it might never
						// be executable, instead we make it into a skip
						delete elseTrans->getExpression();
						elseTrans->setExpression(new exprSkip(elseTrans->getLineNb()));
					}*/

					stmnt->detachChild0();
					delete stmnt;

				} break;

			default:
				std::cout << "The statement at line "<< stmnt->getLineNb() <<" (of type "<< stmnt->getType() << ") cannot be treated.\n";
				break;
		}

		// There are some new loose GOTOs in separate sequence branches
		// Look in the FSM labels and in the new labels whether they can
		// be found
		if(!newGotos.empty()) {
			std::map<std::string, std::list<fsmTrans*>> keepGotos;
			fsmNode* labeledNode = nullptr;

			for(auto looseGoto : newGotos) {
				assert(!looseGoto.second.empty()); 

				if((labeledNode = labeledNodes[looseGoto.first]))
					for(auto labeledTrans : looseGoto.second)
						labeledTrans->setTargetNode(labeledNode);
				else keepGotos.insert(looseGoto);
			}
			newGotos = keepGotos;
		}

		// There are new labelled nodes in the sequence branches.
		// Look in the loose GOTOs of the FSM (not in the new GOTOs,
		// that's been taken care of just before) whether they are
		// referenced.
		if(!newLabeledNodes.empty()) {
			std::map<std::string, std::list<fsmTrans*>> keepGotos;
			fsmNode* labeledNode = nullptr;

			for(auto looseGoto : looseGotos) {
				assert(!looseGoto.second.empty()); 

				if((labeledNode = newLabeledNodes[looseGoto.first]))
					for(auto labeledTrans : looseGoto.second)
						labeledTrans->setTargetNode(labeledNode);
				else keepGotos.insert(looseGoto);
			}
			looseGotos = keepGotos;
		}

		for(auto& elem : newLabeledNodes) 
			labeledNodes.insert(elem);
		for(auto& elem : newGotos)
			looseGotos[elem.first].merge(elem.second);
	}
	return this;
}