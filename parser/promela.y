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

#include <stdlib.h>
#include <string>
#include <iostream>

#include "error.h"
#include "symbols.h"
#include "automata.h"
#include "expression.h"

#include "y.tab.h"

#ifdef CPP
extern "C" 
#endif
int yylex(YYSTYPE * yylval_param, symTabNode** globalSymTab);

extern int nbrLines;

int yyerror (symTabNode** globalSymTab, mTypeNode** mtypes, char* msg){
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

%}

%pure_parser
%lex-param		{symTabNode** globalSymTab}
%parse-param 	{symTabNode** globalSymTab}
%parse-param 	{mTypeNode** mtypes}

%union { 
	int       				iVal;
	char*    				sVal;
	double					rVal;
	class dataTuple			pDataVal;
	
	class stmnt*			pStmntVal;
	class stmntOpt*			pStmntOptVal;
	class expr*				pExprVal;
	class exprVarRef*		pExprVarRefVal;
	class exprVarRefName*	pExprVarRefNameVal;
	class exprArgList*		pExprArgListVal;
	class exprRArg*			pExprRArgVal;
	class fsm*				pFsmVal;
	class symTabNode*		pSymTabNodeVal;
	
	enum symTabNode::Type   iType;
}

//%token <iVal> CONST TYPE IF DO
%token <iVal> CONST IF DO
%token <iType> TYPE 

%token <sVal> NAME UNAME PNAME INAME STRING
%token <rVal> REAL
%type  <sVal> aname
%type  <rVal> real_expr
%type  <pStmntVal> step stmnt timed_stmnt Special Stmnt  
%type  <pStmntOptVal> options
%type  <pExprVal> Expr expr full_expr Probe inst
%type  <pExprVarRefVal> varref varref_ cmpnd cmpnd_ sfld sfld_ 
%type  <pExprVarRefNameVal> pfld pfld_
%type  <pExprArgListVal> arg args rargs margs prargs
%type  <pExprRArgVal> rarg
%type  <pDataVal> vardcl basetype ch_init
%type  <pSymTabNodeVal> decl one_decl decl_lst ivar var_list typ_list utype
%type  <pFsmVal> body sequence option

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

start_parsing	: program;

varref_	: cmpnd_								{ $$ = $1; }
		;

pfld_	: NAME									{ 	symTabNode* symbol = *globalSymTab ? (*globalSymTab)->lookupInSymTab($1) : nullptr;
													if(symbol) 
														$$ = new exprVarRefName($1, symbol, nbrLines);
													else $$ = new exprConst((*mtypes)->getMTypeValue($1), nbrLines);		
												}
		;

cmpnd_	: pfld_ sfld_							{ if($1->getType() == astNode::E_VARREF_NAME)
													$$ = new exprVarRef($1, $2, nbrLines); 
												  else
												    $$ = $1;
												}
		;

sfld_	: /* empty */							{ $$ = nullptr; }
		| '.' cmpnd_ %prec DOT					{ $$ = $2;   }
		;
				
/** PROMELA Grammar Rules **/


program	: units
		;

units	: unit									/* dealt with locally */ 
		| units unit							/* dealt with locally */ 
		;

unit	: proc		/* proctype { }       */	/* dealt with locally */ 
		| init		/* init { }           */	/* dealt with locally */
		| events	/* event assertions   */  	{ std::cout << "The 'events' construct is currently not supported."; }
		| one_decl	/* variables, chans   */	{ *globalSymTab = symTabNode::merge(*globalSymTab, $1); }
		| utype		/* user defined types */	{ *globalSymTab = symTabNode::merge(*globalSymTab, $1); }
		| c_fcts	/* c functions etc.   */  	{ std::cout << "Embedded C code is not supported."; }
		| ns		/* named sequence     */  	{ std::cout << "The 'named sequence' construct is currently not supported."; }
		| SEMI		/* optional separator */	/* ignored */			
	/*	| error									 ?! undefined non-terminal */
		;

proc	: inst		/* optional instantiator */	/* returns an EXP_NODE describing the number of initially active procs; */
		  proctype NAME							/* Ignore the proctype nonterminal; use the sval of NAME */
		  '(' decl ')'							
		  Opt_priority							/* Ignore */
		  Opt_enabler							/* Ignore */
		  body									{	$9->setSymTab(symTabNode::merge($5, $9->getSymTab()));
		  											symTabNode* proc = new procSymNode($3, $1, $9, nbrLines);
		  											*globalSymTab = symTabNode::merge(*globalSymTab, proc);
		  										}
		;

proctype: PROCTYPE								/* Ignore */
		| D_PROCTYPE							{ std::cout << "Deterministic proctypes are not supported (only useful for simulation)."; }
		;

inst	: /* empty */							{ $$ = new exprConst(0, nbrLines); }
		| ACTIVE								{ $$ = new exprConst(1, nbrLines); }
		| ACTIVE '[' CONST ']'					{ $$ = new exprConst($3, nbrLines); }
		| ACTIVE '[' NAME ']'					{	symTabNode* var = *globalSymTab? (*globalSymTab)->lookupInSymTab($3) : nullptr;
													if(var == nullptr) std::cout << "The variable "<<$3<<" does not exist.";
													else if(var->getType() != symTabNode::T_INT && var->getType() != symTabNode::T_BYTE && var->getType() != symTabNode::T_SHORT) std::cout << "The variable "<<$3<<" is not of type int, short or bit.";
													else if(var->getInitExpr() == nullptr || var->getInitExpr()->getType() != astNode::E_EXPR_CONST) std::cout << "The variable "<<$3<<" does not have a constant value.";
													else {
														$$ = new exprConst(var->getInitExpr()->getIVal(), nbrLines);
													}
													//delete $3;											
												}
		;

init	: INIT Opt_priority body				{	if(*globalSymTab && (*globalSymTab)->lookupInSymTab("init") != nullptr) 
	std::cout << "This is the second init process; only one is allowed.";
													else {
														symTabNode* chan = new procSymNode("init", $3, nbrLines);
														*globalSymTab = symTabNode::merge(*globalSymTab, chan);
													}

												}				
		;

events	: TRACE body							{ std::cout << "Event sequences (traces) are not supported."; }
		;

utype	: TYPEDEF NAME '{' decl_lst '}'			{	$$ = new tdefSymNode($2, $4, nbrLines);  } 
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

sequence: step									{ 	$$ = new fsm();
													if($1->getType() == astNode::E_DECL) {
														$$->setSymTab($1->getSymbol());
														$1->setSymbol(nullptr);
														delete $1;
													} else if($1->getType() == astNode::E_STMNT) {
														$$->stmnt2fsm($1->getChild0(), *globalSymTab);
														$1->detachChild0();
														delete $1;
													}
												}
		| sequence MS step						{	if($3->getType() == astNode::E_DECL) {
														$$ = $1;
														$$->setSymTab(symTabNode::merge($$->getSymTab(), $3->getSymbol()));
														$3->setSymbol(nullptr);
														delete $3;
													} else if($3->getType() == astNode::E_STMNT) {
														$$ = $1->stmnt2fsm($3->getChild0(), *globalSymTab);
														$3->detachChild0();
														delete $3;
													}
												}
		;
		
step    : one_decl								{ $$ = new decl($1, nbrLines); }
		| XU vref_lst							{ std::cout << "Channel assertions are currently not supported."; }
		| NAME ':' one_decl						{ std::cout << "Declarations with labels are not suported."; }
		| NAME ':' XU							{ std::cout << "Channel assertions are currently not supported."; }
		| stmnt									{ $$ = new stmnt($1, nbrLines); }
		| stmnt UNLESS stmnt					{ std::cout << "Unless statements are currently not supported."; }
		;

timed_stmnt	: WHILE '(' expr ')' WAIT								{ $$ = new stmntWait($3, nbrLines); }
			| WHEN '(' expr ')' DO Stmnt							{ $$ = new stmntWhen($3, $6, nbrLines); }
			| WHEN '(' expr ')' RESET '(' var_list ')'	DO Stmnt	{ $$ = new stmntWhen($3, $10, $7, nbrLines); }
			;

vis		: /* empty */							/* Ignore */
		| HIDDEN								{ std::cout << "The 'hidden' keyword is not supported."; }
		| SHOW									{ std::cout << "The 'show' keyword is not supported."; }
		| ISLOCAL								{ std::cout << "The 'local' keyword is not supported."; }
		;

asgn	: /* empty */							/* Ignore */
		| ASGN									/* Ignore */
		;

		
/* Note: "bit", "bool", "byte", "pid", "short", "int", "unsigned", "chan", "mtype", "clock", all produce a TYPE token with ival which contains the type. */
		
one_decl: vis TYPE var_list						{	symTabNode* cur = $3;
													symTabNode* res = nullptr;
													while(cur != nullptr) {
														symTabNode* tmp = nullptr;
														
														if(cur->getType() == symTabNode::T_NA) {
															symTabNode* next = symTabNode::createSymTabNode($2, *cur);
															next->setLineNb(nbrLines);
															// If type != 0, then the var is a T_CHAN
														
															//cur->getType() = $2
															if(res == nullptr) {
																res = next;
																tmp = next;
															} else {
																tmp->setNext(next);
																tmp = tmp->nextSym();
															}
														} else {
															assert(cur->getType() == symTabNode::T_CHAN);
															symTabNode* next = new chanSymNode(*cur);
															next->setLineNb(nbrLines);
															
															if(res == nullptr) {
																res = next;
																tmp = next;
															} else {
																tmp->setNext(next);
																tmp = tmp->nextSym();
															}
														}
														
														cur = cur->nextSym();
													}
													delete $3;
													$$ = res;
												}
	 	| vis UNAME var_list 					{	symTabNode* type = *globalSymTab? (*globalSymTab)->lookupInSymTab($2) : nullptr;
	 												if(type == nullptr)
	 													std::cout << "The type "<<$2<<" was not declared in a typedef.";
													else {
														symTabNode* cur = $3;
														while(cur != nullptr) {
															//cur->getType() = T_UTYPE;
															cur->setUType(type);
															cur = cur->nextSym();
														}
														$$ = $3;
													}
	 												//delete $2;
												}	
		| vis TYPE asgn '{' nlst '}'			{	if($2 != symTabNode::T_MTYPE) std::cout <<  "This syntax only works for MTYPEs.";
													$$ = nullptr;
													/* The mtype values are added in the nlst rule. */ 
												}
		;

decl_lst: one_decl								{ $$ = $1; }
		| one_decl SEMI decl_lst				{ $$ = symTabNode::merge($1, $3); }
		;

												// Used for the parameters of a proctype
decl    : /* empty */							{ $$ = nullptr; }
		| decl_lst								{ $$ = $1; }
		;

vref_lst: varref								/* Unreachable */
		| varref ',' vref_lst					/* Unreachable */
		;

var_list: ivar									{ $$ = $1; }
		| ivar ',' var_list						{ $$ = symTabNode::merge($1, $3); }
		;

ivar    : vardcl								{ $$ = symTabNode::createSymTabNode($1.iType, nbrLines, $1.sVal); }
		| vardcl ASGN expr						{ 	int mtype;
													if($3->getType() == astNode::E_EXPR_VAR && (mtype = (*mtypes)->getMTypeValue(static_cast<exprVar*>($3)->getExprVarRefName()->getName())) != -1) {
														exprConst* newExpr = new exprConst(mtype, $3->getLineNb());
														delete $3;
														$3 = newExpr;
													}
													$$ = symTabNode::createSymTabNode($1.iType, nbrLines, $1.sVal, $3);
												}
		| vardcl ASGN ch_init					{ $$ = new chanSymNode($1.sVal, $1.iVal, $3.iVal, $3.symTabNodeVal, nbrLines); }
		;

ch_init : '[' CONST ']' OF '{' typ_list '}'		{ $$.iVal = $2; $$.symTabNodeVal = $6; } 
		;

vardcl  : NAME  								{ $$.sVal = $1; $$.iVal = 1; }
		| NAME ':' CONST						{ std::cout << "The 'unsigned' data type is not supported."; }
		| NAME '[' CONST ']'					{ $$.sVal = $1; $$.iVal = $3; }
		;

varref	: cmpnd									{ $$ = $1; }
		;

pfld	: NAME									{ $$ = new exprVarRefName($1, nbrLines); }
		| NAME '[' expr ']'						{ $$ = new exprVarRefName($1, $3, nbrLines); }
		;

cmpnd	: pfld sfld								{ $$ = new exprVarRef($1, $2, nbrLines); }
		| CONTEXT '.' pfld sfld					{ $$ = new exprVarRef($3, $4, nbrLines); }
		;

sfld	: /* empty */							{ $$ = nullptr; }
		| '.' cmpnd %prec DOT					{ $$ = $2;   }
		;
		
stmnt	: Special								{ $$ = $1; }
		| Stmnt									{ $$ = $1; }
		;	

Special : varref RCV rargs						{ $$ = new stmntChanRecv($1, $3, nbrLines); }
		| varref SND margs						{ $$ = new stmntChanSnd($1, $3, nbrLines); }
		| IF options FI 						{ $$ = new stmntIf($2, $1); }
		| DO options OD							{ $$ = new stmntDo($2, $1); }
		| BREAK									{ $$ = new stmntBreak(nbrLines); }
		| GOTO NAME								{ $$ = new stmntGoto($2, nbrLines); }
		| NAME ':' stmnt						{ if($3->getType() == astNode::E_STMNT_LABEL && $3->getChild0() && $3->getChild0()->getType() == astNode::E_STMNT_LABEL) std::cout << "Only two labels per state are supported."; 
												  $$ = new stmntLabel($1, $3, nbrLines); }

Stmnt	: varref ASGN full_expr					{ $$ = new stmntAsgn($1, $3, nbrLines); }
		| varref INCR							{ $$ = new stmntIncr($1, nbrLines); }
		| varref DECR							{ $$ = new stmntDecr($1, nbrLines); }
		| PRINT	'(' STRING prargs ')'			{ $$ = new stmntPrint($3, $4, nbrLines); } 
		| PRINTM '(' varref ')'					{ $$ = new stmntPrintm($3, nbrLines); }
		| PRINTM '(' CONST ')'					{ $$ = new stmntPrintm($3, nbrLines); }
		| ASSERT full_expr						{ $$ = new stmntAssert($2, nbrLines); }
		| ccode									{ std::cout << "Embedded C code is not supported."; }
		| varref R_RCV rargs					{ std::cout << "Sorted send and random receive are not supported."; }
		| varref RCV LT rargs GT				{ std::cout << "Channel poll operations are not supported."; }
		| varref R_RCV LT rargs GT				{ std::cout << "Channel poll operations are not supported."; }
		| varref O_SND margs					{ std::cout << "Sorted send and random receive are not supported."; }
		| full_expr								{ $$ = new stmntExpr($1, nbrLines); }
		| ELSE									{ $$ = new stmntElse(nbrLines); }
		| ATOMIC '{' sequence OS '}'			{ $$ = new stmntAtomic($3, nbrLines); }
		| D_STEP '{' sequence OS '}'			{ std::cout << "Deterministic steps are not yet supported."; }
		| '{' sequence OS '}'					{ $$ = new stmntSeq($2, nbrLines); }
		| INAME '(' args ')' Stmnt				{ std::cout << "Inline calls are not yet supported."; }
		;

options : option								{ $$ = new stmntOpt($1, nbrLines); }
		| option options						{ $$ = new stmntOpt($1, $2, nbrLines); }
		;

option  : SEP sequence OS						{ $$ = $2; }
		;
		

real_expr	: '(' real_expr ')'							{ $$ = $2; }
			| real_expr '+' real_expr					{ $$ = $1 + $3; }
			| real_expr '-' real_expr					{ $$ = $1 - $3; }
			| real_expr '*' real_expr                   { $$ = $1 * $3; }
			| real_expr '/' real_expr                   { $$ = $1 / $3; }
			| REAL										{ $$ = $1;}
			| CONST										{ $$ = $1;}
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
		
expr    : '(' expr ')'							{ $$ = new exprPar		($2, nbrLines); }
		| expr '+' expr							{ $$ = new exprPlus		($1, $3, nbrLines); }
		| expr '-' expr							{ $$ = new exprMinus	($1, $3, nbrLines); }
		| expr '*' expr							{ $$ = new exprTimes	($1, $3, nbrLines); }
		| expr '/' expr							{ $$ = new exprDiv		($1, $3, nbrLines); }
		| expr '%' expr							{ $$ = new exprMod		($1, $3, nbrLines); }
		| expr '&' expr							{ $$ = new exprBitwAnd	($1, $3, nbrLines); }
		| expr '^' expr							{ $$ = new exprBitwXor	($1, $3, nbrLines); }
		| expr '|' expr							{ $$ = new exprBitwOr	($1, $3, nbrLines); }
		| expr GT expr							{ $$ = new exprGT		($1, $3, nbrLines); }
		| expr LT expr							{ $$ = new exprLT		($1, $3, nbrLines); }
		| expr GE expr							{ $$ = new exprGE		($1, $3, nbrLines); }
		| expr LE expr							{ $$ = new exprLE		($1, $3, nbrLines); }
		| expr EQ expr							{ $$ = new exprEQ		($1, $3, nbrLines); }
		| expr NE expr							{ $$ = new exprNE		($1, $3, nbrLines); }
		| expr AND expr							{ $$ = new exprAnd		($1, $3, nbrLines); }
		| expr OR  expr							{ $$ = new exprOr		($1, $3, nbrLines); }
		| expr LSHIFT expr						{ $$ = new exprLShift	($1, $3, nbrLines); }
		| expr RSHIFT expr						{ $$ = new exprRShift	($1, $3, nbrLines); }
		| COUNT '(' expr ')'					{ $$ = new exprCount	($3, nbrLines); }
		| '~' expr								{ $$ = new exprBitwNeg	($2, nbrLines); }
		| '-' expr %prec UMIN					{ 	if($2->getType() != astNode::E_EXPR_CONST) 
														$$ = new exprUMin($2, nbrLines);
													else {
														$2->setIVal(-$2->getIVal());
														$$ = $2;
													}
												} 
		| SND expr %prec NEG					{ $$ = new exprNeg	($2, nbrLines); }
		| '(' expr SEMI expr ':' expr ')'		{ $$ = new exprCond	($2, $4, $6, nbrLines); }
		| RUN aname '(' args ')' Opt_priority	{ $$ = new exprRun	($4, $2, nbrLines); }
		| RUN aname '[' varref ']' '(' args ')' Opt_priority
						     					{ $$ = new exprRun	($7, $4, $2, nbrLines); }
		| LEN '(' varref ')'					{ $$ = new exprLen	($3, nbrLines); }
		| ENABLED '(' expr ')'					{ std::cout << "The enabled keyword is not supported."; }
		| varref RCV '[' rargs ']'				{ std::cout << "Construct not supported."; /* Unclear */ }
		| varref R_RCV '[' rargs ']'			{ std::cout << "Sorted send and random receive are not supported."; }
		| varref								{ $$ = new exprVar	($1, nbrLines); }
		| cexpr									{ std::cout << "Embedded C code is not supported."; }
		| CONST									{ $$ = new exprConst($1, nbrLines); }
		| TRUE									{ $$ = new exprTrue	(nbrLines); }
		| FALSE									{ $$ = new exprFalse(nbrLines); }
		| TIMEOUT								{ $$ = new exprTimeout(nbrLines); }
		| NONPROGRESS							{ std::cout << "The 'np_' variable is not supported."; } /* Global variable (p. 447), true in a state if not labelled progress. */
		| PC_VAL '(' expr ')'					{ std::cout << "The 'pc_value()' construct is not supported."; } /* Predefined function (p. 448). */
		| PNAME '[' expr ']' '@' NAME			{ std::cout << "Construct not supported."; /* Unclear */ }
		| PNAME '[' expr ']' ':' pfld			{ std::cout << "Construct not supported."; /* Unclear */ }
		| PNAME '@' NAME						{ std::cout << "Construct not supported."; /* Unclear */ }
		| PNAME ':' pfld						{ std::cout << "Construct not supported."; /* Unclear */ }
		;
		
Opt_priority:	/* none */
		| PRIORITY CONST						{ std::cout << "The 'priority' construct is related to simulation and not supported."; }
		;

full_expr:	expr								{ $$ = $1; }
		|	Expr								{ $$ = $1; }
		;

Opt_enabler:	/* none */
		| PROVIDED '(' full_expr ')'			{ std::cout << "The 'provided' construct is currently not supported."; }
	/*	| PROVIDED error						{ std::cout << "The 'provided' construct is currently not supported."; } */
		;

/* an Expr cannot be negated - to protect Probe expressions */
Expr	: Probe									{ $$ = $1; }
		| '(' Expr ')'							{ $$ = new exprPar	($2, nbrLines); }
		| Expr AND Expr							{ $$ = new exprAnd	($1, $3, nbrLines); }
		| Expr AND expr							{ $$ = new exprAnd	($1, $3, nbrLines); }
		| Expr OR  Expr							{ $$ = new exprOr	($1, $3, nbrLines); }
		| Expr OR  expr							{ $$ = new exprOr	($1, $3, nbrLines); }
		| expr AND Expr							{ $$ = new exprAnd	($1, $3, nbrLines); }
		| expr OR  Expr							{ $$ = new exprOr	($1, $3, nbrLines); }
		| SKIP									{ $$ = new exprSkip	(nbrLines); }
		;
		
Probe	: FULL '(' varref ')'					{ $$ = new exprFull	($3, nbrLines); }
		| NFULL '(' varref ')'					{ $$ = new exprNFull($3, nbrLines); }
		| EMPTY '(' varref ')'					{ $$ = new exprEmpty($3, nbrLines); }
		| NEMPTY '(' varref ')'					{ $$ = new exprNEmpty($3, nbrLines); }
		;
		
basetype: TYPE									{ $$.sVal = nullptr; $$.iType = $1; }
		| UNAME 								{ $$.sVal = $1; $$.iType = symTabNode::T_UTYPE; }
	/*	| error	 e.g., unsigned ':' const */	/* ?! Undefined non-terminal ?! */
		;

typ_list: basetype								{	if($1.iType != symTabNode::T_UTYPE) {
														$$ = symTabNode::createSymTabNode($1.iType, nbrLines);
													} else {
														symTabNode* pType = *globalSymTab ? (*globalSymTab)->lookupInSymTab($1.sVal) : nullptr;
														$$ = new utypeSymNode(pType, nbrLines);
														if($$ == nullptr) std::cout << "The type "<<$1.sVal<<" was not declared in a typedef.\n";
													}
												}		
		| basetype ',' typ_list					{	if($1.iType != symTabNode::T_UTYPE) {
														$$ = symTabNode::merge($$, symTabNode::createSymTabNode($1.iType, nbrLines));
													} else {
														symTabNode* pType = *globalSymTab ? (*globalSymTab)->lookupInSymTab($1.sVal) : nullptr;
														symTabNode* temp = new utypeSymNode(pType, nbrLines);
														if(temp == nullptr) 
															std::cout << "The type "<<$1.sVal<<" was not declared in a typedef.\n";
														else 
															$$ = symTabNode::merge($3, temp);
													}
												}
		;

/* ProcType and Inline arguments */
args    : /* empty */
		| arg									{ $$ = $1; }
		;

/* Print arguments */
prargs  : /* empty */							{ $$ = nullptr; }
		| ',' arg								{ $$ = $2; }
		;

/* Send arguments */
margs   : arg									{ $$ = $1; }
		| expr '(' arg ')'						{ $$ = new exprArgList(static_cast<exprRArg*>($1), static_cast<exprArgList*>($3), nbrLines); }
		;

arg     : expr									{ $$ = new exprArgList(static_cast<exprRArg*>($1), nbrLines); }
		| expr ',' arg							{ $$ = new exprArgList(static_cast<exprRArg*>($1), static_cast<exprArgList*>($3), nbrLines); }
		;

rarg	: varref								{ $$ = new exprRArgVar($1, nbrLines); }
		| EVAL '(' expr ')'						{ $$ = new exprRArgEval($3, nbrLines); } /*  the received parameter must be equal to the mtype of expr */
		| CONST									{ $$ = new exprRArgConst($1, nbrLines); }
		| '-' CONST %prec UMIN					{ $$ = new exprRArgConst(-$2, nbrLines); }
		;

/* Receive arguments */
rargs	: rarg									{ $$ = new exprArgList($1, nbrLines); }
		| rarg ',' rargs						{ $$ = new exprArgList($1, $3, nbrLines); }
		| rarg '(' rargs ')'					{ $$ = new exprArgList($1, $3, nbrLines); }
		| '(' rargs ')'							{ $$ = $2; }
		;

nlst	: NAME									{ *mtypes = (*mtypes)->addMType($1); }
		| nlst NAME								{ *mtypes = (*mtypes)->addMType($2); }
		| nlst ',' /* commas optional */		/* Ignore */
		;
%%
