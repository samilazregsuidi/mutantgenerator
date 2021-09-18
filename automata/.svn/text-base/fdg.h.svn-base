/*
 * FEATURED DEPENDENCIES GRAPH (FDGs)
 * * * * * * * * * * * * * * * * * * */

struct fdgNode_ {
	ptFsmNode node; // First statement the node
	struct fdgNode_ * reunion; // Reunion node
	ptList trans_out; // Transitions to other FDG nodes.
	ptList trans_in; // Transitions from other FDG nodes.
	ptBoolFct reachables;
};
typedef struct fdgNode_ tFdgNode;
typedef struct fdgNode_ * ptFdgNode;

struct fdgTrans_ {
	struct fdgNode_ * source;
	struct fdgNode_ * target;
	ptFsmTrans trans;
	ptLList writes; // Associates variables (the label) to the list of variables that modifies its value in the transition
	ptBoolFct criticalFeatures;
	ptList reachableCritical;
};
typedef struct fdgTrans_ tFdgTrans;
typedef struct fdgTrans_ * ptFdgTrans;

struct fdg_ {
	struct fdgNode_ * init;
	ptList nodes; // list of FDG nodes in the graph
};
typedef struct fdg_ tFdg;
typedef struct fdg_ * ptFdg;

struct fdg_Visited_Trans {
	ptFdgTrans trans;
	ptBoolFct features;
};
typedef struct fdg_Visited_Trans tFVT;
typedef struct fdg_Visited_Trans * ptFVT;

ptFdgNode createFdgNode(ptFsmNode node);
ptFdgTrans createFdgTrans(ptFdgNode source, ptFdgNode target, ptFsmTrans trans);
ptFVT createFdgVisitedTrans(ptFdgTrans trans, ptBoolFct features);

ptFdg computeFdg(ptFsm fsm, ptList criticalVars);
ptList computeFdg_rec(ptList criticalVars, ptFdg fdg, ptFdgNode prev, void ** tableRef, ptFsmTrans prevTrans);
ptFdg reachables(ptFdg fdg);
ptFdg computeFeatureImportance(ptFdg fdg, ptList criticalTrans, ptList criticalVars);
ptFdg computeFeatureImportanceFromCriticalTrans(ptFdg fdg, ptFdgTrans start, ptList criticalVars);
ptList computeNewCriticalVars(ptFdgTrans trans, ptList criticalVars);

ptFdg updateFeatureExpressions(ptFdg fdg); // Conjunct statements feature expression with important features
ptList getInfluentVariables(ptExpNode expression, ptList criticalVars, byte conditions);
ptLList computeVariableDependencies(ptFsmTrans trans, ptExpNode expression, byte flag);
char * varexp2String(ptExpNode expression);
