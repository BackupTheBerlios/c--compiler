#ifndef IL_h
#define IL_h
#include "OTypes.h"
#include "NameList.h"
#include "ConstList.h"
#include "FunctionList.h"
#include "Stack.h"
#include "List.h"
#include <iostream>
using namespace std;

/*
 * Diese Klasse generiert eine Zwischensprache
 * in Form von 3 Adress Code Anweisungen.
 *
 */
extern NameList nl;
extern ConstList cl;
extern FunctionList fl;
extern List ilList;

class IL
{
public:



IL();

char* genIL(unsigned*, unsigned*);


private:

	TOperand* varid(unsigned);
	
	TOperand* conid(unsigned);
	
	TOperand* tempid(TType);
	
	TOperand* labelid();

	TOperand* condlabelid();

	TOperand* funcid(unsigned);	
	
	void outcopy(TOperand*, TOperand*);
	
	void outbin(TOperand*, TOperand*, TBinOp, TOperand*);
	
	void outun(TOperand*, TUnOp, TOperand*);

	void outgoto(TOperand*, bool);
	
	void outlabel(TOperand*);

	void outjump(TOperand*,TOperand*,TJmp);
	
	void outret(TOperand*, TOperand*);
	
	void outgetret(TOperand*);
	
	void outpush(TOperand*);
	
	void outconvert(TOperand*, TOperand*, TType);
	
	void outio(TOpType, TOperand*, TOperand*);	// fuer Ausgabe
	
	void outio(TOpType, TOperand*);			// fuer Eingabe
	
	void outstop();
	
	TType checkConvAssign(TOperand*&, TOperand*&);
	
	TType checkConv(TOperand*&, TOperand*&);
	
	
	Stack op;
	Stack label;
	Stack cond;
	Stack breakst;
	bool condition;
	unsigned condinsert;
	unsigned tempcount;
	unsigned labelcount;
	unsigned condlabelcount;

};





#endif
