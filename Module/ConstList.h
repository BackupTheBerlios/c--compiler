#ifndef constlist_h
#define constlist_h
#include "OTypes.h"

class ConstList
{
public:

union tvalue
{
	int i;
	double f;
	unsigned u;
	char c;
};

struct TConstListEntry
{
	tvalue val;
	TType t;
	struct TConstListEntry* next;
	unsigned ct;
	unsigned add;
};

ConstList();

// fügt eine neue Char-Konstante ein
void insert(char, unsigned);

// fügt eine neue Int-Konstante ein
void insert(int, unsigned);

// fügt eine neue float-Konstante ein
void insert(double, unsigned);

// gibt die Adresse des übergebenen Elements zurück
unsigned getAddr(unsigned);

// gibt den Wert des übergebnen Elements zurück
tvalue getValue(unsigned);

// gibt den Typ des übergebnen Elements zurück
TType getType(unsigned);

// gibt die Konstantenliste aus
void out();

// Hilfsfunktion fürs alignment
unsigned align(unsigned, unsigned);

// Gibt die Grösse zurück, die für alle Konstanten benötigt wird
unsigned getSize();

// Gibt die Anzahl der Konstanten zurueck
unsigned getCount();

// gibt den Wert einer char Konstanten zurück
char* getVal(unsigned);

// gibt den Wert einer Int Konstanten zurück
int getIntVal(unsigned);

private:
	
	struct TConstListEntry* last;
	unsigned curadd;
	unsigned nmb;
	
};




#endif
