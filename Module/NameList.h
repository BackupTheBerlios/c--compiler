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
	unsigned add;
	bool isGlobal;
	
};

NameList();

unsigned insert(char*, unsigned, TType, unsigned, bool);

TType typeOf(char*, unsigned);

unsigned isDefined(char*, unsigned);

void out();

char* getIdent(unsigned);

unsigned getBlock(unsigned);

TType getType(unsigned);

unsigned getAddr(unsigned);

bool isGlobal(unsigned);


private:
	struct TNameListEntry* start;
	struct TNameListEntry* last;
	unsigned no;
	
	
};




#endif
