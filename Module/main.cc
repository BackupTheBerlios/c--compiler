#include <iostream>
#include <istream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "Context.h"
#include "IL.h"
#include "NameList.h"
#include "ConstList.h"
using namespace std;

extern void yyparse();
extern struct TNode* root;
extern unsigned* start;
extern unsigned* pos;

extern FILE *yyin, *yyout;

ConstList cl;
NameList nl;
Context c;
IL il;


int main(int argc, char* arv[])
{
	system("cat include test.cc > parserfile.cc");
	
	yyin = fopen("parserfile.cc","r+");
	
	yyparse();
	cout<<"\n[parser] OK\n";
	//fclose(yyin);
	
	c.context(root);  
	cout<<"\n[context] OK\n";
	
	il.genIL(start, pos);
	cout<<"\n[code-il] OK\n";
	
}



