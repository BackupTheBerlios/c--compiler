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
				if (i%2==1) continue;		// wenn 4 byte verarbeitungsbreite werden nur gerade register vergeben!
				if ((i<regusable)&&(reglist[i+1].var==0))
				{
					found = true;
					break;
				}
			}
			else
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
	// was mach ich, wenn kein register mehr frei ist? ->wuerde zu fehler fuehren
	// todo: spillcode einfuegen
	reglist[i].var = temp;
	reglist[i].mark = mark++;
	if (temp->vtype>=slong)
	{
		reglist[i+1].var = temp;
		reglist[i+1].mark = mark;
	}
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
			if (temp->vtype>=slong)
			{
				reglist[i+1].var = 0;
				reglist[i+1].mark = 0;
			}
			return;
		}
	}
	cout<<"freeReg() error\n";
}

void Register::changeReg(TOperand* dest, TOperand* src)		// Register wird von op2 auf op1 geaendert
{
	if ( (src->vtype>=slong && dest->vtype<=sint) || (src->vtype<=sint && dest->vtype>=slong) ) { cout<<"changeReg() error, types not compatible!\n"; return; }
	for(int i=0; i<regusable; i++)
	{
		if (reglist[i].var == src)
		{
			reglist[i].var = dest;
			reglist[i].mark = mark++;
			if (src->vtype>=slong)
			{
				reglist[i+1].var = dest;
				reglist[i+1].mark = mark;
			}
			return;
		}
	}
	cout<<"changeReg() error: Register not found!\n";
}

TReg Register::biggerReg(TOperand* op)
{
	for(int i=0; i<regusable; i++)
	{
		if (reglist[i].var == op)	// op gefunden
		{
			if (i%2==0 && reglist[i+1].var == 0) // register liegt an gerader stelle und dahinter ist platz
			{
				reglist[i].mark = mark++;
				reglist[i+1].var = op;
				reglist[i+1].mark = mark;
				return (TReg)(i+1);		// oberes Register wird null gesetzt
			}
			for(int j=0; j<regusable-1; j++)
			{
				if (reglist[j].var == 0 && reglist[j+1].var == 0 && j%2==0)
				{
					reglist[j].var = op;
					reglist[j].mark = mark++;
					reglist[j+1].var = op;
					reglist[j+1].mark = mark;
					reglist[i].var = 0;
					reglist[i].mark = 0;
					return (TReg)(j+1);	// oberes Register wird null gesetzt
					// außerdem muß noch das alte kleine Register ins niederwertige neue verschoben werden
				}
			}
			cout<<"biggerReg() error - no Reg free!\n";
		}
	}
	// todo: spillcode einfuegen
	cout<<"biggerReg() error - op not found!\n";
	return unknown;
}

void Register::smallerReg(TOperand* op)
{
	for(int i=0; i<regusable; i++)
	{
		if (reglist[i].var == op)	// op gefunden
		{
			if (reglist[i+1].var == op) // register gehoeren wirklich zusammen
			{
				reglist[i+1].var = 0;
				reglist[i+1].mark = 0;
				reglist[i].mark = mark++;
				return;
			}
			cout<<"smallerReg() error\n";
		}
	}
	cout<<"smallerReg() error - op not found!\n";
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
	if (r>regmax-1) cout<<" Registerfehler";
	char* n = (char*)malloc(3);
	strcpy(n,"r");
	sprintf (n+1,"%u",r);
	return n;
}

TReg Register::typeToReg(TOperandType t)
{
	// 	if (t==constant) return rconst;
	if (t==gvar) return rglobal;
	if (t==lvar) return rlb;
	return unknown;
}

void Register::invalidate()
{
	for(int i=0; i<regmax; i++)
	{
		reglist[i].var = 0;
		reglist[i].mark = 0;
	}
}
