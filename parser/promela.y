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

#include "symbols.hpp"
#include "ast.hpp"

#include "y.tab.hpp"

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
mtypedefSymNode* mtypeDef = nullptr;

symTable* currentSymTab = nullptr;
symTable* savedSymTab = nullptr;

std::list<varSymNode*> declSyms;
std::list<varSymNode*> typeLst;
std::list<std::string> params;

int mtypeId = 1;
bool inInline = false;

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
	class exprRArgList*		pExprRArgListVal;
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
%token  SPEC EVENTUALLY ALWAYS GLOBALLY FINALLY UNTIL LTL/* TCTL */

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
%type  <pStmntVal> step stmnt timed_stmnt Special Stmnt proc init utypedef mtypedef body sequence option ns
%type  <pStmntOptVal> options
%type  <pExprVal> Expr expr full_expr Probe
%type  <pConstExprVal> inst
%type  <pExprVarRefVal> varref cmpnd sfld  
%type  <pExprVarRefNameVal> pfld
%type  <pExprRArgListVal> rargs
%type  <pExprRArgVal> rarg
%type  <pExprArgListVal> arg args margs prargs
%type  <pDataVal> vardcl basetype ch_init
%type  <pVarSymVal> ivar


%start start_parsing


%%

start_parsing	: { *globalSymTab = new symTable("global"); symTable::addPredefinedSym(*globalSymTab); currentSymTab = *globalSymTab; } program props
				
/** PROMELA Grammar Rules **/


program	: units	 								{ /*DBUG("REDUCE: units -> program\n")*/}
		;

units	: unit									{ /*DBUG("REDUCE: unit -> units\n")*/ }
		| units unit							{ /*DBUG("REDUCE: units unit -> units\n")*/ }
		;

unit	: proc		/* proctype { }       */	{ /*DBUG("REDUCE: proc -> unit\n")*/ *program = stmnt::merge(*program, $1); }
		| init		/* init { }           */	{ /*DBUG("REDUCE: init -> unit\n")*/ *program = stmnt::merge(*program, $1); }
		| events	/* event assertions   */  	{ assert(false); std::cout << "The 'events' construct is currently not supported."; }
		| one_decl	/* variables, chans   */	{ 
													/*DBUG("REDUCE: one_decl -> unit\n")*/
													stmnt* decl = nullptr;
													if (declSyms.front()->getType() == symbol::T_CHAN) 
														decl = new chanDecl(declSyms, nbrLines);
													else {
														assert(declSyms.front()->getType() != symbol::T_MTYPE_DEF && declSyms.front()->getType() != symbol::T_TDEF);
														decl = new varDecl(declSyms, nbrLines);
													}
													assert(decl);
													declSyms.clear();
													*program = stmnt::merge(*program, decl);
												}
		| utypedef		/* user defined types */{ /*DBUG("REDUCE: utype -> unit\n")*/ *program = stmnt::merge(*program, $1); }
		| mtypedef								{ /*DBUG("REDUCE: mtype -> unit\n")*/ *program = stmnt::merge(*program, $1); }
		| c_fcts	/* c functions etc.   */  	{ std::cout << "Embedded C code is not supported."; 						}
		| ns		/* named sequence     */  	{ /*DBUG("REDUCE: ns -> unit\n")*/ *program = stmnt::merge(*program, $1); 	}
		| SEMI		/* optional separator */	/* ignored */			
	/*	| error									 ?! undefined non-terminal */
		;

proc	: inst		/* optional instantiator */	/* returns an EXP_NODE describing the number of initially active procs; */
		  proctype NAME							
		  										{ 
													nameSpace = $3; savedSymTab = currentSymTab; 
													currentSymTab = currentSymTab->createSubTable(nameSpace); 
													auto predef = new pidSymNode(0, "_pid");
													predef->setMask(symbol::READ_ACCESS | symbol::PREDEFINED); 
													currentSymTab->insert(predef);
												}
		  '(' decl ')'
		  { currentSymTab = savedSymTab; }							
		  Opt_priority							/* Ignore */
		  Opt_enabler							/* Ignore */
		  body									{	
		  											/*DBUG("REDUCE: inst proctype NAME ( decl ) prio ena body -> proc\n")*/
													auto procNbLine = $11->getLineNb();
		  											procSymNode* proc = new procSymNode($3, $1, declSyms, $11, procNbLine);
		  											declSyms.clear();
		  											$$ = new procDecl(proc, procNbLine);
		  											(*globalSymTab)->insert(proc);
		  											nameSpace = "global";
		  											free($3);
		  										}
		;

proctype: PROCTYPE								{ /*DBUG("REDUCE: -> PROCTYPE proctype\n")*/ }
		| D_PROCTYPE							{ std::cout << "Deterministic proctypes are not supported (only useful for simulation)."; }
		;

inst	: /* empty */							{ /*DBUG("REDUCE: void -> inst\n")*/ $$ = new exprConst(0, nbrLines); 	}
		| ACTIVE								{ /*DBUG("REDUCE: ACTIVE -> inst\n")*/ $$ = new exprConst(1, nbrLines); }
		| ACTIVE '[' CONST ']'					{ /*DBUG("REDUCE: ACTIVE [ CONST ] -> inst \n")*/ $$ = new exprConst($3, nbrLines); }
		| ACTIVE '[' NAME ']'					{ 
													/*DBUG("REDUCE: ACTIVE [ NAME ] -> inst\n")*/
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
													/*DBUG("REDUCE: INIT Opt_priority body -> init\n")*/
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

utypedef: TYPEDEF NAME '{' decl_lst '}'			{	
													/*DBUG("REDUCE: TYPEDEF NAME '{' decl_lst '}' -> utype\n")*/
													tdefSymNode* tdef = new tdefSymNode($2, *globalSymTab, declSyms, nbrLines);
													$$ = new tdefDecl(tdef, nbrLines);
													(*globalSymTab)->insert(tdef);
													for(auto declSym : declSyms)
														(*globalSymTab)->remove(declSym->getName());
													declSyms.clear();
													free($2);  
												}
		;
		
mtypedef: vis TYPE  asgn 						{	mtypeDef = new mtypedefSymNode(nbrLines);	} 
							'{' nlst '}' 		{
													assert(mtypeDef->getMTypeList().size() != 0);
													(*globalSymTab)->insert(mtypeDef);

													/*DBUG("REDUCE: vis TYPE asgn { nlst } -> one_decl\n")*/
													if($2 != symbol::T_MTYPE) {
														std::cout <<  "This syntax only works for MTYPEs definition.";
														exit(1);
													}
													$$ = new mtypeDecl(mtypeDef, nbrLines);
													// The mtype values are added in the nlst rule.
												}
		;

nm		: NAME									/* Unreachable */
		| INAME									/* Unreachable */
		;

ns		: INLINE { inInline = true; } 
		  NAME { nameSpace = $3; savedSymTab = currentSymTab; currentSymTab = currentSymTab->createSubTable(nameSpace); } 
		  '(' param_list ')'
		  { for(std::string it : params) 
		  		currentSymTab->insert(varSymNode::createSymbol(symbol::T_NA, nbrLines, it));
		    currentSymTab = savedSymTab;
		  }
		  body									{
													/*DBUG("REDUCE: INLINE nm ( param_list ) body -> ns\n")*/
													auto sym = new inlineSymNode($3, params, $9, nbrLines);
													params.clear();
		  											$$ = new inlineDecl(sym, nbrLines);
													(*globalSymTab)->insert(sym);
													inInline = false;
													free($3);
												}
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

body	: '{' 									{ 
													savedSymTab = currentSymTab; 
													if(!(currentSymTab = (*globalSymTab)->getSubSymTab(nameSpace)))
														currentSymTab = savedSymTab->createSubTable(nameSpace); 
													nameSpace = "";
												} 
				sequence OS 
		  '}'									{ /*DBUG("REDUCE: '{' sequence OS '}' -> body\n")*/ $$ = $3; $$->setLocalSymTab(currentSymTab); currentSymTab->setBlock($3); currentSymTab = savedSymTab; }
		;

sequence: step									{ /*DBUG("REDUCE: step -> sequence\n")*/ $$ = $1;  }
		| sequence MS step						{ /*DBUG("REDUCE: sequence MS step -> sequence\n")*/ $$ = stmnt::merge($1, $3); }
		| sequence step							{ /*DBUG("REDUCE: sequence step -> sequence\n")*/ $$ = stmnt::merge($1, $2); }
		;
		
step    : one_decl								{ 
													assert(declSyms.front()->getType() != symbol::T_MTYPE_DEF); 
												 	$$ = new varDecl(static_cast<std::list<varSymNode*>>(declSyms), nbrLines);
												 	declSyms.clear();
												}
		| NAME ':' one_decl						{ std::cout << "Declarations with labels are not suported."; }
		| NAME ':' XU							{ std::cout << "Channel assertions are currently not supported."; }
		| stmnt									{ /*DBUG("REDUCE: stmnt -> step\n")*/ $$ = $1; }
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
		
one_decl: vis TYPE { declType = $2; } var_list	{ /*DBUG("REDUCE: vis TYPE var_list -> one_decl\n")*/ }
	 	| vis UNAME { declType = symbol::T_UTYPE; typeDef = *globalSymTab? static_cast<tdefSymNode*>((*globalSymTab)->lookup($2)) : nullptr; assert(typeDef); } var_list 			{ /*DBUG("REDUCE: vis UNAME var_list -> one_decl\n")*/ free($2); }
		;

decl_lst: one_decl								{ /*DBUG("REDUCE: one_decl -> decl_list\n")*/ }
		| one_decl SEMI decl_lst				{ /*DBUG("REDUCE: one_decl SEMI decl_list -> decl_lst\n")*/ }
		;

												// Used for the parameters of a proctype
decl    : /* empty */							{ /*DBUG("REDUCE: void -> decl\n")*/ }
		| decl_lst								{ /*DBUG("REDUCE: decl_list -> decl\n")*/ }
		;

//vref_lst: varref								/* Unreachable */
//		| varref ',' vref_lst					/* Unreachable */
		;

var_list: ivar									{ /*DBUG("REDUCE: ivar -> var_list\n")*/ currentSymTab->insert($1); declSyms.push_front($1); }
		| ivar ',' var_list						{ /*DBUG("REDUCE: ivar , var_list -> var_list\n")*/ currentSymTab->insert($1); declSyms.push_front($1); }
		;

ivar    : vardcl								{ 
												  /*DBUG("REDUCE: var_decl -> ivar\n")*/ $$ = varSymNode::createSymbol(declType, nbrLines, $1.sVal, $1.iVal); 
												  if(declType == symbol::T_UTYPE) { assert(typeDef); static_cast<utypeSymNode*>($$)->setUType(typeDef); }
												  if($1.sVal) free($1.sVal);
												}
		| vardcl ASGN expr						{ /*DBUG("REDUCE: var_decl ASGN expr -> ivar\n")*/ 
												  $$ = varSymNode::createSymbol(declType, nbrLines, $1.sVal, $1.iVal, $3); 
												  if(declType == symbol::T_UTYPE) { assert(typeDef); static_cast<utypeSymNode*>($$)->setUType(typeDef); }
												  if($1.sVal) free($1.sVal);
												}
		| vardcl ASGN ch_init					{ /*DBUG("REDUCE: var_decl ASGN ch_init -> ivar\n")*/ $$ = new chanSymNode(nbrLines, $1.sVal, $1.iVal, $3.iVal, typeLst);	
												  typeLst.clear(); if($1.sVal) free($1.sVal); //double free???if($3.sVal) free($3.sVal); 
												}
		;

param_list	: 									{ }
			| NAME								{ params.push_front(std::string($1)); free($1); }
			| NAME ',' param_list	            { params.push_front(std::string($1)); free($1); }
			;


ch_init : '[' CONST ']' OF '{' typ_list '}'		{ /*DBUG("REDUCE: [ CONST ] OF { typ_list } -> ch_init\n")*/ $$.iVal = $2; } 
		;
				
basetype: TYPE									{ $$.sVal = nullptr; $$.iType = $1; }
		| UNAME 								{ $$.sVal = $1; $$.iType = symbol::T_UTYPE; }
	/*	| error	 e.g., unsigned ':' const */	/* ?! Undefined non-terminal ?! */
		;

typ_list: basetype								{	/*DBUG("REDUCE: basetype -> typ_list\n")*/
													varSymNode* typ = nullptr;
													if($1.iType != symbol::T_UTYPE && $1.iType != symbol::T_NA) {
														typ = varSymNode::createSymbol($1.iType, nbrLines);
													} else {
														tdefSymNode* pType = *globalSymTab ? dynamic_cast<tdefSymNode*>((*globalSymTab)->lookup($1.sVal)) : nullptr;
														typ = new utypeSymNode(pType, nbrLines);
														if(typ == nullptr) {
															std::cout << "The type "<<$1.sVal<<" was not declared in a typedef.\n";
															assert(false);
														}
													}
													typeLst.push_back(typ);
													if($1.sVal) free($1.sVal);
												}		
		| basetype ',' typ_list					{	/*DBUG("REDUCE: basetype , typ_list -> typ_list\n")*/
													varSymNode* typ = nullptr;
													if($1.iType != symbol::T_UTYPE && $1.iType != symbol::T_NA) {
														typ = varSymNode::createSymbol($1.iType, nbrLines);
													} else {
														tdefSymNode* pType = *globalSymTab ? dynamic_cast<tdefSymNode*>((*globalSymTab)->lookup($1.sVal)) : nullptr;
														typ = new utypeSymNode(pType, nbrLines);
														if(typ == nullptr) {
															std::cout << "The type "<<$1.sVal<<" was not declared in a typedef.\n";
															assert(false);
														}
													}
													typeLst.push_front(typ);
													if($1.sVal) free($1.sVal);
												}
		;

vardcl  : NAME  								{ /*/*DBUG("REDUCE: NAME -> vardcl\n"*)*/ $$.sVal = $1; $$.iVal = 1; }
		| NAME ':' CONST						{ std::cout << "The 'unsigned' data type is not supported."; }
		| NAME '[' CONST ']'					{ /*DBUG("REDUCE: NAME [ CONST ] -> vardcl\n")*/ $$.sVal = $1; $$.iVal = $3; }
		;

varref	: cmpnd									{ /*DBUG("REDUCE: cmpnd -> varref\n")*/ $$ = $1; symbol* sym = nullptr; if(!inInline) sym = $$->resolve(currentSymTab); assert(sym || inInline); }
		;

pfld	: NAME									{ /*DBUG("REDUCE: NAME -> pfld\n")*/ $$ = new exprVarRefName($1, nbrLines); free($1); }
		| NAME '[' expr ']'						{ /*DBUG("REDUCE: NAME [ expr ] -> pfld\n")*/ $$ = new exprVarRefName($1, $3, nbrLines); free($1); }
		;

cmpnd	: pfld sfld								{ /*DBUG("REDUCE: pfld sfld -> cmpnd\n")*/ $$ = new exprVarRef(nbrLines, $1, $2); }
		| CONTEXT '.' pfld sfld					{ /*DBUG("REDUCE: CONTEX . pfld sfld -> cmpnd\n")*/ $$ = new exprVarRef(nbrLines, $3, $4); }
		;

sfld	: 										{ /*DBUG("REDUCE: void -> sfld\n")*/ $$ = nullptr; }
		| '.' cmpnd %prec DOT					{ /*DBUG("REDUCE: . cmpnd -> sfld\n")*/ $$ = $2;   }
		;

		
stmnt	: Special								{ /*DBUG("REDUCE: special -> stmnt\n")*/ $$ = $1; }
		| Stmnt									{ /*DBUG("REDUCE: Stmnt -> stmnt\n")*/ $$ = $1; }
		;	

Special : varref RCV rargs						{ $$ = new stmntChanRecv($1, $3, nbrLines); }
		| varref SND margs						{ $$ = new stmntChanSnd($1, $3, nbrLines); }
		| IF options FI 						{ $$ = new stmntIf($2, $1); }
		| DO options OD							{ $$ = new stmntDo($2, $1); }
		| BREAK									{ $$ = new stmntBreak(nbrLines); }
		| GOTO NAME								{ $$ = new stmntGoto($2, nbrLines); free($2); }
		| NAME ':' stmnt						{ if($3->getType() == astNode::E_STMNT_LABEL && static_cast<stmntLabel*>($3)->getLabelled()->getType() == astNode::E_STMNT_LABEL) 
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
		| D_STEP '{' sequence OS '}'			{ $$ = new stmntDStep($3, nbrLines); }
		| '{' sequence OS '}'					{ $$ = new stmntSeq($2, nbrLines); }
		| INAME '(' args ')' 					{ 
													$$ = new stmntCall($1, $3, nbrLines); 
													auto fctSym = (*globalSymTab)->lookup($1);
													std::cout << "Inline call "<< $1 <<" at line "<< nbrLines <<"\n";
													assert(fctSym->getType() == symbol::T_INLINE);
													assert(dynamic_cast<inlineSymNode*>(fctSym) != nullptr);
													if($3)
														assert(dynamic_cast<inlineSymNode*>(fctSym)->getParams().size() == $3->getSize());
													free($1); 
												}
		;

options : option								{ $$ = new stmntOpt($1, nbrLines); }
		| option options						{ $$ = new stmntOpt($1, $2, nbrLines); }
		;

option  : SEP sequence OS						{ $$ = $2; }
		| SEP '[' real_expr ']' sequence OS		{ $$ = $5; $5->setProb($3); }
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
														exprConst* tmp = dynamic_cast<exprConst*>($2);
														$$ = new exprConst(- tmp->getCstValue(), nbrLines);
														delete tmp;
													}
												} 
		| SND expr %prec NEG					{ $$ = new exprNeg	($2, nbrLines); }
		| '(' expr SEMI expr ':' expr ')'		{ $$ = new exprCond	($2, $4, $6, nbrLines); }
		| RUN aname '(' args ')' Opt_priority	{ auto run = new exprRun ($2, $4, nbrLines);
												  $$ = run;
												  auto procSym = run->resolve(*globalSymTab); 
												  assert(procSym); free($2); 
												}
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
		| PRIORITY CONST						{ assert(false); std::cout << "The 'priority' construct is related to simulation and not supported."; }
		;

full_expr:	expr								{ $$ = $1; }
		|	Expr								{ $$ = $1; }
		;

Opt_enabler:	/* none */
		| PROVIDED '(' full_expr ')'			{ assert(false); std::cout << "The 'provided' construct is currently not supported."; }
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
args    : /* empty */                           { $$ = nullptr; }
		| arg									{ $$ = $1; }
		;

/* Print arguments */
prargs  : /* empty */							{ $$ = nullptr; }
		| ',' arg								{ $$ = $2; }
		;

/* Send arguments */
margs   : arg									{ $$ = $1; }
		| expr '(' arg ')'						{ assert(false); }//$$ = new exprArgList(static_cast<exprRArg*>($1), static_cast<exprArgList*>($3), nbrLines); }
		;

arg     : expr									{ $$ = new exprArgList(new exprArg($1, nbrLines), nbrLines); }
		| expr ',' arg							{ $$ = new exprArgList(new exprArg($1, nbrLines), $3, nbrLines); }
		;

rarg	: varref								{ $$ = new exprRArgVar($1, nbrLines); }
		| EVAL '(' expr ')'						{ $$ = new exprRArgEval($3, nbrLines); } /*  the received parameter must be equal to the mtype of expr */
		| CONST									{ $$ = new exprRArgConst(new exprConst($1, nbrLines), nbrLines); }
		| '-' CONST %prec UMIN					{ $$ = new exprRArgConst(new exprConst(-$2, nbrLines), nbrLines); }
		;

/* Receive arguments */
rargs	: rarg									{ $$ = new exprRArgList($1, nbrLines); }
		| rarg ',' rargs						{ $$ = new exprRArgList($1, $3, nbrLines); }
		| rarg '(' rargs ')'					{ $$ = new exprRArgList($1, $3, nbrLines); }
		| '(' rargs ')'							{ $$ = $2; }
		;

nlst	: NAME									{ /*DBUG("REDUCE: NAME -> nlst\n")*/ cmtypeSymNode* sym = new cmtypeSymNode(nbrLines, mtypeDef, $1, mtypeId++); (*globalSymTab)->insert(sym); free($1); }
		| nlst NAME								{ /*DBUG("REDUCE: nlst NAME -> NAME\n")*/ cmtypeSymNode* sym = new cmtypeSymNode(nbrLines, mtypeDef, $2, mtypeId++); (*globalSymTab)->insert(sym); free($2); }
		| nlst ',' /* commas optional */		{ /*DBUG("REDUCE: nlst , -> nlst\n")*/ }
		;
		
		
props	: /* empty */
		| prop
		| prop props
	;
	
prop	: LTL NAME '{' prop_expr '}'
		;


prop_expr	: '(' prop_expr ')'
		| quants prop_expr							
		| prop_expr '+' prop_expr
		| prop_expr '-' prop_expr
		| prop_expr '*' prop_expr
		| prop_expr '/' prop_expr
		| prop_expr '%' prop_expr
		| prop_expr '&' prop_expr
		| prop_expr '^' prop_expr
		| prop_expr '|' prop_expr
		| prop_expr GT prop_expr
		| prop_expr LT prop_expr
		| prop_expr GE prop_expr
		| prop_expr LE prop_expr
		| prop_expr EQ prop_expr
		| prop_expr NE prop_expr
		| prop_expr AND prop_expr
		| prop_expr OR prop_expr
		| prop_expr SEMI prop_expr
		| prop_expr UNTIL prop_expr
		| SND prop_expr %prec NEG
		| varref
		| CONST
		;
	
quants	: quant
	| quant quants
	;
	
quant	: ALWAYS 
	| EVENTUALLY
	;
%%
