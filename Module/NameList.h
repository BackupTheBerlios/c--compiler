#ifndef namelist_h
#define namelist_h

#include "OTypes.h"

class NameList
{
public:


struct TNameListEntry
{
	char* name;
	unsigned block;
	char* ttype;
	
	
};

NameList();

unsigned insert(char*, unsigned, char*);

char* typeOf(char*, unsigned);

unsigned isDefined(char*, unsigned);

void out();

char* getIdent(unsigned);

unsigned getBlock(unsigned);


private:
	struct TNameListEntry* start;
	struct TNameListEntry* last;
	unsigned no;
	
	
};




#endif
