#ifndef functionlist_h
#define functionlist_h

#include "OTypes.h"

class FunctionList
{
public:


struct TFunctionListEntry
{
	char* name;
	char* signature;
	char* rettype;
	unsigned num;
	struct TFunctionListEntry* next;
	bool proto;
};

FunctionList();

unsigned insert(char*, char*, char*, unsigned, bool);

unsigned isDefined(char*, unsigned, bool);

void out();

char* getIdent(unsigned);

unsigned getNum(unsigned);

unsigned nextId();

private:
	
	struct TFunctionListEntry* last;
	struct TFunctionListEntry* start;
	unsigned no;
	
};




#endif
