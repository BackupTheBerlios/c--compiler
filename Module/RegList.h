#ifndef reglist_h
#define reglist_h
#include "OTypes.h"
#include <iostream>
#include <fstream>
using namespace std;

extern ofstream bsm;
extern ofstream spilldata;

class RegList
{
public:

struct TRegListEntry
{
	struct TOperand* op;
	char* label;
	struct TRegListEntry* next;
};

RegList();

void append (struct TOperand*, char*);
void append (struct TOperand*, TReg);
bool del (struct TOperand*);
bool isValid (struct TOperand*);
char* where (struct TOperand*);

void invalidate();
unsigned count();


// void insert (struct TOperand*, unsigned n);	// element wird an n gesetzt
// struct TOperand* getelem(struct TOperand*);	// Schreibt das Re
// void out();

private:
	
	unsigned elems;
	struct TRegListEntry* start;
	struct TRegListEntry* end;
	unsigned maxcount;
};

#endif
