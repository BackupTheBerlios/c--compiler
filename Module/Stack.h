#ifndef stack_h
#define stack_h
#include "OTypes.h"

class Stack
{
public:

union TStackRet
{
	char* name;
	int block;
};	

struct TStackEntry
{
	TStackRet ret;
	TType type;
	struct TStackEntry* next;
};


Stack();

void pop (int n);


void push (char* name);
void push (unsigned block);
void push (char*, TType);
void push (TType);

char* top ();
unsigned topi (unsigned);
TType toptype();

char* first ();
unsigned firsti ();
TType firsttype();

void out();

unsigned count();
	
	

private:
	
	struct TStackEntry* tos;
	struct TStackEntry* start;
	
	
};




#endif
