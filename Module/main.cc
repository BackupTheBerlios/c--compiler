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

ConstList cl;  // Konstantenliste
ConstList icl; //interne Konstantenliste, zb. Framegroessen, ect.
NameList nl; // Namensliste
FunctionList fl; // Funktionsliste
Context c;
IL il;
List ilList;
Bacom bc;
ofstream bsm;
ofstream spilldata;


int main(int argc, char* arv[])
{
	char* ifile, *ofile;
	bool basm = false;
	bool bac = false;
	bool info = false;
	
	// Auswertung der Kommandozeilenargumente
	if (argc>1) ifile = arv[1];
	else 
	{
		cout<<"[main] no input file\n";
		info = true;
	}
	if (argc>2) ofile = arv[2];
	else 
	{
		cout<<"[main] no output file\n";
		info = true;
	}
	if (argc>3)
	{
		if (strcmp(arv[3], "-a")==0) basm = true;
		else if (strcmp(arv[3], "-b")==0) { basm = true; bac = true; } 
		else 
		{
			cout<<"[main] unknown option\n";
			info = true;
		}
	}
	
	// Ausgabe des Infotextes
	if (info)
	{
		cout<<"Usage:  inputfile outputfile [-a | -b]\n";
		cout<<"-a for assemble\n";
		cout<<"-b for assemble and execute\n";
		exit(-1);
	}
	
	
	// Dateien öffnen
	bsm.open(ofile);
	spilldata.open("spill");
	yyin = fopen(ifile,"r+");
	
	// Parser starten
	yyparse();
	cout<<"\n[parser] OK\n";
	//fclose(yyin);
	
	// Kontextprüfung starten
	c.context(root);  
	cout<<"\n[context] OK\n";
	
	// Zwischencodeerzeugung starten
	il.genIL(start, pos);
	cout<<"\n[code-il] OK\n";
	
	// Bacom Zielcodeerzeugung starten
	bc.genAsm();
	cout<<"\n[bacom] OK\n";
	bsm.close();
	spilldata.close();
	
	// Ausführung von basm / bacom
	// Kommandozeilen zusammenbasteln
	char* f = (char*)malloc(50);
	strcpy(f, "cat spill>>");
	strcpy(f+11, ofile);
	system(f);
	system("rm spill");
		
	if (basm)
	{
		char* f = (char*)malloc(50);
		strcpy(f, "basm ");
		strcpy(f+5, ofile);
		system(f);
		if (bac)
		{
		
			char* n = strrchr(ofile, '.');
			strcpy( n+1, "pro");
			strcpy( f, "bacom ");
			strcpy( f+6, ofile );
			system(f);
		}
	}
}



