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
#include <list>

#include "symbols.h"
#include "expression.h"

#include "y.tab.h"

#define YYDEBUG 1

#ifdef CPP
extern "C" 
#endif
int yylex(YYSTYPE * yylval_param, symTable** globalSymTab);

extern int nbrLines;

int yyerror (symTable** globalSymTab, stmnt** program, const char* msg){
	fprintf(stderr, "Syntax error on line %d: '%s'.\n", nbrLines, msg);
	exit(1);
}

std::string nameSpace = "global";
symbol::Type declType = symbol::T_NA;
tdefSymNode* typeDef = nullptr;

symTable* currentSymTab = nullptr;
symTable* savedSymTab = nullptr;

std::list<varSymNode*> declSyms;
std::list<symbol*> typeLst;
std::unordered_map<std::string, cmtypeSymNode*> mtypes; 

int mtypeId = 0;

%}

%error-verbose
%debug
%pure_parser
%lex-param		{symTable** globalSymTab}
%parse-param 	{symTable** globalSymTab}
%parse-param	{stmnt** program}

%union { 
	int       				iVal;
	char*    				sVal;
	double					rVal;
	class dataTuple			pDataVal;
	
	class stmnt*			pStmntVal;
	class stmntOpt*			pStmntOptVal;
	class expr*				pExprVal;
	class exprConst*		pConstExprVal;
	class exprVarRef*		pExprVarRefVal;
	class exprVarRefName*	pExprVarRefNameVal;
	class exprArgList*		pExprArgListVal;
	class exprRArg*			pExprRArgVal;
	
	class symbol*			pSymTabVal;
	class varSymNode*		pVarSymVal;
	class tdefSymNode*		pTdefSymVal;
	class mtypedefSymNode*	pTypedefSymVal;
	
	enum symbol::Type   iType;
}

//%token <iVal> CONST TYPE IF DO
%token <iVal> CONST IF DO
%token <iType> TYPE 
%token <sVal> NAME UNAME PNAME INAME STRING
%token <rVal> REAL
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

%type  <sVal> aname
%type  <rVal> real_expr
%type  <pStmntVal> step stmnt timed_stmnt Special Stmnt proc init utype mtype body sequence option
%type  <pStmntOptVal> options
%type  <pExprVal> Expr expr full_expr Probe
%type  <pConstExprVal> inst
%type  <pExprVarRefVal> varref cmpnd sfld  
%type  <pExprVarRefNameVal> pfld
%type  <pExprArgListVal> arg args rargs margs prargs
%type  <pExprRArgVal> rarg
%type  <pDataVal> vardcl basetype ch_init
%type  <pVarSymVal> ivar


%start start_parsing


%%

start_parsing	: { *globalSymTab = new symTable("global"); symTable::addPredefinedSym(*globalSymTab); currentSymTab = *globalSymTab; } program;
				
/** PROMELA Grammar Rules **/


program	: units	 								{ std::cout<< "REDUCE: units -> program\n"; }
		;

units	: unit									{ std::cout<< "REDUCE: unit -> units\n"; }
		| units unit							{ std::cout<< "REDUCE: units unit -> units\n"; }
		;

unit	: proc		/* proctype { }       */	{ std::cout<< "REDUCE: proc -> unit\n"; *program = stmnt::merge(*program, $1); }
		| init		/* init { }           */	{ std::cout<< "REDUCE: init -> unit\n"; *program = stmnt::merge(*program, $1); }
		| events	/* event assertions   */  	{ std::cout << "The 'events' construct is currently not supported."; }
		| one_decl	/* variables, chans   */	{ 
													std::cout << "REDUCE: one_decl -> unit\n";
													stmnt* decl = nullptr;
													if (declSyms.front()->getType() == symbol::T_CHAN) 
														decl = new chanDecl(declSyms, nbrLines);
													else {
														assert(declSyms.front()->getType() != symbol::T_MTYPE_DEF && declSyms.front()->getType() != symbol::T_UTYPE);
														decl = new varDecl(declSyms, nbrLines);
													}
													assert(decl);
													declSyms.clear();
													*program = stmnt::merge(*program, decl);
												}
		| utype		/* user defined types */	{ std::cout << "REDUCE: utype -> unit\n"; *program = stmnt::merge(*program, $1); }
		| mtype									{ std::cout << "REDUCE: mtype -> unit\n"; *program = stmnt::merge(*program, $1); }
		| c_fcts	/* c functions etc.   */  	{ std::cout << "Embedded C code is not supported."; }
		| ns		/* named sequence     */  	{ std::cout << "The 'named sequence' construct is currently not supported."; }
		| SEMI		/* optional separator */	/* ignored */			
	/*	| error									 ?! undefined non-terminal */
		;

proc	: inst		/* optional instantiator */	/* returns an EXP_NODE describing the number of initially active procs; */
		  proctype NAME							
		  { nameSpace = $3; }
		  '(' decl ')'							
		  Opt_priority							/* Ignore */
		  Opt_enabler							/* Ignore */
		  body									{	
		  											std::cout<< "REDUCE: inst proctype NAME ( decl ) prio ena body -> proc\n";
		  											procSymNode* proc = new procSymNode($3, $1, declSyms, $10, nbrLines);
		  											symTable* local = proc->getBlock()->getLocalSymTab();
		  											if(local)
		  												for(auto s : declSyms)
		  													local->insert(s);
		  											declSyms.clear();
		  											$$ = new procDecl(proc, nbrLines);
		  											(*globalSymTab)->insert(proc);
		  											nameSpace = "global";
		  											free($3);
		  										}
		;

proctype: PROCTYPE								{ std::cout << "REDUCE: -> PROCTYPE proctype\n"; }
		| D_PROCTYPE							{ std::cout << "Deterministic proctypes are not supported (only useful for simulation)."; }
		;

inst	: /* empty */							{ std::cout << "REDUCE: void -> inst\n"; $$ = new exprConst(0, nbrLines); }
		| ACTIVE								{ std::cout << "REDUCE: ACTIVE -> inst\n"; $$ = new exprConst(1, nbrLines); }
		| ACTIVE '[' CONST ']'					{ std::cout << "REDUCE: ACTIVE [ CONST ] -> inst \n"; $$ = new exprConst($3, nbrLines); }
		| ACTIVE '[' NAME ']'					{ 
													std::cout << "REDUCE: ACTIVE [ NAME ] -> inst\n";
													varSymNode* var = *globalSymTab? static_cast<varSymNode*>((*globalSymTab)->lookup($3)) : nullptr;
													if(var == nullptr) std::cout << "The variable "<<$3<<" does not exist.";
													else if(var->getType() != symbol::T_INT && var->getType() != symbol::T_BYTE && var->getType() != symbol::T_SHORT) std::cout << "The variable "<<$3<<" is not of type int, short or bit.";
													else if(var->getInitExpr() == nullptr || var->getInitExpr()->getType() != astNode::E_EXPR_CONST) std::cout << "The variable "<<$3<<" does not have a constant value.";
													else {
														$$ = new exprConst(static_cast<exprConst*>(var->getInitExpr())->getCstValue(), nbrLines);
													}
													free($3);											
												}
		;

init	: INIT 
		{ nameSpace = "init"; } 
		Opt_priority 
		body 									{	
													std::cout << "REDUCE: INIT Opt_priority body -> init\n";
													if(*globalSymTab && (*globalSymTab)->lookup("init") != nullptr) 
														std::cout << "This is the second init process; only one is allowed.";
													else {
														initSymNode* init = new initSymNode(nbrLines, $4);
														$$ = new initDecl(init, nbrLines);
														(*globalSymTab)->insert(init);
													}
													nameSpace = "global";
												}				
		;

events	: TRACE body							{ std::cout << "Event sequences (traces) are not supported."; }
		;

utype	: TYPEDEF NAME '{' decl_lst '}'			{	
													std::cout << "REDUCE: TYPEDEF NAME '{' decl_lst '}' -> utype\n";
													tdefSymNode* tdef = new tdefSymNode($2, declSyms, nbrLines);
													declSyms.clear();
													$$ = new tdefDecl(tdef, nbrLines);
													(*globalSymTab)->insert(tdef);
													free($2);  
												}
		;
		
mtype 	: vis TYPE asgn '{' nlst '}'			{	
													std::cout << "REDUCE: vis TYPE asgn { nlst } -> one_decl\n";
													if($2 != symbol::T_MTYPE) {
														std::cout <<  "This syntax only works for MTYPEs.";
														exit(1);
													}
													mtypedefSymNode* mtypeDef = new mtypedefSymNode(mtypes, nbrLines);
													mtypes.clear();
													(*globalSymTab)->insert(mtypeDef);
													$$ = new mtypeDecl(mtypeDef, nbrLines);
													// The mtype values are added in the nlst rule.
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

body	: '{' 									{ savedSymTab = currentSymTab; currentSymTab = currentSymTab->createSubTable(nameSpace); nameSpace = ""; } 
				sequence OS 
		  '}'									{ std::cout << "REDUCE: '{' sequence OS '}' -> body\n"; $$ = $3; $$->setLocalSymTab(currentSymTab); currentSymTab->setBlock($3); currentSymTab = savedSymTab; }
		;

sequence: step									{ std::cout << "REDUCE: step -> sequence\n"; $$ = $1;  }
		| sequence MS step						{ std::cout << "REDUCE: sequence MS step -> sequence\n"; $$ = stmnt::merge($1, $3); }
		;
		
step    : one_decl								{ 
													assert(declSyms.front()->getType() != symbol::T_MTYPE_DEF && declSyms.front()->getType() != symbol::T_CHAN); 
												 	$$ = new varDecl(static_cast<std::list<varSymNode*>>(declSyms), nbrLines);
												 	declSyms.clear();
												}
		| NAME ':' one_decl						{ std::cout << "Declarations with labels are not suported."; }
		| NAME ':' XU							{ std::cout << "Channel assertions are currently not supported."; }
		| stmnt									{ std::cout << "REDUCE: stmnt -> step\n"; $$ = $1; }
		| stmnt UNLESS stmnt					{ std::cout << "Unless statements are currently not supported."; }
		;

timed_stmnt	: WHILE '(' expr ')' WAIT								{ $$ = new stmntWait($3, nbrLines); }
			| WHEN '(' expr ')' DO Stmnt							{ $$ = new stmntWhen($3, $6, nbrLines); }
			| WHEN '(' expr ')' RESET '(' var_list ')'	DO Stmnt	{ $$ = new stmntWhen($3, $10, declSyms, nbrLines); declSyms.clear(); }
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
		
one_decl: vis TYPE { declType = $2; } var_list	{ std::cout << "REDUCE: vis TYPE var_list -> one_decl\n"; }
	 	| vis UNAME { declType = symbol::T_UTYPE; typeDef = *globalSymTab? static_cast<tdefSymNode*>((*globalSymTab)->lookup($2)) : nullptr; assert(typeDef); } var_list 			{ std::cout << "REDUCE: vis UNAME var_list -> one_decl\n"; free($2); }
		;

decl_lst: one_decl								{ std::cout << "REDUCE: one_decl -> decl_list\n"; }
		| one_decl SEMI decl_lst				{ std::cout << "REDUCE: one_decl SEMI decl_list -> decl_lst\n"; }
		;

												// Used for the parameters of a proctype
decl    : /* empty */							{ std::cout << "REDUCE: void -> decl\n"; }
		| decl_lst								{ std::cout << "REDUCE: decl_list -> decl\n"; }
		;

//vref_lst: varref								/* Unreachable */
//		| varref ',' vref_lst					/* Unreachable */
		;

var_list: ivar									{ std::cout << "REDUCE: ivar -> var_list\n"; currentSymTab->insert($1); declSyms.push_front($1); }
		| ivar ',' var_list						{ std::cout << "REDUCE: ivar , var_list -> var_list\n"; }
		;

ivar    : vardcl								{ std::cout << "REDUCE: var_decl -> ivar\n"; $$ = varSymNode::createSymbol(declType, nbrLines, $1.sVal, $1.iVal); if(declType == symbol::T_UTYPE) { assert(typeDef); static_cast<utypeSymNode*>($$)->setUType(typeDef); } }
		| vardcl ASGN expr						{ std::cout << "REDUCE: var_decl ASGN expr -> ivar\n"; $$ = varSymNode::createSymbol(declType, nbrLines, $1.sVal, $1.iVal, $3); if(declType == symbol::T_UTYPE) { assert(typeDef); static_cast<utypeSymNode*>($$)->setUType(typeDef); } }
		| vardcl ASGN ch_init					{ std::cout << "REDUCE: var_decl ASGN ch_init -> ivar\n"; $$ = new chanSymNode(nbrLines, $1.sVal, $1.iVal, $3.iVal, typeLst); typeLst.clear(); }
		;

ch_init : '[' CONST ']' OF '{' typ_list '}'		{ std::cout << "REDUCE: [ CONST ] OF { typ_list } -> ch_init\n"; $$.iVal = $2; } 
		;
				
basetype: TYPE									{ $$.sVal = nullptr; $$.iType = $1; }
		| UNAME 								{ $$.sVal = $1; $$.iType = symbol::T_UTYPE; }
	/*	| error	 e.g., unsigned ':' const */	/* ?! Undefined non-terminal ?! */
		;

typ_list: basetype								{	std::cout << "REDUCE: basetype -> typ_list\n";
													varSymNode* typ = nullptr;
													if($1.iType != symbol::T_UTYPE && $1.iType != symbol::T_NA) {
														typ = varSymNode::createSymbol($1.iType, nbrLines);
													} else {
														tdefSymNode* pType = *globalSymTab ? static_cast<tdefSymNode*>((*globalSymTab)->lookup($1.sVal)) : nullptr;
														typ = new utypeSymNode(pType, nbrLines);
														if(typ == nullptr) 
															std::cout << "The type "<<$1.sVal<<" was not declared in a typedef.\n";
													}
													typeLst.push_front(typ);
												}		
		| basetype ',' typ_list					{	std::cout << "REDUCE: basetype , typ_list -> typ_list\n"; }
		;

vardcl  : NAME  								{ std::cout << "REDUCE: NAME -> vardcl\n"; $$.sVal = $1; $$.iVal = 1; }
		| NAME ':' CONST						{ std::cout << "The 'unsigned' data type is not supported."; }
		| NAME '[' CONST ']'					{ std::cout << "REDUCE: NAME [ CONST ] -> vardcl\n"; $$.sVal = $1; $$.iVal = $3; }
		;

varref	: cmpnd									{ std::cout << "REDUCE: cmpnd -> varref\n"; $$ = $1; $$->resolve(currentSymTab); }
		;

pfld	: NAME									{ std::cout << "REDUCE: NAME -> pfld\n"; $$ = new exprVarRefName($1, nbrLines); free($1); }
		| NAME '[' expr ']'						{ std::cout << "REDUCE: NAME [ expr ] -> pfld\n"; $$ = new exprVarRefName($1, $3, nbrLines); free($1); }
		;

cmpnd	: pfld sfld								{ std::cout << "REDUCE: pfld sfld -> cmpnd\n"; $$ = new exprVarRef(nbrLines, $1, $2); }
		| CONTEXT '.' pfld sfld					{ std::cout << "REDUCE: CONTEX . pfld sfld -> cmpnd\n"; $$ = new exprVarRef(nbrLines, $3, $4); }
		;

sfld	: 										{ std::cout << "REDUCE: void -> sfld\n"; $$ = nullptr; }
		| '.' cmpnd %prec DOT					{ std::cout << "REDUCE: . cmpnd -> sfld\n"; $$ = $2;   }
		;

		
stmnt	: Special								{ std::cout << "REDUCE: special -> stmnt\n"; $$ = $1; }
		| Stmnt									{ std::cout << "REDUCE: Stmnt -> stmnt\n"; $$ = $1; }
		;	

Special : varref RCV rargs						{ $$ = new stmntChanRecv($1, $3, nbrLines); }
		| varref SND margs						{ $$ = new stmntChanSnd($1, $3, nbrLines); }
		| IF options FI 						{ $$ = new stmntIf($2, $1); }
		| DO options OD							{ $$ = new stmntDo($2, $1); }
		| BREAK									{ $$ = new stmntBreak(nbrLines); }
		| GOTO NAME								{ $$ = new stmntGoto($2, nbrLines); free($2); }
		| NAME ':' stmnt						{ if($3->getType() == astNode::E_STMNT_LABEL && static_cast<stmntLabel*>($3)->getLabelledStmnt()->getType() == astNode::E_STMNT_LABEL) 
													std::cout << "Only two labels per state are supported."; 
												  $$ = new stmntLabel($1, $3, nbrLines); free($1); }

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
														exprConst* tmp = static_cast<exprConst*>($2);
														tmp->setCstValue(- tmp->getCstValue());
														$$ = tmp;
													}
												} 
		| SND expr %prec NEG					{ $$ = new exprNeg	($2, nbrLines); }
		| '(' expr SEMI expr ':' expr ')'		{ $$ = new exprCond	($2, $4, $6, nbrLines); }
		| RUN aname '(' args ')' Opt_priority	{ $$ = new exprRun	($2, $4, nbrLines); }
		| RUN aname '[' varref ']' '(' args ')' Opt_priority
						     					{ $$ = new exprRun	($2, $7, $4, nbrLines); }
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

nlst	: NAME									{ std::cout << "REDUCE: NAME -> nlst\n"; cmtypeSymNode* sym = new cmtypeSymNode(nbrLines, $1, mtypeId++); mtypes[$1] = sym; (*globalSymTab)->insert(sym); free($1); }
		| nlst NAME								{ std::cout << "REDUCE: nlst NAME -> NAME\n"; cmtypeSymNode* sym = new cmtypeSymNode(nbrLines, $2, mtypeId++); mtypes[$2] = sym; (*globalSymTab)->insert(sym); free($2); }
		| nlst ',' /* commas optional */		{ std::cout << "REDUCE: nlst , -> nlst\n"; }
		;
%%
