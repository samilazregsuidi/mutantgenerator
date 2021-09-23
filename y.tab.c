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

#ifdef CPP
extern "C" 
#endif
int yylex(YYSTYPE * yylval_param, symTabNode** globalSymTab);

extern int nbrLines;

int yyerror (symTabNode** globalSymTab, mTypeList** mtypes, char* msg){
	fprintf(stderr, "Syntax error on line %d: '%s'.\n", nbrLines, msg);
	exit(1);
}

/*int printf(char *msg, char *param) {
	char buffer [strlen(msg) + strlen(param) + 1];
	sprintf(buffer, msg, param);
	fprintf(stderr, "Syntax error on line %d: '%s'.\n", nbrLines, buffer);
	exit(1);
}*/

// extern - lex


#line 115 "y.tab.c"

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
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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
#line 51 "promela.y"
 
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
	class varSymNode*		pVarSymVal;
	class tdefSymNode*		pTdefSymVal;
	
	enum symTabNode::Type   iType;

#line 375 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (symTabNode** globalSymTab, mTypeList** mtypes);

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
#define YYLAST   1410

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  114
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  195
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  395

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
     105,   106,    92,    90,   112,    91,   104,    93,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   111,     2,
       2,     2,     2,     2,   113,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   107,     2,   108,    80,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   109,    79,   110,    97,     2,     2,     2,
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
       0,   131,   131,   160,   163,   164,   167,   168,   169,   170,
     171,   172,   173,   174,   178,   191,   192,   195,   196,   197,
     198,   209,   219,   222,   225,   226,   229,   232,   233,   236,
     237,   238,   239,   242,   243,   246,   249,   252,   264,   269,
     270,   271,   272,   273,   274,   282,   283,   284,   285,   288,
     289,   295,   332,   346,   353,   354,   358,   359,   362,   363,
     366,   367,   370,   371,   379,   382,   385,   386,   387,   390,
     393,   394,   397,   398,   401,   402,   405,   406,   409,   410,
     411,   412,   413,   414,   415,   419,   420,   421,   422,   423,
     424,   425,   426,   427,   428,   429,   430,   431,   432,   433,
     434,   435,   436,   439,   440,   443,   456,   457,   460,   461,
     464,   465,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   487,   488,   489,   496,   497,   498,   499,   501,   502,
     503,   504,   505,   506,   507,   508,   509,   510,   511,   512,
     513,   514,   515,   516,   519,   520,   523,   524,   527,   528,
     533,   534,   535,   536,   537,   538,   539,   540,   541,   544,
     545,   546,   547,   550,   551,   555,   564,   578,   579,   583,
     584,   588,   589,   592,   593,   596,   597,   598,   599,   603,
     604,   605,   606,   609,   610,   611
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
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
  "IMPLIES", "'.'", "'('", "')'", "'['", "']'", "'{'", "'}'", "':'", "','",
  "'@'", "$accept", "start_parsing", "program", "units", "unit", "proc",
  "proctype", "inst", "init", "events", "utype", "nm", "ns", "c_fcts",
  "cstate", "ccode", "cexpr", "body", "sequence", "step", "vis", "asgn",
  "one_decl", "decl_lst", "decl", "vref_lst", "var_list", "ivar",
  "ch_init", "vardcl", "varref", "pfld", "cmpnd", "sfld", "stmnt",
  "Special", "Stmnt", "options", "option", "OS", "MS", "aname", "expr",
  "Opt_priority", "full_expr", "Opt_enabler", "Expr", "Probe", "basetype",
  "typ_list", "args", "prargs", "margs", "arg", "rarg", "rargs", "nlst", YY_NULLPTR
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
     346,   347,   348,   349,    46,    40,    41,    91,    93,   123,
     125,    58,    44,    64
};
# endif

#define YYPACT_NINF (-322)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-108)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     677,  -322,  -322,    26,    34,    57,    83,  -322,     6,  -322,
    -322,  -322,   -27,    72,   148,  -322,   246,  -322,  -322,    43,
    -322,  -322,  -322,  -322,  -322,  -322,  -322,    51,  -322,   138,
     144,    56,  -322,  -322,    74,    20,   440,  -322,   167,   -27,
    -322,  -322,  -322,  -322,   182,     5,   189,   187,   191,   132,
     888,    92,   102,  -322,   177,   177,   -75,   -40,   113,  -322,
    -322,  -322,   862,   122,   123,  -322,    65,   124,   125,   126,
     218,  -322,  -322,   127,   129,  -322,  -322,   128,   130,   134,
     135,    -1,   888,   888,   888,   139,   141,   862,   440,  -322,
    -322,   197,  -322,  -322,   -20,   145,  -322,   204,  -322,  -322,
    1298,  -322,    24,  -322,  -322,  -322,   146,    39,  -322,   147,
    -322,   143,   178,  -322,  -322,  -322,   216,   149,   150,   888,
     117,  1013,   152,  -322,  -322,  -322,   440,   223,   177,   224,
     888,   543,   888,   255,   257,   888,  -322,   256,    21,  -322,
    -322,    61,    -1,   888,   888,  -322,   440,   440,    -1,    -1,
      -1,    -1,  -322,   158,  -322,  -322,  -322,   888,   255,   917,
     -38,   197,   -25,   161,   337,   862,   888,   888,    62,    96,
    -322,  -322,    -1,  -322,   646,   862,   862,   888,   888,   888,
     888,   888,   888,   888,   888,   888,   888,   888,   888,   888,
     888,   888,   888,   862,   862,    10,   269,   270,   267,   189,
     773,   132,  -322,   947,   169,   171,   888,   888,   888,  -322,
     197,  -322,  -322,  -322,  1084,    53,  -322,  -322,  -322,  1116,
    -322,  -322,   173,   179,   176,   186,   888,    -1,   188,  1148,
    1178,   197,   197,   193,   195,   198,   199,    -1,  1208,   145,
     888,  -322,  -322,   185,  -322,  -322,  -322,  -322,   977,  -322,
    -322,  -322,  -322,   206,    19,   299,    19,    19,  -322,   -63,
    -322,    19,    19,  -322,  -322,  -322,   333,   225,   538,  -322,
     741,   855,   418,   313,   313,   196,   196,   196,   196,   115,
     115,   120,   120,  -322,  -322,  -322,   333,   225,   538,  -322,
    -322,   203,   205,  -322,  -322,     9,  -322,   309,  -322,  1316,
    -322,   436,   538,  -322,  -322,  -322,   646,    77,   747,   888,
     208,  -322,  -322,   209,   210,  -322,  -322,  -322,   207,   213,
    -322,  -322,  -322,  -322,  -322,  -322,  -322,  1049,  -322,   888,
     888,   232,  -322,   214,   211,    19,    19,   240,   217,    72,
    -322,  -322,  -322,  -322,   220,   255,   319,    99,  -322,  -322,
    -322,    72,   226,  -322,  -322,   888,   227,  1238,  -322,  -322,
    -322,   230,  -322,  -322,  -322,   278,   304,  -322,  -322,   -64,
    -322,   888,  1268,  -322,  -322,  -322,   234,   -27,   236,   237,
    -322,   862,  -322,   170,    72,   242,  -322,  -322,   247,   239,
    -322,  -322,   170,  -322,  -322
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      17,    33,    34,     0,     0,     0,     0,    13,    18,    46,
      47,    48,     0,   154,     0,     2,    17,     4,     6,     0,
       7,     8,    10,    12,    11,    28,    27,     0,     9,     0,
       0,     0,    24,    25,     0,     0,    45,    22,     0,     0,
       1,     5,    15,    16,     0,    49,     0,    29,    30,    45,
     177,     0,     0,   144,     0,     0,    70,     0,     0,   145,
     146,   168,     0,     0,     0,    35,     0,     0,     0,     0,
       0,    82,    98,     0,     0,   147,   148,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    45,    92,
     143,   106,    37,    39,   142,    74,    69,    43,    76,    77,
     156,    97,   157,   160,   155,    21,     0,    66,    50,     0,
      51,    60,    62,    52,    31,    32,    54,     0,    70,     0,
     142,   183,     0,   178,    19,    20,    45,     0,   103,     0,
       0,    45,     0,     0,     0,   177,    91,     0,     0,   110,
     111,     0,     0,     0,     0,    83,    45,    45,     0,     0,
       0,     0,    40,    58,   134,   133,   132,     0,     0,     0,
       0,   106,   108,     0,    45,     0,     0,     0,     0,     0,
      86,    87,     0,    72,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    45,     0,     0,     0,     0,
       0,    45,    23,     0,     0,     0,     0,     0,     0,    26,
     106,    80,   104,    81,     0,    70,    42,    41,    84,     0,
     153,   152,     0,   179,     0,     0,   177,     0,     0,     0,
       0,   106,   106,     0,     0,     0,     0,     0,     0,    74,
       0,   112,   161,     0,    36,   109,    38,    85,   183,    79,
     181,    96,   187,     0,     0,     0,     0,     0,   185,   189,
      78,     0,     0,    93,    75,    44,   128,   167,   127,   166,
     120,   119,   118,   125,   126,   121,   122,   123,   124,   129,
     130,   113,   114,   115,   116,   117,   165,   164,   163,   162,
      57,     0,     0,    67,   193,     0,    61,     0,    64,    63,
      55,   128,   127,   184,   105,    71,     0,     0,     0,     0,
       0,    90,    89,     0,     0,   138,   139,   149,     0,     0,
     169,   171,   170,   172,    59,   131,    73,     0,   101,     0,
       0,     0,   188,     0,     0,     0,     0,     0,     0,   154,
      68,   194,    53,   195,     0,     0,     0,   142,   102,   180,
      88,   154,     0,    99,   100,     0,     0,     0,    94,   192,
     140,     0,   190,    95,   141,   158,     0,   151,   150,     0,
     136,   177,     0,   182,   186,   191,     0,     0,     0,     0,
     135,     0,    14,     0,   154,     0,   173,   174,   175,     0,
     137,   159,     0,    65,   176
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -322,  -322,  -322,  -322,   344,  -322,  -322,  -322,  -322,  -322,
    -322,  -322,  -322,  -322,  -322,    25,  -322,   -39,   -68,   200,
    -322,  -322,    31,  -151,  -322,   131,   -43,  -322,  -322,  -322,
      73,  -129,   194,   136,  -126,  -322,    59,   -44,  -322,  -144,
    -322,  -322,   -49,  -321,   -60,  -322,   -79,  -322,  -322,   -23,
    -128,  -322,   219,  -157,  -322,  -150,  -322
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    14,    15,    16,    17,    18,    44,    19,    20,    21,
      22,    34,    23,    24,    25,    89,    90,    37,    91,    92,
      27,   109,    93,   117,   291,   152,   110,   111,   298,   112,
     120,    95,    96,   173,    97,    98,    99,   127,   128,   163,
     164,   141,   100,    39,   101,   377,   102,   103,   388,   389,
     122,   310,   249,   123,   259,   260,   295
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     105,   121,   136,   113,   220,   218,   118,   222,   160,   250,
     250,   129,   107,  -107,  -107,  -107,   341,   243,   365,   263,
     161,   254,   252,    51,   224,    26,   118,    52,   118,   239,
     370,    28,   130,   154,   155,   156,   131,    29,   159,   193,
     194,    26,   335,   257,   290,    30,   253,    28,   265,   336,
     300,   303,   165,   166,   167,   168,   169,    45,   210,    46,
       9,    10,    11,   390,    31,   252,   304,   132,   242,   118,
     203,   133,   139,   134,   140,   170,   171,   108,   231,   232,
     116,   214,    36,   219,   212,  -107,   121,   318,   319,   253,
      32,    42,    43,    33,   229,   230,   267,   269,   313,   252,
      86,   193,   194,   118,   331,   247,   333,   334,   238,    94,
     255,   337,   338,    35,   287,   289,   -56,   248,   248,   342,
      86,   343,    86,   253,   256,    38,   266,   268,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   288,   196,   254,    40,    47,
     197,   299,   349,   255,   153,    48,   296,   301,   302,   121,
     130,    94,   217,    86,   306,    49,   226,   256,   227,   257,
     104,   165,   356,   167,   369,   169,   386,   121,   387,    50,
     218,   261,     9,    10,    11,   361,   362,   255,   345,   106,
     346,   327,   204,   205,   170,   171,   107,    86,   114,    94,
     124,   256,   115,   262,    94,   188,   189,   190,   191,   192,
     125,   225,   190,   191,   192,   228,   367,   126,   135,    94,
      94,   233,   234,   235,   236,   145,   116,   137,   138,   142,
     143,   144,   116,   148,   162,   149,   146,    94,   147,   150,
     151,   258,   258,   379,   157,   158,    -3,    94,   174,   172,
     200,   195,   -45,   201,   -45,   199,   198,   130,   209,   202,
     121,   211,   118,   213,   221,     1,     2,   223,     3,     4,
     237,   244,   292,   293,   294,     5,   257,     6,   262,   308,
     121,   357,   311,     7,   186,   187,   188,   189,   190,   191,
     192,   309,   312,     8,   315,   328,     9,    10,    11,   320,
     314,   321,   332,   194,   322,   323,   372,    12,    13,   339,
     153,   330,   344,   340,   350,   351,   358,   353,   352,   360,
     359,   385,   121,   354,   363,   364,   368,   258,   366,   258,
     258,   371,   376,   373,   258,   258,   375,   378,   382,   381,
      53,    54,    55,   384,    56,   383,    57,    58,   391,   393,
      59,    60,    61,    62,    63,    64,     1,     2,    65,   392,
      41,    66,    67,    68,   246,    69,   264,   348,   324,   394,
       0,    70,    71,    72,   245,   326,     0,     0,    73,    94,
      74,   347,    75,    76,     0,     0,   251,     9,    10,    11,
       0,     0,    77,    78,    79,    80,    81,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   258,   258,
      82,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,    83,     0,
       0,     0,     0,     0,    84,     0,     0,    85,    86,     0,
       0,     0,    87,    53,    54,    55,    88,    56,     0,    57,
      58,     0,     0,    59,    60,    61,    62,    63,    64,     1,
       2,    65,     0,     0,    66,    67,    68,     0,    69,     0,
       0,     0,     0,     0,    70,    71,    72,     0,     0,     0,
       0,    73,     0,    74,     0,    75,    76,     0,     0,     0,
       9,    10,    11,     0,     0,    77,    78,    79,    80,    81,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,    82,   207,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,    83,     0,     0,     0,     0,     0,    84,     0,     0,
      85,    86,     0,     0,     0,    87,    53,    54,    55,    88,
     215,     0,    57,    58,     0,     0,    59,    60,    61,    62,
      63,    64,     1,     2,    65,     0,     0,    66,    67,    68,
       0,    69,     0,     0,     0,     0,     0,    70,    71,    72,
       0,     0,     0,     0,    73,     0,    74,     0,    75,    76,
       0,     0,     0,     9,    10,    11,     0,     0,    77,    78,
      79,    80,   216,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    82,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,     0,    83,     0,     0,     0,     0,     0,
      84,     0,     0,    85,    86,     0,     0,     0,    87,    53,
      54,    55,    88,   215,     0,    57,    58,     0,     0,    59,
      60,    61,    62,    63,    64,     1,     2,    65,     0,     0,
      66,    67,    68,     0,    69,     0,     0,     0,     0,     0,
      70,    71,    72,   -45,     0,   -45,     0,    73,     0,    74,
       0,    75,    76,     0,     0,     0,     1,     2,     0,     3,
       4,    77,    78,    79,    80,     0,     5,     0,     6,     0,
       0,     0,     0,     0,     7,     0,     0,     0,     0,    82,
       0,     0,     0,     0,     8,     0,     0,     9,    10,    11,
       0,     0,     0,     0,     0,     0,     0,    83,    12,    13,
       0,     0,     0,    84,     0,     0,    85,    86,     0,     0,
      53,    87,     0,     0,   118,    88,    57,    58,     0,     0,
      59,    60,    61,    62,    63,    64,     1,     2,    65,     0,
       0,    66,    67,    68,     0,    69,    53,     0,     0,     0,
     118,     0,    57,    72,     0,     0,    59,    60,    73,     0,
      74,     0,    75,    76,    65,     0,     0,    66,    67,    68,
       0,    69,    77,    78,    79,    80,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    75,    76,
      82,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,     0,     0,    83,     0,
       0,     0,     0,     0,    84,     0,    82,    85,    86,     0,
       0,     0,    87,     0,     0,     0,    88,     0,     0,     0,
       0,     0,     0,     0,    83,    53,     0,     0,     0,   118,
      84,    57,     0,    85,    86,    59,    60,    61,   119,     0,
     297,     0,     0,    65,     0,     0,    66,    67,    68,     0,
      69,    53,     0,     0,     0,   118,     0,    57,     0,     0,
       0,    59,    60,     0,     0,     0,     0,    75,    76,    65,
       0,     0,    66,    67,    68,     0,    69,    77,    78,    79,
      80,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    75,    76,    82,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
       0,     0,     0,    83,   240,     0,     0,     0,     0,    84,
       0,    82,    85,    86,     0,     0,     0,    87,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    83,
       0,     0,     0,     0,   240,    84,     0,     0,    85,    86,
       0,     0,     0,   119,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   241,   206,   207,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   241,   206,   207,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   329,     0,     0,     0,     0,     0,     0,   208,
     206,   207,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   208,   206,   207,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     355,   206,   207,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   305,   206,   207,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   307,   206,   207,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   316,   206,   207,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   317,   206,   207,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   325,   206,   207,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   374,   206,   207,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   380,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   206,   207,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192
};

static const yytype_int16 yycheck[] =
{
      39,    50,    62,    46,   133,   131,     7,   135,    87,   166,
     167,    55,     7,    38,    39,    40,     7,   161,   339,   169,
      88,    85,     3,     3,     3,     0,     7,     7,     7,   158,
     351,     0,   107,    82,    83,    84,   111,    11,    87,    77,
      78,    16,   105,   107,   195,    11,    27,    16,   174,   112,
     201,   208,    72,    73,    74,    75,    76,     6,   126,     8,
      50,    51,    52,   384,     7,     3,   210,   107,   106,     7,
     119,   111,     7,   113,     9,    95,    96,    72,   146,   147,
      49,   130,   109,   132,   128,   110,   135,   231,   232,    27,
       7,    48,    49,    10,   143,   144,   175,   176,   226,     3,
     101,    77,    78,     7,   254,   165,   256,   257,   157,    36,
      91,   261,   262,   107,   193,   194,   106,   166,   167,   110,
     101,   112,   101,    27,   105,    53,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   107,    85,     0,    11,
     111,   200,   309,    91,    81,    11,   199,   206,   207,   208,
     107,    88,   131,   101,   111,   109,   105,   105,   107,   107,
       3,    72,   329,    74,    75,    76,     6,   226,     8,   105,
     306,    85,    50,    51,    52,   335,   336,    91,   111,     7,
     113,   240,    75,    76,    95,    96,     7,   101,    11,   126,
     108,   105,    11,   107,   131,    90,    91,    92,    93,    94,
     108,   138,    92,    93,    94,   142,   345,    40,   105,   146,
     147,   148,   149,   150,   151,     7,   195,   105,   105,   105,
     105,   105,   201,   105,    37,   105,   109,   164,   109,   105,
     105,   168,   169,   371,   105,   104,     0,   174,    44,   104,
      72,   105,     6,    37,     8,   112,   109,   107,   106,   110,
     309,    38,     7,    39,     7,    19,    20,    11,    22,    23,
     112,   110,     3,     3,     7,    29,   107,    31,   107,   106,
     329,   330,   106,    37,    88,    89,    90,    91,    92,    93,
      94,   112,   106,    47,   106,   110,    50,    51,    52,   106,
     227,   106,     3,    78,   106,   106,   355,    61,    62,   106,
     237,   105,     3,   108,   106,   106,    84,   110,   108,   108,
     106,   381,   371,   110,    84,   108,     7,   254,   108,   256,
     257,   105,    54,   106,   261,   262,   106,    33,   377,   105,
       3,     4,     5,   106,     7,   109,     9,    10,   106,   110,
      13,    14,    15,    16,    17,    18,    19,    20,    21,   112,
      16,    24,    25,    26,   164,    28,   172,   308,   237,   392,
      -1,    34,    35,    36,    37,   239,    -1,    -1,    41,   306,
      43,   308,    45,    46,    -1,    -1,   167,    50,    51,    52,
      -1,    -1,    55,    56,    57,    58,    59,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,   335,   336,
      73,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    91,    -1,
      -1,    -1,    -1,    -1,    97,    -1,    -1,   100,   101,    -1,
      -1,    -1,   105,     3,     4,     5,   109,     7,    -1,     9,
      10,    -1,    -1,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    24,    25,    26,    -1,    28,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,
      -1,    41,    -1,    43,    -1,    45,    46,    -1,    -1,    -1,
      50,    51,    52,    -1,    -1,    55,    56,    57,    58,    59,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    73,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    91,    -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,
     100,   101,    -1,    -1,    -1,   105,     3,     4,     5,   109,
       7,    -1,     9,    10,    -1,    -1,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    24,    25,    26,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      -1,    -1,    -1,    -1,    41,    -1,    43,    -1,    45,    46,
      -1,    -1,    -1,    50,    51,    52,    -1,    -1,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    -1,    91,    -1,    -1,    -1,    -1,    -1,
      97,    -1,    -1,   100,   101,    -1,    -1,    -1,   105,     3,
       4,     5,   109,     7,    -1,     9,    10,    -1,    -1,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
      24,    25,    26,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,     6,    -1,     8,    -1,    41,    -1,    43,
      -1,    45,    46,    -1,    -1,    -1,    19,    20,    -1,    22,
      23,    55,    56,    57,    58,    -1,    29,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,    73,
      -1,    -1,    -1,    -1,    47,    -1,    -1,    50,    51,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    61,    62,
      -1,    -1,    -1,    97,    -1,    -1,   100,   101,    -1,    -1,
       3,   105,    -1,    -1,     7,   109,     9,    10,    -1,    -1,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    24,    25,    26,    -1,    28,     3,    -1,    -1,    -1,
       7,    -1,     9,    36,    -1,    -1,    13,    14,    41,    -1,
      43,    -1,    45,    46,    21,    -1,    -1,    24,    25,    26,
      -1,    28,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,
      73,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    -1,    -1,    91,    -1,
      -1,    -1,    -1,    -1,    97,    -1,    73,   100,   101,    -1,
      -1,    -1,   105,    -1,    -1,    -1,   109,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    91,     3,    -1,    -1,    -1,     7,
      97,     9,    -1,   100,   101,    13,    14,    15,   105,    -1,
     107,    -1,    -1,    21,    -1,    -1,    24,    25,    26,    -1,
      28,     3,    -1,    -1,    -1,     7,    -1,     9,    -1,    -1,
      -1,    13,    14,    -1,    -1,    -1,    -1,    45,    46,    21,
      -1,    -1,    24,    25,    26,    -1,    28,    55,    56,    57,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    46,    73,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      -1,    -1,    -1,    91,    37,    -1,    -1,    -1,    -1,    97,
      -1,    73,   100,   101,    -1,    -1,    -1,   105,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    -1,    -1,    -1,    37,    97,    -1,    -1,   100,   101,
      -1,    -1,    -1,   105,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,   112,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   112,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     111,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   108,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   108,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   106,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   106,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   106,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   106,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   106,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    20,    22,    23,    29,    31,    37,    47,    50,
      51,    52,    61,    62,   115,   116,   117,   118,   119,   121,
     122,   123,   124,   126,   127,   128,   129,   134,   136,    11,
      11,     7,     7,    10,   125,   107,   109,   131,    53,   157,
       0,   118,    48,    49,   120,     6,     8,    11,    11,   109,
     105,     3,     7,     3,     4,     5,     7,     9,    10,    13,
      14,    15,    16,    17,    18,    21,    24,    25,    26,    28,
      34,    35,    36,    41,    43,    45,    46,    55,    56,    57,
      58,    59,    73,    91,    97,   100,   101,   105,   109,   129,
     130,   132,   133,   136,   144,   145,   146,   148,   149,   150,
     156,   158,   160,   161,     3,   131,     7,     7,    72,   135,
     140,   141,   143,   140,    11,    11,   136,   137,     7,   105,
     144,   156,   164,   167,   108,   108,    40,   151,   152,   151,
     107,   111,   107,   111,   113,   105,   158,   105,   105,     7,
       9,   155,   105,   105,   105,     7,   109,   109,   105,   105,
     105,   105,   139,   144,   156,   156,   156,   105,   104,   156,
     160,   132,    37,   153,   154,    72,    73,    74,    75,    76,
      95,    96,   104,   147,    44,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    77,    78,   105,   107,   111,   109,   112,
      72,    37,   110,   156,    75,    76,    77,    78,   112,   106,
     132,    38,   151,    39,   156,     7,    59,   136,   148,   156,
     145,     7,   164,    11,     3,   144,   105,   107,   144,   156,
     156,   132,   132,   144,   144,   144,   144,   112,   156,   145,
      37,   106,   106,   153,   110,    37,   133,   158,   156,   166,
     167,   166,     3,    27,    85,    91,   105,   107,   144,   168,
     169,    85,   107,   169,   146,   148,   156,   160,   156,   160,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   160,   156,   160,
     137,   138,     3,     3,     7,   170,   140,   107,   142,   156,
     137,   156,   156,   167,   153,   108,   111,   108,   106,   112,
     165,   106,   106,   164,   144,   106,   106,   106,   153,   153,
     106,   106,   106,   106,   139,   106,   147,   156,   110,   105,
     105,   169,     3,   169,   169,   105,   112,   169,   169,   106,
     108,     7,   110,   112,     3,   111,   113,   144,   150,   167,
     106,   106,   108,   110,   110,   111,   167,   156,    84,   106,
     108,   169,   169,    84,   108,   157,   108,   145,     7,    75,
     157,   105,   156,   106,   106,   106,    54,   159,    33,   164,
     106,   105,   131,   109,   106,   158,     6,     8,   162,   163,
     157,   106,   112,   110,   163
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   114,   115,   116,   117,   117,   118,   118,   118,   118,
     118,   118,   118,   118,   119,   120,   120,   121,   121,   121,
     121,   122,   123,   124,   125,   125,   126,   127,   127,   128,
     128,   128,   128,   129,   129,   130,   131,   132,   132,   133,
     133,   133,   133,   133,   133,   134,   134,   134,   134,   135,
     135,   136,   136,   136,   137,   137,   138,   138,   139,   139,
     140,   140,   141,   141,   141,   142,   143,   143,   143,   144,
     145,   145,   146,   146,   147,   147,   148,   148,   149,   149,
     149,   149,   149,   149,   149,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   151,   151,   152,   153,   153,   154,   154,
     155,   155,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   157,   157,   158,   158,   159,   159,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   161,
     161,   161,   161,   162,   162,   163,   163,   164,   164,   165,
     165,   166,   166,   167,   167,   168,   168,   168,   168,   169,
     169,   169,   169,   170,   170,   170
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     9,     1,     1,     0,     1,     4,
       4,     3,     2,     5,     1,     1,     5,     1,     1,     3,
       3,     4,     4,     1,     1,     1,     4,     1,     3,     1,
       2,     3,     3,     1,     3,     0,     1,     1,     1,     0,
       1,     3,     3,     6,     1,     3,     0,     1,     1,     3,
       1,     3,     1,     3,     3,     7,     1,     3,     4,     1,
       1,     4,     2,     4,     0,     2,     1,     1,     3,     3,
       3,     3,     1,     2,     3,     3,     2,     2,     5,     4,
       4,     2,     1,     3,     5,     5,     3,     1,     1,     5,
       5,     4,     5,     1,     2,     3,     0,     1,     1,     2,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     2,     2,     2,     7,     6,     9,     4,     4,
       5,     5,     1,     1,     1,     1,     1,     1,     1,     4,
       6,     6,     3,     3,     0,     2,     1,     1,     0,     4,
       1,     3,     3,     3,     3,     3,     3,     3,     1,     4,
       4,     4,     4,     1,     1,     1,     3,     0,     1,     0,
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
        yyerror (globalSymTab, mtypes, YY_("syntax error: cannot back up")); \
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
                  Type, Value, globalSymTab, mtypes); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, symTabNode** globalSymTab, mTypeList** mtypes)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (globalSymTab);
  YYUSE (mtypes);
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
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, symTabNode** globalSymTab, mTypeList** mtypes)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, globalSymTab, mtypes);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, symTabNode** globalSymTab, mTypeList** mtypes)
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
                                              , globalSymTab, mtypes);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, globalSymTab, mtypes); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, symTabNode** globalSymTab, mTypeList** mtypes)
{
  YYUSE (yyvaluep);
  YYUSE (globalSymTab);
  YYUSE (mtypes);
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
yyparse (symTabNode** globalSymTab, mTypeList** mtypes)
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
  case 8:
#line 169 "promela.y"
                                                                { std::cout << "The 'events' construct is currently not supported."; }
#line 2050 "y.tab.c"
    break;

  case 9:
#line 170 "promela.y"
                                                                { *globalSymTab = symTabNode::merge(*globalSymTab, (yyvsp[0].pVarSymVal)); }
#line 2056 "y.tab.c"
    break;

  case 10:
#line 171 "promela.y"
                                                                { *globalSymTab = symTabNode::merge(*globalSymTab, (yyvsp[0].pTdefSymVal)); }
#line 2062 "y.tab.c"
    break;

  case 11:
#line 172 "promela.y"
                                                                { std::cout << "Embedded C code is not supported."; }
#line 2068 "y.tab.c"
    break;

  case 12:
#line 173 "promela.y"
                                                                { std::cout << "The 'named sequence' construct is currently not supported."; }
#line 2074 "y.tab.c"
    break;

  case 14:
#line 183 "promela.y"
                                                                                        {	
		  											symTabNode* args = symTabNode::deepcopy((yyvsp[-4].pVarSymVal));
		  											(yyvsp[0].pStmntVal)->setLocalSymTab(varSymNode::merge((yyvsp[-4].pVarSymVal), (yyvsp[0].pStmntVal)->getLocalSymTab()));
		  											symTabNode* proc = new procSymNode((yyvsp[-6].sVal), (yyvsp[-8].pConstExprVal), args, (yyvsp[0].pStmntVal), nbrLines);
		  											*globalSymTab = symTabNode::merge(*globalSymTab, proc);
		  										}
#line 2085 "y.tab.c"
    break;

  case 16:
#line 192 "promela.y"
                                                                                { std::cout << "Deterministic proctypes are not supported (only useful for simulation)."; }
#line 2091 "y.tab.c"
    break;

  case 17:
#line 195 "promela.y"
                                                                        { (yyval.pConstExprVal) = new exprConst(0, nbrLines); }
#line 2097 "y.tab.c"
    break;

  case 18:
#line 196 "promela.y"
                                                                                        { (yyval.pConstExprVal) = new exprConst(1, nbrLines); }
#line 2103 "y.tab.c"
    break;

  case 19:
#line 197 "promela.y"
                                                                        { (yyval.pConstExprVal) = new exprConst((yyvsp[-1].iVal), nbrLines); }
#line 2109 "y.tab.c"
    break;

  case 20:
#line 198 "promela.y"
                                                                        {	varSymNode* var = *globalSymTab? static_cast<varSymNode*>((*globalSymTab)->lookupInSymTab((yyvsp[-1].sVal))) : nullptr;
													if(var == nullptr) std::cout << "The variable "<<(yyvsp[-1].sVal)<<" does not exist.";
													else if(var->getType() != symTabNode::T_INT && var->getType() != symTabNode::T_BYTE && var->getType() != symTabNode::T_SHORT) std::cout << "The variable "<<(yyvsp[-1].sVal)<<" is not of type int, short or bit.";
													else if(var->getInitExpr() == nullptr || var->getInitExpr()->getType() != astNode::E_EXPR_CONST) std::cout << "The variable "<<(yyvsp[-1].sVal)<<" does not have a constant value.";
													else {
														(yyval.pConstExprVal) = new exprConst(var->getInitExpr()->getIVal(), nbrLines);
													}
													free((yyvsp[-1].sVal));											
												}
#line 2123 "y.tab.c"
    break;

  case 21:
#line 209 "promela.y"
                                                                {	if(*globalSymTab && (*globalSymTab)->lookupInSymTab("init") != nullptr) 
	std::cout << "This is the second init process; only one is allowed.";
													else {
														symTabNode* init = new initSymNode(nbrLines, (yyvsp[0].pStmntVal));
														*globalSymTab = symTabNode::merge(*globalSymTab, init);
													}

												}
#line 2136 "y.tab.c"
    break;

  case 22:
#line 219 "promela.y"
                                                                        { std::cout << "Event sequences (traces) are not supported."; }
#line 2142 "y.tab.c"
    break;

  case 23:
#line 222 "promela.y"
                                                        {	(yyval.pTdefSymVal) = new tdefSymNode((yyvsp[-3].sVal), (yyvsp[-1].pVarSymVal), nbrLines);  free((yyvsp[-3].sVal)); }
#line 2148 "y.tab.c"
    break;

  case 36:
#line 249 "promela.y"
                                                                { (yyval.pStmntVal) = (yyvsp[-2].pStmntVal); }
#line 2154 "y.tab.c"
    break;

  case 37:
#line 252 "promela.y"
                                                                                { 	(yyval.pStmntVal) = (yyvsp[0].pStmntVal);
													/*$$ = new fsm();
													if($1->getType() == astNode::E_DECL) {
														$$->setSymTab($1->getLocalSymTab());
														$1->setSymbol(nullptr);
														delete $1;
													} else if($1->getType() == astNode::E_STMNT) {
														$$->stmnt2fsm($1->getChild0(), *globalSymTab);
														$1->detachChild0();
														delete $1;
													}*/
												}
#line 2171 "y.tab.c"
    break;

  case 38:
#line 264 "promela.y"
                                                                                {	(yyval.pStmntVal) = stmnt::merge((yyval.pStmntVal), (yyvsp[0].pStmntVal));
													(yyvsp[0].pStmntVal)->setLocalSymTab(symTabNode::merge((yyval.pStmntVal)->getLocalSymTab(), (yyvsp[0].pStmntVal)->getLocalSymTab()));
												}
#line 2179 "y.tab.c"
    break;

  case 39:
#line 269 "promela.y"
                                                                                { (yyval.pStmntVal) = new decl((yyvsp[0].pVarSymVal), nbrLines); }
#line 2185 "y.tab.c"
    break;

  case 40:
#line 270 "promela.y"
                                                                                { std::cout << "Channel assertions are currently not supported."; }
#line 2191 "y.tab.c"
    break;

  case 41:
#line 271 "promela.y"
                                                                                { std::cout << "Declarations with labels are not suported."; }
#line 2197 "y.tab.c"
    break;

  case 42:
#line 272 "promela.y"
                                                                                { std::cout << "Channel assertions are currently not supported."; }
#line 2203 "y.tab.c"
    break;

  case 43:
#line 273 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntWrapper((yyvsp[0].pStmntVal), nbrLines); }
#line 2209 "y.tab.c"
    break;

  case 44:
#line 274 "promela.y"
                                                                        { std::cout << "Unless statements are currently not supported."; }
#line 2215 "y.tab.c"
    break;

  case 46:
#line 283 "promela.y"
                                                                                        { std::cout << "The 'hidden' keyword is not supported."; }
#line 2221 "y.tab.c"
    break;

  case 47:
#line 284 "promela.y"
                                                                                        { std::cout << "The 'show' keyword is not supported."; }
#line 2227 "y.tab.c"
    break;

  case 48:
#line 285 "promela.y"
                                                                                        { std::cout << "The 'local' keyword is not supported."; }
#line 2233 "y.tab.c"
    break;

  case 51:
#line 295 "promela.y"
                                                                        {	varSymNode* cur = (yyvsp[0].pVarSymVal);
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
													(yyval.pVarSymVal) = res;
												}
#line 2275 "y.tab.c"
    break;

  case 52:
#line 332 "promela.y"
                                                                        {	tdefSymNode* type = *globalSymTab? static_cast<tdefSymNode*>((*globalSymTab)->lookupInSymTab((yyvsp[-1].sVal))) : nullptr;
	 												if(type == nullptr)
	 													std::cout << "The type "<<(yyvsp[-1].sVal)<<" was not declared in a typedef.";
													else {
														utypeSymNode* cur = static_cast<utypeSymNode*>((yyvsp[0].pVarSymVal));
														while(cur != nullptr) {
															//cur->getType() = T_UTYPE;
															cur->setUType(type);
															cur = static_cast<utypeSymNode*>(cur->nextSym());
														}
														(yyval.pVarSymVal) = (yyvsp[0].pVarSymVal);
													}
	 												free((yyvsp[-1].sVal));
												}
#line 2294 "y.tab.c"
    break;

  case 53:
#line 346 "promela.y"
                                                                {	if((yyvsp[-4].iType) != symTabNode::T_MTYPE) 
														std::cout <<  "This syntax only works for MTYPEs.";
													(yyval.pVarSymVal) = nullptr;
													/* The mtype values are added in the nlst rule. */ 
												}
#line 2304 "y.tab.c"
    break;

  case 54:
#line 353 "promela.y"
                                                                                { (yyval.pVarSymVal) = (yyvsp[0].pVarSymVal); }
#line 2310 "y.tab.c"
    break;

  case 55:
#line 354 "promela.y"
                                                                        { (yyval.pVarSymVal) = varSymNode::merge((yyvsp[-2].pVarSymVal), (yyvsp[0].pVarSymVal)); }
#line 2316 "y.tab.c"
    break;

  case 56:
#line 358 "promela.y"
                                                                        { (yyval.pVarSymVal) = nullptr; }
#line 2322 "y.tab.c"
    break;

  case 57:
#line 359 "promela.y"
                                                                                        { (yyval.pVarSymVal) = (yyvsp[0].pVarSymVal); }
#line 2328 "y.tab.c"
    break;

  case 60:
#line 366 "promela.y"
                                                                                { (yyval.pVarSymVal) = (yyvsp[0].pVarSymVal); }
#line 2334 "y.tab.c"
    break;

  case 61:
#line 367 "promela.y"
                                                                                { (yyval.pVarSymVal) = varSymNode::merge((yyvsp[-2].pVarSymVal), (yyvsp[0].pVarSymVal)); }
#line 2340 "y.tab.c"
    break;

  case 62:
#line 370 "promela.y"
                                                                                { (yyval.pVarSymVal) = varSymNode::createSymTabNode((yyvsp[0].pDataVal).iType, nbrLines, (yyvsp[0].pDataVal).sVal, (yyvsp[0].pDataVal).iVal); }
#line 2346 "y.tab.c"
    break;

  case 63:
#line 371 "promela.y"
                                                                                { 	int mtype;
													if((yyvsp[0].pExprVal)->getType() == astNode::E_EXPR_VAR && (mtype = (*mtypes? (*mtypes)->getMTypeValue(static_cast<exprVar*>((yyvsp[0].pExprVal))->getVarRefName()->getName()) : -1)) != -1) {
														exprConst* newExpr = new exprConst(mtype, (yyvsp[0].pExprVal)->getLineNb());
														delete (yyvsp[0].pExprVal);
														(yyvsp[0].pExprVal) = newExpr;
													}
													(yyval.pVarSymVal) = varSymNode::createSymTabNode((yyvsp[-2].pDataVal).iType, nbrLines, (yyvsp[-2].pDataVal).sVal, (yyvsp[-2].pDataVal).iVal, (yyvsp[0].pExprVal));
												}
#line 2359 "y.tab.c"
    break;

  case 64:
#line 379 "promela.y"
                                                                        { (yyval.pVarSymVal) = new chanSymNode(nbrLines, (yyvsp[-2].pDataVal).sVal, (yyvsp[-2].pDataVal).iVal, (yyvsp[0].pDataVal).iVal, (yyvsp[0].pDataVal).symTabNodeVal); }
#line 2365 "y.tab.c"
    break;

  case 65:
#line 382 "promela.y"
                                                        { (yyval.pDataVal).iVal = (yyvsp[-5].iVal); (yyval.pDataVal).symTabNodeVal = (yyvsp[-1].pVarSymVal); }
#line 2371 "y.tab.c"
    break;

  case 66:
#line 385 "promela.y"
                                                                                { (yyval.pDataVal).sVal = (yyvsp[0].sVal); (yyval.pDataVal).iVal = 1; }
#line 2377 "y.tab.c"
    break;

  case 67:
#line 386 "promela.y"
                                                                                { std::cout << "The 'unsigned' data type is not supported."; }
#line 2383 "y.tab.c"
    break;

  case 68:
#line 387 "promela.y"
                                                                        { (yyval.pDataVal).sVal = (yyvsp[-3].sVal); (yyval.pDataVal).iVal = (yyvsp[-1].iVal); }
#line 2389 "y.tab.c"
    break;

  case 69:
#line 390 "promela.y"
                                                                                { (yyval.pExprVarRefVal) = (yyvsp[0].pExprVarRefVal); }
#line 2395 "y.tab.c"
    break;

  case 70:
#line 393 "promela.y"
                                                                                { (yyval.pExprVarRefNameVal) = new exprVarRefName((yyvsp[0].sVal), nbrLines); free((yyvsp[0].sVal)); }
#line 2401 "y.tab.c"
    break;

  case 71:
#line 394 "promela.y"
                                                                                { (yyval.pExprVarRefNameVal) = new exprVarRefName((yyvsp[-3].sVal), (yyvsp[-1].pExprVal), nbrLines); free((yyvsp[-3].sVal)); }
#line 2407 "y.tab.c"
    break;

  case 72:
#line 397 "promela.y"
                                                                                { (yyval.pExprVarRefVal) = new exprVarRef((yyvsp[-1].pExprVarRefNameVal), (yyvsp[0].pExprVarRefVal), nbrLines); }
#line 2413 "y.tab.c"
    break;

  case 73:
#line 398 "promela.y"
                                                                        { (yyval.pExprVarRefVal) = new exprVarRef((yyvsp[-1].pExprVarRefNameVal), (yyvsp[0].pExprVarRefVal), nbrLines); }
#line 2419 "y.tab.c"
    break;

  case 74:
#line 401 "promela.y"
                                                                        { (yyval.pExprVarRefVal) = nullptr; }
#line 2425 "y.tab.c"
    break;

  case 75:
#line 402 "promela.y"
                                                                        { (yyval.pExprVarRefVal) = (yyvsp[0].pExprVarRefVal);   }
#line 2431 "y.tab.c"
    break;

  case 76:
#line 405 "promela.y"
                                                                                { (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2437 "y.tab.c"
    break;

  case 77:
#line 406 "promela.y"
                                                                                        { (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2443 "y.tab.c"
    break;

  case 78:
#line 409 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntChanRecv((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprArgListVal), nbrLines); }
#line 2449 "y.tab.c"
    break;

  case 79:
#line 410 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntChanSnd((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprArgListVal), nbrLines); }
#line 2455 "y.tab.c"
    break;

  case 80:
#line 411 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntIf((yyvsp[-1].pStmntOptVal), (yyvsp[-2].iVal)); }
#line 2461 "y.tab.c"
    break;

  case 81:
#line 412 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntDo((yyvsp[-1].pStmntOptVal), (yyvsp[-2].iVal)); }
#line 2467 "y.tab.c"
    break;

  case 82:
#line 413 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntBreak(nbrLines); }
#line 2473 "y.tab.c"
    break;

  case 83:
#line 414 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntGoto((yyvsp[0].sVal), nbrLines); free((yyvsp[0].sVal)); }
#line 2479 "y.tab.c"
    break;

  case 84:
#line 415 "promela.y"
                                                                                { if((yyvsp[0].pStmntVal)->getType() == astNode::E_STMNT_LABEL && static_cast<stmntWrapper*>((yyvsp[0].pStmntVal))->getStmnt()->getType() == astNode::E_STMNT_LABEL) 
													std::cout << "Only two labels per state are supported."; 
												  (yyval.pStmntVal) = new stmntLabel((yyvsp[-2].sVal), (yyvsp[0].pStmntVal), nbrLines); free((yyvsp[-2].sVal)); }
#line 2487 "y.tab.c"
    break;

  case 85:
#line 419 "promela.y"
                                                                { (yyval.pStmntVal) = new stmntAsgn((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2493 "y.tab.c"
    break;

  case 86:
#line 420 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntIncr((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2499 "y.tab.c"
    break;

  case 87:
#line 421 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntDecr((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2505 "y.tab.c"
    break;

  case 88:
#line 422 "promela.y"
                                                                { (yyval.pStmntVal) = new stmntPrint((yyvsp[-2].sVal), (yyvsp[-1].pExprArgListVal), nbrLines); }
#line 2511 "y.tab.c"
    break;

  case 89:
#line 423 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntPrintm((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2517 "y.tab.c"
    break;

  case 90:
#line 424 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntPrintm((yyvsp[-1].iVal), nbrLines); }
#line 2523 "y.tab.c"
    break;

  case 91:
#line 425 "promela.y"
                                                                                { (yyval.pStmntVal) = new stmntAssert((yyvsp[0].pExprVal), nbrLines); }
#line 2529 "y.tab.c"
    break;

  case 92:
#line 426 "promela.y"
                                                                                        { std::cout << "Embedded C code is not supported."; }
#line 2535 "y.tab.c"
    break;

  case 93:
#line 427 "promela.y"
                                                                        { std::cout << "Sorted send and random receive are not supported."; }
#line 2541 "y.tab.c"
    break;

  case 94:
#line 428 "promela.y"
                                                                        { std::cout << "Channel poll operations are not supported."; }
#line 2547 "y.tab.c"
    break;

  case 95:
#line 429 "promela.y"
                                                                        { std::cout << "Channel poll operations are not supported."; }
#line 2553 "y.tab.c"
    break;

  case 96:
#line 430 "promela.y"
                                                                        { std::cout << "Sorted send and random receive are not supported."; }
#line 2559 "y.tab.c"
    break;

  case 97:
#line 431 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntExpr((yyvsp[0].pExprVal), nbrLines); }
#line 2565 "y.tab.c"
    break;

  case 98:
#line 432 "promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntElse(nbrLines); }
#line 2571 "y.tab.c"
    break;

  case 99:
#line 433 "promela.y"
                                                                { (yyval.pStmntVal) = new stmntAtomic((yyvsp[-2].pStmntVal), nbrLines); }
#line 2577 "y.tab.c"
    break;

  case 100:
#line 434 "promela.y"
                                                                { std::cout << "Deterministic steps are not yet supported."; }
#line 2583 "y.tab.c"
    break;

  case 101:
#line 435 "promela.y"
                                                                        { (yyval.pStmntVal) = new stmntSeq((yyvsp[-2].pStmntVal), nbrLines); }
#line 2589 "y.tab.c"
    break;

  case 102:
#line 436 "promela.y"
                                                                        { std::cout << "Inline calls are not yet supported."; }
#line 2595 "y.tab.c"
    break;

  case 103:
#line 439 "promela.y"
                                                                                { (yyval.pStmntOptVal) = new stmntOpt((yyvsp[0].pStmntVal), nbrLines); }
#line 2601 "y.tab.c"
    break;

  case 104:
#line 440 "promela.y"
                                                                                { (yyval.pStmntOptVal) = new stmntOpt((yyvsp[-1].pStmntVal), (yyvsp[0].pStmntOptVal), nbrLines); }
#line 2607 "y.tab.c"
    break;

  case 105:
#line 443 "promela.y"
                                                                        { (yyval.pStmntVal) = (yyvsp[-1].pStmntVal); }
#line 2613 "y.tab.c"
    break;

  case 107:
#line 457 "promela.y"
                                        { /* redundant semi at end of sequence */ }
#line 2619 "y.tab.c"
    break;

  case 108:
#line 460 "promela.y"
                                        { /* at least one semi-colon */ }
#line 2625 "y.tab.c"
    break;

  case 109:
#line 461 "promela.y"
                                        { /* but more are okay too   */ }
#line 2631 "y.tab.c"
    break;

  case 110:
#line 464 "promela.y"
                                                                                { (yyval.sVal) = (yyvsp[0].sVal); }
#line 2637 "y.tab.c"
    break;

  case 111:
#line 465 "promela.y"
                                                                                        { (yyval.sVal) = (yyvsp[0].sVal); }
#line 2643 "y.tab.c"
    break;

  case 112:
#line 468 "promela.y"
                                                                        { (yyval.pExprVal) = new exprPar		((yyvsp[-1].pExprVal), nbrLines); }
#line 2649 "y.tab.c"
    break;

  case 113:
#line 469 "promela.y"
                                                                                { (yyval.pExprVal) = new exprPlus		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2655 "y.tab.c"
    break;

  case 114:
#line 470 "promela.y"
                                                                                { (yyval.pExprVal) = new exprMinus	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2661 "y.tab.c"
    break;

  case 115:
#line 471 "promela.y"
                                                                                { (yyval.pExprVal) = new exprTimes	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2667 "y.tab.c"
    break;

  case 116:
#line 472 "promela.y"
                                                                                { (yyval.pExprVal) = new exprDiv		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2673 "y.tab.c"
    break;

  case 117:
#line 473 "promela.y"
                                                                                { (yyval.pExprVal) = new exprMod		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2679 "y.tab.c"
    break;

  case 118:
#line 474 "promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2685 "y.tab.c"
    break;

  case 119:
#line 475 "promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwXor	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2691 "y.tab.c"
    break;

  case 120:
#line 476 "promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2697 "y.tab.c"
    break;

  case 121:
#line 477 "promela.y"
                                                                                { (yyval.pExprVal) = new exprGT		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2703 "y.tab.c"
    break;

  case 122:
#line 478 "promela.y"
                                                                                { (yyval.pExprVal) = new exprLT		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2709 "y.tab.c"
    break;

  case 123:
#line 479 "promela.y"
                                                                                { (yyval.pExprVal) = new exprGE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2715 "y.tab.c"
    break;

  case 124:
#line 480 "promela.y"
                                                                                { (yyval.pExprVal) = new exprLE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2721 "y.tab.c"
    break;

  case 125:
#line 481 "promela.y"
                                                                                { (yyval.pExprVal) = new exprEQ		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2727 "y.tab.c"
    break;

  case 126:
#line 482 "promela.y"
                                                                                { (yyval.pExprVal) = new exprNE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2733 "y.tab.c"
    break;

  case 127:
#line 483 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2739 "y.tab.c"
    break;

  case 128:
#line 484 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2745 "y.tab.c"
    break;

  case 129:
#line 485 "promela.y"
                                                                                { (yyval.pExprVal) = new exprLShift	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2751 "y.tab.c"
    break;

  case 130:
#line 486 "promela.y"
                                                                                { (yyval.pExprVal) = new exprRShift	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2757 "y.tab.c"
    break;

  case 131:
#line 487 "promela.y"
                                                                        { (yyval.pExprVal) = new exprCount	((yyvsp[-1].pExprVal), nbrLines); }
#line 2763 "y.tab.c"
    break;

  case 132:
#line 488 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprBitwNeg	((yyvsp[0].pExprVal), nbrLines); }
#line 2769 "y.tab.c"
    break;

  case 133:
#line 489 "promela.y"
                                                                        { 	if((yyvsp[0].pExprVal)->getType() != astNode::E_EXPR_CONST) 
														(yyval.pExprVal) = new exprUMin((yyvsp[0].pExprVal), nbrLines);
													else {
														(yyvsp[0].pExprVal)->setIVal(-(yyvsp[0].pExprVal)->getIVal());
														(yyval.pExprVal) = (yyvsp[0].pExprVal);
													}
												}
#line 2781 "y.tab.c"
    break;

  case 134:
#line 496 "promela.y"
                                                                        { (yyval.pExprVal) = new exprNeg	((yyvsp[0].pExprVal), nbrLines); }
#line 2787 "y.tab.c"
    break;

  case 135:
#line 497 "promela.y"
                                                                { (yyval.pExprVal) = new exprCond	((yyvsp[-5].pExprVal), (yyvsp[-3].pExprVal), (yyvsp[-1].pExprVal), nbrLines); }
#line 2793 "y.tab.c"
    break;

  case 136:
#line 498 "promela.y"
                                                        { (yyval.pExprVal) = new exprRun	((yyvsp[-4].sVal), (yyvsp[-2].pExprArgListVal), nbrLines); }
#line 2799 "y.tab.c"
    break;

  case 137:
#line 500 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprRun	((yyvsp[-7].sVal), (yyvsp[-2].pExprArgListVal), (yyvsp[-5].pExprVarRefVal), nbrLines); }
#line 2805 "y.tab.c"
    break;

  case 138:
#line 501 "promela.y"
                                                                        { (yyval.pExprVal) = new exprLen	((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2811 "y.tab.c"
    break;

  case 139:
#line 502 "promela.y"
                                                                        { std::cout << "The enabled keyword is not supported."; }
#line 2817 "y.tab.c"
    break;

  case 140:
#line 503 "promela.y"
                                                                        { std::cout << "Construct not supported."; /* Unclear */ }
#line 2823 "y.tab.c"
    break;

  case 141:
#line 504 "promela.y"
                                                                { std::cout << "Sorted send and random receive are not supported."; }
#line 2829 "y.tab.c"
    break;

  case 142:
#line 505 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprVar	((yyvsp[0].pExprVarRefVal), nbrLines); }
#line 2835 "y.tab.c"
    break;

  case 143:
#line 506 "promela.y"
                                                                                        { std::cout << "Embedded C code is not supported."; }
#line 2841 "y.tab.c"
    break;

  case 144:
#line 507 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprConst((yyvsp[0].iVal), nbrLines); }
#line 2847 "y.tab.c"
    break;

  case 145:
#line 508 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprTrue	(nbrLines); }
#line 2853 "y.tab.c"
    break;

  case 146:
#line 509 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprFalse(nbrLines); }
#line 2859 "y.tab.c"
    break;

  case 147:
#line 510 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprTimeout(nbrLines); }
#line 2865 "y.tab.c"
    break;

  case 148:
#line 511 "promela.y"
                                                                                { std::cout << "The 'np_' variable is not supported."; }
#line 2871 "y.tab.c"
    break;

  case 149:
#line 512 "promela.y"
                                                                        { std::cout << "The 'pc_value()' construct is not supported."; }
#line 2877 "y.tab.c"
    break;

  case 150:
#line 513 "promela.y"
                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 2883 "y.tab.c"
    break;

  case 151:
#line 514 "promela.y"
                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 2889 "y.tab.c"
    break;

  case 152:
#line 515 "promela.y"
                                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 2895 "y.tab.c"
    break;

  case 153:
#line 516 "promela.y"
                                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 2901 "y.tab.c"
    break;

  case 155:
#line 520 "promela.y"
                                                                                { std::cout << "The 'priority' construct is related to simulation and not supported."; }
#line 2907 "y.tab.c"
    break;

  case 156:
#line 523 "promela.y"
                                                                                { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 2913 "y.tab.c"
    break;

  case 157:
#line 524 "promela.y"
                                                                                        { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 2919 "y.tab.c"
    break;

  case 159:
#line 528 "promela.y"
                                                                { std::cout << "The 'provided' construct is currently not supported."; }
#line 2925 "y.tab.c"
    break;

  case 160:
#line 533 "promela.y"
                                                                                { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 2931 "y.tab.c"
    break;

  case 161:
#line 534 "promela.y"
                                                                                { (yyval.pExprVal) = new exprPar	((yyvsp[-1].pExprVal), nbrLines); }
#line 2937 "y.tab.c"
    break;

  case 162:
#line 535 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2943 "y.tab.c"
    break;

  case 163:
#line 536 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2949 "y.tab.c"
    break;

  case 164:
#line 537 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2955 "y.tab.c"
    break;

  case 165:
#line 538 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2961 "y.tab.c"
    break;

  case 166:
#line 539 "promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2967 "y.tab.c"
    break;

  case 167:
#line 540 "promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2973 "y.tab.c"
    break;

  case 168:
#line 541 "promela.y"
                                                                                        { (yyval.pExprVal) = new exprSkip	(nbrLines); }
#line 2979 "y.tab.c"
    break;

  case 169:
#line 544 "promela.y"
                                                                { (yyval.pExprVal) = new exprFull	((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2985 "y.tab.c"
    break;

  case 170:
#line 545 "promela.y"
                                                                        { (yyval.pExprVal) = new exprNFull((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2991 "y.tab.c"
    break;

  case 171:
#line 546 "promela.y"
                                                                        { (yyval.pExprVal) = new exprEmpty((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2997 "y.tab.c"
    break;

  case 172:
#line 547 "promela.y"
                                                                        { (yyval.pExprVal) = new exprNEmpty((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3003 "y.tab.c"
    break;

  case 173:
#line 550 "promela.y"
                                                                                { (yyval.pDataVal).sVal = nullptr; (yyval.pDataVal).iType = (yyvsp[0].iType); }
#line 3009 "y.tab.c"
    break;

  case 174:
#line 551 "promela.y"
                                                                                        { (yyval.pDataVal).sVal = (yyvsp[0].sVal); (yyval.pDataVal).iType = symTabNode::T_UTYPE; }
#line 3015 "y.tab.c"
    break;

  case 175:
#line 555 "promela.y"
                                                                                {	if((yyvsp[0].pDataVal).iType != symTabNode::T_UTYPE) {
														(yyval.pVarSymVal) = varSymNode::createSymTabNode((yyvsp[0].pDataVal).iType, nbrLines);
													} else {
														tdefSymNode* pType = *globalSymTab ? static_cast<tdefSymNode*>((*globalSymTab)->lookupInSymTab((yyvsp[0].pDataVal).sVal)) : nullptr;
														(yyval.pVarSymVal) = new utypeSymNode(pType, nbrLines);
														if((yyval.pVarSymVal) == nullptr) 
															std::cout << "The type "<<(yyvsp[0].pDataVal).sVal<<" was not declared in a typedef.\n";
													}
												}
#line 3029 "y.tab.c"
    break;

  case 176:
#line 564 "promela.y"
                                                                        {	if((yyvsp[-2].pDataVal).iType != symTabNode::T_UTYPE) {
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
#line 3045 "y.tab.c"
    break;

  case 178:
#line 579 "promela.y"
                                                                                        { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3051 "y.tab.c"
    break;

  case 179:
#line 583 "promela.y"
                                                                        { (yyval.pExprArgListVal) = nullptr; }
#line 3057 "y.tab.c"
    break;

  case 180:
#line 584 "promela.y"
                                                                                        { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3063 "y.tab.c"
    break;

  case 181:
#line 588 "promela.y"
                                                                                { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3069 "y.tab.c"
    break;

  case 182:
#line 589 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList(static_cast<exprRArg*>((yyvsp[-3].pExprVal)), static_cast<exprArgList*>((yyvsp[-1].pExprArgListVal)), nbrLines); }
#line 3075 "y.tab.c"
    break;

  case 183:
#line 592 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList(static_cast<exprRArg*>((yyvsp[0].pExprVal)), nbrLines); }
#line 3081 "y.tab.c"
    break;

  case 184:
#line 593 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList(static_cast<exprRArg*>((yyvsp[-2].pExprVal)), static_cast<exprArgList*>((yyvsp[0].pExprArgListVal)), nbrLines); }
#line 3087 "y.tab.c"
    break;

  case 185:
#line 596 "promela.y"
                                                                                { (yyval.pExprRArgVal) = new exprRArgVar((yyvsp[0].pExprVarRefVal), nbrLines); }
#line 3093 "y.tab.c"
    break;

  case 186:
#line 597 "promela.y"
                                                                                { (yyval.pExprRArgVal) = new exprRArgEval((yyvsp[-1].pExprVal), nbrLines); }
#line 3099 "y.tab.c"
    break;

  case 187:
#line 598 "promela.y"
                                                                                        { (yyval.pExprRArgVal) = new exprRArgConst((yyvsp[0].iVal), nbrLines); }
#line 3105 "y.tab.c"
    break;

  case 188:
#line 599 "promela.y"
                                                                        { (yyval.pExprRArgVal) = new exprRArgConst(-(yyvsp[0].iVal), nbrLines); }
#line 3111 "y.tab.c"
    break;

  case 189:
#line 603 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList((yyvsp[0].pExprRArgVal), nbrLines); }
#line 3117 "y.tab.c"
    break;

  case 190:
#line 604 "promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList((yyvsp[-2].pExprRArgVal), (yyvsp[0].pExprArgListVal), nbrLines); }
#line 3123 "y.tab.c"
    break;

  case 191:
#line 605 "promela.y"
                                                                        { (yyval.pExprArgListVal) = new exprArgList((yyvsp[-3].pExprRArgVal), (yyvsp[-1].pExprArgListVal), nbrLines); }
#line 3129 "y.tab.c"
    break;

  case 192:
#line 606 "promela.y"
                                                                                { (yyval.pExprArgListVal) = (yyvsp[-1].pExprArgListVal); }
#line 3135 "y.tab.c"
    break;

  case 193:
#line 609 "promela.y"
                                                                                { *mtypes = (*mtypes)->addMType((yyvsp[0].sVal)); free((yyvsp[0].sVal)); }
#line 3141 "y.tab.c"
    break;

  case 194:
#line 610 "promela.y"
                                                                                        { *mtypes = (*mtypes)->addMType((yyvsp[0].sVal)); free((yyvsp[0].sVal)); }
#line 3147 "y.tab.c"
    break;


#line 3151 "y.tab.c"

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
      yyerror (globalSymTab, mtypes, YY_("syntax error"));
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
        yyerror (globalSymTab, mtypes, yymsgp);
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
                      yytoken, &yylval, globalSymTab, mtypes);
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
                  yystos[yystate], yyvsp, globalSymTab, mtypes);
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
  yyerror (globalSymTab, mtypes, YY_("memory exhausted"));
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
                  yytoken, &yylval, globalSymTab, mtypes);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, globalSymTab, mtypes);
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
#line 613 "promela.y"

