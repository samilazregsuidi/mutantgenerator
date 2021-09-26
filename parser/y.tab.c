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

#include "symbols.h"
#include "expression.h"

#include "y.tab.h"

#define YYDEBUG 1

#ifdef CPP
extern "C" 
#endif
int yylex(YYSTYPE * yylval_param, symTabNode** globalSymTab);

extern int nbrLines;

int yyerror (symTabNode** globalSymTab, stmnt** program, const char* msg){
	fprintf(stderr, "Syntax error on line %d: '%s'.\n", nbrLines, msg);
	exit(1);
}



#line 109 "y.tab.c"

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
#line 47 "promela.y"
 
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
	
	class symTabNode*		pSymTabVal;
	class varSymNode*		pVarSymVal;
	class tdefSymNode*		pTdefSymVal;
	class mtypedefSymNode*	pTypedefSymVal;
	class mtypeList*		pMTypeListVal;
	
	enum symTabNode::Type   iType;

#line 373 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (symTabNode** globalSymTab, stmnt** program);

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
#define YYFINAL  40
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1371

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  114
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  192
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  390

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
       0,   132,   132,   137,   140,   141,   144,   145,   146,   147,
     157,   158,   159,   160,   164,   179,   180,   183,   184,   185,
     186,   199,   211,   214,   225,   226,   229,   232,   233,   236,
     237,   238,   239,   242,   243,   246,   249,   252,   253,   256,
     260,   261,   262,   263,   271,   272,   273,   274,   277,   278,
     284,   322,   337,   349,   350,   354,   355,   362,   363,   366,
     367,   368,   371,   374,   375,   376,   379,   382,   383,   386,
     387,   390,   391,   395,   396,   399,   400,   401,   402,   403,
     404,   405,   409,   410,   411,   412,   413,   414,   415,   416,
     417,   418,   419,   420,   421,   422,   423,   424,   425,   426,
     429,   430,   433,   446,   447,   450,   451,   454,   455,   458,
     459,   460,   461,   462,   463,   464,   465,   466,   467,   468,
     469,   470,   471,   472,   473,   474,   475,   476,   477,   478,
     479,   487,   488,   489,   490,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   510,   511,   514,   515,   518,   519,   524,   525,   526,
     527,   528,   529,   530,   531,   532,   535,   536,   537,   538,
     541,   542,   546,   556,   571,   572,   576,   577,   581,   582,
     585,   586,   589,   590,   591,   592,   596,   597,   598,   599,
     602,   603,   604
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
  "'@'", "$accept", "start_parsing", "program", "units", "unit", "proc",
  "proctype", "inst", "init", "events", "utype", "nm", "ns", "c_fcts",
  "cstate", "ccode", "cexpr", "body", "sequence", "step", "vis", "asgn",
  "one_decl", "decl_lst", "decl", "var_list", "ivar", "ch_init", "vardcl",
  "varref", "pfld", "cmpnd", "sfld", "stmnt", "Special", "Stmnt",
  "options", "option", "OS", "MS", "aname", "expr", "Opt_priority",
  "full_expr", "Opt_enabler", "Expr", "Probe", "basetype", "typ_list",
  "args", "prargs", "margs", "arg", "rarg", "rargs", "nlst", YY_NULLPTR
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

#define YYPACT_NINF (-307)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-105)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     962,  -307,  -307,     9,    61,    77,    51,  -307,    -7,  -307,
    -307,  -307,    56,   106,   173,  -307,   936,  -307,  -307,    18,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,    75,  -307,   165,
     172,    80,  -307,  -307,   104,    83,   543,  -307,   207,    56,
    -307,  -307,  -307,  -307,   221,     5,   222,   203,   225,    70,
     812,   131,   132,  -307,   200,   200,   -15,   -53,   137,  -307,
    -307,  -307,   755,   139,   141,  -307,    97,   144,   146,   149,
     239,  -307,  -307,   147,   150,  -307,  -307,   155,   156,   167,
     170,   812,   812,   812,   177,   171,   755,   543,  -307,  -307,
     217,  -307,  -307,   -31,   184,  -307,   238,  -307,  -307,  1259,
    -307,   129,  -307,  -307,  -307,   194,    41,  -307,   191,  -307,
     189,   233,  -307,  -307,  -307,   265,   199,   205,   812,   142,
     983,   204,  -307,  -307,  -307,   543,   274,   200,   279,   812,
     339,   812,   306,   312,   812,  -307,   309,    12,  -307,  -307,
      40,     2,   812,   812,  -307,   543,   543,     2,     2,     2,
       2,  -307,  -307,  -307,   812,   306,   783,   -42,   217,   -22,
     214,   441,   755,   812,   812,   230,   277,  -307,  -307,     2,
    -307,   645,   755,   755,   812,   812,   812,   812,   812,   812,
     812,   812,   812,   812,   812,   812,   812,   812,   812,   812,
     755,   755,   -29,   322,   323,   320,   222,   702,    70,  -307,
     841,   223,   224,   812,   812,   812,  -307,   217,  -307,  -307,
    -307,  1052,    43,  -307,  -307,  -307,  1083,  -307,  -307,   227,
     226,   234,   235,   812,     2,   236,  1114,  1143,   217,   217,
     240,   242,   256,   261,  1172,   184,   812,  -307,  -307,   219,
    -307,  -307,  -307,  -307,   948,  -307,  -307,  -307,  -307,   231,
      71,   366,    71,    71,  -307,   -80,  -307,    71,    71,  -307,
    -307,  -307,   335,   260,   538,  -307,   998,   419,   110,   201,
     201,   311,   311,   311,   311,   175,   175,    86,    86,  -307,
    -307,  -307,   335,   260,   538,  -307,  -307,   266,   263,  -307,
    -307,    -1,  -307,   369,  -307,  1277,  -307,   437,   538,  -307,
    -307,  -307,   645,    50,   206,   812,   271,  -307,  -307,   272,
     280,  -307,  -307,  -307,   270,   283,  -307,  -307,  -307,  -307,
    -307,  -307,  1018,  -307,   812,   812,   302,  -307,   288,   281,
      71,    71,   324,   299,   106,  -307,  -307,  -307,  -307,   300,
     306,   402,   -25,  -307,  -307,  -307,   106,   307,  -307,  -307,
     812,   305,  1201,  -307,  -307,  -307,   326,  -307,  -307,  -307,
     378,   400,  -307,  -307,   -47,  -307,   812,  1230,  -307,  -307,
    -307,   330,    56,   327,   332,  -307,   755,  -307,   176,   106,
     333,  -307,  -307,   331,   340,  -307,  -307,   176,  -307,  -307
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      17,    33,    34,     0,     0,     0,     0,    13,    18,    45,
      46,    47,     0,   151,     0,     2,    17,     4,     6,     0,
       7,     8,    10,    12,    11,    28,    27,     0,     9,     0,
       0,     0,    24,    25,     0,     0,    44,    22,     0,     0,
       1,     5,    15,    16,     0,    48,     0,    29,    30,    44,
     174,     0,     0,   141,     0,     0,    67,     0,     0,   142,
     143,   165,     0,     0,     0,    35,     0,     0,     0,     0,
       0,    79,    95,     0,     0,   144,   145,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    44,    89,   140,
     103,    37,    39,   139,    71,    66,    42,    73,    74,   153,
      94,   154,   157,   152,    21,     0,    63,    49,     0,    50,
      57,    59,    51,    31,    32,    53,     0,    67,     0,   139,
     180,     0,   175,    19,    20,    44,     0,   100,     0,     0,
      44,     0,     0,     0,   174,    88,     0,     0,   107,   108,
       0,     0,     0,     0,    80,    44,    44,     0,     0,     0,
       0,   131,   130,   129,     0,     0,     0,     0,   103,   105,
       0,    44,     0,     0,     0,     0,     0,    83,    84,     0,
      69,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    44,     0,     0,     0,     0,     0,    44,    23,
       0,     0,     0,     0,     0,     0,    26,   103,    77,   101,
      78,     0,    67,    41,    40,    81,     0,   150,   149,     0,
     176,     0,     0,   174,     0,     0,     0,     0,   103,   103,
       0,     0,     0,     0,     0,    71,     0,   109,   158,     0,
      36,   106,    38,    82,   180,    76,   178,    93,   184,     0,
       0,     0,     0,     0,   182,   186,    75,     0,     0,    90,
      72,    43,   125,   164,   124,   163,   117,   116,   115,   122,
     123,   118,   119,   120,   121,   126,   127,   110,   111,   112,
     113,   114,   162,   161,   160,   159,    56,     0,     0,    64,
     190,     0,    58,     0,    61,    60,    54,   125,   124,   181,
     102,    68,     0,     0,     0,     0,     0,    87,    86,     0,
       0,   135,   136,   146,     0,     0,   166,   168,   167,   169,
     128,    70,     0,    98,     0,     0,     0,   185,     0,     0,
       0,     0,     0,     0,   151,    65,   191,    52,   192,     0,
       0,     0,   139,    99,   177,    85,   151,     0,    96,    97,
       0,     0,     0,    91,   189,   137,     0,   187,    92,   138,
     155,     0,   148,   147,     0,   133,   174,     0,   179,   183,
     188,     0,     0,     0,     0,   132,     0,    14,     0,   151,
       0,   170,   171,   172,     0,   134,   156,     0,    62,   173
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -307,  -307,  -307,  -307,   425,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,    39,  -307,   -39,   -57,   291,
    -307,  -307,    13,  -144,  -307,   -38,  -307,  -307,  -307,    20,
    -128,   284,   228,  -125,  -307,   160,   -48,  -307,  -132,  -307,
    -307,   -49,  -306,   -60,  -307,   -72,  -307,  -307,    81,  -131,
    -307,   308,  -153,  -307,  -141,  -307
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    14,    15,    16,    17,    18,    44,    19,    20,    21,
      22,    34,    23,    24,    25,    88,    89,    37,    90,    91,
      27,   108,    92,   116,   287,   109,   110,   294,   111,   119,
      94,    95,   170,    96,    97,    98,   126,   127,   160,   161,
     140,    99,    39,   100,   372,   101,   102,   383,   384,   121,
     306,   245,   122,   255,   256,   291
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     104,   120,   135,   219,   217,   215,   336,   128,   112,   117,
     246,   246,   106,    28,   157,   221,  -104,  -104,  -104,   117,
      29,     9,    10,    11,   330,   259,   239,   235,   360,    28,
     158,   331,   151,   152,   153,   190,   191,   156,   250,    26,
     365,   162,   163,   164,   165,   166,   261,   162,   286,   164,
     364,   166,   299,   131,   296,    26,    93,   132,    32,   253,
     133,    33,   115,   238,   167,   168,    42,    43,   207,   200,
     167,   168,    30,   385,   248,   300,   -55,   107,   117,   209,
     211,    45,   216,    46,    31,   120,    51,  -104,   228,   229,
      52,   129,   309,   226,   227,   130,   314,   315,   249,    35,
     263,   265,   243,    85,   138,   234,   139,    93,   337,   326,
     338,   328,   329,    85,   244,   244,   332,   333,   283,   285,
       9,    10,    11,   262,   264,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   284,   214,   223,    93,   224,   193,   295,   129,
      93,   194,   344,   302,   297,   298,   120,   222,   292,    38,
     340,   225,   251,   341,    36,    93,    93,   230,   231,   232,
     233,   351,    85,    40,   120,   252,    47,   215,   187,   188,
     189,    93,   381,    48,   382,   254,   254,   322,    49,   356,
     357,    93,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   115,   190,   191,    50,    53,
     103,   115,   362,   117,   113,    57,    58,   201,   202,    59,
      60,    61,    62,    63,    64,     1,     2,    65,   105,   106,
      66,    67,    68,   248,    69,   374,   114,   117,   123,   124,
     125,   134,    72,   136,   310,   137,   144,    73,   141,    74,
     142,    75,    76,   143,   159,   145,   120,   249,   146,   147,
     148,    77,    78,    79,    80,   185,   186,   187,   188,   189,
     254,   149,   254,   254,   150,   120,   352,   254,   254,    81,
     248,   154,   171,   155,   117,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   169,    82,   192,   195,
     196,   367,   198,    83,   249,   197,    84,    85,   199,   206,
      86,   129,   208,   117,    87,   250,   380,   120,   210,   218,
     220,   251,    93,   240,   342,   288,   289,   290,   323,   253,
     258,    85,   304,   377,   252,   325,   253,   305,   191,   307,
     308,   311,    53,    54,    55,   316,   212,   317,    57,    58,
     254,   254,    59,    60,    61,    62,    63,    64,     1,     2,
      65,   318,   257,    66,    67,    68,   319,    69,   251,   327,
     335,   334,   339,    70,    71,    72,   345,   346,    85,   348,
      73,   252,    74,   258,    75,    76,   353,   347,   355,     9,
      10,    11,   349,   354,    77,    78,    79,    80,   213,   183,
     184,   185,   186,   187,   188,   189,   359,   361,   358,   363,
     368,   366,    81,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
      82,   370,   371,   373,   376,   378,    83,   379,   386,    84,
      85,    41,   387,    86,    53,    54,    55,    87,    56,   388,
      57,    58,   242,   260,    59,    60,    61,    62,    63,    64,
       1,     2,    65,   321,   343,    66,    67,    68,   389,    69,
       0,     0,   247,     0,     0,    70,    71,    72,   241,     0,
       0,     0,    73,     0,    74,     0,    75,    76,     0,     0,
       0,     9,    10,    11,     0,     0,    77,    78,    79,    80,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,    81,   204,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,    82,     0,     0,     0,     0,     0,    83,     0,
       0,    84,    85,     0,     0,    86,    53,    54,    55,    87,
      56,     0,    57,    58,     0,     0,    59,    60,    61,    62,
      63,    64,     1,     2,    65,     0,     0,    66,    67,    68,
       0,    69,     0,     0,     0,     0,     0,    70,    71,    72,
       0,     0,     0,     0,    73,     0,    74,     0,    75,    76,
       0,     0,     0,     9,    10,    11,     0,     0,    77,    78,
      79,    80,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    81,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,     0,    82,     0,     0,     0,     0,     0,
      83,     0,     0,    84,    85,     0,     0,    86,    53,    54,
      55,    87,   212,     0,    57,    58,     0,     0,    59,    60,
      61,    62,    63,    64,     1,     2,    65,     0,     0,    66,
      67,    68,     0,    69,     0,     0,     0,     0,     0,    70,
      71,    72,     0,     0,     0,     0,    73,     0,    74,     0,
      75,    76,     0,     0,     0,     0,     0,     0,     0,     0,
      77,    78,    79,    80,     0,    53,     0,     0,     0,   117,
       0,    57,     0,     0,     0,    59,    60,     0,    81,     0,
       0,     0,     0,    65,     0,     0,    66,    67,    68,     0,
      69,     0,     0,     0,     0,     0,    82,     0,     0,     0,
       0,     0,    83,     0,     0,    84,    85,    75,    76,    86,
       0,     0,     0,    87,     0,     0,     0,     0,    53,     0,
       0,     0,   117,     0,    57,     0,     0,     0,    59,    60,
      61,     0,     0,     0,     0,    81,    65,     0,     0,    66,
      67,    68,     0,    69,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    82,     0,     0,     0,     0,     0,    83,
      75,    76,    84,    85,     0,     0,   118,     0,   293,     0,
      77,    78,    79,    80,     0,    53,     0,     0,     0,   117,
     236,    57,     0,     0,     0,    59,    60,     0,    81,     0,
       0,     0,     0,    65,     0,     0,    66,    67,    68,     0,
      69,     0,     0,     0,     0,     0,    82,     0,     0,     0,
       0,     0,    83,     0,     0,    84,    85,    75,    76,    86,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   236,     0,
       0,     0,     0,     0,     0,    81,     0,     0,   237,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    82,     0,     0,     0,     0,     0,    83,
       0,     0,    84,    85,     0,     0,   118,     0,   203,   204,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,    -3,     0,     0,     0,
       0,     0,   -44,     0,   -44,     0,   237,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     2,     0,     3,     4,
       0,     0,     0,     0,     0,     5,     0,     6,   -44,     0,
     -44,     0,     0,     7,     0,     0,     0,     0,     0,     0,
       0,     1,     2,     8,     3,     4,     9,    10,    11,     0,
       0,     5,     0,     6,     0,     0,     0,    12,    13,     7,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     8,
       0,     0,     9,    10,    11,     0,     0,     0,     0,     0,
       0,     0,     0,    12,    13,   203,   204,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   324,     0,     0,     0,     0,     0,     0,   205,
     203,   204,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,     0,   205,   203,   204,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   350,   203,
     204,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   301,
     203,   204,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     303,   203,   204,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   312,
     203,   204,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   313,   203,
     204,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   320,   203,   204,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   369,   203,   204,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   375,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   203,   204,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189
};

static const yytype_int16 yycheck[] =
{
      39,    50,    62,   134,   132,   130,     7,    55,    46,     7,
     163,   164,     7,     0,    86,     3,    38,    39,    40,     7,
      11,    50,    51,    52,   104,   166,   158,   155,   334,    16,
      87,   111,    81,    82,    83,    77,    78,    86,    85,     0,
     346,    72,    73,    74,    75,    76,   171,    72,   192,    74,
      75,    76,   205,   106,   198,    16,    36,   110,     7,   106,
     113,    10,    49,   105,    95,    96,    48,    49,   125,   118,
      95,    96,    11,   379,     3,   207,   105,    72,     7,   127,
     129,     6,   131,     8,     7,   134,     3,   109,   145,   146,
       7,   106,   223,   142,   143,   110,   228,   229,    27,   106,
     172,   173,   162,   101,     7,   154,     9,    87,   109,   250,
     111,   252,   253,   101,   163,   164,   257,   258,   190,   191,
      50,    51,    52,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   130,   104,   125,   106,   106,   197,   106,
     130,   110,   305,   110,   203,   204,   205,   137,   196,    53,
     110,   141,    91,   113,   108,   145,   146,   147,   148,   149,
     150,   324,   101,     0,   223,   104,    11,   302,    92,    93,
      94,   161,     6,    11,     8,   165,   166,   236,   108,   330,
     331,   171,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,   192,    77,    78,   104,     3,
       3,   198,   340,     7,    11,     9,    10,    75,    76,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     7,     7,
      24,    25,    26,     3,    28,   366,    11,     7,   107,   107,
      40,   104,    36,   104,   224,   104,     7,    41,   104,    43,
     104,    45,    46,   104,    37,   108,   305,    27,   108,   104,
     104,    55,    56,    57,    58,    90,    91,    92,    93,    94,
     250,   104,   252,   253,   104,   324,   325,   257,   258,    73,
       3,   104,    44,   112,     7,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,   112,    91,   104,   108,
     111,   350,    37,    97,    27,    72,   100,   101,   109,   105,
     104,   106,    38,     7,   108,    85,   376,   366,    39,     7,
      11,    91,   302,   109,   304,     3,     3,     7,   109,   106,
     106,   101,   105,   372,   104,   104,   106,   111,    78,   105,
     105,   105,     3,     4,     5,   105,     7,   105,     9,    10,
     330,   331,    13,    14,    15,    16,    17,    18,    19,    20,
      21,   105,    85,    24,    25,    26,   105,    28,    91,     3,
     107,   105,     3,    34,    35,    36,   105,   105,   101,   109,
      41,   104,    43,   106,    45,    46,    84,   107,   107,    50,
      51,    52,   109,   105,    55,    56,    57,    58,    59,    88,
      89,    90,    91,    92,    93,    94,   107,   107,    84,     7,
     105,   104,    73,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      91,   105,    54,    33,   104,   108,    97,   105,   105,   100,
     101,    16,   111,   104,     3,     4,     5,   108,     7,   109,
       9,    10,   161,   169,    13,    14,    15,    16,    17,    18,
      19,    20,    21,   235,   304,    24,    25,    26,   387,    28,
      -1,    -1,   164,    -1,    -1,    34,    35,    36,    37,    -1,
      -1,    -1,    41,    -1,    43,    -1,    45,    46,    -1,    -1,
      -1,    50,    51,    52,    -1,    -1,    55,    56,    57,    58,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    73,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    91,    -1,    -1,    -1,    -1,    -1,    97,    -1,
      -1,   100,   101,    -1,    -1,   104,     3,     4,     5,   108,
       7,    -1,     9,    10,    -1,    -1,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    24,    25,    26,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      -1,    -1,    -1,    -1,    41,    -1,    43,    -1,    45,    46,
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
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    56,    57,    58,    -1,     3,    -1,    -1,    -1,     7,
      -1,     9,    -1,    -1,    -1,    13,    14,    -1,    73,    -1,
      -1,    -1,    -1,    21,    -1,    -1,    24,    25,    26,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,
      -1,    -1,    97,    -1,    -1,   100,   101,    45,    46,   104,
      -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,     3,    -1,
      -1,    -1,     7,    -1,     9,    -1,    -1,    -1,    13,    14,
      15,    -1,    -1,    -1,    -1,    73,    21,    -1,    -1,    24,
      25,    26,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,    97,
      45,    46,   100,   101,    -1,    -1,   104,    -1,   106,    -1,
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
      89,    90,    91,    92,    93,    94,     0,    -1,    -1,    -1,
      -1,    -1,     6,    -1,     8,    -1,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    20,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    31,     6,    -1,
       8,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    19,    20,    47,    22,    23,    50,    51,    52,    -1,
      -1,    29,    -1,    31,    -1,    -1,    -1,    61,    62,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      -1,    -1,    50,    51,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    62,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   104,    -1,    -1,    -1,    -1,    -1,    -1,   111,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    -1,   111,    77,    78,    79,    80,    81,
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
       0,    19,    20,    22,    23,    29,    31,    37,    47,    50,
      51,    52,    61,    62,   115,   116,   117,   118,   119,   121,
     122,   123,   124,   126,   127,   128,   129,   134,   136,    11,
      11,     7,     7,    10,   125,   106,   108,   131,    53,   156,
       0,   118,    48,    49,   120,     6,     8,    11,    11,   108,
     104,     3,     7,     3,     4,     5,     7,     9,    10,    13,
      14,    15,    16,    17,    18,    21,    24,    25,    26,    28,
      34,    35,    36,    41,    43,    45,    46,    55,    56,    57,
      58,    73,    91,    97,   100,   101,   104,   108,   129,   130,
     132,   133,   136,   143,   144,   145,   147,   148,   149,   155,
     157,   159,   160,     3,   131,     7,     7,    72,   135,   139,
     140,   142,   139,    11,    11,   136,   137,     7,   104,   143,
     155,   163,   166,   107,   107,    40,   150,   151,   150,   106,
     110,   106,   110,   113,   104,   157,   104,   104,     7,     9,
     154,   104,   104,   104,     7,   108,   108,   104,   104,   104,
     104,   155,   155,   155,   104,   112,   155,   159,   132,    37,
     152,   153,    72,    73,    74,    75,    76,    95,    96,   112,
     146,    44,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      77,    78,   104,   106,   110,   108,   111,    72,    37,   109,
     155,    75,    76,    77,    78,   111,   105,   132,    38,   150,
      39,   155,     7,    59,   136,   147,   155,   144,     7,   163,
      11,     3,   143,   104,   106,   143,   155,   155,   132,   132,
     143,   143,   143,   143,   155,   144,    37,   105,   105,   152,
     109,    37,   133,   157,   155,   165,   166,   165,     3,    27,
      85,    91,   104,   106,   143,   167,   168,    85,   106,   168,
     145,   147,   155,   159,   155,   159,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   159,   155,   159,   137,   138,     3,     3,
       7,   169,   139,   106,   141,   155,   137,   155,   155,   166,
     152,   107,   110,   107,   105,   111,   164,   105,   105,   163,
     143,   105,   105,   105,   152,   152,   105,   105,   105,   105,
     105,   146,   155,   109,   104,   104,   168,     3,   168,   168,
     104,   111,   168,   168,   105,   107,     7,   109,   111,     3,
     110,   113,   143,   149,   166,   105,   105,   107,   109,   109,
     110,   166,   155,    84,   105,   107,   168,   168,    84,   107,
     156,   107,   144,     7,    75,   156,   104,   155,   105,   105,
     105,    54,   158,    33,   163,   105,   104,   131,   108,   105,
     157,     6,     8,   161,   162,   156,   105,   111,   109,   162
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   114,   115,   116,   117,   117,   118,   118,   118,   118,
     118,   118,   118,   118,   119,   120,   120,   121,   121,   121,
     121,   122,   123,   124,   125,   125,   126,   127,   127,   128,
     128,   128,   128,   129,   129,   130,   131,   132,   132,   133,
     133,   133,   133,   133,   134,   134,   134,   134,   135,   135,
     136,   136,   136,   137,   137,   138,   138,   139,   139,   140,
     140,   140,   141,   142,   142,   142,   143,   144,   144,   145,
     145,   146,   146,   147,   147,   148,   148,   148,   148,   148,
     148,   148,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     150,   150,   151,   152,   152,   153,   153,   154,   154,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   156,   156,   157,   157,   158,   158,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   160,   160,   160,   160,
     161,   161,   162,   162,   163,   163,   164,   164,   165,   165,
     166,   166,   167,   167,   167,   167,   168,   168,   168,   168,
     169,   169,   169
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     9,     1,     1,     0,     1,     4,
       4,     3,     2,     5,     1,     1,     5,     1,     1,     3,
       3,     4,     4,     1,     1,     1,     4,     1,     3,     1,
       3,     3,     1,     3,     0,     1,     1,     1,     0,     1,
       3,     3,     6,     1,     3,     0,     1,     1,     3,     1,
       3,     3,     7,     1,     3,     4,     1,     1,     4,     2,
       4,     0,     2,     1,     1,     3,     3,     3,     3,     1,
       2,     3,     3,     2,     2,     5,     4,     4,     2,     1,
       3,     5,     5,     3,     1,     1,     5,     5,     4,     5,
       1,     2,     3,     0,     1,     1,     2,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     4,     2,
       2,     2,     7,     6,     9,     4,     4,     5,     5,     1,
       1,     1,     1,     1,     1,     1,     4,     6,     6,     3,
       3,     0,     2,     1,     1,     0,     4,     1,     3,     3,
       3,     3,     3,     3,     3,     1,     4,     4,     4,     4,
       1,     1,     1,     3,     0,     1,     0,     2,     1,     4,
       1,     3,     1,     4,     1,     2,     1,     3,     4,     3,
       1,     2,     2
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
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, symTabNode** globalSymTab, stmnt** program)
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
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, symTabNode** globalSymTab, stmnt** program)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, symTabNode** globalSymTab, stmnt** program)
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, symTabNode** globalSymTab, stmnt** program)
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
yyparse (symTabNode** globalSymTab, stmnt** program)
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
  case 3:
#line 137 "promela.y"
                                                                                { std::cout<< "REDUCE: units -> program\n"; }
#line 2037 "y.tab.c"
    break;

  case 4:
#line 140 "promela.y"
                                                                                { std::cout<< "REDUCE: unit -> units\n"; }
#line 2043 "y.tab.c"
    break;

  case 5:
#line 141 "promela.y"
                                                                                { std::cout<< "REDUCE: units unit -> units\n"; }
#line 2049 "y.tab.c"
    break;

  case 6:
#line 144 "promela.y"
                                                        { std::cout<< "REDUCE: proc -> unit\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2055 "y.tab.c"
    break;

  case 7:
#line 145 "promela.y"
                                                                { std::cout<< "REDUCE: init -> unit\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2061 "y.tab.c"
    break;

  case 8:
#line 146 "promela.y"
                                                                { std::cout << "The 'events' construct is currently not supported."; }
#line 2067 "y.tab.c"
    break;

  case 9:
#line 147 "promela.y"
                                                                { 
													std::cout << "REDUCE: one_decl -> unit\n";
													if ((yyvsp[0].pSymTabVal)->getType() == symTabNode::T_MTYPE_DEF)
														(yyval.pStmntVal) = new mtypeDecl(static_cast<mtypedefSymNode*>((yyvsp[0].pSymTabVal)), nbrLines); 
													if ((yyvsp[0].pSymTabVal)->getType() == symTabNode::T_CHAN) 
														(yyval.pStmntVal) = new chanDecl(static_cast<chanSymNode*>((yyvsp[0].pSymTabVal)), nbrLines);
													else 
														(yyval.pStmntVal) = new varDecl(static_cast<varSymNode*>((yyvsp[0].pSymTabVal)), nbrLines);
													*globalSymTab = symTabNode::merge(*globalSymTab, (yyvsp[0].pSymTabVal)); 
												}
#line 2082 "y.tab.c"
    break;

  case 10:
#line 157 "promela.y"
                                                                { std::cout<< "REDUCE: utype -> unit\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2088 "y.tab.c"
    break;

  case 11:
#line 158 "promela.y"
                                                                { std::cout << "Embedded C code is not supported."; }
#line 2094 "y.tab.c"
    break;

  case 12:
#line 159 "promela.y"
                                                                { std::cout << "The 'named sequence' construct is currently not supported."; }
#line 2100 "y.tab.c"
    break;

  case 14:
#line 169 "promela.y"
                                                                                        {	
		  											std::cout<< "REDUCE: inst proctype NAME ( decl ) prio ena body -> proc\n";
		  											
		  											procSymNode* proc = new procSymNode((yyvsp[-6].sVal), (yyvsp[-8].pConstExprVal), (yyvsp[-4].pVarSymVal), (yyvsp[0].pStmntVal), nbrLines);
		  											(yyval.pStmntVal) = new procDecl(proc, nbrLines);
		  											(yyval.pStmntVal)->setLocalSymTab(static_cast<varSymNode*>(symTabNode::deepcopy((yyvsp[-4].pVarSymVal))));
		  											*globalSymTab = symTabNode::merge(*globalSymTab, proc);
		  										}
#line 2113 "y.tab.c"
    break;

  case 15:
#line 179 "promela.y"
                                                                                { std::cout << "REDUCE: -> PROCTYPE proctype\n"; }
#line 2119 "y.tab.c"
    break;

  case 16:
#line 180 "promela.y"
                                                                                { std::cout << "Deterministic proctypes are not supported (only useful for simulation)."; }
#line 2125 "y.tab.c"
    break;

  case 17:
#line 183 "promela.y"
                                                                        { std::cout << "REDUCE: void -> inst\n"; (yyval.pConstExprVal) = new exprConst(0, nbrLines); }
#line 2131 "y.tab.c"
    break;

  case 18:
#line 184 "promela.y"
                                                                                        { std::cout << "REDUCE: ACTIVE -> inst\n"; (yyval.pConstExprVal) = new exprConst(1, nbrLines); }
#line 2137 "y.tab.c"
    break;

  case 19:
#line 185 "promela.y"
                                                                        { std::cout << "REDUCE: ACTIVE [ CONST ] -> inst \n"; (yyval.pConstExprVal) = new exprConst((yyvsp[-1].iVal), nbrLines); }
#line 2143 "y.tab.c"
    break;

  case 20:
#line 186 "promela.y"
                                                                        { 
													std::cout << "REDUCE: ACTIVE [ NAME ] -> inst\n";
													varSymNode* var = *globalSymTab? static_cast<varSymNode*>((*globalSymTab)->lookupInSymTab((yyvsp[-1].sVal))) : nullptr;
													if(var == nullptr) std::cout << "The variable "<<(yyvsp[-1].sVal)<<" does not exist.";
													else if(var->getType() != symTabNode::T_INT && var->getType() != symTabNode::T_BYTE && var->getType() != symTabNode::T_SHORT) std::cout << "The variable "<<(yyvsp[-1].sVal)<<" is not of type int, short or bit.";
													else if(var->getInitExpr() == nullptr || var->getInitExpr()->getType() != astNode::E_EXPR_CONST) std::cout << "The variable "<<(yyvsp[-1].sVal)<<" does not have a constant value.";
													else {
														(yyval.pConstExprVal) = new exprConst(static_cast<exprConst*>(var->getInitExpr())->getCstValue(), nbrLines);
													}
													free((yyvsp[-1].sVal));											
												}
#line 2159 "y.tab.c"
    break;

  case 21:
#line 199 "promela.y"
                                                                {	
													std::cout << "REDUCE: INIT Opt_priority body -> init\n";
													if(*globalSymTab && (*globalSymTab)->lookupInSymTab("init") != nullptr) 
														std::cout << "This is the second init process; only one is allowed.";
													else {
														initSymNode* init = new initSymNode(nbrLines, (yyvsp[0].pStmntVal));
														(yyval.pStmntVal) = new initDecl(init, nbrLines);
														*globalSymTab = symTabNode::merge(*globalSymTab, init);
													}
												}
#line 2174 "y.tab.c"
    break;

  case 22:
#line 211 "promela.y"
                                                                        { std::cout << "Event sequences (traces) are not supported."; }
#line 2180 "y.tab.c"
    break;

  case 23:
#line 214 "promela.y"
                                                        {	
													std::cout << "REDUCE: TYPEDEF NAME '{' decl_lst '}' -> utype\n";
													tdefSymNode* tdef = new tdefSymNode((yyvsp[-3].sVal), (yyvsp[-1].pVarSymVal), nbrLines);
													(yyval.pStmntVal) = new tdefDecl(tdef, nbrLines);
													*globalSymTab = symTabNode::merge(*globalSymTab, tdef);
													free((yyvsp[-3].sVal));  
												}
#line 2192 "y.tab.c"
    break;

  case 36:
#line 249 "promela.y"
                                                                { std::cout << "REDUCE: '{' sequence OS '}' -> body\n"; (yyval.pStmntVal) = (yyvsp[-2].pStmntVal); }
#line 2198 "y.tab.c"
    break;

  case 37:
#line 252 "promela.y"
                                                                                { 	std::cout << "REDUCE: step -> sequence\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal);   }
#line 2204 "y.tab.c"
    break;

  case 38:
#line 253 "promela.y"
                                                                                {	std::cout << "REDUCE: sequence MS step -> sequence\n"; (yyval.pStmntVal) = stmnt::merge((yyval.pStmntVal), (yyvsp[0].pStmntVal)); }
#line 2210 "y.tab.c"
    break;

  case 39:
#line 256 "promela.y"
                                                                                { 
													assert((yyvsp[0].pSymTabVal)->getType() != symTabNode::T_MTYPE_DEF && (yyvsp[0].pSymTabVal)->getType() != symTabNode::T_CHAN); 
												 	(yyval.pStmntVal) = new varDecl(static_cast<varSymNode*>((yyvsp[0].pSymTabVal)), nbrLines); 
												}
#line 2219 "y.tab.c"
    break;

  case 40:
#line 260 "promela.y"
                                                                                { std::cout << "Declarations with labels are not suported."; }
#line 2225 "y.tab.c"
    break;

  case 41:
#line 261 "promela.y"
                                                                                { std::cout << "Channel assertions are currently not supported."; }
#line 2231 "y.tab.c"
    break;

  case 42:
#line 262 "promela.y"
                                                                                        { std::cout << "REDUCE: stmnt -> step\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2237 "y.tab.c"
    break;

  case 43:
#line 263 "promela.y"
                                                                        { std::cout << "Unless statements are currently not supported."; }
#line 2243 "y.tab.c"
    break;

  case 45:
#line 272 "promela.y"
                                                                                        { std::cout << "The 'hidden' keyword is not supported."; }
#line 2249 "y.tab.c"
    break;

  case 46:
#line 273 "promela.y"
                                                                                        { std::cout << "The 'show' keyword is not supported."; }
#line 2255 "y.tab.c"
    break;

  case 47:
#line 274 "promela.y"
                                                                                        { std::cout << "The 'local' keyword is not supported."; }
#line 2261 "y.tab.c"
    break;

  case 50:
#line 284 "promela.y"
                                                                        {	std::cout << "REDUCE: vis TYPE var_list -> one_decl\n";
													varSymNode* cur = (yyvsp[0].pVarSymVal);
													varSymNode* res = nullptr;
													while(cur != nullptr) {
														varSymNode* tmp = nullptr;
														
														if(cur->getType() == symTabNode::T_NA) { 
															varSymNode* next = varSymNode::createSymTabNode((yyvsp[-1].iType), cur->getLineNb(), cur->getName(), cur->getBound(), cur->getInitExpr());
															next->setLineNb(nbrLines);
															// If type != 0, then the var is a T_CHAN
														
															//cur->getType() = $2
															if(res == nullptr) {
																res = next;
																tmp = next;
															} else {
																tmp->makeNext(next);
																tmp = static_cast<varSymNode*>(tmp->nextSym());
															}
														} else {
															assert(cur->getType() == symTabNode::T_CHAN);
															varSymNode* next = new chanSymNode(*static_cast<chanSymNode*>(cur));
															
															if(res == nullptr) {
																res = next;
																tmp = next;
															} else {
																tmp->makeNext(next);
																tmp = static_cast<varSymNode*>(tmp->nextSym());
															}
														}
														
														//cur->detachChildAndInitSymNodes();
														cur = static_cast<varSymNode*>(cur->nextSym());
													}
													//delete $3;
													(yyval.pSymTabVal) = res;
												}
#line 2304 "y.tab.c"
    break;

  case 51:
#line 322 "promela.y"
                                                                        {	std::cout << "REDUCE: vis UNAME var_list -> one_decl\n";
	 												tdefSymNode* type = *globalSymTab? static_cast<tdefSymNode*>((*globalSymTab)->lookupInSymTab((yyvsp[-1].sVal))) : nullptr;
	 												if(type == nullptr)
	 													std::cout << "The type "<<(yyvsp[-1].sVal)<<" was not declared in a typedef.";
													else {
														utypeSymNode* cur = static_cast<utypeSymNode*>((yyvsp[0].pVarSymVal));
														while(cur != nullptr) {
															//cur->getType() = T_UTYPE;
															cur->setUType(type);
															cur = static_cast<utypeSymNode*>(cur->nextSym());
														}
														(yyval.pSymTabVal) = (yyvsp[0].pVarSymVal);
													}
	 												free((yyvsp[-1].sVal));
												}
#line 2324 "y.tab.c"
    break;

  case 52:
#line 337 "promela.y"
                                                                {	
													std::cout << "REDUCE: vis TYPE asgn { nlst } -> one_decl\n";
													if((yyvsp[-4].iType) != symTabNode::T_MTYPE) {
														std::cout <<  "This syntax only works for MTYPEs.";
														exit(1);
													}
													mtypedefSymNode* mtypeDef = new mtypedefSymNode((yyvsp[-1].pMTypeListVal), nbrLines);
													(yyval.pSymTabVal) = mtypeDef;
													// The mtype values are added in the nlst rule.
												}
#line 2339 "y.tab.c"
    break;

  case 53:
#line 349 "promela.y"
                                                                                { std::cout << "REDUCE: one_decl -> decl_list\n"; (yyval.pVarSymVal) = static_cast<varSymNode*>((yyvsp[0].pSymTabVal)); }
#line 2345 "y.tab.c"
    break;

  case 54:
#line 350 "promela.y"
                                                                        { std::cout << "REDUCE: one_decl SEMI decl_list -> decl_lst\n"; (yyval.pVarSymVal) = varSymNode::merge(static_cast<varSymNode*>((yyvsp[-2].pSymTabVal)), (yyvsp[0].pVarSymVal)); }
#line 2351 "y.tab.c"
    break;

  case 55:
#line 354 "promela.y"
                                                                        { std::cout << "REDUCE: void -> decl\n"; (yyval.pVarSymVal) = nullptr; }
#line 2357 "y.tab.c"
    break;

  case 56:
#line 355 "promela.y"
                                                                                        { std::cout << "REDUCE: decl_list -> decl\n"; (yyval.pVarSymVal) = (yyvsp[0].pVarSymVal); }
#line 2363 "y.tab.c"
    break;

  case 57:
#line 362 "promela.y"
                                                                                { std::cout << "REDUCE: ivar -> var_list\n"; (yyval.pVarSymVal) = (yyvsp[0].pVarSymVal); }
#line 2369 "y.tab.c"
    break;

  case 58:
#line 363 "promela.y"
                                                                                { std::cout << "REDUCE: ivar , var_list -> var_list\n"; (yyval.pVarSymVal) = varSymNode::merge((yyvsp[-2].pVarSymVal), (yyvsp[0].pVarSymVal)); }
#line 2375 "y.tab.c"
    break;

  case 59:
#line 366 "promela.y"
                                                                                { std::cout << "REDUCE: var_decl -> ivar\n"; (yyval.pVarSymVal) = varSymNode::createSymTabNode((yyvsp[0].pDataVal).iType, nbrLines, (yyvsp[0].pDataVal).sVal, (yyvsp[0].pDataVal).iVal); }
#line 2381 "y.tab.c"
    break;

  case 60:
#line 367 "promela.y"
                                                                                { std::cout << "REDUCE: var_decl ASGN expr -> ivar\n"; (yyval.pVarSymVal) = varSymNode::createSymTabNode((yyvsp[-2].pDataVal).iType, nbrLines, (yyvsp[-2].pDataVal).sVal, (yyvsp[-2].pDataVal).iVal, (yyvsp[0].pExprVal)); }
#line 2387 "y.tab.c"
    break;

  case 61:
#line 368 "promela.y"
                                                                        { std::cout << "REDUCE: var_decl ASGN ch_init -> ivar\n"; (yyval.pVarSymVal) = new chanSymNode(nbrLines, (yyvsp[-2].pDataVal).sVal, (yyvsp[-2].pDataVal).iVal, (yyvsp[0].pDataVal).iVal, (yyvsp[0].pDataVal).symTabNodeVal); }
#line 2393 "y.tab.c"
    break;

  case 62:
#line 371 "promela.y"
                                                        { std::cout << "REDUCE: [ CONST ] OF { typ_list } -> ch_init\n"; (yyval.pDataVal).iVal = (yyvsp[-5].iVal); (yyval.pDataVal).symTabNodeVal = (yyvsp[-1].pVarSymVal); }
#line 2399 "y.tab.c"
    break;

  case 63:
#line 374 "promela.y"
                                                                                { std::cout << "REDUCE: NAME -> vardcl\n"; (yyval.pDataVal).sVal = (yyvsp[0].sVal); (yyval.pDataVal).iVal = 1; }
#line 2405 "y.tab.c"
    break;

  case 64:
#line 375 "promela.y"
                                                                                { std::cout << "The 'unsigned' data type is not supported."; }
#line 2411 "y.tab.c"
    break;

  case 65:
#line 376 "promela.y"
                                                                        { std::cout << "REDUCE: NAME [ CONST ] -> vardcl\n"; (yyval.pDataVal).sVal = (yyvsp[-3].sVal); (yyval.pDataVal).iVal = (yyvsp[-1].iVal); }
#line 2417 "y.tab.c"
    break;

  case 66:
#line 379 "promela.y"
                                                                                { std::cout << "REDUCE: cmpnd -> varref\n"; (yyval.pExprVarRefVal) = (yyvsp[0].pExprVarRefVal); }
#line 2423 "y.tab.c"
    break;

  case 67:
#line 382 "promela.y"
                                                                                { std::cout << "REDUCE: NAME -> pfld\n"; (yyval.pExprVarRefNameVal) = new exprVarRefName((yyvsp[0].sVal), nbrLines); free((yyvsp[0].sVal)); }
#line 2429 "y.tab.c"
    break;

  case 68:
#line 383 "promela.y"
                                                                                { std::cout << "REDUCE: NAME [ expr ] -> pfld\n"; (yyval.pExprVarRefNameVal) = new exprVarRefName((yyvsp[-3].sVal), (yyvsp[-1].pExprVal), nbrLines); free((yyvsp[-3].sVal)); }
#line 2435 "y.tab.c"
    break;

  case 69:
#line 386 "promela.y"
                                                                                { std::cout << "REDUCE: pfld sfld -> cmpnd\n"; (yyval.pExprVarRefVal) = new exprVarRef(nbrLines, (yyvsp[-1].pExprVarRefNameVal), (yyvsp[0].pExprVarRefVal)); }
#line 2441 "y.tab.c"
    break;

  case 70:
#line 387 "promela.y"
                                                                        { std::cout << "REDUCE: CONTEX . pfld sfld -> cmpnd\n"; (yyval.pExprVarRefVal) = new exprVarRef(nbrLines, (yyvsp[-1].pExprVarRefNameVal), (yyvsp[0].pExprVarRefVal)); }
#line 2447 "y.tab.c"
    break;

  case 71:
#line 390 "promela.y"
                                                                                        { std::cout << "REDUCE: void -> sfld\n"; (yyval.pExprVarRefVal) = nullptr; }
#line 2453 "y.tab.c"
    break;

  case 72:
#line 391 "promela.y"
                                                                        { std::cout << "REDUCE: . cmpnd -> sfld\n"; (yyval.pExprVarRefVal) = (yyvsp[0].pExprVarRefVal);   }
#line 2459 "y.tab.c"
    break;

  case 73:
#line 395 "promela.y"
                                                                                { std::cout << "REDUCE: special -> stmnt\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2465 "y.tab.c"
    break;

  case 74:
#line 396 "promela.y"
                                                                                        { std::cout << "REDUCE: Stmnt -> stmnt\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2471 "y.tab.c"
    break;

  case 75:
#line 399 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntChanRecv((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprArgListVal), nbrLines); }
#line 2477 "y.tab.c"
    break;

  case 76:
#line 400 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntChanSnd((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprArgListVal), nbrLines); }
#line 2483 "y.tab.c"
    break;

  case 77:
#line 401 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntIf((yyvsp[-1].pStmntOptVal), (yyvsp[-2].iVal)); }
#line 2489 "y.tab.c"
    break;

  case 78:
#line 402 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntDo((yyvsp[-1].pStmntOptVal), (yyvsp[-2].iVal)); }
#line 2495 "y.tab.c"
    break;

  case 79:
#line 403 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntBreak(nbrLines); }
#line 2501 "y.tab.c"
    break;

  case 80:
#line 404 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntGoto((yyvsp[0].sVal), nbrLines); free((yyvsp[0].sVal)); }
#line 2507 "y.tab.c"
    break;

  case 81:
#line 405 "promela.y"
                                                                                { if((yyvsp[0].pStmntVal)->getType() == astNode::E_STMNT_LABEL && static_cast<stmntLabel*>((yyvsp[0].pStmntVal))->getLabelledStmnt()->getType() == astNode::E_STMNT_LABEL) 
													std::cout << "Only two labels per state are supported."; 
												  (yyval.pStmntVal) = new stmntLabel((yyvsp[-2].sVal), (yyvsp[0].pStmntVal), nbrLines); free((yyvsp[-2].sVal)); }
#line 2515 "y.tab.c"
    break;

  case 82:
#line 409 "promela.y"
                                                                { (yyval.pStmntVal) = new stmntAsgn((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2521 "y.tab.c"
    break;

  case 83:
#line 410 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntIncr((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2527 "y.tab.c"
    break;

  case 84:
#line 411 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntDecr((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2533 "y.tab.c"
    break;

  case 85:
#line 412 "promela.y"
                                                                { (yyval.pStmntVal) = new stmntPrint((yyvsp[-2].sVal), (yyvsp[-1].pExprArgListVal), nbrLines); }
#line 2539 "y.tab.c"
    break;

  case 86:
#line 413 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntPrintm((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2545 "y.tab.c"
    break;

  case 87:
#line 414 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntPrintm((yyvsp[-1].iVal), nbrLines); }
#line 2551 "y.tab.c"
    break;

  case 88:
#line 415 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntAssert((yyvsp[0].pExprVal), nbrLines); }
#line 2557 "y.tab.c"
    break;

  case 89:
#line 416 "promela.y"
                                                                                        { std::cout << "Embedded C code is not supported."; }
#line 2563 "y.tab.c"
    break;

  case 90:
#line 417 "promela.y"
                                                                        { std::cout << "Sorted send and random receive are not supported."; }
#line 2569 "y.tab.c"
    break;

  case 91:
#line 418 "promela.y"
                                                                        { std::cout << "Channel poll operations are not supported."; }
#line 2575 "y.tab.c"
    break;

  case 92:
#line 419 "promela.y"
                                                                        { std::cout << "Channel poll operations are not supported."; }
#line 2581 "y.tab.c"
    break;

  case 93:
#line 420 "promela.y"
                                                                        { std::cout << "Sorted send and random receive are not supported."; }
#line 2587 "y.tab.c"
    break;

  case 94:
#line 421 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntExpr((yyvsp[0].pExprVal), nbrLines); }
#line 2593 "y.tab.c"
    break;

  case 95:
#line 422 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntElse(nbrLines); }
#line 2599 "y.tab.c"
    break;

  case 96:
#line 423 "promela.y"
                                                                { (yyval.pStmntVal) = new stmntAtomic((yyvsp[-2].pStmntVal), nbrLines); }
#line 2605 "y.tab.c"
    break;

  case 97:
#line 424 "promela.y"
                                                                { std::cout << "Deterministic steps are not yet supported."; }
#line 2611 "y.tab.c"
    break;

  case 98:
#line 425 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntSeq((yyvsp[-2].pStmntVal), nbrLines); }
#line 2617 "y.tab.c"
    break;

  case 99:
#line 426 "promela.y"
                                                                        { std::cout << "Inline calls are not yet supported."; }
#line 2623 "y.tab.c"
    break;

  case 100:
#line 429 "promela.y"
                                                                                { (yyval.pStmntOptVal) = new stmntOpt((yyvsp[0].pStmntVal), nbrLines); }
#line 2629 "y.tab.c"
    break;

  case 101:
#line 430 "promela.y"
                                                                                { (yyval.pStmntOptVal) = new stmntOpt((yyvsp[-1].pStmntVal), (yyvsp[0].pStmntOptVal), nbrLines); }
#line 2635 "y.tab.c"
    break;

  case 102:
#line 433 "promela.y"
                                                                        { (yyval.pStmntVal) = (yyvsp[-1].pStmntVal); }
#line 2641 "y.tab.c"
    break;

  case 104:
#line 447 "promela.y"
                                        { /* redundant semi at end of sequence */ }
#line 2647 "y.tab.c"
    break;

  case 105:
#line 450 "promela.y"
                                        { /* at least one semi-colon */ }
#line 2653 "y.tab.c"
    break;

  case 106:
#line 451 "promela.y"
                                        { /* but more are okay too   */ }
#line 2659 "y.tab.c"
    break;

  case 107:
#line 454 "promela.y"
                                                                                { (yyval.sVal) = (yyvsp[0].sVal); }
#line 2665 "y.tab.c"
    break;

  case 108:
#line 455 "promela.y"
                                                                                        { (yyval.sVal) = (yyvsp[0].sVal); }
#line 2671 "y.tab.c"
    break;

  case 109:
#line 458 "promela.y"
                                                                        { (yyval.pExprVal) = new exprPar		((yyvsp[-1].pExprVal), nbrLines); }
#line 2677 "y.tab.c"
    break;

  case 110:
#line 459 "promela.y"
                                                                                { (yyval.pExprVal) = new exprPlus		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2683 "y.tab.c"
    break;

  case 111:
#line 460 "promela.y"
                                                                                { (yyval.pExprVal) = new exprMinus	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2689 "y.tab.c"
    break;

  case 112:
#line 461 "promela.y"
                                                                                { (yyval.pExprVal) = new exprTimes	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2695 "y.tab.c"
    break;

  case 113:
#line 462 "promela.y"
                                                                                { (yyval.pExprVal) = new exprDiv		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2701 "y.tab.c"
    break;

  case 114:
#line 463 "promela.y"
                                                                                { (yyval.pExprVal) = new exprMod		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2707 "y.tab.c"
    break;

  case 115:
#line 464 "promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2713 "y.tab.c"
    break;

  case 116:
#line 465 "promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwXor	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2719 "y.tab.c"
    break;

  case 117:
#line 466 "promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2725 "y.tab.c"
    break;

  case 118:
#line 467 "promela.y"
                                                                                { (yyval.pExprVal) = new exprGT		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2731 "y.tab.c"
    break;

  case 119:
#line 468 "promela.y"
                                                                                { (yyval.pExprVal) = new exprLT		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2737 "y.tab.c"
    break;

  case 120:
#line 469 "promela.y"
                                                                                { (yyval.pExprVal) = new exprGE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2743 "y.tab.c"
    break;

  case 121:
#line 470 "promela.y"
                                                                                { (yyval.pExprVal) = new exprLE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2749 "y.tab.c"
    break;

  case 122:
#line 471 "promela.y"
                                                                                { (yyval.pExprVal) = new exprEQ		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2755 "y.tab.c"
    break;

  case 123:
#line 472 "promela.y"
                                                                                { (yyval.pExprVal) = new exprNE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2761 "y.tab.c"
    break;

  case 124:
#line 473 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2767 "y.tab.c"
    break;

  case 125:
#line 474 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2773 "y.tab.c"
    break;

  case 126:
#line 475 "promela.y"
                                                                                { (yyval.pExprVal) = new exprLShift	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2779 "y.tab.c"
    break;

  case 127:
#line 476 "promela.y"
                                                                                { (yyval.pExprVal) = new exprRShift	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2785 "y.tab.c"
    break;

  case 128:
#line 477 "promela.y"
                                                                        { (yyval.pExprVal) = new exprCount	((yyvsp[-1].pExprVal), nbrLines); }
#line 2791 "y.tab.c"
    break;

  case 129:
#line 478 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprBitwNeg	((yyvsp[0].pExprVal), nbrLines); }
#line 2797 "y.tab.c"
    break;

  case 130:
#line 479 "promela.y"
                                                                        { 	if((yyvsp[0].pExprVal)->getType() != astNode::E_EXPR_CONST) 
														(yyval.pExprVal) = new exprUMin((yyvsp[0].pExprVal), nbrLines);
													else {
														exprConst* tmp = static_cast<exprConst*>((yyvsp[0].pExprVal));
														tmp->setCstValue(- tmp->getCstValue());
														(yyval.pExprVal) = tmp;
													}
												}
#line 2810 "y.tab.c"
    break;

  case 131:
#line 487 "promela.y"
                                                                        { (yyval.pExprVal) = new exprNeg	((yyvsp[0].pExprVal), nbrLines); }
#line 2816 "y.tab.c"
    break;

  case 132:
#line 488 "promela.y"
                                                                { (yyval.pExprVal) = new exprCond	((yyvsp[-5].pExprVal), (yyvsp[-3].pExprVal), (yyvsp[-1].pExprVal), nbrLines); }
#line 2822 "y.tab.c"
    break;

  case 133:
#line 489 "promela.y"
                                                        { (yyval.pExprVal) = new exprRun	((yyvsp[-4].sVal), (yyvsp[-2].pExprArgListVal), nbrLines); }
#line 2828 "y.tab.c"
    break;

  case 134:
#line 491 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprRun	((yyvsp[-7].sVal), (yyvsp[-2].pExprArgListVal), (yyvsp[-5].pExprVarRefVal), nbrLines); }
#line 2834 "y.tab.c"
    break;

  case 135:
#line 492 "promela.y"
                                                                        { (yyval.pExprVal) = new exprLen	((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2840 "y.tab.c"
    break;

  case 136:
#line 493 "promela.y"
                                                                        { std::cout << "The enabled keyword is not supported."; }
#line 2846 "y.tab.c"
    break;

  case 137:
#line 494 "promela.y"
                                                                        { std::cout << "Construct not supported."; /* Unclear */ }
#line 2852 "y.tab.c"
    break;

  case 138:
#line 495 "promela.y"
                                                                { std::cout << "Sorted send and random receive are not supported."; }
#line 2858 "y.tab.c"
    break;

  case 139:
#line 496 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprVar	((yyvsp[0].pExprVarRefVal), nbrLines); }
#line 2864 "y.tab.c"
    break;

  case 140:
#line 497 "promela.y"
                                                                                        { std::cout << "Embedded C code is not supported."; }
#line 2870 "y.tab.c"
    break;

  case 141:
#line 498 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprConst((yyvsp[0].iVal), nbrLines); }
#line 2876 "y.tab.c"
    break;

  case 142:
#line 499 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprTrue	(nbrLines); }
#line 2882 "y.tab.c"
    break;

  case 143:
#line 500 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprFalse(nbrLines); }
#line 2888 "y.tab.c"
    break;

  case 144:
#line 501 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprTimeout(nbrLines); }
#line 2894 "y.tab.c"
    break;

  case 145:
#line 502 "promela.y"
                                                                                { std::cout << "The 'np_' variable is not supported."; }
#line 2900 "y.tab.c"
    break;

  case 146:
#line 503 "promela.y"
                                                                        { std::cout << "The 'pc_value()' construct is not supported."; }
#line 2906 "y.tab.c"
    break;

  case 147:
#line 504 "promela.y"
                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 2912 "y.tab.c"
    break;

  case 148:
#line 505 "promela.y"
                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 2918 "y.tab.c"
    break;

  case 149:
#line 506 "promela.y"
                                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 2924 "y.tab.c"
    break;

  case 150:
#line 507 "promela.y"
                                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 2930 "y.tab.c"
    break;

  case 152:
#line 511 "promela.y"
                                                                                { std::cout << "The 'priority' construct is related to simulation and not supported."; }
#line 2936 "y.tab.c"
    break;

  case 153:
#line 514 "promela.y"
                                                                                { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 2942 "y.tab.c"
    break;

  case 154:
#line 515 "promela.y"
                                                                                        { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 2948 "y.tab.c"
    break;

  case 156:
#line 519 "promela.y"
                                                                { std::cout << "The 'provided' construct is currently not supported."; }
#line 2954 "y.tab.c"
    break;

  case 157:
#line 524 "promela.y"
                                                                                { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 2960 "y.tab.c"
    break;

  case 158:
#line 525 "promela.y"
                                                                                { (yyval.pExprVal) = new exprPar	((yyvsp[-1].pExprVal), nbrLines); }
#line 2966 "y.tab.c"
    break;

  case 159:
#line 526 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2972 "y.tab.c"
    break;

  case 160:
#line 527 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2978 "y.tab.c"
    break;

  case 161:
#line 528 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2984 "y.tab.c"
    break;

  case 162:
#line 529 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2990 "y.tab.c"
    break;

  case 163:
#line 530 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2996 "y.tab.c"
    break;

  case 164:
#line 531 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3002 "y.tab.c"
    break;

  case 165:
#line 532 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprSkip	(nbrLines); }
#line 3008 "y.tab.c"
    break;

  case 166:
#line 535 "promela.y"
                                                                { (yyval.pExprVal) = new exprFull	((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3014 "y.tab.c"
    break;

  case 167:
#line 536 "promela.y"
                                                                        { (yyval.pExprVal) = new exprNFull((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3020 "y.tab.c"
    break;

  case 168:
#line 537 "promela.y"
                                                                        { (yyval.pExprVal) = new exprEmpty((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3026 "y.tab.c"
    break;

  case 169:
#line 538 "promela.y"
                                                                        { (yyval.pExprVal) = new exprNEmpty((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3032 "y.tab.c"
    break;

  case 170:
#line 541 "promela.y"
                                                                                { (yyval.pDataVal).sVal = nullptr; (yyval.pDataVal).iType = (yyvsp[0].iType); }
#line 3038 "y.tab.c"
    break;

  case 171:
#line 542 "promela.y"
                                                                                        { (yyval.pDataVal).sVal = (yyvsp[0].sVal); (yyval.pDataVal).iType = symTabNode::T_UTYPE; }
#line 3044 "y.tab.c"
    break;

  case 172:
#line 546 "promela.y"
                                                                                {	std::cout << "REDUCE: basetype -> typ_list\n";
													if((yyvsp[0].pDataVal).iType != symTabNode::T_UTYPE) {
														(yyval.pVarSymVal) = varSymNode::createSymTabNode((yyvsp[0].pDataVal).iType, nbrLines);
													} else {
														tdefSymNode* pType = *globalSymTab ? static_cast<tdefSymNode*>((*globalSymTab)->lookupInSymTab((yyvsp[0].pDataVal).sVal)) : nullptr;
														(yyval.pVarSymVal) = new utypeSymNode(pType, nbrLines);
														if((yyval.pVarSymVal) == nullptr) 
															std::cout << "The type "<<(yyvsp[0].pDataVal).sVal<<" was not declared in a typedef.\n";
													}
												}
#line 3059 "y.tab.c"
    break;

  case 173:
#line 556 "promela.y"
                                                                        {	std::cout << "REDUCE: basetype , typ_list -> typ_list\n";
													if((yyvsp[-2].pDataVal).iType != symTabNode::T_UTYPE) {
														(yyval.pVarSymVal) = varSymNode::merge((yyval.pVarSymVal), varSymNode::createSymTabNode((yyvsp[-2].pDataVal).iType, nbrLines));
													} else {
														tdefSymNode* pType = *globalSymTab ? static_cast<tdefSymNode*>((*globalSymTab)->lookupInSymTab((yyvsp[-2].pDataVal).sVal)) : nullptr;
														utypeSymNode* temp = new utypeSymNode(pType, nbrLines);
														if(temp == nullptr) 
															std::cout << "The type "<<(yyvsp[-2].pDataVal).sVal<<" was not declared in a typedef.\n";
														else 
															(yyval.pVarSymVal) = varSymNode::merge((yyvsp[0].pVarSymVal), temp);
													}
												}
#line 3076 "y.tab.c"
    break;

  case 175:
#line 572 "promela.y"
                                                                                        { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3082 "y.tab.c"
    break;

  case 176:
#line 576 "promela.y"
                                                                        { (yyval.pExprArgListVal) = nullptr; }
#line 3088 "y.tab.c"
    break;

  case 177:
#line 577 "promela.y"
                                                                                        { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3094 "y.tab.c"
    break;

  case 178:
#line 581 "promela.y"
                                                                                { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3100 "y.tab.c"
    break;

  case 179:
#line 582 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList(static_cast<exprRArg*>((yyvsp[-3].pExprVal)), static_cast<exprArgList*>((yyvsp[-1].pExprArgListVal)), nbrLines); }
#line 3106 "y.tab.c"
    break;

  case 180:
#line 585 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList(static_cast<exprRArg*>((yyvsp[0].pExprVal)), nbrLines); }
#line 3112 "y.tab.c"
    break;

  case 181:
#line 586 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList(static_cast<exprRArg*>((yyvsp[-2].pExprVal)), static_cast<exprArgList*>((yyvsp[0].pExprArgListVal)), nbrLines); }
#line 3118 "y.tab.c"
    break;

  case 182:
#line 589 "promela.y"
                                                                                { (yyval.pExprRArgVal) = new exprRArgVar((yyvsp[0].pExprVarRefVal), nbrLines); }
#line 3124 "y.tab.c"
    break;

  case 183:
#line 590 "promela.y"
                                                                                { (yyval.pExprRArgVal) = new exprRArgEval((yyvsp[-1].pExprVal), nbrLines); }
#line 3130 "y.tab.c"
    break;

  case 184:
#line 591 "promela.y"
                                                                                        { (yyval.pExprRArgVal) = new exprRArgConst((yyvsp[0].iVal), nbrLines); }
#line 3136 "y.tab.c"
    break;

  case 185:
#line 592 "promela.y"
                                                                        { (yyval.pExprRArgVal) = new exprRArgConst(-(yyvsp[0].iVal), nbrLines); }
#line 3142 "y.tab.c"
    break;

  case 186:
#line 596 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList((yyvsp[0].pExprRArgVal), nbrLines); }
#line 3148 "y.tab.c"
    break;

  case 187:
#line 597 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList((yyvsp[-2].pExprRArgVal), (yyvsp[0].pExprArgListVal), nbrLines); }
#line 3154 "y.tab.c"
    break;

  case 188:
#line 598 "promela.y"
                                                                        { (yyval.pExprArgListVal) = new exprArgList((yyvsp[-3].pExprRArgVal), (yyvsp[-1].pExprArgListVal), nbrLines); }
#line 3160 "y.tab.c"
    break;

  case 189:
#line 599 "promela.y"
                                                                                { (yyval.pExprArgListVal) = (yyvsp[-1].pExprArgListVal); }
#line 3166 "y.tab.c"
    break;

  case 190:
#line 602 "promela.y"
                                                                                { std::cout << "REDUCE: NAME -> nlst\n"; (yyval.pMTypeListVal) = mtypeList::addMType(nullptr, (yyvsp[0].sVal)); free((yyvsp[0].sVal)); }
#line 3172 "y.tab.c"
    break;

  case 191:
#line 603 "promela.y"
                                                                                        { std::cout << "REDUCE: nlst NAME -> NAME\n"; (yyval.pMTypeListVal) = mtypeList::addMType((yyval.pMTypeListVal), (yyvsp[0].sVal)); free((yyvsp[0].sVal)); }
#line 3178 "y.tab.c"
    break;

  case 192:
#line 604 "promela.y"
                                                                { std::cout << "REDUCE: nlst , -> nlst\n"; }
#line 3184 "y.tab.c"
    break;


#line 3188 "y.tab.c"

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
#line 606 "promela.y"

