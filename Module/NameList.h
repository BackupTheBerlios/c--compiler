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

// Einf�gen einer neuen Variable
unsigned insert(char*, unsigned, TType, unsigned, bool);

// gibt den Typ einer Variablen mit bestimmten Namen in einem bestimmten Block zur�ck
TType typeOf(char*, unsigned);

// gibt zur�ck, ob die Variable im �bergebenen Block definiert ist
unsigned isDefined(char*, unsigned);

// gibt die Namensliste aus
void out();

// gibt den Namen der Variable mit dem �bergebenen Index zur�ck
char* getIdent(unsigned);

// gibt die Blocknummer der Variable mit dem �bergebenen Index zur�ck
unsigned getBlock(unsigned);

// gibt den Typ der Variable mit dem �bergebenen Index zur�ck
TType getType(unsigned);

// gibt die Adresse der Variable mit dem �bergebenen Index zur�ck
unsigned getAddr(unsigned);

// gibt zur�ck ob die Variable mit dem �bergebenen Index global ist
bool isGlobal(unsigned);


private:
	struct TNameListEntry* start;
	struct TNameListEntry* last;
	unsigned no;
	
	
};


#endif
