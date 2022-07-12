/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"


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
mtypedefSymNode* mtypeDef = nullptr;

symTable* currentSymTab = nullptr;
symTable* savedSymTab = nullptr;

std::list<varSymNode*> declSyms;
std::list<varSymNode*> typeLst;
std::list<std::string> params;

int mtypeId = 0;
bool inInline = false;


#line 124 "y.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_HPP_INCLUDED
# define YY_YY_Y_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CONST = 258,
    IF = 259,
    DO = 260,
    TYPE = 261,
    NAME = 262,
    UNAME = 263,
    PNAME = 264,
    INAME = 265,
    STRING = 266,
    REAL = 267,
    TRUE = 268,
    FALSE = 269,
    SKIP = 270,
    ASSERT = 271,
    PRINT = 272,
    PRINTM = 273,
    C_CODE = 274,
    C_DECL = 275,
    C_EXPR = 276,
    C_STATE = 277,
    C_TRACK = 278,
    RUN = 279,
    LEN = 280,
    ENABLED = 281,
    EVAL = 282,
    PC_VAL = 283,
    TYPEDEF = 284,
    MTYPE = 285,
    INLINE = 286,
    LABEL = 287,
    OF = 288,
    GOTO = 289,
    BREAK = 290,
    ELSE = 291,
    SEMI = 292,
    FI = 293,
    OD = 294,
    SEP = 295,
    ATOMIC = 296,
    NON_ATOMIC = 297,
    D_STEP = 298,
    UNLESS = 299,
    TIMEOUT = 300,
    NONPROGRESS = 301,
    ACTIVE = 302,
    PROCTYPE = 303,
    D_PROCTYPE = 304,
    HIDDEN = 305,
    SHOW = 306,
    ISLOCAL = 307,
    PRIORITY = 308,
    PROVIDED = 309,
    FULL = 310,
    EMPTY = 311,
    NFULL = 312,
    NEMPTY = 313,
    XU = 314,
    CLAIM = 315,
    TRACE = 316,
    INIT = 317,
    WHILE = 318,
    WHEN = 319,
    WAIT = 320,
    RESET = 321,
    SPEC = 322,
    EVENTUALLY = 323,
    ALWAYS = 324,
    GLOBALLY = 325,
    FINALLY = 326,
    ASGN = 327,
    SND = 328,
    O_SND = 329,
    RCV = 330,
    R_RCV = 331,
    OR = 332,
    AND = 333,
    EQ = 334,
    NE = 335,
    GT = 336,
    LT = 337,
    GE = 338,
    LE = 339,
    LSHIFT = 340,
    RSHIFT = 341,
    INCR = 342,
    DECR = 343,
    UMIN = 344,
    NEG = 345,
    COUNT = 346,
    CONTEXT = 347,
    DOT = 348,
    IMPLIES = 349
  };
#endif
/* Tokens.  */
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
#define ASGN 327
#define SND 328
#define O_SND 329
#define RCV 330
#define R_RCV 331
#define OR 332
#define AND 333
#define EQ 334
#define NE 335
#define GT 336
#define LT 337
#define GE 338
#define LE 339
#define LSHIFT 340
#define RSHIFT 341
#define INCR 342
#define DECR 343
#define UMIN 344
#define NEG 345
#define COUNT 346
#define CONTEXT 347
#define DOT 348
#define IMPLIES 349

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 62 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
 
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

#line 388 "y.tab.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (symTable** globalSymTab, stmnt** program);

#endif /* !YY_YY_Y_TAB_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1531

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  114
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  68
/* YYNRULES -- Number of rules.  */
#define YYNRULES  205
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  397

#define YYUNDEFTOK  2
#define YYMAXUTOK   349


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    94,    81,     2,
     104,   105,    92,    90,   111,    91,   112,    93,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   110,     2,
       2,     2,     2,     2,   113,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   106,     2,   107,    80,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   108,    79,   109,    97,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    82,    83,    84,    85,    86,    87,
      88,    89,    95,    96,    98,    99,   100,   101,   102,   103
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   145,   145,   145,   150,   153,   154,   157,   158,   159,
     160,   173,   174,   175,   176,   177,   183,   185,   181,   200,
     201,   204,   205,   206,   207,   221,   220,   236,   239,   251,
     251,   270,   271,   273,   270,   288,   289,   292,   293,   294,
     295,   298,   299,   302,   305,   305,   315,   316,   317,   320,
     325,   326,   327,   328,   336,   337,   338,   339,   342,   343,
     349,   349,   350,   350,   353,   354,   358,   359,   366,   367,
     370,   375,   380,   385,   386,   387,   391,   394,   395,   399,
     414,   431,   432,   433,   436,   439,   440,   443,   444,   447,
     448,   452,   453,   456,   457,   458,   459,   460,   461,   462,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   483,   495,   496,
     499,   512,   513,   516,   517,   520,   521,   524,   525,   526,
     527,   528,   529,   530,   531,   532,   533,   534,   535,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   545,   553,
     554,   555,   560,   561,   562,   563,   564,   565,   566,   567,
     568,   569,   570,   571,   572,   573,   574,   575,   578,   579,
     582,   583,   586,   587,   592,   593,   594,   595,   596,   597,
     598,   599,   600,   603,   604,   605,   606,   610,   611,   615,
     616,   620,   621,   624,   625,   628,   629,   630,   631,   635,
     636,   637,   638,   641,   642,   643
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CONST", "IF", "DO", "TYPE", "NAME",
  "UNAME", "PNAME", "INAME", "STRING", "REAL", "TRUE", "FALSE", "SKIP",
  "ASSERT", "PRINT", "PRINTM", "C_CODE", "C_DECL", "C_EXPR", "C_STATE",
  "C_TRACK", "RUN", "LEN", "ENABLED", "EVAL", "PC_VAL", "TYPEDEF", "MTYPE",
  "INLINE", "LABEL", "OF", "GOTO", "BREAK", "ELSE", "SEMI", "FI", "OD",
  "SEP", "ATOMIC", "NON_ATOMIC", "D_STEP", "UNLESS", "TIMEOUT",
  "NONPROGRESS", "ACTIVE", "PROCTYPE", "D_PROCTYPE", "HIDDEN", "SHOW",
  "ISLOCAL", "PRIORITY", "PROVIDED", "FULL", "EMPTY", "NFULL", "NEMPTY",
  "XU", "CLAIM", "TRACE", "INIT", "WHILE", "WHEN", "WAIT", "RESET", "SPEC",
  "EVENTUALLY", "ALWAYS", "GLOBALLY", "FINALLY", "ASGN", "SND", "O_SND",
  "RCV", "R_RCV", "OR", "AND", "'|'", "'^'", "'&'", "EQ", "NE", "GT", "LT",
  "GE", "LE", "LSHIFT", "RSHIFT", "'+'", "'-'", "'*'", "'/'", "'%'",
  "INCR", "DECR", "'~'", "UMIN", "NEG", "COUNT", "CONTEXT", "DOT",
  "IMPLIES", "'('", "')'", "'['", "']'", "'{'", "'}'", "':'", "','", "'.'",
  "'@'", "$accept", "start_parsing", "$@1", "program", "units", "unit",
  "proc", "$@2", "$@3", "proctype", "inst", "init", "$@4", "events",
  "utypedef", "mtypedef", "$@5", "ns", "$@6", "$@7", "$@8", "c_fcts",
  "cstate", "ccode", "cexpr", "body", "$@9", "sequence", "step", "vis",
  "asgn", "one_decl", "$@10", "$@11", "decl_lst", "decl", "var_list",
  "ivar", "param_list", "ch_init", "basetype", "typ_list", "vardcl",
  "varref", "pfld", "cmpnd", "sfld", "stmnt", "Special", "Stmnt",
  "options", "option", "OS", "MS", "aname", "expr", "Opt_priority",
  "full_expr", "Opt_enabler", "Expr", "Probe", "args", "prargs", "margs",
  "arg", "rarg", "rargs", "nlst", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   124,
      94,    38,   334,   335,   336,   337,   338,   339,   340,   341,
      43,    45,    42,    47,    37,   342,   343,   126,   344,   345,
     346,   347,   348,   349,    40,    41,    91,    93,   123,   125,
      58,    44,    46,    64
};
# endif

#define YYPACT_NINF (-336)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-123)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -336,    33,  1122,  -336,  -336,  -336,    43,    82,     9,  -336,
    -336,   -62,  -336,  -336,  -336,    -6,  -336,  -336,   251,  -336,
    -336,    36,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,
      66,  -336,   119,   121,    28,    70,    39,  -336,  -336,    -3,
    -336,  -336,  -336,   133,    19,  -336,   137,   140,    77,  -336,
      63,    64,   735,   165,    -6,  -336,  -336,  -336,   168,   168,
    -336,  -336,   107,   145,    74,    80,  -336,  -336,  -336,   147,
     147,   -39,   -65,    85,  -336,  -336,  -336,   947,    86,    89,
    -336,    40,    90,    91,    94,   181,  -336,  -336,    93,    95,
    -336,  -336,    98,   101,   102,   104,  1004,  1004,  1004,   105,
      87,   947,   735,  -336,  -336,   322,  -336,  -336,   171,    99,
    -336,   172,  -336,  -336,  1419,  -336,    79,  -336,  -336,  -336,
     116,   113,   -12,  -336,   111,   177,  -336,  -336,    77,  -336,
     243,   735,   214,   147,   215,  1004,   531,  1004,   246,   248,
    1004,   150,    84,  -336,   247,     8,  -336,  -336,   157,    10,
    1004,  1004,  -336,   735,   735,    10,    10,    10,    10,  1004,
    -336,  -336,  -336,  1004,   246,   975,   -48,   322,   -19,  -336,
     153,   633,   947,  1004,  1004,    61,    73,  -336,  -336,    10,
    -336,   837,   947,   947,  1004,  1004,  1004,  1004,  1004,  1004,
    1004,  1004,  1004,  1004,  1004,  1004,  1004,  1004,  1004,  1004,
     947,   947,   -13,   256,   261,   262,   168,   894,  -336,   158,
     163,   429,  -336,  -336,  -336,  1212,    -9,  -336,  -336,  -336,
    1243,  -336,  -336,  1143,   170,  -336,   173,   175,   166,   180,
     184,  1004,   187,  1274,  1303,   322,   322,   188,   189,   190,
     191,  1033,  1004,  1004,  1332,    99,  1004,  -336,  -336,   167,
    -336,  -336,  -336,  -336,  1108,  -336,  -336,  -336,  -336,   174,
      62,   283,    62,    62,  -336,   -68,  -336,    62,    62,  -336,
    -336,  -336,   425,   221,   628,  -336,   729,   300,   406,   230,
     230,   314,   314,   314,   314,   -31,   -31,    51,    51,  -336,
    -336,  -336,   425,   221,   628,  -336,  -336,   195,  -336,     3,
     197,  -336,  -336,   302,  -336,  1437,   243,  -336,  -336,  -336,
     837,   -85,  1004,  -336,  1004,   201,  -336,  -336,   202,  -336,
    -336,  -336,   199,   200,  -336,  -336,  -336,  -336,   527,   628,
    -336,  -336,  1178,  -336,  1004,  1004,   227,  -336,   223,   226,
      62,    62,   250,   237,  -336,  -336,  -336,  -336,  -336,   238,
    -336,    -6,   246,   342,  -336,  -336,  -336,    -3,  -336,  -336,
    1004,   249,  1361,  -336,  -336,  -336,   255,  -336,  -336,  -336,
      -3,   318,  -336,  -336,  -336,  -336,  1390,  -336,  -336,  -336,
     298,   253,  -336,   258,    -6,   114,   947,  -336,  -336,  -336,
     259,   257,   264,   114,  -336,  -336,  -336
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,    21,     1,    41,    42,     0,     0,     0,    31,
      15,    22,    55,    56,    57,     0,    25,     3,    21,     5,
       7,     0,     8,     9,    11,    12,    14,    13,    36,    35,
       0,    10,     0,     0,     0,     0,     0,    44,    27,   168,
       6,    19,    20,     0,    58,    62,    37,    38,    54,    32,
       0,     0,    54,     0,     0,    16,    59,    29,     0,     0,
      39,    40,     0,    64,     0,     0,    23,    24,   158,     0,
       0,    85,     0,     0,   159,   160,   182,     0,     0,     0,
      43,     0,     0,     0,     0,     0,    97,   113,     0,     0,
     161,   162,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    54,   107,   157,    54,    46,    49,   156,    89,
      84,    52,    91,    92,   170,   112,   171,   174,   169,    26,
       0,     0,    81,    61,    68,    70,    63,    60,    54,    28,
      73,    54,     0,   118,     0,     0,    54,     0,     0,     0,
     187,    85,   156,   106,     0,     0,   125,   126,     0,     0,
       0,     0,    98,    54,    54,     0,     0,     0,     0,     0,
     149,   148,   147,     0,     0,     0,     0,    54,   123,    48,
       0,    54,     0,     0,     0,     0,     0,   101,   102,     0,
      87,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    54,     0,     0,     0,     0,     0,    65,    74,
       0,   121,    95,   119,    96,     0,    85,    51,    50,    99,
       0,   167,   166,   193,     0,   188,     0,     0,   189,     0,
       0,   187,     0,     0,     0,    54,    54,     0,     0,     0,
       0,     0,     0,     0,     0,    89,     0,   127,   175,     0,
      45,   124,    47,   100,   193,    94,   191,   111,   197,     0,
       0,     0,     0,     0,   195,   199,    93,     0,     0,   108,
      90,    53,   143,   181,   142,   180,   135,   134,   133,   140,
     141,   136,   137,   138,   139,   144,   145,   128,   129,   130,
     131,   132,   179,   178,   177,   176,    67,     0,   203,     0,
       0,    82,    69,     0,    72,    71,    73,    33,   120,    86,
       0,     0,     0,   117,     0,     0,   105,   104,     0,   152,
     153,   163,     0,     0,   183,   185,   184,   186,   143,   142,
     146,    88,     0,   116,     0,     0,     0,   198,     0,     0,
       0,     0,     0,     0,    17,   204,    30,   205,    83,     0,
      75,     0,     0,     0,   194,   190,   103,   168,   114,   115,
       0,     0,     0,   109,   202,   154,     0,   200,   110,   155,
     168,     0,    34,   165,   164,   151,     0,   192,   196,   201,
     172,     0,   150,     0,     0,     0,     0,    18,    77,    78,
      79,     0,     0,     0,    76,   173,    80
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -336,  -336,  -336,  -336,  -336,   346,  -336,  -336,  -336,  -336,
    -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,
    -336,  -336,  -336,    16,  -336,   -54,  -336,   -75,  -101,    22,
    -336,     5,  -336,  -336,  -115,  -336,   -56,  -336,    65,  -336,
    -336,     4,  -336,   -50,  -133,   217,   154,  -130,  -336,  -336,
     -58,  -336,  -153,  -336,  -336,    41,  -335,   -76,  -336,   -28,
    -336,   169,  -336,   224,  -165,  -336,  -144,  -336
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    17,    18,    19,    20,   120,   370,    43,
      21,    22,    39,    23,    24,    25,   121,    26,    35,    65,
     351,    27,    28,   103,   104,    38,    52,   105,   106,    62,
      57,   107,    58,    59,    64,   297,   123,   124,   210,   304,
     390,   391,   125,   142,   109,   110,   180,   111,   112,   113,
     132,   133,   170,   171,   148,   114,    54,   115,   384,   116,
     117,   224,   315,   255,   225,   265,   266,   299
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     119,   143,   108,   126,   169,   221,   219,    31,   256,   256,
     345,   229,   134,   208,   249,   141,    34,   141,    29,  -122,
    -122,  -122,   375,    31,    30,   352,   -60,   167,   353,   200,
     201,   245,   269,     3,    29,   380,   340,    12,    13,    14,
      30,   137,    50,   341,    36,   138,    51,   146,   139,   147,
      53,   271,   108,    63,    32,   108,   211,   248,   308,   195,
     196,   197,   198,   199,   258,   258,   169,   135,   141,   141,
     252,   136,    44,   166,    45,   213,   258,    49,   235,   236,
     141,   108,   322,   323,    41,    42,   108,   296,   259,   259,
    -122,    56,   -66,    33,   204,   230,   253,   135,   205,   232,
     259,   310,    37,   108,   108,   237,   238,   239,   240,   100,
     169,   100,   346,   127,   347,    45,   336,   108,   338,   339,
     388,   108,   389,   342,   343,   264,   264,    12,    13,    14,
      46,   108,    47,    63,   169,   169,    48,   160,   161,   162,
      55,   218,   165,   197,   198,   199,   260,   354,    60,   355,
     302,    61,   261,   261,   273,   275,   200,   201,   267,   226,
     227,   108,   100,   100,   261,   262,   262,   263,   118,   361,
      66,    67,   293,   295,   100,   122,   215,   262,   220,   268,
     219,   223,   128,   129,   130,   108,   108,   131,   152,   140,
     144,   233,   234,   145,   149,   150,   366,   367,   151,   164,
     241,   153,   155,   154,   244,   156,   157,    63,   158,   163,
     264,   179,   264,   264,   254,   254,   181,   264,   264,   373,
     202,   203,   206,   272,   274,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   294,   172,   173,   174,   175,   176,   305,   207,
     209,    -4,   212,   141,   214,   222,   135,   -54,   228,   -54,
     108,   231,   250,   298,   300,   301,   177,   178,   307,   306,
       4,     5,   223,     6,     7,   313,   333,   314,   335,   263,
       8,   268,     9,   328,   329,   316,   337,   332,    10,   317,
     264,   264,   319,   324,   325,   326,   327,   372,    11,   201,
     344,    12,    13,    14,   348,   349,   356,   357,   358,   359,
     392,   363,    15,    16,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,    68,    69,    70,   364,    71,
     387,    72,    73,   365,   368,    74,    75,    76,    77,    78,
      79,     4,     5,    80,   369,   371,    81,    82,    83,   374,
      84,   381,   383,   223,   377,   223,    85,    86,    87,   168,
     379,   385,   386,    88,    40,    89,   394,    90,    91,   395,
     393,   350,    12,    13,    14,   223,   362,    92,    93,    94,
      95,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,    96,   270,   396,   257,   331,
     318,   376,   193,   194,   195,   196,   197,   198,   199,     0,
       0,     0,     0,    97,     0,     0,     0,     0,     0,    98,
       0,     0,    99,   100,     0,     0,   101,     0,     0,     0,
     102,  -121,    68,    69,    70,   -54,    71,   -54,    72,    73,
       0,     0,    74,    75,    76,    77,    78,    79,     4,     5,
      80,     0,     0,    81,    82,    83,     0,    84,     0,     0,
       0,     0,     0,    85,    86,    87,   168,     0,     0,     0,
      88,     0,    89,     0,    90,    91,     0,     0,     0,    12,
      13,    14,     0,     0,    92,    93,    94,    95,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,     0,    96,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
      97,     0,     0,     0,     0,     0,    98,     0,     0,    99,
     100,     0,     0,   101,    68,    69,    70,   102,   216,     0,
      72,    73,     0,     0,    74,    75,    76,    77,    78,    79,
       4,     5,    80,     0,     0,    81,    82,    83,     0,    84,
       0,     0,     0,     0,     0,    85,    86,    87,     0,     0,
       0,     0,    88,     0,    89,     0,    90,    91,     0,     0,
       0,    12,    13,    14,     0,     0,    92,    93,    94,    95,
     217,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    96,   243,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,    97,     0,     0,     0,     0,     0,    98,     0,
       0,    99,   100,     0,     0,   101,    68,    69,    70,   102,
      71,     0,    72,    73,     0,     0,    74,    75,    76,    77,
      78,    79,     4,     5,    80,     0,     0,    81,    82,    83,
       0,    84,     0,     0,     0,     0,     0,    85,    86,    87,
     251,     0,     0,     0,    88,     0,    89,     0,    90,    91,
       0,     0,     0,    12,    13,    14,     0,     0,    92,    93,
      94,    95,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    96,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,     0,    97,     0,     0,     0,     0,     0,
      98,     0,     0,    99,   100,     0,     0,   101,    68,    69,
      70,   102,    71,     0,    72,    73,     0,     0,    74,    75,
      76,    77,    78,    79,     4,     5,    80,     0,     0,    81,
      82,    83,     0,    84,     0,     0,     0,     0,     0,    85,
      86,    87,     0,     0,     0,     0,    88,     0,    89,     0,
      90,    91,     0,     0,     0,    12,    13,    14,     0,     0,
      92,    93,    94,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    96,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,     0,     0,    97,     0,     0,     0,
       0,     0,    98,     0,     0,    99,   100,     0,     0,   101,
      68,    69,    70,   102,   216,     0,    72,    73,     0,     0,
      74,    75,    76,    77,    78,    79,     4,     5,    80,     0,
       0,    81,    82,    83,     0,    84,     0,     0,     0,     0,
       0,    85,    86,    87,     0,     0,     0,     0,    88,     0,
      89,     0,    90,    91,     0,     0,     0,     0,     0,     0,
       0,     0,    92,    93,    94,    95,     0,    68,     0,     0,
       0,   141,     0,    72,     0,     0,     0,    74,    75,     0,
      96,     0,     0,     0,     0,    80,     0,     0,    81,    82,
      83,     0,    84,     0,     0,     0,     0,     0,    97,     0,
       0,     0,     0,     0,    98,     0,     0,    99,   100,    90,
      91,   101,     0,     0,     0,   102,     0,     0,     0,     0,
      68,     0,     0,     0,   141,     0,    72,     0,     0,     0,
      74,    75,    76,     0,     0,     0,     0,    96,    80,     0,
       0,    81,    82,    83,     0,    84,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    97,     0,     0,     0,     0,
       0,    98,    90,    91,    99,   100,     0,     0,   159,     0,
     303,     0,    92,    93,    94,    95,     0,    68,     0,     0,
       0,   141,   246,    72,     0,     0,     0,    74,    75,     0,
      96,     0,     0,     0,     0,    80,     0,     0,    81,    82,
      83,     0,    84,     0,     0,     0,     0,     0,    97,     0,
       0,     0,     0,     0,    98,     0,     0,    99,   100,    90,
      91,   101,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     246,     0,     0,     0,     0,     0,     0,    96,     0,     0,
     247,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    97,     0,     0,     0,     0,
       0,    98,     0,     0,    99,   100,     0,     0,   159,     0,
     242,   243,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   -54,     0,
     -54,     0,     0,     0,     0,     0,     0,     0,   247,     0,
       0,     4,     5,     0,     6,     7,     0,     0,     0,     0,
       0,     8,     0,     9,     0,     0,     0,     0,     0,    10,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    11,
       0,     0,    12,    13,    14,     0,     0,     0,     0,     0,
       0,     0,     0,    15,    16,   242,   243,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   334,     0,     0,     0,     0,     0,     0,   312,
     242,   243,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   312,   242,   243,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   360,   242,
     243,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   309,
     242,   243,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     311,   242,   243,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   320,
     242,   243,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   321,   242,
     243,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   330,   242,   243,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   378,   242,   243,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   382,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   242,   243,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199
};

static const yytype_int16 yycheck[] =
{
      54,    77,    52,    59,   105,   138,   136,     2,   173,   174,
       7,     3,    70,   128,   167,     7,     7,     7,     2,    38,
      39,    40,   357,    18,     2,   110,     7,   102,   113,    77,
      78,   164,   176,     0,    18,   370,   104,    50,    51,    52,
      18,   106,     3,   111,   106,   110,     7,     7,   113,     9,
      53,   181,   102,    48,    11,   105,   131,   105,   211,    90,
      91,    92,    93,    94,     3,     3,   167,   106,     7,     7,
     171,   110,     6,   101,     8,   133,     3,     7,   153,   154,
       7,   131,   235,   236,    48,    49,   136,   202,    27,    27,
     109,    72,   105,    11,   106,   145,   172,   106,   110,   149,
      27,   110,   108,   153,   154,   155,   156,   157,   158,   101,
     211,   101,   109,     6,   111,     8,   260,   167,   262,   263,
       6,   171,     8,   267,   268,   175,   176,    50,    51,    52,
      11,   181,    11,   128,   235,   236,   108,    96,    97,    98,
       7,   136,   101,    92,    93,    94,    85,   312,    11,   314,
     206,    11,    91,    91,   182,   183,    77,    78,    85,    75,
      76,   211,   101,   101,    91,   104,   104,   106,     3,   334,
     107,   107,   200,   201,   101,     7,   135,   104,   137,   106,
     310,   140,    37,   109,   104,   235,   236,    40,     7,   104,
     104,   150,   151,   104,   104,   104,   340,   341,   104,   112,
     159,   108,   104,   108,   163,   104,   104,   202,   104,   104,
     260,   112,   262,   263,   173,   174,    44,   267,   268,   352,
     104,   108,   111,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,    72,    73,    74,    75,    76,   207,    72,
       7,     0,    38,     7,    39,     7,   106,     6,    11,     8,
     310,   104,   109,     7,     3,     3,    95,    96,   105,   111,
      19,    20,   231,    22,    23,   105,   109,   111,   104,   106,
      29,   106,    31,   242,   243,   105,     3,   246,    37,   105,
     340,   341,   105,   105,   105,   105,   105,   351,    47,    78,
     105,    50,    51,    52,   107,     3,   105,   105,   109,   109,
     386,    84,    61,    62,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,     3,     4,     5,   105,     7,
     384,     9,    10,   107,    84,    13,    14,    15,    16,    17,
      18,    19,    20,    21,   107,   107,    24,    25,    26,     7,
      28,    33,    54,   312,   105,   314,    34,    35,    36,    37,
     105,   108,   104,    41,    18,    43,   109,    45,    46,   105,
     111,   306,    50,    51,    52,   334,   335,    55,    56,    57,
      58,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    73,   179,   393,   174,   245,
     231,   360,    88,    89,    90,    91,    92,    93,    94,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,    97,
      -1,    -1,   100,   101,    -1,    -1,   104,    -1,    -1,    -1,
     108,   109,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,    -1,    24,    25,    26,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    -1,    -1,    -1,
      41,    -1,    43,    -1,    45,    46,    -1,    -1,    -1,    50,
      51,    52,    -1,    -1,    55,    56,    57,    58,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    -1,    73,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      91,    -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,   100,
     101,    -1,    -1,   104,     3,     4,     5,   108,     7,    -1,
       9,    10,    -1,    -1,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    -1,    24,    25,    26,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    -1,    -1,
      -1,    -1,    41,    -1,    43,    -1,    45,    46,    -1,    -1,
      -1,    50,    51,    52,    -1,    -1,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    91,    -1,    -1,    -1,    -1,    -1,    97,    -1,
      -1,   100,   101,    -1,    -1,   104,     3,     4,     5,   108,
       7,    -1,     9,    10,    -1,    -1,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    24,    25,    26,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    -1,    -1,    -1,    41,    -1,    43,    -1,    45,    46,
      -1,    -1,    -1,    50,    51,    52,    -1,    -1,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    -1,    91,    -1,    -1,    -1,    -1,    -1,
      97,    -1,    -1,   100,   101,    -1,    -1,   104,     3,     4,
       5,   108,     7,    -1,     9,    10,    -1,    -1,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    24,
      25,    26,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,    -1,    -1,    -1,    -1,    41,    -1,    43,    -1,
      45,    46,    -1,    -1,    -1,    50,    51,    52,    -1,    -1,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    -1,    -1,    91,    -1,    -1,    -1,
      -1,    -1,    97,    -1,    -1,   100,   101,    -1,    -1,   104,
       3,     4,     5,   108,     7,    -1,     9,    10,    -1,    -1,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    24,    25,    26,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    -1,    -1,    -1,    -1,    41,    -1,
      43,    -1,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    57,    58,    -1,     3,    -1,    -1,
      -1,     7,    -1,     9,    -1,    -1,    -1,    13,    14,    -1,
      73,    -1,    -1,    -1,    -1,    21,    -1,    -1,    24,    25,
      26,    -1,    28,    -1,    -1,    -1,    -1,    -1,    91,    -1,
      -1,    -1,    -1,    -1,    97,    -1,    -1,   100,   101,    45,
      46,   104,    -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,
       3,    -1,    -1,    -1,     7,    -1,     9,    -1,    -1,    -1,
      13,    14,    15,    -1,    -1,    -1,    -1,    73,    21,    -1,
      -1,    24,    25,    26,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,
      -1,    97,    45,    46,   100,   101,    -1,    -1,   104,    -1,
     106,    -1,    55,    56,    57,    58,    -1,     3,    -1,    -1,
      -1,     7,    37,     9,    -1,    -1,    -1,    13,    14,    -1,
      73,    -1,    -1,    -1,    -1,    21,    -1,    -1,    24,    25,
      26,    -1,    28,    -1,    -1,    -1,    -1,    -1,    91,    -1,
      -1,    -1,    -1,    -1,    97,    -1,    -1,   100,   101,    45,
      46,   104,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    73,    -1,    -1,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,
      -1,    97,    -1,    -1,   100,   101,    -1,    -1,   104,    -1,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,     6,    -1,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,
      -1,    19,    20,    -1,    22,    23,    -1,    -1,    -1,    -1,
      -1,    29,    -1,    31,    -1,    -1,    -1,    -1,    -1,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      -1,    -1,    50,    51,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    62,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   104,    -1,    -1,    -1,    -1,    -1,    -1,   111,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   111,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     107,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   105,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   105,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   115,   116,     0,    19,    20,    22,    23,    29,    31,
      37,    47,    50,    51,    52,    61,    62,   117,   118,   119,
     120,   124,   125,   127,   128,   129,   131,   135,   136,   137,
     143,   145,    11,    11,     7,   132,   106,   108,   139,   126,
     119,    48,    49,   123,     6,     8,    11,    11,   108,     7,
       3,     7,   140,    53,   170,     7,    72,   144,   146,   147,
      11,    11,   143,   145,   148,   133,   107,   107,     3,     4,
       5,     7,     9,    10,    13,    14,    15,    16,    17,    18,
      21,    24,    25,    26,    28,    34,    35,    36,    41,    43,
      45,    46,    55,    56,    57,    58,    73,    91,    97,   100,
     101,   104,   108,   137,   138,   141,   142,   145,   157,   158,
     159,   161,   162,   163,   169,   171,   173,   174,     3,   139,
     121,   130,     7,   150,   151,   156,   150,     6,    37,   109,
     104,    40,   164,   165,   164,   106,   110,   106,   110,   113,
     104,     7,   157,   171,   104,   104,     7,     9,   168,   104,
     104,   104,     7,   108,   108,   104,   104,   104,   104,   104,
     169,   169,   169,   104,   112,   169,   173,   141,    37,   142,
     166,   167,    72,    73,    74,    75,    76,    95,    96,   112,
     160,    44,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      77,    78,   104,   108,   106,   110,   111,    72,   148,     7,
     152,   141,    38,   164,    39,   169,     7,    59,   145,   161,
     169,   158,     7,   169,   175,   178,    75,    76,    11,     3,
     157,   104,   157,   169,   169,   141,   141,   157,   157,   157,
     157,   169,    77,    78,   169,   158,    37,   105,   105,   166,
     109,    37,   142,   171,   169,   177,   178,   177,     3,    27,
      85,    91,   104,   106,   157,   179,   180,    85,   106,   180,
     159,   161,   169,   173,   169,   173,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   173,   169,   173,   148,   149,     7,   181,
       3,     3,   150,   106,   153,   169,   111,   105,   166,   107,
     110,   107,   111,   105,   111,   176,   105,   105,   175,   105,
     105,   105,   166,   166,   105,   105,   105,   105,   169,   169,
     105,   160,   169,   109,   104,   104,   180,     3,   180,   180,
     104,   111,   180,   180,   105,     7,   109,   111,   107,     3,
     152,   134,   110,   113,   178,   178,   105,   105,   109,   109,
     110,   178,   169,    84,   105,   107,   180,   180,    84,   107,
     122,   107,   139,   158,     7,   170,   169,   105,   105,   105,
     170,    33,   105,    54,   172,   108,   104,   139,     6,     8,
     154,   155,   171,   111,   109,   105,   155
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   114,   116,   115,   117,   118,   118,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   121,   122,   120,   123,
     123,   124,   124,   124,   124,   126,   125,   127,   128,   130,
     129,   132,   133,   134,   131,   135,   135,   136,   136,   136,
     136,   137,   137,   138,   140,   139,   141,   141,   141,   142,
     142,   142,   142,   142,   143,   143,   143,   143,   144,   144,
     146,   145,   147,   145,   148,   148,   149,   149,   150,   150,
     151,   151,   151,   152,   152,   152,   153,   154,   154,   155,
     155,   156,   156,   156,   157,   158,   158,   159,   159,   160,
     160,   161,   161,   162,   162,   162,   162,   162,   162,   162,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   164,   164,
     165,   166,   166,   167,   167,   168,   168,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   170,   170,
     171,   171,   172,   172,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   174,   174,   174,   174,   175,   175,   176,
     176,   177,   177,   178,   178,   179,   179,   179,   179,   180,
     180,   180,   180,   181,   181,   181
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     0,    11,     1,
       1,     0,     1,     4,     4,     0,     4,     2,     5,     0,
       7,     0,     0,     0,     9,     1,     1,     3,     3,     4,
       4,     1,     1,     1,     0,     5,     1,     3,     2,     1,
       3,     3,     1,     3,     0,     1,     1,     1,     0,     1,
       0,     4,     0,     4,     1,     3,     0,     1,     1,     3,
       1,     3,     3,     0,     1,     3,     7,     1,     1,     1,
       3,     1,     3,     4,     1,     1,     4,     2,     4,     0,
       2,     1,     1,     3,     3,     3,     3,     1,     2,     3,
       3,     2,     2,     5,     4,     4,     2,     1,     3,     5,
       5,     3,     1,     1,     5,     5,     4,     4,     1,     2,
       3,     0,     1,     1,     2,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     4,     2,     2,     2,
       7,     6,     4,     4,     5,     5,     1,     1,     1,     1,
       1,     1,     1,     4,     6,     6,     3,     3,     0,     2,
       1,     1,     0,     4,     1,     3,     3,     3,     3,     3,
       3,     3,     1,     4,     4,     4,     4,     0,     1,     0,
       2,     1,     4,     1,     3,     1,     4,     1,     2,     1,
       3,     4,     3,     1,     2,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (globalSymTab, program, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, globalSymTab, program); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, symTable** globalSymTab, stmnt** program)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (globalSymTab);
  YYUSE (program);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, symTable** globalSymTab, stmnt** program)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, globalSymTab, program);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, symTable** globalSymTab, stmnt** program)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              , globalSymTab, program);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, globalSymTab, program); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, symTable** globalSymTab, stmnt** program)
{
  YYUSE (yyvaluep);
  YYUSE (globalSymTab);
  YYUSE (program);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (symTable** globalSymTab, stmnt** program)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, globalSymTab);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 145 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                  { *globalSymTab = new symTable("global"); symTable::addPredefinedSym(*globalSymTab); currentSymTab = *globalSymTab; }
#line 2094 "y.tab.cpp"
    break;

  case 4:
#line 150 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout<< "REDUCE: units -> program\n";}
#line 2100 "y.tab.cpp"
    break;

  case 5:
#line 153 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout<< "REDUCE: unit -> units\n"; }
#line 2106 "y.tab.cpp"
    break;

  case 6:
#line 154 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout<< "REDUCE: units unit -> units\n"; }
#line 2112 "y.tab.cpp"
    break;

  case 7:
#line 157 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                        { std::cout<< "REDUCE: proc -> unit\n"; *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2118 "y.tab.cpp"
    break;

  case 8:
#line 158 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { std::cout<< "REDUCE: init -> unit\n"; *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2124 "y.tab.cpp"
    break;

  case 9:
#line 159 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { assert(false); std::cout << "The 'events' construct is currently not supported."; }
#line 2130 "y.tab.cpp"
    break;

  case 10:
#line 160 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { 
													std::cout << "REDUCE: one_decl -> unit\n";
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
#line 2148 "y.tab.cpp"
    break;

  case 11:
#line 173 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { std::cout << "REDUCE: utype -> unit\n"; *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2154 "y.tab.cpp"
    break;

  case 12:
#line 174 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { std::cout << "REDUCE: mtype -> unit\n"; *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2160 "y.tab.cpp"
    break;

  case 13:
#line 175 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { std::cout << "Embedded C code is not supported."; }
#line 2166 "y.tab.cpp"
    break;

  case 14:
#line 176 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { std::cout << "REDUCE: ns -> unit\n"; *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2172 "y.tab.cpp"
    break;

  case 16:
#line 183 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                  { nameSpace = (yyvsp[0].sVal); savedSymTab = currentSymTab; currentSymTab = currentSymTab->createSubTable(nameSpace); }
#line 2178 "y.tab.cpp"
    break;

  case 17:
#line 185 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                  { currentSymTab = savedSymTab; }
#line 2184 "y.tab.cpp"
    break;

  case 18:
#line 188 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        {	
		  											std::cout<< "REDUCE: inst proctype NAME ( decl ) prio ena body -> proc\n";
													auto procNbLine = (yyvsp[0].pStmntVal)->getLineNb();
		  											procSymNode* proc = new procSymNode((yyvsp[-8].sVal), (yyvsp[-10].pConstExprVal), declSyms, (yyvsp[0].pStmntVal), procNbLine);
		  											declSyms.clear();
		  											(yyval.pStmntVal) = new procDecl(proc, procNbLine);
		  											(*globalSymTab)->insert(proc);
		  											nameSpace = "global";
		  											free((yyvsp[-8].sVal));
		  										}
#line 2199 "y.tab.cpp"
    break;

  case 19:
#line 200 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "REDUCE: -> PROCTYPE proctype\n"; }
#line 2205 "y.tab.cpp"
    break;

  case 20:
#line 201 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "Deterministic proctypes are not supported (only useful for simulation)."; }
#line 2211 "y.tab.cpp"
    break;

  case 21:
#line 204 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "REDUCE: void -> inst\n"; (yyval.pConstExprVal) = new exprConst(0, nbrLines); }
#line 2217 "y.tab.cpp"
    break;

  case 22:
#line 205 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { std::cout << "REDUCE: ACTIVE -> inst\n"; (yyval.pConstExprVal) = new exprConst(1, nbrLines); }
#line 2223 "y.tab.cpp"
    break;

  case 23:
#line 206 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "REDUCE: ACTIVE [ CONST ] -> inst \n"; (yyval.pConstExprVal) = new exprConst((yyvsp[-1].iVal), nbrLines); }
#line 2229 "y.tab.cpp"
    break;

  case 24:
#line 207 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { 
													std::cout << "REDUCE: ACTIVE [ NAME ] -> inst\n";
													varSymNode* var = *globalSymTab? static_cast<varSymNode*>((*globalSymTab)->lookup((yyvsp[-1].sVal))) : nullptr;
													if(var == nullptr) std::cout << "The variable "<<(yyvsp[-1].sVal)<<" does not exist.";
													else if(var->getType() != symbol::T_INT && var->getType() != symbol::T_BYTE && var->getType() != symbol::T_SHORT) std::cout << "The variable "<<(yyvsp[-1].sVal)<<" is not of type int, short or bit.";
													else if(var->getInitExpr() == nullptr || var->getInitExpr()->getType() != astNode::E_EXPR_CONST) std::cout << "The variable "<<(yyvsp[-1].sVal)<<" does not have a constant value.";
													else {
														(yyval.pConstExprVal) = new exprConst(static_cast<exprConst*>(var->getInitExpr())->getCstValue(), nbrLines);
													}
													free((yyvsp[-1].sVal));											
												}
#line 2245 "y.tab.cpp"
    break;

  case 25:
#line 221 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                { nameSpace = "init"; }
#line 2251 "y.tab.cpp"
    break;

  case 26:
#line 223 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        {	
													std::cout << "REDUCE: INIT Opt_priority body -> init\n";
													if(*globalSymTab && (*globalSymTab)->lookup("init") != nullptr) 
														std::cout << "This is the second init process; only one is allowed.";
													else {
														initSymNode* init = new initSymNode(nbrLines, (yyvsp[0].pStmntVal));
														(yyval.pStmntVal) = new initDecl(init, nbrLines);
														(*globalSymTab)->insert(init);
													}
													nameSpace = "global";
												}
#line 2267 "y.tab.cpp"
    break;

  case 27:
#line 236 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "Event sequences (traces) are not supported."; }
#line 2273 "y.tab.cpp"
    break;

  case 28:
#line 239 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                        {	
													std::cout << "REDUCE: TYPEDEF NAME '{' decl_lst '}' -> utype\n";
													tdefSymNode* tdef = new tdefSymNode((yyvsp[-3].sVal), *globalSymTab, declSyms, nbrLines);
													(yyval.pStmntVal) = new tdefDecl(tdef, nbrLines);
													(*globalSymTab)->insert(tdef);
													for(auto declSym : declSyms)
														(*globalSymTab)->remove(declSym->getName());
													declSyms.clear();
													free((yyvsp[-3].sVal));  
												}
#line 2288 "y.tab.cpp"
    break;

  case 29:
#line 251 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        {	mtypeDef = new mtypedefSymNode(nbrLines);	}
#line 2294 "y.tab.cpp"
    break;

  case 30:
#line 252 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                {
													assert(mtypeDef->getMTypeList().size() != 0);
													(*globalSymTab)->insert(mtypeDef);

													std::cout << "REDUCE: vis TYPE asgn { nlst } -> one_decl\n";
													if((yyvsp[-5].iType) != symbol::T_MTYPE) {
														std::cout <<  "This syntax only works for MTYPEs definition.";
														exit(1);
													}
													(yyval.pStmntVal) = new mtypeDecl(mtypeDef, nbrLines);
													// The mtype values are added in the nlst rule.
												}
#line 2311 "y.tab.cpp"
    break;

  case 31:
#line 270 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                         { inInline = true; }
#line 2317 "y.tab.cpp"
    break;

  case 32:
#line 271 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                       { nameSpace = (yyvsp[0].sVal); savedSymTab = currentSymTab; currentSymTab = currentSymTab->createSubTable(nameSpace); }
#line 2323 "y.tab.cpp"
    break;

  case 33:
#line 273 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                  { for(std::string it : params) 
		  		currentSymTab->insert(varSymNode::createSymbol(symbol::T_NA, nbrLines, it));
		    currentSymTab = savedSymTab;
		  }
#line 2332 "y.tab.cpp"
    break;

  case 34:
#line 277 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        {
													std::cout<< "REDUCE: INLINE nm ( param_list ) body -> ns\n";
													auto sym = new inlineSymNode((yyvsp[-6].sVal), params, (yyvsp[0].pStmntVal), nbrLines);
													params.clear();
		  											(yyval.pStmntVal) = new inlineDecl(sym, nbrLines);
													(*globalSymTab)->insert(sym);
													inInline = false;
													free((yyvsp[-6].sVal));
												}
#line 2346 "y.tab.cpp"
    break;

  case 44:
#line 305 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { 
													savedSymTab = currentSymTab; 
													if(!(currentSymTab = (*globalSymTab)->getSubSymTab(nameSpace)))
														currentSymTab = savedSymTab->createSubTable(nameSpace); 
													nameSpace = "";
												}
#line 2357 "y.tab.cpp"
    break;

  case 45:
#line 312 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { std::cout << "REDUCE: '{' sequence OS '}' -> body\n"; (yyval.pStmntVal) = (yyvsp[-2].pStmntVal); (yyval.pStmntVal)->setLocalSymTab(currentSymTab); currentSymTab->setBlock((yyvsp[-2].pStmntVal)); currentSymTab = savedSymTab; }
#line 2363 "y.tab.cpp"
    break;

  case 46:
#line 315 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "REDUCE: step -> sequence\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal);  }
#line 2369 "y.tab.cpp"
    break;

  case 47:
#line 316 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "REDUCE: sequence MS step -> sequence\n"; (yyval.pStmntVal) = stmnt::merge((yyvsp[-2].pStmntVal), (yyvsp[0].pStmntVal)); }
#line 2375 "y.tab.cpp"
    break;

  case 48:
#line 317 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "REDUCE: sequence step -> sequence\n"; (yyval.pStmntVal) = stmnt::merge((yyvsp[-1].pStmntVal), (yyvsp[0].pStmntVal)); }
#line 2381 "y.tab.cpp"
    break;

  case 49:
#line 320 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { 
													assert(declSyms.front()->getType() != symbol::T_MTYPE_DEF); 
												 	(yyval.pStmntVal) = new varDecl(static_cast<std::list<varSymNode*>>(declSyms), nbrLines);
												 	declSyms.clear();
												}
#line 2391 "y.tab.cpp"
    break;

  case 50:
#line 325 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "Declarations with labels are not suported."; }
#line 2397 "y.tab.cpp"
    break;

  case 51:
#line 326 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "Channel assertions are currently not supported."; }
#line 2403 "y.tab.cpp"
    break;

  case 52:
#line 327 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { std::cout << "REDUCE: stmnt -> step\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2409 "y.tab.cpp"
    break;

  case 53:
#line 328 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "Unless statements are currently not supported."; }
#line 2415 "y.tab.cpp"
    break;

  case 55:
#line 337 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { std::cout << "The 'hidden' keyword is not supported."; }
#line 2421 "y.tab.cpp"
    break;

  case 56:
#line 338 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { std::cout << "The 'show' keyword is not supported."; }
#line 2427 "y.tab.cpp"
    break;

  case 57:
#line 339 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { std::cout << "The 'local' keyword is not supported."; }
#line 2433 "y.tab.cpp"
    break;

  case 60:
#line 349 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                   { declType = (yyvsp[0].iType); }
#line 2439 "y.tab.cpp"
    break;

  case 61:
#line 349 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                { std::cout << "REDUCE: vis TYPE var_list -> one_decl\n"; }
#line 2445 "y.tab.cpp"
    break;

  case 62:
#line 350 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                            { declType = symbol::T_UTYPE; typeDef = *globalSymTab? static_cast<tdefSymNode*>((*globalSymTab)->lookup((yyvsp[0].sVal))) : nullptr; assert(typeDef); }
#line 2451 "y.tab.cpp"
    break;

  case 63:
#line 350 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                                                                                                                                        { std::cout << "REDUCE: vis UNAME var_list -> one_decl\n"; free((yyvsp[-2].sVal)); }
#line 2457 "y.tab.cpp"
    break;

  case 64:
#line 353 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "REDUCE: one_decl -> decl_list\n"; }
#line 2463 "y.tab.cpp"
    break;

  case 65:
#line 354 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "REDUCE: one_decl SEMI decl_list -> decl_lst\n"; }
#line 2469 "y.tab.cpp"
    break;

  case 66:
#line 358 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "REDUCE: void -> decl\n"; }
#line 2475 "y.tab.cpp"
    break;

  case 67:
#line 359 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { std::cout << "REDUCE: decl_list -> decl\n"; }
#line 2481 "y.tab.cpp"
    break;

  case 68:
#line 366 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "REDUCE: ivar -> var_list\n"; currentSymTab->insert((yyvsp[0].pVarSymVal)); declSyms.push_front((yyvsp[0].pVarSymVal)); }
#line 2487 "y.tab.cpp"
    break;

  case 69:
#line 367 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "REDUCE: ivar , var_list -> var_list\n"; currentSymTab->insert((yyvsp[-2].pVarSymVal)); declSyms.push_front((yyvsp[-2].pVarSymVal)); }
#line 2493 "y.tab.cpp"
    break;

  case 70:
#line 370 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { 
												  std::cout << "REDUCE: var_decl -> ivar\n"; (yyval.pVarSymVal) = varSymNode::createSymbol(declType, nbrLines, (yyvsp[0].pDataVal).sVal, (yyvsp[0].pDataVal).iVal); 
												  if(declType == symbol::T_UTYPE) { assert(typeDef); static_cast<utypeSymNode*>((yyval.pVarSymVal))->setUType(typeDef); }
												  if((yyvsp[0].pDataVal).sVal) free((yyvsp[0].pDataVal).sVal);
												}
#line 2503 "y.tab.cpp"
    break;

  case 71:
#line 375 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "REDUCE: var_decl ASGN expr -> ivar\n"; 
												  (yyval.pVarSymVal) = varSymNode::createSymbol(declType, nbrLines, (yyvsp[-2].pDataVal).sVal, (yyvsp[-2].pDataVal).iVal, (yyvsp[0].pExprVal)); 
												  if(declType == symbol::T_UTYPE) { assert(typeDef); static_cast<utypeSymNode*>((yyval.pVarSymVal))->setUType(typeDef); }
												  if((yyvsp[-2].pDataVal).sVal) free((yyvsp[-2].pDataVal).sVal);
												}
#line 2513 "y.tab.cpp"
    break;

  case 72:
#line 380 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "REDUCE: var_decl ASGN ch_init -> ivar\n"; (yyval.pVarSymVal) = new chanSymNode(nbrLines, (yyvsp[-2].pDataVal).sVal, (yyvsp[-2].pDataVal).iVal, (yyvsp[0].pDataVal).iVal, typeLst);	
												  typeLst.clear(); if((yyvsp[-2].pDataVal).sVal) free((yyvsp[-2].pDataVal).sVal); //double free???if($3.sVal) free($3.sVal); 
												}
#line 2521 "y.tab.cpp"
    break;

  case 73:
#line 385 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { }
#line 2527 "y.tab.cpp"
    break;

  case 74:
#line 386 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { params.push_front(std::string((yyvsp[0].sVal))); free((yyvsp[0].sVal)); }
#line 2533 "y.tab.cpp"
    break;

  case 75:
#line 387 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                            { params.push_front(std::string((yyvsp[-2].sVal))); free((yyvsp[-2].sVal)); }
#line 2539 "y.tab.cpp"
    break;

  case 76:
#line 391 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                        { std::cout << "REDUCE: [ CONST ] OF { typ_list } -> ch_init\n"; (yyval.pDataVal).iVal = (yyvsp[-5].iVal); }
#line 2545 "y.tab.cpp"
    break;

  case 77:
#line 394 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pDataVal).sVal = nullptr; (yyval.pDataVal).iType = (yyvsp[0].iType); }
#line 2551 "y.tab.cpp"
    break;

  case 78:
#line 395 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pDataVal).sVal = (yyvsp[0].sVal); (yyval.pDataVal).iType = symbol::T_UTYPE; }
#line 2557 "y.tab.cpp"
    break;

  case 79:
#line 399 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                {	std::cout << "REDUCE: basetype -> typ_list\n";
													varSymNode* typ = nullptr;
													if((yyvsp[0].pDataVal).iType != symbol::T_UTYPE && (yyvsp[0].pDataVal).iType != symbol::T_NA) {
														typ = varSymNode::createSymbol((yyvsp[0].pDataVal).iType, nbrLines);
													} else {
														tdefSymNode* pType = *globalSymTab ? dynamic_cast<tdefSymNode*>((*globalSymTab)->lookup((yyvsp[0].pDataVal).sVal)) : nullptr;
														typ = new utypeSymNode(pType, nbrLines);
														if(typ == nullptr) {
															std::cout << "The type "<<(yyvsp[0].pDataVal).sVal<<" was not declared in a typedef.\n";
															assert(false);
														}
													}
													typeLst.push_back(typ);
													if((yyvsp[0].pDataVal).sVal) free((yyvsp[0].pDataVal).sVal);
												}
#line 2577 "y.tab.cpp"
    break;

  case 80:
#line 414 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        {	std::cout << "REDUCE: basetype , typ_list -> typ_list\n";
													varSymNode* typ = nullptr;
													if((yyvsp[-2].pDataVal).iType != symbol::T_UTYPE && (yyvsp[-2].pDataVal).iType != symbol::T_NA) {
														typ = varSymNode::createSymbol((yyvsp[-2].pDataVal).iType, nbrLines);
													} else {
														tdefSymNode* pType = *globalSymTab ? dynamic_cast<tdefSymNode*>((*globalSymTab)->lookup((yyvsp[-2].pDataVal).sVal)) : nullptr;
														typ = new utypeSymNode(pType, nbrLines);
														if(typ == nullptr) {
															std::cout << "The type "<<(yyvsp[-2].pDataVal).sVal<<" was not declared in a typedef.\n";
															assert(false);
														}
													}
													typeLst.push_front(typ);
													if((yyvsp[-2].pDataVal).sVal) free((yyvsp[-2].pDataVal).sVal);
												}
#line 2597 "y.tab.cpp"
    break;

  case 81:
#line 431 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "REDUCE: NAME -> vardcl\n"; (yyval.pDataVal).sVal = (yyvsp[0].sVal); (yyval.pDataVal).iVal = 1; }
#line 2603 "y.tab.cpp"
    break;

  case 82:
#line 432 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "The 'unsigned' data type is not supported."; }
#line 2609 "y.tab.cpp"
    break;

  case 83:
#line 433 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "REDUCE: NAME [ CONST ] -> vardcl\n"; (yyval.pDataVal).sVal = (yyvsp[-3].sVal); (yyval.pDataVal).iVal = (yyvsp[-1].iVal); }
#line 2615 "y.tab.cpp"
    break;

  case 84:
#line 436 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "REDUCE: cmpnd -> varref\n"; (yyval.pExprVarRefVal) = (yyvsp[0].pExprVarRefVal); auto sym = (yyval.pExprVarRefVal)->resolve(currentSymTab); assert(sym || inInline); }
#line 2621 "y.tab.cpp"
    break;

  case 85:
#line 439 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "REDUCE: NAME -> pfld\n"; (yyval.pExprVarRefNameVal) = new exprVarRefName((yyvsp[0].sVal), nbrLines); free((yyvsp[0].sVal)); }
#line 2627 "y.tab.cpp"
    break;

  case 86:
#line 440 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "REDUCE: NAME [ expr ] -> pfld\n"; (yyval.pExprVarRefNameVal) = new exprVarRefName((yyvsp[-3].sVal), (yyvsp[-1].pExprVal), nbrLines); free((yyvsp[-3].sVal)); }
#line 2633 "y.tab.cpp"
    break;

  case 87:
#line 443 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "REDUCE: pfld sfld -> cmpnd\n"; (yyval.pExprVarRefVal) = new exprVarRef(nbrLines, (yyvsp[-1].pExprVarRefNameVal), (yyvsp[0].pExprVarRefVal)); }
#line 2639 "y.tab.cpp"
    break;

  case 88:
#line 444 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "REDUCE: CONTEX . pfld sfld -> cmpnd\n"; (yyval.pExprVarRefVal) = new exprVarRef(nbrLines, (yyvsp[-1].pExprVarRefNameVal), (yyvsp[0].pExprVarRefVal)); }
#line 2645 "y.tab.cpp"
    break;

  case 89:
#line 447 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { std::cout << "REDUCE: void -> sfld\n"; (yyval.pExprVarRefVal) = nullptr; }
#line 2651 "y.tab.cpp"
    break;

  case 90:
#line 448 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "REDUCE: . cmpnd -> sfld\n"; (yyval.pExprVarRefVal) = (yyvsp[0].pExprVarRefVal);   }
#line 2657 "y.tab.cpp"
    break;

  case 91:
#line 452 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "REDUCE: special -> stmnt\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2663 "y.tab.cpp"
    break;

  case 92:
#line 453 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { std::cout << "REDUCE: Stmnt -> stmnt\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2669 "y.tab.cpp"
    break;

  case 93:
#line 456 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pStmntVal) = new stmntChanRecv((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprRArgListVal), nbrLines); }
#line 2675 "y.tab.cpp"
    break;

  case 94:
#line 457 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pStmntVal) = new stmntChanSnd((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprArgListVal), nbrLines); }
#line 2681 "y.tab.cpp"
    break;

  case 95:
#line 458 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pStmntVal) = new stmntIf((yyvsp[-1].pStmntOptVal), (yyvsp[-2].iVal)); }
#line 2687 "y.tab.cpp"
    break;

  case 96:
#line 459 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pStmntVal) = new stmntDo((yyvsp[-1].pStmntOptVal), (yyvsp[-2].iVal)); }
#line 2693 "y.tab.cpp"
    break;

  case 97:
#line 460 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntBreak(nbrLines); }
#line 2699 "y.tab.cpp"
    break;

  case 98:
#line 461 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntGoto((yyvsp[0].sVal), nbrLines); free((yyvsp[0].sVal)); }
#line 2705 "y.tab.cpp"
    break;

  case 99:
#line 462 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { if((yyvsp[0].pStmntVal)->getType() == astNode::E_STMNT_LABEL && static_cast<stmntLabel*>((yyvsp[0].pStmntVal))->getLabelled()->getType() == astNode::E_STMNT_LABEL) 
													std::cout << "Only two labels per state are supported."; 
												  (yyval.pStmntVal) = new stmntLabel((yyvsp[-2].sVal), (yyvsp[0].pStmntVal), nbrLines); free((yyvsp[-2].sVal)); }
#line 2713 "y.tab.cpp"
    break;

  case 100:
#line 466 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { (yyval.pStmntVal) = new stmntAsgn((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2719 "y.tab.cpp"
    break;

  case 101:
#line 467 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pStmntVal) = new stmntIncr((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2725 "y.tab.cpp"
    break;

  case 102:
#line 468 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pStmntVal) = new stmntDecr((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2731 "y.tab.cpp"
    break;

  case 103:
#line 469 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { (yyval.pStmntVal) = new stmntPrint((yyvsp[-2].sVal), (yyvsp[-1].pExprArgListVal), nbrLines); }
#line 2737 "y.tab.cpp"
    break;

  case 104:
#line 470 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pStmntVal) = new stmntPrintm((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2743 "y.tab.cpp"
    break;

  case 105:
#line 471 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pStmntVal) = new stmntPrintm((yyvsp[-1].iVal), nbrLines); }
#line 2749 "y.tab.cpp"
    break;

  case 106:
#line 472 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pStmntVal) = new stmntAssert((yyvsp[0].pExprVal), nbrLines); }
#line 2755 "y.tab.cpp"
    break;

  case 107:
#line 473 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { std::cout << "Embedded C code is not supported."; }
#line 2761 "y.tab.cpp"
    break;

  case 108:
#line 474 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "Sorted send and random receive are not supported."; }
#line 2767 "y.tab.cpp"
    break;

  case 109:
#line 475 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "Channel poll operations are not supported."; }
#line 2773 "y.tab.cpp"
    break;

  case 110:
#line 476 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "Channel poll operations are not supported."; }
#line 2779 "y.tab.cpp"
    break;

  case 111:
#line 477 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "Sorted send and random receive are not supported."; }
#line 2785 "y.tab.cpp"
    break;

  case 112:
#line 478 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntExpr((yyvsp[0].pExprVal), nbrLines); }
#line 2791 "y.tab.cpp"
    break;

  case 113:
#line 479 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntElse(nbrLines); }
#line 2797 "y.tab.cpp"
    break;

  case 114:
#line 480 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { (yyval.pStmntVal) = new stmntAtomic((yyvsp[-2].pStmntVal), nbrLines); }
#line 2803 "y.tab.cpp"
    break;

  case 115:
#line 481 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { (yyval.pStmntVal) = new stmntDStep((yyvsp[-2].pStmntVal), nbrLines); }
#line 2809 "y.tab.cpp"
    break;

  case 116:
#line 482 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pStmntVal) = new stmntSeq((yyvsp[-2].pStmntVal), nbrLines); }
#line 2815 "y.tab.cpp"
    break;

  case 117:
#line 483 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { 
													(yyval.pStmntVal) = new stmntCall((yyvsp[-3].sVal), (yyvsp[-1].pExprArgListVal), nbrLines); 
													auto fctSym = (*globalSymTab)->lookup((yyvsp[-3].sVal));
													std::cout << "Inline call "<< (yyvsp[-3].sVal) <<" at line "<< nbrLines <<"\n";
													assert(fctSym->getType() == symbol::T_INLINE);
													assert(dynamic_cast<inlineSymNode*>(fctSym) != nullptr);
													if((yyvsp[-1].pExprArgListVal))
														assert(dynamic_cast<inlineSymNode*>(fctSym)->getParams().size() == (yyvsp[-1].pExprArgListVal)->getSize());
													free((yyvsp[-3].sVal)); 
												}
#line 2830 "y.tab.cpp"
    break;

  case 118:
#line 495 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pStmntOptVal) = new stmntOpt((yyvsp[0].pStmntVal), nbrLines); }
#line 2836 "y.tab.cpp"
    break;

  case 119:
#line 496 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pStmntOptVal) = new stmntOpt((yyvsp[-1].pStmntVal), (yyvsp[0].pStmntOptVal), nbrLines); }
#line 2842 "y.tab.cpp"
    break;

  case 120:
#line 499 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pStmntVal) = (yyvsp[-1].pStmntVal); }
#line 2848 "y.tab.cpp"
    break;

  case 122:
#line 513 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                        { /* redundant semi at end of sequence */ }
#line 2854 "y.tab.cpp"
    break;

  case 123:
#line 516 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                        { /* at least one semi-colon */ }
#line 2860 "y.tab.cpp"
    break;

  case 124:
#line 517 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                        { /* but more are okay too   */ }
#line 2866 "y.tab.cpp"
    break;

  case 125:
#line 520 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.sVal) = (yyvsp[0].sVal); }
#line 2872 "y.tab.cpp"
    break;

  case 126:
#line 521 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.sVal) = (yyvsp[0].sVal); }
#line 2878 "y.tab.cpp"
    break;

  case 127:
#line 524 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprVal) = new exprPar		((yyvsp[-1].pExprVal), nbrLines); }
#line 2884 "y.tab.cpp"
    break;

  case 128:
#line 525 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprPlus		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2890 "y.tab.cpp"
    break;

  case 129:
#line 526 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprMinus	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2896 "y.tab.cpp"
    break;

  case 130:
#line 527 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprTimes	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2902 "y.tab.cpp"
    break;

  case 131:
#line 528 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprDiv		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2908 "y.tab.cpp"
    break;

  case 132:
#line 529 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprMod		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2914 "y.tab.cpp"
    break;

  case 133:
#line 530 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2920 "y.tab.cpp"
    break;

  case 134:
#line 531 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwXor	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2926 "y.tab.cpp"
    break;

  case 135:
#line 532 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2932 "y.tab.cpp"
    break;

  case 136:
#line 533 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprGT		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2938 "y.tab.cpp"
    break;

  case 137:
#line 534 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprLT		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2944 "y.tab.cpp"
    break;

  case 138:
#line 535 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprGE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2950 "y.tab.cpp"
    break;

  case 139:
#line 536 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprLE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2956 "y.tab.cpp"
    break;

  case 140:
#line 537 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprEQ		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2962 "y.tab.cpp"
    break;

  case 141:
#line 538 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprNE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2968 "y.tab.cpp"
    break;

  case 142:
#line 539 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2974 "y.tab.cpp"
    break;

  case 143:
#line 540 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprOr		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2980 "y.tab.cpp"
    break;

  case 144:
#line 541 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprLShift	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2986 "y.tab.cpp"
    break;

  case 145:
#line 542 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprRShift	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2992 "y.tab.cpp"
    break;

  case 146:
#line 543 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprVal) = new exprCount	((yyvsp[-1].pExprVal), nbrLines); }
#line 2998 "y.tab.cpp"
    break;

  case 147:
#line 544 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprVal) = new exprBitwNeg	((yyvsp[0].pExprVal), nbrLines); }
#line 3004 "y.tab.cpp"
    break;

  case 148:
#line 545 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { 	if((yyvsp[0].pExprVal)->getType() != astNode::E_EXPR_CONST) 
														(yyval.pExprVal) = new exprUMin((yyvsp[0].pExprVal), nbrLines);
													else {
														exprConst* tmp = dynamic_cast<exprConst*>((yyvsp[0].pExprVal));
														(yyval.pExprVal) = new exprConst(- tmp->getCstValue(), nbrLines);
														delete tmp;
													}
												}
#line 3017 "y.tab.cpp"
    break;

  case 149:
#line 553 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprVal) = new exprNeg	((yyvsp[0].pExprVal), nbrLines); }
#line 3023 "y.tab.cpp"
    break;

  case 150:
#line 554 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { (yyval.pExprVal) = new exprCond	((yyvsp[-5].pExprVal), (yyvsp[-3].pExprVal), (yyvsp[-1].pExprVal), nbrLines); }
#line 3029 "y.tab.cpp"
    break;

  case 151:
#line 555 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                        { auto run = new exprRun ((yyvsp[-4].sVal), (yyvsp[-2].pExprArgListVal), nbrLines);
												  (yyval.pExprVal) = run;
												  auto procSym = run->resolve(*globalSymTab); 
												  assert(procSym); free((yyvsp[-4].sVal)); 
												}
#line 3039 "y.tab.cpp"
    break;

  case 152:
#line 560 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprVal) = new exprLen	((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3045 "y.tab.cpp"
    break;

  case 153:
#line 561 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "The enabled keyword is not supported."; }
#line 3051 "y.tab.cpp"
    break;

  case 154:
#line 562 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "Construct not supported."; /* Unclear */ }
#line 3057 "y.tab.cpp"
    break;

  case 155:
#line 563 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { std::cout << "Sorted send and random receive are not supported."; }
#line 3063 "y.tab.cpp"
    break;

  case 156:
#line 564 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprVal) = new exprVar	((yyvsp[0].pExprVarRefVal), nbrLines); }
#line 3069 "y.tab.cpp"
    break;

  case 157:
#line 565 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { std::cout << "Embedded C code is not supported."; }
#line 3075 "y.tab.cpp"
    break;

  case 158:
#line 566 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprVal) = new exprConst((yyvsp[0].iVal), nbrLines); }
#line 3081 "y.tab.cpp"
    break;

  case 159:
#line 567 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprVal) = new exprTrue	(nbrLines); }
#line 3087 "y.tab.cpp"
    break;

  case 160:
#line 568 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprVal) = new exprFalse(nbrLines); }
#line 3093 "y.tab.cpp"
    break;

  case 161:
#line 569 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprVal) = new exprTimeout(nbrLines); }
#line 3099 "y.tab.cpp"
    break;

  case 162:
#line 570 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "The 'np_' variable is not supported."; }
#line 3105 "y.tab.cpp"
    break;

  case 163:
#line 571 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "The 'pc_value()' construct is not supported."; }
#line 3111 "y.tab.cpp"
    break;

  case 164:
#line 572 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 3117 "y.tab.cpp"
    break;

  case 165:
#line 573 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 3123 "y.tab.cpp"
    break;

  case 166:
#line 574 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 3129 "y.tab.cpp"
    break;

  case 167:
#line 575 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 3135 "y.tab.cpp"
    break;

  case 169:
#line 579 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { assert(false); std::cout << "The 'priority' construct is related to simulation and not supported."; }
#line 3141 "y.tab.cpp"
    break;

  case 170:
#line 582 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 3147 "y.tab.cpp"
    break;

  case 171:
#line 583 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 3153 "y.tab.cpp"
    break;

  case 173:
#line 587 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { assert(false); std::cout << "The 'provided' construct is currently not supported."; }
#line 3159 "y.tab.cpp"
    break;

  case 174:
#line 592 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 3165 "y.tab.cpp"
    break;

  case 175:
#line 593 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprPar	((yyvsp[-1].pExprVal), nbrLines); }
#line 3171 "y.tab.cpp"
    break;

  case 176:
#line 594 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3177 "y.tab.cpp"
    break;

  case 177:
#line 595 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3183 "y.tab.cpp"
    break;

  case 178:
#line 596 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3189 "y.tab.cpp"
    break;

  case 179:
#line 597 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3195 "y.tab.cpp"
    break;

  case 180:
#line 598 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3201 "y.tab.cpp"
    break;

  case 181:
#line 599 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3207 "y.tab.cpp"
    break;

  case 182:
#line 600 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprVal) = new exprSkip	(nbrLines); }
#line 3213 "y.tab.cpp"
    break;

  case 183:
#line 603 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { (yyval.pExprVal) = new exprFull	((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3219 "y.tab.cpp"
    break;

  case 184:
#line 604 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprVal) = new exprNFull((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3225 "y.tab.cpp"
    break;

  case 185:
#line 605 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprVal) = new exprEmpty((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3231 "y.tab.cpp"
    break;

  case 186:
#line 606 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprVal) = new exprNEmpty((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3237 "y.tab.cpp"
    break;

  case 187:
#line 610 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                { (yyval.pExprArgListVal) = nullptr; }
#line 3243 "y.tab.cpp"
    break;

  case 188:
#line 611 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3249 "y.tab.cpp"
    break;

  case 189:
#line 615 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprArgListVal) = nullptr; }
#line 3255 "y.tab.cpp"
    break;

  case 190:
#line 616 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3261 "y.tab.cpp"
    break;

  case 191:
#line 620 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3267 "y.tab.cpp"
    break;

  case 192:
#line 621 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { assert(false); }
#line 3273 "y.tab.cpp"
    break;

  case 193:
#line 624 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList(new exprArg((yyvsp[0].pExprVal), nbrLines), nbrLines); }
#line 3279 "y.tab.cpp"
    break;

  case 194:
#line 625 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList(new exprArg((yyvsp[-2].pExprVal), nbrLines), (yyvsp[0].pExprArgListVal), nbrLines); }
#line 3285 "y.tab.cpp"
    break;

  case 195:
#line 628 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprRArgVal) = new exprRArgVar((yyvsp[0].pExprVarRefVal), nbrLines); }
#line 3291 "y.tab.cpp"
    break;

  case 196:
#line 629 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprRArgVal) = new exprRArgEval((yyvsp[-1].pExprVal), nbrLines); }
#line 3297 "y.tab.cpp"
    break;

  case 197:
#line 630 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprRArgVal) = new exprRArgConst(new exprConst((yyvsp[0].iVal), nbrLines), nbrLines); }
#line 3303 "y.tab.cpp"
    break;

  case 198:
#line 631 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprRArgVal) = new exprRArgConst(new exprConst(-(yyvsp[0].iVal), nbrLines), nbrLines); }
#line 3309 "y.tab.cpp"
    break;

  case 199:
#line 635 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprRArgListVal) = new exprRArgList((yyvsp[0].pExprRArgVal), nbrLines); }
#line 3315 "y.tab.cpp"
    break;

  case 200:
#line 636 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprRArgListVal) = new exprRArgList((yyvsp[-2].pExprRArgVal), (yyvsp[0].pExprRArgListVal), nbrLines); }
#line 3321 "y.tab.cpp"
    break;

  case 201:
#line 637 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprRArgListVal) = new exprRArgList((yyvsp[-3].pExprRArgVal), (yyvsp[-1].pExprRArgListVal), nbrLines); }
#line 3327 "y.tab.cpp"
    break;

  case 202:
#line 638 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprRArgListVal) = (yyvsp[-1].pExprRArgListVal); }
#line 3333 "y.tab.cpp"
    break;

  case 203:
#line 641 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "REDUCE: NAME -> nlst\n"; cmtypeSymNode* sym = new cmtypeSymNode(nbrLines, mtypeDef, (yyvsp[0].sVal), mtypeId++); (*globalSymTab)->insert(sym); free((yyvsp[0].sVal)); }
#line 3339 "y.tab.cpp"
    break;

  case 204:
#line 642 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { std::cout << "REDUCE: nlst NAME -> NAME\n"; cmtypeSymNode* sym = new cmtypeSymNode(nbrLines, mtypeDef, (yyvsp[0].sVal), mtypeId++); (*globalSymTab)->insert(sym); free((yyvsp[0].sVal)); }
#line 3345 "y.tab.cpp"
    break;

  case 205:
#line 643 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { std::cout << "REDUCE: nlst , -> nlst\n"; }
#line 3351 "y.tab.cpp"
    break;


#line 3355 "y.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (globalSymTab, program, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (globalSymTab, program, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, globalSymTab, program);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, globalSymTab, program);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (globalSymTab, program, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, globalSymTab, program);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, globalSymTab, program);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 645 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"

