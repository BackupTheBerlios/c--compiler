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
};

ConstList();

void insert(char, unsigned);

void insert(int, unsigned);

void insert(double, unsigned);

tvalue getValue(unsigned);

TType getType(unsigned);

void out();


private:
	
	struct TConstListEntry* last;
	
};




#endif
