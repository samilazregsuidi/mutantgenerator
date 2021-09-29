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
#define YYFINAL  41
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1375

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  114
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  193
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  393

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
     158,   159,   160,   161,   162,   166,   181,   182,   185,   186,
     187,   188,   201,   213,   216,   225,   238,   239,   242,   245,
     246,   249,   250,   251,   252,   255,   256,   259,   262,   265,
     266,   269,   273,   274,   275,   276,   284,   285,   286,   287,
     290,   291,   297,   326,   343,   344,   348,   349,   356,   357,
     360,   361,   362,   365,   368,   369,   370,   373,   376,   377,
     380,   381,   384,   385,   389,   390,   393,   394,   395,   396,
     397,   398,   399,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   423,   424,   427,   440,   441,   444,   445,   448,   449,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   481,   482,   483,   484,   486,   487,   488,   489,
     490,   491,   492,   493,   494,   495,   496,   497,   498,   499,
     500,   501,   504,   505,   508,   509,   512,   513,   518,   519,
     520,   521,   522,   523,   524,   525,   526,   529,   530,   531,
     532,   535,   536,   540,   550,   565,   566,   570,   571,   575,
     576,   579,   580,   583,   584,   585,   586,   590,   591,   592,
     593,   596,   597,   598
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
  "proctype", "inst", "init", "events", "utype", "mtype", "nm", "ns",
  "c_fcts", "cstate", "ccode", "cexpr", "body", "sequence", "step", "vis",
  "asgn", "one_decl", "decl_lst", "decl", "var_list", "ivar", "ch_init",
  "vardcl", "varref", "pfld", "cmpnd", "sfld", "stmnt", "Special", "Stmnt",
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

#define YYPACT_NINF (-322)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-106)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     966,  -322,  -322,    24,    63,   104,    72,  -322,    60,  -322,
    -322,  -322,    61,   120,   177,  -322,   940,  -322,  -322,    66,
    -322,  -322,  -322,  -322,  -322,  -322,  -322,  -322,    91,  -322,
     176,   187,    95,  -322,  -322,    84,    47,   547,  -322,   202,
      61,  -322,  -322,  -322,  -322,   192,     3,   203,   198,   210,
     111,   816,   108,   113,  -322,   206,   206,   -46,   -51,   128,
    -322,  -322,  -322,   759,   143,   144,  -322,   115,   145,   147,
     149,   249,  -322,  -322,   152,   153,  -322,  -322,   158,   159,
     169,   170,   816,   816,   816,   172,   167,   759,   547,  -322,
    -322,   220,  -322,   166,  -322,   -30,   168,  -322,   239,  -322,
    -322,  1263,  -322,    69,  -322,  -322,  -322,   180,   -22,  -322,
     181,  -322,   175,   218,  -322,  -322,  -322,   260,   189,   193,
     816,    77,   987,   197,  -322,  -322,  -322,   547,   263,   206,
     265,   816,   343,   816,   300,   304,   816,  -322,   301,     8,
    -322,  -322,    90,     2,   816,   816,  -322,   547,   547,     2,
       2,     2,     2,  -322,  -322,  -322,   816,   300,   787,   -47,
     220,     1,   205,   445,   203,   759,   816,   816,    64,   190,
    -322,  -322,     2,  -322,   649,   759,   759,   816,   816,   816,
     816,   816,   816,   816,   816,   816,   816,   816,   816,   816,
     816,   816,   816,   759,   759,   -27,   312,   313,   329,   203,
     706,   111,  -322,   845,   232,   234,   816,   816,   816,  -322,
     220,  -322,  -322,  -322,  1056,    -8,  -322,  -322,  -322,  1087,
    -322,  -322,   236,   231,   238,   244,   816,     2,   246,  1118,
    1147,   220,   220,   250,   267,   268,   269,  1176,   168,   816,
    -322,  -322,   235,  -322,  -322,  -322,  -322,   952,  -322,  -322,
    -322,  -322,   241,   204,   351,   204,   204,  -322,   -19,  -322,
     204,   204,  -322,  -322,  -322,   339,   292,   542,  -322,   240,
     423,   321,   522,   522,   150,   150,   150,   150,   178,   178,
      98,    98,  -322,  -322,  -322,   339,   292,   542,  -322,  -322,
     270,   273,  -322,  -322,    12,  -322,   373,  -322,  1281,  -322,
     441,   542,  -322,  -322,  -322,   649,    41,   209,   816,   276,
    -322,  -322,   277,   278,  -322,  -322,  -322,   274,   281,  -322,
    -322,  -322,  -322,  -322,  -322,  1022,  -322,   816,   816,   303,
    -322,   286,   285,   204,   204,   352,   289,   120,  -322,  -322,
    -322,  -322,   290,   300,   428,   -23,  -322,  -322,  -322,   120,
     333,  -322,  -322,   816,   334,  1205,  -322,  -322,  -322,   336,
    -322,  -322,  -322,   384,   409,  -322,  -322,   -49,  -322,   816,
    1234,  -322,  -322,  -322,   341,    61,   338,   348,  -322,   759,
    -322,   196,   120,   362,  -322,  -322,   345,   359,  -322,  -322,
     196,  -322,  -322
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      18,    35,    36,     0,     0,     0,     0,    14,    19,    47,
      48,    49,     0,   152,     0,     2,    18,     4,     6,     0,
       7,     8,    10,    11,    13,    12,    30,    29,     0,     9,
       0,     0,     0,    26,    27,     0,     0,    46,    23,     0,
       0,     1,     5,    16,    17,     0,    50,     0,    31,    32,
      46,   175,     0,     0,   142,     0,     0,    68,     0,     0,
     143,   144,   166,     0,     0,     0,    37,     0,     0,     0,
       0,     0,    80,    96,     0,     0,   145,   146,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    46,    90,
     141,   104,    39,     0,    41,   140,    72,    67,    44,    74,
      75,   154,    95,   155,   158,   153,    22,     0,    64,    51,
       0,    52,    58,    60,    53,    33,    34,    54,     0,    68,
       0,   140,   181,     0,   176,    20,    21,    46,     0,   101,
       0,     0,    46,     0,     0,     0,   175,    89,     0,     0,
     108,   109,     0,     0,     0,     0,    81,    46,    46,     0,
       0,     0,     0,   132,   131,   130,     0,     0,     0,     0,
     104,   106,     0,    46,     0,     0,     0,     0,     0,     0,
      84,    85,     0,    70,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    46,     0,     0,     0,     0,
       0,    46,    24,     0,     0,     0,     0,     0,     0,    28,
     104,    78,   102,    79,     0,    68,    43,    42,    82,     0,
     151,   150,     0,   177,     0,     0,   175,     0,     0,     0,
       0,   104,   104,     0,     0,     0,     0,     0,    72,     0,
     110,   159,     0,    38,   107,    40,    83,   181,    77,   179,
      94,   185,     0,     0,     0,     0,     0,   183,   187,    76,
       0,     0,    91,    73,    45,   126,   165,   125,   164,   118,
     117,   116,   123,   124,   119,   120,   121,   122,   127,   128,
     111,   112,   113,   114,   115,   163,   162,   161,   160,    57,
       0,     0,    65,   191,     0,    59,     0,    62,    61,    55,
     126,   125,   182,   103,    69,     0,     0,     0,     0,     0,
      88,    87,     0,     0,   136,   137,   147,     0,     0,   167,
     169,   168,   170,   129,    71,     0,    99,     0,     0,     0,
     186,     0,     0,     0,     0,     0,     0,   152,    66,   192,
      25,   193,     0,     0,     0,   140,   100,   178,    86,   152,
       0,    97,    98,     0,     0,     0,    92,   190,   138,     0,
     188,    93,   139,   156,     0,   149,   148,     0,   134,   175,
       0,   180,   184,   189,     0,     0,     0,     0,   133,     0,
      15,     0,   152,     0,   171,   172,   173,     0,   135,   157,
       0,    63,   174
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -322,  -322,  -322,  -322,   456,  -322,  -322,  -322,  -322,  -322,
    -322,  -322,  -322,  -322,  -322,  -322,    22,  -322,   -40,   -71,
     294,    80,  -322,    13,  -175,  -322,   -39,  -322,  -322,  -322,
      32,  -130,   302,   237,  -127,  -322,   171,   -42,  -322,  -142,
    -322,  -322,   -50,  -321,   -61,  -322,   -75,  -322,  -322,    86,
    -133,  -322,   310,  -160,  -322,  -148,  -322
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    14,    15,    16,    17,    18,    45,    19,    20,    21,
      22,    23,    35,    24,    25,    26,    89,    90,    38,    91,
      92,    93,   110,    94,   118,   290,   111,   112,   297,   113,
     121,    96,    97,   173,    98,    99,   100,   128,   129,   162,
     163,   142,   101,    40,   102,   375,   103,   104,   386,   387,
     123,   309,   248,   124,   258,   259,   294
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     106,   122,   137,   222,   220,   218,   249,   249,   114,   119,
     108,   224,   159,    29,   130,   119,   363,   160,   242,   339,
     289,   262,    27,     9,    10,    11,   299,   238,   368,    29,
     193,   194,   153,   154,   155,    30,   253,   158,    27,  -105,
    -105,  -105,   165,   166,   167,   168,   169,   264,   302,   165,
      52,   167,   367,   169,    53,   133,   210,   256,   241,   134,
     131,   388,   135,   117,   132,   170,   171,   251,   303,    95,
     203,   119,   170,   171,    31,   109,   231,   232,   -56,    33,
      28,   214,    34,   219,   196,   333,   122,   212,   197,   317,
     318,   252,   334,   312,   229,   230,    28,    46,   131,    47,
     266,   268,   305,    86,   246,   329,   237,   331,   332,    86,
    -105,    32,   335,   336,    43,    44,   247,   247,   286,   288,
      95,   340,   140,   341,   141,   265,   267,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   287,   217,   193,   194,   347,   253,
     298,   343,   204,   205,   344,   254,   300,   301,   122,    95,
     295,     9,    10,    11,    95,    86,    36,   354,   255,    37,
     256,   225,   164,    39,    47,   228,   122,    41,   218,    95,
      95,   233,   234,   235,   236,   359,   360,    48,    51,   325,
     190,   191,   192,   251,   226,    95,   227,   119,    49,   107,
     257,   257,   384,    50,   385,   105,    95,   251,   117,   115,
     108,   119,    54,   365,   117,   125,   119,   252,    58,    59,
     126,   116,    60,    61,    62,    63,    64,    65,     1,     2,
      66,   252,   136,    67,    68,    69,   377,    70,   186,   187,
     188,   189,   190,   191,   192,    73,   127,   138,   139,   143,
      74,   144,    75,   145,    76,    77,   146,   161,   122,   313,
     147,   148,   149,   150,    78,    79,    80,    81,   188,   189,
     190,   191,   192,   151,   152,   260,   156,   122,   355,   157,
     172,   254,    82,   174,   195,   257,   199,   257,   257,   198,
     200,    86,   257,   257,   255,   254,   261,   201,   202,   131,
      83,   211,   209,   370,   213,    86,    84,   119,   255,    85,
      86,   221,   223,    87,   243,   291,   292,    88,   383,   122,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   380,   293,    95,   256,   345,
     261,   307,   308,   310,   326,   328,    54,    55,    56,   311,
     215,   314,    58,    59,   330,   319,    60,    61,    62,    63,
      64,    65,     1,     2,    66,   257,   257,    67,    68,    69,
     194,    70,   320,   321,   322,   337,   342,    71,    72,    73,
     338,   348,   349,   351,    74,   350,    75,   356,    76,    77,
     352,   357,   358,     9,    10,    11,   362,   364,    78,    79,
      80,    81,   216,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,    82,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,    83,   366,   361,   369,   374,   371,
      84,   373,   376,    85,    86,   379,   381,    87,    54,    55,
      56,    88,    57,   382,    58,    59,   390,   245,    60,    61,
      62,    63,    64,    65,     1,     2,    66,   389,   391,    67,
      68,    69,    42,    70,   263,   324,   392,   250,   346,    71,
      72,    73,   244,     0,     0,     0,    74,     0,    75,     0,
      76,    77,     0,     0,     0,     9,    10,    11,     0,     0,
      78,    79,    80,    81,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,    82,   207,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,    83,     0,     0,     0,
       0,     0,    84,     0,     0,    85,    86,     0,     0,    87,
      54,    55,    56,    88,    57,     0,    58,    59,     0,     0,
      60,    61,    62,    63,    64,    65,     1,     2,    66,     0,
       0,    67,    68,    69,     0,    70,     0,     0,     0,     0,
       0,    71,    72,    73,     0,     0,     0,     0,    74,     0,
      75,     0,    76,    77,     0,     0,     0,     9,    10,    11,
       0,     0,    78,    79,    80,    81,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,     0,     0,     0,
      82,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,     0,    83,     0,
       0,     0,     0,     0,    84,     0,     0,    85,    86,     0,
       0,    87,    54,    55,    56,    88,   215,     0,    58,    59,
       0,     0,    60,    61,    62,    63,    64,    65,     1,     2,
      66,     0,     0,    67,    68,    69,     0,    70,     0,     0,
       0,     0,     0,    71,    72,    73,     0,     0,     0,     0,
      74,     0,    75,     0,    76,    77,     0,     0,     0,     0,
       0,     0,     0,     0,    78,    79,    80,    81,     0,    54,
       0,     0,     0,   119,     0,    58,     0,     0,     0,    60,
      61,     0,    82,     0,     0,     0,     0,    66,     0,     0,
      67,    68,    69,     0,    70,     0,     0,     0,     0,     0,
      83,     0,     0,     0,     0,     0,    84,     0,     0,    85,
      86,    76,    77,    87,     0,     0,     0,    88,     0,     0,
       0,     0,    54,     0,     0,     0,   119,     0,    58,     0,
       0,     0,    60,    61,    62,     0,     0,     0,     0,    82,
      66,     0,     0,    67,    68,    69,     0,    70,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    83,     0,     0,
       0,     0,     0,    84,    76,    77,    85,    86,     0,     0,
     120,     0,   296,     0,    78,    79,    80,    81,     0,    54,
       0,     0,     0,   119,   239,    58,     0,     0,     0,    60,
      61,     0,    82,     0,     0,     0,     0,    66,     0,     0,
      67,    68,    69,     0,    70,     0,     0,     0,     0,     0,
      83,     0,     0,     0,     0,     0,    84,     0,     0,    85,
      86,    76,    77,    87,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   239,     0,     0,     0,     0,     0,     0,    82,
       0,     0,   240,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    83,     0,     0,
       0,     0,     0,    84,     0,     0,    85,    86,     0,     0,
     120,     0,   206,   207,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
      -3,     0,     0,     0,     0,     0,   -46,     0,   -46,     0,
     240,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       2,     0,     3,     4,     0,     0,     0,     0,     0,     5,
       0,     6,   -46,     0,   -46,     0,     0,     7,     0,     0,
       0,     0,     0,     0,     0,     1,     2,     8,     3,     4,
       9,    10,    11,     0,     0,     5,     0,     6,     0,     0,
       0,    12,    13,     7,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     8,     0,     0,     9,    10,    11,     0,
       0,     0,     0,     0,     0,     0,     0,    12,    13,   206,
     207,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   327,     0,     0,     0,
       0,     0,     0,   208,   206,   207,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   208,   206,
     207,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   353,   206,   207,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   304,   206,   207,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   306,   206,   207,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   315,   206,   207,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   316,   206,   207,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   323,   206,   207,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     372,   206,   207,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   378,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   206,   207,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192
};

static const yytype_int16 yycheck[] =
{
      40,    51,    63,   136,   134,   132,   166,   167,    47,     7,
       7,     3,    87,     0,    56,     7,   337,    88,   160,     7,
     195,   169,     0,    50,    51,    52,   201,   157,   349,    16,
      77,    78,    82,    83,    84,    11,    85,    87,    16,    38,
      39,    40,    72,    73,    74,    75,    76,   174,   208,    72,
       3,    74,    75,    76,     7,   106,   127,   106,   105,   110,
     106,   382,   113,    50,   110,    95,    96,     3,   210,    37,
     120,     7,    95,    96,    11,    72,   147,   148,   105,     7,
       0,   131,    10,   133,   106,   104,   136,   129,   110,   231,
     232,    27,   111,   226,   144,   145,    16,     6,   106,     8,
     175,   176,   110,   101,   165,   253,   156,   255,   256,   101,
     109,     7,   260,   261,    48,    49,   166,   167,   193,   194,
      88,   109,     7,   111,     9,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   132,    77,    78,   308,    85,
     200,   110,    75,    76,   113,    91,   206,   207,   208,   127,
     199,    50,    51,    52,   132,   101,   106,   327,   104,   108,
     106,   139,     6,    53,     8,   143,   226,     0,   305,   147,
     148,   149,   150,   151,   152,   333,   334,    11,   104,   239,
      92,    93,    94,     3,   104,   163,   106,     7,    11,     7,
     168,   169,     6,   108,     8,     3,   174,     3,   195,    11,
       7,     7,     3,   343,   201,   107,     7,    27,     9,    10,
     107,    11,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    27,   104,    24,    25,    26,   369,    28,    88,    89,
      90,    91,    92,    93,    94,    36,    40,   104,   104,   104,
      41,   104,    43,   104,    45,    46,     7,    37,   308,   227,
     108,   108,   104,   104,    55,    56,    57,    58,    90,    91,
      92,    93,    94,   104,   104,    85,   104,   327,   328,   112,
     112,    91,    73,    44,   104,   253,   111,   255,   256,   108,
      72,   101,   260,   261,   104,    91,   106,    37,   109,   106,
      91,    38,   105,   353,    39,   101,    97,     7,   104,   100,
     101,     7,    11,   104,   109,     3,     3,   108,   379,   369,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,   375,     7,   305,   106,   307,
     106,   105,   111,   105,   109,   104,     3,     4,     5,   105,
       7,   105,     9,    10,     3,   105,    13,    14,    15,    16,
      17,    18,    19,    20,    21,   333,   334,    24,    25,    26,
      78,    28,   105,   105,   105,   105,     3,    34,    35,    36,
     107,   105,   105,   109,    41,   107,    43,    84,    45,    46,
     109,   105,   107,    50,    51,    52,   107,   107,    55,    56,
      57,    58,    59,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    73,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    91,     7,    84,   104,    54,   105,
      97,   105,    33,   100,   101,   104,   108,   104,     3,     4,
       5,   108,     7,   105,     9,    10,   111,   163,    13,    14,
      15,    16,    17,    18,    19,    20,    21,   105,   109,    24,
      25,    26,    16,    28,   172,   238,   390,   167,   307,    34,
      35,    36,    37,    -1,    -1,    -1,    41,    -1,    43,    -1,
      45,    46,    -1,    -1,    -1,    50,    51,    52,    -1,    -1,
      55,    56,    57,    58,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    73,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    91,    -1,    -1,    -1,
      -1,    -1,    97,    -1,    -1,   100,   101,    -1,    -1,   104,
       3,     4,     5,   108,     7,    -1,     9,    10,    -1,    -1,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    24,    25,    26,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    -1,    -1,    -1,    -1,    41,    -1,
      43,    -1,    45,    46,    -1,    -1,    -1,    50,    51,    52,
      -1,    -1,    55,    56,    57,    58,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    -1,    -1,    -1,
      73,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    -1,    91,    -1,
      -1,    -1,    -1,    -1,    97,    -1,    -1,   100,   101,    -1,
      -1,   104,     3,     4,     5,   108,     7,    -1,     9,    10,
      -1,    -1,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,    -1,    24,    25,    26,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,    -1,
      41,    -1,    43,    -1,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    56,    57,    58,    -1,     3,
      -1,    -1,    -1,     7,    -1,     9,    -1,    -1,    -1,    13,
      14,    -1,    73,    -1,    -1,    -1,    -1,    21,    -1,    -1,
      24,    25,    26,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,   100,
     101,    45,    46,   104,    -1,    -1,    -1,   108,    -1,    -1,
      -1,    -1,     3,    -1,    -1,    -1,     7,    -1,     9,    -1,
      -1,    -1,    13,    14,    15,    -1,    -1,    -1,    -1,    73,
      21,    -1,    -1,    24,    25,    26,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      -1,    -1,    -1,    97,    45,    46,   100,   101,    -1,    -1,
     104,    -1,   106,    -1,    55,    56,    57,    58,    -1,     3,
      -1,    -1,    -1,     7,    37,     9,    -1,    -1,    -1,    13,
      14,    -1,    73,    -1,    -1,    -1,    -1,    21,    -1,    -1,
      24,    25,    26,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,   100,
     101,    45,    46,   104,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    37,    -1,    -1,    -1,    -1,    -1,    -1,    73,
      -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      -1,    -1,    -1,    97,    -1,    -1,   100,   101,    -1,    -1,
     104,    -1,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
       0,    -1,    -1,    -1,    -1,    -1,     6,    -1,     8,    -1,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      20,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    31,     6,    -1,     8,    -1,    -1,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    20,    47,    22,    23,
      50,    51,    52,    -1,    -1,    29,    -1,    31,    -1,    -1,
      -1,    61,    62,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    -1,    50,    51,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,    -1,    -1,
      -1,    -1,    -1,   111,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   110,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   107,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   105,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   105,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   105,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     105,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    20,    22,    23,    29,    31,    37,    47,    50,
      51,    52,    61,    62,   115,   116,   117,   118,   119,   121,
     122,   123,   124,   125,   127,   128,   129,   130,   135,   137,
      11,    11,     7,     7,    10,   126,   106,   108,   132,    53,
     157,     0,   118,    48,    49,   120,     6,     8,    11,    11,
     108,   104,     3,     7,     3,     4,     5,     7,     9,    10,
      13,    14,    15,    16,    17,    18,    21,    24,    25,    26,
      28,    34,    35,    36,    41,    43,    45,    46,    55,    56,
      57,    58,    73,    91,    97,   100,   101,   104,   108,   130,
     131,   133,   134,   135,   137,   144,   145,   146,   148,   149,
     150,   156,   158,   160,   161,     3,   132,     7,     7,    72,
     136,   140,   141,   143,   140,    11,    11,   137,   138,     7,
     104,   144,   156,   164,   167,   107,   107,    40,   151,   152,
     151,   106,   110,   106,   110,   113,   104,   158,   104,   104,
       7,     9,   155,   104,   104,   104,     7,   108,   108,   104,
     104,   104,   104,   156,   156,   156,   104,   112,   156,   160,
     133,    37,   153,   154,     6,    72,    73,    74,    75,    76,
      95,    96,   112,   147,    44,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    77,    78,   104,   106,   110,   108,   111,
      72,    37,   109,   156,    75,    76,    77,    78,   111,   105,
     133,    38,   151,    39,   156,     7,    59,   137,   148,   156,
     145,     7,   164,    11,     3,   144,   104,   106,   144,   156,
     156,   133,   133,   144,   144,   144,   144,   156,   145,    37,
     105,   105,   153,   109,    37,   134,   158,   156,   166,   167,
     166,     3,    27,    85,    91,   104,   106,   144,   168,   169,
      85,   106,   169,   146,   148,   156,   160,   156,   160,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   160,   156,   160,   138,
     139,     3,     3,     7,   170,   140,   106,   142,   156,   138,
     156,   156,   167,   153,   107,   110,   107,   105,   111,   165,
     105,   105,   164,   144,   105,   105,   105,   153,   153,   105,
     105,   105,   105,   105,   147,   156,   109,   104,   104,   169,
       3,   169,   169,   104,   111,   169,   169,   105,   107,     7,
     109,   111,     3,   110,   113,   144,   150,   167,   105,   105,
     107,   109,   109,   110,   167,   156,    84,   105,   107,   169,
     169,    84,   107,   157,   107,   145,     7,    75,   157,   104,
     156,   105,   105,   105,    54,   159,    33,   164,   105,   104,
     132,   108,   105,   158,     6,     8,   162,   163,   157,   105,
     111,   109,   163
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   114,   115,   116,   117,   117,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   119,   120,   120,   121,   121,
     121,   121,   122,   123,   124,   125,   126,   126,   127,   128,
     128,   129,   129,   129,   129,   130,   130,   131,   132,   133,
     133,   134,   134,   134,   134,   134,   135,   135,   135,   135,
     136,   136,   137,   137,   138,   138,   139,   139,   140,   140,
     141,   141,   141,   142,   143,   143,   143,   144,   145,   145,
     146,   146,   147,   147,   148,   148,   149,   149,   149,   149,
     149,   149,   149,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   151,   151,   152,   153,   153,   154,   154,   155,   155,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   157,   157,   158,   158,   159,   159,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   161,   161,   161,
     161,   162,   162,   163,   163,   164,   164,   165,   165,   166,
     166,   167,   167,   168,   168,   168,   168,   169,   169,   169,
     169,   170,   170,   170
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     9,     1,     1,     0,     1,
       4,     4,     3,     2,     5,     6,     1,     1,     5,     1,
       1,     3,     3,     4,     4,     1,     1,     1,     4,     1,
       3,     1,     3,     3,     1,     3,     0,     1,     1,     1,
       0,     1,     3,     3,     1,     3,     0,     1,     1,     3,
       1,     3,     3,     7,     1,     3,     4,     1,     1,     4,
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
       4,     1,     1,     1,     3,     0,     1,     0,     2,     1,
       4,     1,     3,     1,     4,     1,     2,     1,     3,     4,
       3,     1,     2,     2
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
#line 2040 "y.tab.c"
    break;

  case 4:
#line 140 "promela.y"
                                                                                { std::cout<< "REDUCE: unit -> units\n"; }
#line 2046 "y.tab.c"
    break;

  case 5:
#line 141 "promela.y"
                                                                                { std::cout<< "REDUCE: units unit -> units\n"; }
#line 2052 "y.tab.c"
    break;

  case 6:
#line 144 "promela.y"
                                                        { std::cout<< "REDUCE: proc -> unit\n"; *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2058 "y.tab.c"
    break;

  case 7:
#line 145 "promela.y"
                                                                { std::cout<< "REDUCE: init -> unit\n"; *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2064 "y.tab.c"
    break;

  case 8:
#line 146 "promela.y"
                                                                { std::cout << "The 'events' construct is currently not supported."; }
#line 2070 "y.tab.c"
    break;

  case 9:
#line 147 "promela.y"
                                                                { 
													std::cout << "REDUCE: one_decl -> unit\n"; 
													if ((yyvsp[0].pSymTabVal)->getType() == symTabNode::T_CHAN) 
														(yyval.pStmntVal) = new chanDecl(static_cast<chanSymNode*>((yyvsp[0].pSymTabVal)), nbrLines);
													else {
														assert((yyvsp[0].pSymTabVal)->getType() != symTabNode::T_MTYPE_DEF && (yyvsp[0].pSymTabVal)->getType() != symTabNode::T_UTYPE);
														(yyval.pStmntVal) = new varDecl(static_cast<varSymNode*>((yyvsp[0].pSymTabVal)), nbrLines);
													}
													*globalSymTab = symTabNode::merge(*globalSymTab, (yyvsp[0].pSymTabVal));
													*program = stmnt::merge(*program, (yyval.pStmntVal));
												}
#line 2086 "y.tab.c"
    break;

  case 10:
#line 158 "promela.y"
                                                                { std::cout << "REDUCE: utype -> unit\n"; *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2092 "y.tab.c"
    break;

  case 11:
#line 159 "promela.y"
                                                                                        { std::cout << "REDUCE: mtype -> unit\n"; *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2098 "y.tab.c"
    break;

  case 12:
#line 160 "promela.y"
                                                                { std::cout << "Embedded C code is not supported."; }
#line 2104 "y.tab.c"
    break;

  case 13:
#line 161 "promela.y"
                                                                { std::cout << "The 'named sequence' construct is currently not supported."; }
#line 2110 "y.tab.c"
    break;

  case 15:
#line 171 "promela.y"
                                                                                        {	
		  											std::cout<< "REDUCE: inst proctype NAME ( decl ) prio ena body -> proc\n";
		  											
		  											procSymNode* proc = new procSymNode((yyvsp[-6].sVal), (yyvsp[-8].pConstExprVal), (yyvsp[-4].pVarSymVal), (yyvsp[0].pStmntVal), nbrLines);
		  											(yyval.pStmntVal) = new procDecl(proc, nbrLines);
		  											(yyval.pStmntVal)->setLocalSymTab(static_cast<varSymNode*>(symTabNode::deepcopy((yyvsp[-4].pVarSymVal))));
		  											*globalSymTab = symTabNode::merge(*globalSymTab, proc);
		  										}
#line 2123 "y.tab.c"
    break;

  case 16:
#line 181 "promela.y"
                                                                                { std::cout << "REDUCE: -> PROCTYPE proctype\n"; }
#line 2129 "y.tab.c"
    break;

  case 17:
#line 182 "promela.y"
                                                                                { std::cout << "Deterministic proctypes are not supported (only useful for simulation)."; }
#line 2135 "y.tab.c"
    break;

  case 18:
#line 185 "promela.y"
                                                                        { std::cout << "REDUCE: void -> inst\n"; (yyval.pConstExprVal) = new exprConst(0, nbrLines); }
#line 2141 "y.tab.c"
    break;

  case 19:
#line 186 "promela.y"
                                                                                        { std::cout << "REDUCE: ACTIVE -> inst\n"; (yyval.pConstExprVal) = new exprConst(1, nbrLines); }
#line 2147 "y.tab.c"
    break;

  case 20:
#line 187 "promela.y"
                                                                        { std::cout << "REDUCE: ACTIVE [ CONST ] -> inst \n"; (yyval.pConstExprVal) = new exprConst((yyvsp[-1].iVal), nbrLines); }
#line 2153 "y.tab.c"
    break;

  case 21:
#line 188 "promela.y"
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
#line 2169 "y.tab.c"
    break;

  case 22:
#line 201 "promela.y"
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
#line 2184 "y.tab.c"
    break;

  case 23:
#line 213 "promela.y"
                                                                        { std::cout << "Event sequences (traces) are not supported."; }
#line 2190 "y.tab.c"
    break;

  case 24:
#line 216 "promela.y"
                                                        {	
													std::cout << "REDUCE: TYPEDEF NAME '{' decl_lst '}' -> utype\n";
													tdefSymNode* tdef = new tdefSymNode((yyvsp[-3].sVal), (yyvsp[-1].pVarSymVal), nbrLines);
													(yyval.pStmntVal) = new tdefDecl(tdef, nbrLines);
													*globalSymTab = symTabNode::merge(*globalSymTab, tdef);
													free((yyvsp[-3].sVal));  
												}
#line 2202 "y.tab.c"
    break;

  case 25:
#line 225 "promela.y"
                                                        {	
													std::cout << "REDUCE: vis TYPE asgn { nlst } -> one_decl\n";
													if((yyvsp[-4].iType) != symTabNode::T_MTYPE) {
														std::cout <<  "This syntax only works for MTYPEs.";
														exit(1);
													}
													mtypedefSymNode* mtypeDef = new mtypedefSymNode((yyvsp[-1].pMTypeListVal), nbrLines);
													*globalSymTab = symTabNode::merge(*globalSymTab, mtypeDef);
													(yyval.pStmntVal) = new mtypeDecl(mtypeDef, nbrLines);
													// The mtype values are added in the nlst rule.
												}
#line 2218 "y.tab.c"
    break;

  case 38:
#line 262 "promela.y"
                                                                { std::cout << "REDUCE: '{' sequence OS '}' -> body\n"; (yyval.pStmntVal) = (yyvsp[-2].pStmntVal); }
#line 2224 "y.tab.c"
    break;

  case 39:
#line 265 "promela.y"
                                                                                { 	std::cout << "REDUCE: step -> sequence\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal);   }
#line 2230 "y.tab.c"
    break;

  case 40:
#line 266 "promela.y"
                                                                                {	std::cout << "REDUCE: sequence MS step -> sequence\n"; (yyval.pStmntVal) = stmnt::merge((yyval.pStmntVal), (yyvsp[0].pStmntVal)); }
#line 2236 "y.tab.c"
    break;

  case 41:
#line 269 "promela.y"
                                                                                { 
													assert((yyvsp[0].pSymTabVal)->getType() != symTabNode::T_MTYPE_DEF && (yyvsp[0].pSymTabVal)->getType() != symTabNode::T_CHAN); 
												 	(yyval.pStmntVal) = new varDecl(static_cast<varSymNode*>((yyvsp[0].pSymTabVal)), nbrLines); 
												}
#line 2245 "y.tab.c"
    break;

  case 42:
#line 273 "promela.y"
                                                                                { std::cout << "Declarations with labels are not suported."; }
#line 2251 "y.tab.c"
    break;

  case 43:
#line 274 "promela.y"
                                                                                { std::cout << "Channel assertions are currently not supported."; }
#line 2257 "y.tab.c"
    break;

  case 44:
#line 275 "promela.y"
                                                                                        { std::cout << "REDUCE: stmnt -> step\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2263 "y.tab.c"
    break;

  case 45:
#line 276 "promela.y"
                                                                        { std::cout << "Unless statements are currently not supported."; }
#line 2269 "y.tab.c"
    break;

  case 47:
#line 285 "promela.y"
                                                                                        { std::cout << "The 'hidden' keyword is not supported."; }
#line 2275 "y.tab.c"
    break;

  case 48:
#line 286 "promela.y"
                                                                                        { std::cout << "The 'show' keyword is not supported."; }
#line 2281 "y.tab.c"
    break;

  case 49:
#line 287 "promela.y"
                                                                                        { std::cout << "The 'local' keyword is not supported."; }
#line 2287 "y.tab.c"
    break;

  case 52:
#line 297 "promela.y"
                                                                        {	std::cout << "REDUCE: vis TYPE var_list -> one_decl\n";
													varSymNode* cur = (yyvsp[0].pVarSymVal);
													varSymNode* res = nullptr;
													while(cur != nullptr) {
														varSymNode* tmp = nullptr;
														
														if(cur->getType() == symTabNode::T_NA) { 
															varSymNode* next = varSymNode::createSymTabNode((yyvsp[-1].iType), cur->getLineNb(), cur->getName(), cur->getBound(), cur->getInitExpr());
															// If type != 0, then the var is a T_CHAN
														
															//cur->getType() = $2
															if(res == nullptr) {
																res = next;
																tmp = next;
															} else {
																tmp->makeNext(next);
																tmp = static_cast<varSymNode*>(tmp->nextSym());
															}
														} else if (cur->getType() == symTabNode::T_CHAN) {
															res = (yyvsp[0].pVarSymVal);
															break;
														}
														
														//cur->detachChildAndInitSymNodes();
														cur = static_cast<varSymNode*>(cur->nextSym());
													}
													//delete $3;
													(yyval.pSymTabVal) = res;
												}
#line 2321 "y.tab.c"
    break;

  case 53:
#line 326 "promela.y"
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
#line 2341 "y.tab.c"
    break;

  case 54:
#line 343 "promela.y"
                                                                                { std::cout << "REDUCE: one_decl -> decl_list\n"; (yyval.pVarSymVal) = static_cast<varSymNode*>((yyvsp[0].pSymTabVal)); }
#line 2347 "y.tab.c"
    break;

  case 55:
#line 344 "promela.y"
                                                                        { std::cout << "REDUCE: one_decl SEMI decl_list -> decl_lst\n"; (yyval.pVarSymVal) = varSymNode::merge(static_cast<varSymNode*>((yyvsp[-2].pSymTabVal)), (yyvsp[0].pVarSymVal)); }
#line 2353 "y.tab.c"
    break;

  case 56:
#line 348 "promela.y"
                                                                        { std::cout << "REDUCE: void -> decl\n"; (yyval.pVarSymVal) = nullptr; }
#line 2359 "y.tab.c"
    break;

  case 57:
#line 349 "promela.y"
                                                                                        { std::cout << "REDUCE: decl_list -> decl\n"; (yyval.pVarSymVal) = (yyvsp[0].pVarSymVal); }
#line 2365 "y.tab.c"
    break;

  case 58:
#line 356 "promela.y"
                                                                                { std::cout << "REDUCE: ivar -> var_list\n"; (yyval.pVarSymVal) = (yyvsp[0].pVarSymVal); }
#line 2371 "y.tab.c"
    break;

  case 59:
#line 357 "promela.y"
                                                                                { std::cout << "REDUCE: ivar , var_list -> var_list\n"; (yyval.pVarSymVal) = varSymNode::merge((yyvsp[-2].pVarSymVal), (yyvsp[0].pVarSymVal)); }
#line 2377 "y.tab.c"
    break;

  case 60:
#line 360 "promela.y"
                                                                                { std::cout << "REDUCE: var_decl -> ivar\n"; (yyval.pVarSymVal) = varSymNode::createSymTabNode((yyvsp[0].pDataVal).iType, nbrLines, (yyvsp[0].pDataVal).sVal, (yyvsp[0].pDataVal).iVal); }
#line 2383 "y.tab.c"
    break;

  case 61:
#line 361 "promela.y"
                                                                                { std::cout << "REDUCE: var_decl ASGN expr -> ivar\n"; (yyval.pVarSymVal) = varSymNode::createSymTabNode((yyvsp[-2].pDataVal).iType, nbrLines, (yyvsp[-2].pDataVal).sVal, (yyvsp[-2].pDataVal).iVal, (yyvsp[0].pExprVal)); }
#line 2389 "y.tab.c"
    break;

  case 62:
#line 362 "promela.y"
                                                                        { std::cout << "REDUCE: var_decl ASGN ch_init -> ivar\n"; (yyval.pVarSymVal) = new chanSymNode(nbrLines, (yyvsp[-2].pDataVal).sVal, (yyvsp[-2].pDataVal).iVal, (yyvsp[0].pDataVal).iVal, (yyvsp[0].pDataVal).symTabNodeVal); }
#line 2395 "y.tab.c"
    break;

  case 63:
#line 365 "promela.y"
                                                        { std::cout << "REDUCE: [ CONST ] OF { typ_list } -> ch_init\n"; (yyval.pDataVal).iVal = (yyvsp[-5].iVal); (yyval.pDataVal).symTabNodeVal = (yyvsp[-1].pVarSymVal); }
#line 2401 "y.tab.c"
    break;

  case 64:
#line 368 "promela.y"
                                                                                { std::cout << "REDUCE: NAME -> vardcl\n"; (yyval.pDataVal).sVal = (yyvsp[0].sVal); (yyval.pDataVal).iVal = 1; }
#line 2407 "y.tab.c"
    break;

  case 65:
#line 369 "promela.y"
                                                                                { std::cout << "The 'unsigned' data type is not supported."; }
#line 2413 "y.tab.c"
    break;

  case 66:
#line 370 "promela.y"
                                                                        { std::cout << "REDUCE: NAME [ CONST ] -> vardcl\n"; (yyval.pDataVal).sVal = (yyvsp[-3].sVal); (yyval.pDataVal).iVal = (yyvsp[-1].iVal); }
#line 2419 "y.tab.c"
    break;

  case 67:
#line 373 "promela.y"
                                                                                { std::cout << "REDUCE: cmpnd -> varref\n"; (yyval.pExprVarRefVal) = (yyvsp[0].pExprVarRefVal); }
#line 2425 "y.tab.c"
    break;

  case 68:
#line 376 "promela.y"
                                                                                { std::cout << "REDUCE: NAME -> pfld\n"; (yyval.pExprVarRefNameVal) = new exprVarRefName((yyvsp[0].sVal), nbrLines); free((yyvsp[0].sVal)); }
#line 2431 "y.tab.c"
    break;

  case 69:
#line 377 "promela.y"
                                                                                { std::cout << "REDUCE: NAME [ expr ] -> pfld\n"; (yyval.pExprVarRefNameVal) = new exprVarRefName((yyvsp[-3].sVal), (yyvsp[-1].pExprVal), nbrLines); free((yyvsp[-3].sVal)); }
#line 2437 "y.tab.c"
    break;

  case 70:
#line 380 "promela.y"
                                                                                { std::cout << "REDUCE: pfld sfld -> cmpnd\n"; (yyval.pExprVarRefVal) = new exprVarRef(nbrLines, (yyvsp[-1].pExprVarRefNameVal), (yyvsp[0].pExprVarRefVal)); }
#line 2443 "y.tab.c"
    break;

  case 71:
#line 381 "promela.y"
                                                                        { std::cout << "REDUCE: CONTEX . pfld sfld -> cmpnd\n"; (yyval.pExprVarRefVal) = new exprVarRef(nbrLines, (yyvsp[-1].pExprVarRefNameVal), (yyvsp[0].pExprVarRefVal)); }
#line 2449 "y.tab.c"
    break;

  case 72:
#line 384 "promela.y"
                                                                                        { std::cout << "REDUCE: void -> sfld\n"; (yyval.pExprVarRefVal) = nullptr; }
#line 2455 "y.tab.c"
    break;

  case 73:
#line 385 "promela.y"
                                                                        { std::cout << "REDUCE: . cmpnd -> sfld\n"; (yyval.pExprVarRefVal) = (yyvsp[0].pExprVarRefVal);   }
#line 2461 "y.tab.c"
    break;

  case 74:
#line 389 "promela.y"
                                                                                { std::cout << "REDUCE: special -> stmnt\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2467 "y.tab.c"
    break;

  case 75:
#line 390 "promela.y"
                                                                                        { std::cout << "REDUCE: Stmnt -> stmnt\n"; (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2473 "y.tab.c"
    break;

  case 76:
#line 393 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntChanRecv((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprArgListVal), nbrLines); }
#line 2479 "y.tab.c"
    break;

  case 77:
#line 394 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntChanSnd((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprArgListVal), nbrLines); }
#line 2485 "y.tab.c"
    break;

  case 78:
#line 395 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntIf((yyvsp[-1].pStmntOptVal), (yyvsp[-2].iVal)); }
#line 2491 "y.tab.c"
    break;

  case 79:
#line 396 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntDo((yyvsp[-1].pStmntOptVal), (yyvsp[-2].iVal)); }
#line 2497 "y.tab.c"
    break;

  case 80:
#line 397 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntBreak(nbrLines); }
#line 2503 "y.tab.c"
    break;

  case 81:
#line 398 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntGoto((yyvsp[0].sVal), nbrLines); free((yyvsp[0].sVal)); }
#line 2509 "y.tab.c"
    break;

  case 82:
#line 399 "promela.y"
                                                                                { if((yyvsp[0].pStmntVal)->getType() == astNode::E_STMNT_LABEL && static_cast<stmntLabel*>((yyvsp[0].pStmntVal))->getLabelledStmnt()->getType() == astNode::E_STMNT_LABEL) 
													std::cout << "Only two labels per state are supported."; 
												  (yyval.pStmntVal) = new stmntLabel((yyvsp[-2].sVal), (yyvsp[0].pStmntVal), nbrLines); free((yyvsp[-2].sVal)); }
#line 2517 "y.tab.c"
    break;

  case 83:
#line 403 "promela.y"
                                                                { (yyval.pStmntVal) = new stmntAsgn((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2523 "y.tab.c"
    break;

  case 84:
#line 404 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntIncr((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2529 "y.tab.c"
    break;

  case 85:
#line 405 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntDecr((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2535 "y.tab.c"
    break;

  case 86:
#line 406 "promela.y"
                                                                { (yyval.pStmntVal) = new stmntPrint((yyvsp[-2].sVal), (yyvsp[-1].pExprArgListVal), nbrLines); }
#line 2541 "y.tab.c"
    break;

  case 87:
#line 407 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntPrintm((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2547 "y.tab.c"
    break;

  case 88:
#line 408 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntPrintm((yyvsp[-1].iVal), nbrLines); }
#line 2553 "y.tab.c"
    break;

  case 89:
#line 409 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntAssert((yyvsp[0].pExprVal), nbrLines); }
#line 2559 "y.tab.c"
    break;

  case 90:
#line 410 "promela.y"
                                                                                        { std::cout << "Embedded C code is not supported."; }
#line 2565 "y.tab.c"
    break;

  case 91:
#line 411 "promela.y"
                                                                        { std::cout << "Sorted send and random receive are not supported."; }
#line 2571 "y.tab.c"
    break;

  case 92:
#line 412 "promela.y"
                                                                        { std::cout << "Channel poll operations are not supported."; }
#line 2577 "y.tab.c"
    break;

  case 93:
#line 413 "promela.y"
                                                                        { std::cout << "Channel poll operations are not supported."; }
#line 2583 "y.tab.c"
    break;

  case 94:
#line 414 "promela.y"
                                                                        { std::cout << "Sorted send and random receive are not supported."; }
#line 2589 "y.tab.c"
    break;

  case 95:
#line 415 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntExpr((yyvsp[0].pExprVal), nbrLines); }
#line 2595 "y.tab.c"
    break;

  case 96:
#line 416 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntElse(nbrLines); }
#line 2601 "y.tab.c"
    break;

  case 97:
#line 417 "promela.y"
                                                                { (yyval.pStmntVal) = new stmntAtomic((yyvsp[-2].pStmntVal), nbrLines); }
#line 2607 "y.tab.c"
    break;

  case 98:
#line 418 "promela.y"
                                                                { std::cout << "Deterministic steps are not yet supported."; }
#line 2613 "y.tab.c"
    break;

  case 99:
#line 419 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntSeq((yyvsp[-2].pStmntVal), nbrLines); }
#line 2619 "y.tab.c"
    break;

  case 100:
#line 420 "promela.y"
                                                                        { std::cout << "Inline calls are not yet supported."; }
#line 2625 "y.tab.c"
    break;

  case 101:
#line 423 "promela.y"
                                                                                { (yyval.pStmntOptVal) = new stmntOpt((yyvsp[0].pStmntVal), nbrLines); }
#line 2631 "y.tab.c"
    break;

  case 102:
#line 424 "promela.y"
                                                                                { (yyval.pStmntOptVal) = new stmntOpt((yyvsp[-1].pStmntVal), (yyvsp[0].pStmntOptVal), nbrLines); }
#line 2637 "y.tab.c"
    break;

  case 103:
#line 427 "promela.y"
                                                                        { (yyval.pStmntVal) = (yyvsp[-1].pStmntVal); }
#line 2643 "y.tab.c"
    break;

  case 105:
#line 441 "promela.y"
                                        { /* redundant semi at end of sequence */ }
#line 2649 "y.tab.c"
    break;

  case 106:
#line 444 "promela.y"
                                        { /* at least one semi-colon */ }
#line 2655 "y.tab.c"
    break;

  case 107:
#line 445 "promela.y"
                                        { /* but more are okay too   */ }
#line 2661 "y.tab.c"
    break;

  case 108:
#line 448 "promela.y"
                                                                                { (yyval.sVal) = (yyvsp[0].sVal); }
#line 2667 "y.tab.c"
    break;

  case 109:
#line 449 "promela.y"
                                                                                        { (yyval.sVal) = (yyvsp[0].sVal); }
#line 2673 "y.tab.c"
    break;

  case 110:
#line 452 "promela.y"
                                                                        { (yyval.pExprVal) = new exprPar		((yyvsp[-1].pExprVal), nbrLines); }
#line 2679 "y.tab.c"
    break;

  case 111:
#line 453 "promela.y"
                                                                                { (yyval.pExprVal) = new exprPlus		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2685 "y.tab.c"
    break;

  case 112:
#line 454 "promela.y"
                                                                                { (yyval.pExprVal) = new exprMinus	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2691 "y.tab.c"
    break;

  case 113:
#line 455 "promela.y"
                                                                                { (yyval.pExprVal) = new exprTimes	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2697 "y.tab.c"
    break;

  case 114:
#line 456 "promela.y"
                                                                                { (yyval.pExprVal) = new exprDiv		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2703 "y.tab.c"
    break;

  case 115:
#line 457 "promela.y"
                                                                                { (yyval.pExprVal) = new exprMod		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2709 "y.tab.c"
    break;

  case 116:
#line 458 "promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2715 "y.tab.c"
    break;

  case 117:
#line 459 "promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwXor	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2721 "y.tab.c"
    break;

  case 118:
#line 460 "promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2727 "y.tab.c"
    break;

  case 119:
#line 461 "promela.y"
                                                                                { (yyval.pExprVal) = new exprGT		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2733 "y.tab.c"
    break;

  case 120:
#line 462 "promela.y"
                                                                                { (yyval.pExprVal) = new exprLT		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2739 "y.tab.c"
    break;

  case 121:
#line 463 "promela.y"
                                                                                { (yyval.pExprVal) = new exprGE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2745 "y.tab.c"
    break;

  case 122:
#line 464 "promela.y"
                                                                                { (yyval.pExprVal) = new exprLE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2751 "y.tab.c"
    break;

  case 123:
#line 465 "promela.y"
                                                                                { (yyval.pExprVal) = new exprEQ		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2757 "y.tab.c"
    break;

  case 124:
#line 466 "promela.y"
                                                                                { (yyval.pExprVal) = new exprNE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2763 "y.tab.c"
    break;

  case 125:
#line 467 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2769 "y.tab.c"
    break;

  case 126:
#line 468 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2775 "y.tab.c"
    break;

  case 127:
#line 469 "promela.y"
                                                                                { (yyval.pExprVal) = new exprLShift	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2781 "y.tab.c"
    break;

  case 128:
#line 470 "promela.y"
                                                                                { (yyval.pExprVal) = new exprRShift	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2787 "y.tab.c"
    break;

  case 129:
#line 471 "promela.y"
                                                                        { (yyval.pExprVal) = new exprCount	((yyvsp[-1].pExprVal), nbrLines); }
#line 2793 "y.tab.c"
    break;

  case 130:
#line 472 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprBitwNeg	((yyvsp[0].pExprVal), nbrLines); }
#line 2799 "y.tab.c"
    break;

  case 131:
#line 473 "promela.y"
                                                                        { 	if((yyvsp[0].pExprVal)->getType() != astNode::E_EXPR_CONST) 
														(yyval.pExprVal) = new exprUMin((yyvsp[0].pExprVal), nbrLines);
													else {
														exprConst* tmp = static_cast<exprConst*>((yyvsp[0].pExprVal));
														tmp->setCstValue(- tmp->getCstValue());
														(yyval.pExprVal) = tmp;
													}
												}
#line 2812 "y.tab.c"
    break;

  case 132:
#line 481 "promela.y"
                                                                        { (yyval.pExprVal) = new exprNeg	((yyvsp[0].pExprVal), nbrLines); }
#line 2818 "y.tab.c"
    break;

  case 133:
#line 482 "promela.y"
                                                                { (yyval.pExprVal) = new exprCond	((yyvsp[-5].pExprVal), (yyvsp[-3].pExprVal), (yyvsp[-1].pExprVal), nbrLines); }
#line 2824 "y.tab.c"
    break;

  case 134:
#line 483 "promela.y"
                                                        { (yyval.pExprVal) = new exprRun	((yyvsp[-4].sVal), (yyvsp[-2].pExprArgListVal), nbrLines); }
#line 2830 "y.tab.c"
    break;

  case 135:
#line 485 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprRun	((yyvsp[-7].sVal), (yyvsp[-2].pExprArgListVal), (yyvsp[-5].pExprVarRefVal), nbrLines); }
#line 2836 "y.tab.c"
    break;

  case 136:
#line 486 "promela.y"
                                                                        { (yyval.pExprVal) = new exprLen	((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2842 "y.tab.c"
    break;

  case 137:
#line 487 "promela.y"
                                                                        { std::cout << "The enabled keyword is not supported."; }
#line 2848 "y.tab.c"
    break;

  case 138:
#line 488 "promela.y"
                                                                        { std::cout << "Construct not supported."; /* Unclear */ }
#line 2854 "y.tab.c"
    break;

  case 139:
#line 489 "promela.y"
                                                                { std::cout << "Sorted send and random receive are not supported."; }
#line 2860 "y.tab.c"
    break;

  case 140:
#line 490 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprVar	((yyvsp[0].pExprVarRefVal), nbrLines); }
#line 2866 "y.tab.c"
    break;

  case 141:
#line 491 "promela.y"
                                                                                        { std::cout << "Embedded C code is not supported."; }
#line 2872 "y.tab.c"
    break;

  case 142:
#line 492 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprConst((yyvsp[0].iVal), nbrLines); }
#line 2878 "y.tab.c"
    break;

  case 143:
#line 493 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprTrue	(nbrLines); }
#line 2884 "y.tab.c"
    break;

  case 144:
#line 494 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprFalse(nbrLines); }
#line 2890 "y.tab.c"
    break;

  case 145:
#line 495 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprTimeout(nbrLines); }
#line 2896 "y.tab.c"
    break;

  case 146:
#line 496 "promela.y"
                                                                                { std::cout << "The 'np_' variable is not supported."; }
#line 2902 "y.tab.c"
    break;

  case 147:
#line 497 "promela.y"
                                                                        { std::cout << "The 'pc_value()' construct is not supported."; }
#line 2908 "y.tab.c"
    break;

  case 148:
#line 498 "promela.y"
                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 2914 "y.tab.c"
    break;

  case 149:
#line 499 "promela.y"
                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 2920 "y.tab.c"
    break;

  case 150:
#line 500 "promela.y"
                                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 2926 "y.tab.c"
    break;

  case 151:
#line 501 "promela.y"
                                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 2932 "y.tab.c"
    break;

  case 153:
#line 505 "promela.y"
                                                                                { std::cout << "The 'priority' construct is related to simulation and not supported."; }
#line 2938 "y.tab.c"
    break;

  case 154:
#line 508 "promela.y"
                                                                                { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 2944 "y.tab.c"
    break;

  case 155:
#line 509 "promela.y"
                                                                                        { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 2950 "y.tab.c"
    break;

  case 157:
#line 513 "promela.y"
                                                                { std::cout << "The 'provided' construct is currently not supported."; }
#line 2956 "y.tab.c"
    break;

  case 158:
#line 518 "promela.y"
                                                                                { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 2962 "y.tab.c"
    break;

  case 159:
#line 519 "promela.y"
                                                                                { (yyval.pExprVal) = new exprPar	((yyvsp[-1].pExprVal), nbrLines); }
#line 2968 "y.tab.c"
    break;

  case 160:
#line 520 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2974 "y.tab.c"
    break;

  case 161:
#line 521 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2980 "y.tab.c"
    break;

  case 162:
#line 522 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2986 "y.tab.c"
    break;

  case 163:
#line 523 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2992 "y.tab.c"
    break;

  case 164:
#line 524 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2998 "y.tab.c"
    break;

  case 165:
#line 525 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3004 "y.tab.c"
    break;

  case 166:
#line 526 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprSkip	(nbrLines); }
#line 3010 "y.tab.c"
    break;

  case 167:
#line 529 "promela.y"
                                                                { (yyval.pExprVal) = new exprFull	((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3016 "y.tab.c"
    break;

  case 168:
#line 530 "promela.y"
                                                                        { (yyval.pExprVal) = new exprNFull((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3022 "y.tab.c"
    break;

  case 169:
#line 531 "promela.y"
                                                                        { (yyval.pExprVal) = new exprEmpty((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3028 "y.tab.c"
    break;

  case 170:
#line 532 "promela.y"
                                                                        { (yyval.pExprVal) = new exprNEmpty((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3034 "y.tab.c"
    break;

  case 171:
#line 535 "promela.y"
                                                                                { (yyval.pDataVal).sVal = nullptr; (yyval.pDataVal).iType = (yyvsp[0].iType); }
#line 3040 "y.tab.c"
    break;

  case 172:
#line 536 "promela.y"
                                                                                        { (yyval.pDataVal).sVal = (yyvsp[0].sVal); (yyval.pDataVal).iType = symTabNode::T_UTYPE; }
#line 3046 "y.tab.c"
    break;

  case 173:
#line 540 "promela.y"
                                                                                {	std::cout << "REDUCE: basetype -> typ_list\n";
													if((yyvsp[0].pDataVal).iType != symTabNode::T_UTYPE && (yyvsp[0].pDataVal).iType) {
														(yyval.pVarSymVal) = varSymNode::createSymTabNode((yyvsp[0].pDataVal).iType, nbrLines);
													} else {
														tdefSymNode* pType = *globalSymTab ? static_cast<tdefSymNode*>((*globalSymTab)->lookupInSymTab((yyvsp[0].pDataVal).sVal)) : nullptr;
														(yyval.pVarSymVal) = new utypeSymNode(pType, nbrLines);
														if((yyval.pVarSymVal) == nullptr) 
															std::cout << "The type "<<(yyvsp[0].pDataVal).sVal<<" was not declared in a typedef.\n";
													}
												}
#line 3061 "y.tab.c"
    break;

  case 174:
#line 550 "promela.y"
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
#line 3078 "y.tab.c"
    break;

  case 176:
#line 566 "promela.y"
                                                                                        { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3084 "y.tab.c"
    break;

  case 177:
#line 570 "promela.y"
                                                                        { (yyval.pExprArgListVal) = nullptr; }
#line 3090 "y.tab.c"
    break;

  case 178:
#line 571 "promela.y"
                                                                                        { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3096 "y.tab.c"
    break;

  case 179:
#line 575 "promela.y"
                                                                                { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3102 "y.tab.c"
    break;

  case 180:
#line 576 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList(static_cast<exprRArg*>((yyvsp[-3].pExprVal)), static_cast<exprArgList*>((yyvsp[-1].pExprArgListVal)), nbrLines); }
#line 3108 "y.tab.c"
    break;

  case 181:
#line 579 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList(static_cast<exprRArg*>((yyvsp[0].pExprVal)), nbrLines); }
#line 3114 "y.tab.c"
    break;

  case 182:
#line 580 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList(static_cast<exprRArg*>((yyvsp[-2].pExprVal)), static_cast<exprArgList*>((yyvsp[0].pExprArgListVal)), nbrLines); }
#line 3120 "y.tab.c"
    break;

  case 183:
#line 583 "promela.y"
                                                                                { (yyval.pExprRArgVal) = new exprRArgVar((yyvsp[0].pExprVarRefVal), nbrLines); }
#line 3126 "y.tab.c"
    break;

  case 184:
#line 584 "promela.y"
                                                                                { (yyval.pExprRArgVal) = new exprRArgEval((yyvsp[-1].pExprVal), nbrLines); }
#line 3132 "y.tab.c"
    break;

  case 185:
#line 585 "promela.y"
                                                                                        { (yyval.pExprRArgVal) = new exprRArgConst((yyvsp[0].iVal), nbrLines); }
#line 3138 "y.tab.c"
    break;

  case 186:
#line 586 "promela.y"
                                                                        { (yyval.pExprRArgVal) = new exprRArgConst(-(yyvsp[0].iVal), nbrLines); }
#line 3144 "y.tab.c"
    break;

  case 187:
#line 590 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList((yyvsp[0].pExprRArgVal), nbrLines); }
#line 3150 "y.tab.c"
    break;

  case 188:
#line 591 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList((yyvsp[-2].pExprRArgVal), (yyvsp[0].pExprArgListVal), nbrLines); }
#line 3156 "y.tab.c"
    break;

  case 189:
#line 592 "promela.y"
                                                                        { (yyval.pExprArgListVal) = new exprArgList((yyvsp[-3].pExprRArgVal), (yyvsp[-1].pExprArgListVal), nbrLines); }
#line 3162 "y.tab.c"
    break;

  case 190:
#line 593 "promela.y"
                                                                                { (yyval.pExprArgListVal) = (yyvsp[-1].pExprArgListVal); }
#line 3168 "y.tab.c"
    break;

  case 191:
#line 596 "promela.y"
                                                                                { std::cout << "REDUCE: NAME -> nlst\n"; (yyval.pMTypeListVal) = mtypeList::addMType(nullptr, (yyvsp[0].sVal)); free((yyvsp[0].sVal)); }
#line 3174 "y.tab.c"
    break;

  case 192:
#line 597 "promela.y"
                                                                                        { std::cout << "REDUCE: nlst NAME -> NAME\n"; (yyval.pMTypeListVal) = mtypeList::addMType((yyval.pMTypeListVal), (yyvsp[0].sVal)); free((yyvsp[0].sVal)); }
#line 3180 "y.tab.c"
    break;

  case 193:
#line 598 "promela.y"
                                                                { std::cout << "REDUCE: nlst , -> nlst\n"; }
#line 3186 "y.tab.c"
    break;


#line 3190 "y.tab.c"

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
#line 600 "promela.y"

