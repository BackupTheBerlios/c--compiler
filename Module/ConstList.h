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

// f�gt eine neue Char-Konstante ein
void insert(char, unsigned);

// f�gt eine neue Int-Konstante ein
void insert(int, unsigned);

// f�gt eine neue float-Konstante ein
void insert(double, unsigned);

// gibt die Adresse des �bergebenen Elements zur�ck
unsigned getAddr(unsigned);

// gibt den Wert des �bergebnen Elements zur�ck
tvalue getValue(unsigned);

// gibt den Typ des �bergebnen Elements zur�ck
TType getType(unsigned);

// gibt die Konstantenliste aus
void out();

// Hilfsfunktion f�rs alignment
unsigned align(unsigned, unsigned);

// Gibt die Gr�sse zur�ck, die f�r alle Konstanten ben�tigt wird
unsigned getSize();

// Gibt die Anzahl der Konstanten zurueck
unsigned getCount();

// gibt den Wert einer char Konstanten zur�ck
char* getVal(unsigned);

// gibt den Wert einer Int Konstanten zur�ck
int getIntVal(unsigned);

private:
	
	struct TConstListEntry* last;
	unsigned curadd;
	unsigned nmb;
	
};




#endif
