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
 * Diese Klasse f�hrt die Kontextpr�fung durch.
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
	

private:
	
	Stack b;      //Blocknummern-Stack
	Stack s;      //Variablen-Ident-Stack
	Stack f;      //Funktions-Ident-Stack
	Stack ft;     // Funktions-Typen-Stack
	Stack par;    //Parameter-Stack
	Stack stype;  //typen-stack
	
	Stack pro;  // Protypen-ident
	char* lasttype;  //letzter Basistyp
	
	unsigned* cpos;
	int cblock;     // aktueller block
	int blockmax;   // letzte vergebene blocknummer
	int decl;       // variablendeklarationsz�hler
	bool func;   // funcdecl ?
	bool retu;   // return Statement?
	int ex;          // expression count
	bool proto;  // prototype
	bool call;    // func-call?
	unsigned cc; //Konstenzaehler
	
	




};





#endif
