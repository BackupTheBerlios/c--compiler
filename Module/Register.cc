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
		if (temp->vtype>=slong && i%2==1)
			continue;				// wenn 4 byte verarbeitungsbreite werden nur gerade register vergeben!
		if (reglist[i].mark<minmark)
		{
			minpos = i;
			minmark = reglist[i].mark;
		}
	}
	if (!found) {
		i = minpos;				// ->wurde lange nicht mehr benutzt, wird ausgelagert
		spillreglist.append(reglist[i].var, (TReg)i);	// wenn kein register mehr frei ->am laengsten nicht mehr benutztes wird ausgelagert
	}
	reglist[i].var = temp;
	reglist[i].mark = mark++;
	if (temp->vtype>=slong)
	{
		reglist[i+1].var = temp;
		reglist[i+1].mark = mark;
	}
	if (i>=regusable) cout<<"Register "<<i<<" wurde vergeben!\n";
	r = (TReg)i;
	return (TReg)i;
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
	if (!spillreglist.del(temp))		// evt. noch ausgelagert, muss auch geloescht werden, Fehler, wenn auch dort nicht vorhanden
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
	char* label=spillreglist.where(src);
	if (!spillreglist.del(src))		// evt ausgelagert, dort loeschen
		cout<<"changeReg() error: Register not found!\n";
	else
		spillreglist.append(dest,label);	// ... und neuen operanden einfuegen
}

void Register::biggerReg(TOperand* op)
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
				bsm<<"mov.w\tr"<<i+1<<", r"<<rnull<<endl;	// oberes Register wird null gesetzt
				return;
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
					bsm<<"mov.w\tr"<<j+1<<", r"<<rnull<<endl;	// oberes Register wird null gesetzt
					bsm<<"mov.w\tr"<<j<<", r"<<i<<endl;		// außerdem muß noch das alte kleine Register ins niederwertige neue verschoben werden
					return;
				}
			}
		}
	}
	if (!spillreglist.isValid(op))		// pruefen, ob operand ausgelagert ist
		cout<<"biggerReg() error - op not found!\n";
	return;
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
	if (!spillreglist.isValid(op))		// pruefen, ob operand ausgelagert ist
		cout<<"smallerReg() error - op not found!\n";
	return;
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
// 	cout<<"Register::whichReg ->Operand nicht in Registern vorhanden!\n";
	if (spillreglist.isValid(temp))		// pruefen, ob operand ausgelagert ist
	{
		TReg r;
		getReg(temp,r);			// einlagern
		bsm<<"// Spillcode: Einlagern"<<endl;
		bsm<<"loa.";
		if (temp->vtype==schar) bsm<<"b";
		else if (temp->vtype==sint) bsm<<"w";
		else if (temp->vtype==slong) bsm<<"l";
		else if (temp->vtype==sfloat) bsm<<"f";
		bsm<<"\tr"<<r<<", r"<<rnull<<" + "<<spillreglist.where(temp)<<endl;
		spillreglist.del(temp);
		return r;
	}
	cout<<"Register::whichReg error!\n";
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
	if (r>regmax-1) cout<<"Registerfehler!\n";
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
	spillreglist.invalidate();
}
