#ifndef IL_h
#define IL_h
#include "OTypes.h"
#include "NameList.h"
#include "ConstList.h"
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


class IL
{
public:



IL();

char* genIL(unsigned*, unsigned*);


private:

	char* varid(unsigned);
	
	char* conid(unsigned);
	
	char* tempid();
	
	void outcopy(char*, char*);
	
	void outbin(char*, char*, TBinOp, char*);
	
	void outun(char*, TUnOp, char*);
	
	Stack op;
	unsigned tempcount;

};





#endif
