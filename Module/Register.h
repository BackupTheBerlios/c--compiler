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

// beschaft ein Register f�r die uebergebene temporaere Variable, Register steht im Argument
// R�ckgabe ist das Register, welches freigemacht wurde
TReg getReg(TOperand*, TReg&);

// welches Register belegt diese Variable?
TReg whichReg(TOperand*);

// gibt das Register wieder frei
void freeReg(TOperand*);

// aendert Register von einem auf den anderen Operanden, (dst,src)
void changeReg(TOperand*, TOperand*);

// packt den Operanden in ein 4-byte grosses Register
void biggerReg(TOperand*);

// packt den Operanden in ein 2-byte grosses Register
void smallerReg(TOperand*);

// l�scht alle Zuordnungen
void invalidate();

static TReg typeToReg(TOperandType);

void out();

static char* toString(TReg);

private:

TRegEntry reglist[regmax];
unsigned mark;


};
#endif
