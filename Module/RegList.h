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
		char* label;			// Stelle, an der der Operand gespeichert wird
		struct TRegListEntry* next;
	};

	RegList();

	void append (struct TOperand*, char*);	// anhaengen mit Speicherstelle (wird von changeReg aufgerufen, Zuordnung wird nur geandert)
	void append (struct TOperand*, TReg);	// anhaengen mit Register
	bool del (struct TOperand*);		// loeschen, gibt false zurueck, falls nicht vorhanden
	bool isValid (struct TOperand*);	// prueft, ob der Operand vorhanden ist
	char* where (struct TOperand*);		// gibt das Label zurueck, an dem der Operand gespeichert ist

	void invalidate();			// alle loeschen
	void out();
	unsigned count();

private:

	unsigned elems;
	struct TRegListEntry* start;
	struct TRegListEntry* end;
	unsigned maxcount;
};

#endif
