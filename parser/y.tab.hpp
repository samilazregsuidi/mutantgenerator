/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HOME_SLAZREG_WORK_RESEARCH_MUTATION_MUTANTGENERATOR_PARSER_Y_TAB_HPP_INCLUDED
# define YY_YY_HOME_SLAZREG_WORK_RESEARCH_MUTATION_MUTANTGENERATOR_PARSER_Y_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CONST = 258,                   /* CONST  */
    IF = 259,                      /* IF  */
    DO = 260,                      /* DO  */
    TYPE = 261,                    /* TYPE  */
    NAME = 262,                    /* NAME  */
    UNAME = 263,                   /* UNAME  */
    PNAME = 264,                   /* PNAME  */
    INAME = 265,                   /* INAME  */
    STRING = 266,                  /* STRING  */
    REAL = 267,                    /* REAL  */
    TRUE = 268,                    /* TRUE  */
    FALSE = 269,                   /* FALSE  */
    SKIP = 270,                    /* SKIP  */
    ASSERT = 271,                  /* ASSERT  */
    PRINT = 272,                   /* PRINT  */
    PRINTM = 273,                  /* PRINTM  */
    C_CODE = 274,                  /* C_CODE  */
    C_DECL = 275,                  /* C_DECL  */
    C_EXPR = 276,                  /* C_EXPR  */
    C_STATE = 277,                 /* C_STATE  */
    C_TRACK = 278,                 /* C_TRACK  */
    RUN = 279,                     /* RUN  */
    LEN = 280,                     /* LEN  */
    ENABLED = 281,                 /* ENABLED  */
    EVAL = 282,                    /* EVAL  */
    PC_VAL = 283,                  /* PC_VAL  */
    TYPEDEF = 284,                 /* TYPEDEF  */
    MTYPE = 285,                   /* MTYPE  */
    INLINE = 286,                  /* INLINE  */
    LABEL = 287,                   /* LABEL  */
    OF = 288,                      /* OF  */
    GOTO = 289,                    /* GOTO  */
    BREAK = 290,                   /* BREAK  */
    ELSE = 291,                    /* ELSE  */
    SEMI = 292,                    /* SEMI  */
    FI = 293,                      /* FI  */
    OD = 294,                      /* OD  */
    SEP = 295,                     /* SEP  */
    ATOMIC = 296,                  /* ATOMIC  */
    NON_ATOMIC = 297,              /* NON_ATOMIC  */
    D_STEP = 298,                  /* D_STEP  */
    UNLESS = 299,                  /* UNLESS  */
    TIMEOUT = 300,                 /* TIMEOUT  */
    NONPROGRESS = 301,             /* NONPROGRESS  */
    ACTIVE = 302,                  /* ACTIVE  */
    PROCTYPE = 303,                /* PROCTYPE  */
    D_PROCTYPE = 304,              /* D_PROCTYPE  */
    HIDDEN = 305,                  /* HIDDEN  */
    SHOW = 306,                    /* SHOW  */
    ISLOCAL = 307,                 /* ISLOCAL  */
    PRIORITY = 308,                /* PRIORITY  */
    PROVIDED = 309,                /* PROVIDED  */
    FULL = 310,                    /* FULL  */
    EMPTY = 311,                   /* EMPTY  */
    NFULL = 312,                   /* NFULL  */
    NEMPTY = 313,                  /* NEMPTY  */
    XU = 314,                      /* XU  */
    CLAIM = 315,                   /* CLAIM  */
    TRACE = 316,                   /* TRACE  */
    INIT = 317,                    /* INIT  */
    WHILE = 318,                   /* WHILE  */
    WHEN = 319,                    /* WHEN  */
    WAIT = 320,                    /* WAIT  */
    RESET = 321,                   /* RESET  */
    SPEC = 322,                    /* SPEC  */
    EVENTUALLY = 323,              /* EVENTUALLY  */
    ALWAYS = 324,                  /* ALWAYS  */
    GLOBALLY = 325,                /* GLOBALLY  */
    FINALLY = 326,                 /* FINALLY  */
    UNTIL = 327,                   /* UNTIL  */
    LTL = 328,                     /* LTL  */
    ASGN = 329,                    /* ASGN  */
    SND = 330,                     /* SND  */
    O_SND = 331,                   /* O_SND  */
    RCV = 332,                     /* RCV  */
    R_RCV = 333,                   /* R_RCV  */
    OR = 334,                      /* OR  */
    AND = 335,                     /* AND  */
    EQ = 336,                      /* EQ  */
    NE = 337,                      /* NE  */
    GT = 338,                      /* GT  */
    LT = 339,                      /* LT  */
    GE = 340,                      /* GE  */
    LE = 341,                      /* LE  */
    LSHIFT = 342,                  /* LSHIFT  */
    RSHIFT = 343,                  /* RSHIFT  */
    INCR = 344,                    /* INCR  */
    DECR = 345,                    /* DECR  */
    UMIN = 346,                    /* UMIN  */
    NEG = 347,                     /* NEG  */
    COUNT = 348,                   /* COUNT  */
    CONTEXT = 349,                 /* CONTEXT  */
    DOT = 350,                     /* DOT  */
    IMPLIES = 351                  /* IMPLIES  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define CONST 258
#define IF 259
#define DO 260
#define TYPE 261
#define NAME 262
#define UNAME 263
#define PNAME 264
#define INAME 265
#define STRING 266
#define REAL 267
#define TRUE 268
#define FALSE 269
#define SKIP 270
#define ASSERT 271
#define PRINT 272
#define PRINTM 273
#define C_CODE 274
#define C_DECL 275
#define C_EXPR 276
#define C_STATE 277
#define C_TRACK 278
#define RUN 279
#define LEN 280
#define ENABLED 281
#define EVAL 282
#define PC_VAL 283
#define TYPEDEF 284
#define MTYPE 285
#define INLINE 286
#define LABEL 287
#define OF 288
#define GOTO 289
#define BREAK 290
#define ELSE 291
#define SEMI 292
#define FI 293
#define OD 294
#define SEP 295
#define ATOMIC 296
#define NON_ATOMIC 297
#define D_STEP 298
#define UNLESS 299
#define TIMEOUT 300
#define NONPROGRESS 301
#define ACTIVE 302
#define PROCTYPE 303
#define D_PROCTYPE 304
#define HIDDEN 305
#define SHOW 306
#define ISLOCAL 307
#define PRIORITY 308
#define PROVIDED 309
#define FULL 310
#define EMPTY 311
#define NFULL 312
#define NEMPTY 313
#define XU 314
#define CLAIM 315
#define TRACE 316
#define INIT 317
#define WHILE 318
#define WHEN 319
#define WAIT 320
#define RESET 321
#define SPEC 322
#define EVENTUALLY 323
#define ALWAYS 324
#define GLOBALLY 325
#define FINALLY 326
#define UNTIL 327
#define LTL 328
#define ASGN 329
#define SND 330
#define O_SND 331
#define RCV 332
#define R_RCV 333
#define OR 334
#define AND 335
#define EQ 336
#define NE 337
#define GT 338
#define LT 339
#define GE 340
#define LE 341
#define LSHIFT 342
#define RSHIFT 343
#define INCR 344
#define DECR 345
#define UMIN 346
#define NEG 347
#define COUNT 348
#define CONTEXT 349
#define DOT 350
#define IMPLIES 351

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 63 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
 
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

#line 283 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int yyparse (symTable** globalSymTab, stmnt** program);


#endif /* !YY_YY_HOME_SLAZREG_WORK_RESEARCH_MUTATION_MUTANTGENERATOR_PARSER_Y_TAB_HPP_INCLUDED  */
