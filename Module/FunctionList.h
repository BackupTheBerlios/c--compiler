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

	// Einf�gen einer neuen Funktion
	unsigned insert(char*, TType*, TType, unsigned, bool, unsigned, unsigned, unsigned );

	// gibts zur�ck ob die �bergebene Funktion definiert ist
	unsigned isDefined(char*, unsigned, bool);

	// Ausgabe der Funktionsliste
	void out();

	// gibt den Namen der Funktion mit dem �bergebenen Index zur�ck
	char* getIdent(unsigned);

	// gibt die Anzahl der Parameter der Funktion mit dem �bergebenen Index zur�ck
	unsigned getNum(unsigned);

	// gibt den n�chsten freien Index zur�ck
	unsigned nextId();

	// gibt zur�ck, ob es sich bei der �bergebene Funktion um einen Prototyp handelt
	unsigned isProto(char*, unsigned);

	// gibt den Typ eines bestimmten Parameters zur�ck
	TType getSigType(unsigned, unsigned);

	// gibt den R�ckgabetyp zur�ck
	TType getReturnType(unsigned);

	// schaut in der Liste, ob es noch Funktionen ohne zugeh�rige Implementierung gibt
	char* checkForUnImplemented();

	// gibt die Framegr�ssen-Konstante zur�ck
	unsigned getFrameConstant(unsigned);

	// gibt die Signaturgr�ssen-Konstante zur�ck
	unsigned getSigConstant(unsigned);

	// setzt die Adresse der Variable des x-ten Parameters
	void setParaAdd(unsigned, unsigned, unsigned);

	// gibt die Adresse der Variable des x-ten Parameters zur�ck
	unsigned getParaAdd(unsigned, unsigned);

	// setzt die main-Funktion auf einen bestimmten index
	void setMainFunc(unsigned i) { mainfunc = i; }

	// gibt den Index der main-Funktion zur�ck
	unsigned getMainFunc() { return mainfunc; }


private:

	struct TFunctionListEntry* last;
	struct TFunctionListEntry* start;
	unsigned no;
	unsigned mainfunc;
	Stack par;

};




#endif
