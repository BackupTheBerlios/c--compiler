#ifndef functionlist_h
#define functionlist_h

#include "OTypes.h"
#include "Stack.h"

class FunctionList
{
public:


	struct TFunctionListEntry
	{
		char* name;
		TType* signature;
		TType rettype;
		unsigned num;
		struct TFunctionListEntry* next;
		bool proto;
		unsigned maxsp; // Groesse des Variablensblocks im lokalen Frame
		unsigned frame_constant;
		unsigned sig_constant;
		unsigned para[MAX_NO_OF_PARAMETERS];
	};

	FunctionList();

	// Einfügen einer neuen Funktion
	unsigned insert(char*, TType*, TType, unsigned, bool, unsigned, unsigned, unsigned );

	// gibts zurück ob die übergebene Funktion definiert ist
	unsigned isDefined(char*, unsigned, bool);

	// Ausgabe der Funktionsliste
	void out();

	// gibt den Namen der Funktion mit dem übergebenen Index zurück
	char* getIdent(unsigned);

	// gibt die Anzahl der Parameter der Funktion mit dem übergebenen Index zurück
	unsigned getNum(unsigned);

	// gibt den nächsten freien Index zurück
	unsigned nextId();

	// gibt zurück, ob es sich bei der übergebene Funktion um einen Prototyp handelt
	unsigned isProto(char*, unsigned);

	// gibt den Typ eines bestimmten Parameters zurück
	TType getSigType(unsigned, unsigned);

	// gibt den Rückgabetyp zurück
	TType getReturnType(unsigned);

	// schaut in der Liste, ob es noch Funktionen ohne zugehörige Implementierung gibt
	char* checkForUnImplemented();

	// gibt die Framegrössen-Konstante zurück
	unsigned getFrameConstant(unsigned);

	// gibt die Signaturgrössen-Konstante zurück
	unsigned getSigConstant(unsigned);

	// setzt die Adresse der Variable des x-ten Parameters
	void setParaAdd(unsigned, unsigned, unsigned);

	// gibt die Adresse der Variable des x-ten Parameters zurück
	unsigned getParaAdd(unsigned, unsigned);

	// setzt die main-Funktion auf einen bestimmten index
	void setMainFunc(unsigned i) { mainfunc = i; }

	// gibt den Index der main-Funktion zurück
	unsigned getMainFunc() { return mainfunc; }


private:

	struct TFunctionListEntry* last;
	struct TFunctionListEntry* start;
	unsigned no;
	unsigned mainfunc;
	Stack par;

};




#endif
