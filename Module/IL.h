#ifndef IL_h
#define IL_h
#include "OTypes.h"
#include "NameList.h"
#include "ConstList.h"
#include "FunctionList.h"
#include "Stack.h"
#include "List.h"
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


private:

	char* varid(unsigned);
	
	char* conid(unsigned);
	
	char* tempid();
	
	char* labelid();

	char* condlabelid();

	char* funcid(unsigned);	
	
	void outcopy(char*, char*);
	
	void outbin(char*, char*, TBinOp, char*);
	
	void outun(char*, TUnOp, char*);

	void outgoto(char*, bool);
	
	void outlabel(char*);

	void outjump(char*,char*,TJmp);
	
	void outret(char*);
	
	void outpush(char*);
	
	void outconvert(char*, char*, TType);
	
	TType checkConvAssign(char*&, TType, TType);
	
	TType checkConv(char*&, char*&, TType, TType);
	
	List ilList;
	
	Stack op;
	Stack label;
	Stack cond;
	bool condition;
	unsigned condinsert;
	unsigned tempcount;
	unsigned labelcount;
	unsigned condlabelcount;

};





#endif
