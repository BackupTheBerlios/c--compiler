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

void insert(char, unsigned);

void insert(int, unsigned);

void insert(double, unsigned);

unsigned getAddr(unsigned);

tvalue getValue(unsigned);

TType getType(unsigned);

void out();

unsigned align(unsigned, unsigned);

// Gibt die Grösse zurück, die für alle Konstanten benötigt wird
unsigned getSize();


private:
	
	struct TConstListEntry* last;
	unsigned curadd;
	
	
};




#endif
