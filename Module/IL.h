#ifndef IL_h
#define IL_h
#include "OTypes.h"
#include "NameList.h"
#include "ConstList.h"
#include "FunctionList.h"
#include "Stack.h"
#include <iostream>
using namespace std;

/*
 * Diese Klasse generiert eine Zwischensprache
 * in Form von 3 Adress Code Anweisungen.
 *
 */
extern NameList nl;
extern ConstList cl;
extern FunctionList fl;

class IL
{
public:



IL();

char* genIL(unsigned*, unsigned*);
void pushLabel(bool);


private:

	char* varid(unsigned);
	
	char* conid(unsigned);
	
	char* tempid();
	
	char* labelid();

	char* funcid(unsigned);	
	
	void outcopy(char*, char*);
	
	void outbin(char*, char*, TBinOp, char*);
	
	void outun(char*, TUnOp, char*);

	void outgoto(char*, bool);
	
	void outlabel(char*);
	
	void outret(char*);
	
	void outpush(char *);
	
	Stack op;
	Stack label;
	unsigned tempcount;
	unsigned labelcount;
// 	unsigned labelin;
// 	unsigned labelout;

};





#endif
