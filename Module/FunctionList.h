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

unsigned insert(char*, TType*, TType, unsigned, bool, unsigned, unsigned, unsigned );

unsigned isDefined(char*, unsigned, bool);

void out();

char* getIdent(unsigned);

unsigned getNum(unsigned);

unsigned nextId();

unsigned isProto(char*, unsigned);

TType getSigType(unsigned, unsigned);
TType getReturnType(unsigned);

char* checkForUnImplemented();

unsigned getFrameConstant(unsigned);
unsigned getSigConstant(unsigned);

void setParaAdd(unsigned, unsigned, unsigned);
unsigned getParaAdd(unsigned, unsigned);


void setMainFunc(unsigned i) { mainfunc = i; }
unsigned getMainFunc() { return mainfunc; }


private:
	
	struct TFunctionListEntry* last;
	struct TFunctionListEntry* start;
	unsigned no;
	unsigned mainfunc;
	Stack par;
	
};




#endif
