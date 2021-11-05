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
#line 1 "promela.y"


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
#include "ast.h"

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


#line 122 "y.tab.c"

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
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
#line 60 "promela.y"
 
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

#line 385 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (symTable** globalSymTab, stmnt** program);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



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
#define YYLAST   1369

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  114
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  199
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  399

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
       0,   141,   141,   141,   146,   149,   150,   153,   154,   155,
     156,   169,   170,   171,   172,   173,   179,   177,   198,   199,
     202,   203,   204,   205,   219,   218,   234,   237,   249,   263,
     264,   267,   270,   271,   274,   275,   276,   277,   280,   281,
     284,   287,   287,   292,   293,   296,   301,   302,   303,   304,
     312,   313,   314,   315,   318,   319,   325,   325,   326,   326,
     329,   330,   334,   335,   342,   343,   346,   347,   348,   351,
     354,   355,   359,   371,   374,   375,   376,   379,   382,   383,
     386,   387,   390,   391,   395,   396,   399,   400,   401,   402,
     403,   404,   405,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,   425,
     426,   429,   430,   433,   446,   447,   450,   451,   454,   455,
     458,   459,   460,   461,   462,   463,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   487,   488,   489,   490,   492,   493,   494,   495,
     496,   497,   498,   499,   500,   501,   502,   503,   504,   505,
     506,   507,   510,   511,   514,   515,   518,   519,   524,   525,
     526,   527,   528,   529,   530,   531,   532,   535,   536,   537,
     538,   542,   543,   547,   548,   552,   553,   556,   557,   560,
     561,   562,   563,   567,   568,   569,   570,   573,   574,   575
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
  "proc", "$@2", "proctype", "inst", "init", "$@3", "events", "utypedef",
  "mtypedef", "nm", "ns", "c_fcts", "cstate", "ccode", "cexpr", "body",
  "$@4", "sequence", "step", "vis", "asgn", "one_decl", "$@5", "$@6",
  "decl_lst", "decl", "var_list", "ivar", "ch_init", "basetype",
  "typ_list", "vardcl", "varref", "pfld", "cmpnd", "sfld", "stmnt",
  "Special", "Stmnt", "options", "option", "OS", "MS", "aname", "expr",
  "Opt_priority", "full_expr", "Opt_enabler", "Expr", "Probe", "args",
  "prargs", "margs", "arg", "rarg", "rargs", "nlst", YY_NULLPTR
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

#define YYPACT_NINF (-330)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-116)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -330,    15,   960,  -330,  -330,  -330,    17,    52,    78,    33,
    -330,   -17,  -330,  -330,  -330,    -3,  -330,  -330,   663,  -330,
    -330,    86,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,
      76,  -330,    91,   119,    32,  -330,  -330,    49,    61,  -330,
    -330,   103,  -330,  -330,  -330,   162,     5,  -330,   155,   182,
       3,   842,    87,   100,   530,   203,    -3,  -330,  -330,   102,
     207,   207,  -330,  -330,   156,   178,   113,  -330,   118,   -61,
    -330,  -330,  -330,   192,   121,   124,   125,  -330,  -330,   842,
     842,   842,   133,   126,   842,  -330,    71,   127,  -330,   981,
     137,  -330,  -330,  -330,   204,   204,   -41,   139,  -330,   785,
     141,   143,   241,  -330,  -330,   142,   144,   149,   152,   153,
     172,   785,   530,  -330,   222,  -330,  -330,   159,   235,  -330,
    -330,  1257,  -330,   111,  -330,  -330,  -330,   179,   278,   -40,
    -330,   176,   219,  -330,  -330,     3,  -330,   842,   842,   286,
     287,  -330,  -330,    99,     0,   842,   842,  -330,  -330,  -330,
     842,   286,   813,   191,   194,     0,  -330,   842,   842,   842,
     842,   842,   842,   842,   842,   842,   842,   842,   842,   842,
     842,   842,   842,   842,   842,   842,  -330,   530,   260,   204,
     263,   326,   842,  -330,   310,     2,  -330,   530,   530,     0,
       0,     0,     0,   871,   -45,   222,   -19,   213,   428,   785,
     842,   842,    64,   145,  -330,  -330,   632,   785,   785,   785,
     785,    23,  -330,    18,   320,   323,   207,   195,  -330,  1050,
    1081,  -330,  -330,   842,     0,   223,  1112,  1141,  1170,   127,
     842,  -330,    35,    35,  -330,   322,   525,   224,   406,   304,
     505,   505,   181,   181,   181,   181,   173,   173,    84,    84,
    -330,  -330,  -330,  -330,   222,  -330,  -330,  -330,   -34,  -330,
    -330,  -330,   227,   216,   229,   243,   222,   222,   244,   248,
     250,   251,  -330,   249,  -330,  -330,  -330,  -330,   946,  -330,
    -330,  -330,  -330,   253,    35,   356,    35,  -330,   -53,  -330,
      35,  -330,  -330,   424,   285,   525,  -330,   424,   285,   525,
    -330,  -330,   259,  -330,  -330,  -330,   258,  -330,  -330,   363,
    -330,  1275,  -330,   -32,   265,   261,  -330,  -330,  -330,  -330,
    -330,  1016,   266,   267,  -330,   632,   728,   842,   270,  -330,
    -330,   271,   309,  -330,  -330,  -330,  -330,  -330,   842,   842,
     295,  -330,   314,    35,    35,   336,   103,  -330,   315,   286,
     414,   103,   321,   842,  -330,  -330,   186,  -330,  -330,  -330,
    -330,  -330,   319,  1199,  -330,  -330,   324,  -330,  -330,   374,
     403,  -330,  -330,  -330,   842,  1228,   -59,  -330,  -330,  -330,
     335,    -3,   332,   345,  -330,   785,  -330,   205,   103,   346,
    -330,  -330,   344,   348,  -330,  -330,   205,  -330,  -330
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,    20,     1,    38,    39,     0,     0,     0,     0,
      15,    21,    51,    52,    53,     0,    24,     3,    20,     5,
       7,     0,     8,     9,    11,    12,    14,    13,    33,    32,
       0,    10,     0,     0,     0,    29,    30,     0,     0,    41,
      26,   162,     6,    18,    19,     0,    54,    58,    34,    35,
      50,   181,     0,     0,    50,     0,     0,    16,    55,     0,
       0,     0,    36,    37,     0,    60,     0,   152,    78,     0,
     153,   154,    40,     0,     0,     0,     0,   155,   156,     0,
       0,     0,     0,     0,     0,   151,   150,    82,    77,   187,
       0,   182,    22,    23,     0,     0,    78,     0,   176,     0,
       0,     0,     0,    90,   106,     0,     0,     0,     0,     0,
       0,     0,    50,   100,   114,    43,    45,   150,    48,    84,
      85,   164,   105,   165,   168,   163,    25,     0,     0,    74,
      57,    64,    66,    59,    56,    50,    27,     0,     0,     0,
       0,   118,   119,     0,     0,     0,     0,   142,   141,   140,
       0,     0,     0,     0,     0,     0,    80,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    31,    50,     0,   111,
       0,    50,   181,    99,     0,     0,    91,    50,    50,     0,
       0,     0,     0,     0,     0,   114,   116,     0,    50,     0,
       0,     0,     0,     0,    94,    95,     0,     0,     0,     0,
       0,    50,   197,     0,     0,     0,     0,     0,    61,     0,
       0,   161,   160,   181,     0,     0,     0,     0,     0,    82,
       0,   120,     0,     0,    83,   136,   135,   128,   127,   126,
     133,   134,   129,   130,   131,   132,   137,   138,   121,   122,
     123,   124,   125,   188,   114,    88,   112,    89,    78,    47,
      46,    92,     0,   183,     0,     0,   114,   114,     0,     0,
       0,     0,   169,     0,    42,   117,    44,    93,   187,    87,
     185,   104,   191,     0,     0,     0,     0,   189,   193,    86,
       0,   101,    49,   136,   175,   135,   174,   173,   172,   171,
     170,    63,     0,   198,    28,   199,     0,    75,    65,     0,
      68,    67,    79,     0,     0,     0,   146,   147,   157,   139,
      81,     0,     0,     0,   113,     0,     0,     0,     0,    98,
      97,     0,     0,   177,   179,   178,   180,   109,     0,     0,
       0,   192,     0,     0,     0,     0,   162,    76,     0,     0,
       0,   162,     0,     0,   148,   149,   150,   110,   184,    96,
     107,   108,     0,     0,   102,   196,     0,   194,   103,   166,
       0,   159,   158,   144,   181,     0,     0,   186,   190,   195,
       0,     0,     0,     0,   143,     0,    17,     0,   162,     0,
      70,    71,    72,     0,   145,   167,     0,    69,    73
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -330,  -330,  -330,  -330,  -330,   440,  -330,  -330,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,    21,
    -330,   -56,  -330,   -94,   262,    39,  -330,     6,  -330,  -330,
    -119,  -330,   -55,  -330,  -330,  -330,    63,  -330,    -6,  -137,
     306,   237,  -171,  -330,   146,   -82,  -330,  -168,  -330,  -330,
     -50,  -329,   -95,  -330,   -65,  -330,  -179,  -330,   269,  -164,
    -330,  -153,  -330
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    17,    18,    19,    20,   127,    45,    21,
      22,    41,    23,    24,    25,    37,    26,    27,    28,   113,
      85,    40,    54,   114,   115,    64,    59,   116,    60,    61,
      66,   302,   130,   131,   310,   392,   393,   132,    86,    87,
      88,   156,   118,   119,   120,   178,   179,   197,   198,   143,
     121,    56,   122,   381,   123,   124,    90,   328,   279,    91,
     288,   289,   213
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     126,    89,   221,   262,   183,   264,   133,    68,    31,    68,
     261,   253,   -56,   180,   229,     3,   218,   369,   195,  -115,
    -115,  -115,   373,    29,    31,   303,   284,   273,    32,   147,
     148,   149,   209,   210,   152,   292,   280,   280,   282,    29,
      35,    30,    68,    36,   314,   138,   194,   232,   117,   139,
     291,   343,   140,    12,    13,    14,    65,    30,   344,   394,
     272,   193,   283,    33,    52,   137,   214,   282,    53,   181,
     215,    68,   137,    12,    13,    14,   325,    58,   349,   322,
     323,   350,    46,   254,    47,    34,   324,   219,   220,    38,
    -115,   283,   301,   266,   267,   226,   227,   256,   331,   332,
     228,    83,    48,    83,   277,    39,   117,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,    89,   285,   304,   -62,   305,
      49,   340,    89,   342,    43,    44,    83,   345,   225,   286,
      50,    65,   294,   296,   298,   300,   153,   154,   282,   284,
     278,   278,    68,    51,   261,   285,    55,   293,   295,   297,
     299,   308,   134,   358,    47,    83,    62,   311,   286,    57,
     232,   117,   283,    89,   362,   117,   172,   173,   174,   265,
     321,   117,   117,   268,   269,   270,   271,   260,   209,   210,
     366,   367,   117,    63,    92,   383,   287,   287,    67,   141,
     117,   142,    68,   223,    69,   224,   125,    93,    70,    71,
     128,   390,   371,   391,   129,   135,    72,    65,   315,    73,
      74,    75,   136,    76,   137,   144,   287,   287,   145,   146,
     290,   199,   200,   201,   202,   203,   285,   150,   151,   155,
      77,    78,   176,   182,   177,   184,    83,   185,   186,   286,
     187,   233,   188,   189,   204,   205,   190,   191,   199,   196,
     201,   376,   203,   170,   171,   172,   173,   174,    79,   168,
     169,   170,   171,   172,   173,   174,   192,    89,   287,   206,
     287,   204,   205,   211,   287,   212,    80,   216,    89,   363,
     389,   217,    81,    68,   222,    82,    83,   232,   255,    84,
     233,   309,   257,   375,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   117,
     356,   263,   274,   306,    89,   386,   307,   327,   316,    67,
      94,    95,   326,   258,   329,    69,    97,   287,   287,    70,
      71,    98,    99,   100,   101,     4,     5,    72,   330,   333,
      73,    74,    75,   334,    76,   335,   336,   339,   337,   341,
     102,   103,   104,   210,   346,   347,   348,   105,   352,   106,
     351,    77,    78,   354,   355,   359,    12,    13,    14,   364,
     360,   107,   108,   109,   110,   259,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,    79,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,    80,   361,   365,
     368,   372,   370,    81,   377,   374,    82,    83,   380,   379,
     111,    67,    94,    95,   112,    96,   382,    69,    97,   385,
     387,    70,    71,    98,    99,   100,   101,     4,     5,    72,
     388,   395,    73,    74,    75,   396,    76,   397,    42,   398,
     276,   234,   102,   103,   104,   275,   320,     0,     0,   105,
     281,   106,   357,    77,    78,     0,     0,     0,    12,    13,
      14,     0,     0,   107,   108,   109,   110,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,    79,   208,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,    80,
       0,     0,     0,     0,     0,    81,     0,     0,    82,    83,
       0,     0,   111,    67,    94,    95,   112,    96,     0,    69,
      97,     0,     0,    70,    71,    98,    99,   100,   101,     4,
       5,    72,     0,     0,    73,    74,    75,     0,    76,     0,
       0,     0,     0,     0,   102,   103,   104,     0,     0,     0,
       0,   105,     0,   106,     0,    77,    78,     0,     0,     0,
      12,    13,    14,     0,     0,   107,   108,   109,   110,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
       0,     0,     0,    79,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
       0,    80,     0,     0,     0,     0,     0,    81,     0,     0,
      82,    83,     0,     0,   111,    67,    94,    95,   112,   258,
       0,    69,    97,     0,     0,    70,    71,    98,    99,   100,
     101,     4,     5,    72,     0,     0,    73,    74,    75,     0,
      76,     0,     0,    -4,     0,     0,   102,   103,   104,   -50,
       0,   -50,     0,   105,     0,   106,     0,    77,    78,     0,
       0,     0,     4,     5,     0,     6,     7,   107,   108,   109,
     110,     0,     8,     0,     9,     0,     0,     0,     0,     0,
      10,     0,     0,     0,     0,    79,     0,     0,     0,     0,
      11,     0,     0,    12,    13,    14,     0,     0,     0,     0,
       0,     0,     0,    80,    15,    16,     0,     0,     0,    81,
       0,    67,    82,    83,     0,    68,   111,    69,    97,     0,
     112,    70,    71,    98,    99,   100,   101,     4,     5,    72,
       0,     0,    73,    74,    75,     0,    76,     0,     0,     0,
       0,     0,     0,     0,   104,     0,     0,     0,     0,   105,
       0,   106,     0,    77,    78,     0,     0,     0,     0,     0,
       0,     0,     0,   107,   108,   109,   110,     0,    67,     0,
       0,     0,    68,     0,    69,     0,     0,     0,    70,    71,
      98,    79,     0,     0,     0,     0,    72,     0,     0,    73,
      74,    75,     0,    76,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,    81,     0,     0,    82,    83,
      77,    78,   111,     0,     0,     0,   112,     0,     0,     0,
     107,   108,   109,   110,     0,    67,     0,     0,     0,    68,
     230,    69,     0,     0,     0,    70,    71,     0,    79,     0,
       0,     0,     0,    72,     0,     0,    73,    74,    75,     0,
      76,     0,     0,     0,     0,     0,    80,     0,     0,     0,
       0,     0,    81,     0,     0,    82,    83,    77,    78,   111,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   230,     0,
       0,     0,     0,     0,     0,    79,     0,     0,   231,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    80,     0,     0,     0,     0,     0,    81,
       0,     0,    82,    83,     0,     0,    84,     0,   207,   208,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   -50,     0,   -50,     0,
       0,     0,     0,     0,     0,     0,   231,     0,     0,     4,
       5,     0,     6,     7,     0,     0,     0,     0,     0,     8,
       0,     9,     0,     0,     0,     0,     0,    10,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    11,     0,     0,
      12,    13,    14,     0,     0,     0,     0,     0,     0,     0,
       0,    15,    16,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     338,     0,     0,     0,     0,     0,     0,   175,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   175,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   353,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   312,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   313,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   317,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   318,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   319,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   378,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   384,   207,   208,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174
};

static const yytype_int16 yycheck[] =
{
      56,    51,   139,   182,    99,     3,    61,     7,     2,     7,
     181,   175,     7,    95,   151,     0,   135,   346,   112,    38,
      39,    40,   351,     2,    18,     7,    85,   195,    11,    79,
      80,    81,    77,    78,    84,   206,   200,   201,     3,    18,
       7,     2,     7,    10,   223,   106,   111,   106,    54,   110,
     203,   104,   113,    50,    51,    52,    50,    18,   111,   388,
     105,   111,    27,    11,     3,   106,   106,     3,     7,   110,
     110,     7,   106,    50,    51,    52,   110,    72,   110,   232,
     233,   113,     6,   177,     8,     7,   254,   137,   138,   106,
     109,    27,   211,   187,   188,   145,   146,   179,   266,   267,
     150,   101,    11,   101,   199,   108,   112,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,    91,   109,   105,   111,
      11,   284,   182,   286,    48,    49,   101,   290,   144,   104,
     108,   135,   207,   208,   209,   210,    75,    76,     3,    85,
     200,   201,     7,   104,   325,    91,    53,   207,   208,   209,
     210,   216,     6,   327,     8,   101,    11,   217,   104,     7,
     106,   177,    27,   223,   338,   181,    92,    93,    94,   185,
     230,   187,   188,   189,   190,   191,   192,   181,    77,    78,
     343,   344,   198,    11,   107,   374,   202,   203,     3,     7,
     206,     9,     7,   104,     9,   106,     3,   107,    13,    14,
     108,     6,   349,     8,     7,    37,    21,   211,   224,    24,
      25,    26,   109,    28,   106,   104,   232,   233,   104,   104,
      85,    72,    73,    74,    75,    76,    91,   104,   112,   112,
      45,    46,   105,   104,    40,   104,   101,   104,     7,   104,
     108,   106,   108,   104,    95,    96,   104,   104,    72,    37,
      74,    75,    76,    90,    91,    92,    93,    94,    73,    88,
      89,    90,    91,    92,    93,    94,   104,   327,   284,    44,
     286,    95,    96,   104,   290,     7,    91,   111,   338,   339,
     385,    72,    97,     7,     7,   100,   101,   106,    38,   104,
     106,   106,    39,   353,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,   325,
     326,    11,   109,     3,   374,   381,     3,   111,   105,     3,
       4,     5,   105,     7,   105,     9,    10,   343,   344,    13,
      14,    15,    16,    17,    18,    19,    20,    21,   105,   105,
      24,    25,    26,   105,    28,   105,   105,   104,   109,     3,
      34,    35,    36,    78,   105,   107,     3,    41,   107,    43,
     105,    45,    46,   107,   107,   105,    50,    51,    52,    84,
     109,    55,    56,    57,    58,    59,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    73,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    91,   109,   105,
      84,     7,   107,    97,   105,   104,   100,   101,    54,   105,
     104,     3,     4,     5,   108,     7,    33,     9,    10,   104,
     108,    13,    14,    15,    16,    17,    18,    19,    20,    21,
     105,   105,    24,    25,    26,   111,    28,   109,    18,   396,
     198,   155,    34,    35,    36,    37,   229,    -1,    -1,    41,
     201,    43,   326,    45,    46,    -1,    -1,    -1,    50,    51,
      52,    -1,    -1,    55,    56,    57,    58,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    73,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    91,
      -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,   100,   101,
      -1,    -1,   104,     3,     4,     5,   108,     7,    -1,     9,
      10,    -1,    -1,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    24,    25,    26,    -1,    28,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,
      -1,    41,    -1,    43,    -1,    45,    46,    -1,    -1,    -1,
      50,    51,    52,    -1,    -1,    55,    56,    57,    58,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      -1,    -1,    -1,    73,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      -1,    91,    -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,
     100,   101,    -1,    -1,   104,     3,     4,     5,   108,     7,
      -1,     9,    10,    -1,    -1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    24,    25,    26,    -1,
      28,    -1,    -1,     0,    -1,    -1,    34,    35,    36,     6,
      -1,     8,    -1,    41,    -1,    43,    -1,    45,    46,    -1,
      -1,    -1,    19,    20,    -1,    22,    23,    55,    56,    57,
      58,    -1,    29,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      37,    -1,    -1,    -1,    -1,    73,    -1,    -1,    -1,    -1,
      47,    -1,    -1,    50,    51,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    61,    62,    -1,    -1,    -1,    97,
      -1,     3,   100,   101,    -1,     7,   104,     9,    10,    -1,
     108,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    24,    25,    26,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    41,
      -1,    43,    -1,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    56,    57,    58,    -1,     3,    -1,
      -1,    -1,     7,    -1,     9,    -1,    -1,    -1,    13,    14,
      15,    73,    -1,    -1,    -1,    -1,    21,    -1,    -1,    24,
      25,    26,    -1,    28,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,   100,   101,
      45,    46,   104,    -1,    -1,    -1,   108,    -1,    -1,    -1,
      55,    56,    57,    58,    -1,     3,    -1,    -1,    -1,     7,
      37,     9,    -1,    -1,    -1,    13,    14,    -1,    73,    -1,
      -1,    -1,    -1,    21,    -1,    -1,    24,    25,    26,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,
      -1,    -1,    97,    -1,    -1,   100,   101,    45,    46,   104,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    -1,    -1,   105,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,    97,
      -1,    -1,   100,   101,    -1,    -1,   104,    -1,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,     6,    -1,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,    19,
      20,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,
      50,    51,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    62,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,    -1,    -1,    -1,    -1,    -1,    -1,   111,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   111,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   110,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,    77,
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
      91,    92,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   105,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   105,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   115,   116,     0,    19,    20,    22,    23,    29,    31,
      37,    47,    50,    51,    52,    61,    62,   117,   118,   119,
     120,   123,   124,   126,   127,   128,   130,   131,   132,   133,
     139,   141,    11,    11,     7,     7,    10,   129,   106,   108,
     135,   125,   119,    48,    49,   122,     6,     8,    11,    11,
     108,   104,     3,     7,   136,    53,   165,     7,    72,   140,
     142,   143,    11,    11,   139,   141,   144,     3,     7,     9,
      13,    14,    21,    24,    25,    26,    28,    45,    46,    73,
      91,    97,   100,   101,   104,   134,   152,   153,   154,   164,
     170,   173,   107,   107,     4,     5,     7,    10,    15,    16,
      17,    18,    34,    35,    36,    41,    43,    55,    56,    57,
      58,   104,   108,   133,   137,   138,   141,   152,   156,   157,
     158,   164,   166,   168,   169,     3,   135,   121,   108,     7,
     146,   147,   151,   146,     6,    37,   109,   106,   106,   110,
     113,     7,     9,   163,   104,   104,   104,   164,   164,   164,
     104,   112,   164,    75,    76,   112,   155,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,   111,   105,    40,   159,   160,
     159,   110,   104,   166,   104,   104,     7,   108,   108,   104,
     104,   104,   104,   164,   168,   137,    37,   161,   162,    72,
      73,    74,    75,    76,    95,    96,    44,    77,    78,    77,
      78,   104,     7,   176,   106,   110,   111,    72,   144,   164,
     164,   153,     7,   104,   106,   152,   164,   164,   164,   153,
      37,   105,   106,   106,   154,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   173,   137,    38,   159,    39,     7,    59,
     141,   156,   170,    11,     3,   152,   137,   137,   152,   152,
     152,   152,   105,   161,   109,    37,   138,   166,   164,   172,
     173,   172,     3,    27,    85,    91,   104,   152,   174,   175,
      85,   175,   156,   164,   168,   164,   168,   164,   168,   164,
     168,   144,   145,     7,   109,   111,     3,     3,   146,   106,
     148,   164,   107,   107,   170,   152,   105,   105,   105,   105,
     155,   164,   175,   175,   161,   110,   105,   111,   171,   105,
     105,   161,   161,   105,   105,   105,   105,   109,   104,   104,
     175,     3,   175,   104,   111,   175,   105,   107,     3,   110,
     113,   105,   107,   110,   107,   107,   152,   158,   173,   105,
     109,   109,   173,   164,    84,   105,   175,   175,    84,   165,
     107,   153,     7,   165,   104,   164,    75,   105,   105,   105,
      54,   167,    33,   170,   105,   104,   135,   108,   105,   166,
       6,     8,   149,   150,   165,   105,   111,   109,   150
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   114,   116,   115,   117,   118,   118,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   121,   120,   122,   122,
     123,   123,   123,   123,   125,   124,   126,   127,   128,   129,
     129,   130,   131,   131,   132,   132,   132,   132,   133,   133,
     134,   136,   135,   137,   137,   138,   138,   138,   138,   138,
     139,   139,   139,   139,   140,   140,   142,   141,   143,   141,
     144,   144,   145,   145,   146,   146,   147,   147,   147,   148,
     149,   149,   150,   150,   151,   151,   151,   152,   153,   153,
     154,   154,   155,   155,   156,   156,   157,   157,   157,   157,
     157,   157,   157,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   159,   159,   160,   161,   161,   162,   162,   163,   163,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   165,   165,   166,   166,   167,   167,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   169,   169,   169,
     169,   170,   170,   171,   171,   172,   172,   173,   173,   174,
     174,   174,   174,   175,   175,   175,   175,   176,   176,   176
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,    10,     1,     1,
       0,     1,     4,     4,     0,     4,     2,     5,     6,     1,
       1,     5,     1,     1,     3,     3,     4,     4,     1,     1,
       1,     0,     5,     1,     3,     1,     3,     3,     1,     3,
       0,     1,     1,     1,     0,     1,     0,     4,     0,     4,
       1,     3,     0,     1,     1,     3,     1,     3,     3,     7,
       1,     1,     1,     3,     1,     3,     4,     1,     1,     4,
       2,     4,     0,     2,     1,     1,     3,     3,     3,     3,
       1,     2,     3,     3,     2,     2,     5,     4,     4,     2,
       1,     3,     5,     5,     3,     1,     1,     5,     5,     4,
       5,     1,     2,     3,     0,     1,     1,     2,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     4,
       2,     2,     2,     7,     6,     9,     4,     4,     5,     5,
       1,     1,     1,     1,     1,     1,     1,     4,     6,     6,
       3,     3,     0,     2,     1,     1,     0,     4,     1,     3,
       3,     3,     3,     3,     3,     3,     1,     4,     4,     4,
       4,     0,     1,     0,     2,     1,     4,     1,     3,     1,
       4,     1,     2,     1,     3,     4,     3,     1,     2,     2
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
#line 141 "promela.y"
                  { *globalSymTab = new symTable("global"); symTable::addPredefinedSym(*globalSymTab); currentSymTab = *globalSymTab; }
#line 2053 "y.tab.c"
    break;

  case 4:
#line 146 "promela.y"
                                                                                { std::cout<< "REDUCE: units -> program\n"; }
#line 2059 "y.tab.c"
    break;

  case 5:
#line 149 "promela.y"
                                                                                { std::cout<< "REDUCE: unit -> units\n"; }
#line 2065 "y.tab.c"
    break;

  case 6:
#line 150 "promela.y"
                                                                                { std::cout<< "REDUCE: units unit -> units\n"; }
#line 2071 "y.tab.c"
    break;

  case 7:
#line 153 "promela.y"
                                                        { std::cout<< "REDUCE: proc -> unit\n"; *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2077 "y.tab.c"
    break;

  case 8:
#line 154 "promela.y"
                                                                { std::cout<< "REDUCE: init -> unit\n"; *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2083 "y.tab.c"
    break;

  case 9:
#line 155 "promela.y"
                                                                { std::cout << "The 'events' construct is currently not supported."; }
#line 2089 "y.tab.c"
    break;

  case 10:
#line 156 "promela.y"
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
#line 2107 "y.tab.c"
    break;

  case 11:
#line 169 "promela.y"
                                                                        { std::cout << "REDUCE: utype -> unit\n"; *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2113 "y.tab.c"
    break;

  case 12:
#line 170 "promela.y"
                                                                                                { std::cout << "REDUCE: mtype -> unit\n"; *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2119 "y.tab.c"
    break;

  case 13:
#line 171 "promela.y"
                                                                { std::cout << "Embedded C code is not supported."; }
#line 2125 "y.tab.c"
    break;

  case 14:
#line 172 "promela.y"
                                                                { std::cout << "The 'named sequence' construct is currently not supported."; }
#line 2131 "y.tab.c"
    break;

  case 16:
#line 179 "promela.y"
                  { nameSpace = (yyvsp[0].sVal); }
#line 2137 "y.tab.c"
    break;

  case 17:
#line 183 "promela.y"
                                                                                        {	
		  											std::cout<< "REDUCE: inst proctype NAME ( decl ) prio ena body -> proc\n";
		  											procSymNode* proc = new procSymNode((yyvsp[-7].sVal), (yyvsp[-9].pConstExprVal), declSyms, (yyvsp[0].pStmntVal), nbrLines);
		  											symTable* local = proc->getBlock()->getLocalSymTab();
		  											if(local)
		  												for(auto s : declSyms)
		  													local->insert(s);
		  											declSyms.clear();
		  											(yyval.pStmntVal) = new procDecl(proc, nbrLines);
		  											(*globalSymTab)->insert(proc);
		  											nameSpace = "global";
		  											free((yyvsp[-7].sVal));
		  										}
#line 2155 "y.tab.c"
    break;

  case 18:
#line 198 "promela.y"
                                                                                { std::cout << "REDUCE: -> PROCTYPE proctype\n"; }
#line 2161 "y.tab.c"
    break;

  case 19:
#line 199 "promela.y"
                                                                                { std::cout << "Deterministic proctypes are not supported (only useful for simulation)."; }
#line 2167 "y.tab.c"
    break;

  case 20:
#line 202 "promela.y"
                                                                        { std::cout << "REDUCE: void -> inst\n"; (yyval.pConstExprVal) = new exprConst(0, nbrLines); }
#line 2173 "y.tab.c"
    break;

  case 21:
#line 203 "promela.y"
                                                                                        { std::cout << "REDUCE: ACTIVE -> inst\n"; (yyval.pConstExprVal) = new exprConst(1, nbrLines); }
#line 2179 "y.tab.c"
    break;

  case 22:
#line 204 "promela.y"
                                                                        { std::cout << "REDUCE: ACTIVE [ CONST ] -> inst \n"; (yyval.pConstExprVal) = new exprConst((yyvsp[-1].iVal), nbrLines); }
#line 2185 "y.tab.c"
    break;

  case 23:
#line 205 "promela.y"
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
#line 2201 "y.tab.c"
    break;

  case 24:
#line 219 "promela.y"
                { nameSpace = "init"; }
#line 2207 "y.tab.c"
    break;

  case 25:
#line 221 "promela.y"
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
#line 2223 "y.tab.c"
    break;

  case 26:
#line 234 "promela.y"
                                                                        { std::cout << "Event sequences (traces) are not supported."; }
#line 2229 "y.tab.c"
    break;

  case 27:
#line 237 "promela.y"
                                                        {	
													std::cout << "REDUCE: TYPEDEF NAME '{' decl_lst '}' -> utype\n";
													tdefSymNode* tdef = new tdefSymNode((yyvsp[-3].sVal), declSyms, nbrLines);
													(yyval.pStmntVal) = new tdefDecl(tdef, nbrLines);
													(*globalSymTab)->insert(tdef);
													for(auto declSym : declSyms)
														(*globalSymTab)->remove(declSym->getName());
													declSyms.clear();
													free((yyvsp[-3].sVal));  
												}
#line 2244 "y.tab.c"
    break;

  case 28:
#line 249 "promela.y"
                                                        {	
													std::cout << "REDUCE: vis TYPE asgn { nlst } -> one_decl\n";
													if((yyvsp[-4].iType) != symbol::T_MTYPE) {
														std::cout <<  "This syntax only works for MTYPEs definition.";
														exit(1);
													}
													mtypedefSymNode* mtypeDef = new mtypedefSymNode(mtypes, nbrLines);
													mtypes.clear();
													(*globalSymTab)->insert(mtypeDef);
													(yyval.pStmntVal) = new mtypeDecl(mtypeDef, nbrLines);
													// The mtype values are added in the nlst rule.
												}
#line 2261 "y.tab.c"
    break;

  case 41:
#line 287 "promela.y"
                                                                                { savedSymTab = currentSymTab; currentSymTab = currentSymTab->createSubTable(nameSpace); nameSpace = ""; }
#line 2267 "y.tab.c"
    break;

  case 42:
#line 289 "promela.y"
                                                                                        { std::cout << "REDUCE: '{' sequence OS '}' -> body\n"; (yyval.pStmntVal) = (yyvsp[-2].pStmntVal); (yyval.pStmntVal)->setLocalSymTab(currentSymTab); currentSymTab->setBlock((yyvsp[-2].pStmntVal)); currentSymTab = savedSymTab; }
#line 2273 "y.tab.c"
    break;

  case 43:
#line 292 "promela.y"
                                                                                { std::cout << "REDUCE: step -> sequence\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal);  }
#line 2279 "y.tab.c"
    break;

  case 44:
#line 293 "promela.y"
                                                                                { std::cout << "REDUCE: sequence MS step -> sequence\n"; (yyval.pStmntVal) = stmnt::merge((yyvsp[-2].pStmntVal), (yyvsp[0].pStmntVal)); }
#line 2285 "y.tab.c"
    break;

  case 45:
#line 296 "promela.y"
                                                                                { 
													assert(declSyms.front()->getType() != symbol::T_MTYPE_DEF && declSyms.front()->getType() != symbol::T_CHAN); 
												 	(yyval.pStmntVal) = new varDecl(static_cast<std::list<varSymNode*>>(declSyms), nbrLines);
												 	declSyms.clear();
												}
#line 2295 "y.tab.c"
    break;

  case 46:
#line 301 "promela.y"
                                                                                { std::cout << "Declarations with labels are not suported."; }
#line 2301 "y.tab.c"
    break;

  case 47:
#line 302 "promela.y"
                                                                                { std::cout << "Channel assertions are currently not supported."; }
#line 2307 "y.tab.c"
    break;

  case 48:
#line 303 "promela.y"
                                                                                        { std::cout << "REDUCE: stmnt -> step\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2313 "y.tab.c"
    break;

  case 49:
#line 304 "promela.y"
                                                                        { std::cout << "Unless statements are currently not supported."; }
#line 2319 "y.tab.c"
    break;

  case 51:
#line 313 "promela.y"
                                                                                        { std::cout << "The 'hidden' keyword is not supported."; }
#line 2325 "y.tab.c"
    break;

  case 52:
#line 314 "promela.y"
                                                                                        { std::cout << "The 'show' keyword is not supported."; }
#line 2331 "y.tab.c"
    break;

  case 53:
#line 315 "promela.y"
                                                                                        { std::cout << "The 'local' keyword is not supported."; }
#line 2337 "y.tab.c"
    break;

  case 56:
#line 325 "promela.y"
                   { declType = (yyvsp[0].iType); }
#line 2343 "y.tab.c"
    break;

  case 57:
#line 325 "promela.y"
                                                { std::cout << "REDUCE: vis TYPE var_list -> one_decl\n"; }
#line 2349 "y.tab.c"
    break;

  case 58:
#line 326 "promela.y"
                            { declType = symbol::T_UTYPE; typeDef = *globalSymTab? static_cast<tdefSymNode*>((*globalSymTab)->lookup((yyvsp[0].sVal))) : nullptr; assert(typeDef); }
#line 2355 "y.tab.c"
    break;

  case 59:
#line 326 "promela.y"
                                                                                                                                                                                                        { std::cout << "REDUCE: vis UNAME var_list -> one_decl\n"; free((yyvsp[-2].sVal)); }
#line 2361 "y.tab.c"
    break;

  case 60:
#line 329 "promela.y"
                                                                                { std::cout << "REDUCE: one_decl -> decl_list\n"; }
#line 2367 "y.tab.c"
    break;

  case 61:
#line 330 "promela.y"
                                                                        { std::cout << "REDUCE: one_decl SEMI decl_list -> decl_lst\n"; }
#line 2373 "y.tab.c"
    break;

  case 62:
#line 334 "promela.y"
                                                                        { std::cout << "REDUCE: void -> decl\n"; }
#line 2379 "y.tab.c"
    break;

  case 63:
#line 335 "promela.y"
                                                                                        { std::cout << "REDUCE: decl_list -> decl\n"; }
#line 2385 "y.tab.c"
    break;

  case 64:
#line 342 "promela.y"
                                                                                { std::cout << "REDUCE: ivar -> var_list\n"; currentSymTab->insert((yyvsp[0].pVarSymVal)); declSyms.push_front((yyvsp[0].pVarSymVal)); }
#line 2391 "y.tab.c"
    break;

  case 65:
#line 343 "promela.y"
                                                                                { std::cout << "REDUCE: ivar , var_list -> var_list\n"; currentSymTab->insert((yyvsp[-2].pVarSymVal)); declSyms.push_front((yyvsp[-2].pVarSymVal)); }
#line 2397 "y.tab.c"
    break;

  case 66:
#line 346 "promela.y"
                                                                                { std::cout << "REDUCE: var_decl -> ivar\n"; (yyval.pVarSymVal) = varSymNode::createSymbol(declType, nbrLines, (yyvsp[0].pDataVal).sVal, (yyvsp[0].pDataVal).iVal); if(declType == symbol::T_UTYPE) { assert(typeDef); static_cast<utypeSymNode*>((yyval.pVarSymVal))->setUType(typeDef); } }
#line 2403 "y.tab.c"
    break;

  case 67:
#line 347 "promela.y"
                                                                                { std::cout << "REDUCE: var_decl ASGN expr -> ivar\n"; (yyval.pVarSymVal) = varSymNode::createSymbol(declType, nbrLines, (yyvsp[-2].pDataVal).sVal, (yyvsp[-2].pDataVal).iVal, (yyvsp[0].pExprVal)); if(declType == symbol::T_UTYPE) { assert(typeDef); static_cast<utypeSymNode*>((yyval.pVarSymVal))->setUType(typeDef); } }
#line 2409 "y.tab.c"
    break;

  case 68:
#line 348 "promela.y"
                                                                        { std::cout << "REDUCE: var_decl ASGN ch_init -> ivar\n"; (yyval.pVarSymVal) = new chanSymNode(nbrLines, (yyvsp[-2].pDataVal).sVal, (yyvsp[-2].pDataVal).iVal, (yyvsp[0].pDataVal).iVal, typeLst); typeLst.clear(); }
#line 2415 "y.tab.c"
    break;

  case 69:
#line 351 "promela.y"
                                                        { std::cout << "REDUCE: [ CONST ] OF { typ_list } -> ch_init\n"; (yyval.pDataVal).iVal = (yyvsp[-5].iVal); }
#line 2421 "y.tab.c"
    break;

  case 70:
#line 354 "promela.y"
                                                                                { (yyval.pDataVal).sVal = nullptr; (yyval.pDataVal).iType = (yyvsp[0].iType); }
#line 2427 "y.tab.c"
    break;

  case 71:
#line 355 "promela.y"
                                                                                        { (yyval.pDataVal).sVal = (yyvsp[0].sVal); (yyval.pDataVal).iType = symbol::T_UTYPE; }
#line 2433 "y.tab.c"
    break;

  case 72:
#line 359 "promela.y"
                                                                                {	std::cout << "REDUCE: basetype -> typ_list\n";
													varSymNode* typ = nullptr;
													if((yyvsp[0].pDataVal).iType != symbol::T_UTYPE && (yyvsp[0].pDataVal).iType != symbol::T_NA) {
														typ = varSymNode::createSymbol((yyvsp[0].pDataVal).iType, nbrLines);
													} else {
														tdefSymNode* pType = *globalSymTab ? static_cast<tdefSymNode*>((*globalSymTab)->lookup((yyvsp[0].pDataVal).sVal)) : nullptr;
														typ = new utypeSymNode(pType, nbrLines);
														if(typ == nullptr) 
															std::cout << "The type "<<(yyvsp[0].pDataVal).sVal<<" was not declared in a typedef.\n";
													}
													typeLst.push_front(typ);
												}
#line 2450 "y.tab.c"
    break;

  case 73:
#line 371 "promela.y"
                                                                        {	std::cout << "REDUCE: basetype , typ_list -> typ_list\n"; }
#line 2456 "y.tab.c"
    break;

  case 74:
#line 374 "promela.y"
                                                                                { std::cout << "REDUCE: NAME -> vardcl\n"; (yyval.pDataVal).sVal = (yyvsp[0].sVal); (yyval.pDataVal).iVal = 1; }
#line 2462 "y.tab.c"
    break;

  case 75:
#line 375 "promela.y"
                                                                                { std::cout << "The 'unsigned' data type is not supported."; }
#line 2468 "y.tab.c"
    break;

  case 76:
#line 376 "promela.y"
                                                                        { std::cout << "REDUCE: NAME [ CONST ] -> vardcl\n"; (yyval.pDataVal).sVal = (yyvsp[-3].sVal); (yyval.pDataVal).iVal = (yyvsp[-1].iVal); }
#line 2474 "y.tab.c"
    break;

  case 77:
#line 379 "promela.y"
                                                                                { std::cout << "REDUCE: cmpnd -> varref\n"; (yyval.pExprVarRefVal) = (yyvsp[0].pExprVarRefVal); (yyval.pExprVarRefVal)->resolve(currentSymTab); }
#line 2480 "y.tab.c"
    break;

  case 78:
#line 382 "promela.y"
                                                                                { std::cout << "REDUCE: NAME -> pfld\n"; (yyval.pExprVarRefNameVal) = new exprVarRefName((yyvsp[0].sVal), nbrLines); free((yyvsp[0].sVal)); }
#line 2486 "y.tab.c"
    break;

  case 79:
#line 383 "promela.y"
                                                                                { std::cout << "REDUCE: NAME [ expr ] -> pfld\n"; (yyval.pExprVarRefNameVal) = new exprVarRefName((yyvsp[-3].sVal), (yyvsp[-1].pExprVal), nbrLines); free((yyvsp[-3].sVal)); }
#line 2492 "y.tab.c"
    break;

  case 80:
#line 386 "promela.y"
                                                                                { std::cout << "REDUCE: pfld sfld -> cmpnd\n"; (yyval.pExprVarRefVal) = new exprVarRef(nbrLines, (yyvsp[-1].pExprVarRefNameVal), (yyvsp[0].pExprVarRefVal)); }
#line 2498 "y.tab.c"
    break;

  case 81:
#line 387 "promela.y"
                                                                        { std::cout << "REDUCE: CONTEX . pfld sfld -> cmpnd\n"; (yyval.pExprVarRefVal) = new exprVarRef(nbrLines, (yyvsp[-1].pExprVarRefNameVal), (yyvsp[0].pExprVarRefVal)); }
#line 2504 "y.tab.c"
    break;

  case 82:
#line 390 "promela.y"
                                                                                        { std::cout << "REDUCE: void -> sfld\n"; (yyval.pExprVarRefVal) = nullptr; }
#line 2510 "y.tab.c"
    break;

  case 83:
#line 391 "promela.y"
                                                                        { std::cout << "REDUCE: . cmpnd -> sfld\n"; (yyval.pExprVarRefVal) = (yyvsp[0].pExprVarRefVal);   }
#line 2516 "y.tab.c"
    break;

  case 84:
#line 395 "promela.y"
                                                                                { std::cout << "REDUCE: special -> stmnt\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2522 "y.tab.c"
    break;

  case 85:
#line 396 "promela.y"
                                                                                        { std::cout << "REDUCE: Stmnt -> stmnt\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2528 "y.tab.c"
    break;

  case 86:
#line 399 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntChanRecv((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprArgListVal), nbrLines); }
#line 2534 "y.tab.c"
    break;

  case 87:
#line 400 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntChanSnd((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprArgListVal), nbrLines); }
#line 2540 "y.tab.c"
    break;

  case 88:
#line 401 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntIf((yyvsp[-1].pStmntOptVal), (yyvsp[-2].iVal)); }
#line 2546 "y.tab.c"
    break;

  case 89:
#line 402 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntDo((yyvsp[-1].pStmntOptVal), (yyvsp[-2].iVal)); }
#line 2552 "y.tab.c"
    break;

  case 90:
#line 403 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntBreak(nbrLines); }
#line 2558 "y.tab.c"
    break;

  case 91:
#line 404 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntGoto((yyvsp[0].sVal), nbrLines); free((yyvsp[0].sVal)); }
#line 2564 "y.tab.c"
    break;

  case 92:
#line 405 "promela.y"
                                                                                { if((yyvsp[0].pStmntVal)->getType() == astNode::E_STMNT_LABEL && static_cast<stmntLabel*>((yyvsp[0].pStmntVal))->getLabelledStmnt()->getType() == astNode::E_STMNT_LABEL) 
													std::cout << "Only two labels per state are supported."; 
												  (yyval.pStmntVal) = new stmntLabel((yyvsp[-2].sVal), (yyvsp[0].pStmntVal), nbrLines); free((yyvsp[-2].sVal)); }
#line 2572 "y.tab.c"
    break;

  case 93:
#line 409 "promela.y"
                                                                { (yyval.pStmntVal) = new stmntAsgn((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2578 "y.tab.c"
    break;

  case 94:
#line 410 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntIncr((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2584 "y.tab.c"
    break;

  case 95:
#line 411 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntDecr((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2590 "y.tab.c"
    break;

  case 96:
#line 412 "promela.y"
                                                                { (yyval.pStmntVal) = new stmntPrint((yyvsp[-2].sVal), (yyvsp[-1].pExprArgListVal), nbrLines); }
#line 2596 "y.tab.c"
    break;

  case 97:
#line 413 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntPrintm((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2602 "y.tab.c"
    break;

  case 98:
#line 414 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntPrintm((yyvsp[-1].iVal), nbrLines); }
#line 2608 "y.tab.c"
    break;

  case 99:
#line 415 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntAssert((yyvsp[0].pExprVal), nbrLines); }
#line 2614 "y.tab.c"
    break;

  case 100:
#line 416 "promela.y"
                                                                                        { std::cout << "Embedded C code is not supported."; }
#line 2620 "y.tab.c"
    break;

  case 101:
#line 417 "promela.y"
                                                                        { std::cout << "Sorted send and random receive are not supported."; }
#line 2626 "y.tab.c"
    break;

  case 102:
#line 418 "promela.y"
                                                                        { std::cout << "Channel poll operations are not supported."; }
#line 2632 "y.tab.c"
    break;

  case 103:
#line 419 "promela.y"
                                                                        { std::cout << "Channel poll operations are not supported."; }
#line 2638 "y.tab.c"
    break;

  case 104:
#line 420 "promela.y"
                                                                        { std::cout << "Sorted send and random receive are not supported."; }
#line 2644 "y.tab.c"
    break;

  case 105:
#line 421 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntExpr((yyvsp[0].pExprVal), nbrLines); }
#line 2650 "y.tab.c"
    break;

  case 106:
#line 422 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntElse(nbrLines); }
#line 2656 "y.tab.c"
    break;

  case 107:
#line 423 "promela.y"
                                                                { (yyval.pStmntVal) = new stmntAtomic((yyvsp[-2].pStmntVal), nbrLines); }
#line 2662 "y.tab.c"
    break;

  case 108:
#line 424 "promela.y"
                                                                { std::cout << "Deterministic steps are not yet supported."; }
#line 2668 "y.tab.c"
    break;

  case 109:
#line 425 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntSeq((yyvsp[-2].pStmntVal), nbrLines); }
#line 2674 "y.tab.c"
    break;

  case 110:
#line 426 "promela.y"
                                                                        { std::cout << "Inline calls are not yet supported."; }
#line 2680 "y.tab.c"
    break;

  case 111:
#line 429 "promela.y"
                                                                                { (yyval.pStmntOptVal) = new stmntOpt((yyvsp[0].pStmntVal), nbrLines); }
#line 2686 "y.tab.c"
    break;

  case 112:
#line 430 "promela.y"
                                                                                { (yyval.pStmntOptVal) = new stmntOpt((yyvsp[-1].pStmntVal), (yyvsp[0].pStmntOptVal), nbrLines); }
#line 2692 "y.tab.c"
    break;

  case 113:
#line 433 "promela.y"
                                                                        { (yyval.pStmntVal) = (yyvsp[-1].pStmntVal); }
#line 2698 "y.tab.c"
    break;

  case 115:
#line 447 "promela.y"
                                        { /* redundant semi at end of sequence */ }
#line 2704 "y.tab.c"
    break;

  case 116:
#line 450 "promela.y"
                                        { /* at least one semi-colon */ }
#line 2710 "y.tab.c"
    break;

  case 117:
#line 451 "promela.y"
                                        { /* but more are okay too   */ }
#line 2716 "y.tab.c"
    break;

  case 118:
#line 454 "promela.y"
                                                                                { (yyval.sVal) = (yyvsp[0].sVal); }
#line 2722 "y.tab.c"
    break;

  case 119:
#line 455 "promela.y"
                                                                                        { (yyval.sVal) = (yyvsp[0].sVal); }
#line 2728 "y.tab.c"
    break;

  case 120:
#line 458 "promela.y"
                                                                        { (yyval.pExprVal) = new exprPar		((yyvsp[-1].pExprVal), nbrLines); }
#line 2734 "y.tab.c"
    break;

  case 121:
#line 459 "promela.y"
                                                                                { (yyval.pExprVal) = new exprPlus		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2740 "y.tab.c"
    break;

  case 122:
#line 460 "promela.y"
                                                                                { (yyval.pExprVal) = new exprMinus	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2746 "y.tab.c"
    break;

  case 123:
#line 461 "promela.y"
                                                                                { (yyval.pExprVal) = new exprTimes	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2752 "y.tab.c"
    break;

  case 124:
#line 462 "promela.y"
                                                                                { (yyval.pExprVal) = new exprDiv		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2758 "y.tab.c"
    break;

  case 125:
#line 463 "promela.y"
                                                                                { (yyval.pExprVal) = new exprMod		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2764 "y.tab.c"
    break;

  case 126:
#line 464 "promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2770 "y.tab.c"
    break;

  case 127:
#line 465 "promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwXor	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2776 "y.tab.c"
    break;

  case 128:
#line 466 "promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2782 "y.tab.c"
    break;

  case 129:
#line 467 "promela.y"
                                                                                { (yyval.pExprVal) = new exprGT		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2788 "y.tab.c"
    break;

  case 130:
#line 468 "promela.y"
                                                                                { (yyval.pExprVal) = new exprLT		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2794 "y.tab.c"
    break;

  case 131:
#line 469 "promela.y"
                                                                                { (yyval.pExprVal) = new exprGE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2800 "y.tab.c"
    break;

  case 132:
#line 470 "promela.y"
                                                                                { (yyval.pExprVal) = new exprLE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2806 "y.tab.c"
    break;

  case 133:
#line 471 "promela.y"
                                                                                { (yyval.pExprVal) = new exprEQ		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2812 "y.tab.c"
    break;

  case 134:
#line 472 "promela.y"
                                                                                { (yyval.pExprVal) = new exprNE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2818 "y.tab.c"
    break;

  case 135:
#line 473 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2824 "y.tab.c"
    break;

  case 136:
#line 474 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2830 "y.tab.c"
    break;

  case 137:
#line 475 "promela.y"
                                                                                { (yyval.pExprVal) = new exprLShift	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2836 "y.tab.c"
    break;

  case 138:
#line 476 "promela.y"
                                                                                { (yyval.pExprVal) = new exprRShift	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2842 "y.tab.c"
    break;

  case 139:
#line 477 "promela.y"
                                                                        { (yyval.pExprVal) = new exprCount	((yyvsp[-1].pExprVal), nbrLines); }
#line 2848 "y.tab.c"
    break;

  case 140:
#line 478 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprBitwNeg	((yyvsp[0].pExprVal), nbrLines); }
#line 2854 "y.tab.c"
    break;

  case 141:
#line 479 "promela.y"
                                                                        { 	if((yyvsp[0].pExprVal)->getType() != astNode::E_EXPR_CONST) 
														(yyval.pExprVal) = new exprUMin((yyvsp[0].pExprVal), nbrLines);
													else {
														exprConst* tmp = static_cast<exprConst*>((yyvsp[0].pExprVal));
														tmp->setCstValue(- tmp->getCstValue());
														(yyval.pExprVal) = tmp;
													}
												}
#line 2867 "y.tab.c"
    break;

  case 142:
#line 487 "promela.y"
                                                                        { (yyval.pExprVal) = new exprNeg	((yyvsp[0].pExprVal), nbrLines); }
#line 2873 "y.tab.c"
    break;

  case 143:
#line 488 "promela.y"
                                                                { (yyval.pExprVal) = new exprCond	((yyvsp[-5].pExprVal), (yyvsp[-3].pExprVal), (yyvsp[-1].pExprVal), nbrLines); }
#line 2879 "y.tab.c"
    break;

  case 144:
#line 489 "promela.y"
                                                        { (yyval.pExprVal) = new exprRun	((yyvsp[-4].sVal), (yyvsp[-2].pExprArgListVal), nbrLines); }
#line 2885 "y.tab.c"
    break;

  case 145:
#line 491 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprRun	((yyvsp[-7].sVal), (yyvsp[-2].pExprArgListVal), (yyvsp[-5].pExprVarRefVal), nbrLines); }
#line 2891 "y.tab.c"
    break;

  case 146:
#line 492 "promela.y"
                                                                        { (yyval.pExprVal) = new exprLen	((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2897 "y.tab.c"
    break;

  case 147:
#line 493 "promela.y"
                                                                        { std::cout << "The enabled keyword is not supported."; }
#line 2903 "y.tab.c"
    break;

  case 148:
#line 494 "promela.y"
                                                                        { std::cout << "Construct not supported."; /* Unclear */ }
#line 2909 "y.tab.c"
    break;

  case 149:
#line 495 "promela.y"
                                                                { std::cout << "Sorted send and random receive are not supported."; }
#line 2915 "y.tab.c"
    break;

  case 150:
#line 496 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprVar	((yyvsp[0].pExprVarRefVal), nbrLines); }
#line 2921 "y.tab.c"
    break;

  case 151:
#line 497 "promela.y"
                                                                                        { std::cout << "Embedded C code is not supported."; }
#line 2927 "y.tab.c"
    break;

  case 152:
#line 498 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprConst((yyvsp[0].iVal), nbrLines); }
#line 2933 "y.tab.c"
    break;

  case 153:
#line 499 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprTrue	(nbrLines); }
#line 2939 "y.tab.c"
    break;

  case 154:
#line 500 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprFalse(nbrLines); }
#line 2945 "y.tab.c"
    break;

  case 155:
#line 501 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprTimeout(nbrLines); }
#line 2951 "y.tab.c"
    break;

  case 156:
#line 502 "promela.y"
                                                                                { std::cout << "The 'np_' variable is not supported."; }
#line 2957 "y.tab.c"
    break;

  case 157:
#line 503 "promela.y"
                                                                        { std::cout << "The 'pc_value()' construct is not supported."; }
#line 2963 "y.tab.c"
    break;

  case 158:
#line 504 "promela.y"
                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 2969 "y.tab.c"
    break;

  case 159:
#line 505 "promela.y"
                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 2975 "y.tab.c"
    break;

  case 160:
#line 506 "promela.y"
                                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 2981 "y.tab.c"
    break;

  case 161:
#line 507 "promela.y"
                                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 2987 "y.tab.c"
    break;

  case 163:
#line 511 "promela.y"
                                                                                { std::cout << "The 'priority' construct is related to simulation and not supported."; }
#line 2993 "y.tab.c"
    break;

  case 164:
#line 514 "promela.y"
                                                                                { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 2999 "y.tab.c"
    break;

  case 165:
#line 515 "promela.y"
                                                                                        { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 3005 "y.tab.c"
    break;

  case 167:
#line 519 "promela.y"
                                                                { std::cout << "The 'provided' construct is currently not supported."; }
#line 3011 "y.tab.c"
    break;

  case 168:
#line 524 "promela.y"
                                                                                { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 3017 "y.tab.c"
    break;

  case 169:
#line 525 "promela.y"
                                                                                { (yyval.pExprVal) = new exprPar	((yyvsp[-1].pExprVal), nbrLines); }
#line 3023 "y.tab.c"
    break;

  case 170:
#line 526 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3029 "y.tab.c"
    break;

  case 171:
#line 527 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3035 "y.tab.c"
    break;

  case 172:
#line 528 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3041 "y.tab.c"
    break;

  case 173:
#line 529 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3047 "y.tab.c"
    break;

  case 174:
#line 530 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3053 "y.tab.c"
    break;

  case 175:
#line 531 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3059 "y.tab.c"
    break;

  case 176:
#line 532 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprSkip	(nbrLines); }
#line 3065 "y.tab.c"
    break;

  case 177:
#line 535 "promela.y"
                                                                { (yyval.pExprVal) = new exprFull	((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3071 "y.tab.c"
    break;

  case 178:
#line 536 "promela.y"
                                                                        { (yyval.pExprVal) = new exprNFull((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3077 "y.tab.c"
    break;

  case 179:
#line 537 "promela.y"
                                                                        { (yyval.pExprVal) = new exprEmpty((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3083 "y.tab.c"
    break;

  case 180:
#line 538 "promela.y"
                                                                        { (yyval.pExprVal) = new exprNEmpty((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3089 "y.tab.c"
    break;

  case 182:
#line 543 "promela.y"
                                                                                        { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3095 "y.tab.c"
    break;

  case 183:
#line 547 "promela.y"
                                                                        { (yyval.pExprArgListVal) = nullptr; }
#line 3101 "y.tab.c"
    break;

  case 184:
#line 548 "promela.y"
                                                                                        { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3107 "y.tab.c"
    break;

  case 185:
#line 552 "promela.y"
                                                                                { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3113 "y.tab.c"
    break;

  case 186:
#line 553 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList(static_cast<exprRArg*>((yyvsp[-3].pExprVal)), static_cast<exprArgList*>((yyvsp[-1].pExprArgListVal)), nbrLines); }
#line 3119 "y.tab.c"
    break;

  case 187:
#line 556 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList(static_cast<exprRArg*>((yyvsp[0].pExprVal)), nbrLines); }
#line 3125 "y.tab.c"
    break;

  case 188:
#line 557 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList(static_cast<exprRArg*>((yyvsp[-2].pExprVal)), static_cast<exprArgList*>((yyvsp[0].pExprArgListVal)), nbrLines); }
#line 3131 "y.tab.c"
    break;

  case 189:
#line 560 "promela.y"
                                                                                { (yyval.pExprRArgVal) = new exprRArgVar((yyvsp[0].pExprVarRefVal), nbrLines); }
#line 3137 "y.tab.c"
    break;

  case 190:
#line 561 "promela.y"
                                                                                { (yyval.pExprRArgVal) = new exprRArgEval((yyvsp[-1].pExprVal), nbrLines); }
#line 3143 "y.tab.c"
    break;

  case 191:
#line 562 "promela.y"
                                                                                        { (yyval.pExprRArgVal) = new exprRArgConst((yyvsp[0].iVal), nbrLines); }
#line 3149 "y.tab.c"
    break;

  case 192:
#line 563 "promela.y"
                                                                        { (yyval.pExprRArgVal) = new exprRArgConst(-(yyvsp[0].iVal), nbrLines); }
#line 3155 "y.tab.c"
    break;

  case 193:
#line 567 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList((yyvsp[0].pExprRArgVal), nbrLines); }
#line 3161 "y.tab.c"
    break;

  case 194:
#line 568 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList((yyvsp[-2].pExprRArgVal), (yyvsp[0].pExprArgListVal), nbrLines); }
#line 3167 "y.tab.c"
    break;

  case 195:
#line 569 "promela.y"
                                                                        { (yyval.pExprArgListVal) = new exprArgList((yyvsp[-3].pExprRArgVal), (yyvsp[-1].pExprArgListVal), nbrLines); }
#line 3173 "y.tab.c"
    break;

  case 196:
#line 570 "promela.y"
                                                                                { (yyval.pExprArgListVal) = (yyvsp[-1].pExprArgListVal); }
#line 3179 "y.tab.c"
    break;

  case 197:
#line 573 "promela.y"
                                                                                { std::cout << "REDUCE: NAME -> nlst\n"; cmtypeSymNode* sym = new cmtypeSymNode(nbrLines, (yyvsp[0].sVal), mtypeId++); mtypes[(yyvsp[0].sVal)] = sym; (*globalSymTab)->insert(sym); free((yyvsp[0].sVal)); }
#line 3185 "y.tab.c"
    break;

  case 198:
#line 574 "promela.y"
                                                                                        { std::cout << "REDUCE: nlst NAME -> NAME\n"; cmtypeSymNode* sym = new cmtypeSymNode(nbrLines, (yyvsp[0].sVal), mtypeId++); mtypes[(yyvsp[0].sVal)] = sym; (*globalSymTab)->insert(sym); free((yyvsp[0].sVal)); }
#line 3191 "y.tab.c"
    break;

  case 199:
#line 575 "promela.y"
                                                                { std::cout << "REDUCE: nlst , -> nlst\n"; }
#line 3197 "y.tab.c"
    break;


#line 3201 "y.tab.c"

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
#line 577 "promela.y"

