/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ident = 258,
     numb_lit = 259,
     char_lit = 260,
     float_lit = 261,
     _struct = 262,
     _char = 263,
     _int = 264,
     _long = 265,
     _float = 266,
     _break = 267,
     _return = 268,
     _if = 269,
     _else = 270,
     _switch = 271,
     _case = 272,
     _default = 273,
     _while = 274,
     _void = 275,
     _gl = 276,
     _ngl = 277,
     _klgl = 278,
     _grgl = 279,
     _shl = 280,
     _shr = 281
   };
#endif
#define ident 258
#define numb_lit 259
#define char_lit 260
#define float_lit 261
#define _struct 262
#define _char 263
#define _int 264
#define _long 265
#define _float 266
#define _break 267
#define _return 268
#define _if 269
#define _else 270
#define _switch 271
#define _case 272
#define _default 273
#define _while 274
#define _void 275
#define _gl 276
#define _ngl 277
#define _klgl 278
#define _grgl 279
#define _shl 280
#define _shr 281




/* Copy the first part of user declarations.  */
#line 1 "prak.y++"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "OTypes.h"

using namespace std;



int yyerror(char*);
extern int yylex();

struct TNode* createNewNode(struct TNode* n1, struct TNode* n2, struct TNode* n3, struct TNode* n4, struct TNode* n5, int type);

void out(struct TNode* n);
void gen(unsigned);

#define output
struct TNode* root;

// Speicher für traversierten Syntaxbaum
unsigned* pos = (unsigned*)malloc(8096);
unsigned* start = pos;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 30 "prak.y++"
typedef union YYSTYPE {
  struct TNode* nodep;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 159 "prak.cc"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 171 "prak.cc"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  21
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   314

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  65
/* YYNRULES -- Number of rules. */
#define YYNRULES  144
/* YYNRULES -- Number of states. */
#define YYNSTATES  268

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    31,     2,     2,
      39,    40,    29,    27,    35,    28,    44,    30,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    41,    34,
      42,    38,    43,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    36,     2,    37,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,    33,     2,     2,     2,     2,
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
      25,    26
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     4,     6,     8,    11,    13,    15,    17,
      24,    26,    29,    31,    35,    37,    41,    45,    48,    53,
      57,    60,    63,    65,    67,    69,    72,    74,    77,    80,
      84,    86,    89,    92,    96,    98,   100,   104,   108,   110,
     113,   116,   118,   121,   124,   127,   130,   132,   134,   136,
     138,   140,   142,   145,   148,   150,   153,   158,   162,   164,
     166,   172,   179,   185,   192,   197,   203,   205,   207,   209,
     213,   215,   218,   224,   232,   238,   246,   251,   258,   260,
     264,   267,   269,   274,   276,   279,   281,   283,   285,   287,
     289,   291,   293,   295,   297,   300,   303,   306,   310,   316,
     324,   326,   335,   337,   340,   345,   348,   351,   353,   359,
     364,   366,   370,   372,   376,   378,   382,   386,   388,   392,
     396,   400,   404,   406,   410,   414,   416,   420,   424,   426,
     430,   434,   438,   440,   443,   446,   450,   452,   454,   456,
     459,   461,   465,   471,   475
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      47,     0,    -1,    -1,    48,    -1,    49,    -1,    49,    48,
      -1,    50,    -1,    54,    -1,    73,    -1,     7,     3,    32,
      51,    33,    34,    -1,    46,    -1,    54,    51,    -1,    58,
      -1,    58,    35,    53,    -1,    59,    -1,    59,    35,    53,
      -1,    57,    52,    34,    -1,    55,    34,    -1,    55,    35,
      53,    34,    -1,    56,    53,    34,    -1,    57,     3,    -1,
       7,     3,    -1,     8,    -1,     9,    -1,    10,    -1,    10,
       9,    -1,    11,    -1,    60,    62,    -1,    60,    64,    -1,
      60,    62,    64,    -1,    60,    -1,    60,    62,    -1,    60,
      64,    -1,    60,    62,    64,    -1,     3,    -1,    63,    -1,
      63,    35,    61,    -1,    36,    61,    37,    -1,     4,    -1,
      38,    65,    -1,    38,    72,    -1,    66,    -1,    27,    68,
      -1,    27,    69,    -1,    28,    68,    -1,    28,    69,    -1,
      67,    -1,    68,    -1,    69,    -1,     5,    -1,     4,    -1,
       6,    -1,    35,    65,    -1,    35,    72,    -1,    70,    -1,
      70,    71,    -1,    32,    65,    71,    33,    -1,    32,    71,
      33,    -1,    74,    -1,    79,    -1,    75,    76,    39,    40,
      34,    -1,    75,    76,    39,    77,    40,    34,    -1,    56,
      76,    39,    40,    34,    -1,    56,    76,    39,    77,    40,
      34,    -1,    55,    39,    40,    34,    -1,    55,    39,    77,
      40,    34,    -1,    20,    -1,     3,    -1,    78,    -1,    78,
      35,    77,    -1,    57,    -1,     7,     3,    -1,    75,    76,
      39,    40,    83,    -1,    75,    76,    39,    81,    80,    40,
      83,    -1,    56,    76,    39,    40,    83,    -1,    56,    76,
      39,    81,    80,    40,    83,    -1,    55,    39,    40,    83,
      -1,    55,    39,    81,    80,    40,    83,    -1,    46,    -1,
      35,    81,    80,    -1,    78,    82,    -1,     3,    -1,    32,
      51,    84,    33,    -1,    46,    -1,    85,    84,    -1,    86,
      -1,    87,    -1,    88,    -1,    89,    -1,    90,    -1,    92,
      -1,    96,    -1,    97,    -1,    34,    -1,    99,    34,    -1,
      12,    34,    -1,    13,    34,    -1,    13,    99,    34,    -1,
      14,    39,    91,    40,    85,    -1,    14,    39,    91,    40,
      85,    15,    85,    -1,    99,    -1,    16,    39,    91,    40,
      32,    94,    93,    33,    -1,    46,    -1,    94,    93,    -1,
      95,    41,    85,    84,    -1,    17,    67,    -1,    17,    68,
      -1,    18,    -1,    19,    39,    91,    40,    85,    -1,    32,
      51,    84,    33,    -1,    46,    -1,    35,    99,    98,    -1,
     100,    -1,   107,    38,    99,    -1,   101,    -1,   100,    21,
     101,    -1,   100,    22,   101,    -1,   102,    -1,   101,    42,
     102,    -1,   101,    43,   102,    -1,   101,    23,   102,    -1,
     101,    24,   102,    -1,   103,    -1,   102,    25,   103,    -1,
     102,    26,   103,    -1,   104,    -1,   103,    27,   104,    -1,
     103,    28,   104,    -1,   105,    -1,   104,    29,   105,    -1,
     104,    30,   105,    -1,   104,    31,   105,    -1,   106,    -1,
      27,   106,    -1,    28,   106,    -1,    39,    99,    40,    -1,
      66,    -1,   107,    -1,   109,    -1,    60,   108,    -1,    46,
      -1,   108,    44,    60,    -1,   108,    36,    99,    98,    37,
      -1,    76,    39,    40,    -1,    76,    39,    99,    98,    40,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,    56,    56,    58,    66,    67,    69,    70,    71,    73,
      75,    76,    78,    79,    82,    83,    87,    88,    89,    90,
      93,    96,    99,   100,   101,   102,   103,   105,   106,   107,
     110,   111,   112,   113,   116,   118,   119,   121,   123,   125,
     126,   128,   129,   130,   131,   132,   134,   135,   136,   138,
     140,   142,   144,   145,   147,   148,   150,   151,   153,   154,
     156,   157,   158,   159,   160,   161,   163,   166,   168,   169,
     171,   172,   174,   175,   176,   177,   178,   179,   182,   183,
     185,   187,   189,   191,   192,   194,   195,   196,   197,   198,
     199,   200,   201,   203,   205,   207,   209,   210,   212,   213,
     215,   217,   219,   220,   222,   224,   225,   226,   228,   230,
     232,   233,   235,   236,   238,   239,   240,   242,   243,   244,
     245,   246,   248,   249,   250,   252,   253,   254,   256,   257,
     258,   259,   261,   262,   263,   264,   266,   267,   268,   270,
     272,   273,   274,   276,   277
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ident", "numb_lit", "char_lit", 
  "float_lit", "_struct", "_char", "_int", "_long", "_float", "_break", 
  "_return", "_if", "_else", "_switch", "_case", "_default", "_while", 
  "_void", "_gl", "_ngl", "_klgl", "_grgl", "_shl", "_shr", "'+'", "'-'", 
  "'*'", "'/'", "'%'", "'{'", "'}'", "';'", "','", "'['", "']'", "'='", 
  "'('", "')'", "':'", "'<'", "'>'", "'.'", "$accept", "epsilon", 
  "program", "decl_st", "decl", "struct_decl", "var_decl_st", 
  "var_part_st", "var_part_all_st", "var_decl", "def_part", "struct_part", 
  "base_type", "var_part", "var_part_all", "var_ident", "dim_st", 
  "array_part", "dim", "init_part", "constant", "unsigned_constant", 
  "char_constant", "int_constant", "float_constant", 
  "complex_constant_opt", "complex_constant_st", "complex_constant", 
  "func_decl", "prototype", "ret_type", "func_ident", "par_type_st", 
  "par_type", "implementation", "par_decl_st", "par_decl", "par_ident", 
  "block", "stm_st", "stm", "empty", "expr", "break", "return", "if", 
  "cond", "switch", "case_st", "case", "case_label", "while", "compound", 
  "expression_st", "expression", "equality", "relation", "shift", 
  "add_sub", "mult_div", "primitive", "operand", "variable", "qualifying", 
  "function_call", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,    43,    45,    42,
      47,    37,   123,   125,    59,    44,    91,    93,    61,    40,
      41,    58,    60,    62,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    45,    46,    47,    48,    48,    49,    49,    49,    50,
      51,    51,    52,    52,    53,    53,    54,    54,    54,    54,
      55,    56,    57,    57,    57,    57,    57,    58,    58,    58,
      59,    59,    59,    59,    60,    61,    61,    62,    63,    64,
      64,    65,    65,    65,    65,    65,    66,    66,    66,    67,
      68,    69,    70,    70,    71,    71,    72,    72,    73,    73,
      74,    74,    74,    74,    74,    74,    75,    76,    77,    77,
      78,    78,    79,    79,    79,    79,    79,    79,    80,    80,
      81,    82,    83,    84,    84,    85,    85,    85,    85,    85,
      85,    85,    85,    86,    87,    88,    89,    89,    90,    90,
      91,    92,    93,    93,    94,    95,    95,    95,    96,    97,
      98,    98,    99,    99,   100,   100,   100,   101,   101,   101,
     101,   101,   102,   102,   102,   103,   103,   103,   104,   104,
     104,   104,   105,   105,   105,   105,   106,   106,   106,   107,
     108,   108,   108,   109,   109
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     1,     1,     2,     1,     1,     1,     6,
       1,     2,     1,     3,     1,     3,     3,     2,     4,     3,
       2,     2,     1,     1,     1,     2,     1,     2,     2,     3,
       1,     2,     2,     3,     1,     1,     3,     3,     1,     2,
       2,     1,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     2,     4,     3,     1,     1,
       5,     6,     5,     6,     4,     5,     1,     1,     1,     3,
       1,     2,     5,     7,     5,     7,     4,     6,     1,     3,
       2,     1,     4,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     3,     5,     7,
       1,     8,     1,     2,     4,     2,     2,     1,     5,     4,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     1,     2,     2,     3,     1,     1,     1,     2,
       1,     3,     5,     3,     5
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,    22,    23,    24,    26,    66,     0,     3,     4,
       6,     7,     0,     0,     0,     8,    58,     0,    59,    21,
      25,     1,     5,    17,     0,     0,    34,     0,    14,    30,
       0,    20,     0,    12,     0,    67,     0,     2,    34,     0,
       0,     0,    70,     0,    68,     2,    19,     0,     0,     0,
      31,    32,     0,    16,     0,    27,    28,     0,     0,    10,
       0,     2,     0,     0,    18,    71,     2,    64,    76,     0,
      81,     0,    80,     0,    78,     0,    15,    38,     0,    35,
      50,    49,    51,     0,     0,     0,    39,    41,    46,    47,
      48,    40,    33,     0,     0,     2,    13,    29,     0,     0,
       2,    21,     0,    11,     2,    65,    69,    68,     0,     2,
       0,    37,     0,    42,    43,    44,    45,     0,     0,    54,
       0,    62,    74,     0,     0,    60,    72,     0,     0,     9,
       0,     0,     0,     0,     0,     0,     0,     2,    93,     0,
      83,     2,   136,     0,     0,     2,    85,    86,    87,    88,
      89,    90,    91,    92,     0,   112,   114,   117,   122,   125,
     128,   132,   137,   138,    79,    77,    36,    52,    53,     0,
      55,    57,    63,     0,    61,     0,    95,    96,     0,     0,
       0,     0,   133,   137,   134,     2,     0,   140,   139,     0,
      82,    84,    94,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    56,    75,    73,
      97,     0,   100,     0,     0,     0,   135,     0,     0,   143,
       2,   115,   116,   120,   121,   118,   119,   123,   124,   126,
     127,   129,   130,   131,   113,     0,     0,     0,   109,     2,
     141,     0,   110,     0,    98,     0,   108,     0,     2,   144,
       0,     0,   107,     2,     0,   142,   111,    99,   105,   106,
     102,     0,     2,     0,   101,   103,     2,   104
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    59,     7,     8,     9,    10,    60,    32,    27,    61,
      62,    63,    14,    33,    28,   141,    78,    50,    79,    51,
      86,   142,    88,    89,    90,   119,   120,    91,    15,    16,
      17,   143,    43,    44,    18,    75,    45,    72,    68,   144,
     145,   146,   147,   148,   149,   150,   211,   151,   261,   262,
     254,   152,   153,   243,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   188,   163
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -210
static const short yypact[] =
{
     180,     4,  -210,  -210,    13,  -210,  -210,    52,  -210,   180,
    -210,  -210,   -15,    72,   116,  -210,  -210,   126,  -210,   110,
    -210,  -210,  -210,  -210,   151,    22,   133,   173,   157,    46,
     199,   115,   220,   224,    46,  -210,   221,   188,  -210,   227,
     259,   129,  -210,   225,    12,   228,  -210,   151,   260,   142,
     229,  -210,    82,  -210,   151,   229,  -210,   169,   263,  -210,
     235,   188,   101,   151,  -210,  -210,   188,  -210,  -210,   236,
    -210,   203,  -210,   203,  -210,   231,  -210,  -210,   232,   237,
    -210,  -210,  -210,   160,   160,    93,  -210,  -210,  -210,  -210,
    -210,  -210,  -210,   201,   233,   228,  -210,  -210,   202,   234,
     228,  -210,   241,  -210,   111,  -210,  -210,   242,   273,   228,
     246,  -210,   260,  -210,  -210,  -210,  -210,   142,   244,   244,
     247,  -210,  -210,   248,   243,  -210,  -210,   250,   245,  -210,
     252,   128,   249,   251,   253,   219,   219,   188,  -210,   154,
    -210,  -210,  -210,   254,   256,   111,  -210,  -210,  -210,  -210,
    -210,  -210,  -210,  -210,   257,   194,   162,   158,   174,   189,
    -210,  -210,   258,  -210,  -210,  -210,  -210,  -210,  -210,   261,
    -210,  -210,  -210,   246,  -210,   246,  -210,  -210,   264,   154,
     154,   154,  -210,  -210,  -210,   111,   255,  -210,    43,    33,
    -210,  -210,  -210,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,  -210,  -210,  -210,
    -210,   262,  -210,   265,   266,   267,  -210,   154,   151,  -210,
     268,   162,   162,   158,   158,   158,   158,   174,   174,   189,
     189,  -210,  -210,  -210,  -210,   111,   269,   111,  -210,   268,
    -210,   154,  -210,   270,   272,   223,  -210,   271,   268,  -210,
     111,   238,  -210,   223,   240,  -210,  -210,  -210,  -210,  -210,
    -210,   274,   223,   111,  -210,  -210,   111,  -210
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -210,   -45,  -210,   288,  -210,  -210,   -52,  -210,    16,    25,
      65,    68,    -4,  -210,  -210,   -12,   187,   275,  -210,   118,
     -68,   -39,    60,   -80,   161,  -210,   130,   195,  -210,  -210,
    -210,   124,    24,   166,  -210,   -82,    92,  -210,   -87,  -140,
    -209,  -210,  -210,  -210,  -210,  -210,    66,  -210,    42,    69,
    -210,  -210,  -210,  -168,  -123,  -210,    57,    31,    53,    54,
      27,   122,   -92,  -210,  -210
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -68
static const short yytable[] =
{
      74,    29,    34,   113,   115,   191,   122,    19,   178,   103,
      87,   126,    29,   124,   104,    70,   186,   118,   128,    23,
      24,    42,    20,   165,    25,    11,   244,   164,   246,    40,
       2,     3,     4,     5,    11,    29,    26,    80,    81,    82,
      39,   257,    29,   183,   183,   215,    87,    71,    42,   167,
      74,    29,    21,    42,   266,    74,   212,   212,   212,   140,
     135,   136,    41,    76,    74,    12,   220,    42,    13,    42,
      96,   247,   139,   219,    12,    26,    94,    13,    87,   217,
     256,    99,    48,   234,    49,   185,   208,   218,   209,    40,
       2,     3,     4,     5,   239,   106,   187,    80,    81,    82,
     140,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   183,   183,    26,    80,    81,    82,   248,    31,
      83,    84,    93,   130,   131,   132,   267,   133,   117,    35,
     134,    26,    80,    81,    82,    23,    24,    30,   135,   136,
     140,    36,    37,   137,    95,   138,    80,    81,    82,   100,
     139,   -34,    56,   -34,    38,   135,   136,    26,    80,    81,
      82,    66,   177,    67,    80,   109,    82,   139,    92,    83,
      84,   259,   -67,    97,    85,   242,    40,     2,     3,     4,
       5,   135,   136,   199,   200,   195,   196,     1,     2,     3,
       4,     5,    47,   139,   242,    58,     2,     3,     4,     5,
       6,   201,   202,   242,   197,   198,   240,    46,   260,    98,
      40,     2,     3,     4,     5,   193,   194,   260,   203,   204,
     205,   140,    26,    80,    81,    82,   223,   224,   225,   226,
     231,   232,   233,    66,    66,   121,   125,   107,    52,   108,
     251,   252,    80,    81,   114,   116,   213,   214,   169,   170,
     221,   222,   227,   228,    53,   229,   230,   182,   184,    54,
      57,    64,    65,    73,    77,    69,   101,    49,   102,   111,
     105,   110,   112,   123,   127,   129,    70,    71,    66,   117,
     171,   263,   172,   173,   174,   175,   176,   250,   179,   190,
     180,   192,   181,   189,   207,   216,   206,    22,   210,   166,
     238,   245,   235,   241,   265,   236,   237,   264,   255,    55,
     249,   258,   168,     0,   253
};

static const short yycheck[] =
{
      45,    13,    14,    83,    84,   145,    93,     3,   131,    61,
      49,    98,    24,    95,    66,     3,   139,    85,   100,    34,
      35,    25,     9,   110,    39,     0,   235,   109,   237,     7,
       8,     9,    10,    11,     9,    47,     3,     4,     5,     6,
      24,   250,    54,   135,   136,   185,    85,    35,    52,   117,
      95,    63,     0,    57,   263,   100,   179,   180,   181,   104,
      27,    28,    40,    47,   109,     0,   189,    71,     0,    73,
      54,   239,    39,    40,     9,     3,    52,     9,   117,    36,
     248,    57,    36,   206,    38,   137,   173,    44,   175,     7,
       8,     9,    10,    11,   217,    71,   141,     4,     5,     6,
     145,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,     3,     4,     5,     6,   241,     3,
      27,    28,    40,    12,    13,    14,   266,    16,    35,     3,
      19,     3,     4,     5,     6,    34,    35,    13,    27,    28,
     185,    17,    32,    32,    52,    34,     4,     5,     6,    57,
      39,    36,    34,    38,     3,    27,    28,     3,     4,     5,
       6,    32,    34,    34,     4,    73,     6,    39,    50,    27,
      28,   251,    39,    55,    32,   220,     7,     8,     9,    10,
      11,    27,    28,    25,    26,    23,    24,     7,     8,     9,
      10,    11,    35,    39,   239,     7,     8,     9,    10,    11,
      20,    27,    28,   248,    42,    43,   218,    34,   253,    40,
       7,     8,     9,    10,    11,    21,    22,   262,    29,    30,
      31,   266,     3,     4,     5,     6,   195,   196,   197,   198,
     203,   204,   205,    32,    32,    34,    34,    71,    39,    73,
      17,    18,     4,     5,    83,    84,   180,   181,   118,   119,
     193,   194,   199,   200,    34,   201,   202,   135,   136,    35,
      39,    34,     3,    35,     4,    40,     3,    38,    33,    37,
      34,    40,    35,    40,    40,    34,     3,    35,    32,    35,
      33,    41,    34,    40,    34,    40,    34,    15,    39,    33,
      39,    34,    39,    39,    33,    40,    38,     9,    34,   112,
      33,    32,    40,    35,   262,    40,    40,    33,    37,    34,
      40,   251,   117,    -1,   245
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     7,     8,     9,    10,    11,    20,    47,    48,    49,
      50,    54,    55,    56,    57,    73,    74,    75,    79,     3,
       9,     0,    48,    34,    35,    39,     3,    53,    59,    60,
      76,     3,    52,    58,    60,     3,    76,    32,     3,    53,
       7,    40,    57,    77,    78,    81,    34,    35,    36,    38,
      62,    64,    39,    34,    35,    62,    64,    39,     7,    46,
      51,    54,    55,    56,    34,     3,    32,    34,    83,    40,
       3,    35,    82,    35,    46,    80,    53,     4,    61,    63,
       4,     5,     6,    27,    28,    32,    65,    66,    67,    68,
      69,    72,    64,    40,    77,    81,    53,    64,    40,    77,
      81,     3,    33,    51,    51,    34,    77,    78,    78,    81,
      40,    37,    35,    68,    69,    68,    69,    35,    65,    70,
      71,    34,    83,    40,    80,    34,    83,    40,    80,    34,
      12,    13,    14,    16,    19,    27,    28,    32,    34,    39,
      46,    60,    66,    76,    84,    85,    86,    87,    88,    89,
      90,    92,    96,    97,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   109,    80,    83,    61,    65,    72,    71,
      71,    33,    34,    40,    34,    40,    34,    34,    99,    39,
      39,    39,   106,   107,   106,    51,    99,    46,   108,    39,
      33,    84,    34,    21,    22,    23,    24,    42,    43,    25,
      26,    27,    28,    29,    30,    31,    38,    33,    83,    83,
      34,    91,    99,    91,    91,    84,    40,    36,    44,    40,
      99,   101,   101,   102,   102,   102,   102,   103,   103,   104,
     104,   105,   105,   105,    99,    40,    40,    40,    33,    99,
      60,    35,    46,    98,    85,    32,    85,    98,    99,    40,
      15,    17,    18,    94,    95,    37,    98,    85,    67,    68,
      46,    93,    94,    41,    33,    93,    85,    84
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1

/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

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
#line 56 "prak.y++"
    { yyval.nodep = createNewNode(0,0,0,0,0,EPSILON);}
    break;

  case 3:
#line 58 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,PROGRAM);
                                                                          root = yyval.nodep;
                                                                          #ifdef output 
                                                                          out(yyval.nodep); 
                                                                          #endif
                                                                          return 0;
                                                                        }
    break;

  case 4:
#line 66 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,DECL_ST_1);}
    break;

  case 5:
#line 67 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,yyvsp[0].nodep,0,0,0,DECL_ST_2);}
    break;

  case 6:
#line 69 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,DECL);}
    break;

  case 7:
#line 70 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,DECL);}
    break;

  case 8:
#line 71 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,DECL);}
    break;

  case 9:
#line 73 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-4].nodep,yyvsp[-2].nodep,0,0,0,STRUCT_DECL);}
    break;

  case 10:
#line 75 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,VAR_DECL_ST_1);}
    break;

  case 11:
#line 76 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,yyvsp[0].nodep,0,0,0,VAR_DECL_ST_2);}
    break;

  case 12:
#line 78 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,VAR_PART_ST_1);}
    break;

  case 13:
#line 79 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,VAR_PART_ST_2);}
    break;

  case 14:
#line 82 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,VAR_PART_ALL_ST_1);}
    break;

  case 15:
#line 83 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,VAR_PART_ALL_ST_2);}
    break;

  case 16:
#line 87 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[-1].nodep,0,0,0,VAR_DECL_1);}
    break;

  case 17:
#line 88 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,0,0,0,0,VAR_DECL_2);}
    break;

  case 18:
#line 89 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-3].nodep,yyvsp[-1].nodep,0,0,0,VAR_DECL_3);}
    break;

  case 19:
#line 90 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[-1].nodep,0,0,0,VAR_DECL_4);}
    break;

  case 20:
#line 93 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,yyvsp[0].nodep,0,0,0,DEF_PART);}
    break;

  case 21:
#line 96 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,STRUCT_PART);}
    break;

  case 22:
#line 99 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,BASE_TYPE);}
    break;

  case 23:
#line 100 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,BASE_TYPE);}
    break;

  case 24:
#line 101 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,BASE_TYPE);}
    break;

  case 25:
#line 102 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,0,0,0,0,BASE_TYPE);}
    break;

  case 26:
#line 103 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,BASE_TYPE);}
    break;

  case 27:
#line 105 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,yyvsp[0].nodep,0,0,0,VAR_PART_1);}
    break;

  case 28:
#line 106 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,yyvsp[0].nodep,0,0,0,VAR_PART_1);}
    break;

  case 29:
#line 107 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[-1].nodep,yyvsp[0].nodep,0,0,VAR_PART_2);}
    break;

  case 30:
#line 110 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,VAR_PART_ALL_1);}
    break;

  case 31:
#line 111 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,yyvsp[0].nodep,0,0,0,VAR_PART_ALL_2);}
    break;

  case 32:
#line 112 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,yyvsp[0].nodep,0,0,0,VAR_PART_ALL_2);}
    break;

  case 33:
#line 113 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[-1].nodep,yyvsp[0].nodep,0,0,VAR_PART_ALL_3);}
    break;

  case 34:
#line 116 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,VAR_IDENT);}
    break;

  case 35:
#line 118 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,DIM_ST_1);}
    break;

  case 36:
#line 119 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,DIM_ST_2);}
    break;

  case 37:
#line 121 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,0,0,0,0,ARRAY_PART);}
    break;

  case 38:
#line 123 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,DIM);}
    break;

  case 39:
#line 125 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,INIT_PART);}
    break;

  case 40:
#line 126 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,INIT_PART);}
    break;

  case 41:
#line 128 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,CONSTANT_1);}
    break;

  case 42:
#line 129 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,CONSTANT_2);}
    break;

  case 43:
#line 130 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,CONSTANT_2);}
    break;

  case 44:
#line 131 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,CONSTANT_3);}
    break;

  case 45:
#line 132 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,CONSTANT_3);}
    break;

  case 46:
#line 134 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,UNSIGNED_CONSTANT);}
    break;

  case 47:
#line 135 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,UNSIGNED_CONSTANT);}
    break;

  case 48:
#line 136 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,UNSIGNED_CONSTANT);}
    break;

  case 49:
#line 138 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,CHAR_CONSTANT);}
    break;

  case 50:
#line 140 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,INT_CONSTANT);}
    break;

  case 51:
#line 142 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,FLOAT_CONSTANT);}
    break;

  case 52:
#line 144 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,COMPLEX_CONSTANT_OPT);}
    break;

  case 53:
#line 145 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,COMPLEX_CONSTANT_OPT);}
    break;

  case 54:
#line 147 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,COMPLEX_CONSTANT_ST_1);}
    break;

  case 55:
#line 148 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,yyvsp[0].nodep,0,0,0,COMPLEX_CONSTANT_ST_2);}
    break;

  case 56:
#line 150 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[-1].nodep,0,0,0,COMPLEX_CONSTANT_1);}
    break;

  case 57:
#line 151 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,0,0,0,0,COMPLEX_CONSTANT_2);}
    break;

  case 58:
#line 153 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,FUNC_DECL);}
    break;

  case 59:
#line 154 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,FUNC_DECL);}
    break;

  case 60:
#line 156 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-4].nodep,yyvsp[-3].nodep,0,0,0,PROTOTYPE_1);}
    break;

  case 61:
#line 157 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-5].nodep,yyvsp[-4].nodep,yyvsp[-2].nodep,0,0,PROTOTYPE_2);}
    break;

  case 62:
#line 158 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-4].nodep,yyvsp[-3].nodep,0,0,0,PROTOTYPE_3);}
    break;

  case 63:
#line 159 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-5].nodep,yyvsp[-4].nodep,yyvsp[-2].nodep,0,0,PROTOTYPE_4);}
    break;

  case 64:
#line 160 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-3].nodep,0,0,0,0,PROTOTYPE_5);}
    break;

  case 65:
#line 161 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-4].nodep,yyvsp[-2].nodep,0,0,0,PROTOTYPE_6);}
    break;

  case 66:
#line 163 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,RET_TYPE);}
    break;

  case 67:
#line 166 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,FUNC_IDENT);}
    break;

  case 68:
#line 168 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,PAR_TYPE_ST_1);}
    break;

  case 69:
#line 169 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,PAR_TYPE_ST_2);}
    break;

  case 70:
#line 171 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,PAR_TYPE_1);}
    break;

  case 71:
#line 172 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,PAR_TYPE_2);}
    break;

  case 72:
#line 174 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-4].nodep,yyvsp[-3].nodep,yyvsp[0].nodep,0,0,IMPLEMENTATION_1);}
    break;

  case 73:
#line 175 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-6].nodep,yyvsp[-5].nodep,yyvsp[-3].nodep,yyvsp[-2].nodep,yyvsp[0].nodep,IMPLEMENTATION_2);}
    break;

  case 74:
#line 176 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-4].nodep,yyvsp[-3].nodep,yyvsp[0].nodep,0,0,IMPLEMENTATION_3);}
    break;

  case 75:
#line 177 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-6].nodep,yyvsp[-5].nodep,yyvsp[-3].nodep,yyvsp[-2].nodep,yyvsp[0].nodep,IMPLEMENTATION_4);}
    break;

  case 76:
#line 178 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-3].nodep,yyvsp[0].nodep,0,0,0,IMPLEMENTATION_5);}
    break;

  case 77:
#line 179 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-5].nodep,yyvsp[-3].nodep,yyvsp[-2].nodep,yyvsp[0].nodep,0,IMPLEMENTATION_6);}
    break;

  case 78:
#line 182 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,PAR_DECL_ST_1);}
    break;

  case 79:
#line 183 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,yyvsp[0].nodep,0,0,0,PAR_DECL_ST_2);}
    break;

  case 80:
#line 185 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,yyvsp[0].nodep,0,0,0,PAR_DECL);}
    break;

  case 81:
#line 187 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,PAR_IDENT);}
    break;

  case 82:
#line 189 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[-1].nodep,0,0,0,BLOCK);}
    break;

  case 83:
#line 191 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,STM_ST_1);}
    break;

  case 84:
#line 192 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,yyvsp[0].nodep,0,0,0,STM_ST_2);}
    break;

  case 85:
#line 194 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,STM);}
    break;

  case 86:
#line 195 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,STM);}
    break;

  case 87:
#line 196 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,STM);}
    break;

  case 88:
#line 197 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,STM);}
    break;

  case 89:
#line 198 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,STM);}
    break;

  case 90:
#line 199 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,STM);}
    break;

  case 91:
#line 200 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,STM);}
    break;

  case 92:
#line 201 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,STM);}
    break;

  case 93:
#line 203 "prak.y++"
    { yyval.nodep = createNewNode(0,0,0,0,0,EMPTY);}
    break;

  case 94:
#line 205 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,0,0,0,0,EXPR);}
    break;

  case 95:
#line 207 "prak.y++"
    { yyval.nodep = createNewNode(0,0,0,0,0,BREAK);}
    break;

  case 96:
#line 209 "prak.y++"
    { yyval.nodep = createNewNode(0,0,0,0,0,RETURN_1);}
    break;

  case 97:
#line 210 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,0,0,0,0,RETURN_2);}
    break;

  case 98:
#line 212 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,IF_1);}
    break;

  case 99:
#line 213 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-4].nodep,yyvsp[-2].nodep,yyvsp[0].nodep,0,0,IF_2);}
    break;

  case 100:
#line 215 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,COND);}
    break;

  case 101:
#line 217 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-5].nodep,yyvsp[-2].nodep,yyvsp[-1].nodep,0,0,SWITCH);}
    break;

  case 102:
#line 219 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,CASE_ST_1);}
    break;

  case 103:
#line 220 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,yyvsp[0].nodep,0,0,0,CASE_ST_2);}
    break;

  case 104:
#line 222 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-3].nodep,yyvsp[-1].nodep,yyvsp[0].nodep,0,0,CASE);}
    break;

  case 105:
#line 224 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,CASE_LABEL_1);}
    break;

  case 106:
#line 225 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,CASE_LABEL_1);}
    break;

  case 107:
#line 226 "prak.y++"
    { yyval.nodep = createNewNode(0,0,0,0,0,CASE_LABEL_2);}
    break;

  case 108:
#line 228 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,WHILE);}
    break;

  case 109:
#line 230 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[-1].nodep,0,0,0,COMPOUND);}
    break;

  case 110:
#line 232 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,EXPRESSION_ST_1);}
    break;

  case 111:
#line 233 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,yyvsp[0].nodep,0,0,0,EXPRESSION_ST_2);}
    break;

  case 112:
#line 235 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,EXPRESSION_1);}
    break;

  case 113:
#line 236 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,EXPRESSION_2);}
    break;

  case 114:
#line 238 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,EQUALITY_1);}
    break;

  case 115:
#line 239 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,EQUALITY_2);}
    break;

  case 116:
#line 240 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,EQUALITY_3);}
    break;

  case 117:
#line 242 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,RELATION_1);}
    break;

  case 118:
#line 243 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,RELATION_2);}
    break;

  case 119:
#line 244 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,RELATION_3);}
    break;

  case 120:
#line 245 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,RELATION_4);}
    break;

  case 121:
#line 246 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,RELATION_5);}
    break;

  case 122:
#line 248 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,SHIFT_1);}
    break;

  case 123:
#line 249 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,SHIFT_2);}
    break;

  case 124:
#line 250 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,SHIFT_3);}
    break;

  case 125:
#line 252 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,ADD_SUB_1);}
    break;

  case 126:
#line 253 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,ADD_SUB_2);}
    break;

  case 127:
#line 254 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,ADD_SUB_3);}
    break;

  case 128:
#line 256 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,MULT_DIV_1);}
    break;

  case 129:
#line 257 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,MULT_DIV_2);}
    break;

  case 130:
#line 258 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,MULT_DIV_3);}
    break;

  case 131:
#line 259 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,MULT_DIV_4);}
    break;

  case 132:
#line 261 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,PRIMITIVE_1);}
    break;

  case 133:
#line 262 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,PRIMITIVE_2);}
    break;

  case 134:
#line 263 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,PRIMITIVE_3);}
    break;

  case 135:
#line 264 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,0,0,0,0,PRIMITIVE_4);}
    break;

  case 136:
#line 266 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,OPERAND);}
    break;

  case 137:
#line 267 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,OPERAND);}
    break;

  case 138:
#line 268 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,OPERAND);}
    break;

  case 139:
#line 270 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-1].nodep,yyvsp[0].nodep,0,0,0,VARIABLE);}
    break;

  case 140:
#line 272 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[0].nodep,0,0,0,0,QUALIFYING_1);}
    break;

  case 141:
#line 273 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,yyvsp[0].nodep,0,0,0,QUALIFYING_2);}
    break;

  case 142:
#line 274 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-4].nodep,yyvsp[-2].nodep,yyvsp[-1].nodep,0,0,QUALIFYING_3);}
    break;

  case 143:
#line 276 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-2].nodep,0,0,0,0,FUNCTION_CALL_1);}
    break;

  case 144:
#line 277 "prak.y++"
    { yyval.nodep = createNewNode(yyvsp[-4].nodep,yyvsp[-2].nodep,yyvsp[-1].nodep,0,0,FUNCTION_CALL_2);}
    break;


    }

/* Line 991 of yacc.c.  */
#line 2032 "prak.cc"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab2;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:

  /* Suppress GCC warning that yyerrlab1 is unused when no action
     invokes YYERROR.  */
#if !defined(__MINGW32__)
#if defined (__GNUC_MINOR__) && 2093 <= (__GNUC__ * 1000 + __GNUC_MINOR__)
  __attribute__ ((__unused__))
#endif
#endif

  goto yyerrlab2;


/*---------------------------------------------------------------.
| yyerrlab2 -- pop states until the error token can be shifted.  |
`---------------------------------------------------------------*/
yyerrlab2:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 281 "prak.y++"


struct TNode* createNewNode(struct TNode* n1, struct TNode* n2, struct TNode* n3, struct TNode* n4, struct TNode* n5, int type)
{
  struct TNode* newNode = (struct TNode*)malloc(sizeof(struct TNode));

  newNode->n1 = n1;
  newNode->n2 = n2;
  newNode->n3 = n3;
  newNode->n4 = n4;
  newNode->n5 = n5;
  newNode->type = type;

  return newNode;
}
        





void out(struct TNode* n)
{ 
  if(n != 0)
  {
    switch(n->type)
    { 
        
        case PROGRAM                    : out(n->n1); gen(n->type); printf("program \n"); break;
        case DECL_ST_1                  : out(n->n1); gen(n->type); printf("{decl}* 1"); break;
        case DECL_ST_2                  : out(n->n1); out(n->n2); gen(n->type); printf("{decl}* 2"); break;
        case DECL                       : out(n->n1); gen(n->type); printf("decl "); break;
        case STRUCT_DECL                : out(n->n1); out(n->n2); gen(n->type); printf("struct_decl "); break;
        case VAR_DECL_ST_1              : out(n->n1); gen(n->type); printf("{var_decl}* 1"); break;
        case VAR_DECL_ST_2              : out(n->n1); out(n->n2); gen(n->type); printf("{var_decl}* 2"); break;
        case VAR_PART_ST_1              : out(n->n1); gen(n->type); printf("{var_part}* 3"); break;
        case VAR_PART_ST_2              : out(n->n1); out(n->n2); gen(n->type); printf("{var_part}* 4"); break;
        case VAR_PART_ALL_ST_1          : out(n->n1); gen(n->type); printf("{var_part_all}* "); break;
        case VAR_PART_ALL_ST_2          : out(n->n1); out(n->n2); gen(n->type); printf("{var_part_all}* "); break;
        case VAR_DECL_1                 : out(n->n1); out(n->n2); gen(n->type); printf("var_decl 1 "); break;
        case VAR_DECL_2                 : out(n->n1); gen(n->type); printf("var_decl 2 "); break;
        case VAR_DECL_3                 : out(n->n1); out(n->n2); gen(n->type); printf("var_decl 3 "); break;
        case VAR_DECL_4                 : out(n->n1); out(n->n2); gen(n->type); printf("var_decl 4 "); break; 
        case DEF_PART                   : out(n->n1); gen(n->type); gen(IDENTIFIER); printf("ident: %s ",(char*)n->n2); printf("def_part "); break;
        case STRUCT_PART                : out(n->n1); gen(n->type); printf("struct_part "); break;
        case BASE_TYPE                  : gen(n->type); printf("base_type "); break;
        case VAR_PART_1                 : out(n->n1); out(n->n2); gen(n->type); printf("var_part "); break;
        case VAR_PART_2                 : out(n->n1); out(n->n2); out(n->n3); gen(n->type); printf("var_part "); break;
        case VAR_PART_ALL_1             : out(n->n1); gen(n->type); printf("var_part_all "); break;
        case VAR_PART_ALL_2             : out(n->n1); out(n->n2); gen(n->type); printf("var_part_all "); break;
        case VAR_PART_ALL_3             : out(n->n1); out(n->n2); out(n->n3); gen(n->type); printf("var_part_all "); break;
        case VAR_IDENT                  : gen(IDENTIFIER); printf("var_ident "); break;
        case DIM_ST_1                   : out(n->n1); gen(n->type); printf("{dim}* "); break;
        case DIM_ST_2                   : out(n->n1); out(n->n2); gen(n->type); printf("{dim}* "); break;
        case ARRAY_PART                 : out(n->n1); gen(n->type); printf("array_part "); break;
        case DIM                        : gen(n->type); printf("dim "); break;
        case INIT_PART                  : out(n->n1); gen(n->type); printf("init_part "); break;
        case CONSTANT_1                 : out(n->n1); gen(n->type); printf("constant "); break;
        case CONSTANT_2                 : out(n->n1); gen(n->type); printf("constant(+) "); break;
        case CONSTANT_3                 : out(n->n1); gen(n->type); printf("constant(-) "); break;
        case UNSIGNED_CONSTANT          : out(n->n1); gen(n->type); printf("unsigned_constant "); break;
        case CHAR_CONSTANT              : gen(n->type); printf("char_constant "); break;
        case INT_CONSTANT               : gen(n->type); printf("int_constant "); break;
        case FLOAT_CONSTANT		: gen(n->type); printf("float_constant "); break;
        case COMPLEX_CONSTANT_OPT       : out(n->n1); gen(n->type); printf("complex_constant_opt "); break;
        case COMPLEX_CONSTANT_ST_1      : out(n->n1); gen(n->type); printf("{complex_constant}* "); break;
        case COMPLEX_CONSTANT_ST_2      : out(n->n1); out(n->n2); gen(n->type); printf("{complex_constant}* "); break;
        case COMPLEX_CONSTANT_1         : out(n->n1); out(n->n2); gen(n->type); printf("complex_constant "); break;
        case COMPLEX_CONSTANT_2         : out(n->n1); gen(n->type); printf("complex_constant "); break;
        case FUNC_DECL                  : out(n->n1); gen(n->type); printf("func_decl "); break;
        case PROTOTYPE_1                : out(n->n1); out(n->n2); gen(n->type); printf("prototype "); break;
        case PROTOTYPE_2                : out(n->n1); out(n->n2); out(n->n3); gen(n->type); printf("prototype "); break;
        case PROTOTYPE_3                : out(n->n1); out(n->n2); gen(n->type); printf("prototype "); break;
        case PROTOTYPE_4                : out(n->n1); out(n->n2); out(n->n3); gen(n->type); printf("prototype "); break;
        case PROTOTYPE_5                : out(n->n1); gen(n->type); printf("prototype "); break;
        case PROTOTYPE_6                : out(n->n1); out(n->n2); gen(n->type); printf("prototype "); break;
        case RET_TYPE                   : out(n->n1); gen(n->type); printf("ret_type "); break;
        case FUNC_IDENT                 : gen(IDENTIFIER); printf("func_ident "); break;
        case PAR_TYPE_ST_1              : out(n->n1); gen(n->type); printf("{par_type}* "); break;
        case PAR_TYPE_ST_2              : out(n->n1); out(n->n2); gen(n->type); printf("{par_type}* "); break;
        case PAR_TYPE_1                 : out(n->n1); gen(n->type); printf("par_type "); break;
        case PAR_TYPE_2                 : out(n->n1); gen(n->type); printf("par_type "); break;
        case IMPLEMENTATION_1           : out(n->n1); out(n->n2); out(n->n3); gen(n->type); printf("implementation "); break;
        case IMPLEMENTATION_2           : out(n->n1); out(n->n2); out(n->n3); out(n->n4); out(n->n5); gen(n->type); printf("implementation "); break;
        case IMPLEMENTATION_3           : out(n->n1); out(n->n2); out(n->n3); gen(n->type); printf("implementation "); break;
        case IMPLEMENTATION_4           : out(n->n1); out(n->n2); out(n->n3); out(n->n4); out(n->n5); gen(n->type); printf("implementation "); break;
        case IMPLEMENTATION_5           : out(n->n1); out(n->n2); gen(n->type); printf("implementation "); break;
        case IMPLEMENTATION_6           : out(n->n1); out(n->n2); out(n->n3); out(n->n4); gen(n->type); printf("implementation "); break;
        case PAR_DECL_ST_1              : out(n->n1); gen(n->type); printf("{par_decl}* "); break;
        case PAR_DECL_ST_2              : out(n->n1); out(n->n2); gen(n->type); printf("{par_decl}* "); break;
        case PAR_DECL                   : out(n->n1); out(n->n2); gen(n->type); printf("par_decl "); break;
        case PAR_IDENT                  : gen(IDENTIFIER); printf("par_ident "); break;
        case BLOCK                      : out(n->n1); out(n->n2); gen(n->type); printf("block "); break;
        case STM_ST_1                   : out(n->n1); gen(n->type); printf("{stm}* "); break;
        case STM_ST_2                   : out(n->n1); out(n->n2); gen(n->type); printf("{stm}* "); break;
        case STM                        : out(n->n1); gen(n->type); printf("stm "); break;
        case EMPTY                      : gen(n->type); printf("empty "); break;
        case EXPR                       : out(n->n1); gen(n->type); printf("expr "); break;
        case BREAK                      : gen(n->type); printf("break "); break;
        case RETURN_1                   : gen(n->type); printf("return "); break;
        case RETURN_2                   : out(n->n1); gen(n->type); printf("return "); break;
        case IF_1                       : out(n->n1); out(n->n2); gen(n->type); printf("if "); break;
        case IF_2                       : out(n->n1); out(n->n2); out(n->n3); gen(n->type); printf("if "); break;
        case COND                       : out(n->n1); gen(n->type); printf("cond "); break;
        case SWITCH                     : out(n->n1); out(n->n2); out(n->n3); gen(n->type); printf("switch "); break;
        case CASE_ST_1                  : out(n->n1); gen(n->type); printf("{case}* "); break;
        case CASE_ST_2                  : out(n->n1); out(n->n2); gen(n->type); printf("{case}* "); break;
        case CASE                       : out(n->n1); out(n->n2); out(n->n3); gen(n->type); printf("case "); break;
        case CASE_LABEL_1               : out(n->n1); gen(n->type); printf("case_label "); break;
        case CASE_LABEL_2               : gen(n->type); printf("case_label "); break;
        case WHILE                      : out(n->n1); out(n->n2); gen(n->type); printf("while "); break;
        case COMPOUND                   : out(n->n1); out(n->n2); gen(n->type); printf("compound "); break;
        case EXPRESSION_ST_1            : out(n->n1); gen(n->type); printf("{expression}* "); break;
        case EXPRESSION_ST_2            : out(n->n1); out(n->n2); gen(n->type); printf("{expression}* "); break;
        case EXPRESSION_1               : out(n->n1); gen(n->type); printf("expression "); break;
        case EXPRESSION_2               : out(n->n1); out(n->n2); gen(n->type); printf("expression "); break;
        case EQUALITY_1                 : out(n->n1); gen(n->type); printf("equality "); break;
        case EQUALITY_2                 : out(n->n1); out(n->n2); gen(n->type); printf("equality(==) "); break;
        case EQUALITY_3                 : out(n->n1); out(n->n2); gen(n->type); printf("equality(!=) "); break;
        case RELATION_1                 : out(n->n1); gen(n->type); printf("relation "); break;
        case RELATION_2                 : out(n->n1); out(n->n2); gen(n->type); printf("relation(<) "); break;
        case RELATION_3                 : out(n->n1); out(n->n2); gen(n->type); printf("relation(>) "); break;
        case RELATION_4                 : out(n->n1); out(n->n2); gen(n->type); printf("relation(<=) "); break;
        case RELATION_5                 : out(n->n1); out(n->n2); gen(n->type); printf("relation(>=) "); break;
        case SHIFT_1                    : out(n->n1); gen(n->type); printf("shift "); break;
        case SHIFT_2                    : out(n->n1); out(n->n2); gen(n->type); printf("shift(<<) "); break;
        case SHIFT_3                    : out(n->n1); out(n->n2); gen(n->type); printf("shift(>>) "); break;
        case ADD_SUB_1                  : out(n->n1); gen(n->type); printf("add_sub "); break;
        case ADD_SUB_2                  : out(n->n1); out(n->n2); gen(n->type); printf("add_sub(+) "); break;
        case ADD_SUB_3                  : out(n->n1); out(n->n2); gen(n->type); printf("add_sub(-) "); break;
        case MULT_DIV_1                 : out(n->n1); gen(n->type); printf("mult_div "); break;
        case MULT_DIV_2                 : out(n->n1); out(n->n2); gen(n->type); printf("mult_div(*) "); break;
        case MULT_DIV_3                 : out(n->n1); out(n->n2); gen(n->type); printf("mult_div(/) "); break;
        case MULT_DIV_4                 : out(n->n1); out(n->n2); gen(n->type); printf("mult_div(p) "); break;
        case PRIMITIVE_1                : out(n->n1); gen(n->type); printf("primitive "); break;
        case PRIMITIVE_2                : out(n->n1); gen(n->type); printf("primitive(+) "); break;
        case PRIMITIVE_3                : out(n->n1); gen(n->type); printf("primitive(-) "); break;
        case PRIMITIVE_4                : out(n->n1); gen(n->type); printf("primitive "); break;
        case OPERAND                    : out(n->n1); gen(n->type); printf("operand "); break;
        case VARIABLE                   : out(n->n1); out(n->n2); gen(n->type); printf("variable "); break;
        case QUALIFYING_1               : out(n->n1); gen(n->type); printf("qualifying "); break;
        case QUALIFYING_2               : out(n->n1); out(n->n2); gen(n->type); printf("qualifying "); break;
        case QUALIFYING_3               : out(n->n1); out(n->n2); out(n->n3); gen(n->type); printf("qualifying "); break;
        case FUNCTION_CALL_1            : out(n->n1); gen(n->type); printf("function_call "); break;
        case FUNCTION_CALL_2            : out(n->n1); out(n->n2); out(n->n3); gen(n->type); printf("function_call "); break;
        case EPSILON                    : gen(n->type); printf("epsilon "); break;
    }
  }
}

void gen(unsigned u)
{
	*pos = u;
	if (u==IDENTIFIER) pos++; // Platz lassen für Namenslistenindex des Identifiers
	pos++;
}


int yyerror(char* s)
{
  printf("[parser] %s\n",s);
  exit(-1);
  return 0;
}

