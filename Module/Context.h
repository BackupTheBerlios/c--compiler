#ifndef context_h
#define context_h
#include "OTypes.h"
#include "Stack.h"
#include "FunctionList.h"
#include "NameList.h"
#include "ConstList.h"
#include <iostream>
using namespace std;

/*
 * Diese Klasse führt die Kontextprüfung durch.
 * 
 */
extern NameList nl;
extern ConstList cl;
extern FunctionList fl;
extern unsigned* start;

class Context
{
public:

	Context();
	
	void context(struct TNode*);
	
	void ins(unsigned);
	
	void insrev(unsigned);
	
	unsigned align(unsigned, unsigned);
	

private:
	
	Stack b;      //Blocknummern-Stack
	Stack s;      //Variablen-Ident-Stack
	Stack f;      //Funktions-Ident-Stack
	Stack ft;     // Funktions-Typen-Stack
	Stack par;    //Parameter-Stack
	Stack stype;  //typen-stack
	
	Stack pro;  // Protypen-ident
	TType lasttype;  //letzter Basistyp
	
	unsigned* cpos;
	unsigned cblock;     // aktueller block
	unsigned blockmax;   // letzte vergebene blocknummer
	unsigned decl;       // variablendeklarationszähler
	bool func;   // funcdecl ?
	bool retu;   // return Statement?
	unsigned ex;          // expression count
	bool proto;  // prototype
	bool call;    // func-call?
	unsigned cc; //Konstenzaehler
	bool minus; // minuszeichen?
	unsigned sp; // der quasi-stackpointer (zur Adressberechnung)
	unsigned gp; // pointer fuer globale variablen (auch zur Adressberechnung)
	Stack bl; // Speichergroesse der Bloecke
	unsigned maxsp; // max. grosse des Speicherbereichs einer Funktion
	
	unsigned caselabels[MAX_NO_OF_CASE_LABELS];
	unsigned labelcount;
	Stack startcount;
	unsigned lastconst;
	unsigned startc;




};





#endif
