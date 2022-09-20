%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbols.hpp"
#include "ast.hpp"

#include "y.tab.hpp"

#define YY_DECL int yylex(YYSTYPE * yylval_param, symTable** globalSymTab)

int nbrLines = 0;
char strBuffer[1024];
int strBufferLen = 0;

#define DBOUG 0

#ifdef DBOUG
	#define DBUG(TOKEN) std::cout<<"TOKEN : " << #TOKEN << "\n"
	#define DBUG_CHAR(CHAR) std::cout<<"TOKEN : " << CHAR << "\n"
#elif
	#define DBUG(TOKEN) ;
	#define DBUG_CHAR(CHAR) ;
#endif

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


<CODE>"::"       	{ DBUG(SEP);return SEP; }
<CODE>"->"       	{ DBUG(SEMI);return SEMI; }
<CODE>";"        	{ DBUG(SEMI);return SEMI; }
<CODE>"--"       	{ DBUG(DECR);return DECR; }
<CODE>"++"       	{ DBUG(INCR);return INCR; }
<CODE>"<<"       	{ DBUG(LSHIFT);return LSHIFT; }
<CODE>"<="       	{ DBUG(LE);return LE; }
<CODE>"<"        	{ DBUG(LT);return LT; }
<CODE>">>"       	{ DBUG(RSHIFT);return RSHIFT; }
<CODE>">="       	{ DBUG(GE);return GE; }
<CODE>"=>"			{ DBUG(IMPLIES);return IMPLIES; }
<CODE>">"        	{ DBUG(GT);return GT; }
<CODE>"=="       	{ DBUG(EQ);return EQ; }
<CODE>"="        	{ DBUG(ASGN);return ASGN; }
<CODE>"!="       	{ DBUG(NE);return NE; }
<CODE>"!!"       	{ DBUG(O_SND);return O_SND; /* Sorted send, p.48 */ }
<CODE>"!"        	{ DBUG(SND);return SND; }
<CODE>"??"       	{ DBUG(R_RCV);return R_RCV; /* Random receive, p.48 */ }
<CODE>"?"        	{ DBUG(RCV);return RCV; }
<CODE>"&&"       	{ DBUG(AND);return AND; }
<CODE>"||"       	{ DBUG(OR);return OR; }
<CODE>"spec"		{ DBUG(SPEC);return SPEC; }
<CODE>"ltl"			{ DBUG(LTL); return LTL; }
<CODE>"E"			{ DBUG(EVENTUALLY);return EVENTUALLY; }
<CODE>"<>"			{ DBUG(EVENTUALLY);return EVENTUALLY; }
<CODE>"A"			{ DBUG(ALWAYS);return ALWAYS; }
<CODE>"[]"			{ DBUG(ALWAYS);return ALWAYS; }
<CODE>"U"			{ DBUG(UNTIL);return UNTIL; }
<CODE>"card"		{ DBUG(COUNT);return COUNT; }
<CODE>"this"		{ DBUG(CONTEXT);return CONTEXT; }

<CODE>"active"		{ DBUG(ACTIVE);return ACTIVE; }
<CODE>"assert"		{ DBUG(ASSERT);return ASSERT; }
<CODE>"atomic"		{ DBUG(ATOMIC);return ATOMIC; }
<CODE>"break"		{ DBUG(BREAK);return BREAK; }
<CODE>"c_code"		{ DBUG(C_CODE);return C_CODE; }
<CODE>"c_decl"		{ DBUG(C_DECL);return C_DECL; }
<CODE>"c_expr"		{ DBUG(C_EXPR);return C_EXPR; }
<CODE>"c_state"		{ DBUG(C_STATE);return C_STATE; }
<CODE>"c_track"		{ DBUG(C_TRACK);return C_TRACK; }
<CODE>"D_proctype"	{ DBUG(D_PROTOTYPE);return D_PROCTYPE; }
<CODE>"do"			{ DBUG(DO);yylval->iVal = nbrLines; 
					  return DO; }
<CODE>"else"		{ DBUG(ELSE);return ELSE; }
<CODE>"empty"		{ DBUG(EMPTY);return EMPTY; }
<CODE>"enabled"		{ DBUG(ENABLED);return ENABLED; }
<CODE>"eval"		{ DBUG(EVAL);return EVAL; }
<CODE>"fi"			{ DBUG(FI);return FI; }
<CODE>"dg"			{ DBUG(FI);return FI; }
<CODE>"full"		{ DBUG(FULL);return FULL; }
<CODE>"goto"		{ DBUG(GOTO);return GOTO; }
<CODE>"hidden"		{ DBUG(HIDDEN);return HIDDEN; }
<CODE>"if"			{ yylval->iVal = nbrLines; DBUG(IF);return IF; }
<CODE>"gd"			{ yylval->iVal = nbrLines; DBUG(IF); return IF; }

<CODE>"init"		{ DBUG(HIDDEN);return INIT; }
<CODE>"len"			{ DBUG(LEN); return LEN; }
<CODE>"local"		{ DBUG(ISLOCAL); return ISLOCAL; }
<CODE>"nempty"		{ DBUG(NEMPTY); return NEMPTY; }
<CODE>"never"		{ DBUG(CLAIM); return CLAIM; }
<CODE>"nfull"		{ DBUG(NFULL); return NFULL; }
<CODE>"notrace"		{ DBUG(TRACE); return TRACE; }
<CODE>"np_"			{ DBUG(NONPROGRESS); return NONPROGRESS; }
<CODE>"od"			{ DBUG(OD); return OD; }
<CODE>"of"			{ DBUG(OF); return OF; }
<CODE>"pc_value"	{ DBUG(PC_VAL); return PC_VAL; }
<CODE>"printf"		{ DBUG(PRINT); return PRINT; }
<CODE>"printm"		{ DBUG(PRINTM); return PRINTM; }
<CODE>"priority"	{ DBUG(PRIORITY); return PRIORITY; }
<CODE>"proctype"	{ DBUG(PROCTYPE); return PROCTYPE; }
<CODE>"provided"	{ DBUG(PROVIDED); return PROVIDED; }
<CODE>"run"			{ DBUG(RUN); return RUN; }
<CODE>"d_step"		{ DBUG(D_STEP); return D_STEP; }
<CODE>"timeout"		{ DBUG(TIMEOUT); return TIMEOUT; }
<CODE>"trace"		{ DBUG(TRACE); return TRACE; }
<CODE>"show"		{ DBUG(SHOW); return SHOW; }
<CODE>"typedef"		{ DBUG(TYPEDEF); return TYPEDEF; }
<CODE>"unless"		{ DBUG(UNLESS); return UNLESS; }
<CODE>"xr"			{ DBUG(XU); return XU; }
<CODE>"xs"			{ DBUG(XU); return XU; }
<CODE>"when"		{ DBUG(WHEN); return WHEN; }
<CODE>"while"		{ DBUG(WHILE); return WHILE; }
<CODE>"wait"		{ DBUG(WAIT); return WAIT; }
<CODE>"reset"		{ DBUG(RESET); return RESET; }

<CODE>"bit"			{ yylval->iType = symbol::T_BIT;
					  DBUG(TYPE); return TYPE; }
<CODE>"bool"		{ DBUG(TYPE); yylval->iType = symbol::T_BOOL;
					  return TYPE; }
<CODE>"byte"		{ DBUG(TYPE); yylval->iType = symbol::T_BYTE;
					  return TYPE; }
<CODE>"pid"			{ DBUG(TYPE); yylval->iType = symbol::T_PID;
					  return TYPE; }
<CODE>"short"		{ DBUG(TYPE); yylval->iType = symbol::T_SHORT;
					  return TYPE; }
<CODE>"int"			{ DBUG(TYPE); yylval->iType = symbol::T_INT;
					  return TYPE; }
<CODE>"unsigned"	{ fprintf(stderr, "The 'unsigned' type is not supported.\n");
					  exit(1);			
						/*	yylval->iVal = T_UNSGN; 
							return TYPE; */ }
<CODE>"chan"		{ DBUG(TYPE); yylval->iType = symbol::T_CID;
					  return TYPE; }
<CODE>"mtype"		{ DBUG(TYPE); yylval->iType = symbol::T_MTYPE;
					  return TYPE; }
<CODE>"clock"		{ DBUG(TYPE); yylval->iType = symbol::T_CLOCK;
					  return TYPE; }

<CODE>"inline"		{ return INLINE; }

<CODE>"false"		{ DBUG(FALSE);  yylval->iVal = 0; 
					  return FALSE; }

<CODE>"true"		{ DBUG(TRUE); std::cout << "TOKEN: TRUE\n"; yylval->iVal = 1; 
					  return TRUE; }

<CODE>"skip"		{ DBUG(SKIP); return SKIP; }

<CODE>"\""          { BEGIN STRINGBLOCK; 													/* printf("BEGIN STRINGBLOCK AT L %d\n", nbrLines); */
					  strBufferLen = 0; }
<STRINGBLOCK>"\""	{ BEGIN CODE;															/* printf("BEGIN CODE AT L %d\n", nbrLines); */
					  strBuffer[strBufferLen] = '\0';
					  yylval->sVal = (char*) calloc(strBufferLen + 1, sizeof(char));
					  strcpy(yylval->sVal, strBuffer);
					  yylval->sVal = strBuffer;
					  
					  return STRING; }
<STRINGBLOCK>"\\\"" { strBuffer[strBufferLen] = '"';
					  strBufferLen++; }
<STRINGBLOCK>"\n"   { strBuffer[strBufferLen] = '\n';
					  strBufferLen++; }
<STRINGBLOCK>.      { strBuffer[strBufferLen] = yytext[0];
					  strBufferLen++; }
 

<CODE>{symbol}	 	{ DBUG_CHAR(yytext[0]); return yytext[0]; } 

<CODE>{id}       	{
					  yylval->sVal = (char*) calloc(strlen(yytext) + 1, sizeof(char));
					  strcpy(yylval->sVal, yytext);
 
					  // The grammar differentiates between UNAME -> user type, PNAME -> proctype, INAME -> inline, NAME -> everything else
					  symbol* node = nullptr;
					  if(*globalSymTab != nullptr && (node = (*globalSymTab)->lookup(yylval->sVal))) {
					  	  switch(node->getType()) {
							  case symbol::T_TDEF:
						   		 DBUG(UNAME);
						  	     return UNAME; 

						      case symbol::T_PROC:
						  	     DBUG(PNAME);
						  	     return PNAME;
                              
							  case symbol::T_INLINE:
							     DBUG(INAME);
								 return INAME;
							  default:
							  	 break;
						  }
					  }
					  
					  DBUG(NAME);
					  return NAME;
					}
					
<CODE>{real}		{ yylval->rVal = atof(yytext);
					  DBUG(REAL); return REAL;  }
<CODE>{number}		{ DBUG(CONST); yylval->iVal = atoi(yytext);
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
