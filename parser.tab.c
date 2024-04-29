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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#define YYPARSER
#define YYDEBUG 1
#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parser.h"
#include "util.h"

static int yylex();
void yyerror(char* msg);

TreeNode* parse(void);

#define YYSTYPE TreeNode*
static TreeNode* raiz;  // raiza da árvore sintatica





#line 93 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_VOID = 3,                       /* VOID  */
  YYSYMBOL_INT = 4,                        /* INT  */
  YYSYMBOL_IF = 5,                         /* IF  */
  YYSYMBOL_WHILE = 6,                      /* WHILE  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_SOMA = 9,                       /* SOMA  */
  YYSYMBOL_SUB = 10,                       /* SUB  */
  YYSYMBOL_MUL = 11,                       /* MUL  */
  YYSYMBOL_DIV = 12,                       /* DIV  */
  YYSYMBOL_APR = 13,                       /* APR  */
  YYSYMBOL_FPR = 14,                       /* FPR  */
  YYSYMBOL_NUM = 15,                       /* NUM  */
  YYSYMBOL_ESP = 16,                       /* ESP  */
  YYSYMBOL_ID = 17,                        /* ID  */
  YYSYMBOL_ACOL = 18,                      /* ACOL  */
  YYSYMBOL_FCOL = 19,                      /* FCOL  */
  YYSYMBOL_ACH = 20,                       /* ACH  */
  YYSYMBOL_FCH = 21,                       /* FCH  */
  YYSYMBOL_ATRIB = 22,                     /* ATRIB  */
  YYSYMBOL_IGL = 23,                       /* IGL  */
  YYSYMBOL_DIF = 24,                       /* DIF  */
  YYSYMBOL_MAIGL = 25,                     /* MAIGL  */
  YYSYMBOL_MEIGL = 26,                     /* MEIGL  */
  YYSYMBOL_MAI = 27,                       /* MAI  */
  YYSYMBOL_MEN = 28,                       /* MEN  */
  YYSYMBOL_VIRG = 29,                      /* VIRG  */
  YYSYMBOL_PV = 30,                        /* PV  */
  YYSYMBOL_NL = 31,                        /* NL  */
  YYSYMBOL_ERRO = 32,                      /* ERRO  */
  YYSYMBOL_FIM = 33,                       /* FIM  */
  YYSYMBOL_YYACCEPT = 34,                  /* $accept  */
  YYSYMBOL_programa = 35,                  /* programa  */
  YYSYMBOL_declaracao_lista = 36,          /* declaracao_lista  */
  YYSYMBOL_declaracao = 37,                /* declaracao  */
  YYSYMBOL_var_declaracao = 38,            /* var_declaracao  */
  YYSYMBOL_vet_num = 39,                   /* vet_num  */
  YYSYMBOL_fun_declaracao = 40,            /* fun_declaracao  */
  YYSYMBOL_tipo_especificador = 41,        /* tipo_especificador  */
  YYSYMBOL_params = 42,                    /* params  */
  YYSYMBOL_param_lista = 43,               /* param_lista  */
  YYSYMBOL_param = 44,                     /* param  */
  YYSYMBOL_composto_decl = 45,             /* composto_decl  */
  YYSYMBOL_local_declaracoes = 46,         /* local_declaracoes  */
  YYSYMBOL_statement_lista = 47,           /* statement_lista  */
  YYSYMBOL_statement = 48,                 /* statement  */
  YYSYMBOL_expressao_decl = 49,            /* expressao_decl  */
  YYSYMBOL_selecao_decl = 50,              /* selecao_decl  */
  YYSYMBOL_iteracao_decl = 51,             /* iteracao_decl  */
  YYSYMBOL_retorno_decl = 52,              /* retorno_decl  */
  YYSYMBOL_expressao = 53,                 /* expressao  */
  YYSYMBOL_var = 54,                       /* var  */
  YYSYMBOL_simples_expressao = 55,         /* simples_expressao  */
  YYSYMBOL_relacional = 56,                /* relacional  */
  YYSYMBOL_soma_expressao = 57,            /* soma_expressao  */
  YYSYMBOL_soma = 58,                      /* soma  */
  YYSYMBOL_termo = 59,                     /* termo  */
  YYSYMBOL_mult = 60,                      /* mult  */
  YYSYMBOL_fator = 61,                     /* fator  */
  YYSYMBOL_ativacao = 62,                  /* ativacao  */
  YYSYMBOL_args = 63,                      /* args  */
  YYSYMBOL_arg_lista = 64,                 /* arg_lista  */
  YYSYMBOL_id = 65                         /* id  */
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
typedef yytype_int8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   102

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  105

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   288


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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    31,    31,    33,    45,    49,    52,    56,    64,    74,
      80,    94,    98,   103,   106,   111,   123,   127,   134,   142,
     155,   167,   171,   183,   185,   188,   191,   194,   197,   201,
     205,   209,   213,   220,   226,   229,   234,   239,   243,   248,
     255,   261,   265,   269,   273,   277,   281,   285,   290,   295,
     299,   304,   310,   317,   323,   328,   334,   334,   334,   335,
     341,   349,   355,   357,   368,   372
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "VOID", "INT", "IF",
  "WHILE", "ELSE", "RETURN", "SOMA", "SUB", "MUL", "DIV", "APR", "FPR",
  "NUM", "ESP", "ID", "ACOL", "FCOL", "ACH", "FCH", "ATRIB", "IGL", "DIF",
  "MAIGL", "MEIGL", "MAI", "MEN", "VIRG", "PV", "NL", "ERRO", "FIM",
  "$accept", "programa", "declaracao_lista", "declaracao",
  "var_declaracao", "vet_num", "fun_declaracao", "tipo_especificador",
  "params", "param_lista", "param", "composto_decl", "local_declaracoes",
  "statement_lista", "statement", "expressao_decl", "selecao_decl",
  "iteracao_decl", "retorno_decl", "expressao", "var", "simples_expressao",
  "relacional", "soma_expressao", "soma", "termo", "mult", "fator",
  "ativacao", "args", "arg_lista", "id", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-44)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-15)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      51,   -44,   -44,     4,    51,   -44,   -44,   -44,    -7,   -44,
     -44,   -44,    20,    53,    -3,   -44,    13,    -7,    16,     3,
     -44,   -44,    17,    25,    31,    51,    15,    56,   -44,   -44,
     -44,   -44,   -44,    51,   -44,    -7,     1,   -13,    60,    70,
      11,    57,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,
     -44,    55,    62,   -44,    38,    67,   -44,   -44,    -5,    57,
      57,   -44,    58,    73,   -44,    57,   -44,   -44,   -44,   -44,
     -44,   -44,   -44,   -44,    57,    57,   -44,   -44,    57,    54,
      57,    75,    76,   -44,   -44,   -44,   -44,    72,    67,   -44,
     -44,   -44,    77,    63,    74,    29,    29,   -44,    57,   -44,
      79,   -44,   -44,    29,   -44
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    12,    11,     0,     2,     4,     5,     6,     0,     1,
       3,    65,     0,     0,     0,     7,    12,     0,     0,    13,
      16,     9,     0,    17,     0,     0,     0,     0,    21,    10,
      15,     8,    18,    23,    20,     0,     0,     0,     0,     0,
       0,     0,    59,    19,    30,    25,    22,    24,    26,    27,
      28,     0,    57,    37,    41,    49,    53,    58,    38,     0,
       0,    34,     0,     0,    29,     0,    50,    51,    46,    47,
      45,    42,    44,    43,     0,     0,    54,    55,     0,     0,
       0,     0,     0,    35,    56,    36,    57,    40,    48,    52,
      61,    64,     0,    62,     0,     0,     0,    60,     0,    39,
      31,    33,    63,     0,    32
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -44,   -44,   -44,    90,    64,   -44,   -44,   -10,   -44,   -44,
      71,    78,   -44,   -44,   -43,   -44,   -44,   -44,   -44,   -40,
       2,   -44,   -44,    21,   -44,    23,   -44,    22,   -44,   -44,
     -44,    -6
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,     6,    22,     7,     8,    18,    19,
      20,    45,    33,    36,    46,    47,    48,    49,    50,    51,
      52,    53,    74,    54,    75,    55,    78,    56,    57,    92,
      93,    58
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      62,    63,    12,    17,     9,    14,    38,    39,    79,    40,
      11,    23,    21,    80,    41,    17,    42,    15,    11,    81,
      82,    28,    43,    35,    41,    85,    42,   -14,    11,    37,
      24,    44,    25,    13,    38,    39,    26,    40,    14,    91,
      94,    61,    41,    27,    42,    31,    11,    66,    67,    28,
      15,    28,   100,   101,     1,     2,    16,     2,   102,    44,
     104,    68,    69,    70,    71,    72,    73,    41,    90,    42,
      41,    11,    42,    59,    11,    32,    86,    86,    76,    77,
      86,    66,    67,    60,    65,    64,   103,    84,    83,    95,
      96,    97,    98,    99,    10,    87,    30,    34,    88,     0,
      89,     0,    29
};

static const yytype_int8 yycheck[] =
{
      40,    41,     8,    13,     0,    18,     5,     6,    13,     8,
      17,    17,    15,    18,    13,    25,    15,    30,    17,    59,
      60,    20,    21,    33,    13,    65,    15,    14,    17,    35,
      14,    30,    29,    13,     5,     6,    19,     8,    18,    79,
      80,    30,    13,    18,    15,    30,    17,     9,    10,    20,
      30,    20,    95,    96,     3,     4,     3,     4,    98,    30,
     103,    23,    24,    25,    26,    27,    28,    13,    14,    15,
      13,    17,    15,    13,    17,    19,    74,    75,    11,    12,
      78,     9,    10,    13,    22,    30,     7,    14,    30,    14,
      14,    14,    29,    19,     4,    74,    25,    33,    75,    -1,
      78,    -1,    24
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,    35,    36,    37,    38,    40,    41,     0,
      37,    17,    65,    13,    18,    30,     3,    41,    42,    43,
      44,    15,    39,    65,    14,    29,    19,    18,    20,    45,
      44,    30,    19,    46,    38,    41,    47,    65,     5,     6,
       8,    13,    15,    21,    30,    45,    48,    49,    50,    51,
      52,    53,    54,    55,    57,    59,    61,    62,    65,    13,
      13,    30,    53,    53,    30,    22,     9,    10,    23,    24,
      25,    26,    27,    28,    56,    58,    11,    12,    60,    13,
      18,    53,    53,    30,    14,    53,    54,    57,    59,    61,
      14,    53,    63,    64,    53,    14,    14,    14,    29,    19,
      48,    48,    53,     7,    48
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    34,    35,    36,    36,    37,    37,    38,    38,    39,
      40,    41,    41,    42,    42,    43,    43,    44,    44,    45,
      46,    46,    47,    47,    48,    48,    48,    48,    48,    49,
      49,    50,    50,    51,    52,    52,    53,    53,    54,    54,
      55,    55,    56,    56,    56,    56,    56,    56,    57,    57,
      58,    58,    59,    59,    60,    60,    61,    61,    61,    61,
      62,    62,    63,    64,    64,    65
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     1,
       6,     1,     1,     1,     1,     3,     1,     2,     4,     4,
       2,     0,     2,     0,     1,     1,     1,     1,     1,     2,
       1,     5,     7,     5,     2,     3,     3,     1,     1,     4,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       4,     3,     1,     3,     1,     1
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
        yyerror (YY_("syntax error: cannot back up")); \
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
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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
      yychar = yylex ();
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
  case 2: /* programa: declaracao_lista  */
#line 31 "parser.y"
                            { raiz = yyvsp[0];}
#line 1217 "parser.tab.c"
    break;

  case 3: /* declaracao_lista: declaracao_lista declaracao  */
#line 34 "parser.y"
{
    YYSTYPE t = yyvsp[-1];
    if(t != NULL){
        while(t->irmao != NULL){    //gera n declarações, que serão todos irmão, o primeiro no é quando declaração_lista deriva em declaração
            t = t->irmao;
        }

        t->irmao  = yyvsp[0];
        yyval = yyvsp[-1];
    } // pode dar erro
}
#line 1233 "parser.tab.c"
    break;

  case 4: /* declaracao_lista: declaracao  */
#line 45 "parser.y"
                 {
        yyval = yyvsp[0];    //primeira declaração, que será a raiz
    }
#line 1241 "parser.tab.c"
    break;

  case 5: /* declaracao: var_declaracao  */
#line 49 "parser.y"
                           {
    yyval = yyvsp[0];
}
#line 1249 "parser.tab.c"
    break;

  case 6: /* declaracao: fun_declaracao  */
#line 52 "parser.y"
                      { // so passa a o no pra cima
        yyval = yyvsp[0];
    }
#line 1257 "parser.tab.c"
    break;

  case 7: /* var_declaracao: tipo_especificador id PV  */
#line 56 "parser.y"
                                        {   // como tem nos folha, aloca-se nos
    yyval = yyvsp[-2];
    yyval->filho[0] = newStmtNode(VarK);
    yyval->filho[0]->type = yyval->type;
    yyval->filho[0]->attr.nome = copyString(yyvsp[-1]->attr.nome);    //para declaração de variaveis globais
    yyval->filho[0]->lineno = yyvsp[-1]->lineno;
    yyval->filho[0]->escopo = copyString("global");
}
#line 1270 "parser.tab.c"
    break;

  case 8: /* var_declaracao: tipo_especificador id ACOL vet_num FCOL PV  */
#line 64 "parser.y"
                                                  {
        yyval = yyvsp[-5];
        yyval->filho[0] = newStmtNode(VetK);
        yyval->filho[0]->type = yyval->type;
        yyval->filho[0]->attr.nome = copyString(yyvsp[-4]->attr.nome); //mesma coisa so que com vetores
        yyval->filho[0]->lineno = yyvsp[-4]->lineno;
        yyval->filho[0]->escopo = copyString("global");
        yyval->filho[0]->filho[0] = yyvsp[-2];    // o filho do vetor é o numero de elementos
}
#line 1284 "parser.tab.c"
    break;

  case 9: /* vet_num: NUM  */
#line 74 "parser.y"
            {
    yyval = newExpNode(ConstK);
    yyval->attr.val = atoi(tokenString);   //cria o no folha para nums
    yyval->type = Integer; 
}
#line 1294 "parser.tab.c"
    break;

  case 10: /* fun_declaracao: tipo_especificador id APR params FPR composto_decl  */
#line 80 "parser.y"
                                                                  {
    yyval = yyvsp[-5];
    yyval->filho[0] = newStmtNode(FuncaoK);
    yyval->filho[0]->type = yyval->type;
    yyval->filho[0]->filho[0] = yyvsp[-2];
    yyval->filho[0]->filho[1] = yyvsp[0];
    yyval->filho[0]->attr.nome = copyString(yyvsp[-4]->attr.nome);
    yyval->filho[0]->lineno = yyvsp[-4]->lineno;
    yyval->filho[0]->escopo = copyString("global");    // note que todo escopo é global até estar dentro de uma função
    yyval->filho[0]->filho[1] = yyvsp[0];    //  função tem 2 filhos parametros e o que ela faz
    insereEscopo(yyval->filho[0]->filho[0],yyvsp[-4]->attr.nome); // o escopo ddas variaveis a baixo da declaração de função são o nome da propria
    insereEscopo(yyval->filho[0]->filho[1],yyvsp[-4]->attr.nome);
}
#line 1312 "parser.tab.c"
    break;

  case 11: /* tipo_especificador: INT  */
#line 94 "parser.y"
                        {
    yyval = newExpNode(TypeK);
    yyval->type = Integer;
}
#line 1321 "parser.tab.c"
    break;

  case 12: /* tipo_especificador: VOID  */
#line 98 "parser.y"
             {
        yyval = newExpNode(TypeK);
        yyval->type = Void;
    }
#line 1330 "parser.tab.c"
    break;

  case 13: /* params: param_lista  */
#line 103 "parser.y"
                   {
    yyval = yyvsp[0];
}
#line 1338 "parser.tab.c"
    break;

  case 14: /* params: VOID  */
#line 106 "parser.y"
             {
        yyval = newExpNode(ConstK); // o parametro é void, então cria-se um no do tipo void
        yyval->type = Void;    //pode dar erro
    }
#line 1347 "parser.tab.c"
    break;

  case 15: /* param_lista: param_lista VIRG param  */
#line 111 "parser.y"
                                    {

                
                YYSTYPE t = yyvsp[-2];
                if(t != NULL){      // verifica se a lista de parametros não é vazia
                    while(t->irmao != NULL){
                        t = t->irmao;   //vai adicionando os parametros ao final da lista de irmaos
                    }
                    t->irmao = yyvsp[0];  //adiciona o parametro
                    yyval = yyvsp[-2];
                }   //pode dar erro
}
#line 1364 "parser.tab.c"
    break;

  case 16: /* param_lista: param  */
#line 123 "parser.y"
              {
        yyval = yyvsp[0];     //primeiro parametro a ser adicionado
    }
#line 1372 "parser.tab.c"
    break;

  case 17: /* param: tipo_especificador id  */
#line 127 "parser.y"
                             {
    yyval = yyvsp[-1];
    yyval->filho[0] = newStmtNode(VarK);   // o filho do tipo da variavel é a variavel
    yyval->filho[0]->type = yyval->type;
    yyval->filho[0]->attr.nome = copyString(yyvsp[0]->attr.nome);
    yyval->filho[0]->lineno = yyvsp[0]->lineno;
}
#line 1384 "parser.tab.c"
    break;

  case 18: /* param: tipo_especificador id ACOL FCOL  */
#line 134 "parser.y"
                                      {
        yyval = yyvsp[-3];
        yyval->filho[0] = newStmtNode(VetK);   //mesma coisa so que para listas
        yyval->filho[0]->type = yyval->type;
        yyval->filho[0]->attr.nome = copyString(yyvsp[-2]->attr.nome);
        yyval->filho[0]->lineno = yyvsp[-2]->lineno;
}
#line 1396 "parser.tab.c"
    break;

  case 19: /* composto_decl: ACH local_declaracoes statement_lista FCH  */
#line 142 "parser.y"
                                                         {
        YYSTYPE t = yyvsp[-2];
        if(t != NULL){
            while(t->irmao != NULL){
                t = t->irmao;
            }
            t->irmao = yyvsp[-1];//o primeiro no de statement vai ficar no final da fila de irmaos
            yyval = yyvsp[-2];
        }else{
            yyval = yyvsp[-1];    //  caso não tenha declarações locais
        }
}
#line 1413 "parser.tab.c"
    break;

  case 20: /* local_declaracoes: local_declaracoes var_declaracao  */
#line 155 "parser.y"
                                                    {
    YYSTYPE t = yyvsp[-1];
    if(t != NULL){
        while(t->irmao != NULL){
            t = t->irmao;
        }
        t->irmao = yyvsp[0];
        yyval = yyvsp[-1];
    }else{
        yyval = yyvsp[0];
    }
}
#line 1430 "parser.tab.c"
    break;

  case 21: /* local_declaracoes: %empty  */
#line 167 "parser.y"
            {
        yyval = NULL;
    }
#line 1438 "parser.tab.c"
    break;

  case 22: /* statement_lista: statement_lista statement  */
#line 171 "parser.y"
                                           {

    YYSTYPE t = yyvsp[-1];
    if(t != NULL){
        while(t->irmao != NULL){
            t = t->irmao;
        }
        t->irmao = yyvsp[0];
    }else{
        yyval = yyvsp[0];
    }

}
#line 1456 "parser.tab.c"
    break;

  case 23: /* statement_lista: %empty  */
#line 183 "parser.y"
          {yyval = NULL;}
#line 1462 "parser.tab.c"
    break;

  case 24: /* statement: expressao_decl  */
#line 185 "parser.y"
                          {
    yyval = yyvsp[0];
    }
#line 1470 "parser.tab.c"
    break;

  case 25: /* statement: composto_decl  */
#line 188 "parser.y"
                     {
        yyval = yyvsp[0];
    }
#line 1478 "parser.tab.c"
    break;

  case 26: /* statement: selecao_decl  */
#line 191 "parser.y"
                    {
        yyval = yyvsp[0];
    }
#line 1486 "parser.tab.c"
    break;

  case 27: /* statement: iteracao_decl  */
#line 194 "parser.y"
                     {
        yyval = yyvsp[0];
    }
#line 1494 "parser.tab.c"
    break;

  case 28: /* statement: retorno_decl  */
#line 197 "parser.y"
                    {
        yyval = yyvsp[0];
    }
#line 1502 "parser.tab.c"
    break;

  case 29: /* expressao_decl: expressao PV  */
#line 201 "parser.y"
                             {

    yyval = yyvsp[-1];
    }
#line 1511 "parser.tab.c"
    break;

  case 30: /* expressao_decl: PV  */
#line 205 "parser.y"
         {
        yyval = NULL;
    }
#line 1519 "parser.tab.c"
    break;

  case 31: /* selecao_decl: IF APR expressao FPR statement  */
#line 209 "parser.y"
                                           {
    yyval = newStmtNode(IfK);
    yyval->filho[0] = yyvsp[-2];
    yyval->filho[1] = yyvsp[0]; 
}
#line 1529 "parser.tab.c"
    break;

  case 32: /* selecao_decl: IF APR expressao FPR statement ELSE statement  */
#line 213 "parser.y"
                                                 {
    yyval = newStmtNode(IfK);
    yyval->filho[0] = yyvsp[-4];
    yyval->filho[1] = yyvsp[-2];
    yyval->filho[2] = yyvsp[0];  // quando tem o else tem 3 filhos
}
#line 1540 "parser.tab.c"
    break;

  case 33: /* iteracao_decl: WHILE APR expressao FPR statement  */
#line 220 "parser.y"
                                                {
    yyval = newStmtNode(WhileK);
    yyval->filho[0] = yyvsp[-2];
    yyval->filho[1] = yyvsp[0];
}
#line 1550 "parser.tab.c"
    break;

  case 34: /* retorno_decl: RETURN PV  */
#line 226 "parser.y"
                       {

        yyval = newStmtNode(ReturnK);
}
#line 1559 "parser.tab.c"
    break;

  case 35: /* retorno_decl: RETURN expressao PV  */
#line 229 "parser.y"
                       {
    yyval = newStmtNode(ReturnK);
    yyval->filho[0] = yyvsp[-1];
}
#line 1568 "parser.tab.c"
    break;

  case 36: /* expressao: var ATRIB expressao  */
#line 234 "parser.y"
                              {
    yyval = newStmtNode(AssignK);
    yyval->filho[0] = yyvsp[-2];
    yyval->filho[1] = yyvsp[0];
}
#line 1578 "parser.tab.c"
    break;

  case 37: /* expressao: simples_expressao  */
#line 239 "parser.y"
                         {
        yyval = yyvsp[0];
    }
#line 1586 "parser.tab.c"
    break;

  case 38: /* var: id  */
#line 243 "parser.y"
       {
    yyval = yyvsp[0];
    yyval->type = Integer;
    yyval->kind.exp = VarIdK;
}
#line 1596 "parser.tab.c"
    break;

  case 39: /* var: id ACOL expressao FCOL  */
#line 248 "parser.y"
                            {
        yyval = yyvsp[-3];
        yyval->filho[0] = yyvsp[-1];
        yyval->kind.exp = VetIdK;
        yyval->type = Integer;
    }
#line 1607 "parser.tab.c"
    break;

  case 40: /* simples_expressao: soma_expressao relacional soma_expressao  */
#line 255 "parser.y"
                                                            {
    yyval = yyvsp[-1];
    yyval->filho[0] = yyvsp[-2];
    yyval->filho[1] = yyvsp[0];
}
#line 1617 "parser.tab.c"
    break;

  case 41: /* simples_expressao: soma_expressao  */
#line 261 "parser.y"
                    {
        yyval = yyvsp[0];
    }
#line 1625 "parser.tab.c"
    break;

  case 42: /* relacional: MEIGL  */
#line 265 "parser.y"
                  {
                yyval = newExpNode(OpK);
                yyval->attr.op = MEIGL;
            }
#line 1634 "parser.tab.c"
    break;

  case 43: /* relacional: MEN  */
#line 269 "parser.y"
                 {
                yyval = newExpNode(OpK);
                yyval->attr.op = MEN;
            }
#line 1643 "parser.tab.c"
    break;

  case 44: /* relacional: MAI  */
#line 273 "parser.y"
                 {
                yyval = newExpNode(OpK);
                yyval->attr.op = MAI;
            }
#line 1652 "parser.tab.c"
    break;

  case 45: /* relacional: MAIGL  */
#line 277 "parser.y"
                   {
                yyval = newExpNode(OpK);
                yyval->attr.op = MAIGL;
            }
#line 1661 "parser.tab.c"
    break;

  case 46: /* relacional: IGL  */
#line 281 "parser.y"
                 {
                yyval = newExpNode(OpK);
                yyval->attr.op = IGL;
            }
#line 1670 "parser.tab.c"
    break;

  case 47: /* relacional: DIF  */
#line 285 "parser.y"
                 {
                yyval = newExpNode(OpK);
                yyval->attr.op = DIF;
            }
#line 1679 "parser.tab.c"
    break;

  case 48: /* soma_expressao: soma_expressao soma termo  */
#line 290 "parser.y"
                                          {
    yyval = yyvsp[-1];
    yyval->filho[0] = yyvsp[-2];
    yyval->filho[1] = yyvsp[0];
}
#line 1689 "parser.tab.c"
    break;

  case 49: /* soma_expressao: termo  */
#line 295 "parser.y"
             {
        yyval = yyvsp[0];
    }
#line 1697 "parser.tab.c"
    break;

  case 50: /* soma: SOMA  */
#line 299 "parser.y"
           {
    yyval = newExpNode(OpK);
    yyval->attr.op = SOMA;
    yyval->type = Integer;
    }
#line 1707 "parser.tab.c"
    break;

  case 51: /* soma: SUB  */
#line 304 "parser.y"
         {
    yyval = newExpNode(OpK);
    yyval->attr.op = SUB;
    yyval->type = Integer;
    }
#line 1717 "parser.tab.c"
    break;

  case 52: /* termo: termo mult fator  */
#line 310 "parser.y"
                       {

    yyval = yyvsp[-1];
    yyval->filho[0] = yyvsp[-2];
    yyval->filho[1] = yyvsp[0];

    }
#line 1729 "parser.tab.c"
    break;

  case 53: /* termo: fator  */
#line 317 "parser.y"
           {

     yyval = yyvsp[0];

    }
#line 1739 "parser.tab.c"
    break;

  case 54: /* mult: MUL  */
#line 323 "parser.y"
          {
    yyval = newExpNode(OpK);
    yyval->type = Integer;
    yyval->attr.op = MUL;
    }
#line 1749 "parser.tab.c"
    break;

  case 55: /* mult: DIV  */
#line 328 "parser.y"
         {
    yyval = newExpNode(OpK);
    yyval->type = Integer;
    yyval->attr.op = DIV;    
    }
#line 1759 "parser.tab.c"
    break;

  case 56: /* fator: APR expressao FPR  */
#line 334 "parser.y"
                          {yyval = yyvsp[-1];}
#line 1765 "parser.tab.c"
    break;

  case 57: /* fator: var  */
#line 334 "parser.y"
                                          {yyval = yyvsp[0];}
#line 1771 "parser.tab.c"
    break;

  case 58: /* fator: ativacao  */
#line 334 "parser.y"
                                                                {yyval = yyvsp[0];}
#line 1777 "parser.tab.c"
    break;

  case 59: /* fator: NUM  */
#line 335 "parser.y"
         {
        yyval = newExpNode(ConstK);
        yyval->attr.val = atoi(tokenString);
        yyval->type = Integer;
    }
#line 1787 "parser.tab.c"
    break;

  case 60: /* ativacao: id APR args FPR  */
#line 341 "parser.y"
                          {

    yyval = newStmtNode(CallK);
    yyval->filho[0] = yyvsp[-1];
    yyval->attr.nome  = copyString(yyvsp[-3]->attr.nome);
    yyval->lineno = yyvsp[-3]->lineno;
}
#line 1799 "parser.tab.c"
    break;

  case 61: /* ativacao: id APR FPR  */
#line 349 "parser.y"
                {
        yyval = newStmtNode(CallK);
        yyval->attr.nome = copyString(yyvsp[-2]->attr.nome);
        yyval->lineno = yyvsp[-2]->lineno;
    }
#line 1809 "parser.tab.c"
    break;

  case 62: /* args: arg_lista  */
#line 355 "parser.y"
                 {yyval = yyvsp[0];}
#line 1815 "parser.tab.c"
    break;

  case 63: /* arg_lista: arg_lista VIRG expressao  */
#line 357 "parser.y"
                                    {
        YYSTYPE t = yyvsp[-2];
        if(t != NULL){
            while(t->irmao != NULL){
                t = t->irmao;
            }
            t->irmao = yyvsp[0];
        }else{
            yyval = yyvsp[0];
        }
}
#line 1831 "parser.tab.c"
    break;

  case 64: /* arg_lista: expressao  */
#line 368 "parser.y"
               {
        yyval = yyvsp[0];
    }
#line 1839 "parser.tab.c"
    break;

  case 65: /* id: ID  */
#line 372 "parser.y"
       {
    yyval = newExpNode(IdK);
    yyval->attr.nome = copyString(tokenString);
    yyval->lineno = lineno;
}
#line 1849 "parser.tab.c"
    break;


#line 1853 "parser.tab.c"

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
      yyerror (YY_("syntax error"));
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
                      yytoken, &yylval);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 378 "parser.y"



void yyerror(char *msg)
{
	if(yychar == ERRO)
	{
		exit(0);
	}
	else
	{
		char *t = printToken(yychar,tokenString);
	   	printf("ERRO SINTÁTICO: %s Linha %d\n",t,lineno);
	}
}

static int yylex(void)
{
	TokenType t = getToken();
	return t;
}

TreeNode *parse(void)
{
	yyparse();
    return raiz;
}
