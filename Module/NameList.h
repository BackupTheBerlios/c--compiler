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

	// Einfügen einer neuen Variable
	unsigned insert(char*, unsigned, TType, unsigned, bool);

	// gibt den Typ einer Variablen mit bestimmten Namen in einem bestimmten Block zurück
	TType typeOf(char*, unsigned);

	// gibt zurück, ob die Variable im übergebenen Block definiert ist
	unsigned isDefined(char*, unsigned);

	// gibt die Namensliste aus
	void out();

	// gibt den Namen der Variable mit dem übergebenen Index zurück
	char* getIdent(unsigned);

	// gibt die Blocknummer der Variable mit dem übergebenen Index zurück
	unsigned getBlock(unsigned);

	// gibt den Typ der Variable mit dem übergebenen Index zurück
	TType getType(unsigned);

	// gibt die Adresse der Variable mit dem übergebenen Index zurück
	unsigned getAddr(unsigned);

	// gibt zurück ob die Variable mit dem übergebenen Index global ist
	bool isGlobal(unsigned);


private:
	struct TNameListEntry* start;
	struct TNameListEntry* last;
	unsigned no;


};


#endif
