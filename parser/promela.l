%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "symbols.h"
#include "automata.h"
#include "expression.h"

#include "y.tab.h"

#define YY_DECL int yylex(YYSTYPE * yylval_param, symTabNode** globalSymTab)

int nbrLines = 0;
char strBuffer[1024];
int strBufferLen = 0;

%}

%option bison-bridge
%option header-file="lexer.h"
%option noyywrap
%s CODE COMMENTBLOCK COMMENTLINE STRINGBLOCK CPPBLOCK

letter    [A-Za-z]
digit     [0-9]
id        ({letter}|_)({letter}|{digit}|_)*
number    {digit}+
real	  {number}[.]{number}
blank     [ \t]+
symbol    [*+/%^!&~\|?:,.()\-\[\]\{\}] 

%%


<CODE>"::"       	{ return SEP; }
<CODE>"->"       	{ return SEMI; }
<CODE>";"        	{ return SEMI; }
<CODE>"--"       	{ return DECR; }
<CODE>"++"       	{ return INCR; }
<CODE>"<<"       	{ return LSHIFT; }
<CODE>"<="       	{ return LE; }
<CODE>"<"        	{ return LT; }
<CODE>">>"       	{ return RSHIFT; }
<CODE>">="       	{ return GE; }
<CODE>"=>"			{ return IMPLIES; }
<CODE>">"        	{ return GT; }
<CODE>"=="       	{ return EQ; }
<CODE>"="        	{ return ASGN; }
<CODE>"!="       	{ return NE; }
<CODE>"!!"       	{ return O_SND; /* Sorted send, p.48 */ }
<CODE>"!"        	{ return SND; }
<CODE>"??"       	{ return R_RCV; /* Random receive, p.48 */ }
<CODE>"?"        	{ return RCV; }
<CODE>"&&"       	{ return AND; }
<CODE>"||"       	{ return OR; }
<CODE>"spec"		{ return SPEC; }
<CODE>"E"			{ return EVENTUALLY;}
<CODE>"A"			{ return ALWAYS;}
<CODE>"G"			{ return GLOBALLY;}
<CODE>"F"			{ return FINALLY;}
<CODE>"card"		{ return COUNT; }
<CODE>"this"		{ return CONTEXT; }

<CODE>"active"		{ return ACTIVE; }
<CODE>"assert"		{ return ASSERT; }
<CODE>"atomic"		{ return ATOMIC; }
<CODE>"break"		{ return BREAK; }
<CODE>"c_code"		{ return C_CODE; }
<CODE>"c_decl"		{ return C_DECL; }
<CODE>"c_expr"		{ return C_EXPR; }
<CODE>"c_state"		{ return C_STATE; }
<CODE>"c_track"		{ return C_TRACK; }
<CODE>"D_proctype"	{ return D_PROCTYPE; }
<CODE>"do"			{ yylval->iVal = nbrLines; 
					  return DO; }
<CODE>"else"		{ return ELSE; }
<CODE>"empty"		{ return EMPTY; }
<CODE>"enabled"		{ return ENABLED; }
<CODE>"eval"		{ return EVAL; }
<CODE>"fi"			{ return FI; }
<CODE>"dg"			{ return FI; }
<CODE>"full"		{ return FULL; }
<CODE>"goto"		{ return GOTO; }
<CODE>"hidden"		{ return HIDDEN; }
<CODE>"if"			{ yylval->iVal = nbrLines; 
					  return IF; }
<CODE>"gd"			{ yylval->iVal = nbrLines; 
					  return IF; }
<CODE>"init"		{ return INIT; }
<CODE>"len"			{ return LEN; }
<CODE>"local"		{ return ISLOCAL; }
<CODE>"nempty"		{ return NEMPTY; }
<CODE>"never"		{ return CLAIM; }
<CODE>"nfull"		{ return NFULL; }
<CODE>"notrace"		{ return TRACE; }
<CODE>"np_"			{ return NONPROGRESS; }
<CODE>"od"			{ return OD; }
<CODE>"of"			{ return OF; }
<CODE>"pc_value"	{ return PC_VAL; }
<CODE>"printf"		{ return PRINT; }
<CODE>"printm"		{ return PRINTM; }
<CODE>"priority"	{ return PRIORITY; }
<CODE>"proctype"	{ return PROCTYPE; }
<CODE>"provided"	{ return PROVIDED; }
<CODE>"run"			{ return RUN; }
<CODE>"d_step"		{ return D_STEP; }
<CODE>"timeout"		{ return TIMEOUT; }
<CODE>"trace"		{ return TRACE; }
<CODE>"show"		{ return SHOW; }
<CODE>"typedef"		{ return TYPEDEF; }
<CODE>"unless"		{ return UNLESS; }
<CODE>"xr"			{ return XU; }
<CODE>"xs"			{ return XU; }
<CODE>"when"		{ return WHEN; }
<CODE>"while"		{ return WHILE; }
<CODE>"wait"		{ return WAIT; }
<CODE>"reset"		{ return RESET; }

<CODE>"bit"			{ yylval->iType = symTabNode::T_BIT;
					  return TYPE; }
<CODE>"bool"		{ yylval->iType = symTabNode::T_BOOL;
					  return TYPE; }
<CODE>"byte"		{ yylval->iType = symTabNode::T_BYTE;
					  return TYPE; }
<CODE>"pid"			{ yylval->iType = symTabNode::T_PID;
					  return TYPE; }
<CODE>"short"		{ yylval->iType = symTabNode::T_SHORT;
					  return TYPE; }
<CODE>"int"			{ yylval->iType = symTabNode::T_INT;
					  return TYPE; }
<CODE>"unsigned"	{ fprintf(stderr, "The 'unsigned' type is not supported.\n");
					  exit(1);			
						/*	yylval->iVal = T_UNSGN; 
							return TYPE; */ }
<CODE>"chan"		{ yylval->iType = symTabNode::T_CID;
					  return TYPE; }
<CODE>"mtype"		{ yylval->iType = symTabNode::T_MTYPE;
					  return TYPE; }
<CODE>"clock"		{ yylval->iType = symTabNode::T_CLOCK;
					  return TYPE; }

<CODE>"inline"		{ fprintf(stderr, "Inline declarations are not supported.\n");
					  exit(1); /* return INLINE; */ }

<CODE>"false"		{ yylval->iVal = 0; 
					  return FALSE; }

<CODE>"true"		{ yylval->iVal = 1; 
					  return TRUE; }

<CODE>"skip"		{ return SKIP; }

<CODE>"\""          { BEGIN STRINGBLOCK; 													/* printf("BEGIN STRINGBLOCK AT L %d\n", nbrLines); */
					  strBufferLen = 0; }
<STRINGBLOCK>"\""	{ BEGIN CODE;															/* printf("BEGIN CODE AT L %d\n", nbrLines); */
					  strBuffer[strBufferLen] = '\0';
					  //yylval->sVal = (char*) calloc(strBufferLen + 1, sizeof(char));
					  //strcpy(yylval->sVal, strBuffer);
					  yylval->sVal = strBuffer;
					  
					  return STRING; }
<STRINGBLOCK>"\\\"" { strBuffer[strBufferLen] = '"';
					  strBufferLen++; }
<STRINGBLOCK>"\n"   { strBuffer[strBufferLen] = '\n';
					  strBufferLen++; }
<STRINGBLOCK>.      { strBuffer[strBufferLen] = yytext[0];
					  strBufferLen++; }
 

<CODE>{symbol}	 	{ return yytext[0]; } 

<CODE>{id}       	{ yylval->sVal = (char*) calloc(strlen(yytext) + 1, sizeof(char));
					  strcpy(yylval->sVal, yytext);
					  // The grammar differentiates between UNAME -> user type, PNAME -> proctype, INAME -> inline, NAME -> everything else
					  
					  if(*globalSymTab != nullptr) {
					  	  symTabNode* node = (*globalSymTab)->lookupInSymTab(yylval->sVal);
						  if(node && node->getType() == symTabNode::T_TDEF) 
						  	return UNAME; 
						  else if(node && node->getType() == symTabNode::T_PROC) 
						  	return PNAME; 
					  } else 
					  	return NAME; }
<CODE>{real}		{ yylval->rVal = atof(yytext);
					  return REAL;  }
<CODE>{number}		{ yylval->iVal = atoi(yytext);
					  return CONST; }

<CODE>"\n"       	{ nbrLines++; }
<CODE>{blank}    	{ }

<CODE>"/*"			{ BEGIN COMMENTBLOCK; 													/* printf("BEGIN COMMENTBLOCK AT L %d\n", nbrLines); */ }
<COMMENTBLOCK>"*/"	{ BEGIN CODE;															/* printf("BEGIN CODE AT L %d\n", nbrLines); */ }
<COMMENTBLOCK>"\n"	{ nbrLines++; }
<COMMENTBLOCK>.		{ }

<CODE>"//"			{ BEGIN COMMENTLINE; 													/* printf("BEGIN COMMENTLINE AT L %d\n", nbrLines); */ }
<COMMENTLINE>"\n"	{ nbrLines++; BEGIN CODE; 												/* printf("BEGIN CODE AT L %d\n", nbrLines); */ }
<COMMENTLINE>.		{ }

<CODE>"#"       	{ BEGIN CPPBLOCK; }
<CPPBLOCK>"\n"		{ BEGIN CODE; }
<CPPBLOCK>{number}	{ nbrLines = atoi(yytext); }
<CPPBLOCK>.			{ }

.					{ fprintf(stderr, "Invalid char '%s' at line %d\n", yytext, nbrLines);
					  exit(1); }

%%

void init_lex(){
	BEGIN CODE;
}
