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
    UNTIL = 327,
    LTL = 328,
    ASGN = 329,
    SND = 330,
    O_SND = 331,
    RCV = 332,
    R_RCV = 333,
    OR = 334,
    AND = 335,
    EQ = 336,
    NE = 337,
    GT = 338,
    LT = 339,
    GE = 340,
    LE = 341,
    LSHIFT = 342,
    RSHIFT = 343,
    INCR = 344,
    DECR = 345,
    UMIN = 346,
    NEG = 347,
    COUNT = 348,
    CONTEXT = 349,
    DOT = 350,
    IMPLIES = 351
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
#line 62 "promela.y"
 
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

#line 392 "y.tab.cpp"

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
#define YYLAST   1709

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  116
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  236
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  454

#define YYUNDEFTOK  2
#define YYMAXUTOK   351


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
       2,     2,     2,     2,     2,     2,     2,    96,    83,     2,
     106,   107,    94,    92,   113,    93,   114,    95,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   112,     2,
       2,     2,     2,     2,   115,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   108,     2,   109,    82,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   110,    81,   111,    99,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    84,    85,    86,    87,
      88,    89,    90,    91,    97,    98,   100,   101,   102,   103,
     104,   105
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   145,   145,   145,   150,   153,   154,   157,   158,   159,
     160,   173,   174,   175,   176,   177,   183,   191,   181,   206,
     207,   210,   211,   212,   213,   227,   226,   242,   245,   257,
     257,   276,   277,   279,   276,   294,   295,   298,   299,   300,
     301,   304,   305,   308,   311,   311,   321,   322,   323,   326,
     331,   332,   333,   334,   342,   343,   344,   345,   348,   349,
     355,   355,   356,   356,   359,   360,   364,   365,   372,   373,
     376,   381,   386,   391,   392,   393,   397,   400,   401,   405,
     420,   437,   438,   439,   442,   445,   446,   449,   450,   453,
     454,   458,   459,   462,   463,   464,   465,   466,   467,   468,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,   489,   501,   502,
     505,   518,   519,   522,   523,   526,   527,   530,   531,   532,
     533,   534,   535,   536,   537,   538,   539,   540,   541,   542,
     543,   544,   545,   546,   547,   548,   549,   550,   551,   559,
     560,   561,   566,   567,   568,   569,   570,   571,   572,   573,
     574,   575,   576,   577,   578,   579,   580,   581,   584,   585,
     588,   589,   592,   593,   598,   599,   600,   601,   602,   603,
     604,   605,   606,   609,   610,   611,   612,   616,   617,   621,
     622,   626,   627,   630,   631,   634,   635,   636,   637,   641,
     642,   643,   644,   647,   648,   649,   653,   654,   655,   658,
     662,   663,   664,   665,   666,   667,   668,   669,   670,   671,
     672,   673,   674,   675,   676,   677,   678,   679,   680,   681,
     682,   683,   684,   687,   688,   691,   692
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
  "EVENTUALLY", "ALWAYS", "GLOBALLY", "FINALLY", "UNTIL", "LTL", "ASGN",
  "SND", "O_SND", "RCV", "R_RCV", "OR", "AND", "'|'", "'^'", "'&'", "EQ",
  "NE", "GT", "LT", "GE", "LE", "LSHIFT", "RSHIFT", "'+'", "'-'", "'*'",
  "'/'", "'%'", "INCR", "DECR", "'~'", "UMIN", "NEG", "COUNT", "CONTEXT",
  "DOT", "IMPLIES", "'('", "')'", "'['", "']'", "'{'", "'}'", "':'", "','",
  "'.'", "'@'", "$accept", "start_parsing", "$@1", "program", "units",
  "unit", "proc", "$@2", "$@3", "proctype", "inst", "init", "$@4",
  "events", "utypedef", "mtypedef", "$@5", "ns", "$@6", "$@7", "$@8",
  "c_fcts", "cstate", "ccode", "cexpr", "body", "$@9", "sequence", "step",
  "vis", "asgn", "one_decl", "$@10", "$@11", "decl_lst", "decl",
  "var_list", "ivar", "param_list", "ch_init", "basetype", "typ_list",
  "vardcl", "varref", "pfld", "cmpnd", "sfld", "stmnt", "Special", "Stmnt",
  "options", "option", "OS", "MS", "aname", "expr", "Opt_priority",
  "full_expr", "Opt_enabler", "Expr", "Probe", "args", "prargs", "margs",
  "arg", "rarg", "rargs", "nlst", "props", "prop", "prop_expr", "quants",
  "quant", YY_NULLPTR
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
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   124,    94,    38,   336,   337,   338,   339,   340,   341,
     342,   343,    43,    45,    42,    47,    37,   344,   345,   126,
     346,   347,   348,   349,   350,   351,    40,    41,    91,    93,
     123,   125,    58,    44,    46,    64
};
# endif

#define YYPACT_NINF (-384)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-123)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -384,    32,  1300,  -384,  -384,  -384,    34,    40,    66,  -384,
    -384,   -32,  -384,  -384,  -384,   -18,  -384,    63,  1266,  -384,
    -384,    70,  -384,  -384,  -384,  -384,  -384,  -384,  -384,  -384,
      77,  -384,    94,   122,    31,   137,    62,  -384,  -384,    96,
     148,  -384,    63,  -384,  -384,  -384,   153,     8,  -384,   167,
     179,   124,  -384,   114,   128,   840,   206,   -18,   118,  -384,
    -384,  -384,  -384,   233,   233,  -384,  -384,   230,   208,   140,
     146,  -384,  -384,  -384,   213,   213,   -37,   -75,   151,  -384,
    -384,  -384,  1058,   152,   173,  -384,   232,   174,   175,   177,
     252,  -384,  -384,   176,   178,  -384,  -384,   183,   184,   186,
     187,  1117,  1117,  1117,   188,   171,  1058,   840,  -384,  -384,
     419,  -384,  -384,   157,   182,  -384,   255,  -384,  -384,  1595,
    -384,    91,  -384,  -384,  -384,    11,   194,   193,    38,  -384,
     191,   234,  -384,  -384,   124,  -384,   300,   840,   271,   213,
     277,  1117,   632,  1117,   310,   311,  1117,   211,   139,  -384,
     312,     9,  -384,  -384,   218,    -2,  1117,  1117,  -384,   840,
     840,    -2,    -2,    -2,    -2,  1117,  -384,  -384,  -384,  1117,
     310,  1086,   -51,   419,   -15,  -384,   216,   736,  1058,  1117,
    1117,    60,    61,  -384,  -384,    -2,  -384,   944,  1058,  1058,
    1117,  1117,  1117,  1117,  1117,  1117,  1117,  1117,  1117,  1117,
    1117,  1117,  1117,  1117,  1117,  1117,  1058,  1058,  -384,  -384,
    -384,    11,    11,  -384,   285,    11,   181,   -16,   321,   346,
     347,   233,  1003,  -384,   239,   246,   528,  -384,  -384,  -384,
    1388,    49,  -384,  -384,  -384,  1419,  -384,  -384,  1319,   247,
    -384,   248,   250,   242,   253,   254,  1117,   268,  1450,  1479,
     419,   419,   269,   275,   276,   278,  1146,  1117,  1117,  1508,
     182,  1117,  -384,  -384,   284,  -384,  -384,  -384,  -384,  1284,
    -384,  -384,  -384,  -384,   280,    39,   356,    39,    39,  -384,
     -65,  -384,    39,    39,  -384,  -384,  -384,   732,   317,   714,
    -384,   817,  1111,  1332,  1365,  1365,   298,   298,   298,   298,
     -34,   -34,   125,   125,  -384,  -384,  -384,   732,   317,   714,
    -384,   -17,  1175,    11,    11,    11,    11,    11,    11,    11,
      11,    11,    11,    11,    11,    11,    11,    11,    11,    11,
      11,  -384,   530,  -384,  -384,   293,  -384,     2,   292,  -384,
    -384,   418,  -384,  1613,   300,  -384,  -384,  -384,   944,   -62,
    1117,  -384,  1117,   318,  -384,  -384,   320,  -384,  -384,  -384,
     319,   330,  -384,  -384,  -384,  -384,   836,   714,  -384,  -384,
    1354,  -384,  1117,  1117,   360,  -384,   335,   339,    39,    39,
     363,   342,  -384,   530,   530,   100,   119,   413,   625,   394,
     503,   503,   219,   219,   219,   219,    44,    44,   -17,   -17,
     -17,  -384,  -384,  -384,  -384,  -384,   343,  -384,   -18,   310,
     450,  -384,  -384,  -384,    96,  -384,  -384,  1117,   351,  1537,
    -384,  -384,  -384,   352,  -384,  -384,  -384,    96,   428,  -384,
    -384,  -384,  -384,  1566,  -384,  -384,  -384,   409,   357,  -384,
     362,   -18,   240,  1058,  -384,  -384,  -384,   359,   373,   366,
     240,  -384,  -384,  -384
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,    21,     1,    41,    42,     0,     0,     0,    31,
      15,    22,    55,    56,    57,     0,    25,   206,     4,     5,
       7,     0,     8,     9,    11,    12,    14,    13,    36,    35,
       0,    10,     0,     0,     0,     0,     0,    44,    27,   168,
       0,     3,   206,     6,    19,    20,     0,    58,    62,    37,
      38,    54,    32,     0,     0,    54,     0,     0,     0,   208,
      16,    59,    29,     0,     0,    39,    40,     0,    64,     0,
       0,    23,    24,   158,     0,     0,    85,     0,     0,   159,
     160,   182,     0,     0,     0,    43,     0,     0,     0,     0,
       0,    97,   113,     0,     0,   161,   162,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    54,   107,   157,
      54,    46,    49,   156,    89,    84,    52,    91,    92,   170,
     112,   171,   174,   169,    26,     0,     0,     0,    81,    61,
      68,    70,    63,    60,    54,    28,    73,    54,     0,   118,
       0,     0,    54,     0,     0,     0,   187,    85,   156,   106,
       0,     0,   125,   126,     0,     0,     0,     0,    98,    54,
      54,     0,     0,     0,     0,     0,   149,   148,   147,     0,
       0,     0,     0,    54,   123,    48,     0,    54,     0,     0,
       0,     0,     0,   101,   102,     0,    87,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   232,   236,
     235,     0,     0,   231,     0,     0,   233,    54,     0,     0,
       0,     0,     0,    65,    74,     0,   121,    95,   119,    96,
       0,    85,    51,    50,    99,     0,   167,   166,   193,     0,
     188,     0,     0,   189,     0,     0,   187,     0,     0,     0,
      54,    54,     0,     0,     0,     0,     0,     0,     0,     0,
      89,     0,   127,   175,     0,    45,   124,    47,   100,   193,
      94,   191,   111,   197,     0,     0,     0,     0,     0,   195,
     199,    93,     0,     0,   108,    90,    53,   143,   181,   142,
     180,   135,   134,   133,   140,   141,   136,   137,   138,   139,
     144,   145,   128,   129,   130,   131,   132,   179,   178,   177,
     176,   230,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   209,   211,   234,    67,     0,   203,     0,     0,    82,
      69,     0,    72,    71,    73,    33,   120,    86,     0,     0,
       0,   117,     0,     0,   105,   104,     0,   152,   153,   163,
       0,     0,   183,   185,   184,   186,   143,   142,   146,    88,
       0,   116,     0,     0,     0,   198,     0,     0,     0,     0,
       0,     0,   210,   228,   229,   227,   226,   219,   218,   217,
     224,   225,   220,   221,   222,   223,   212,   213,   214,   215,
     216,    17,   204,    30,   205,    83,     0,    75,     0,     0,
       0,   194,   190,   103,   168,   114,   115,     0,     0,     0,
     109,   202,   154,     0,   200,   110,   155,   168,     0,    34,
     165,   164,   151,     0,   192,   196,   201,   172,     0,   150,
       0,     0,     0,     0,    18,    77,    78,    79,     0,     0,
       0,    76,   173,    80
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -384,  -384,  -384,  -384,  -384,   474,  -384,  -384,  -384,  -384,
    -384,  -384,  -384,  -384,  -384,  -384,  -384,  -384,  -384,  -384,
    -384,  -384,  -384,    20,  -384,   -57,  -384,   -60,   -99,    25,
    -384,     1,  -384,  -384,  -124,  -384,   -56,  -384,   159,  -384,
    -384,    54,  -384,   -53,  -131,   325,   251,  -138,  -384,  -384,
     -49,  -384,  -156,  -384,  -384,   141,  -383,   -81,  -384,   -85,
    -384,   270,  -384,   337,  -173,  -384,  -152,  -384,   473,  -384,
      90,   303,  -384
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    17,    18,    19,    20,   126,   427,    46,
      21,    22,    39,    23,    24,    25,   127,    26,    35,    70,
     408,    27,    28,   108,   109,    38,    55,   110,   111,    67,
      62,   112,    63,    64,    69,   335,   129,   130,   225,   342,
     447,   448,   131,   148,   114,   115,   186,   116,   117,   118,
     138,   139,   176,   177,   154,   119,    57,   120,   441,   121,
     122,   239,   353,   270,   240,   280,   281,   337,    41,    42,
     214,   215,   216
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     124,   149,   113,    31,   234,   147,   271,   271,   132,   402,
     223,   175,   244,   236,   208,   -60,   147,   264,   147,    31,
     313,   172,    29,  -122,  -122,  -122,   140,    30,   206,   207,
     284,   432,     3,   143,    12,    13,    14,   144,    29,   260,
     145,   378,   273,    30,   437,    32,   147,   173,   379,   286,
     409,    33,    68,   410,   113,   314,   263,   113,   201,   202,
     203,   204,   205,   273,   273,    53,   274,   147,   147,    54,
     346,   141,   213,    34,   175,   142,    36,   226,   267,   209,
     210,   313,    61,    47,   113,    48,   211,   274,   274,   113,
     228,   -66,    37,   334,   360,   361,  -122,   268,   245,   250,
     251,   105,   247,   288,   290,    49,   113,   113,   252,   253,
     254,   255,   105,   403,   105,   404,   314,   212,    44,    45,
     113,   308,   310,   374,   113,   376,   377,   175,   279,   279,
     380,   381,   276,    50,   113,    68,    40,   313,   328,   329,
     330,    51,   105,   233,    52,   277,   219,   275,   282,    56,
     220,   175,   175,   276,   276,    58,   313,   141,   213,   213,
      60,   348,   213,   105,   105,   340,   277,   277,   278,   283,
     206,   207,   314,   113,    12,    13,    14,   411,    65,   412,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
      66,   314,   326,   327,   328,   329,   330,   113,   113,   418,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   123,
     234,   326,   327,   328,   329,   330,   241,   242,    68,   203,
     204,   205,   279,    71,   279,   279,   423,   424,   125,   279,
     279,   178,   179,   180,   181,   182,   133,    72,    48,   152,
     128,   153,   166,   167,   168,   134,   445,   171,   446,   209,
     210,   135,   136,   137,   183,   184,   313,   146,   150,   158,
     213,   213,   213,   213,   213,   213,   213,   213,   213,   213,
     213,   213,   213,   213,   213,   213,   213,   213,   430,   151,
     155,   156,   230,   157,   235,   170,   159,   238,   160,   161,
     162,   314,   163,   164,   169,   113,   185,   248,   249,   187,
     217,   311,   312,   218,   221,   332,   256,   224,   222,   227,
     259,   326,   327,   328,   329,   330,   229,   147,   237,   141,
     269,   269,   313,   243,   246,   279,   279,   265,   336,   287,
     289,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   309,   338,
     339,   429,   344,   345,   351,   352,   278,   314,   283,   375,
     354,   355,   449,   343,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   357,   362,   326,   327,   328,
     329,   330,   363,   364,   444,   365,   373,   238,   199,   200,
     201,   202,   203,   204,   205,   371,   331,   207,   366,   367,
     401,   405,   370,   383,   384,   385,   386,   387,   388,   389,
     390,   391,   392,   393,   394,   395,   396,   397,   398,   399,
     400,   406,    73,    74,    75,   413,    76,   414,    77,    78,
     415,   313,    79,    80,    81,    82,    83,    84,     4,     5,
      85,   416,   421,    86,    87,    88,   420,    89,   422,   425,
     313,   426,   428,    90,    91,    92,   174,   431,   434,   436,
      93,   438,    94,   440,    95,    96,   314,   442,   443,    12,
      13,    14,   450,   452,    97,    98,    99,   100,   320,   321,
     322,   323,   324,   325,   451,   314,   326,   327,   328,   329,
     330,   238,    43,   238,   101,   318,   319,   320,   321,   322,
     323,   324,   325,   407,   453,   326,   327,   328,   329,   330,
     285,   369,   102,   238,   419,    59,   356,   272,   103,   333,
       0,   104,   105,     0,     0,   106,     0,     0,     0,   107,
    -121,    73,    74,    75,   -54,    76,   -54,    77,    78,     0,
     313,    79,    80,    81,    82,    83,    84,     4,     5,    85,
       0,     0,    86,    87,    88,     0,    89,     0,   433,     0,
       0,     0,    90,    91,    92,   174,     0,   313,     0,    93,
       0,    94,     0,    95,    96,   314,     0,     0,    12,    13,
      14,     0,     0,    97,    98,    99,   100,     0,     0,   322,
     323,   324,   325,     0,     0,   326,   327,   328,   329,   330,
       0,     0,   314,   101,     0,     0,     0,     0,     0,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
       0,   102,   326,   327,   328,   329,   330,   103,     0,     0,
     104,   105,     0,     0,   106,    73,    74,    75,   107,   231,
       0,    77,    78,     0,     0,    79,    80,    81,    82,    83,
      84,     4,     5,    85,     0,     0,    86,    87,    88,     0,
      89,     0,   313,     0,     0,     0,    90,    91,    92,     0,
       0,     0,     0,    93,     0,    94,     0,    95,    96,     0,
       0,     0,    12,    13,    14,     0,     0,    97,    98,    99,
     100,   232,     0,     0,     0,     0,     0,   314,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   101,   319,   320,
     321,   322,   323,   324,   325,     0,     0,   326,   327,   328,
     329,   330,     0,     0,     0,   102,     0,     0,     0,     0,
       0,   103,     0,     0,   104,   105,     0,     0,   106,    73,
      74,    75,   107,    76,     0,    77,    78,     0,     0,    79,
      80,    81,    82,    83,    84,     4,     5,    85,     0,     0,
      86,    87,    88,     0,    89,     0,     0,     0,     0,     0,
      90,    91,    92,   266,     0,     0,     0,    93,     0,    94,
       0,    95,    96,     0,     0,     0,    12,    13,    14,     0,
       0,    97,    98,    99,   100,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   101,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   102,
       0,     0,     0,     0,     0,   103,     0,     0,   104,   105,
       0,     0,   106,    73,    74,    75,   107,    76,     0,    77,
      78,     0,     0,    79,    80,    81,    82,    83,    84,     4,
       5,    85,     0,     0,    86,    87,    88,     0,    89,     0,
       0,     0,     0,     0,    90,    91,    92,     0,     0,     0,
       0,    93,     0,    94,     0,    95,    96,     0,     0,     0,
      12,    13,    14,     0,     0,    97,    98,    99,   100,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,     0,   101,   258,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   102,     0,     0,     0,     0,     0,   103,
       0,     0,   104,   105,     0,     0,   106,    73,    74,    75,
     107,   231,     0,    77,    78,     0,     0,    79,    80,    81,
      82,    83,    84,     4,     5,    85,     0,     0,    86,    87,
      88,     0,    89,     0,     0,     0,     0,     0,    90,    91,
      92,     0,     0,     0,     0,    93,     0,    94,     0,    95,
      96,     0,     0,     0,     0,     0,     0,     0,     0,    97,
      98,    99,   100,     0,     0,     0,    73,     0,     0,     0,
     147,     0,    77,     0,     0,     0,    79,    80,     0,   101,
       0,     0,     0,     0,    85,     0,     0,    86,    87,    88,
       0,    89,     0,     0,     0,     0,     0,   102,     0,     0,
       0,     0,     0,   103,     0,     0,   104,   105,    95,    96,
     106,     0,     0,     0,   107,     0,     0,     0,     0,     0,
       0,    73,     0,     0,     0,   147,     0,    77,     0,     0,
       0,    79,    80,    81,     0,     0,     0,     0,   101,    85,
       0,     0,    86,    87,    88,     0,    89,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   102,     0,     0,     0,
       0,     0,   103,    95,    96,   104,   105,     0,     0,   165,
       0,   341,     0,    97,    98,    99,   100,     0,     0,     0,
      73,     0,     0,   261,   147,     0,    77,     0,     0,     0,
      79,    80,     0,   101,     0,     0,     0,     0,    85,     0,
       0,    86,    87,    88,     0,    89,     0,     0,     0,     0,
       0,   102,     0,     0,     0,     0,     0,   103,     0,     0,
     104,   105,    95,    96,   106,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   261,     0,     0,     0,     0,     0,     0,
       0,     0,   101,   262,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,     0,     0,
     102,     0,   313,     0,     0,     0,   103,     0,     0,   104,
     105,     0,     0,   165,     0,   257,   258,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,     0,     0,     0,     0,   314,     0,     0,
       0,     0,     0,   262,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,     0,     0,   326,   327,   328,
     329,   330,   -54,     0,   -54,     0,     0,     0,     0,     0,
       0,     0,   382,     0,     0,     4,     5,     0,     6,     7,
       0,     0,     0,     0,     0,     8,     0,     9,     0,     0,
       0,     0,     0,    10,     0,     0,   -54,     0,   -54,     0,
       0,     0,     0,    11,   -21,   -21,    12,    13,    14,     4,
       5,     0,     6,     7,     0,     0,     0,    15,    16,     8,
       0,     9,     0,     0,     0,     0,     0,    10,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    11,     0,     0,
      12,    13,    14,     0,     0,     0,     0,     0,     0,     0,
       0,    15,    16,   257,   258,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     372,     0,     0,     0,     0,     0,     0,   350,   257,   258,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,     0,
       0,     0,   350,   257,   258,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,     0,     0,     0,     0,   417,   257,   258,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   347,   257,   258,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   349,   257,
     258,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   358,   257,   258,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   359,   257,   258,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   368,   257,   258,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   435,   257,   258,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   439,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   257,   258,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205
};

static const yytype_int16 yycheck[] =
{
      57,    82,    55,     2,   142,     7,   179,   180,    64,     7,
     134,   110,     3,   144,     3,     7,     7,   173,     7,    18,
      37,   106,     2,    38,    39,    40,    75,     2,    79,    80,
     182,   414,     0,   108,    50,    51,    52,   112,    18,   170,
     115,   106,     3,    18,   427,    11,     7,   107,   113,   187,
     112,    11,    51,   115,   107,    72,   107,   110,    92,    93,
      94,    95,    96,     3,     3,     3,    27,     7,     7,     7,
     226,   108,   125,     7,   173,   112,   108,   137,   177,    68,
      69,    37,    74,     6,   137,     8,    75,    27,    27,   142,
     139,   107,   110,   217,   250,   251,   111,   178,   151,   159,
     160,   103,   155,   188,   189,    11,   159,   160,   161,   162,
     163,   164,   103,   111,   103,   113,    72,   106,    48,    49,
     173,   206,   207,   275,   177,   277,   278,   226,   181,   182,
     282,   283,    93,    11,   187,   134,    73,    37,    94,    95,
      96,   110,   103,   142,     7,   106,   108,    87,    87,    53,
     112,   250,   251,    93,    93,     7,    37,   108,   211,   212,
       7,   112,   215,   103,   103,   221,   106,   106,   108,   108,
      79,    80,    72,   226,    50,    51,    52,   350,    11,   352,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      11,    72,    92,    93,    94,    95,    96,   250,   251,   372,
      81,    82,    83,    84,    85,    86,    87,    88,    89,     3,
     348,    92,    93,    94,    95,    96,    77,    78,   217,    94,
      95,    96,   275,   109,   277,   278,   378,   379,   110,   282,
     283,    74,    75,    76,    77,    78,     6,   109,     8,     7,
       7,     9,   101,   102,   103,    37,     6,   106,     8,    68,
      69,   111,   106,    40,    97,    98,    37,   106,   106,     7,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   409,   106,
     106,   106,   141,   106,   143,   114,   110,   146,   110,   106,
     106,    72,   106,   106,   106,   348,   114,   156,   157,    44,
     106,   211,   212,   110,   113,   215,   165,     7,    74,    38,
     169,    92,    93,    94,    95,    96,    39,     7,     7,   108,
     179,   180,    37,    11,   106,   378,   379,   111,     7,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,     3,
       3,   408,   113,   107,   107,   113,   108,    72,   108,     3,
     107,   107,   443,   222,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,   107,   107,    92,    93,    94,
      95,    96,   107,   107,   441,   107,   106,   246,    90,    91,
      92,    93,    94,    95,    96,   111,   111,    80,   257,   258,
     107,   109,   261,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,     3,     3,     4,     5,   107,     7,   107,     9,    10,
     111,    37,    13,    14,    15,    16,    17,    18,    19,    20,
      21,   111,   107,    24,    25,    26,    86,    28,   109,    86,
      37,   109,   109,    34,    35,    36,    37,     7,   107,   107,
      41,    33,    43,    54,    45,    46,    72,   110,   106,    50,
      51,    52,   113,   107,    55,    56,    57,    58,    84,    85,
      86,    87,    88,    89,   111,    72,    92,    93,    94,    95,
      96,   350,    18,   352,    75,    82,    83,    84,    85,    86,
      87,    88,    89,   344,   450,    92,    93,    94,    95,    96,
     185,   260,    93,   372,   373,    42,   246,   180,    99,   216,
      -1,   102,   103,    -1,    -1,   106,    -1,    -1,    -1,   110,
     111,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      37,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    24,    25,    26,    -1,    28,    -1,   417,    -1,
      -1,    -1,    34,    35,    36,    37,    -1,    37,    -1,    41,
      -1,    43,    -1,    45,    46,    72,    -1,    -1,    50,    51,
      52,    -1,    -1,    55,    56,    57,    58,    -1,    -1,    86,
      87,    88,    89,    -1,    -1,    92,    93,    94,    95,    96,
      -1,    -1,    72,    75,    -1,    -1,    -1,    -1,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    93,    92,    93,    94,    95,    96,    99,    -1,    -1,
     102,   103,    -1,    -1,   106,     3,     4,     5,   110,     7,
      -1,     9,    10,    -1,    -1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    24,    25,    26,    -1,
      28,    -1,    37,    -1,    -1,    -1,    34,    35,    36,    -1,
      -1,    -1,    -1,    41,    -1,    43,    -1,    45,    46,    -1,
      -1,    -1,    50,    51,    52,    -1,    -1,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    83,    84,
      85,    86,    87,    88,    89,    -1,    -1,    92,    93,    94,
      95,    96,    -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,
      -1,    99,    -1,    -1,   102,   103,    -1,    -1,   106,     3,
       4,     5,   110,     7,    -1,     9,    10,    -1,    -1,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
      24,    25,    26,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    -1,    -1,    -1,    41,    -1,    43,
      -1,    45,    46,    -1,    -1,    -1,    50,    51,    52,    -1,
      -1,    55,    56,    57,    58,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    75,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    93,
      -1,    -1,    -1,    -1,    -1,    99,    -1,    -1,   102,   103,
      -1,    -1,   106,     3,     4,     5,   110,     7,    -1,     9,
      10,    -1,    -1,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    24,    25,    26,    -1,    28,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,
      -1,    41,    -1,    43,    -1,    45,    46,    -1,    -1,    -1,
      50,    51,    52,    -1,    -1,    55,    56,    57,    58,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    -1,    75,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    93,    -1,    -1,    -1,    -1,    -1,    99,
      -1,    -1,   102,   103,    -1,    -1,   106,     3,     4,     5,
     110,     7,    -1,     9,    10,    -1,    -1,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    24,    25,
      26,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,    35,
      36,    -1,    -1,    -1,    -1,    41,    -1,    43,    -1,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    58,    -1,    -1,    -1,     3,    -1,    -1,    -1,
       7,    -1,     9,    -1,    -1,    -1,    13,    14,    -1,    75,
      -1,    -1,    -1,    -1,    21,    -1,    -1,    24,    25,    26,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    93,    -1,    -1,
      -1,    -1,    -1,    99,    -1,    -1,   102,   103,    45,    46,
     106,    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    -1,    -1,    -1,     7,    -1,     9,    -1,    -1,
      -1,    13,    14,    15,    -1,    -1,    -1,    -1,    75,    21,
      -1,    -1,    24,    25,    26,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,    -1,    -1,
      -1,    -1,    99,    45,    46,   102,   103,    -1,    -1,   106,
      -1,   108,    -1,    55,    56,    57,    58,    -1,    -1,    -1,
       3,    -1,    -1,    37,     7,    -1,     9,    -1,    -1,    -1,
      13,    14,    -1,    75,    -1,    -1,    -1,    -1,    21,    -1,
      -1,    24,    25,    26,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    93,    -1,    -1,    -1,    -1,    -1,    99,    -1,    -1,
     102,   103,    45,    46,   106,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,   107,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    -1,    -1,
      93,    -1,    37,    -1,    -1,    -1,    99,    -1,    -1,   102,
     103,    -1,    -1,   106,    -1,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    -1,    -1,    -1,    -1,    72,    -1,    -1,
      -1,    -1,    -1,   107,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    -1,    -1,    92,    93,    94,
      95,    96,     6,    -1,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   107,    -1,    -1,    19,    20,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    37,    -1,    -1,     6,    -1,     8,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    19,
      20,    -1,    22,    23,    -1,    -1,    -1,    61,    62,    29,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,
      50,    51,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    62,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     106,    -1,    -1,    -1,    -1,    -1,    -1,   113,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    -1,
      -1,    -1,   113,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    -1,    -1,    -1,    -1,   112,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   107,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   107,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   107,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   117,   118,     0,    19,    20,    22,    23,    29,    31,
      37,    47,    50,    51,    52,    61,    62,   119,   120,   121,
     122,   126,   127,   129,   130,   131,   133,   137,   138,   139,
     145,   147,    11,    11,     7,   134,   108,   110,   141,   128,
      73,   184,   185,   121,    48,    49,   125,     6,     8,    11,
      11,   110,     7,     3,     7,   142,    53,   172,     7,   184,
       7,    74,   146,   148,   149,    11,    11,   145,   147,   150,
     135,   109,   109,     3,     4,     5,     7,     9,    10,    13,
      14,    15,    16,    17,    18,    21,    24,    25,    26,    28,
      34,    35,    36,    41,    43,    45,    46,    55,    56,    57,
      58,    75,    93,    99,   102,   103,   106,   110,   139,   140,
     143,   144,   147,   159,   160,   161,   163,   164,   165,   171,
     173,   175,   176,     3,   141,   110,   123,   132,     7,   152,
     153,   158,   152,     6,    37,   111,   106,    40,   166,   167,
     166,   108,   112,   108,   112,   115,   106,     7,   159,   173,
     106,   106,     7,     9,   170,   106,   106,   106,     7,   110,
     110,   106,   106,   106,   106,   106,   171,   171,   171,   106,
     114,   171,   175,   143,    37,   144,   168,   169,    74,    75,
      76,    77,    78,    97,    98,   114,   162,    44,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    79,    80,     3,    68,
      69,    75,   106,   159,   186,   187,   188,   106,   110,   108,
     112,   113,    74,   150,     7,   154,   143,    38,   166,    39,
     171,     7,    59,   147,   163,   171,   160,     7,   171,   177,
     180,    77,    78,    11,     3,   159,   106,   159,   171,   171,
     143,   143,   159,   159,   159,   159,   171,    79,    80,   171,
     160,    37,   107,   107,   168,   111,    37,   144,   173,   171,
     179,   180,   179,     3,    27,    87,    93,   106,   108,   159,
     181,   182,    87,   108,   182,   161,   163,   171,   175,   171,
     175,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   175,   171,
     175,   186,   186,    37,    72,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    92,    93,    94,    95,
      96,   111,   186,   187,   150,   151,     7,   183,     3,     3,
     152,   108,   155,   171,   113,   107,   168,   109,   112,   109,
     113,   107,   113,   178,   107,   107,   177,   107,   107,   107,
     168,   168,   107,   107,   107,   107,   171,   171,   107,   162,
     171,   111,   106,   106,   182,     3,   182,   182,   106,   113,
     182,   182,   107,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   107,     7,   111,   113,   109,     3,   154,   136,   112,
     115,   180,   180,   107,   107,   111,   111,   112,   180,   171,
      86,   107,   109,   182,   182,    86,   109,   124,   109,   141,
     160,     7,   172,   171,   107,   107,   107,   172,    33,   107,
      54,   174,   110,   106,   141,     6,     8,   156,   157,   173,
     113,   111,   107,   157
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   116,   118,   117,   119,   120,   120,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   123,   124,   122,   125,
     125,   126,   126,   126,   126,   128,   127,   129,   130,   132,
     131,   134,   135,   136,   133,   137,   137,   138,   138,   138,
     138,   139,   139,   140,   142,   141,   143,   143,   143,   144,
     144,   144,   144,   144,   145,   145,   145,   145,   146,   146,
     148,   147,   149,   147,   150,   150,   151,   151,   152,   152,
     153,   153,   153,   154,   154,   154,   155,   156,   156,   157,
     157,   158,   158,   158,   159,   160,   160,   161,   161,   162,
     162,   163,   163,   164,   164,   164,   164,   164,   164,   164,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   166,   166,
     167,   168,   168,   169,   169,   170,   170,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   172,   172,
     173,   173,   174,   174,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   176,   176,   176,   176,   177,   177,   178,
     178,   179,   179,   180,   180,   181,   181,   181,   181,   182,
     182,   182,   182,   183,   183,   183,   184,   184,   184,   185,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   187,   187,   188,   188
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     1,     1,     2,     1,     1,     1,
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
       3,     4,     3,     1,     2,     2,     0,     1,     2,     5,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     1,     1,     1,     2,     1,     1
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
#line 145 "promela.y"
                  { *globalSymTab = new symTable("global"); symTable::addPredefinedSym(*globalSymTab); currentSymTab = *globalSymTab; }
#line 2163 "y.tab.cpp"
    break;

  case 4:
#line 150 "promela.y"
                                                                                { std::cout<< "REDUCE: units -> program\n";}
#line 2169 "y.tab.cpp"
    break;

  case 5:
#line 153 "promela.y"
                                                                                { std::cout<< "REDUCE: unit -> units\n"; }
#line 2175 "y.tab.cpp"
    break;

  case 6:
#line 154 "promela.y"
                                                                                { std::cout<< "REDUCE: units unit -> units\n"; }
#line 2181 "y.tab.cpp"
    break;

  case 7:
#line 157 "promela.y"
                                                        { std::cout<< "REDUCE: proc -> unit\n"; *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2187 "y.tab.cpp"
    break;

  case 8:
#line 158 "promela.y"
                                                                { std::cout<< "REDUCE: init -> unit\n"; *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2193 "y.tab.cpp"
    break;

  case 9:
#line 159 "promela.y"
                                                                { assert(false); std::cout << "The 'events' construct is currently not supported."; }
#line 2199 "y.tab.cpp"
    break;

  case 10:
#line 160 "promela.y"
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
#line 2217 "y.tab.cpp"
    break;

  case 11:
#line 173 "promela.y"
                                                                { std::cout << "REDUCE: utype -> unit\n"; *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2223 "y.tab.cpp"
    break;

  case 12:
#line 174 "promela.y"
                                                                                        { std::cout << "REDUCE: mtype -> unit\n"; *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2229 "y.tab.cpp"
    break;

  case 13:
#line 175 "promela.y"
                                                                { std::cout << "Embedded C code is not supported."; }
#line 2235 "y.tab.cpp"
    break;

  case 14:
#line 176 "promela.y"
                                                                { std::cout << "REDUCE: ns -> unit\n"; *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2241 "y.tab.cpp"
    break;

  case 16:
#line 183 "promela.y"
                                                                                                { 
													nameSpace = (yyvsp[0].sVal); savedSymTab = currentSymTab; 
													currentSymTab = currentSymTab->createSubTable(nameSpace); 
													auto predef = new pidSymNode(0, "_pid");
													predef->setMask(symbol::READ_ACCESS | symbol::PREDEFINED); 
													currentSymTab->insert(predef);
												}
#line 2253 "y.tab.cpp"
    break;

  case 17:
#line 191 "promela.y"
                  { currentSymTab = savedSymTab; }
#line 2259 "y.tab.cpp"
    break;

  case 18:
#line 194 "promela.y"
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
#line 2274 "y.tab.cpp"
    break;

  case 19:
#line 206 "promela.y"
                                                                                { std::cout << "REDUCE: -> PROCTYPE proctype\n"; }
#line 2280 "y.tab.cpp"
    break;

  case 20:
#line 207 "promela.y"
                                                                                { std::cout << "Deterministic proctypes are not supported (only useful for simulation)."; }
#line 2286 "y.tab.cpp"
    break;

  case 21:
#line 210 "promela.y"
                                                                        { std::cout << "REDUCE: void -> inst\n"; (yyval.pConstExprVal) = new exprConst(0, nbrLines); }
#line 2292 "y.tab.cpp"
    break;

  case 22:
#line 211 "promela.y"
                                                                                        { std::cout << "REDUCE: ACTIVE -> inst\n"; (yyval.pConstExprVal) = new exprConst(1, nbrLines); }
#line 2298 "y.tab.cpp"
    break;

  case 23:
#line 212 "promela.y"
                                                                        { std::cout << "REDUCE: ACTIVE [ CONST ] -> inst \n"; (yyval.pConstExprVal) = new exprConst((yyvsp[-1].iVal), nbrLines); }
#line 2304 "y.tab.cpp"
    break;

  case 24:
#line 213 "promela.y"
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
#line 2320 "y.tab.cpp"
    break;

  case 25:
#line 227 "promela.y"
                { nameSpace = "init"; }
#line 2326 "y.tab.cpp"
    break;

  case 26:
#line 229 "promela.y"
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
#line 2342 "y.tab.cpp"
    break;

  case 27:
#line 242 "promela.y"
                                                                        { std::cout << "Event sequences (traces) are not supported."; }
#line 2348 "y.tab.cpp"
    break;

  case 28:
#line 245 "promela.y"
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
#line 2363 "y.tab.cpp"
    break;

  case 29:
#line 257 "promela.y"
                                                                        {	mtypeDef = new mtypedefSymNode(nbrLines);	}
#line 2369 "y.tab.cpp"
    break;

  case 30:
#line 258 "promela.y"
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
#line 2386 "y.tab.cpp"
    break;

  case 31:
#line 276 "promela.y"
                         { inInline = true; }
#line 2392 "y.tab.cpp"
    break;

  case 32:
#line 277 "promela.y"
                       { nameSpace = (yyvsp[0].sVal); savedSymTab = currentSymTab; currentSymTab = currentSymTab->createSubTable(nameSpace); }
#line 2398 "y.tab.cpp"
    break;

  case 33:
#line 279 "promela.y"
                  { for(std::string it : params) 
		  		currentSymTab->insert(varSymNode::createSymbol(symbol::T_NA, nbrLines, it));
		    currentSymTab = savedSymTab;
		  }
#line 2407 "y.tab.cpp"
    break;

  case 34:
#line 283 "promela.y"
                                                                                        {
													std::cout<< "REDUCE: INLINE nm ( param_list ) body -> ns\n";
													auto sym = new inlineSymNode((yyvsp[-6].sVal), params, (yyvsp[0].pStmntVal), nbrLines);
													params.clear();
		  											(yyval.pStmntVal) = new inlineDecl(sym, nbrLines);
													(*globalSymTab)->insert(sym);
													inInline = false;
													free((yyvsp[-6].sVal));
												}
#line 2421 "y.tab.cpp"
    break;

  case 44:
#line 311 "promela.y"
                                                                                { 
													savedSymTab = currentSymTab; 
													if(!(currentSymTab = (*globalSymTab)->getSubSymTab(nameSpace)))
														currentSymTab = savedSymTab->createSubTable(nameSpace); 
													nameSpace = "";
												}
#line 2432 "y.tab.cpp"
    break;

  case 45:
#line 318 "promela.y"
                                                                                        { std::cout << "REDUCE: '{' sequence OS '}' -> body\n"; (yyval.pStmntVal) = (yyvsp[-2].pStmntVal); (yyval.pStmntVal)->setLocalSymTab(currentSymTab); currentSymTab->setBlock((yyvsp[-2].pStmntVal)); currentSymTab = savedSymTab; }
#line 2438 "y.tab.cpp"
    break;

  case 46:
#line 321 "promela.y"
                                                                                { std::cout << "REDUCE: step -> sequence\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal);  }
#line 2444 "y.tab.cpp"
    break;

  case 47:
#line 322 "promela.y"
                                                                                { std::cout << "REDUCE: sequence MS step -> sequence\n"; (yyval.pStmntVal) = stmnt::merge((yyvsp[-2].pStmntVal), (yyvsp[0].pStmntVal)); }
#line 2450 "y.tab.cpp"
    break;

  case 48:
#line 323 "promela.y"
                                                                                { std::cout << "REDUCE: sequence step -> sequence\n"; (yyval.pStmntVal) = stmnt::merge((yyvsp[-1].pStmntVal), (yyvsp[0].pStmntVal)); }
#line 2456 "y.tab.cpp"
    break;

  case 49:
#line 326 "promela.y"
                                                                                { 
													assert(declSyms.front()->getType() != symbol::T_MTYPE_DEF); 
												 	(yyval.pStmntVal) = new varDecl(static_cast<std::list<varSymNode*>>(declSyms), nbrLines);
												 	declSyms.clear();
												}
#line 2466 "y.tab.cpp"
    break;

  case 50:
#line 331 "promela.y"
                                                                                { std::cout << "Declarations with labels are not suported."; }
#line 2472 "y.tab.cpp"
    break;

  case 51:
#line 332 "promela.y"
                                                                                { std::cout << "Channel assertions are currently not supported."; }
#line 2478 "y.tab.cpp"
    break;

  case 52:
#line 333 "promela.y"
                                                                                        { std::cout << "REDUCE: stmnt -> step\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2484 "y.tab.cpp"
    break;

  case 53:
#line 334 "promela.y"
                                                                        { std::cout << "Unless statements are currently not supported."; }
#line 2490 "y.tab.cpp"
    break;

  case 55:
#line 343 "promela.y"
                                                                                        { std::cout << "The 'hidden' keyword is not supported."; }
#line 2496 "y.tab.cpp"
    break;

  case 56:
#line 344 "promela.y"
                                                                                        { std::cout << "The 'show' keyword is not supported."; }
#line 2502 "y.tab.cpp"
    break;

  case 57:
#line 345 "promela.y"
                                                                                        { std::cout << "The 'local' keyword is not supported."; }
#line 2508 "y.tab.cpp"
    break;

  case 60:
#line 355 "promela.y"
                   { declType = (yyvsp[0].iType); }
#line 2514 "y.tab.cpp"
    break;

  case 61:
#line 355 "promela.y"
                                                { std::cout << "REDUCE: vis TYPE var_list -> one_decl\n"; }
#line 2520 "y.tab.cpp"
    break;

  case 62:
#line 356 "promela.y"
                            { declType = symbol::T_UTYPE; typeDef = *globalSymTab? static_cast<tdefSymNode*>((*globalSymTab)->lookup((yyvsp[0].sVal))) : nullptr; assert(typeDef); }
#line 2526 "y.tab.cpp"
    break;

  case 63:
#line 356 "promela.y"
                                                                                                                                                                                                        { std::cout << "REDUCE: vis UNAME var_list -> one_decl\n"; free((yyvsp[-2].sVal)); }
#line 2532 "y.tab.cpp"
    break;

  case 64:
#line 359 "promela.y"
                                                                                { std::cout << "REDUCE: one_decl -> decl_list\n"; }
#line 2538 "y.tab.cpp"
    break;

  case 65:
#line 360 "promela.y"
                                                                        { std::cout << "REDUCE: one_decl SEMI decl_list -> decl_lst\n"; }
#line 2544 "y.tab.cpp"
    break;

  case 66:
#line 364 "promela.y"
                                                                        { std::cout << "REDUCE: void -> decl\n"; }
#line 2550 "y.tab.cpp"
    break;

  case 67:
#line 365 "promela.y"
                                                                                        { std::cout << "REDUCE: decl_list -> decl\n"; }
#line 2556 "y.tab.cpp"
    break;

  case 68:
#line 372 "promela.y"
                                                                                { std::cout << "REDUCE: ivar -> var_list\n"; currentSymTab->insert((yyvsp[0].pVarSymVal)); declSyms.push_front((yyvsp[0].pVarSymVal)); }
#line 2562 "y.tab.cpp"
    break;

  case 69:
#line 373 "promela.y"
                                                                                { std::cout << "REDUCE: ivar , var_list -> var_list\n"; currentSymTab->insert((yyvsp[-2].pVarSymVal)); declSyms.push_front((yyvsp[-2].pVarSymVal)); }
#line 2568 "y.tab.cpp"
    break;

  case 70:
#line 376 "promela.y"
                                                                                { 
												  std::cout << "REDUCE: var_decl -> ivar\n"; (yyval.pVarSymVal) = varSymNode::createSymbol(declType, nbrLines, (yyvsp[0].pDataVal).sVal, (yyvsp[0].pDataVal).iVal); 
												  if(declType == symbol::T_UTYPE) { assert(typeDef); static_cast<utypeSymNode*>((yyval.pVarSymVal))->setUType(typeDef); }
												  if((yyvsp[0].pDataVal).sVal) free((yyvsp[0].pDataVal).sVal);
												}
#line 2578 "y.tab.cpp"
    break;

  case 71:
#line 381 "promela.y"
                                                                                { std::cout << "REDUCE: var_decl ASGN expr -> ivar\n"; 
												  (yyval.pVarSymVal) = varSymNode::createSymbol(declType, nbrLines, (yyvsp[-2].pDataVal).sVal, (yyvsp[-2].pDataVal).iVal, (yyvsp[0].pExprVal)); 
												  if(declType == symbol::T_UTYPE) { assert(typeDef); static_cast<utypeSymNode*>((yyval.pVarSymVal))->setUType(typeDef); }
												  if((yyvsp[-2].pDataVal).sVal) free((yyvsp[-2].pDataVal).sVal);
												}
#line 2588 "y.tab.cpp"
    break;

  case 72:
#line 386 "promela.y"
                                                                        { std::cout << "REDUCE: var_decl ASGN ch_init -> ivar\n"; (yyval.pVarSymVal) = new chanSymNode(nbrLines, (yyvsp[-2].pDataVal).sVal, (yyvsp[-2].pDataVal).iVal, (yyvsp[0].pDataVal).iVal, typeLst);	
												  typeLst.clear(); if((yyvsp[-2].pDataVal).sVal) free((yyvsp[-2].pDataVal).sVal); //double free???if($3.sVal) free($3.sVal); 
												}
#line 2596 "y.tab.cpp"
    break;

  case 73:
#line 391 "promela.y"
                                                                                        { }
#line 2602 "y.tab.cpp"
    break;

  case 74:
#line 392 "promela.y"
                                                                                        { params.push_front(std::string((yyvsp[0].sVal))); free((yyvsp[0].sVal)); }
#line 2608 "y.tab.cpp"
    break;

  case 75:
#line 393 "promela.y"
                                                            { params.push_front(std::string((yyvsp[-2].sVal))); free((yyvsp[-2].sVal)); }
#line 2614 "y.tab.cpp"
    break;

  case 76:
#line 397 "promela.y"
                                                        { std::cout << "REDUCE: [ CONST ] OF { typ_list } -> ch_init\n"; (yyval.pDataVal).iVal = (yyvsp[-5].iVal); }
#line 2620 "y.tab.cpp"
    break;

  case 77:
#line 400 "promela.y"
                                                                                { (yyval.pDataVal).sVal = nullptr; (yyval.pDataVal).iType = (yyvsp[0].iType); }
#line 2626 "y.tab.cpp"
    break;

  case 78:
#line 401 "promela.y"
                                                                                        { (yyval.pDataVal).sVal = (yyvsp[0].sVal); (yyval.pDataVal).iType = symbol::T_UTYPE; }
#line 2632 "y.tab.cpp"
    break;

  case 79:
#line 405 "promela.y"
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
#line 2652 "y.tab.cpp"
    break;

  case 80:
#line 420 "promela.y"
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
#line 2672 "y.tab.cpp"
    break;

  case 81:
#line 437 "promela.y"
                                                                                { std::cout << "REDUCE: NAME -> vardcl\n"; (yyval.pDataVal).sVal = (yyvsp[0].sVal); (yyval.pDataVal).iVal = 1; }
#line 2678 "y.tab.cpp"
    break;

  case 82:
#line 438 "promela.y"
                                                                                { std::cout << "The 'unsigned' data type is not supported."; }
#line 2684 "y.tab.cpp"
    break;

  case 83:
#line 439 "promela.y"
                                                                        { std::cout << "REDUCE: NAME [ CONST ] -> vardcl\n"; (yyval.pDataVal).sVal = (yyvsp[-3].sVal); (yyval.pDataVal).iVal = (yyvsp[-1].iVal); }
#line 2690 "y.tab.cpp"
    break;

  case 84:
#line 442 "promela.y"
                                                                                { std::cout << "REDUCE: cmpnd -> varref\n"; (yyval.pExprVarRefVal) = (yyvsp[0].pExprVarRefVal); auto sym = (yyval.pExprVarRefVal)->resolve(currentSymTab); assert(sym || inInline); }
#line 2696 "y.tab.cpp"
    break;

  case 85:
#line 445 "promela.y"
                                                                                { std::cout << "REDUCE: NAME -> pfld\n"; (yyval.pExprVarRefNameVal) = new exprVarRefName((yyvsp[0].sVal), nbrLines); free((yyvsp[0].sVal)); }
#line 2702 "y.tab.cpp"
    break;

  case 86:
#line 446 "promela.y"
                                                                                { std::cout << "REDUCE: NAME [ expr ] -> pfld\n"; (yyval.pExprVarRefNameVal) = new exprVarRefName((yyvsp[-3].sVal), (yyvsp[-1].pExprVal), nbrLines); free((yyvsp[-3].sVal)); }
#line 2708 "y.tab.cpp"
    break;

  case 87:
#line 449 "promela.y"
                                                                                { std::cout << "REDUCE: pfld sfld -> cmpnd\n"; (yyval.pExprVarRefVal) = new exprVarRef(nbrLines, (yyvsp[-1].pExprVarRefNameVal), (yyvsp[0].pExprVarRefVal)); }
#line 2714 "y.tab.cpp"
    break;

  case 88:
#line 450 "promela.y"
                                                                        { std::cout << "REDUCE: CONTEX . pfld sfld -> cmpnd\n"; (yyval.pExprVarRefVal) = new exprVarRef(nbrLines, (yyvsp[-1].pExprVarRefNameVal), (yyvsp[0].pExprVarRefVal)); }
#line 2720 "y.tab.cpp"
    break;

  case 89:
#line 453 "promela.y"
                                                                                        { std::cout << "REDUCE: void -> sfld\n"; (yyval.pExprVarRefVal) = nullptr; }
#line 2726 "y.tab.cpp"
    break;

  case 90:
#line 454 "promela.y"
                                                                        { std::cout << "REDUCE: . cmpnd -> sfld\n"; (yyval.pExprVarRefVal) = (yyvsp[0].pExprVarRefVal);   }
#line 2732 "y.tab.cpp"
    break;

  case 91:
#line 458 "promela.y"
                                                                                { std::cout << "REDUCE: special -> stmnt\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2738 "y.tab.cpp"
    break;

  case 92:
#line 459 "promela.y"
                                                                                        { std::cout << "REDUCE: Stmnt -> stmnt\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2744 "y.tab.cpp"
    break;

  case 93:
#line 462 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntChanRecv((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprRArgListVal), nbrLines); }
#line 2750 "y.tab.cpp"
    break;

  case 94:
#line 463 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntChanSnd((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprArgListVal), nbrLines); }
#line 2756 "y.tab.cpp"
    break;

  case 95:
#line 464 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntIf((yyvsp[-1].pStmntOptVal), (yyvsp[-2].iVal)); }
#line 2762 "y.tab.cpp"
    break;

  case 96:
#line 465 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntDo((yyvsp[-1].pStmntOptVal), (yyvsp[-2].iVal)); }
#line 2768 "y.tab.cpp"
    break;

  case 97:
#line 466 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntBreak(nbrLines); }
#line 2774 "y.tab.cpp"
    break;

  case 98:
#line 467 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntGoto((yyvsp[0].sVal), nbrLines); free((yyvsp[0].sVal)); }
#line 2780 "y.tab.cpp"
    break;

  case 99:
#line 468 "promela.y"
                                                                                { if((yyvsp[0].pStmntVal)->getType() == astNode::E_STMNT_LABEL && static_cast<stmntLabel*>((yyvsp[0].pStmntVal))->getLabelled()->getType() == astNode::E_STMNT_LABEL) 
													std::cout << "Only two labels per state are supported."; 
												  (yyval.pStmntVal) = new stmntLabel((yyvsp[-2].sVal), (yyvsp[0].pStmntVal), nbrLines); free((yyvsp[-2].sVal)); }
#line 2788 "y.tab.cpp"
    break;

  case 100:
#line 472 "promela.y"
                                                                { (yyval.pStmntVal) = new stmntAsgn((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2794 "y.tab.cpp"
    break;

  case 101:
#line 473 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntIncr((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2800 "y.tab.cpp"
    break;

  case 102:
#line 474 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntDecr((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2806 "y.tab.cpp"
    break;

  case 103:
#line 475 "promela.y"
                                                                { (yyval.pStmntVal) = new stmntPrint((yyvsp[-2].sVal), (yyvsp[-1].pExprArgListVal), nbrLines); }
#line 2812 "y.tab.cpp"
    break;

  case 104:
#line 476 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntPrintm((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2818 "y.tab.cpp"
    break;

  case 105:
#line 477 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntPrintm((yyvsp[-1].iVal), nbrLines); }
#line 2824 "y.tab.cpp"
    break;

  case 106:
#line 478 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntAssert((yyvsp[0].pExprVal), nbrLines); }
#line 2830 "y.tab.cpp"
    break;

  case 107:
#line 479 "promela.y"
                                                                                        { std::cout << "Embedded C code is not supported."; }
#line 2836 "y.tab.cpp"
    break;

  case 108:
#line 480 "promela.y"
                                                                        { std::cout << "Sorted send and random receive are not supported."; }
#line 2842 "y.tab.cpp"
    break;

  case 109:
#line 481 "promela.y"
                                                                        { std::cout << "Channel poll operations are not supported."; }
#line 2848 "y.tab.cpp"
    break;

  case 110:
#line 482 "promela.y"
                                                                        { std::cout << "Channel poll operations are not supported."; }
#line 2854 "y.tab.cpp"
    break;

  case 111:
#line 483 "promela.y"
                                                                        { std::cout << "Sorted send and random receive are not supported."; }
#line 2860 "y.tab.cpp"
    break;

  case 112:
#line 484 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntExpr((yyvsp[0].pExprVal), nbrLines); }
#line 2866 "y.tab.cpp"
    break;

  case 113:
#line 485 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntElse(nbrLines); }
#line 2872 "y.tab.cpp"
    break;

  case 114:
#line 486 "promela.y"
                                                                { (yyval.pStmntVal) = new stmntAtomic((yyvsp[-2].pStmntVal), nbrLines); }
#line 2878 "y.tab.cpp"
    break;

  case 115:
#line 487 "promela.y"
                                                                { (yyval.pStmntVal) = new stmntDStep((yyvsp[-2].pStmntVal), nbrLines); }
#line 2884 "y.tab.cpp"
    break;

  case 116:
#line 488 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntSeq((yyvsp[-2].pStmntVal), nbrLines); }
#line 2890 "y.tab.cpp"
    break;

  case 117:
#line 489 "promela.y"
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
#line 2905 "y.tab.cpp"
    break;

  case 118:
#line 501 "promela.y"
                                                                                { (yyval.pStmntOptVal) = new stmntOpt((yyvsp[0].pStmntVal), nbrLines); }
#line 2911 "y.tab.cpp"
    break;

  case 119:
#line 502 "promela.y"
                                                                                { (yyval.pStmntOptVal) = new stmntOpt((yyvsp[-1].pStmntVal), (yyvsp[0].pStmntOptVal), nbrLines); }
#line 2917 "y.tab.cpp"
    break;

  case 120:
#line 505 "promela.y"
                                                                        { (yyval.pStmntVal) = (yyvsp[-1].pStmntVal); }
#line 2923 "y.tab.cpp"
    break;

  case 122:
#line 519 "promela.y"
                                        { /* redundant semi at end of sequence */ }
#line 2929 "y.tab.cpp"
    break;

  case 123:
#line 522 "promela.y"
                                        { /* at least one semi-colon */ }
#line 2935 "y.tab.cpp"
    break;

  case 124:
#line 523 "promela.y"
                                        { /* but more are okay too   */ }
#line 2941 "y.tab.cpp"
    break;

  case 125:
#line 526 "promela.y"
                                                                                { (yyval.sVal) = (yyvsp[0].sVal); }
#line 2947 "y.tab.cpp"
    break;

  case 126:
#line 527 "promela.y"
                                                                                        { (yyval.sVal) = (yyvsp[0].sVal); }
#line 2953 "y.tab.cpp"
    break;

  case 127:
#line 530 "promela.y"
                                                                        { (yyval.pExprVal) = new exprPar		((yyvsp[-1].pExprVal), nbrLines); }
#line 2959 "y.tab.cpp"
    break;

  case 128:
#line 531 "promela.y"
                                                                                { (yyval.pExprVal) = new exprPlus		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2965 "y.tab.cpp"
    break;

  case 129:
#line 532 "promela.y"
                                                                                { (yyval.pExprVal) = new exprMinus	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2971 "y.tab.cpp"
    break;

  case 130:
#line 533 "promela.y"
                                                                                { (yyval.pExprVal) = new exprTimes	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2977 "y.tab.cpp"
    break;

  case 131:
#line 534 "promela.y"
                                                                                { (yyval.pExprVal) = new exprDiv		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2983 "y.tab.cpp"
    break;

  case 132:
#line 535 "promela.y"
                                                                                { (yyval.pExprVal) = new exprMod		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2989 "y.tab.cpp"
    break;

  case 133:
#line 536 "promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2995 "y.tab.cpp"
    break;

  case 134:
#line 537 "promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwXor	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3001 "y.tab.cpp"
    break;

  case 135:
#line 538 "promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3007 "y.tab.cpp"
    break;

  case 136:
#line 539 "promela.y"
                                                                                { (yyval.pExprVal) = new exprGT		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3013 "y.tab.cpp"
    break;

  case 137:
#line 540 "promela.y"
                                                                                { (yyval.pExprVal) = new exprLT		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3019 "y.tab.cpp"
    break;

  case 138:
#line 541 "promela.y"
                                                                                { (yyval.pExprVal) = new exprGE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3025 "y.tab.cpp"
    break;

  case 139:
#line 542 "promela.y"
                                                                                { (yyval.pExprVal) = new exprLE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3031 "y.tab.cpp"
    break;

  case 140:
#line 543 "promela.y"
                                                                                { (yyval.pExprVal) = new exprEQ		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3037 "y.tab.cpp"
    break;

  case 141:
#line 544 "promela.y"
                                                                                { (yyval.pExprVal) = new exprNE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3043 "y.tab.cpp"
    break;

  case 142:
#line 545 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3049 "y.tab.cpp"
    break;

  case 143:
#line 546 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3055 "y.tab.cpp"
    break;

  case 144:
#line 547 "promela.y"
                                                                                { (yyval.pExprVal) = new exprLShift	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3061 "y.tab.cpp"
    break;

  case 145:
#line 548 "promela.y"
                                                                                { (yyval.pExprVal) = new exprRShift	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3067 "y.tab.cpp"
    break;

  case 146:
#line 549 "promela.y"
                                                                        { (yyval.pExprVal) = new exprCount	((yyvsp[-1].pExprVal), nbrLines); }
#line 3073 "y.tab.cpp"
    break;

  case 147:
#line 550 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprBitwNeg	((yyvsp[0].pExprVal), nbrLines); }
#line 3079 "y.tab.cpp"
    break;

  case 148:
#line 551 "promela.y"
                                                                        { 	if((yyvsp[0].pExprVal)->getType() != astNode::E_EXPR_CONST) 
														(yyval.pExprVal) = new exprUMin((yyvsp[0].pExprVal), nbrLines);
													else {
														exprConst* tmp = dynamic_cast<exprConst*>((yyvsp[0].pExprVal));
														(yyval.pExprVal) = new exprConst(- tmp->getCstValue(), nbrLines);
														delete tmp;
													}
												}
#line 3092 "y.tab.cpp"
    break;

  case 149:
#line 559 "promela.y"
                                                                        { (yyval.pExprVal) = new exprNeg	((yyvsp[0].pExprVal), nbrLines); }
#line 3098 "y.tab.cpp"
    break;

  case 150:
#line 560 "promela.y"
                                                                { (yyval.pExprVal) = new exprCond	((yyvsp[-5].pExprVal), (yyvsp[-3].pExprVal), (yyvsp[-1].pExprVal), nbrLines); }
#line 3104 "y.tab.cpp"
    break;

  case 151:
#line 561 "promela.y"
                                                        { auto run = new exprRun ((yyvsp[-4].sVal), (yyvsp[-2].pExprArgListVal), nbrLines);
												  (yyval.pExprVal) = run;
												  auto procSym = run->resolve(*globalSymTab); 
												  assert(procSym); free((yyvsp[-4].sVal)); 
												}
#line 3114 "y.tab.cpp"
    break;

  case 152:
#line 566 "promela.y"
                                                                        { (yyval.pExprVal) = new exprLen	((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3120 "y.tab.cpp"
    break;

  case 153:
#line 567 "promela.y"
                                                                        { std::cout << "The enabled keyword is not supported."; }
#line 3126 "y.tab.cpp"
    break;

  case 154:
#line 568 "promela.y"
                                                                        { std::cout << "Construct not supported."; /* Unclear */ }
#line 3132 "y.tab.cpp"
    break;

  case 155:
#line 569 "promela.y"
                                                                { std::cout << "Sorted send and random receive are not supported."; }
#line 3138 "y.tab.cpp"
    break;

  case 156:
#line 570 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprVar	((yyvsp[0].pExprVarRefVal), nbrLines); }
#line 3144 "y.tab.cpp"
    break;

  case 157:
#line 571 "promela.y"
                                                                                        { std::cout << "Embedded C code is not supported."; }
#line 3150 "y.tab.cpp"
    break;

  case 158:
#line 572 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprConst((yyvsp[0].iVal), nbrLines); }
#line 3156 "y.tab.cpp"
    break;

  case 159:
#line 573 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprTrue	(nbrLines); }
#line 3162 "y.tab.cpp"
    break;

  case 160:
#line 574 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprFalse(nbrLines); }
#line 3168 "y.tab.cpp"
    break;

  case 161:
#line 575 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprTimeout(nbrLines); }
#line 3174 "y.tab.cpp"
    break;

  case 162:
#line 576 "promela.y"
                                                                                { std::cout << "The 'np_' variable is not supported."; }
#line 3180 "y.tab.cpp"
    break;

  case 163:
#line 577 "promela.y"
                                                                        { std::cout << "The 'pc_value()' construct is not supported."; }
#line 3186 "y.tab.cpp"
    break;

  case 164:
#line 578 "promela.y"
                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 3192 "y.tab.cpp"
    break;

  case 165:
#line 579 "promela.y"
                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 3198 "y.tab.cpp"
    break;

  case 166:
#line 580 "promela.y"
                                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 3204 "y.tab.cpp"
    break;

  case 167:
#line 581 "promela.y"
                                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 3210 "y.tab.cpp"
    break;

  case 169:
#line 585 "promela.y"
                                                                                { assert(false); std::cout << "The 'priority' construct is related to simulation and not supported."; }
#line 3216 "y.tab.cpp"
    break;

  case 170:
#line 588 "promela.y"
                                                                                { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 3222 "y.tab.cpp"
    break;

  case 171:
#line 589 "promela.y"
                                                                                        { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 3228 "y.tab.cpp"
    break;

  case 173:
#line 593 "promela.y"
                                                                { assert(false); std::cout << "The 'provided' construct is currently not supported."; }
#line 3234 "y.tab.cpp"
    break;

  case 174:
#line 598 "promela.y"
                                                                                { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 3240 "y.tab.cpp"
    break;

  case 175:
#line 599 "promela.y"
                                                                                { (yyval.pExprVal) = new exprPar	((yyvsp[-1].pExprVal), nbrLines); }
#line 3246 "y.tab.cpp"
    break;

  case 176:
#line 600 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3252 "y.tab.cpp"
    break;

  case 177:
#line 601 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3258 "y.tab.cpp"
    break;

  case 178:
#line 602 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3264 "y.tab.cpp"
    break;

  case 179:
#line 603 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3270 "y.tab.cpp"
    break;

  case 180:
#line 604 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3276 "y.tab.cpp"
    break;

  case 181:
#line 605 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3282 "y.tab.cpp"
    break;

  case 182:
#line 606 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprSkip	(nbrLines); }
#line 3288 "y.tab.cpp"
    break;

  case 183:
#line 609 "promela.y"
                                                                { (yyval.pExprVal) = new exprFull	((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3294 "y.tab.cpp"
    break;

  case 184:
#line 610 "promela.y"
                                                                        { (yyval.pExprVal) = new exprNFull((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3300 "y.tab.cpp"
    break;

  case 185:
#line 611 "promela.y"
                                                                        { (yyval.pExprVal) = new exprEmpty((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3306 "y.tab.cpp"
    break;

  case 186:
#line 612 "promela.y"
                                                                        { (yyval.pExprVal) = new exprNEmpty((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3312 "y.tab.cpp"
    break;

  case 187:
#line 616 "promela.y"
                                                { (yyval.pExprArgListVal) = nullptr; }
#line 3318 "y.tab.cpp"
    break;

  case 188:
#line 617 "promela.y"
                                                                                        { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3324 "y.tab.cpp"
    break;

  case 189:
#line 621 "promela.y"
                                                                        { (yyval.pExprArgListVal) = nullptr; }
#line 3330 "y.tab.cpp"
    break;

  case 190:
#line 622 "promela.y"
                                                                                        { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3336 "y.tab.cpp"
    break;

  case 191:
#line 626 "promela.y"
                                                                                { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3342 "y.tab.cpp"
    break;

  case 192:
#line 627 "promela.y"
                                                                                { assert(false); }
#line 3348 "y.tab.cpp"
    break;

  case 193:
#line 630 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList(new exprArg((yyvsp[0].pExprVal), nbrLines), nbrLines); }
#line 3354 "y.tab.cpp"
    break;

  case 194:
#line 631 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList(new exprArg((yyvsp[-2].pExprVal), nbrLines), (yyvsp[0].pExprArgListVal), nbrLines); }
#line 3360 "y.tab.cpp"
    break;

  case 195:
#line 634 "promela.y"
                                                                                { (yyval.pExprRArgVal) = new exprRArgVar((yyvsp[0].pExprVarRefVal), nbrLines); }
#line 3366 "y.tab.cpp"
    break;

  case 196:
#line 635 "promela.y"
                                                                                { (yyval.pExprRArgVal) = new exprRArgEval((yyvsp[-1].pExprVal), nbrLines); }
#line 3372 "y.tab.cpp"
    break;

  case 197:
#line 636 "promela.y"
                                                                                        { (yyval.pExprRArgVal) = new exprRArgConst(new exprConst((yyvsp[0].iVal), nbrLines), nbrLines); }
#line 3378 "y.tab.cpp"
    break;

  case 198:
#line 637 "promela.y"
                                                                        { (yyval.pExprRArgVal) = new exprRArgConst(new exprConst(-(yyvsp[0].iVal), nbrLines), nbrLines); }
#line 3384 "y.tab.cpp"
    break;

  case 199:
#line 641 "promela.y"
                                                                                { (yyval.pExprRArgListVal) = new exprRArgList((yyvsp[0].pExprRArgVal), nbrLines); }
#line 3390 "y.tab.cpp"
    break;

  case 200:
#line 642 "promela.y"
                                                                                { (yyval.pExprRArgListVal) = new exprRArgList((yyvsp[-2].pExprRArgVal), (yyvsp[0].pExprRArgListVal), nbrLines); }
#line 3396 "y.tab.cpp"
    break;

  case 201:
#line 643 "promela.y"
                                                                        { (yyval.pExprRArgListVal) = new exprRArgList((yyvsp[-3].pExprRArgVal), (yyvsp[-1].pExprRArgListVal), nbrLines); }
#line 3402 "y.tab.cpp"
    break;

  case 202:
#line 644 "promela.y"
                                                                                { (yyval.pExprRArgListVal) = (yyvsp[-1].pExprRArgListVal); }
#line 3408 "y.tab.cpp"
    break;

  case 203:
#line 647 "promela.y"
                                                                                { std::cout << "REDUCE: NAME -> nlst\n"; cmtypeSymNode* sym = new cmtypeSymNode(nbrLines, mtypeDef, (yyvsp[0].sVal), mtypeId++); (*globalSymTab)->insert(sym); free((yyvsp[0].sVal)); }
#line 3414 "y.tab.cpp"
    break;

  case 204:
#line 648 "promela.y"
                                                                                        { std::cout << "REDUCE: nlst NAME -> NAME\n"; cmtypeSymNode* sym = new cmtypeSymNode(nbrLines, mtypeDef, (yyvsp[0].sVal), mtypeId++); (*globalSymTab)->insert(sym); free((yyvsp[0].sVal)); }
#line 3420 "y.tab.cpp"
    break;

  case 205:
#line 649 "promela.y"
                                                                { std::cout << "REDUCE: nlst , -> nlst\n"; }
#line 3426 "y.tab.cpp"
    break;


#line 3430 "y.tab.cpp"

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
#line 694 "promela.y"

