#ifndef list_h
#define list_h
#include "OTypes.h"

class List
{
public:

struct TListEntry
{
	struct TOp* op;
	struct TListEntry* next;
};

List();

void del (unsigned n);
void append (struct TOp*);
struct TOp* getelem(unsigned n);	// n startet bei 1
unsigned count();
void out();

private:
	
	unsigned elems;
	struct TListEntry* start;
	struct TListEntry* end;
};

#endif
