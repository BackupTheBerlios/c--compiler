
/*	Praktikum Compilertechnik SS 2004
 *	flexx
 *		
 */
 
%{


#include "prak.hh"
#include "string.h"
#include <iostream>
using namespace std;



const char tstruct[] = "struct";
const char tchar[] = "char";
const char tint[] = "int";
const char tlong[] = "long";
const char tfloat[] = "float";


extern YYSTYPE yylval;
extern int yyparse();
char tident[255];
%}

DIGIT [0-9]
LETTER [A-Z|a-z]
CHARACTER .
ESCAPE "\\"{DIGIT}+

TRENNER [ \n\t]

%%

"/*""/"*([^*/]|[^*]"/"|"*"[^/])*"*"*"*/"	{ /*printf("___multiple-line-comment___");*/ }
"//"[^\n]*"\n"					{ /*printf("___one-line-comment___");*/ }

{DIGIT}+{TRENNER}*"."{TRENNER}*{DIGIT}*{TRENNER}*("e"{TRENNER}*[+-]?{TRENNER}*{DIGIT}+)?	{ double* d = (double*)malloc(sizeof(double)); *d = atof(yytext);  yylval.nodep = (TNode*)d;  return float_lit; }

"struct"				{ yylval.nodep = (TNode*)&tstruct; return _struct; }
"char"					{ yylval.nodep = (TNode*)&tchar; return _char; }
"int"					{ yylval.nodep = (TNode*)&tint; return _int; }
"long"					{ yylval.nodep = (TNode*)&tlong; return _long; }
"float"					{ yylval.nodep = (TNode*)&tfloat; return _float; }
"break"					{ return _break; }
"return"				{ return _return; }
"if"					{ return _if; }
"else"					{ return _else; }
"switch"				{ return _switch; }
"case"					{ return _case; }
"default"				{ return _default; }
"while"					{ return _while; }
"void"					{ return _void; }
"=="					{ return _gl; }
"!="					{ return _ngl; }
">="					{ return _grgl; }
"<="					{ return _klgl; }
"<<"					{ return _shl; }
">>"					{ return _shr; }
("_"|{LETTER})+("_"|{LETTER}|{DIGIT})* 	{ char* c = (char*)malloc(sizeof(char[255])); strcpy(c,yytext); yylval.nodep = (TNode*)c; return ident;}
{DIGIT}+ 				{ yylval.nodep = (TNode*)atoi(yytext); return numb_lit;}
"'"({CHARACTER}|{ESCAPE})"'" 		{ if (yytext[1]=='\\') yylval.nodep = (TNode*)atoi(yytext+2); else yylval.nodep = (TNode*)yytext[1]; return char_lit;}
{TRENNER} 				;
. 					{/*printf("%c",yytext[0]);*/ return yytext[0];}

%%

int yywrap()
{
  	return 1;
}
