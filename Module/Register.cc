#include "Register.h"

Register::Register()
{
	mark = 0;
}

TReg Register::getReg(char* temp)
{
	unsigned i;
	bool found = false;
	unsigned minmark = 0xFFFFFFFF;
	unsigned minpos;
	for(i=0; i<regmax; i++)
	{
		if (reglist[i].var==0) 
		{
			found = true;
			break;
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
	return (found?unknown:(TReg)i);
}

void Register::freeReg(char* temp)
{
	for(int i=0; i<regmax; i++)
	{
		if (strcmp(reglist[i].var, temp)==0) 
		{
			reglist[i].var = 0;
			reglist[i].mark = 0;
			return;
		}
	}
	cout<<"freeReg() error\n";
}

TReg Register::whichReg(char* temp)
{
	for(int i=0; i<regmax; i++)
	{
		if (strcmp(reglist[i].var, temp)==0)  
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
	for(int i=0; i<regmax; i++)
	{
		if (reglist[i].var!=0) cout<<i<<" "<<reglist[i].var<<endl;
	}
}


