#ifndef register_h
#define register_h
#include "OTypes.h"
#include <iostream>
using namespace std;

#define regmax 16     // Gesamtanzahl der Register
#define regusable 13  // Anzahl frei nutzbarer Register

struct TRegEntry
{
	TOperand* var;  // von welcher temp. Variable belegt?
	unsigned mark; // wann zuletzt benutzt
};

class Register
{
public:

Register();

// beschaft ein Register für die uebergebene temporaere Variable, Register steht im Argument
// Rückgabe ist das Register, welches freigemacht wurde
TReg getReg(TOperand*, TReg&);

// welches Register belegt diese Variable?
TReg whichReg(TOperand*);

// gibt das Register wieder frei
void freeReg(TOperand*);

static TReg typeToReg(TOperandType);

void out();

static char* toString(TReg);

private:

TRegEntry reglist[regmax];
unsigned mark;


};
#endif
