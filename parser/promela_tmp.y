%{

// This is based on the original Yacc grammar of SPIN (spin.y):

/* Copyright (c) 1989-2003 by Lucent Technologies, Bell Laboratories.     */
/* All Rights Reserved.  This software is for educational purposes only.  */
/* No guarantee whatsoever is expressed or implied by the distribution of */
/* this code.  Permission is given to distribute this code provided that  */
/* this introductory message is not removed and no monies are exchanged.  */
/* Software written by Gerard J. Holzmann.  For tool documentation see:   */
/*             http://spinroot.com/                                       */
/* Send all bug-reports and/or questions to: bugs@spinroot.com            */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "main.h"
#include "cnf.h"
#include "list.h"
#include "boolFct.h"
#include "tvl.h"
#ifdef CEGAR
	#include "predicate.h"
#endif
#ifdef CLOCK
	#include "clockZone.h"
	#include "tctl.h"
#endif
#ifdef STOCHASTIC
	#include "pctl.h"
#endif
#include "symbols.h"
#include "automata.h"

#include "y.tab.h"

#ifdef CPP
extern "C" 
#endif
int yylex(YYSTYPE * yylval_param, struct symTabNode_* * globalSymTab);

extern int nbrLines;

int yyerror (struct symTabNode_* * globalSymTab, struct mTypeNode_* * mtypes, void ** property, char* msg){
	fprintf(stderr, "Syntax error on line %d: '%s'.\n", nbrLines, msg);
	exit(1);
}

/*int printf(char *msg, char *param) {
	char buffer [strlen(msg) + strlen(param) + 1];
	sprintf(buffer, msg, param);
	fprintf(stderr, "Syntax error on line %d: '%s'.\n", nbrLines, buffer);
	exit(1);
}*/

// extern - lex

#ifdef CLOCK
	ptList _clocks = NULL;
#endif

ptList add = NULL;
ptList add2 = NULL;

ADD* Alloc(const ADD& a){
	ADD* res = new ADD(a);
	add2 = listAdd(add2, res);
	return res;
}

void Free(void){
	while(add2){
		delete add2->value;
		add2 = add2->next;
	}
}

%}

%pure_parser
%lex-param	{struct symTabNode_* * globalSymTab}
%parse-param {struct symTabNode_* * globalSymTab}
%parse-param {struct mTypeNode_* * mtypes}
%parse-param {void ** property} // Either NULL, a list, or a TCTL/PCTL formula.

%union { 
	int       				iVal;
	char*    				sVal;
	double					rVal;
	tDataTuple				pDataVal;
	ptExpNode				pExpVal;
	ptSymTabNode			pSymTabNodeVal;
	struct ADD*				pBoolFct;
	struct fsm_*			pFsmVal;
	struct list_ *			pList;
	struct _tctlFormula * 	pTctlFormula;
	struct _pctlFormula *   pPctlFormula;
}

%token <iVal> CONST TYPE IF DO
%token <sVal> NAME UNAME PNAME INAME STRING
%token <rVal> REAL
%type  <sVal> aname
%type  <rVal> real_expr
%type  <pExpVal> step stmnt timed_stmnt Expr expr Special Stmnt varref arg args rarg rargs margs options full_expr prargs cmpnd pfld sfld Probe inst prop varref_ cmpnd_ pfld_ sfld_ 
%type  <pDataVal> vardcl basetype ch_init
%type  <pSymTabNodeVal> decl one_decl decl_lst ivar var_list typ_list utype
%type  <pFsmVal> body sequence option
%type  <pList> props
%type  <pTctlFormula> tctl
%type  <pPctlFormula> pctl
%type  <pBoolFct> f_real_expr

%token	TRUE FALSE SKIP ASSERT PRINT PRINTM
%token	C_CODE C_DECL C_EXPR C_STATE C_TRACK
%token	RUN LEN ENABLED EVAL PC_VAL
%token	TYPEDEF MTYPE INLINE LABEL OF
%token	GOTO BREAK ELSE SEMI
%token	FI OD SEP
%token	ATOMIC NON_ATOMIC D_STEP UNLESS
%token  TIMEOUT NONPROGRESS
%token	ACTIVE PROCTYPE D_PROCTYPE
%token	HIDDEN SHOW ISLOCAL
%token	PRIORITY PROVIDED
%token	FULL EMPTY NFULL NEMPTY
%token	XU							/* val */
%token	CLAIM TRACE INIT		/* sym */
%token  WHILE WHEN WAIT RESET /* time */
%token  SPEC EVENTUALLY ALWAYS GLOBALLY FINALLY /* TCTL */

%right	ASGN
%left	SND O_SND RCV R_RCV /* SND doubles as boolean negation */
%left	OR
%left	AND
%left	'|'
%left	'^'
%left	'&'
%left	EQ NE
%left	GT LT GE LE
%left	LSHIFT RSHIFT
%left	'+' '-'
%left	'*' '/' '%'
%left	INCR DECR
%right	'~' UMIN NEG COUNT CONTEXT
%left	DOT
%right  IMPLIES

%start start_parsing


%%

start_parsing	: program						/* dealt with locally */ 
				| props							{if(property) *property = $1;} 
				| SPEC tctl program				{
#ifdef CLOCK
													if(property) *property = $2;
#else
													failure("[parser/yyparse] Timed CTL formulae can only be checked if CLOCK option is enabled.\n");
#endif
												}
				| SPEC pctl program				{
#ifdef STOCHASTIC
													if(property) *property = $2;
#else
													failure("[parser/yyparse] Probabilistic CTL formulae can only be checked if STOCHASTIC option is enabled.\n");
#endif
												}
				;
				
tctl		: EVENTUALLY FINALLY '(' LE CONST ')' expr										{ 
#ifdef CLOCK
																								$$ = createTctlFormula(CTL_EF, NULL, $5, $7); 
#endif
																							}
			| ALWAYS GLOBALLY '(' LE CONST ')' expr											{ 
#ifdef CLOCK
																								$$ = createTctlFormula(CTL_AG, NULL, $5, createExpNode(E_EXPR_NEG, NULL, 0, $7, NULL, NULL, nbrLines, NULL, NULL)); 
#endif
																							}
			;
			
pctl		: FINALLY expr													{ 
#ifdef STOCHASTIC
																				;//$$ = createPctlFormula(PCTL_F, NULL, $2); 
#endif
																			}
			| GLOBALLY expr													{ 
#ifdef STOCHASTIC
																				;//$$ = createPctlFormula(PCTL_G, NULL, $2); 
#endif
																			}
			;
				
props			: prop							{$$ = listAdd(NULL,$1);}
				| props ',' prop				{$$ = listAdd($1,$3);}
				;

prop    : '(' prop ')'							{ $$ = createExpNode(E_EXPR_PAR, 	NULL, 	0, $2, NULL, NULL, nbrLines, NULL, NULL); }
		| prop '+' prop							{ $$ = createExpNode(E_EXPR_PLUS, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| prop '-' prop							{ $$ = createExpNode(E_EXPR_MINUS, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| prop '*' prop							{ $$ = createExpNode(E_EXPR_TIMES, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| prop '/' prop							{ $$ = createExpNode(E_EXPR_DIV, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| prop '%' prop							{ $$ = createExpNode(E_EXPR_MOD, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| prop '&' prop							{ $$ = createExpNode(E_EXPR_BITWAND,NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| prop '^' prop							{ $$ = createExpNode(E_EXPR_BITWXOR,NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| prop '|' prop							{ $$ = createExpNode(E_EXPR_BITWOR,	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| prop GT prop							{ $$ = createExpNode(E_EXPR_GT, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| prop LT prop							{ $$ = createExpNode(E_EXPR_LT, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| prop GE prop							{ $$ = createExpNode(E_EXPR_GE, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| prop LE prop							{ $$ = createExpNode(E_EXPR_LE, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| prop EQ prop							{ $$ = createExpNode(E_EXPR_EQ, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| prop NE prop							{ $$ = createExpNode(E_EXPR_NE, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| prop AND prop							{ $$ = createExpNode(E_EXPR_AND, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| prop OR  prop							{ $$ = createExpNode(E_EXPR_OR, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| varref_								{ $$ = createExpNode(E_EXPR_VAR, 	NULL, 	0, $1, NULL, NULL, nbrLines, NULL, NULL); }
		| CONST									{ $$ = createExpNode(E_EXPR_CONST,  NULL,$1, NULL, NULL, NULL, nbrLines, NULL, NULL); }
		;

varref_	: cmpnd_								{ $$ = $1; }
		;

pfld_	: NAME									{ 	ptSymTabNode symbol = lookupInSymTab(*globalSymTab, $1);
													if(symbol) $$ = createExpNode(E_VARREF_NAME, $1, 0, NULL, NULL, NULL, nbrLines, NULL, symbol);
													else $$ = createExpNode(E_EXPR_CONST,  NULL, getMTypeValue(*mtypes, $1), NULL, NULL, NULL, nbrLines, NULL, NULL);		
												}
		| NAME '[' prop ']'						{ $$ = createExpNode(E_VARREF_NAME,	$1, 0, $3, NULL, NULL, nbrLines, NULL, NULL); }
		;

cmpnd_	: pfld_ sfld_							{ if($1->type == E_VARREF_NAME)
													$$ = createExpNode(E_VARREF, NULL, 0,   $1,   $2, NULL, nbrLines, NULL, NULL); 
												  else
												    $$ = $1;
												}
		;

sfld_	: /* empty */							{ $$ = NULL; }
		| '.' cmpnd_ %prec DOT					{ $$ = $2;   }
		;
				
/** PROMELA Grammar Rules **/


program	: units									{
#ifdef CLOCK
												  encodeClocks(_clocks);
#endif
												}
		;

units	: unit									/* dealt with locally */ 
		| units unit							/* dealt with locally */ 
		;

unit	: proc		/* proctype { }       */	/* dealt with locally */ 
		| init		/* init { }           */	/* dealt with locally */
		| claim		/* never claim        */	/* dealt with locally */
		| events	/* event assertions   */  	{ failure("The 'events' construct is currently not supported."); }
		| one_decl	/* variables, chans   */	{ if($1 != NULL) *globalSymTab = addToSymTab(*globalSymTab, $1); }
		| utype		/* user defined types */	{ *globalSymTab = addToSymTab(*globalSymTab, $1); }
		| c_fcts	/* c functions etc.   */  	{ failure("Embedded C code is not supported."); }
		| ns		/* named sequence     */  	{ failure("The 'named sequence' construct is currently not supported."); }
		| SEMI		/* optional separator */	/* ignored */			
	/*	| error									 ?! undefined non-terminal */
		;

proc	: inst		/* optional instantiator */	/* returns an EXP_NODE describing the number of initially active procs; */
		  proctype NAME							/* Ignore the proctype nonterminal; use the sval of NAME */
		  '(' decl ')'							
		  Opt_priority							/* Ignore */
		  Opt_enabler							/* Ignore */
		  body									{	$9->symTab = addToSymTab($5, $9->symTab);
			  										*globalSymTab = addToSymTab(*globalSymTab, createSymTabNode(T_PROC, $3, nbrLines, 0, 0, $1, $9, NULL));
												}
		;

proctype: PROCTYPE								/* Ignore */
		| D_PROCTYPE							{ failure("Deterministic proctypes are not supported (only useful for simulation)."); }
		;

inst	: /* empty */							{ $$ = createExpNode(E_EXPR_CONST,  NULL, 0, NULL, NULL, NULL, nbrLines, NULL, NULL); }
		| ACTIVE								{ $$ = createExpNode(E_EXPR_CONST,  NULL, 1, NULL, NULL, NULL, nbrLines, NULL, NULL); }
		| ACTIVE '[' CONST ']'					{ $$ = createExpNode(E_EXPR_CONST,  NULL, $3, NULL, NULL, NULL, nbrLines, NULL, NULL); }
		| ACTIVE '[' NAME ']'					{	ptSymTabNode var = lookupInSymTab(*globalSymTab, $3);
													if(var == NULL) printf("The variable %s does not exist.", $3);
													else if(var->type != T_INT && var->type != T_BIT && var->type != T_SHORT) printf("The variable %s is not of type int, short or bit.", $3);
													else if(var->init == NULL || var->init->type != E_EXPR_CONST) printf("The variable %s does not have a constant value.", $3);
													else {
														$$ = createExpNode(E_EXPR_CONST,  NULL, var->init->iVal, NULL, NULL, NULL, nbrLines, NULL, NULL);
													}
													free($3);
												}
		| ACTIVE '[' COUNT '(' expr ')' ']'		{ $$ = createExpNode(E_EXPR_COUNT,  NULL, 	0, $5, NULL, NULL, nbrLines, NULL, NULL); 
#if !defined(Z3) && !defined(MULTI)
                                         		  failure("Feature clones are not allowed in this variant of SNIP.\n");
#endif
												}
		;

init	: INIT Opt_priority body				{	if(lookupInSymTab(*globalSymTab, "init") != NULL) failure("This is the second init process; only one is allowed.");
													else {
														*globalSymTab = addToSymTab(*globalSymTab, createSymTabNode(T_PROC, "init", nbrLines, 1, 0, NULL, $3, NULL));
													}

												}				
		;

claim	: CLAIM body							{ 	if(neverClaim != NULL) failure("Found a second never claim.  Only one claim at a time is allowed.");
													else {
														neverClaim = createSymTabNode(T_NEVER, "__never", nbrLines, 1, 0, NULL, $2, NULL);
														*globalSymTab = addToSymTab(*globalSymTab, neverClaim);
													}
												}
		;

events	: TRACE body							{ failure("Event sequences (traces) are not supported."); }
		;

utype	: TYPEDEF NAME '{' decl_lst '}'			{	$$ = createSymTabNode(T_TDEF, $2, nbrLines, 1, 0, NULL, NULL, $4);
													if(!spinMode && strcmp($$->name, "features") == 0) {
														ptSymTabNode cur = $$->child;
														while(cur != NULL) {
															if(cur->type != T_BOOL && cur->type != T_UTYPE) failure("Feature '%s' is not declared as a boolean or a complex feature but as a '%s'.\n", cur->name, getTypeName(cur->type));
															if(cur->type == T_BOOL && cur->init && cur->init->type != E_EXPR_CONST) failure("The initial value of a Boolean feature must be given as a constant (0 or 1), this is not the case for '%s' at line %d.\n", cur->name, cur->lineNb);
															if(cur->type == T_BOOL)
																cur->type = T_FEAT;
#if defined Z3 || defined MULTI
															else {
																cur->type = T_UFEAT;
																if(!cur->utype || !cur->utype->child || cur->utype->child->type != T_BOOL || (strcmp(cur->utype->child->name, "is_in") != 0))
																	failure("The first subfield of a complex feature like '%s' must be a Boolean called 'is_in'. Here, it is a '%s' called '%s'. \n", cur->name, cur->utype->child ? getTypeName(cur->utype->child->type) : "NULL", cur->utype->child ? cur->utype->child->name : "NULL");
															}
#else 
															else
																failure("The use of complex features without Z3 is forbidden.\n");
															if(cur->bound > 1)
																failure("The use of feature clones without Z3 is forbidden.\n");
#endif
															if(!optimisedSpinMode) {
																cur->capacity = getFeatureID(cur->name);
																if(cur->capacity == -1) failure("Feature '%s' not found in feature model.\n", cur->name);
															}
															cur = cur->next;
														}
													}
												} 
		;

nm		: NAME									/* Unreachable */
		| INAME									/* Unreachable */
		;

ns		: INLINE nm '(' args ')'				/* Unreachable */
		;

c_fcts	: ccode									/* Unreachable */
	    | cstate								/* Unreachable */
	    ;

cstate	: C_STATE STRING STRING					/* Unreachable */
		| C_TRACK STRING STRING					/* Unreachable */
		| C_STATE STRING STRING	STRING			/* Unreachable */
		| C_TRACK STRING STRING STRING			/* Unreachable */
		;

ccode	: C_CODE								/* Unreachable */
		| C_DECL								/* Unreachable */
		;

cexpr	: C_EXPR								/* Unreachable */
		;

body	: '{' sequence OS '}'					{ $$ = $2; }
		;

sequence: step									{ 	$$ = createFsm();
													if($1->type == E_DECL) {
														$$->symTab = $1->symTab;
														$1->symTab = NULL;
														destroyExpNode($1);
													} else if($1->type == E_STMNT) {
														$$ = stmnt2fsm($$, $1->children[0], *globalSymTab);
														$1->children[0] = NULL;
														destroyExpNode($1);
													}
													printFsm($$,  0, "null0");
												}
		| sequence MS step						{	if($3->type == E_DECL) {
														$$ = $1;
														$$->symTab = addToSymTab($$->symTab, $3->symTab);
														$3->symTab = NULL;
														destroyExpNode($3);
													} else if($3->type == E_STMNT) {
														$$ = stmnt2fsm($1, $3->children[0], *globalSymTab);
														$3->children[0] = NULL;
														destroyExpNode($3);
													}
													printFsm($$, 1, "null1");
												}
		;
		
step    : one_decl								{ $$ = createExpNode(E_DECL, NULL, 0, NULL, NULL, NULL, nbrLines, NULL, $1); }
		| XU vref_lst							{ failure("Channel assertions are currently not supported."); }
		| NAME ':' one_decl						{ failure("Declarations with labels are not suported."); }
		| NAME ':' XU							{ failure("Channel assertions are currently not supported."); }
		| stmnt									{ $$ = createExpNode(E_STMNT, NULL, 0, $1, NULL, NULL, nbrLines, NULL, NULL); }
		| stmnt UNLESS stmnt					{ failure("Unless statements are currently not supported."); }
		| timed_stmnt							{ 
		#ifndef CLOCK
													failure("Timed statements are allowed only together with the CLOCK option.");
		#endif
													$$ = createExpNode(E_STMNT, NULL, 0, $1, NULL, NULL, nbrLines, NULL, NULL);; 
												}
		;

timed_stmnt	: WHILE '(' expr ')' WAIT								{ $$ = createExpNode(E_STMNT_WAIT, NULL, 0, $3, NULL, NULL, nbrLines, NULL, NULL); }
			| WHEN '(' expr ')' DO Stmnt							{ $$ = createExpNode(E_STMNT_WHEN, NULL, 0, $3, $6, NULL, nbrLines, NULL, NULL); }
			| WHEN '(' expr ')' RESET '(' var_list ')'	DO Stmnt	{ $$ = createExpNode(E_STMNT_WHEN, NULL, 0, $3, $10, NULL, nbrLines, NULL, $7); }
			;

vis		: /* empty */							/* Ignore */
		| HIDDEN								{ failure("The 'hidden' keyword is not supported."); }
		| SHOW									{ failure("The 'show' keyword is not supported."); }
		| ISLOCAL								{ failure("The 'local' keyword is not supported."); }
		;

asgn	: /* empty */							/* Ignore */
		| ASGN									/* Ignore */
		;

		
/* Note: "bit", "bool", "byte", "pid", "short", "int", "unsigned", "chan", "mtype", "clock", all produce a TYPE token with ival which contains the type. */
		
one_decl: vis TYPE var_list						{	ptSymTabNode cur = $3;
													while(cur != NULL) {
														// If type != 0, then the var is a T_CHAN
														if(cur->type == 0) cur->type = $2;
														if(cur->type == T_CLOCK) { 
#ifdef CLOCK
															if(!_clocks)
																_clocks = listAdd(NULL, GLOBAL_CLOCK);
															_clocks = listAdd(_clocks, cur->name);
#else
															failure("Clocks can only be declared when the CLOCK option is enabled.");
#endif
														}
														cur = cur->next;
													}
													$$ = $3;
												}
	 	| vis UNAME var_list 					{	ptSymTabNode type = lookupInSymTab(*globalSymTab, $2);
	 												if(type == NULL) printf("The type %s was not declared in a typedef.", $2);
													else {
														ptSymTabNode cur = $3;
														while(cur != NULL) {
															cur->type = T_UTYPE;
															cur->utype = type;
															cur = cur->next;
														}
														$$ = $3;
													}
	 												free($2);
												}	
		| vis TYPE asgn '{' nlst '}'			{	if($2 != T_MTYPE) failure("This syntax only works for MTYPEs.");
													$$ = NULL;
													/* The mtype values are added in the nlst rule. */ 
												}
		;

decl_lst: one_decl								{ $$ = $1; }
		| one_decl SEMI decl_lst				{ $$ = addToSymTab($1, $3); }
		;

												// Used for the parameters of a proctype
decl    : /* empty */							{ $$ = NULL; }
		| decl_lst								{ $$ = $1; }
		;

vref_lst: varref								/* Unreachable */
		| varref ',' vref_lst					/* Unreachable */
		;

var_list: ivar									{ $$ = $1; }
		| ivar ',' var_list						{ $$ = addToSymTab($1, $3); }
		;

ivar    : vardcl								{ $$ = createSymTabNode(	 0, $1.sVal, nbrLines, $1.iVal,		  0, NULL, NULL, NULL); }
		| vardcl ASGN expr						{ 	int mtype;
													if($3->type == E_EXPR_VAR && (mtype = getMTypeValue(*mtypes, $3->children[0]->children[0]->sVal)) != -1) {
														$3->type = E_EXPR_CONST;
														$3->iVal = mtype;
														destroyExpNode($3->children[0]);
													}
													$$ = createSymTabNode(	 0, $1.sVal, nbrLines, $1.iVal,	 	  0,   $3, NULL, NULL);
												}
		| vardcl ASGN ch_init					{ $$ = createSymTabNode(T_CHAN, $1.sVal, nbrLines, $1.iVal, $3.iVal, NULL, NULL, $3.symTabNodeVal); }
		;

ch_init : '[' CONST ']' OF '{' typ_list '}'		{ $$.iVal = $2; $$.symTabNodeVal = $6; } 
		;

vardcl  : NAME  								{ $$.sVal = $1; $$.iVal = 1; }
		| NAME ':' CONST						{ failure("The 'unsigned' data type is not supported."); }
		| NAME '[' CONST ']'					{ $$.sVal = $1; $$.iVal = $3; }
		;

varref	: cmpnd									{ $$ = $1; }
		;

pfld	: NAME									{ $$ = createExpNode(E_VARREF_NAME, $1, 0, NULL, NULL, NULL, nbrLines, NULL, NULL); }
		| NAME '[' expr ']'						{ $$ = createExpNode(E_VARREF_NAME,	$1, 0, $3, NULL, NULL, nbrLines, NULL, NULL); }
		;

cmpnd	: pfld sfld								{ $$ = createExpNode(E_VARREF, 	  NULL, 0,   $1,   $2, NULL, nbrLines, NULL, NULL); }
		| CONTEXT '.' pfld sfld					{ $$ = createExpNode(E_VARREF, 	  NULL, 1,   $3,   $4, NULL, nbrLines, NULL, NULL); }
		;

sfld	: /* empty */							{ $$ = NULL; }
		| '.' cmpnd %prec DOT					{ $$ = $2;   }
		;
		
stmnt	: Special								{ $$ = $1; }
		| Stmnt									{ $$ = $1; }
		;	

Special : varref RCV rargs						{ 
													$$ = createExpNode(E_STMNT_CHAN_RCV, 	NULL, 	0,   $1,   $3, NULL, nbrLines, NULL, NULL); 
#ifdef Z3
													ptExpNode varNode = $$->children[1];
													while(varNode) {
														if(varNode->children[0] && varNode->children[0]->type == E_RARG_VAR && varNode->children[0]->children[0] && varNode->children[0]->children[0]->children[0]) {
															ptSymTabNode featureNode = lookupInSymTab(*globalSymTab, varNode->children[0]->children[0]->children[0]->sVal);
															if(featureNode && featureNode->utype && featureNode->utype->child) {
																ptSymTabNode node = lookupInSymTab(featureNode->utype->child, varNode->children[0]->children[0]->children[1]->children[0]->sVal);
																if(node && node->type == T_FEAT || node->type == T_UFEAT)
																	failure("Features cannot occur in right-hand side of channel reception statements at line %d.\n", nbrLines);
															}
														}
														varNode = varNode->children[1];
													}
#endif
												}
		| varref SND margs						{ $$ = createExpNode(E_STMNT_CHAN_SND, 	NULL, 	0,   $1,   $3, NULL, nbrLines, NULL, NULL); }
		| IF options FI 						{ $$ = createExpNode(E_STMNT_IF, 		NULL, 	0,   $2, NULL, NULL,       $1, NULL, NULL); }
		| DO options OD							{ $$ = createExpNode(E_STMNT_DO, 		NULL, 	0,   $2, NULL, NULL,       $1, NULL, NULL); }
		| BREAK									{ $$ = createExpNode(E_STMNT_BREAK, 	NULL, 	0, NULL, NULL, NULL, nbrLines, NULL, NULL); }
		| GOTO NAME								{ $$ = createExpNode(E_STMNT_GOTO, 		$2, 	0, NULL, NULL, NULL, nbrLines, NULL, NULL); }
		| NAME ':' stmnt						{ if($3->type == E_STMNT_LABEL && $3->children[0] && $3->children[0]->type == E_STMNT_LABEL) failure("Only two labels per state are supported."); 
												  $$ = createExpNode(E_STMNT_LABEL,		$1, 	0,   $3, NULL, NULL, nbrLines, NULL, NULL); }
		;

Stmnt	: varref ASGN full_expr					{ 
													$$ = createExpNode(E_STMNT_ASGN, 		NULL, 	0,   $1,   $3, NULL, nbrLines, NULL, NULL);
#ifdef Z3													
													if($1 && $1->children[1] && $1->children[1]->children[0]) {
														ptSymTabNode featureNode = lookupInSymTab(*globalSymTab, $1->children[0]->sVal);
														if(featureNode && featureNode->utype && featureNode->utype->child) {
															ptSymTabNode node = lookupInSymTab(featureNode->utype->child, $1->children[1]->children[0]->sVal);
															if(node && node->type == T_FEAT || node->type == T_UFEAT)
																failure("Features cannot occur in left-hand side of assignment at line %d.\n", nbrLines);
														}
													}
#endif
												}
		| varref INCR							{ $$ = createExpNode(E_STMNT_INCR, 		NULL, 	0,   $1, NULL, NULL, nbrLines, NULL, NULL); }
		| varref DECR							{ $$ = createExpNode(E_STMNT_DECR, 		NULL, 	0,   $1, NULL, NULL, nbrLines, NULL, NULL); }
		| PRINT	'(' STRING prargs ')'			{ $$ = createExpNode(E_STMNT_PRINT, 	$3, 	0,   $4, NULL, NULL, nbrLines, NULL, NULL); } 
		| PRINTM '(' varref ')'					{ $$ = createExpNode(E_STMNT_PRINTM, 	NULL, 	0,   $3, NULL, NULL, nbrLines, NULL, NULL); }
		| PRINTM '(' CONST ')'					{ $$ = createExpNode(E_STMNT_PRINTM, 	NULL,  $3, NULL, NULL, NULL, nbrLines, NULL, NULL); }
		| ASSERT full_expr						{ $$ = createExpNode(E_STMNT_ASSERT, 	NULL, 	0,   $2, NULL, NULL, nbrLines, NULL, NULL); }
		| ccode									{ failure("Embedded C code is not supported."); }
		| varref R_RCV rargs					{ failure("Sorted send and random receive are not supported."); }
		| varref RCV LT rargs GT				{ failure("Channel poll operations are not supported."); }
		| varref R_RCV LT rargs GT				{ failure("Channel poll operations are not supported."); }
		| varref O_SND margs					{ failure("Sorted send and random receive are not supported."); }
		| full_expr								{ $$ = createExpNode(E_STMNT_EXPR, 		NULL, 	0,   $1, NULL, NULL, nbrLines, NULL, NULL); }
		| ELSE									{ $$ = createExpNode(E_STMNT_ELSE, 		NULL, 	0, NULL, NULL, NULL, nbrLines, NULL, NULL); }
		| ATOMIC '{' sequence OS '}'			{ $$ = createExpNode(E_STMNT_ATOMIC,	NULL, 	0, NULL, NULL, NULL, nbrLines,   $3, NULL); }
		| D_STEP '{' sequence OS '}'			{ failure("Deterministic steps are not yet supported."); }
		| '{' sequence OS '}'					{ $$ = createExpNode(E_STMNT_SEQ, 		NULL, 	0, NULL, NULL, NULL, nbrLines,   $2, NULL); }
		| INAME '(' args ')' Stmnt				{ failure("Inline calls are not yet supported."); }
		;

options : option								{ $$ = createExpNode(E_STMNT_OPT, 		NULL, 	0, NULL, NULL, NULL, nbrLines,   $1, NULL); }
		| option options						{ $$ = createExpNode(E_STMNT_OPT, 		NULL, 	0,   $2, NULL, NULL, nbrLines,   $1, NULL); }
		;

option  : SEP sequence OS						{ $$ = $2; }
		| SEP '[' real_expr ']' sequence OS		{ 
#ifdef STOCHASTIC
												  $$ = $5; 
												  if($$ && $$->init && $$->init->trans && $$->init->trans->value && ((ptFsmTrans) $$->init->trans->value)->expression) {
												  	((ptFsmTrans) $$->init->trans->value)->expression->prob = $3;
												  }
#else
												  failure("Probability values may not occur when STOCHASTIC option is disabled.\n");
#endif
												}
		| SEP '[' f_real_expr ']' sequence OS   { 
#ifdef STOCHASTIC											  
												  $$ = $5;
												  if($$ && $$->init && $$->init->trans && $$->init->trans->value && ((ptFsmTrans) $$->init->trans->value)->expression) {
												  	((ptFsmTrans) $$->init->trans->value)->features = addConjunction(createXORFunction(add), *$3, 0, 0);
												  	/*printf("S IL VOUS PLAIT\n");
												  	printBool(((ptFsmTrans) $$->init->trans->value)->features);
												  	printf("MERCI AUREVOIR\n");*/
												  }
												  //printBool($3);
												  Free();
												  listDestroy(add);
												  
												  add = NULL;
#else
												  failure("Featured probability values may not occur when STOCHASTIC option is disabled.\n");
#endif 
												 }
		;
		

real_expr	: '(' real_expr ')'							{ $$ = $2; }
			| real_expr '+' real_expr					{ $$ = $1 + $3; }
			| real_expr '-' real_expr					{ $$ = $1 - $3; }
			| real_expr '*' real_expr                   { $$ = $1 * $3; }
			| real_expr '/' real_expr                   { $$ = $1 / $3; }
			| REAL										{ $$ = $1;}
			| CONST										{ $$ = $1;}
			;
		
				;

f_real_expr: full_expr IMPLIES real_expr 	{								  
											  $$ = Alloc(addConjunction(expression2Bool($1, *globalSymTab).boolFctResult, createConstant($3), 0, 0));
											  add = listAdd(add, new ADD(addConjunction(expression2Bool($1, *globalSymTab).boolFctResult, createConstant(1.0), 0, 0)));
											}
			| f_real_expr ',' f_real_expr 	{ $$ = Alloc(addXorFunction(*$1, *$3, 0, 0)); }
			;

OS		: /* empty */												/* Ignore */
		| SEMI			{ /* redundant semi at end of sequence */ }	/* Ignore */
		;

MS		: SEMI			{ /* at least one semi-colon */ }			/* Ignore */
		| MS SEMI		{ /* but more are okay too   */ }			/* Ignore */
		;
		
aname	: NAME									{ $$ = $1; };													
		| PNAME									{ $$ = $1; };
		;
		
expr    : '(' expr ')'							{ $$ = createExpNode(E_EXPR_PAR, 	NULL, 	0, $2, NULL, NULL, nbrLines, NULL, NULL); }
		| expr '+' expr							{ $$ = createExpNode(E_EXPR_PLUS, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr '-' expr							{ $$ = createExpNode(E_EXPR_MINUS, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr '*' expr							{ $$ = createExpNode(E_EXPR_TIMES, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr '/' expr							{ $$ = createExpNode(E_EXPR_DIV, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr '%' expr							{ $$ = createExpNode(E_EXPR_MOD, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr '&' expr							{ $$ = createExpNode(E_EXPR_BITWAND,NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr '^' expr							{ $$ = createExpNode(E_EXPR_BITWXOR,NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr '|' expr							{ $$ = createExpNode(E_EXPR_BITWOR,	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr GT expr							{ $$ = createExpNode(E_EXPR_GT, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr LT expr							{ $$ = createExpNode(E_EXPR_LT, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr GE expr							{ $$ = createExpNode(E_EXPR_GE, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr LE expr							{ $$ = createExpNode(E_EXPR_LE, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr EQ expr							{ $$ = createExpNode(E_EXPR_EQ, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr NE expr							{ $$ = createExpNode(E_EXPR_NE, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr AND expr							{ $$ = createExpNode(E_EXPR_AND, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr OR  expr							{ $$ = createExpNode(E_EXPR_OR, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr LSHIFT expr						{ $$ = createExpNode(E_EXPR_LSHIFT,	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr RSHIFT expr						{ $$ = createExpNode(E_EXPR_RSHIFT,	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| COUNT '(' expr ')'					{ $$ = createExpNode(E_EXPR_COUNT,  NULL, 	0, $3, NULL, NULL, nbrLines, NULL, NULL); }
		| '~' expr								{ $$ = createExpNode(E_EXPR_BITWNEG,NULL, 	0, $2, NULL, NULL, nbrLines, NULL, NULL); }
		| '-' expr %prec UMIN					{ 	if($2->type != E_EXPR_CONST) $$ = createExpNode(E_EXPR_UMIN,	NULL, 	0, $2, NULL, NULL, nbrLines, NULL, NULL);
													else {
														$2->iVal = - $2->iVal;
														$$ = $2;
													}
												} 
		| SND expr %prec NEG					{ $$ = createExpNode(E_EXPR_NEG, 	NULL, 	0, $2, NULL, NULL, nbrLines, NULL, NULL); }
		| '(' expr SEMI expr ':' expr ')'		{ $$ = createExpNode(E_EXPR_COND, 	NULL, 	0, $2,   $4,   $6, nbrLines, NULL, NULL); }
		| RUN aname '(' args ')' Opt_priority	{ $$ = createExpNode(E_EXPR_RUN, 	  $2,   0, $4, NULL, NULL, nbrLines, NULL, NULL); }
		| RUN aname '[' varref ']' '(' args ')' 
			Opt_priority						{ $$ = createExpNode(E_EXPR_RUN, 	  $2,   0, $7, $4, NULL, nbrLines, NULL, NULL); }
		| LEN '(' varref ')'					{ $$ = createExpNode(E_EXPR_LEN, 	NULL, 	0, $3, NULL, NULL, nbrLines, NULL, NULL); }
		| ENABLED '(' expr ')'					{ failure("The enabled keyword is not supported."); }
		| varref RCV '[' rargs ']'				{ failure("Construct not supported."); /* Unclear */ }
		| varref R_RCV '[' rargs ']'			{ failure("Sorted send and random receive are not supported."); }
		| varref								{ $$ = createExpNode(E_EXPR_VAR, 	NULL, 	0, $1, NULL, NULL, nbrLines, NULL, NULL); }
		| cexpr									{ failure("Embedded C code is not supported."); }
		| CONST									{ $$ = createExpNode(E_EXPR_CONST,  NULL, $1, NULL, NULL, NULL, nbrLines, NULL, NULL); }
		| TRUE									{ $$ = createExpNode(E_EXPR_TRUE,  NULL, 1, NULL, NULL, NULL, nbrLines, NULL, NULL); }
		| FALSE									{ $$ = createExpNode(E_EXPR_FALSE,  NULL, 0, NULL, NULL, NULL, nbrLines, NULL, NULL); }
		| TIMEOUT								{ $$ = createExpNode(E_EXPR_TIMEOUT,NULL, 0, NULL, NULL, NULL, nbrLines, NULL, NULL); }
		| NONPROGRESS							{ failure("The 'np_' variable is not supported."); } /* Global variable (p. 447), true in a state if not labelled progress. */
		| PC_VAL '(' expr ')'					{ failure("The 'pc_value()' construct is not supported."); } /* Predefined function (p. 448). */
		| PNAME '[' expr ']' '@' NAME			{ failure("Construct not supported."); /* Unclear */ }
		| PNAME '[' expr ']' ':' pfld			{ failure("Construct not supported."); /* Unclear */ }
		| PNAME '@' NAME						{ failure("Construct not supported."); /* Unclear */ }
		| PNAME ':' pfld						{ failure("Construct not supported."); /* Unclear */ }
		;
		
Opt_priority:	/* none */
		| PRIORITY CONST						{ failure("The 'priority' construct is related to simulation and not supported."); }
		;

full_expr:	expr								{ $$ = $1; }
		|	Expr								{ $$ = $1; }
		;

Opt_enabler:	/* none */
		| PROVIDED '(' full_expr ')'			{ failure("The 'provided' construct is currently not supported."); }
	/*	| PROVIDED error						{ failure("The 'provided' construct is currently not supported."); } */
		;

/* an Expr cannot be negated - to protect Probe expressions */
Expr	: Probe									{ $$ = $1; }
		| '(' Expr ')'							{ $$ = createExpNode(E_EXPR_PAR, 	NULL, 	0, $2, NULL, NULL, nbrLines, NULL, NULL); }
		| Expr AND Expr							{ $$ = createExpNode(E_EXPR_AND, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| Expr AND expr							{ $$ = createExpNode(E_EXPR_AND, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| Expr OR  Expr							{ $$ = createExpNode(E_EXPR_OR, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| Expr OR  expr							{ $$ = createExpNode(E_EXPR_OR, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr AND Expr							{ $$ = createExpNode(E_EXPR_AND, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| expr OR  Expr							{ $$ = createExpNode(E_EXPR_OR, 	NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| SKIP									{ $$ = createExpNode(E_EXPR_SKIP, 	NULL, 	1,NULL,NULL, NULL, nbrLines, NULL, NULL); }
		;
Probe	: FULL '(' varref ')'					{ $$ = createExpNode(E_EXPR_FULL, 	NULL, 	0, $3, NULL, NULL, nbrLines, NULL, NULL); }
		| NFULL '(' varref ')'					{ $$ = createExpNode(E_EXPR_NFULL, 	NULL, 	0, $3, NULL, NULL, nbrLines, NULL, NULL); }
		| EMPTY '(' varref ')'					{ $$ = createExpNode(E_EXPR_EMPTY, 	NULL, 	0, $3, NULL, NULL, nbrLines, NULL, NULL); }
		| NEMPTY '(' varref ')'					{ $$ = createExpNode(E_EXPR_NEMPTY,	NULL, 	0, $3, NULL, NULL, nbrLines, NULL, NULL); }
		;
		
basetype: TYPE									{ $$.sVal = NULL; $$.iVal = $1; }
		| UNAME 								{ $$.sVal = $1;   $$.iVal = -1; }
	/*	| error	 e.g., unsigned ':' const */	/* ?! Undefined non-terminal ?! */
		;

typ_list: basetype								{	if($1.iVal > -1) {
														$$ = createSymTabNode($1.iVal, NULL, nbrLines, 1, 0, NULL, NULL, NULL);
													} else {
														$$ = createSymTabNodeUType(*globalSymTab, $1.sVal, NULL, nbrLines, 1, 0, NULL, NULL, NULL);
														if($$ == NULL) printf("The type %s was not declared in a typedef.", $1.sVal);
														free($1.sVal);
													}
												}		
		| basetype ',' typ_list					{	if($1.iVal > -1) {
														$$ = addToSymTab(createSymTabNode($1.iVal, NULL, nbrLines, 1, 0, NULL, NULL, NULL), $3);
													} else {
														ptSymTabNode temp = createSymTabNodeUType(*globalSymTab, $1.sVal, NULL, nbrLines, 1, 0, NULL, NULL, NULL);
														if(temp == NULL) printf("The type %s was not declared in a typedef.", $1.sVal);
														else $$ = addToSymTab(temp, $3);
														free($1.sVal);
													}
												}
		;

/* ProcType and Inline arguments */
args    : /* empty */							{ $$ = NULL; }
		| arg									{ $$ = $1; }
		;

/* Print arguments */
prargs  : /* empty */							{ $$ = NULL; }
		| ',' arg								{ $$ = $2; }
		;

/* Send arguments */
margs   : arg									{ $$ = $1; }
		| expr '(' arg ')'						{ $$ = createExpNode(E_ARGLIST,		NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		;

arg     : expr									{ $$ = createExpNode(E_ARGLIST,		NULL, 	0, $1, NULL, NULL, nbrLines, NULL, NULL); }
		| expr ',' arg							{ $$ = createExpNode(E_ARGLIST,		NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		;

rarg	: varref								{ $$ = createExpNode(E_RARG_VAR,	NULL, 	0,   $1, NULL, NULL, nbrLines, NULL, NULL); }
		| EVAL '(' expr ')'						{ $$ = createExpNode(E_RARG_EVAL,	NULL, 	0,   $3, NULL, NULL, nbrLines, NULL, NULL); } /*  the received parameter must be equal to the mtype of expr */
		| CONST									{ $$ = createExpNode(E_RARG_CONST,	NULL,  $1, NULL, NULL, NULL, nbrLines, NULL, NULL); }
		| '-' CONST %prec UMIN					{ $$ = createExpNode(E_RARG_CONST,	NULL, -$2, NULL, NULL, NULL, nbrLines, NULL, NULL); }
		;

/* Receive arguments */
rargs	: rarg									{ $$ = createExpNode(E_ARGLIST,		NULL, 	0, $1, NULL, NULL, nbrLines, NULL, NULL); }
		| rarg ',' rargs						{ $$ = createExpNode(E_ARGLIST,		NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| rarg '(' rargs ')'					{ $$ = createExpNode(E_ARGLIST,		NULL, 	0, $1,   $3, NULL, nbrLines, NULL, NULL); }
		| '(' rargs ')'							{ $$ = $2; }
		;

nlst	: NAME									{ *mtypes = addMType(*mtypes, $1); }
		| nlst NAME								{ *mtypes = addMType(*mtypes, $2); }
		| nlst ',' /* commas optional */		/* Ignore */
		;
%%
