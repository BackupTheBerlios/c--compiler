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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 30 "prak.y++"
typedef union YYSTYPE {
  struct TNode* nodep;
} YYSTYPE;
/* Line 1249 of yacc.c.  */
#line 92 "prak.hh"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



