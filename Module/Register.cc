#include "Register.h"

#define nodebug

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
		if (reglist[i].mark<minmark)			// pruefen, ob Benutzung laenger zurueck liegt, als bei vorherigem minmark
		{
			minpos = i;
			minmark = reglist[i].mark;
		}
	}
	if (!found)
	{
		i = minpos;				// ->wurde lange nicht mehr benutzt, wird ausgelagert
		if (reglist[i].var!=0) spillreglist.append(reglist[i].var, (TReg)i);	// wenn kein register mehr frei ->am laengsten nicht mehr benutztes wird ausgelagert
		if (reglist[i+1].var!=0 && temp->vtype>=slong)
			if (reglist[i+1].var->vtype<=sint) spillreglist.append(reglist[i+1].var, (TReg)(i+1));	// breites Register benoetigt, also noch eins auslagern
	}
	reglist[i].var = temp;
	reglist[i].mark = mark++;
	if (temp->vtype>=slong)
	{
		reglist[i+1].var = temp;
		reglist[i+1].mark = mark;
	}
	if (i>=regusable) cout<<"Register "<<i<<">regusable wurde vergeben!\n";
	if (i%2==1 && temp->vtype>=slong) cout<<"Register::getReg - error in alignment!\n";
	r = (TReg)i;
#ifndef nodebug
	cout<<"\ngetReg() - "<<temp->label<<endl;
	spillreglist.out();
	out();
#endif
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
			if (temp->vtype>=slong)		// bei grossen Registern beide Register loeschen
			{
				reglist[i+1].var = 0;
				reglist[i+1].mark = 0;
			}
#ifndef nodebug
			cout<<"\nfreeReg() - "<<temp->label<<endl;
			spillreglist.out();
			out();
#endif
			return;
		}
	}
	if (!spillreglist.del(temp))		// evt. noch ausgelagert, muss auch geloescht werden, Fehler, wenn auch dort nicht vorhanden
	{
		cout<<"freeReg() error - "<<temp->label<<" not found!\n";
		out();
		exit(-1);
	}
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
			if (src->vtype>=slong)		// bei grossen Registern beide Register bearbeiten
			{
				reglist[i+1].var = dest;
				reglist[i+1].mark = mark;
			}
#ifndef nodebug
			cout<<"\nChangeReg "<<dest->label<<", "<<src->label<<"!\n";
			spillreglist.out();
			out();
#endif
			return;
		}
	}
	char* label=spillreglist.where(src);	// merken, wo src lag

	if (!spillreglist.del(src))		// evt ausgelagert, dort loeschen
	{
		cout<<"changeReg() error: "<<src->label<<" not found!\n";
		out();
		exit(-1);
	}
	else
		spillreglist.append(dest,label);// ... und neuen operanden einfuegen an die stelle, wo src vorher lag

#ifndef nodebug
	cout<<"\nChangeReg "<<dest->label<<", "<<src->label<<"!\n";
	spillreglist.out();
	out();
#endif
}

void Register::biggerReg(TOperand* op)
{
	unsigned minmark = 0xFFFFFFFF;
	unsigned minpos;
	for(int i=0; i<regusable; i++)
	{
		if (reglist[i].var == op)	// op gefunden
		{
			if (i%2==0 && reglist[i+1].var == 0) 	// register liegt an gerader stelle und dahinter ist platz
			{
				reglist[i].mark = mark++;
				reglist[i+1].var = op;
				reglist[i+1].mark = mark;
				bsm<<"mov.w\tr"<<i+1<<", r"<<rnull<<endl;	// oberes Register wird null gesetzt
#ifndef nodebug
				cout<<"\nBiggerReg "<<op->label<<"!\n";
				spillreglist.out();
				out();
#endif
				return;
			}
			for(int j=0; j<regusable-1; j++)	// passendes "breites" Register suchen
			{
				if (reglist[j].var == 0 && reglist[j+1].var == 0 && j%2==0)	// ...gefunden
				{
					reglist[j].var = op;
					reglist[j].mark = mark++;
					reglist[j+1].var = op;
					reglist[j+1].mark = mark;
					reglist[i].var = 0;
					reglist[i].mark = 0;
					bsm<<"mov.w\tr"<<j+1<<", r"<<rnull<<endl;	// oberes Register wird null gesetzt
					bsm<<"mov.w\tr"<<j<<", r"<<i<<endl;		// außerdem muß noch das alte kleine Register ins niederwertige neue verschoben werden
#ifndef nodebug
					cout<<"\nBiggerReg "<<op->label<<"!\n";
					spillreglist.out();
					out();
#endif
					return;
				}
				if (reglist[j].mark<minmark && j%2==0)	// Markierung pruefen
				{
					minpos = j;
					minmark = reglist[j].mark;
				}
			}

			// kein passendes Register gefunden, auslagern und an diese Stelle den neuen grossen Operanden packen
			TType minpostype;
			if (reglist[minpos].var!=0)	// wenn minpos nicht leer ist, auslagern
			{
				spillreglist.append (reglist[minpos].var, (TReg) minpos);
				minpostype=reglist[minpos].var->vtype;
			}
			if (reglist[minpos+1].var!=0 && minpostype<=sint)	// wenn minpos+1 nicht leer ist und der typ von minpos nicht long oder float war, auslagern
				spillreglist.append (reglist[minpos+1].var, (TReg) (minpos+1));

			reglist[minpos].mark = mark++;
			reglist[minpos].var = op;
			reglist[minpos+1].mark = mark;
			reglist[minpos+1].var = op;
			reglist[i].var = 0;
			reglist[i].mark = 0;
			bsm<<"mov.w\tr"<<minpos+1<<", r"<<rnull<<endl;	// oberes Register wird null gesetzt
			bsm<<"mov.w\tr"<<minpos<<", r"<<i<<endl;	// außerdem muß noch das alte kleine Register ins niederwertige neue verschoben werden
#ifndef nodebug
			cout<<"\nBiggerReg "<<op->label<<"!\n";
			spillreglist.out();
			out();
#endif
			return;
		}
	}
	cout<<"biggerReg() error - "<<op->label<<" not found!\n";
	out();
	exit(-1);
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
		}
	}
	if (!spillreglist.isValid(op))		// pruefen, ob operand ausgelagert ist
	{
		cout<<"smallerReg() error - "<<op->label<<" not found!\n";
		out();
		exit(-1);
	}
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
	cout<<"Register::whichReg error - "<<temp->label<<" not found!\n";
	spillreglist.out();
	out();
	exit(-1);
	return unknown;
}


void Register::out()
{
	cout<<"Registerausgabe\n";
	for(int i=0; i<regusable; i++)
	{
		if (reglist[i].var!=0) cout<<i<<" "<<reglist[i].var->label<<endl;
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
