#ifndef bacom_h
#define bacom_h
#include "OTypes.h"
#include "List.h"
#include "ConstList.h"
#include "Register.h" 
#include <iostream>
using namespace std;

extern List ilList;
extern ConstList cl;

class Bacom
{
public:

	void genAsm();

private:

	void outstp();
	void outinp(TType, TReg);
	void outout(TType, TReg);
	void outcvt(TType, TReg, TReg);
	void outlic(TReg, TReg);
	void outbra(char*);
	void outble(char*);
	void outbeq(char*);
	void outbgr(char*);
	void outbne(char*);
	void outmov(TReg, TReg);
	void outloa(TType, TReg, TReg, int);
	void outloa(TType, TReg, TReg, char*);
	void outstr(TType, TReg, TReg, int);
	void outstr(TType, TReg, TReg, char*);
	void outshl(TType, TReg, TReg);
	void outshr(TType, TReg, TReg);
	void outadd(TType, TReg, TReg);
	void outsub(TType, TReg, TReg);
	void outmul(TType, TReg, TReg);
	void outdiv(TType, TReg, TReg);
	void outnop();
	void outds(TType);
	void outdc(char);
	void outdc(TType, int);
	void outdc(float);
	
	Register regs;
	
	
};





#endif
