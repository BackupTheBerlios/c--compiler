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
	TType type;
	
	
};

NameList();

unsigned insert(char*, unsigned, TType);

TType typeOf(char*, unsigned);

unsigned isDefined(char*, unsigned);

void out();

char* getIdent(unsigned);

unsigned getBlock(unsigned);

TType getType(unsigned);


private:
	struct TNameListEntry* start;
	struct TNameListEntry* last;
	unsigned no;
	
	
};




#endif
