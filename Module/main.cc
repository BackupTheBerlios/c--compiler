#include <iostream>
#include <istream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "Context.h"
#include "IL.h"
#include "NameList.h"
#include "ConstList.h"
#include "FunctionList.h"
#include "List.h"
#include "Bacom.h"
using namespace std;

extern void yyparse();
extern struct TNode* root;
extern unsigned* start;
extern unsigned* pos;

extern FILE *yyin, *yyout;

ConstList cl;
ConstList icl; //interne Konstantenliste, zb. Framegroessen, ect.
NameList nl;
FunctionList fl;
Context c;
IL il;
List ilList;
Bacom bc;

int main(int argc, char* arv[])
{
	system("cat test.cc > parserfile.cc");
	
	yyin = fopen("parserfile.cc","r+");
	
	yyparse();
	cout<<"\n[parser] OK\n";
	//fclose(yyin);
	
	c.context(root);  
	cout<<"\n[context] OK\n";
	
	il.genIL(start, pos);
	cout<<"\n[code-il] OK\n";
	
	bc.genAsm();
	cout<<"\n[bacom] OK\n";
	
}



