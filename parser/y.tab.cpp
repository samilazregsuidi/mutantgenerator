/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

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


#line 126 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"

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

#include "y.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CONST = 3,                      /* CONST  */
  YYSYMBOL_IF = 4,                         /* IF  */
  YYSYMBOL_DO = 5,                         /* DO  */
  YYSYMBOL_TYPE = 6,                       /* TYPE  */
  YYSYMBOL_NAME = 7,                       /* NAME  */
  YYSYMBOL_UNAME = 8,                      /* UNAME  */
  YYSYMBOL_PNAME = 9,                      /* PNAME  */
  YYSYMBOL_INAME = 10,                     /* INAME  */
  YYSYMBOL_STRING = 11,                    /* STRING  */
  YYSYMBOL_REAL = 12,                      /* REAL  */
  YYSYMBOL_TRUE = 13,                      /* TRUE  */
  YYSYMBOL_FALSE = 14,                     /* FALSE  */
  YYSYMBOL_SKIP = 15,                      /* SKIP  */
  YYSYMBOL_ASSERT = 16,                    /* ASSERT  */
  YYSYMBOL_PRINT = 17,                     /* PRINT  */
  YYSYMBOL_PRINTM = 18,                    /* PRINTM  */
  YYSYMBOL_C_CODE = 19,                    /* C_CODE  */
  YYSYMBOL_C_DECL = 20,                    /* C_DECL  */
  YYSYMBOL_C_EXPR = 21,                    /* C_EXPR  */
  YYSYMBOL_C_STATE = 22,                   /* C_STATE  */
  YYSYMBOL_C_TRACK = 23,                   /* C_TRACK  */
  YYSYMBOL_RUN = 24,                       /* RUN  */
  YYSYMBOL_LEN = 25,                       /* LEN  */
  YYSYMBOL_ENABLED = 26,                   /* ENABLED  */
  YYSYMBOL_EVAL = 27,                      /* EVAL  */
  YYSYMBOL_PC_VAL = 28,                    /* PC_VAL  */
  YYSYMBOL_TYPEDEF = 29,                   /* TYPEDEF  */
  YYSYMBOL_MTYPE = 30,                     /* MTYPE  */
  YYSYMBOL_INLINE = 31,                    /* INLINE  */
  YYSYMBOL_LABEL = 32,                     /* LABEL  */
  YYSYMBOL_OF = 33,                        /* OF  */
  YYSYMBOL_GOTO = 34,                      /* GOTO  */
  YYSYMBOL_BREAK = 35,                     /* BREAK  */
  YYSYMBOL_ELSE = 36,                      /* ELSE  */
  YYSYMBOL_SEMI = 37,                      /* SEMI  */
  YYSYMBOL_FI = 38,                        /* FI  */
  YYSYMBOL_OD = 39,                        /* OD  */
  YYSYMBOL_SEP = 40,                       /* SEP  */
  YYSYMBOL_ATOMIC = 41,                    /* ATOMIC  */
  YYSYMBOL_NON_ATOMIC = 42,                /* NON_ATOMIC  */
  YYSYMBOL_D_STEP = 43,                    /* D_STEP  */
  YYSYMBOL_UNLESS = 44,                    /* UNLESS  */
  YYSYMBOL_TIMEOUT = 45,                   /* TIMEOUT  */
  YYSYMBOL_NONPROGRESS = 46,               /* NONPROGRESS  */
  YYSYMBOL_ACTIVE = 47,                    /* ACTIVE  */
  YYSYMBOL_PROCTYPE = 48,                  /* PROCTYPE  */
  YYSYMBOL_D_PROCTYPE = 49,                /* D_PROCTYPE  */
  YYSYMBOL_HIDDEN = 50,                    /* HIDDEN  */
  YYSYMBOL_SHOW = 51,                      /* SHOW  */
  YYSYMBOL_ISLOCAL = 52,                   /* ISLOCAL  */
  YYSYMBOL_PRIORITY = 53,                  /* PRIORITY  */
  YYSYMBOL_PROVIDED = 54,                  /* PROVIDED  */
  YYSYMBOL_FULL = 55,                      /* FULL  */
  YYSYMBOL_EMPTY = 56,                     /* EMPTY  */
  YYSYMBOL_NFULL = 57,                     /* NFULL  */
  YYSYMBOL_NEMPTY = 58,                    /* NEMPTY  */
  YYSYMBOL_XU = 59,                        /* XU  */
  YYSYMBOL_CLAIM = 60,                     /* CLAIM  */
  YYSYMBOL_TRACE = 61,                     /* TRACE  */
  YYSYMBOL_INIT = 62,                      /* INIT  */
  YYSYMBOL_WHILE = 63,                     /* WHILE  */
  YYSYMBOL_WHEN = 64,                      /* WHEN  */
  YYSYMBOL_WAIT = 65,                      /* WAIT  */
  YYSYMBOL_RESET = 66,                     /* RESET  */
  YYSYMBOL_SPEC = 67,                      /* SPEC  */
  YYSYMBOL_EVENTUALLY = 68,                /* EVENTUALLY  */
  YYSYMBOL_ALWAYS = 69,                    /* ALWAYS  */
  YYSYMBOL_GLOBALLY = 70,                  /* GLOBALLY  */
  YYSYMBOL_FINALLY = 71,                   /* FINALLY  */
  YYSYMBOL_UNTIL = 72,                     /* UNTIL  */
  YYSYMBOL_LTL = 73,                       /* LTL  */
  YYSYMBOL_ASGN = 74,                      /* ASGN  */
  YYSYMBOL_SND = 75,                       /* SND  */
  YYSYMBOL_O_SND = 76,                     /* O_SND  */
  YYSYMBOL_RCV = 77,                       /* RCV  */
  YYSYMBOL_R_RCV = 78,                     /* R_RCV  */
  YYSYMBOL_OR = 79,                        /* OR  */
  YYSYMBOL_AND = 80,                       /* AND  */
  YYSYMBOL_81_ = 81,                       /* '|'  */
  YYSYMBOL_82_ = 82,                       /* '^'  */
  YYSYMBOL_83_ = 83,                       /* '&'  */
  YYSYMBOL_EQ = 84,                        /* EQ  */
  YYSYMBOL_NE = 85,                        /* NE  */
  YYSYMBOL_GT = 86,                        /* GT  */
  YYSYMBOL_LT = 87,                        /* LT  */
  YYSYMBOL_GE = 88,                        /* GE  */
  YYSYMBOL_LE = 89,                        /* LE  */
  YYSYMBOL_LSHIFT = 90,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 91,                    /* RSHIFT  */
  YYSYMBOL_92_ = 92,                       /* '+'  */
  YYSYMBOL_93_ = 93,                       /* '-'  */
  YYSYMBOL_94_ = 94,                       /* '*'  */
  YYSYMBOL_95_ = 95,                       /* '/'  */
  YYSYMBOL_96_ = 96,                       /* '%'  */
  YYSYMBOL_INCR = 97,                      /* INCR  */
  YYSYMBOL_DECR = 98,                      /* DECR  */
  YYSYMBOL_99_ = 99,                       /* '~'  */
  YYSYMBOL_UMIN = 100,                     /* UMIN  */
  YYSYMBOL_NEG = 101,                      /* NEG  */
  YYSYMBOL_COUNT = 102,                    /* COUNT  */
  YYSYMBOL_CONTEXT = 103,                  /* CONTEXT  */
  YYSYMBOL_DOT = 104,                      /* DOT  */
  YYSYMBOL_IMPLIES = 105,                  /* IMPLIES  */
  YYSYMBOL_106_ = 106,                     /* '('  */
  YYSYMBOL_107_ = 107,                     /* ')'  */
  YYSYMBOL_108_ = 108,                     /* '['  */
  YYSYMBOL_109_ = 109,                     /* ']'  */
  YYSYMBOL_110_ = 110,                     /* '{'  */
  YYSYMBOL_111_ = 111,                     /* '}'  */
  YYSYMBOL_112_ = 112,                     /* ':'  */
  YYSYMBOL_113_ = 113,                     /* ','  */
  YYSYMBOL_114_ = 114,                     /* '.'  */
  YYSYMBOL_115_ = 115,                     /* '@'  */
  YYSYMBOL_YYACCEPT = 116,                 /* $accept  */
  YYSYMBOL_start_parsing = 117,            /* start_parsing  */
  YYSYMBOL_118_1 = 118,                    /* $@1  */
  YYSYMBOL_program = 119,                  /* program  */
  YYSYMBOL_units = 120,                    /* units  */
  YYSYMBOL_unit = 121,                     /* unit  */
  YYSYMBOL_proc = 122,                     /* proc  */
  YYSYMBOL_123_2 = 123,                    /* $@2  */
  YYSYMBOL_124_3 = 124,                    /* $@3  */
  YYSYMBOL_proctype = 125,                 /* proctype  */
  YYSYMBOL_inst = 126,                     /* inst  */
  YYSYMBOL_init = 127,                     /* init  */
  YYSYMBOL_128_4 = 128,                    /* $@4  */
  YYSYMBOL_events = 129,                   /* events  */
  YYSYMBOL_utypedef = 130,                 /* utypedef  */
  YYSYMBOL_mtypedef = 131,                 /* mtypedef  */
  YYSYMBOL_132_5 = 132,                    /* $@5  */
  YYSYMBOL_ns = 133,                       /* ns  */
  YYSYMBOL_134_6 = 134,                    /* $@6  */
  YYSYMBOL_135_7 = 135,                    /* $@7  */
  YYSYMBOL_136_8 = 136,                    /* $@8  */
  YYSYMBOL_c_fcts = 137,                   /* c_fcts  */
  YYSYMBOL_cstate = 138,                   /* cstate  */
  YYSYMBOL_ccode = 139,                    /* ccode  */
  YYSYMBOL_cexpr = 140,                    /* cexpr  */
  YYSYMBOL_body = 141,                     /* body  */
  YYSYMBOL_142_9 = 142,                    /* $@9  */
  YYSYMBOL_sequence = 143,                 /* sequence  */
  YYSYMBOL_step = 144,                     /* step  */
  YYSYMBOL_vis = 145,                      /* vis  */
  YYSYMBOL_asgn = 146,                     /* asgn  */
  YYSYMBOL_one_decl = 147,                 /* one_decl  */
  YYSYMBOL_148_10 = 148,                   /* $@10  */
  YYSYMBOL_149_11 = 149,                   /* $@11  */
  YYSYMBOL_decl_lst = 150,                 /* decl_lst  */
  YYSYMBOL_decl = 151,                     /* decl  */
  YYSYMBOL_var_list = 152,                 /* var_list  */
  YYSYMBOL_ivar = 153,                     /* ivar  */
  YYSYMBOL_param_list = 154,               /* param_list  */
  YYSYMBOL_ch_init = 155,                  /* ch_init  */
  YYSYMBOL_basetype = 156,                 /* basetype  */
  YYSYMBOL_typ_list = 157,                 /* typ_list  */
  YYSYMBOL_vardcl = 158,                   /* vardcl  */
  YYSYMBOL_varref = 159,                   /* varref  */
  YYSYMBOL_pfld = 160,                     /* pfld  */
  YYSYMBOL_cmpnd = 161,                    /* cmpnd  */
  YYSYMBOL_sfld = 162,                     /* sfld  */
  YYSYMBOL_stmnt = 163,                    /* stmnt  */
  YYSYMBOL_Special = 164,                  /* Special  */
  YYSYMBOL_Stmnt = 165,                    /* Stmnt  */
  YYSYMBOL_options = 166,                  /* options  */
  YYSYMBOL_option = 167,                   /* option  */
  YYSYMBOL_real_expr = 168,                /* real_expr  */
  YYSYMBOL_OS = 169,                       /* OS  */
  YYSYMBOL_MS = 170,                       /* MS  */
  YYSYMBOL_aname = 171,                    /* aname  */
  YYSYMBOL_expr = 172,                     /* expr  */
  YYSYMBOL_Opt_priority = 173,             /* Opt_priority  */
  YYSYMBOL_full_expr = 174,                /* full_expr  */
  YYSYMBOL_Opt_enabler = 175,              /* Opt_enabler  */
  YYSYMBOL_Expr = 176,                     /* Expr  */
  YYSYMBOL_Probe = 177,                    /* Probe  */
  YYSYMBOL_args = 178,                     /* args  */
  YYSYMBOL_prargs = 179,                   /* prargs  */
  YYSYMBOL_margs = 180,                    /* margs  */
  YYSYMBOL_arg = 181,                      /* arg  */
  YYSYMBOL_rarg = 182,                     /* rarg  */
  YYSYMBOL_rargs = 183,                    /* rargs  */
  YYSYMBOL_nlst = 184,                     /* nlst  */
  YYSYMBOL_props = 185,                    /* props  */
  YYSYMBOL_prop = 186,                     /* prop  */
  YYSYMBOL_prop_expr = 187,                /* prop_expr  */
  YYSYMBOL_quants = 188,                   /* quants  */
  YYSYMBOL_quant = 189                     /* quant  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if 1

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
#endif /* 1 */

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
#define YYLAST   1832

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  116
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  244
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  472

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   351


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
       0,   146,   146,   146,   151,   154,   155,   158,   159,   160,
     161,   174,   175,   176,   177,   178,   184,   192,   182,   207,
     208,   211,   212,   213,   214,   228,   227,   243,   246,   258,
     258,   277,   278,   280,   277,   295,   296,   299,   300,   301,
     302,   305,   306,   309,   312,   312,   322,   323,   324,   327,
     332,   333,   334,   335,   343,   344,   345,   346,   349,   350,
     356,   356,   357,   357,   360,   361,   365,   366,   373,   374,
     377,   382,   387,   392,   393,   394,   398,   401,   402,   406,
     421,   438,   439,   440,   443,   446,   447,   450,   451,   454,
     455,   459,   460,   463,   464,   465,   466,   467,   468,   469,
     473,   474,   475,   476,   477,   478,   479,   480,   481,   482,
     483,   484,   485,   486,   487,   488,   489,   490,   502,   503,
     506,   507,   511,   512,   513,   514,   515,   516,   517,   520,
     521,   524,   525,   528,   529,   532,   533,   534,   535,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   545,   546,
     547,   548,   549,   550,   551,   552,   553,   561,   562,   563,
     568,   569,   570,   571,   572,   573,   574,   575,   576,   577,
     578,   579,   580,   581,   582,   583,   586,   587,   590,   591,
     594,   595,   600,   601,   602,   603,   604,   605,   606,   607,
     608,   611,   612,   613,   614,   618,   619,   623,   624,   628,
     629,   632,   633,   636,   637,   638,   639,   643,   644,   645,
     646,   649,   650,   651,   655,   656,   657,   660,   664,   665,
     666,   667,   668,   669,   670,   671,   672,   673,   674,   675,
     676,   677,   678,   679,   680,   681,   682,   683,   684,   685,
     686,   689,   690,   693,   694
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CONST", "IF", "DO",
  "TYPE", "NAME", "UNAME", "PNAME", "INAME", "STRING", "REAL", "TRUE",
  "FALSE", "SKIP", "ASSERT", "PRINT", "PRINTM", "C_CODE", "C_DECL",
  "C_EXPR", "C_STATE", "C_TRACK", "RUN", "LEN", "ENABLED", "EVAL",
  "PC_VAL", "TYPEDEF", "MTYPE", "INLINE", "LABEL", "OF", "GOTO", "BREAK",
  "ELSE", "SEMI", "FI", "OD", "SEP", "ATOMIC", "NON_ATOMIC", "D_STEP",
  "UNLESS", "TIMEOUT", "NONPROGRESS", "ACTIVE", "PROCTYPE", "D_PROCTYPE",
  "HIDDEN", "SHOW", "ISLOCAL", "PRIORITY", "PROVIDED", "FULL", "EMPTY",
  "NFULL", "NEMPTY", "XU", "CLAIM", "TRACE", "INIT", "WHILE", "WHEN",
  "WAIT", "RESET", "SPEC", "EVENTUALLY", "ALWAYS", "GLOBALLY", "FINALLY",
  "UNTIL", "LTL", "ASGN", "SND", "O_SND", "RCV", "R_RCV", "OR", "AND",
  "'|'", "'^'", "'&'", "EQ", "NE", "GT", "LT", "GE", "LE", "LSHIFT",
  "RSHIFT", "'+'", "'-'", "'*'", "'/'", "'%'", "INCR", "DECR", "'~'",
  "UMIN", "NEG", "COUNT", "CONTEXT", "DOT", "IMPLIES", "'('", "')'", "'['",
  "']'", "'{'", "'}'", "':'", "','", "'.'", "'@'", "$accept",
  "start_parsing", "$@1", "program", "units", "unit", "proc", "$@2", "$@3",
  "proctype", "inst", "init", "$@4", "events", "utypedef", "mtypedef",
  "$@5", "ns", "$@6", "$@7", "$@8", "c_fcts", "cstate", "ccode", "cexpr",
  "body", "$@9", "sequence", "step", "vis", "asgn", "one_decl", "$@10",
  "$@11", "decl_lst", "decl", "var_list", "ivar", "param_list", "ch_init",
  "basetype", "typ_list", "vardcl", "varref", "pfld", "cmpnd", "sfld",
  "stmnt", "Special", "Stmnt", "options", "option", "real_expr", "OS",
  "MS", "aname", "expr", "Opt_priority", "full_expr", "Opt_enabler",
  "Expr", "Probe", "args", "prargs", "margs", "arg", "rarg", "rargs",
  "nlst", "props", "prop", "prop_expr", "quants", "quant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-403)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-131)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -403,    39,  1423,  -403,  -403,  -403,    48,    51,    11,  -403,
    -403,   -79,  -403,  -403,  -403,   -43,  -403,    -1,  1389,  -403,
    -403,   106,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,
     154,  -403,   115,   120,    27,   139,    87,  -403,  -403,   117,
     168,  -403,    -1,  -403,  -403,  -403,   178,     7,  -403,   177,
     185,   143,  -403,    96,   102,   992,   214,   -43,   113,  -403,
    -403,  -403,  -403,   221,   221,  -403,  -403,   157,   200,   127,
     172,  -403,  -403,  -403,   281,   281,    30,   -26,   216,  -403,
    -403,  -403,  1210,   251,   253,  -403,   174,   255,   256,   258,
     331,  -403,  -403,   257,   260,  -403,  -403,   262,   263,   265,
     266,  1269,  1269,  1269,   269,   252,  1210,   992,  -403,  -403,
     437,  -403,  -403,   138,   264,  -403,   332,  -403,  -403,  1718,
    -403,   121,  -403,  -403,  -403,    61,   271,   270,    35,  -403,
     272,   305,  -403,  -403,   143,  -403,   376,   676,   346,   281,
     348,  1269,   784,  1269,   381,   382,  1269,   282,   149,  -403,
     380,    21,  -403,  -403,   287,    18,  1269,  1269,  -403,   992,
     992,    18,    18,    18,    18,  1269,  -403,  -403,  -403,  1269,
     381,  1238,   -46,   437,     2,  -403,   283,   888,  1210,  1269,
    1269,    66,    84,  -403,  -403,    18,  -403,  1096,  1210,  1210,
    1269,  1269,  1269,  1269,  1269,  1269,  1269,  1269,  1269,  1269,
    1269,  1269,  1269,  1269,  1269,  1269,  1210,  1210,  -403,  -403,
    -403,    61,    61,  -403,   472,    61,   164,   152,   388,   395,
     396,   221,  1155,  -403,   288,   293,     9,   572,  -403,  -403,
    -403,  1511,    68,  -403,  -403,  -403,  1542,  -403,  -403,  1442,
     296,  -403,   335,   337,   291,   341,   352,  1269,   353,  1573,
    1602,   437,   437,   359,   360,   361,   362,  1298,  1269,  1269,
    1631,   264,  1269,  -403,  -403,   338,  -403,  -403,  -403,  -403,
    1407,  -403,  -403,  -403,  -403,   371,    19,   478,    19,    19,
    -403,   -69,  -403,    19,    19,  -403,  -403,  -403,   220,   404,
     259,  -403,   969,   342,  1262,  1453,  1453,   241,   241,   241,
     241,   232,   232,   125,   125,  -403,  -403,  -403,   220,   404,
     259,  -403,   -17,   678,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,  -403,   162,  -403,  -403,   378,  -403,     3,   377,
    -403,  -403,   487,  -403,  1736,   376,  -403,  -403,  -403,     9,
      57,  -403,  -403,  1096,   -20,  1269,  -403,  1269,   384,  -403,
    -403,   389,  -403,  -403,  -403,   386,   387,  -403,  -403,  -403,
    -403,   988,   259,  -403,  -403,  1477,  -403,  1269,  1269,   413,
    -403,   393,   392,    19,    19,   416,   394,  -403,   162,   162,
     433,   567,   778,   881,   651,   759,   759,   -18,   -18,   -18,
     -18,     8,     8,   -17,   -17,   -17,  -403,  -403,  -403,  -403,
    -403,   397,  -403,   -43,   -44,     9,     9,     9,     9,   992,
     381,   497,  -403,  -403,  -403,   117,  -403,  -403,  1269,   400,
    1660,  -403,  -403,  -403,   401,  -403,  -403,  -403,   117,   477,
    -403,  -403,   158,   158,  -403,  -403,   572,  -403,  -403,  -403,
    1689,  -403,  -403,  -403,   457,   414,  -403,  -403,   417,   -43,
     183,  1210,  -403,  -403,  -403,   418,   421,   426,   183,  -403,
    -403,  -403
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,    21,     1,    41,    42,     0,     0,     0,    31,
      15,    22,    55,    56,    57,     0,    25,   214,     4,     5,
       7,     0,     8,     9,    11,    12,    14,    13,    36,    35,
       0,    10,     0,     0,     0,     0,     0,    44,    27,   176,
       0,     3,   214,     6,    19,    20,     0,    58,    62,    37,
      38,    54,    32,     0,     0,    54,     0,     0,     0,   216,
      16,    59,    29,     0,     0,    39,    40,     0,    64,     0,
       0,    23,    24,   166,     0,     0,    85,     0,     0,   167,
     168,   190,     0,     0,     0,    43,     0,     0,     0,     0,
       0,    97,   113,     0,     0,   169,   170,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    54,   107,   165,
      54,    46,    49,   164,    89,    84,    52,    91,    92,   178,
     112,   179,   182,   177,    26,     0,     0,     0,    81,    61,
      68,    70,    63,    60,    54,    28,    73,    54,     0,   118,
       0,     0,    54,     0,     0,     0,   195,    85,   164,   106,
       0,     0,   133,   134,     0,     0,     0,     0,    98,    54,
      54,     0,     0,     0,     0,     0,   157,   156,   155,     0,
       0,     0,     0,    54,   131,    48,     0,    54,     0,     0,
       0,     0,     0,   101,   102,     0,    87,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   240,   244,
     243,     0,     0,   239,     0,     0,   241,    54,     0,     0,
       0,     0,     0,    65,    74,     0,     0,   129,    95,   119,
      96,     0,    85,    51,    50,    99,     0,   175,   174,   201,
       0,   196,     0,     0,   197,     0,     0,   195,     0,     0,
       0,    54,    54,     0,     0,     0,     0,     0,     0,     0,
       0,    89,     0,   135,   183,     0,    45,   132,    47,   100,
     201,    94,   199,   111,   205,     0,     0,     0,     0,     0,
     203,   207,    93,     0,     0,   108,    90,    53,   151,   189,
     150,   188,   143,   142,   141,   148,   149,   144,   145,   146,
     147,   152,   153,   136,   137,   138,   139,   140,   187,   186,
     185,   184,   238,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   217,   219,   242,    67,     0,   211,     0,     0,
      82,    69,     0,    72,    71,    73,    33,   128,   127,     0,
       0,   120,    86,     0,     0,     0,   117,     0,     0,   105,
     104,     0,   160,   161,   171,     0,     0,   191,   193,   192,
     194,   151,   150,   154,    88,     0,   116,     0,     0,     0,
     206,     0,     0,     0,     0,     0,     0,   218,   236,   237,
     235,   234,   227,   226,   225,   232,   233,   228,   229,   230,
     231,   220,   221,   222,   223,   224,    17,   212,    30,   213,
      83,     0,    75,     0,     0,     0,     0,     0,     0,    54,
       0,     0,   202,   198,   103,   176,   114,   115,     0,     0,
       0,   109,   210,   162,     0,   208,   110,   163,   176,     0,
      34,   122,   123,   124,   125,   126,   129,   173,   172,   159,
       0,   200,   204,   209,   180,     0,   121,   158,     0,     0,
       0,     0,    18,    77,    78,    79,     0,     0,     0,    76,
     181,    80
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -403,  -403,  -403,  -403,  -403,   516,  -403,  -403,  -403,  -403,
    -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,
    -403,  -403,  -403,    25,  -403,   -57,  -403,  -102,  -107,    29,
    -403,    14,  -403,  -403,  -121,  -403,   -53,  -403,   190,  -403,
    -403,    69,  -403,   -54,  -140,   356,   277,  -135,  -403,  -403,
     -60,  -403,  -208,  -167,  -403,  -403,   217,  -402,   -80,  -403,
     -89,  -403,   295,  -403,   365,  -171,  -403,  -144,  -403,   504,
    -403,   -33,   333,  -403
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,    17,    18,    19,    20,   126,   438,    46,
      21,    22,    39,    23,    24,    25,   127,    26,    35,    70,
     413,    27,    28,   108,   109,    38,    55,   110,   111,    67,
      62,   112,    63,    64,    69,   336,   129,   130,   225,   343,
     465,   466,   131,   148,   114,   115,   186,   116,   117,   118,
     138,   139,   350,   176,   177,   154,   119,    57,   120,   459,
     121,   122,   240,   358,   271,   241,   281,   282,   338,    41,
      42,   214,   215,   216
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     124,   113,   149,   175,   237,   173,   265,   235,   272,   272,
     407,   132,   347,   223,   -60,   140,    31,   172,    34,   314,
     314,   348,   274,   449,   245,   147,   147,    29,   147,    36,
     261,    30,    31,   206,   207,   227,   454,   383,   285,     3,
    -130,  -130,  -130,    29,   384,   314,   275,    30,   415,   416,
     417,   418,   287,   113,   315,   315,   113,   251,   252,    32,
     351,   264,    33,   441,   208,    68,   175,    37,   147,   274,
     268,   213,    40,   147,   327,   328,   329,   330,   331,   229,
     315,    61,   143,   113,   365,   366,   144,   274,   113,   145,
      53,   147,   420,   275,    54,   421,   335,   246,   269,   289,
     291,   248,   329,   330,   331,   113,   113,   253,   254,   255,
     256,   275,   277,  -130,   408,   349,   409,   309,   311,   113,
     175,   105,   105,   113,   105,   278,    49,   280,   280,   209,
     210,    50,   379,   113,   381,   382,   211,    51,   141,   385,
     386,   414,   142,   219,   175,   175,    52,   220,    68,   415,
     416,   417,   418,   276,    44,    45,   234,   213,   213,   277,
      47,   213,    48,   133,   105,    48,   419,   212,   341,   105,
      56,   283,   278,   113,   279,    58,   141,   277,   312,   313,
     353,   152,   333,   153,   422,    60,   423,   105,    65,   463,
     278,   464,   284,    12,    13,    14,    66,   113,   113,   314,
     206,   207,    12,    13,    14,    71,   429,   442,   443,   444,
     445,    72,   178,   179,   180,   181,   182,   123,   235,   203,
     204,   205,   280,   125,   280,   280,   242,   243,   128,   280,
     280,    68,   209,   210,   315,   183,   184,   134,   135,   434,
     435,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   417,   418,   327,   328,   329,   330,   331,   -66,
     213,   213,   213,   213,   213,   213,   213,   213,   213,   213,
     213,   213,   213,   213,   213,   213,   213,   213,   136,   456,
     447,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   399,   400,   401,   402,   403,   404,   405,   113,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   446,   166,   167,
     168,   137,   146,   171,   201,   202,   203,   204,   205,   280,
     280,   199,   200,   201,   202,   203,   204,   205,   158,   175,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   440,   150,   231,   151,
     236,   155,   156,   239,   157,   113,   170,   159,   161,   162,
     160,   163,   164,   249,   250,   169,   187,   217,   185,   222,
     218,   467,   257,   224,   228,   221,   260,   230,   147,   238,
     141,   244,   113,   247,   266,   337,   270,   270,   339,   340,
     346,   345,   462,   356,   357,   288,   290,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   310,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   344,
      73,    74,    75,   279,    76,   284,    77,    78,   359,   376,
      79,    80,    81,    82,    83,    84,     4,     5,    85,   360,
     362,    86,    87,    88,   239,    89,   367,   368,   369,   370,
     314,    90,    91,    92,   174,   371,   372,   378,    93,   375,
      94,   380,    95,    96,   207,   406,   410,    12,    13,    14,
     411,   424,    97,    98,    99,   100,   425,   426,   427,   431,
     432,   433,   436,   437,   448,   315,   439,   451,   453,   314,
     455,   458,   101,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   461,   460,   327,   328,   329,   330,   331,
     102,   468,   469,   470,    43,   412,   103,   471,   374,   104,
     105,   286,   361,   106,   315,   273,    59,   107,  -129,   334,
       0,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,     0,     0,   327,   328,   329,   330,   331,     0,
       0,     0,   239,     0,   239,    73,    74,    75,   -54,    76,
     -54,    77,    78,   332,     0,    79,    80,    81,    82,    83,
      84,     4,     5,    85,   239,   430,    86,    87,    88,     0,
      89,     0,     0,     0,   314,     0,    90,    91,    92,   174,
       0,     0,     0,    93,     0,    94,     0,    95,    96,     0,
       0,     0,    12,    13,    14,     0,     0,    97,    98,    99,
     100,     0,     0,     0,     0,     0,     0,     0,     0,   315,
       0,     0,     0,     0,     0,   450,     0,   101,   318,   319,
     320,   321,   322,   323,   324,   325,   326,     0,     0,   327,
     328,   329,   330,   331,     0,   102,     0,     0,     0,     0,
       0,   103,     0,     0,   104,   105,     0,     0,   106,    73,
      74,    75,   107,    76,     0,    77,    78,     0,   314,    79,
      80,    81,    82,    83,    84,     4,     5,    85,     0,     0,
      86,    87,    88,     0,    89,     0,     0,     0,     0,     0,
      90,    91,    92,     0,     0,   314,     0,    93,     0,    94,
       0,    95,    96,   315,     0,     0,    12,    13,    14,     0,
       0,    97,    98,    99,   100,   321,   322,   323,   324,   325,
     326,     0,     0,   327,   328,   329,   330,   331,     0,     0,
     315,   101,     0,     0,     0,     0,     0,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,     0,   102,
     327,   328,   329,   330,   331,   103,     0,     0,   104,   105,
       0,     0,   106,     0,   226,   387,   107,    73,    74,    75,
       0,   232,     0,    77,    78,     0,   314,    79,    80,    81,
      82,    83,    84,     4,     5,    85,     0,     0,    86,    87,
      88,     0,    89,     0,     0,   314,     0,     0,    90,    91,
      92,     0,     0,     0,     0,    93,     0,    94,     0,    95,
      96,   315,     0,     0,    12,    13,    14,     0,     0,    97,
      98,    99,   100,   233,     0,   323,   324,   325,   326,     0,
     315,   327,   328,   329,   330,   331,     0,     0,     0,   101,
     319,   320,   321,   322,   323,   324,   325,   326,     0,     0,
     327,   328,   329,   330,   331,     0,     0,   102,     0,     0,
       0,     0,     0,   103,     0,     0,   104,   105,     0,     0,
     106,    73,    74,    75,   107,    76,     0,    77,    78,     0,
       0,    79,    80,    81,    82,    83,    84,     4,     5,    85,
       0,     0,    86,    87,    88,     0,    89,     0,   314,     0,
       0,     0,    90,    91,    92,   267,     0,     0,     0,    93,
       0,    94,     0,    95,    96,     0,     0,     0,    12,    13,
      14,     0,     0,    97,    98,    99,   100,     0,     0,     0,
       0,     0,     0,   315,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   101,   320,   321,   322,   323,   324,   325,
     326,     0,     0,   327,   328,   329,   330,   331,     0,     0,
       0,   102,     0,     0,     0,     0,     0,   103,     0,     0,
     104,   105,     0,     0,   106,    73,    74,    75,   107,    76,
       0,    77,    78,     0,     0,    79,    80,    81,    82,    83,
      84,     4,     5,    85,     0,     0,    86,    87,    88,     0,
      89,     0,     0,     0,     0,     0,    90,    91,    92,     0,
       0,     0,     0,    93,     0,    94,     0,    95,    96,     0,
       0,     0,    12,    13,    14,     0,     0,    97,    98,    99,
     100,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,     0,   101,   259,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   102,     0,     0,     0,     0,
       0,   103,     0,     0,   104,   105,     0,     0,   106,    73,
      74,    75,   107,   232,     0,    77,    78,     0,     0,    79,
      80,    81,    82,    83,    84,     4,     5,    85,     0,     0,
      86,    87,    88,     0,    89,     0,     0,     0,     0,     0,
      90,    91,    92,     0,     0,     0,     0,    93,     0,    94,
       0,    95,    96,     0,     0,     0,     0,     0,     0,     0,
       0,    97,    98,    99,   100,     0,     0,     0,    73,     0,
       0,     0,   147,     0,    77,     0,     0,     0,    79,    80,
       0,   101,     0,     0,     0,     0,    85,     0,     0,    86,
      87,    88,     0,    89,     0,     0,     0,     0,     0,   102,
       0,     0,     0,     0,     0,   103,     0,     0,   104,   105,
      95,    96,   106,     0,     0,     0,   107,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,   147,     0,    77,
       0,     0,     0,    79,    80,    81,     0,     0,     0,     0,
     101,    85,     0,     0,    86,    87,    88,     0,    89,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   102,     0,
       0,     0,     0,     0,   103,    95,    96,   104,   105,     0,
       0,   165,     0,   342,     0,    97,    98,    99,   100,     0,
       0,     0,    73,     0,     0,   262,   147,     0,    77,     0,
       0,     0,    79,    80,     0,   101,     0,     0,     0,     0,
      85,     0,     0,    86,    87,    88,     0,    89,     0,     0,
       0,     0,     0,   102,     0,     0,     0,     0,     0,   103,
       0,     0,   104,   105,    95,    96,   106,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   262,     0,     0,     0,     0,
       0,     0,     0,     0,   101,   263,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,     0,
       0,     0,   102,     0,     0,     0,     0,     0,   103,     0,
       0,   104,   105,     0,     0,   165,     0,   258,   259,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   -54,     0,   -54,     0,     0,
       0,     0,     0,     0,     0,   263,     0,     0,     4,     5,
       0,     6,     7,     0,     0,     0,     0,     0,     8,     0,
       9,     0,     0,     0,     0,     0,    10,     0,     0,   -54,
       0,   -54,     0,     0,     0,     0,    11,   -21,   -21,    12,
      13,    14,     4,     5,     0,     6,     7,     0,     0,     0,
      15,    16,     8,     0,     9,     0,     0,     0,     0,     0,
      10,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      11,     0,     0,    12,    13,    14,     0,     0,     0,     0,
       0,     0,     0,     0,    15,    16,   258,   259,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   377,     0,     0,     0,     0,     0,     0,
     355,   258,   259,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
       0,     0,     0,     0,     0,   355,   258,   259,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   428,
     258,   259,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     352,   258,   259,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   354,   258,   259,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     363,   258,   259,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   364,
     258,   259,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   373,   258,
     259,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   452,   258,   259,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   457,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   258,   259,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205
};

static const yytype_int16 yycheck[] =
{
      57,    55,    82,   110,   144,   107,   173,   142,   179,   180,
       7,    64,     3,   134,     7,    75,     2,   106,     7,    37,
      37,    12,     3,   425,     3,     7,     7,     2,     7,   108,
     170,     2,    18,    79,    80,   137,   438,   106,   182,     0,
      38,    39,    40,    18,   113,    37,    27,    18,    92,    93,
      94,    95,   187,   107,    72,    72,   110,   159,   160,    11,
     227,   107,    11,   107,     3,    51,   173,   110,     7,     3,
     177,   125,    73,     7,    92,    93,    94,    95,    96,   139,
      72,    74,   108,   137,   251,   252,   112,     3,   142,   115,
       3,     7,   112,    27,     7,   115,   217,   151,   178,   188,
     189,   155,    94,    95,    96,   159,   160,   161,   162,   163,
     164,    27,    93,   111,   111,   106,   113,   206,   207,   173,
     227,   103,   103,   177,   103,   106,    11,   181,   182,    68,
      69,    11,   276,   187,   278,   279,    75,   110,   108,   283,
     284,   349,   112,   108,   251,   252,     7,   112,   134,    92,
      93,    94,    95,    87,    48,    49,   142,   211,   212,    93,
       6,   215,     8,     6,   103,     8,   109,   106,   221,   103,
      53,    87,   106,   227,   108,     7,   108,    93,   211,   212,
     112,     7,   215,     9,   355,     7,   357,   103,    11,     6,
     106,     8,   108,    50,    51,    52,    11,   251,   252,    37,
      79,    80,    50,    51,    52,   109,   377,   415,   416,   417,
     418,   109,    74,    75,    76,    77,    78,     3,   353,    94,
      95,    96,   276,   110,   278,   279,    77,    78,     7,   283,
     284,   217,    68,    69,    72,    97,    98,    37,   111,   383,
     384,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    94,    95,    92,    93,    94,    95,    96,   107,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   106,   446,
     420,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   353,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,   419,   101,   102,
     103,    40,   106,   106,    92,    93,    94,    95,    96,   383,
     384,    90,    91,    92,    93,    94,    95,    96,     7,   446,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,   413,   106,   141,   106,
     143,   106,   106,   146,   106,   419,   114,   110,   106,   106,
     110,   106,   106,   156,   157,   106,    44,   106,   114,    74,
     110,   461,   165,     7,    38,   113,   169,    39,     7,     7,
     108,    11,   446,   106,   111,     7,   179,   180,     3,     3,
     107,   113,   459,   107,   113,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,   222,
       3,     4,     5,   108,     7,   108,     9,    10,   107,   111,
      13,    14,    15,    16,    17,    18,    19,    20,    21,   107,
     107,    24,    25,    26,   247,    28,   107,   107,   107,   107,
      37,    34,    35,    36,    37,   258,   259,   106,    41,   262,
      43,     3,    45,    46,    80,   107,   109,    50,    51,    52,
       3,   107,    55,    56,    57,    58,   107,   111,   111,    86,
     107,   109,    86,   109,     7,    72,   109,   107,   107,    37,
      33,    54,    75,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,   106,   110,    92,    93,    94,    95,    96,
      93,   113,   111,   107,    18,   345,    99,   468,   261,   102,
     103,   185,   247,   106,    72,   180,    42,   110,   111,   216,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    -1,    -1,    92,    93,    94,    95,    96,    -1,
      -1,    -1,   355,    -1,   357,     3,     4,     5,     6,     7,
       8,     9,    10,   111,    -1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,   377,   378,    24,    25,    26,    -1,
      28,    -1,    -1,    -1,    37,    -1,    34,    35,    36,    37,
      -1,    -1,    -1,    41,    -1,    43,    -1,    45,    46,    -1,
      -1,    -1,    50,    51,    52,    -1,    -1,    55,    56,    57,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      -1,    -1,    -1,    -1,    -1,   428,    -1,    75,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    -1,    -1,    92,
      93,    94,    95,    96,    -1,    93,    -1,    -1,    -1,    -1,
      -1,    99,    -1,    -1,   102,   103,    -1,    -1,   106,     3,
       4,     5,   110,     7,    -1,     9,    10,    -1,    37,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
      24,    25,    26,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    -1,    -1,    37,    -1,    41,    -1,    43,
      -1,    45,    46,    72,    -1,    -1,    50,    51,    52,    -1,
      -1,    55,    56,    57,    58,    84,    85,    86,    87,    88,
      89,    -1,    -1,    92,    93,    94,    95,    96,    -1,    -1,
      72,    75,    -1,    -1,    -1,    -1,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    93,
      92,    93,    94,    95,    96,    99,    -1,    -1,   102,   103,
      -1,    -1,   106,    -1,   108,   107,   110,     3,     4,     5,
      -1,     7,    -1,     9,    10,    -1,    37,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    24,    25,
      26,    -1,    28,    -1,    -1,    37,    -1,    -1,    34,    35,
      36,    -1,    -1,    -1,    -1,    41,    -1,    43,    -1,    45,
      46,    72,    -1,    -1,    50,    51,    52,    -1,    -1,    55,
      56,    57,    58,    59,    -1,    86,    87,    88,    89,    -1,
      72,    92,    93,    94,    95,    96,    -1,    -1,    -1,    75,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      92,    93,    94,    95,    96,    -1,    -1,    93,    -1,    -1,
      -1,    -1,    -1,    99,    -1,    -1,   102,   103,    -1,    -1,
     106,     3,     4,     5,   110,     7,    -1,     9,    10,    -1,
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    24,    25,    26,    -1,    28,    -1,    37,    -1,
      -1,    -1,    34,    35,    36,    37,    -1,    -1,    -1,    41,
      -1,    43,    -1,    45,    46,    -1,    -1,    -1,    50,    51,
      52,    -1,    -1,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    83,    84,    85,    86,    87,    88,
      89,    -1,    -1,    92,    93,    94,    95,    96,    -1,    -1,
      -1,    93,    -1,    -1,    -1,    -1,    -1,    99,    -1,    -1,
     102,   103,    -1,    -1,   106,     3,     4,     5,   110,     7,
      -1,     9,    10,    -1,    -1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    24,    25,    26,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    -1,
      -1,    -1,    -1,    41,    -1,    43,    -1,    45,    46,    -1,
      -1,    -1,    50,    51,    52,    -1,    -1,    55,    56,    57,
      58,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    -1,    75,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    93,    -1,    -1,    -1,    -1,
      -1,    99,    -1,    -1,   102,   103,    -1,    -1,   106,     3,
       4,     5,   110,     7,    -1,     9,    10,    -1,    -1,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
      24,    25,    26,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    -1,    -1,    -1,    -1,    41,    -1,    43,
      -1,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    56,    57,    58,    -1,    -1,    -1,     3,    -1,
      -1,    -1,     7,    -1,     9,    -1,    -1,    -1,    13,    14,
      -1,    75,    -1,    -1,    -1,    -1,    21,    -1,    -1,    24,
      25,    26,    -1,    28,    -1,    -1,    -1,    -1,    -1,    93,
      -1,    -1,    -1,    -1,    -1,    99,    -1,    -1,   102,   103,
      45,    46,   106,    -1,    -1,    -1,   110,    -1,    -1,    -1,
      -1,    -1,    -1,     3,    -1,    -1,    -1,     7,    -1,     9,
      -1,    -1,    -1,    13,    14,    15,    -1,    -1,    -1,    -1,
      75,    21,    -1,    -1,    24,    25,    26,    -1,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,
      -1,    -1,    -1,    -1,    99,    45,    46,   102,   103,    -1,
      -1,   106,    -1,   108,    -1,    55,    56,    57,    58,    -1,
      -1,    -1,     3,    -1,    -1,    37,     7,    -1,     9,    -1,
      -1,    -1,    13,    14,    -1,    75,    -1,    -1,    -1,    -1,
      21,    -1,    -1,    24,    25,    26,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,
      -1,    -1,   102,   103,    45,    46,   106,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,   107,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    -1,
      -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,    -1,
      -1,   102,   103,    -1,    -1,   106,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,     6,    -1,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   107,    -1,    -1,    19,    20,
      -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    29,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,     6,
      -1,     8,    -1,    -1,    -1,    -1,    47,    48,    49,    50,
      51,    52,    19,    20,    -1,    22,    23,    -1,    -1,    -1,
      61,    62,    29,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    -1,    -1,    50,    51,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    62,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,    -1,    -1,    -1,    -1,    -1,    -1,
     113,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      -1,    -1,    -1,    -1,    -1,   113,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     109,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   109,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     107,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   107,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   117,   118,     0,    19,    20,    22,    23,    29,    31,
      37,    47,    50,    51,    52,    61,    62,   119,   120,   121,
     122,   126,   127,   129,   130,   131,   133,   137,   138,   139,
     145,   147,    11,    11,     7,   134,   108,   110,   141,   128,
      73,   185,   186,   121,    48,    49,   125,     6,     8,    11,
      11,   110,     7,     3,     7,   142,    53,   173,     7,   185,
       7,    74,   146,   148,   149,    11,    11,   145,   147,   150,
     135,   109,   109,     3,     4,     5,     7,     9,    10,    13,
      14,    15,    16,    17,    18,    21,    24,    25,    26,    28,
      34,    35,    36,    41,    43,    45,    46,    55,    56,    57,
      58,    75,    93,    99,   102,   103,   106,   110,   139,   140,
     143,   144,   147,   159,   160,   161,   163,   164,   165,   172,
     174,   176,   177,     3,   141,   110,   123,   132,     7,   152,
     153,   158,   152,     6,    37,   111,   106,    40,   166,   167,
     166,   108,   112,   108,   112,   115,   106,     7,   159,   174,
     106,   106,     7,     9,   171,   106,   106,   106,     7,   110,
     110,   106,   106,   106,   106,   106,   172,   172,   172,   106,
     114,   172,   176,   143,    37,   144,   169,   170,    74,    75,
      76,    77,    78,    97,    98,   114,   162,    44,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    79,    80,     3,    68,
      69,    75,   106,   159,   187,   188,   189,   106,   110,   108,
     112,   113,    74,   150,     7,   154,   108,   143,    38,   166,
      39,   172,     7,    59,   147,   163,   172,   160,     7,   172,
     178,   181,    77,    78,    11,     3,   159,   106,   159,   172,
     172,   143,   143,   159,   159,   159,   159,   172,    79,    80,
     172,   160,    37,   107,   107,   169,   111,    37,   144,   174,
     172,   180,   181,   180,     3,    27,    87,    93,   106,   108,
     159,   182,   183,    87,   108,   183,   161,   163,   172,   176,
     172,   176,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   176,
     172,   176,   187,   187,    37,    72,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    92,    93,    94,
      95,    96,   111,   187,   188,   150,   151,     7,   184,     3,
       3,   152,   108,   155,   172,   113,   107,     3,    12,   106,
     168,   169,   109,   112,   109,   113,   107,   113,   179,   107,
     107,   178,   107,   107,   107,   169,   169,   107,   107,   107,
     107,   172,   172,   107,   162,   172,   111,   106,   106,   183,
       3,   183,   183,   106,   113,   183,   183,   107,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   107,     7,   111,   113,
     109,     3,   154,   136,   168,    92,    93,    94,    95,   109,
     112,   115,   181,   181,   107,   107,   111,   111,   112,   181,
     172,    86,   107,   109,   183,   183,    86,   109,   124,   109,
     141,   107,   168,   168,   168,   168,   143,   160,     7,   173,
     172,   107,   107,   107,   173,    33,   169,   107,    54,   175,
     110,   106,   141,     6,     8,   156,   157,   174,   113,   111,
     107,   157
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
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
     167,   167,   168,   168,   168,   168,   168,   168,   168,   169,
     169,   170,   170,   171,   171,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   173,   173,   174,   174,
     175,   175,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   177,   177,   177,   177,   178,   178,   179,   179,   180,
     180,   181,   181,   182,   182,   182,   182,   183,   183,   183,
     183,   184,   184,   184,   185,   185,   185,   186,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   188,   188,   189,   189
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
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
       3,     6,     3,     3,     3,     3,     3,     1,     1,     0,
       1,     1,     2,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     2,     2,     2,     7,     6,
       4,     4,     5,     5,     1,     1,     1,     1,     1,     1,
       1,     4,     6,     6,     3,     3,     0,     2,     1,     1,
       0,     4,     1,     3,     3,     3,     3,     3,     3,     3,
       1,     4,     4,     4,     4,     0,     1,     0,     2,     1,
       4,     1,     3,     1,     4,     1,     2,     1,     3,     4,
       3,     1,     2,     2,     0,     1,     2,     5,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       1,     1,     2,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, globalSymTab, program); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, symTable** globalSymTab, stmnt** program)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (globalSymTab);
  YY_USE (program);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, symTable** globalSymTab, stmnt** program)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, globalSymTab, program);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, symTable** globalSymTab, stmnt** program)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], globalSymTab, program);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
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
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, symTable** globalSymTab, stmnt** program)
{
  YY_USE (yyvaluep);
  YY_USE (globalSymTab);
  YY_USE (program);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (symTable** globalSymTab, stmnt** program)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, globalSymTab);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* $@1: %empty  */
#line 146 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                  { *globalSymTab = new symTable("global"); symTable::addPredefinedSym(*globalSymTab); currentSymTab = *globalSymTab; }
#line 2194 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 4: /* program: units  */
#line 151 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { /*DBUG("REDUCE: units -> program\n")*/}
#line 2200 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 5: /* units: unit  */
#line 154 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { /*DBUG("REDUCE: unit -> units\n")*/ }
#line 2206 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 6: /* units: units unit  */
#line 155 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { /*DBUG("REDUCE: units unit -> units\n")*/ }
#line 2212 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 7: /* unit: proc  */
#line 158 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                        { /*DBUG("REDUCE: proc -> unit\n")*/ *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2218 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 8: /* unit: init  */
#line 159 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { /*DBUG("REDUCE: init -> unit\n")*/ *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2224 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 9: /* unit: events  */
#line 160 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { assert(false); std::cout << "The 'events' construct is currently not supported."; }
#line 2230 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 10: /* unit: one_decl  */
#line 161 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { 
													/*DBUG("REDUCE: one_decl -> unit\n")*/
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
#line 2248 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 11: /* unit: utypedef  */
#line 174 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { /*DBUG("REDUCE: utype -> unit\n")*/ *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2254 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 12: /* unit: mtypedef  */
#line 175 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { /*DBUG("REDUCE: mtype -> unit\n")*/ *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); }
#line 2260 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 13: /* unit: c_fcts  */
#line 176 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { std::cout << "Embedded C code is not supported."; 						}
#line 2266 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 14: /* unit: ns  */
#line 177 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { /*DBUG("REDUCE: ns -> unit\n")*/ *program = stmnt::merge(*program, (yyvsp[0].pStmntVal)); 	}
#line 2272 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 16: /* $@2: %empty  */
#line 184 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                                { 
													nameSpace = (yyvsp[0].sVal); savedSymTab = currentSymTab; 
													currentSymTab = currentSymTab->createSubTable(nameSpace); 
													auto predef = new pidSymNode(0, "_pid");
													predef->setMask(symbol::READ_ACCESS | symbol::PREDEFINED); 
													currentSymTab->insert(predef);
												}
#line 2284 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 17: /* $@3: %empty  */
#line 192 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                  { currentSymTab = savedSymTab; }
#line 2290 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 18: /* proc: inst proctype NAME $@2 '(' decl ')' $@3 Opt_priority Opt_enabler body  */
#line 195 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        {	
		  											/*DBUG("REDUCE: inst proctype NAME ( decl ) prio ena body -> proc\n")*/
													auto procNbLine = (yyvsp[0].pStmntVal)->getLineNb();
		  											procSymNode* proc = new procSymNode((yyvsp[-8].sVal), (yyvsp[-10].pConstExprVal), declSyms, (yyvsp[0].pStmntVal), procNbLine);
		  											declSyms.clear();
		  											(yyval.pStmntVal) = new procDecl(proc, procNbLine);
		  											(*globalSymTab)->insert(proc);
		  											nameSpace = "global";
		  											free((yyvsp[-8].sVal));
		  										}
#line 2305 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 19: /* proctype: PROCTYPE  */
#line 207 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { /*DBUG("REDUCE: -> PROCTYPE proctype\n")*/ }
#line 2311 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 20: /* proctype: D_PROCTYPE  */
#line 208 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "Deterministic proctypes are not supported (only useful for simulation)."; }
#line 2317 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 21: /* inst: %empty  */
#line 211 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { /*DBUG("REDUCE: void -> inst\n")*/ (yyval.pConstExprVal) = new exprConst(0, nbrLines); 	}
#line 2323 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 22: /* inst: ACTIVE  */
#line 212 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { /*DBUG("REDUCE: ACTIVE -> inst\n")*/ (yyval.pConstExprVal) = new exprConst(1, nbrLines); }
#line 2329 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 23: /* inst: ACTIVE '[' CONST ']'  */
#line 213 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { /*DBUG("REDUCE: ACTIVE [ CONST ] -> inst \n")*/ (yyval.pConstExprVal) = new exprConst((yyvsp[-1].iVal), nbrLines); }
#line 2335 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 24: /* inst: ACTIVE '[' NAME ']'  */
#line 214 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { 
													/*DBUG("REDUCE: ACTIVE [ NAME ] -> inst\n")*/
													varSymNode* var = *globalSymTab? static_cast<varSymNode*>((*globalSymTab)->lookup((yyvsp[-1].sVal))) : nullptr;
													if(var == nullptr) std::cout << "The variable "<<(yyvsp[-1].sVal)<<" does not exist.";
													else if(var->getType() != symbol::T_INT && var->getType() != symbol::T_BYTE && var->getType() != symbol::T_SHORT) std::cout << "The variable "<<(yyvsp[-1].sVal)<<" is not of type int, short or bit.";
													else if(var->getInitExpr() == nullptr || var->getInitExpr()->getType() != astNode::E_EXPR_CONST) std::cout << "The variable "<<(yyvsp[-1].sVal)<<" does not have a constant value.";
													else {
														(yyval.pConstExprVal) = new exprConst(static_cast<exprConst*>(var->getInitExpr())->getCstValue(), nbrLines);
													}
													free((yyvsp[-1].sVal));											
												}
#line 2351 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 25: /* $@4: %empty  */
#line 228 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                { nameSpace = "init"; }
#line 2357 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 26: /* init: INIT $@4 Opt_priority body  */
#line 230 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        {	
													/*DBUG("REDUCE: INIT Opt_priority body -> init\n")*/
													if(*globalSymTab && (*globalSymTab)->lookup("init") != nullptr) 
														std::cout << "This is the second init process; only one is allowed.";
													else {
														initSymNode* init = new initSymNode(nbrLines, (yyvsp[0].pStmntVal));
														(yyval.pStmntVal) = new initDecl(init, nbrLines);
														(*globalSymTab)->insert(init);
													}
													nameSpace = "global";
												}
#line 2373 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 27: /* events: TRACE body  */
#line 243 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "Event sequences (traces) are not supported."; }
#line 2379 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 28: /* utypedef: TYPEDEF NAME '{' decl_lst '}'  */
#line 246 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                        {	
													/*DBUG("REDUCE: TYPEDEF NAME '{' decl_lst '}' -> utype\n")*/
													tdefSymNode* tdef = new tdefSymNode((yyvsp[-3].sVal), *globalSymTab, declSyms, nbrLines);
													(yyval.pStmntVal) = new tdefDecl(tdef, nbrLines);
													(*globalSymTab)->insert(tdef);
													for(auto declSym : declSyms)
														(*globalSymTab)->remove(declSym->getName());
													declSyms.clear();
													free((yyvsp[-3].sVal));  
												}
#line 2394 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 29: /* $@5: %empty  */
#line 258 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        {	mtypeDef = new mtypedefSymNode(nbrLines);	}
#line 2400 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 30: /* mtypedef: vis TYPE asgn $@5 '{' nlst '}'  */
#line 259 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                {
													assert(mtypeDef->getMTypeList().size() != 0);
													(*globalSymTab)->insert(mtypeDef);

													/*DBUG("REDUCE: vis TYPE asgn { nlst } -> one_decl\n")*/
													if((yyvsp[-5].iType) != symbol::T_MTYPE) {
														std::cout <<  "This syntax only works for MTYPEs definition.";
														exit(1);
													}
													(yyval.pStmntVal) = new mtypeDecl(mtypeDef, nbrLines);
													// The mtype values are added in the nlst rule.
												}
#line 2417 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 31: /* $@6: %empty  */
#line 277 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                         { inInline = true; }
#line 2423 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 32: /* $@7: %empty  */
#line 278 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                       { nameSpace = (yyvsp[0].sVal); savedSymTab = currentSymTab; currentSymTab = currentSymTab->createSubTable(nameSpace); }
#line 2429 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 33: /* $@8: %empty  */
#line 280 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                  { for(std::string it : params) 
		  		currentSymTab->insert(varSymNode::createSymbol(symbol::T_NA, nbrLines, it));
		    currentSymTab = savedSymTab;
		  }
#line 2438 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 34: /* ns: INLINE $@6 NAME $@7 '(' param_list ')' $@8 body  */
#line 284 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        {
													/*DBUG("REDUCE: INLINE nm ( param_list ) body -> ns\n")*/
													auto sym = new inlineSymNode((yyvsp[-6].sVal), params, (yyvsp[0].pStmntVal), nbrLines);
													params.clear();
		  											(yyval.pStmntVal) = new inlineDecl(sym, nbrLines);
													(*globalSymTab)->insert(sym);
													inInline = false;
													free((yyvsp[-6].sVal));
												}
#line 2452 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 44: /* $@9: %empty  */
#line 312 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { 
													savedSymTab = currentSymTab; 
													if(!(currentSymTab = (*globalSymTab)->getSubSymTab(nameSpace)))
														currentSymTab = savedSymTab->createSubTable(nameSpace); 
													nameSpace = "";
												}
#line 2463 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 45: /* body: '{' $@9 sequence OS '}'  */
#line 319 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { /*DBUG("REDUCE: '{' sequence OS '}' -> body\n")*/ (yyval.pStmntVal) = (yyvsp[-2].pStmntVal); (yyval.pStmntVal)->setLocalSymTab(currentSymTab); currentSymTab->setBlock((yyvsp[-2].pStmntVal)); currentSymTab = savedSymTab; }
#line 2469 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 46: /* sequence: step  */
#line 322 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { /*DBUG("REDUCE: step -> sequence\n")*/ (yyval.pStmntVal) = (yyvsp[0].pStmntVal);  }
#line 2475 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 47: /* sequence: sequence MS step  */
#line 323 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { /*DBUG("REDUCE: sequence MS step -> sequence\n")*/ (yyval.pStmntVal) = stmnt::merge((yyvsp[-2].pStmntVal), (yyvsp[0].pStmntVal)); }
#line 2481 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 48: /* sequence: sequence step  */
#line 324 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { /*DBUG("REDUCE: sequence step -> sequence\n")*/ (yyval.pStmntVal) = stmnt::merge((yyvsp[-1].pStmntVal), (yyvsp[0].pStmntVal)); }
#line 2487 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 49: /* step: one_decl  */
#line 327 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { 
													assert(declSyms.front()->getType() != symbol::T_MTYPE_DEF); 
												 	(yyval.pStmntVal) = new varDecl(static_cast<std::list<varSymNode*>>(declSyms), nbrLines);
												 	declSyms.clear();
												}
#line 2497 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 50: /* step: NAME ':' one_decl  */
#line 332 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "Declarations with labels are not suported."; }
#line 2503 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 51: /* step: NAME ':' XU  */
#line 333 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "Channel assertions are currently not supported."; }
#line 2509 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 52: /* step: stmnt  */
#line 334 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { /*DBUG("REDUCE: stmnt -> step\n")*/ (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2515 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 53: /* step: stmnt UNLESS stmnt  */
#line 335 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "Unless statements are currently not supported."; }
#line 2521 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 55: /* vis: HIDDEN  */
#line 344 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { std::cout << "The 'hidden' keyword is not supported."; }
#line 2527 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 56: /* vis: SHOW  */
#line 345 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { std::cout << "The 'show' keyword is not supported."; }
#line 2533 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 57: /* vis: ISLOCAL  */
#line 346 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { std::cout << "The 'local' keyword is not supported."; }
#line 2539 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 60: /* $@10: %empty  */
#line 356 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                   { declType = (yyvsp[0].iType); }
#line 2545 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 61: /* one_decl: vis TYPE $@10 var_list  */
#line 356 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                { /*DBUG("REDUCE: vis TYPE var_list -> one_decl\n")*/ }
#line 2551 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 62: /* $@11: %empty  */
#line 357 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                            { declType = symbol::T_UTYPE; typeDef = *globalSymTab? static_cast<tdefSymNode*>((*globalSymTab)->lookup((yyvsp[0].sVal))) : nullptr; assert(typeDef); }
#line 2557 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 63: /* one_decl: vis UNAME $@11 var_list  */
#line 357 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                                                                                                                                        { /*DBUG("REDUCE: vis UNAME var_list -> one_decl\n")*/ free((yyvsp[-2].sVal)); }
#line 2563 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 64: /* decl_lst: one_decl  */
#line 360 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { /*DBUG("REDUCE: one_decl -> decl_list\n")*/ }
#line 2569 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 65: /* decl_lst: one_decl SEMI decl_lst  */
#line 361 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { /*DBUG("REDUCE: one_decl SEMI decl_list -> decl_lst\n")*/ }
#line 2575 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 66: /* decl: %empty  */
#line 365 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { /*DBUG("REDUCE: void -> decl\n")*/ }
#line 2581 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 67: /* decl: decl_lst  */
#line 366 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { /*DBUG("REDUCE: decl_list -> decl\n")*/ }
#line 2587 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 68: /* var_list: ivar  */
#line 373 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { /*DBUG("REDUCE: ivar -> var_list\n")*/ currentSymTab->insert((yyvsp[0].pVarSymVal)); declSyms.push_front((yyvsp[0].pVarSymVal)); }
#line 2593 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 69: /* var_list: ivar ',' var_list  */
#line 374 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { /*DBUG("REDUCE: ivar , var_list -> var_list\n")*/ currentSymTab->insert((yyvsp[-2].pVarSymVal)); declSyms.push_front((yyvsp[-2].pVarSymVal)); }
#line 2599 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 70: /* ivar: vardcl  */
#line 377 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { 
												  /*DBUG("REDUCE: var_decl -> ivar\n")*/ (yyval.pVarSymVal) = varSymNode::createSymbol(declType, nbrLines, (yyvsp[0].pDataVal).sVal, (yyvsp[0].pDataVal).iVal); 
												  if(declType == symbol::T_UTYPE) { assert(typeDef); static_cast<utypeSymNode*>((yyval.pVarSymVal))->setUType(typeDef); }
												  if((yyvsp[0].pDataVal).sVal) free((yyvsp[0].pDataVal).sVal);
												}
#line 2609 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 71: /* ivar: vardcl ASGN expr  */
#line 382 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { /*DBUG("REDUCE: var_decl ASGN expr -> ivar\n")*/ 
												  (yyval.pVarSymVal) = varSymNode::createSymbol(declType, nbrLines, (yyvsp[-2].pDataVal).sVal, (yyvsp[-2].pDataVal).iVal, (yyvsp[0].pExprVal)); 
												  if(declType == symbol::T_UTYPE) { assert(typeDef); static_cast<utypeSymNode*>((yyval.pVarSymVal))->setUType(typeDef); }
												  if((yyvsp[-2].pDataVal).sVal) free((yyvsp[-2].pDataVal).sVal);
												}
#line 2619 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 72: /* ivar: vardcl ASGN ch_init  */
#line 387 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { /*DBUG("REDUCE: var_decl ASGN ch_init -> ivar\n")*/ (yyval.pVarSymVal) = new chanSymNode(nbrLines, (yyvsp[-2].pDataVal).sVal, (yyvsp[-2].pDataVal).iVal, (yyvsp[0].pDataVal).iVal, typeLst);	
												  typeLst.clear(); if((yyvsp[-2].pDataVal).sVal) free((yyvsp[-2].pDataVal).sVal); //double free???if($3.sVal) free($3.sVal); 
												}
#line 2627 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 73: /* param_list: %empty  */
#line 392 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { }
#line 2633 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 74: /* param_list: NAME  */
#line 393 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { params.push_front(std::string((yyvsp[0].sVal))); free((yyvsp[0].sVal)); }
#line 2639 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 75: /* param_list: NAME ',' param_list  */
#line 394 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                            { params.push_front(std::string((yyvsp[-2].sVal))); free((yyvsp[-2].sVal)); }
#line 2645 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 76: /* ch_init: '[' CONST ']' OF '{' typ_list '}'  */
#line 398 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                        { /*DBUG("REDUCE: [ CONST ] OF { typ_list } -> ch_init\n")*/ (yyval.pDataVal).iVal = (yyvsp[-5].iVal); }
#line 2651 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 77: /* basetype: TYPE  */
#line 401 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pDataVal).sVal = nullptr; (yyval.pDataVal).iType = (yyvsp[0].iType); }
#line 2657 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 78: /* basetype: UNAME  */
#line 402 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pDataVal).sVal = (yyvsp[0].sVal); (yyval.pDataVal).iType = symbol::T_UTYPE; }
#line 2663 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 79: /* typ_list: basetype  */
#line 406 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                {	/*DBUG("REDUCE: basetype -> typ_list\n")*/
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
#line 2683 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 80: /* typ_list: basetype ',' typ_list  */
#line 421 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        {	/*DBUG("REDUCE: basetype , typ_list -> typ_list\n")*/
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
#line 2703 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 81: /* vardcl: NAME  */
#line 438 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { /*/*DBUG("REDUCE: NAME -> vardcl\n"*)*/ (yyval.pDataVal).sVal = (yyvsp[0].sVal); (yyval.pDataVal).iVal = 1; }
#line 2709 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 82: /* vardcl: NAME ':' CONST  */
#line 439 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "The 'unsigned' data type is not supported."; }
#line 2715 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 83: /* vardcl: NAME '[' CONST ']'  */
#line 440 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { /*DBUG("REDUCE: NAME [ CONST ] -> vardcl\n")*/ (yyval.pDataVal).sVal = (yyvsp[-3].sVal); (yyval.pDataVal).iVal = (yyvsp[-1].iVal); }
#line 2721 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 84: /* varref: cmpnd  */
#line 443 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { /*DBUG("REDUCE: cmpnd -> varref\n")*/ (yyval.pExprVarRefVal) = (yyvsp[0].pExprVarRefVal); symbol* sym = nullptr; if(!inInline) sym = (yyval.pExprVarRefVal)->resolve(currentSymTab); assert(sym || inInline); }
#line 2727 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 85: /* pfld: NAME  */
#line 446 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { /*DBUG("REDUCE: NAME -> pfld\n")*/ (yyval.pExprVarRefNameVal) = new exprVarRefName((yyvsp[0].sVal), nbrLines); free((yyvsp[0].sVal)); }
#line 2733 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 86: /* pfld: NAME '[' expr ']'  */
#line 447 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { /*DBUG("REDUCE: NAME [ expr ] -> pfld\n")*/ (yyval.pExprVarRefNameVal) = new exprVarRefName((yyvsp[-3].sVal), (yyvsp[-1].pExprVal), nbrLines); free((yyvsp[-3].sVal)); }
#line 2739 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 87: /* cmpnd: pfld sfld  */
#line 450 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { /*DBUG("REDUCE: pfld sfld -> cmpnd\n")*/ (yyval.pExprVarRefVal) = new exprVarRef(nbrLines, (yyvsp[-1].pExprVarRefNameVal), (yyvsp[0].pExprVarRefVal)); }
#line 2745 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 88: /* cmpnd: CONTEXT '.' pfld sfld  */
#line 451 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { /*DBUG("REDUCE: CONTEX . pfld sfld -> cmpnd\n")*/ (yyval.pExprVarRefVal) = new exprVarRef(nbrLines, (yyvsp[-1].pExprVarRefNameVal), (yyvsp[0].pExprVarRefVal)); }
#line 2751 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 89: /* sfld: %empty  */
#line 454 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { /*DBUG("REDUCE: void -> sfld\n")*/ (yyval.pExprVarRefVal) = nullptr; }
#line 2757 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 90: /* sfld: '.' cmpnd  */
#line 455 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { /*DBUG("REDUCE: . cmpnd -> sfld\n")*/ (yyval.pExprVarRefVal) = (yyvsp[0].pExprVarRefVal);   }
#line 2763 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 91: /* stmnt: Special  */
#line 459 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { /*DBUG("REDUCE: special -> stmnt\n")*/ (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2769 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 92: /* stmnt: Stmnt  */
#line 460 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { /*DBUG("REDUCE: Stmnt -> stmnt\n")*/ (yyval.pStmntVal) = (yyvsp[0].pStmntVal); }
#line 2775 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 93: /* Special: varref RCV rargs  */
#line 463 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pStmntVal) = new stmntChanRecv((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprRArgListVal), nbrLines); }
#line 2781 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 94: /* Special: varref SND margs  */
#line 464 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pStmntVal) = new stmntChanSnd((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprArgListVal), nbrLines); }
#line 2787 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 95: /* Special: IF options FI  */
#line 465 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pStmntVal) = new stmntIf((yyvsp[-1].pStmntOptVal), (yyvsp[-2].iVal)); }
#line 2793 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 96: /* Special: DO options OD  */
#line 466 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pStmntVal) = new stmntDo((yyvsp[-1].pStmntOptVal), (yyvsp[-2].iVal)); }
#line 2799 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 97: /* Special: BREAK  */
#line 467 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntBreak(nbrLines); }
#line 2805 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 98: /* Special: GOTO NAME  */
#line 468 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntGoto((yyvsp[0].sVal), nbrLines); free((yyvsp[0].sVal)); }
#line 2811 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 99: /* Special: NAME ':' stmnt  */
#line 469 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { if((yyvsp[0].pStmntVal)->getType() == astNode::E_STMNT_LABEL && static_cast<stmntLabel*>((yyvsp[0].pStmntVal))->getLabelled()->getType() == astNode::E_STMNT_LABEL) 
													std::cout << "Only two labels per state are supported."; 
												  (yyval.pStmntVal) = new stmntLabel((yyvsp[-2].sVal), (yyvsp[0].pStmntVal), nbrLines); free((yyvsp[-2].sVal)); }
#line 2819 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 100: /* Stmnt: varref ASGN full_expr  */
#line 473 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { (yyval.pStmntVal) = new stmntAsgn((yyvsp[-2].pExprVarRefVal), (yyvsp[0].pExprVal), nbrLines); }
#line 2825 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 101: /* Stmnt: varref INCR  */
#line 474 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pStmntVal) = new stmntIncr((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2831 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 102: /* Stmnt: varref DECR  */
#line 475 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pStmntVal) = new stmntDecr((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2837 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 103: /* Stmnt: PRINT '(' STRING prargs ')'  */
#line 476 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { (yyval.pStmntVal) = new stmntPrint((yyvsp[-2].sVal), (yyvsp[-1].pExprArgListVal), nbrLines); }
#line 2843 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 104: /* Stmnt: PRINTM '(' varref ')'  */
#line 477 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pStmntVal) = new stmntPrintm((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 2849 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 105: /* Stmnt: PRINTM '(' CONST ')'  */
#line 478 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pStmntVal) = new stmntPrintm((yyvsp[-1].iVal), nbrLines); }
#line 2855 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 106: /* Stmnt: ASSERT full_expr  */
#line 479 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pStmntVal) = new stmntAssert((yyvsp[0].pExprVal), nbrLines); }
#line 2861 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 107: /* Stmnt: ccode  */
#line 480 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { std::cout << "Embedded C code is not supported."; }
#line 2867 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 108: /* Stmnt: varref R_RCV rargs  */
#line 481 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "Sorted send and random receive are not supported."; }
#line 2873 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 109: /* Stmnt: varref RCV LT rargs GT  */
#line 482 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "Channel poll operations are not supported."; }
#line 2879 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 110: /* Stmnt: varref R_RCV LT rargs GT  */
#line 483 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "Channel poll operations are not supported."; }
#line 2885 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 111: /* Stmnt: varref O_SND margs  */
#line 484 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "Sorted send and random receive are not supported."; }
#line 2891 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 112: /* Stmnt: full_expr  */
#line 485 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntExpr((yyvsp[0].pExprVal), nbrLines); }
#line 2897 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 113: /* Stmnt: ELSE  */
#line 486 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pStmntVal) = new stmntElse(nbrLines); }
#line 2903 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 114: /* Stmnt: ATOMIC '{' sequence OS '}'  */
#line 487 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { (yyval.pStmntVal) = new stmntAtomic((yyvsp[-2].pStmntVal), nbrLines); }
#line 2909 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 115: /* Stmnt: D_STEP '{' sequence OS '}'  */
#line 488 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { (yyval.pStmntVal) = new stmntDStep((yyvsp[-2].pStmntVal), nbrLines); }
#line 2915 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 116: /* Stmnt: '{' sequence OS '}'  */
#line 489 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pStmntVal) = new stmntSeq((yyvsp[-2].pStmntVal), nbrLines); }
#line 2921 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 117: /* Stmnt: INAME '(' args ')'  */
#line 490 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
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
#line 2936 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 118: /* options: option  */
#line 502 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pStmntOptVal) = new stmntOpt((yyvsp[0].pStmntVal), nbrLines); }
#line 2942 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 119: /* options: option options  */
#line 503 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pStmntOptVal) = new stmntOpt((yyvsp[-1].pStmntVal), (yyvsp[0].pStmntOptVal), nbrLines); }
#line 2948 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 120: /* option: SEP sequence OS  */
#line 506 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pStmntVal) = (yyvsp[-1].pStmntVal); }
#line 2954 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 121: /* option: SEP '[' real_expr ']' sequence OS  */
#line 507 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { (yyval.pStmntVal) = (yyvsp[-1].pStmntVal); (yyvsp[-1].pStmntVal)->setProb((yyvsp[-3].rVal)); }
#line 2960 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 122: /* real_expr: '(' real_expr ')'  */
#line 511 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.rVal) = (yyvsp[-1].rVal); }
#line 2966 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 123: /* real_expr: real_expr '+' real_expr  */
#line 512 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.rVal) = (yyvsp[-2].rVal) + (yyvsp[0].rVal); }
#line 2972 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 124: /* real_expr: real_expr '-' real_expr  */
#line 513 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.rVal) = (yyvsp[-2].rVal) - (yyvsp[0].rVal); }
#line 2978 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 125: /* real_expr: real_expr '*' real_expr  */
#line 514 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                    { (yyval.rVal) = (yyvsp[-2].rVal) * (yyvsp[0].rVal); }
#line 2984 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 126: /* real_expr: real_expr '/' real_expr  */
#line 515 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                    { (yyval.rVal) = (yyvsp[-2].rVal) / (yyvsp[0].rVal); }
#line 2990 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 127: /* real_expr: REAL  */
#line 516 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                                        { (yyval.rVal) = (yyvsp[0].rVal);}
#line 2996 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 128: /* real_expr: CONST  */
#line 517 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                                        { (yyval.rVal) = (yyvsp[0].iVal);}
#line 3002 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 130: /* OS: SEMI  */
#line 521 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                        { /* redundant semi at end of sequence */ }
#line 3008 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 131: /* MS: SEMI  */
#line 524 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                        { /* at least one semi-colon */ }
#line 3014 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 132: /* MS: MS SEMI  */
#line 525 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                        { /* but more are okay too   */ }
#line 3020 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 133: /* aname: NAME  */
#line 528 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.sVal) = (yyvsp[0].sVal); }
#line 3026 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 134: /* aname: PNAME  */
#line 529 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.sVal) = (yyvsp[0].sVal); }
#line 3032 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 135: /* expr: '(' expr ')'  */
#line 532 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprVal) = new exprPar		((yyvsp[-1].pExprVal), nbrLines); }
#line 3038 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 136: /* expr: expr '+' expr  */
#line 533 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprPlus		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3044 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 137: /* expr: expr '-' expr  */
#line 534 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprMinus	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3050 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 138: /* expr: expr '*' expr  */
#line 535 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprTimes	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3056 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 139: /* expr: expr '/' expr  */
#line 536 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprDiv		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3062 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 140: /* expr: expr '%' expr  */
#line 537 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprMod		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3068 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 141: /* expr: expr '&' expr  */
#line 538 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3074 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 142: /* expr: expr '^' expr  */
#line 539 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwXor	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3080 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 143: /* expr: expr '|' expr  */
#line 540 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprBitwOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3086 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 144: /* expr: expr GT expr  */
#line 541 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprGT		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3092 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 145: /* expr: expr LT expr  */
#line 542 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprLT		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3098 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 146: /* expr: expr GE expr  */
#line 543 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprGE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3104 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 147: /* expr: expr LE expr  */
#line 544 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprLE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3110 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 148: /* expr: expr EQ expr  */
#line 545 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprEQ		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3116 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 149: /* expr: expr NE expr  */
#line 546 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprNE		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3122 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 150: /* expr: expr AND expr  */
#line 547 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3128 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 151: /* expr: expr OR expr  */
#line 548 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprOr		((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3134 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 152: /* expr: expr LSHIFT expr  */
#line 549 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprLShift	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3140 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 153: /* expr: expr RSHIFT expr  */
#line 550 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprRShift	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3146 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 154: /* expr: COUNT '(' expr ')'  */
#line 551 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprVal) = new exprCount	((yyvsp[-1].pExprVal), nbrLines); }
#line 3152 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 155: /* expr: '~' expr  */
#line 552 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprVal) = new exprBitwNeg	((yyvsp[0].pExprVal), nbrLines); }
#line 3158 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 156: /* expr: '-' expr  */
#line 553 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { 	if((yyvsp[0].pExprVal)->getType() != astNode::E_EXPR_CONST) 
														(yyval.pExprVal) = new exprUMin((yyvsp[0].pExprVal), nbrLines);
													else {
														exprConst* tmp = dynamic_cast<exprConst*>((yyvsp[0].pExprVal));
														(yyval.pExprVal) = new exprConst(- tmp->getCstValue(), nbrLines);
														delete tmp;
													}
												}
#line 3171 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 157: /* expr: SND expr  */
#line 561 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprVal) = new exprNeg	((yyvsp[0].pExprVal), nbrLines); }
#line 3177 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 158: /* expr: '(' expr SEMI expr ':' expr ')'  */
#line 562 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { (yyval.pExprVal) = new exprCond	((yyvsp[-5].pExprVal), (yyvsp[-3].pExprVal), (yyvsp[-1].pExprVal), nbrLines); }
#line 3183 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 159: /* expr: RUN aname '(' args ')' Opt_priority  */
#line 563 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                        { auto run = new exprRun ((yyvsp[-4].sVal), (yyvsp[-2].pExprArgListVal), nbrLines);
												  (yyval.pExprVal) = run;
												  auto procSym = run->resolve(*globalSymTab); 
												  assert(procSym); free((yyvsp[-4].sVal)); 
												}
#line 3193 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 160: /* expr: LEN '(' varref ')'  */
#line 568 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprVal) = new exprLen	((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3199 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 161: /* expr: ENABLED '(' expr ')'  */
#line 569 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "The enabled keyword is not supported."; }
#line 3205 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 162: /* expr: varref RCV '[' rargs ']'  */
#line 570 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "Construct not supported."; /* Unclear */ }
#line 3211 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 163: /* expr: varref R_RCV '[' rargs ']'  */
#line 571 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { std::cout << "Sorted send and random receive are not supported."; }
#line 3217 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 164: /* expr: varref  */
#line 572 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprVal) = new exprVar	((yyvsp[0].pExprVarRefVal), nbrLines); }
#line 3223 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 165: /* expr: cexpr  */
#line 573 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { std::cout << "Embedded C code is not supported."; }
#line 3229 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 166: /* expr: CONST  */
#line 574 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprVal) = new exprConst((yyvsp[0].iVal), nbrLines); }
#line 3235 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 167: /* expr: TRUE  */
#line 575 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprVal) = new exprTrue	(nbrLines); }
#line 3241 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 168: /* expr: FALSE  */
#line 576 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprVal) = new exprFalse(nbrLines); }
#line 3247 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 169: /* expr: TIMEOUT  */
#line 577 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprVal) = new exprTimeout(nbrLines); }
#line 3253 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 170: /* expr: NONPROGRESS  */
#line 578 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "The 'np_' variable is not supported."; }
#line 3259 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 171: /* expr: PC_VAL '(' expr ')'  */
#line 579 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { std::cout << "The 'pc_value()' construct is not supported."; }
#line 3265 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 172: /* expr: PNAME '[' expr ']' '@' NAME  */
#line 580 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 3271 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 173: /* expr: PNAME '[' expr ']' ':' pfld  */
#line 581 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 3277 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 174: /* expr: PNAME '@' NAME  */
#line 582 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 3283 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 175: /* expr: PNAME ':' pfld  */
#line 583 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { std::cout << "Construct not supported."; /* Unclear */ }
#line 3289 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 177: /* Opt_priority: PRIORITY CONST  */
#line 587 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { assert(false); std::cout << "The 'priority' construct is related to simulation and not supported."; }
#line 3295 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 178: /* full_expr: expr  */
#line 590 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 3301 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 179: /* full_expr: Expr  */
#line 591 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 3307 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 181: /* Opt_enabler: PROVIDED '(' full_expr ')'  */
#line 595 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { assert(false); std::cout << "The 'provided' construct is currently not supported."; }
#line 3313 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 182: /* Expr: Probe  */
#line 600 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = (yyvsp[0].pExprVal); }
#line 3319 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 183: /* Expr: '(' Expr ')'  */
#line 601 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprPar	((yyvsp[-1].pExprVal), nbrLines); }
#line 3325 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 184: /* Expr: Expr AND Expr  */
#line 602 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3331 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 185: /* Expr: Expr AND expr  */
#line 603 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3337 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 186: /* Expr: Expr OR Expr  */
#line 604 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3343 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 187: /* Expr: Expr OR expr  */
#line 605 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3349 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 188: /* Expr: expr AND Expr  */
#line 606 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprAnd	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3355 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 189: /* Expr: expr OR Expr  */
#line 607 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprVal) = new exprOr	((yyvsp[-2].pExprVal), (yyvsp[0].pExprVal), nbrLines); }
#line 3361 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 190: /* Expr: SKIP  */
#line 608 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprVal) = new exprSkip	(nbrLines); }
#line 3367 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 191: /* Probe: FULL '(' varref ')'  */
#line 611 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { (yyval.pExprVal) = new exprFull	((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3373 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 192: /* Probe: NFULL '(' varref ')'  */
#line 612 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprVal) = new exprNFull((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3379 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 193: /* Probe: EMPTY '(' varref ')'  */
#line 613 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprVal) = new exprEmpty((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3385 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 194: /* Probe: NEMPTY '(' varref ')'  */
#line 614 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprVal) = new exprNEmpty((yyvsp[-1].pExprVarRefVal), nbrLines); }
#line 3391 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 195: /* args: %empty  */
#line 618 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                { (yyval.pExprArgListVal) = nullptr; }
#line 3397 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 196: /* args: arg  */
#line 619 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3403 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 197: /* prargs: %empty  */
#line 623 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprArgListVal) = nullptr; }
#line 3409 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 198: /* prargs: ',' arg  */
#line 624 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3415 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 199: /* margs: arg  */
#line 628 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprArgListVal) = (yyvsp[0].pExprArgListVal); }
#line 3421 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 200: /* margs: expr '(' arg ')'  */
#line 629 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { assert(false); }
#line 3427 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 201: /* arg: expr  */
#line 632 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList(new exprArg((yyvsp[0].pExprVal), nbrLines), nbrLines); }
#line 3433 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 202: /* arg: expr ',' arg  */
#line 633 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprArgListVal) = new exprArgList(new exprArg((yyvsp[-2].pExprVal), nbrLines), (yyvsp[0].pExprArgListVal), nbrLines); }
#line 3439 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 203: /* rarg: varref  */
#line 636 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprRArgVal) = new exprRArgVar((yyvsp[0].pExprVarRefVal), nbrLines); }
#line 3445 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 204: /* rarg: EVAL '(' expr ')'  */
#line 637 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprRArgVal) = new exprRArgEval((yyvsp[-1].pExprVal), nbrLines); }
#line 3451 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 205: /* rarg: CONST  */
#line 638 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { (yyval.pExprRArgVal) = new exprRArgConst(new exprConst((yyvsp[0].iVal), nbrLines), nbrLines); }
#line 3457 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 206: /* rarg: '-' CONST  */
#line 639 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprRArgVal) = new exprRArgConst(new exprConst(-(yyvsp[0].iVal), nbrLines), nbrLines); }
#line 3463 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 207: /* rargs: rarg  */
#line 643 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprRArgListVal) = new exprRArgList((yyvsp[0].pExprRArgVal), nbrLines); }
#line 3469 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 208: /* rargs: rarg ',' rargs  */
#line 644 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprRArgListVal) = new exprRArgList((yyvsp[-2].pExprRArgVal), (yyvsp[0].pExprRArgListVal), nbrLines); }
#line 3475 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 209: /* rargs: rarg '(' rargs ')'  */
#line 645 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                        { (yyval.pExprRArgListVal) = new exprRArgList((yyvsp[-3].pExprRArgVal), (yyvsp[-1].pExprRArgListVal), nbrLines); }
#line 3481 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 210: /* rargs: '(' rargs ')'  */
#line 646 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { (yyval.pExprRArgListVal) = (yyvsp[-1].pExprRArgListVal); }
#line 3487 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 211: /* nlst: NAME  */
#line 649 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                { /*DBUG("REDUCE: NAME -> nlst\n")*/ cmtypeSymNode* sym = new cmtypeSymNode(nbrLines, mtypeDef, (yyvsp[0].sVal), mtypeId++); (*globalSymTab)->insert(sym); free((yyvsp[0].sVal)); }
#line 3493 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 212: /* nlst: nlst NAME  */
#line 650 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                                        { /*DBUG("REDUCE: nlst NAME -> NAME\n")*/ cmtypeSymNode* sym = new cmtypeSymNode(nbrLines, mtypeDef, (yyvsp[0].sVal), mtypeId++); (*globalSymTab)->insert(sym); free((yyvsp[0].sVal)); }
#line 3499 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;

  case 213: /* nlst: nlst ','  */
#line 651 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"
                                                                { /*DBUG("REDUCE: nlst , -> nlst\n")*/ }
#line 3505 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"
    break;


#line 3509 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/y.tab.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (globalSymTab, program, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, globalSymTab, program);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (globalSymTab, program, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, globalSymTab, program);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 696 "/home/slazreg/Work/Research/Mutation/mutantgenerator/parser/promela.y"

