#ifndef functionlist_h
#define functionlist_h

#include "OTypes.h"

class FunctionList
{
public:


struct TFunctionListEntry
{
	char* name;
	TType* signature;
	TType rettype;
	unsigned num;
	struct TFunctionListEntry* next;
	bool proto;
	unsigned maxsp; // Groesse des Variablensblocks im lokalen Frame
};

FunctionList();

unsigned insert(char*, TType*, TType, unsigned, bool, unsigned);

unsigned isDefined(char*, unsigned, bool);

void out();

char* getIdent(unsigned);

unsigned getNum(unsigned);

unsigned nextId();

unsigned isProto(char*, unsigned);

TType getSigType(unsigned, unsigned);
TType getReturnType(unsigned);

char* checkForUnImplemented();

private:
	
	struct TFunctionListEntry* last;
	struct TFunctionListEntry* start;
	unsigned no;
	
};




#endif
