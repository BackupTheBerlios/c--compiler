#include "Register.h"

Register::Register()
{
	mark = 0;
}

TReg Register::getReg(TOperand* temp, TReg& r)
{
	unsigned i;
	bool found = false;
	unsigned minmark = 0xFFFFFFFF;
	unsigned minpos;
	for(i=0; i<regusable; i++)
	{
		if (reglist[i].var==0) 
		{
			if (temp->vtype>=slong)
			{
				if ((i<regusable)&&(reglist[i+1].var==0)) 
				{
					found = true;
					break;
				}
			} else
			{
				found = true;
				break;
			}
		}
		if (reglist[i].mark<minmark) 
		{
			minpos = i;
			minmark = reglist[i].mark;
		}
	}
	if (!found) i = minpos;
	reglist[i].var = temp;
	reglist[i].mark = mark++;
	r = (TReg)i;
	return (found?unknown:(TReg)i);
}

void Register::freeReg(TOperand* temp)
{
	for(int i=0; i<regusable; i++)
	{
		if (reglist[i].var == temp) 
		{
			reglist[i].var = 0;
			reglist[i].mark = 0;
			return;
		}
	}
	cout<<"freeReg() error\n";
}

TReg Register::whichReg(TOperand* temp)
{
	for(int i=0; i<regusable; i++)
	{
		if (reglist[i].var == temp)
		{
			reglist[i].mark = mark++;
			return (TReg)i;
		}
	}
	return unknown;
}


void Register::out()
{
	cout<<"Registerausgabe\n";
	for(int i=0; i<regusable; i++)
	{
		if (reglist[i].var!=0) cout<<i<<" "<<reglist[i].var<<endl;
	}
}


char* Register::toString(TReg r)
{
	if (r>regmax-1) cout<<"registerfehler";
	char* n = (char*)malloc(3);
	strcpy(n,"r");
	sprintf (n+1,"%u",r);
	return n;
}

TReg Register::typeToReg(TOperandType t)
{
	if (t==constant) return rconst;
	if (t==gvar) return rglobal;
	if (t==lvar) return rlb;
	return unknown;
}
