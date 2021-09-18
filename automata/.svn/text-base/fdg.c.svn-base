#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "main.h"
#include "list.h"
#include "stack.h"
#include "boolFct.h"
#include "hashtableGen.h"
#include "symbols.h"
#include "automata.h"
#include "fdg.h"

ptFVT createFdgVisitedTrans(ptFdgTrans trans, ptBoolFct features) {
	ptFVT fvt = (ptFVT) malloc(sizeof(tFVT));
	fvt->trans = trans;
	fvt->features = features;
	return fvt;
}

ptFVT fvtVisited(void * table, ptFVT fvt) {
	ptList prevS = htSearch(table, fvt->trans->trans->lineNb);
	byte foundChar = 0;
	while(prevS) {
		ptFVT prev = (ptFVT) prevS->value;
		if(fvt->trans == prev->trans) {
			if(impliesWrtFD(fvt->features, prev->features)) {
				return prev;
			}
		}
		prevS = prevS->next;
	}
	return NULL;
}

void fvtInsert(void * table, ptFVT fvt) {
	ptList prevS = htSearch(table, fvt->trans->trans->lineNb);
	byte foundChar = 0;
	while(prevS) {
		ptFVT prev = (ptFVT) prevS->value;
		if(fvt->trans == prev->trans) {
			prev->features = addDisjunction(prev->features, fvt->features, 0, 1);
			return;
		}
		else
			prevS = prevS->next;
	}
	htInsert(table, fvt->trans->trans->lineNb, createFdgVisitedTrans(fvt->trans, fvt->features));
}

ptList fvtListAdd(ptList list, ptFdgTrans trans, ptBoolFct features) {
	if(!features) features = getTrue();
	ptList tmp = list;
	while(tmp) {
		ptFVT current = (ptFVT) tmp->value;
		if(current->trans == trans) {
			current->features = addDisjunction(current->features, features, 0, 1);
			return list;
		}
		tmp = tmp->next;
	}
	list = listAdd(list, createFdgVisitedTrans(trans, features));
	return list;
}

ptBoolFct fvtListFind(ptList list, ptFdgTrans trans) {
	ptList tmp = list;
	while(tmp) {
		ptFVT current = (ptFVT) tmp->value;
		if(current->trans == trans) {
			return current->features;
		}
		tmp = tmp->next;
	}
	return negateBool(getTrue());
}

ptList fvtListConstraint(ptList list, ptFdgTrans trans, ptBoolFct features) {
	ptList tmp = list;
	while(tmp) {
		ptFVT current = (ptFVT) tmp->value;
		if(current->trans == trans) {
			current->features = addConjunction(current->features, features, 0, 1);
			return list;
		}
		tmp = tmp->next;
	}
	return list;
}

ptLList copyDependencies(ptLList depends) {
	ptLList tmp = depends;
	ptLList copy = NULL;
	while(tmp) {
		ptLList tmp2 = (ptLList) tmp->value;
		ptLList copy_reads = NULL;
		while(tmp2) {
			copy_reads = llistAdd(copy_reads, tmp2->label, copyBool((ptBoolFct) tmp2->value));
			tmp2 = tmp2->next;
		}
		copy = llistAdd(copy, tmp->label, copy_reads);
		tmp = tmp->next;
	}
	return copy;
}

/* Inserts write <- [features] read into a list */
ptLList insertDependencies(ptLList into, char * write, char * read, ptBoolFct features, byte * modified) {
	if(!write || !read) return into;
	ptLList prevW = llistFind(into, write);
	if(!prevW) {
		into = llistAdd(into, write, llistAdd(NULL, read, features));
		if(modified) *modified = 1;
	}
	else {
		ptLList prevR = llistFind(prevW->value, read);
		if(!prevR) {
			prevW->value = llistAdd(prevW->value, read, features);
			if(modified) *modified = 1;
		}
		else {
			ptBoolFct prevF = (ptBoolFct) prevR->value;
			prevR->value = addDisjunction((ptBoolFct) prevR->value, features, 1, 1);
			if(modified && !equalsWrtFD(prevR->value, features)) {
				*modified = 1;
			}
		}
	}
	return into;
}

ptLList propagateDependenciesForward(ptLList from, ptLList to, ptBoolFct requiredFeatures, byte * modified) {
	if(!from) return to;
	ptLList tmp1 = NULL, tmp2 = NULL;
	ptLList tmpl1 = NULL, tmpl2 = NULL, prevR = NULL;
	char * c1, c2;
	if(modified) *modified = 0;
	ptBoolFct prevF = NULL;
	tmpl1 = to;
	while(tmpl1) { // for each c = [f1]x1, [f2]x2, [f3]x3, ... in TO
		tmp1 = (ptLList) tmpl1->value;
		while(tmp1) { // for each [fi]xi
			c1 = (char *) tmp1->label;
			tmpl2 = llistFind(from, c1);
			if(tmpl2) { // xi = [g1]y1, [g2]y2, [g3]y3, ... is in FROM
				tmp2 = (ptLList) tmpl2->value;
				while(tmp2) { // for each [gj]yj
					to = insertDependencies(to, tmpl1->label, tmp2->label, tmp2->value, modified);
					tmp2 = tmp2->next;
				}
			}
			tmp1 = tmp1->next;
		}
		tmpl1 = tmpl1->next;
	}
	tmpl2 = from;
	while(tmpl2) { // for each c = [f1]x1, [f2]x2, [f3]x3, ... in FROM
		if(!tmpl2->value) { // c = empty
			tmpl1 = to;
			while(tmpl1) { // condition
				prevR = llistFind((ptLList) tmpl1->value, tmpl2->label);
				if(prevR) {
					if(modified) {
						if(!isTautologyWrtFD((ptBoolFct) prevR->value))
							*modified = 1;
					}
					destroyBool((ptBoolFct) prevR->value);
					prevR->value = NULL;
				}
				else {
					if(modified) *modified = 1;
					tmpl1->value = llistAdd((ptLList) tmpl1->value, tmpl2->label, NULL);
				}
				tmpl1 = tmpl1->next;
			}
		}
		else {
			tmpl1 = llistFind(to, tmpl2->label);
			if(tmpl1) { // c = [g1]y1, [g2]y2, [g3]y3, ... is in TO
				tmp2 = (ptLList) tmpl2->value;
				while(tmp2) { // for each [fi]xi
					prevR = llistFind((ptLList) tmpl1->value, tmp2->label);
					if(!prevR) { // there does not exist yj = xi
						tmpl1->value = llistAdd(tmpl1->value, tmp2->label, tmp2->value);
					}
					else {
						prevF = (ptBoolFct) prevR->value;
						prevR->value = addDisjunction((ptBoolFct) prevR->value, addConjunction((ptBoolFct)tmp2->value, requiredFeatures, 1, 1), 0, 0);
						if(modified) {
							if(!equalsWrtFD(prevF, (ptBoolFct) prevR->value))
								*modified = 1;
						}
						destroyBool(prevF);
						prevF = NULL;
					}
					tmp2 = tmp2->next;
				}
			}
			else {
				if(modified)
					*modified = 1;
				to = llistAdd(to, tmpl2->label, tmpl2->value);
			}
		}
		tmpl2 = tmpl2->next;
	}
	return to;
}

ptFdg computeFeatureImportance(ptFdg fdg, ptList criticalTrans, ptList criticalVars) {
	ptList tmp = criticalTrans;
	while(tmp) {
		fdg = computeFeatureImportanceFromCriticalTrans(fdg, (ptFdgTrans) tmp->value, criticalVars);
		tmp = tmp->next;
	}
	return fdg;
}

ptList computeNewCriticalVars(ptFdgTrans trans, ptList criticalVars) {
	ptList acc = NULL;
	ptList acc_iter = NULL;
	byte found = 0;
	ptList cv_iter = criticalVars;
	while(cv_iter) {
		ptLList elt = llistFind(trans->writes, (char *) cv_iter->value);
		if(elt) {
			ptLList elt_iter = elt->value;
			if(!elt_iter) { // Conditional statement: all the referenced variables become critical.
				acc = listAdd(acc, elt->label);
			}
			else {
				found = 0;
				while(elt_iter) {
					if(strcmp(elt_iter->label, "CONST") != 0) {
						acc_iter = acc;
						while(acc_iter && !found) {
							if(strcmp(acc_iter->value, elt_iter->label) == 0)
								found = 1;
							acc_iter = acc_iter->next;
						}
						if(!found) {
							acc = listAdd(acc, elt_iter->label);
						}
					}
					elt_iter = elt_iter->next;
				}
			}
			elt_iter = NULL;
		}
		acc_iter = acc;
		found = 0;
		while(acc_iter && !found) {
			if(strcmp(acc_iter->value, (char *) cv_iter->value) == 0)
				found = 1;
			acc_iter = acc_iter->next;
		}
		if(!found) {
			acc = listAdd(acc, (char *) cv_iter->value);
		}
		cv_iter = cv_iter->next;
	}
	return acc;
}


ptFdg updateFeatureExpressions(ptFdg fdg) {
	void * table = createHashtable();
	ptList trans_iter = fdg->init->trans_out;
	ptStack stack = NULL;
	ptFdgTrans current;
	while(trans_iter) {
		current = (ptFdgTrans) trans_iter->value;
		stack = push(stack, current);
		htInsert(table, current->trans->lineNb, current->trans);
		trans_iter = trans_iter->next;
	}
	while(!empty(stack)) {
		current = (ptFdgTrans) pop(&stack);
		ptList trans_iter = current->target->trans_out;

		ptFdgTrans cumulator = NULL;
		ptBoolFct cumulatedFeatures = NULL;
		while(trans_iter) {
			ptFdgTrans new = (ptFdgTrans) trans_iter->value;
			if(new->trans->features) {
				if((trans_iter->next || cumulator)) {// || new->reachableCritical)) {
					ptBoolFct disjunction = copyBool(new->criticalFeatures);
					printf("Transition %03d -> %03d (", new->source->node->lineNb, new->target->node->lineNb);
					printBool(new->trans->features);
					printf("):\n");
					ptList rc_iter = new->reachableCritical;
					if(new->criticalFeatures) {
						printf("\tIs critical for the products: (");
						printBool(new->criticalFeatures);
						printf(")\n");
					}
					else printf("\tIsn't critical.\n");
					while(rc_iter) {
						ptList trans_iter_iter = trans_iter->next;
						ptFVT rc = (ptFVT) rc_iter->value;
						ptBoolFct non_redundant = getTrue();
						while(trans_iter_iter) {
							ptFdgTrans alternative = (ptFdgTrans) trans_iter_iter->value;
							non_redundant = addConjunction(non_redundant, negateBool(fvtListFind(alternative->reachableCritical, rc->trans)), 0, 0);
							trans_iter_iter = trans_iter_iter->next;
						}
						printf("\tIs the only alternative to reach the critical trans %03d --> %03d for products:", rc->trans->source->node->lineNb, rc->trans->target->node->lineNb); printBool(addConjunction(rc->features, non_redundant, 1, 1)); printf("\n");
						disjunction = addDisjunction(disjunction, addConjunction(rc->features, non_redundant, 0, 0), 0, 0);
						rc_iter = rc_iter->next;
					}
					printf("\tChanging features into ("); printBool(addConjunction(new->trans->features, disjunction, 1, 1)); printf(")\n");
					new->trans->features = addConjunction(new->trans->features, disjunction, 0, 0);
					cumulatedFeatures = addDisjunction(cumulatedFeatures, negateBool(new->trans->features), 0, 0);
				}
				else {
					printf("Transition %03d -> %03d: changing features ", new->source->node->lineNb, new->target->node->lineNb); printBool(new->trans->features); printf(" into "); printBool(addDisjunction(new->trans->features, cumulatedFeatures, 1, 1)); printf("\n");
					new->trans->features = addDisjunction(new->trans->features, cumulatedFeatures, 0, 0);
				}
			}
			if(!htFind(table, new->trans->lineNb, new)) {
				stack = push(stack, new);
				htInsert(table, new->trans->lineNb, new);
			}
			trans_iter = trans_iter->next;
		}
	}
}

/*
 * FEATURED DEPENDENCIES GRAPH (FDGs)
 * * * * * * * * * * * * * * * * * * */

ptFdgNode createFdgNode(ptFsmNode node) {
	ptFdgNode fnode = (ptFdgNode) malloc(sizeof(tFdgNode));
	if(!fnode)
		failure("[automata/createFdgNode] Out of memory.\n");
	fnode->node = node;
	fnode->reunion = NULL;
	fnode->trans_in = NULL;
	fnode->trans_out = NULL;
	fnode->reachables = negateBool(getTrue());
	return fnode;
}

ptFdgTrans createFdgTrans(ptFdgNode source, ptFdgNode target, ptFsmTrans trans) {
	ptFdgTrans fdgTrans = (ptFdgTrans) malloc(sizeof(tFdgTrans));
	if(!fdgTrans)
			failure("[automata/createFdgTrans] Out of memory.\n");
	fdgTrans->source = source;
	fdgTrans->target = target;
	fdgTrans->trans = trans;
	fdgTrans->writes = NULL;
	fdgTrans->criticalFeatures = negateBool(getTrue());
	fdgTrans->reachableCritical = NULL;
	return fdgTrans;
}


ptFdg computeFdg(ptFsm fsm, ptList criticalVars) { // Computes the FDG
	ptFdg fdg = (ptFdg) malloc(sizeof(tFdg));
	fdg->init = createFdgNode(fsm->init);
	fdg->nodes = listAdd(NULL, fdg->init);
	void * table = createHashtable();
	ptList transList = fsm->init->trans;
	ptList criticalTrans = NULL;
	while(transList) {
		criticalTrans = listConcat(criticalTrans, computeFdg_rec(criticalVars, fdg, fdg->init, &table, (ptFsmTrans) transList->value));
		transList = transList->next;
	}
#ifdef DEBUG
	printf("Found %d critical transitions:", listCount(criticalTrans));
	ptList cn_iter = criticalTrans;
	while(cn_iter) {
		printf(" %03d -> %03d", ((ptFdgTrans) cn_iter->value)->source->node->lineNb, ((ptFdgTrans) cn_iter->value)->target->node->lineNb);
		cn_iter = cn_iter->next;
	}
	printf(".\n");
#endif
	fdg = computeFeatureImportance(fdg, criticalTrans, criticalVars);
	fdg = updateFeatureExpressions(fdg);
	return fdg;
}

ptFdg reachables(ptFdg fdg) {
	ptStack stackN = push(NULL, fdg->init);
	ptStack stackT = push(NULL, fdg->init->trans_out);
	ptStack stackF = push(NULL, getTrue());
	fdg->init->reachables = getTrue();
	ptBoolFct disjunction;

	while(!empty(stackN)) {
		ptFdgNode curN = pop(&stackN);
		ptList curT = pop(&stackT);
		ptBoolFct curF = pop(&stackF);
		if(curT) { // otherwise trans->source is the initial state
			ptFdgTrans trans = (ptFdgTrans) curT->value;
			ptBoolFct features = trans->trans->features;
			ptBoolFct conjunction = addConjunction(curF, features, 1, 1);
			if(isSatisfiableWrtFD(conjunction)) {
				ptFdgNode nextN = trans->target;
				if(curT->next) {
					stackN = push(stackN, curN);
					stackT = push(stackT, curT->next);
					stackF = push(stackF, curF);
				}
				if(!impliesWrtFD(conjunction, nextN->reachables)) {
					nextN->reachables = addDisjunction(nextN->reachables, conjunction, 0, 1);
#ifdef DEBUG
					printf("Node %03d reachable by ", nextN->node->lineNb);
					printBool(nextN->reachables);
					printf("\n");
#endif
					stackN = push(stackN, nextN);
					stackT = push(stackT, nextN->trans_out);
					stackF = push(stackF, conjunction);
				}
			}
		}
	}
	return fdg;
}

ptList computeFdg_rec(ptList criticalVars, ptFdg fdg, ptFdgNode prev, void ** tableRef, ptFsmTrans prevTrans) {
	ptFdgNode newNode;
	ptFdgTrans newTrans;
	ptList criticalTrans = NULL;
	ptLList tmp = NULL;
	ptLList tmpl = NULL;
	ptLList accDepends = NULL;
	ptFsmTrans current = prevTrans;
	while(current) {
		ptList transList = current->target->trans;
		ptList transInList = current->target->trans_in;
		newNode = NULL;

		if(!htFind(*tableRef, current->target->lineNb, current->target)) {
			htInsert(*tableRef, current->target->lineNb, current->target);
			if(listCount(transInList) > 1 || listCount(transList) > 1) {
				// Found new separation or reunion node -> Must create a new FDG node and add a new FDG transition
#ifdef DEBUG
				printf("Adding transition to new separation/reunion node : %03d -> %03d\n", prevTrans->source->lineNb, current->target->lineNb);
#endif
				newNode = createFdgNode(current->target);
				fdg->nodes = listAdd(fdg->nodes, newNode);
				newTrans = createFdgTrans(prev, newNode, prevTrans);
				newTrans->writes = propagateDependenciesForward(accDepends, computeVariableDependencies(current, current->expression, 0), NULL, NULL);

				ptList critical_iter = criticalVars;
				while(critical_iter) {
					if(llistFind(newTrans->writes, (char*) critical_iter->value)) {
						criticalTrans = listAdd(criticalTrans, newTrans);
						newTrans->criticalFeatures = getTrue();
					}
					critical_iter = critical_iter->next;
				}
#ifdef DEBUG
				printf("\t Features: ");
				printBool(prevTrans->features);
				printf("\n");
				tmpl = newTrans->writes;
				while(tmpl) {
					printf("\t Variables that writes %s:", tmpl->label);
					tmp = (ptLList) tmpl->value;
					while(tmp) {
						printf("[");
						printBool((ptBoolFct)tmp->value);
						printf("]%s", tmp->label);
						tmp = tmp->next;
					}
					printf("\n");
					tmpl = tmpl->next;
				}
#endif

				prev->trans_out = listAdd(prev->trans_out, newTrans);
				newNode->trans_in = listAdd(newNode->trans_in, newTrans);

				while(transList) {
					criticalTrans = listConcat(criticalTrans, computeFdg_rec(criticalVars, fdg, newNode, tableRef, (ptFsmTrans) transList->value));
					transList = transList->next;
				}
				current = NULL;

			}
			else { // Only one outgoing transition -> pursue the exploration with the new node
				printf("Found non-critical node %03d.\n", current->target->lineNb);
				if(newNode) // a new node has been reached and created
					prev = newNode;
				ptLList depends = computeVariableDependencies(current, current->expression, 0);
				if(!accDepends)
					accDepends = depends;
				else {
					accDepends = propagateDependenciesForward(accDepends, depends, NULL, NULL);
				}
				current = (ptFsmTrans) transList->value;
			}
		}
		else {
			if(listCount(transInList) > 1 || listCount(transList) > 1) {
#ifdef DEBUG
				printf("Adding transition to visited separation/reunion node: %03d -> %03d\n", prevTrans->source->lineNb, current->target->lineNb);
#endif
				ptList node_iter = fdg->nodes;
				while(node_iter) {
					ptFdgNode node_curr = (ptFdgNode) node_iter->value;
					if(node_curr->node == current->target) {
						newTrans = createFdgTrans(prev, node_curr, prevTrans);
						newTrans->writes = propagateDependenciesForward(accDepends, computeVariableDependencies(current, current->expression, 0), NULL, NULL);

						ptList critical_iter = criticalVars;
						while(critical_iter) {
							if(llistFind(newTrans->writes, (char*) critical_iter->value)) {
								criticalTrans = listAdd(criticalTrans, newTrans);
								newTrans->criticalFeatures = getTrue();
							}
							critical_iter = critical_iter->next;
						}

#ifdef DEBUG
						printf("\t Features: ");
						printBool(prevTrans->features);
						printf("\n");
						tmpl = newTrans->writes;
						while(tmpl) {
							printf("\t Variables that writes %s:", tmpl->label);
							tmp = (ptLList) tmpl->value;
							while(tmp) {
								printf("[");
								printBool((ptBoolFct)tmp->value);
								printf("]%s", tmp->label);
								tmp = tmp->next;
							}
							printf("\n");
							tmpl = tmpl->next;
						}
#endif
						prev->trans_out = listAdd(prev->trans_out, newTrans);
						node_curr->trans_in = listAdd(node_curr->trans_in, newTrans);
					}
					node_iter = node_iter->next;
				}
			}
			current = NULL;
		}

	}
	return criticalTrans;
}

char * varexp2String(ptExpNode expression) {
	ptExpNode exp = expression;
	ptSymTabNode a_symbol;
	int size;
	char * path;
	char * attrName;
	char * tmp;
	path = NULL;
	while(exp) {	// Expression refers to a specific attribute
		a_symbol = expressionSymbolLookUpLeft(exp);
		if(!a_symbol) { // mtype or magic variable
			return NULL;
		}
		else {
			size = strlen(a_symbol->name);
			if(!path) {
				path = (char *) malloc((size+1) * sizeof(char));
			}
			else {
				tmp = (char *) realloc(path, (size+1) * sizeof(char));
				path = tmp;
			}
			strcpy(path,a_symbol->name);
			// Checking if an index is needed
			if(a_symbol->bound > 1) {

				if(!exp->children[0]->children[0] && exp->children[1]) // Expression of the form 'f.Feature.attr' -> forbidden!
					failure("Referring to an attribute of a complex clone-able feature without providing a clone index is forbidden (line %d).\n", expression->lineNb);
				char index[6];
				if(!exp->children[0]->children[0]) { // Expression of the form 'f.Feature' -> existential quantifier
					snprintf(index, 6, "[0]");
				}
				else { // Expression of the form f.Feature[x] or f.Feature[x].attr
					if(exp->children[0]->children[0]->type != E_EXPR_CONST) // Expression type for index
						failure("Only constants may be used for clone selection (line %d).\n", exp->lineNb);
					if(exp->children[0]->children[0]->iVal >= a_symbol->bound) // Index value
						failure("Constant refers to a non-existing clone (line %d).\n", exp->lineNb);
					snprintf(index, 6, "[%d]", exp->children[0]->children[0]->iVal);
				}
				size += strlen(index);
				tmp = (char *) realloc(path, (size+1) * sizeof(char));
				path = tmp;
				strcat(path, index);
			}
			// Checking whether an attribute is referenced
			exp = exp->children[1];
		}
	}
	return path;
}

ptLList computeVariableDependencies(ptFsmTrans trans, ptExpNode expression, byte flag) {
	if(!trans || !expression) return NULL;
	ptLList depends = NULL, depends2 = NULL, reads = NULL, tmpL = NULL, prevW = NULL, prevR = NULL;
	char * written = NULL;
	char * read = NULL;
	char * path = NULL;
	ptList tmp = NULL;
	ptExpNode exp = NULL;
#ifdef DEBUG
//	printf("[automata/fdg/computeVariableDependencies] Start with expression %s\n", getExpTypeName(expression->type));
#endif
	switch(expression->type) {
		case(E_DECL):
		case(E_STMNT):
			break;

		case(E_STMNT_CHAN_RCV):
			read = varexp2String(expression->children[0]);
			if(!read)
				failure("[automata/fdg/computeVariableDependencies] Could not get the name of the receiving channel.\n");
			exp = expression->children[1];
			while(exp) {
				if(exp->children[0] && exp->children[0]->type == E_RARG_VAR) {
					written = varexp2String(exp->children[0]->children[0]);
					if(written) {
						prevW = llistFind(depends, written);
						if(!prevW)
							depends = llistAdd(depends, written, llistAdd(NULL, read, NULL));
						else if (!llistFind((ptLList) prevW->value, read))
							prevW->value = llistAdd((ptLList)prevW->value, read, NULL);
					}
				}
				exp = exp->children[1];
			}
			break;

		case(E_STMNT_CHAN_SND):
			written = varexp2String(expression->children[0]);
			if(!written)
				failure("[automata/fdg/computeVariableDependencies] Could not get the name of the sending channel.\n");
			exp = expression->children[1];
			while(exp) {
				if(exp->children[0] && exp->children[0]->type == E_RARG_VAR) {
					read = varexp2String(exp->children[0]->children[0]);
					if(read) {
						prevW = llistFind(depends, written);
						if(!prevW)
							depends = llistAdd(depends, written, llistAdd(NULL, read, NULL));
						else if (!llistFind((ptLList) prevW->value, read))
							prevW->value = llistAdd((ptLList)prevW->value, read, NULL);
					}
				}
				exp = exp->children[1];
			}
			break;

		case(E_STMNT_IF):
		case(E_STMNT_DO):
		case(E_STMNT_OPT):
		case(E_STMNT_SEQ):
		case(E_STMNT_BREAK):
		case(E_STMNT_GOTO):
		case(E_STMNT_LABEL):
			break;

		case(E_STMNT_ASGN):
		case(E_EXPR_LSHIFT):
		case(E_EXPR_RSHIFT):
			written = varexp2String(expression->children[0]);
			ptLList reads = computeVariableDependencies(trans, expression->children[1], 1);
			tmpL = reads;
			while(tmpL) {
				read = tmpL->label;
				prevW = llistFind(depends, written);
				if(!prevW)
					depends = llistAdd(depends, written, llistAdd(NULL, read, NULL));
				else if (!llistFind((ptLList) prevW->value, read))
					prevW->value = llistAdd((ptLList)prevW->value, read, NULL);
				tmpL = tmpL->next;
			}
			break;


		case(E_STMNT_ELSE):
			tmp = trans->source->trans;
			depends = NULL;
			while(tmp) {
				ptFsmTrans prevT = (ptFsmTrans) tmp->value;
				if(prevT != trans) {
					prevW = computeVariableDependencies(prevT, prevT->expression, 1);
					depends2 = prevW;
					while(depends2) {
						if(!depends2->value && !llistFind(depends, depends2->label)) {
							depends = llistAdd(depends2, depends2->label, NULL);
						}
						depends2 = depends2->next;
					}
				}
				tmp = tmp->next;
			}
			break;

		case(E_STMNT_PRINT):
		case(E_STMNT_PRINTM):
		case(E_STMNT_ASSERT):
			break;

		case(E_STMNT_EXPR):
		case(E_EXPR_PAR):
			depends = computeVariableDependencies(trans, expression->children[0], 0);
			break;

		case(E_EXPR_PLUS):
		case(E_EXPR_MINUS):
		case(E_EXPR_TIMES):
		case(E_EXPR_DIV):
		case(E_EXPR_MOD):
		case(E_EXPR_BITWAND):
		case(E_EXPR_BITWOR):
		case(E_EXPR_BITWXOR):
			if(flag) {
				depends = computeVariableDependencies(trans, expression->children[0], flag);
				depends2 = computeVariableDependencies(trans, expression->children[1], flag);
				tmpL = depends2;
				while(tmpL) {
					if(!llistFind(depends, tmpL->label))
						depends = llistAdd(depends, tmpL->label, NULL);
					tmpL = tmpL->next;
				}
				llistDestroy(depends2);
			}
			break;

		case(E_EXPR_GT):
		case(E_EXPR_LT):
		case(E_EXPR_GE):
		case(E_EXPR_LE):
		case(E_EXPR_EQ):
		case(E_EXPR_NE):
		case(E_EXPR_AND):
		case(E_EXPR_OR):
			depends = computeVariableDependencies(trans, expression->children[0], flag);
			depends2 = computeVariableDependencies(trans, expression->children[1], flag);
			tmpL = depends2;
			while(tmpL) {
				if(!llistFind(depends, tmpL->label))
					depends = llistAdd(depends, tmpL->label, NULL);
				tmpL = tmpL->next;
			}
			llistDestroy(depends2);
			break;

		case(E_EXPR_UMIN):
		case(E_EXPR_BITWNEG):
		case(E_RARG_EVAL):
		case(E_STMNT_INCR):
		case(E_STMNT_DECR):
		case(E_EXPR_LEN):
			if(flag) {
				depends = computeVariableDependencies(trans, expression->children[0], flag);
			}
			break;

		case(E_EXPR_NEG):
		case(E_RARG_VAR):
		case(E_EXPR_VAR):
			depends = computeVariableDependencies(trans, expression->children[0], flag);
			break;

		case(E_EXPR_FULL):
		case(E_EXPR_NFULL):
		case(E_EXPR_EMPTY):
		case(E_EXPR_NEMPTY):
			depends = computeVariableDependencies(trans, expression->children[0], 1);
			break;

		case(E_ARGLIST):
			failure("[automata/fdg/computeVariableDependencies] E_ARGLIST should not occur in this function.\n");

		case(E_EXPR_CONST):
		case(E_RARG_CONST):
			if(flag)
				depends = llistAdd(depends, "CONST", NULL);
			break;


		case(E_EXPR_COND):
			depends = computeVariableDependencies(trans, expression->children[0], flag);
			depends2 = computeVariableDependencies(trans, expression->children[1], flag);
			tmpL = depends2;
			while(tmpL) {
				if(!llistFind(depends, tmpL->label))
					depends = llistAdd(depends, tmpL->label, NULL);
				tmpL = tmpL->next;
			}
			llistDestroy(depends2);
			depends2 = computeVariableDependencies(trans, expression->children[2], flag);
			tmpL = depends2;
			while(tmpL) {
				if(!llistFind(depends, tmpL->label))
					depends = llistAdd(depends, tmpL->label, NULL);
				tmpL = tmpL->next;
			}
			llistDestroy(depends2);
			break;

		case(E_EXPR_TIMEOUT):
		case(E_EXPR_RUN):
			break;

		case(E_VARREF):
			path = varexp2String(expression);
			if(path)
				depends = llistAdd(depends, path, NULL);
		break;
	}
//	printf("[automata/fdg/computeVariableDependencies] End.\n");
	return depends;
}


/*void printFdg(ptFdg fdg) {
	ptFdgNode init = fdg->init;
	printf("--> %d\n", init->stmnt->lineNb);
	ptLList trans = init->trans;
	while(trans) {
		printf("\t --> %s\n", trans->label);
		trans=trans->next;
	}
}*/

byte transitionIsCritical(ptFdgTrans trans, ptList newCrit, ptFdgTrans criticalTrans) {
	/* Check whether the transition */
	ptList crit_iter = newCrit;
	while(crit_iter) {
		if(llistFind(trans->writes, (char *) crit_iter->value)) {
#ifdef DEBUG
			printf("\t Transition is critical for %s!\n", (char *) crit_iter->value);
#endif
			return 1;
		}
		crit_iter = crit_iter->next;
	}
	return 0;
}

 ptFdg computeFeatureImportanceFromCriticalTrans(ptFdg fdg, ptFdgTrans start, ptList criticalVars) {
#ifdef DEBUG
	 printf("[automata/fdg/computeFeatureImportanceFromCriticalTrans] Start...\n");
#endif
	if(!start || !start->source || !start->source->trans_in || !start->trans) {
#ifdef DEBUG
	 printf("[automata/fdg/computeFeatureImportanceFromCriticalTrans] End.\n");
#endif
		return fdg;
	}
	ptStack stackN = push(NULL, start);
	ptStack stackT = push(NULL, start->source->trans_in);
	ptStack stackV = push(NULL, listConcat(computeNewCriticalVars(start, criticalVars), listCopy(criticalVars)));
	ptStack stackF = push(NULL, start->trans->features);
	ptBoolFct disjunction;

	void * table = createHashtable();
	fvtInsert(table, createFdgVisitedTrans(start, NULL));
	while(!empty(stackN)) {
		ptFdgTrans curN = pop(&stackN);
		ptList curT = pop(&stackT);
		ptList curV = pop(&stackV);
		ptBoolFct curF = pop(&stackF);
		if(curT) { // otherwise trans->source is the initial state
			ptFdgTrans trans = (ptFdgTrans) curT->value;
#ifdef DEBUG
			printf("%03d -> %03d (", curN->source->node->lineNb, curN->target->node->lineNb);
			printBool(curN->trans->features);
			printf(") <==== ");
			printf("%03d -> %03d (", trans->source->node->lineNb, trans->target->node->lineNb);
			printBool(trans->trans->features);
			printf(")\n");
			ptList tmp = curV;
			printf("\t curV = {");
			while(tmp) {
				printf(" %s", (char *)tmp->value);
				tmp = tmp->next;
			}
			printf("}\n\t curF: ");
			printBool(curF); printf("\n");
#endif
			ptBoolFct features = trans->trans->features;
			ptBoolFct conjunction = addConjunction(curF, features, 1, 1);
			trans->reachableCritical = fvtListAdd(trans->reachableCritical, start, curF ? copyBool(curF) : getTrue());

			if(isSatisfiableWrtFD(conjunction)) {
				ptFdgNode prevN = trans->source;
				if(curT->next) {
					stackN = push(stackN, curN);
					stackT = push(stackT, curT->next);
					stackV = push(stackV, curV);
					stackF = push(stackF, curF);
				}
				ptList newCrit = computeNewCriticalVars(trans, listCopy(curV));
				if(!curF || !trans->criticalFeatures)
					disjunction = getTrue();
				else
					disjunction = addDisjunction(trans->criticalFeatures, curF, 1, 1);
/*#ifdef DEBUG
				ptList tmp = newCrit;
				printf("New critical vars:");
				while(tmp) {
					printf(" %s", (char *)tmp->value);
					tmp = tmp->next;
				}
				printf("\n");
				printBool(disjunction); printf("\n");
#endif*/
				ptFVT newFVT = createFdgVisitedTrans(trans, conjunction);
				if(!fvtVisited(table, newFVT)) {
					if(transitionIsCritical(trans, newCrit, start)) {// transition is critical
#ifdef DEBUG
						printf("\t Became critical for: ");
						printBool(disjunction);
						printf("\n");
#endif
						destroyBool(trans->criticalFeatures);
						trans->criticalFeatures = disjunction;
					}
					else {
						destroyBool(disjunction);
						disjunction = NULL;
					}
					stackN = push(stackN, trans);
					stackT = push(stackT, trans->source->trans_in);
					stackV = push(stackV, newCrit);
					stackF = push(stackF, conjunction);
					fvtInsert(table, newFVT);
				}
				else {
					listDestroy(newCrit);
					destroyBool(newFVT->features);
					free(newFVT);
					newFVT = NULL;
				}
			}
		}
	}
#ifdef DEBUG
	 printf("[automata/fdg/computeFeatureImportanceFromCriticalTrans] End.\n");
#endif
	return fdg;
}

