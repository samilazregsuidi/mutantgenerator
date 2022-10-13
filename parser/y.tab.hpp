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
    VNAME = 266,                   /* VNAME  */
    BASE = 267,                    /* BASE  */
    STRING = 268,                  /* STRING  */
    REAL = 269,                    /* REAL  */
    TRUE = 270,                    /* TRUE  */
    FALSE = 271,                   /* FALSE  */
    SKIP = 272,                    /* SKIP  */
    ASSERT = 273,                  /* ASSERT  */
    PRINT = 274,                   /* PRINT  */
    PRINTM = 275,                  /* PRINTM  */
    C_CODE = 276,                  /* C_CODE  */
    C_DECL = 277,                  /* C_DECL  */
    C_EXPR = 278,                  /* C_EXPR  */
    C_STATE = 279,                 /* C_STATE  */
    C_TRACK = 280,                 /* C_TRACK  */
    RUN = 281,                     /* RUN  */
    LEN = 282,                     /* LEN  */
    ENABLED = 283,                 /* ENABLED  */
    EVAL = 284,                    /* EVAL  */
    PC_VAL = 285,                  /* PC_VAL  */
    TYPEDEF = 286,                 /* TYPEDEF  */
    MTYPE = 287,                   /* MTYPE  */
    INLINE = 288,                  /* INLINE  */
    LABEL = 289,                   /* LABEL  */
    OF = 290,                      /* OF  */
    GOTO = 291,                    /* GOTO  */
    BREAK = 292,                   /* BREAK  */
    ELSE = 293,                    /* ELSE  */
    SEMI = 294,                    /* SEMI  */
    FI = 295,                      /* FI  */
    OD = 296,                      /* OD  */
    SEP = 297,                     /* SEP  */
    ATOMIC = 298,                  /* ATOMIC  */
    NON_ATOMIC = 299,              /* NON_ATOMIC  */
    D_STEP = 300,                  /* D_STEP  */
    UNLESS = 301,                  /* UNLESS  */
    TIMEOUT = 302,                 /* TIMEOUT  */
    NONPROGRESS = 303,             /* NONPROGRESS  */
    ACTIVE = 304,                  /* ACTIVE  */
    PROCTYPE = 305,                /* PROCTYPE  */
    D_PROCTYPE = 306,              /* D_PROCTYPE  */
    HIDDEN = 307,                  /* HIDDEN  */
    SHOW = 308,                    /* SHOW  */
    ISLOCAL = 309,                 /* ISLOCAL  */
    PRIORITY = 310,                /* PRIORITY  */
    PROVIDED = 311,                /* PROVIDED  */
    FULL = 312,                    /* FULL  */
    EMPTY = 313,                   /* EMPTY  */
    NFULL = 314,                   /* NFULL  */
    NEMPTY = 315,                  /* NEMPTY  */
    XU = 316,                      /* XU  */
    CLAIM = 317,                   /* CLAIM  */
    TRACE = 318,                   /* TRACE  */
    INIT = 319,                    /* INIT  */
    WHILE = 320,                   /* WHILE  */
    WHEN = 321,                    /* WHEN  */
    WAIT = 322,                    /* WAIT  */
    RESET = 323,                   /* RESET  */
    SPEC = 324,                    /* SPEC  */
    EVENTUALLY = 325,              /* EVENTUALLY  */
    ALWAYS = 326,                  /* ALWAYS  */
    GLOBALLY = 327,                /* GLOBALLY  */
    FINALLY = 328,                 /* FINALLY  */
    UNTIL = 329,                   /* UNTIL  */
    NEXT = 330,                    /* NEXT  */
    LTL = 331,                     /* LTL  */
    FMULTILTL = 332,               /* FMULTILTL  */
    ASGN = 333,                    /* ASGN  */
    SND = 334,                     /* SND  */
    O_SND = 335,                   /* O_SND  */
    RCV = 336,                     /* RCV  */
    R_RCV = 337,                   /* R_RCV  */
    OR = 338,                      /* OR  */
    AND = 339,                     /* AND  */
    EQ = 340,                      /* EQ  */
    NE = 341,                      /* NE  */
    GT = 342,                      /* GT  */
    LT = 343,                      /* LT  */
    GE = 344,                      /* GE  */
    LE = 345,                      /* LE  */
    LSHIFT = 346,                  /* LSHIFT  */
    RSHIFT = 347,                  /* RSHIFT  */
    INCR = 348,                    /* INCR  */
    DECR = 349,                    /* DECR  */
    UMIN = 350,                    /* UMIN  */
    NEG = 351,                     /* NEG  */
    COUNT = 352,                   /* COUNT  */
    CONTEXT = 353,                 /* CONTEXT  */
    DOT = 354,                     /* DOT  */
    IMPLIES = 355                  /* IMPLIES  */
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
#define VNAME 266
#define BASE 267
#define STRING 268
#define REAL 269
#define TRUE 270
#define FALSE 271
#define SKIP 272
#define ASSERT 273
#define PRINT 274
#define PRINTM 275
#define C_CODE 276
#define C_DECL 277
#define C_EXPR 278
#define C_STATE 279
#define C_TRACK 280
#define RUN 281
#define LEN 282
#define ENABLED 283
#define EVAL 284
#define PC_VAL 285
#define TYPEDEF 286
#define MTYPE 287
#define INLINE 288
#define LABEL 289
#define OF 290
#define GOTO 291
#define BREAK 292
#define ELSE 293
#define SEMI 294
#define FI 295
#define OD 296
#define SEP 297
#define ATOMIC 298
#define NON_ATOMIC 299
#define D_STEP 300
#define UNLESS 301
#define TIMEOUT 302
#define NONPROGRESS 303
#define ACTIVE 304
#define PROCTYPE 305
#define D_PROCTYPE 306
#define HIDDEN 307
#define SHOW 308
#define ISLOCAL 309
#define PRIORITY 310
#define PROVIDED 311
#define FULL 312
#define EMPTY 313
#define NFULL 314
#define NEMPTY 315
#define XU 316
#define CLAIM 317
#define TRACE 318
#define INIT 319
#define WHILE 320
#define WHEN 321
#define WAIT 322
#define RESET 323
#define SPEC 324
#define EVENTUALLY 325
#define ALWAYS 326
#define GLOBALLY 327
#define FINALLY 328
#define UNTIL 329
#define NEXT 330
#define LTL 331
#define FMULTILTL 332
#define ASGN 333
#define SND 334
#define O_SND 335
#define RCV 336
#define R_RCV 337
#define OR 338
#define AND 339
#define EQ 340
#define NE 341
#define GT 342
#define LT 343
#define GE 344
#define LE 345
#define LSHIFT 346
#define RSHIFT 347
#define INCR 348
#define DECR 349
#define UMIN 350
#define NEG 351
#define COUNT 352
#define CONTEXT 353
#define DOT 354
#define IMPLIES 355

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 64 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
 
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
	class variantQuantifier*pVarQuantVal;
	
	class symbol*			pSymTabVal;
	class varSymNode*		pVarSymVal;
	class tdefSymNode*		pTdefSymVal;
	class mtypedefSymNode*	pTypedefSymVal;
	
	enum symbol::Type   iType;

#line 292 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int yyparse (symTable** globalSymTab, stmnt** program);


#endif /* !YY_YY_HOME_SLAZREG_WORK_RESEARCH_MUTATION_MUTANTGENERATOR_PARSER_Y_TAB_HPP_INCLUDED  */
