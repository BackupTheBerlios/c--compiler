#ifndef register_h
#define register_h
#include "OTypes.h"
#include <iostream>
using namespace std;

#define regmax 3

struct TRegEntry
{
	char* var;
	unsigned mark; // wann zuletzt benutzt
};

class Register
{
public:

Register();

// beschaft ein Register für die uebergebene temporaere Variable
TReg getReg(char*);

// welches Register belegt diese Variable?
TReg whichReg(char*);

// gibt das Register wieder frei
void freeReg(char*);

void out();

private:

TRegEntry reglist[regmax];
unsigned mark;


};
#endif
