#ifndef stack_h
#define stack_h

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
	struct TStackEntry* next;
};


Stack();

void pop (int n);


void push (char* name);
void push (unsigned block);

char* top ();
unsigned topi (unsigned);

char* first ();
unsigned firsti ();

void out();

unsigned count();
	
	

private:
	
	struct TStackEntry* tos;
	struct TStackEntry* start;
	
	
};




#endif
