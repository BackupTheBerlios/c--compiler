#include "IL.h"



IL::IL()
{
	tempcount = 1;
}

/* generiert die Zwischensprache.
 * Durchlaufen der postfixlinearisierung von
 * start bis end.
 */
char* IL::genIL(unsigned* start, unsigned* end)
{
	cout<<endl;
	unsigned constcount = 1;
	char* lastident = 0;
	char* funcident = 0;
	unsigned funcidx = 0;
	unsigned varidx = 0;
	bool func = false;

	while(start<end)
	{
		switch (*start)
		{
			case IDENTIFIER:
			{
				unsigned idx = *++start;
				if (idx>MAX_NO_OF_VARIABLES) {
					funcidx = idx;
					funcident = funcid(idx); 
					if (func)
					{
						func = false;
						outlabel(funcident);
					}
				} else 
				{
					lastident = varid(idx);
					varidx = idx;
				}
				//if (funcident==0) cout<<"IDENT: "<<lastident<<endl;
				//if (funcident!=0) cout<<"FUNCID:"<<funcident<<endl;
				break;
			}
			case VARIABLE:
			{
				op.push(lastident, nl.getType(varidx));
				break;
			}
			case VAR_DECL_ST_2:	break;
			case MULT_DIV_2:
			{
				char* m1 = op.top();
				TType t1 = op.toptype();
				op.pop(1);
				char* m2 = op.top();
				TType t2 = op.toptype();
				op.pop(1);
				TType tt = checkConv(m1,m2,t1,t2);
				char* p = tempid();
				outbin(p, m2, mult, m1);
				op.push(p,tt);
				break;
			}
			case MULT_DIV_3:
			{
				char* m1 = op.top();
				TType t1 = op.toptype();
				op.pop(1);
				char* m2 = op.top();
				TType t2 = op.toptype();
				op.pop(1);
				TType tt = checkConv(m1,m2,t1,t2);
				char* p = tempid();
				outbin(p, m2, divi, m1);
				op.push(p,tt);
				break;
			}
			case MULT_DIV_4:
			{
				char* m1 = op.top();
				TType t1 = op.toptype();
				op.pop(1);
				char* m2 = op.top();
				TType t2 = op.toptype();
				op.pop(1);
				TType tt = checkConv(m1,m2,t1,t2);
				char* p = tempid();
				outbin(p, m2, mod, m1);
				op.push(p,tt);
				break;
			}
			case ADD_SUB_2:
			{
				char* m1 = op.top();
				TType t1 = op.toptype();
				op.pop(1);
				char* m2 = op.top();
				TType t2 = op.toptype();
				op.pop(1);
				TType tt = checkConv(m1,m2,t1,t2);
				char* p = tempid();
				outbin(p, m2, add, m1);
				op.push(p,tt);
				break;
			}
			case ADD_SUB_3:
			{
				char* m1 = op.top();
				TType t1 = op.toptype();
				op.pop(1);
				char* m2 = op.top();
				TType t2 = op.toptype();
				op.pop(1);
				TType tt = checkConv(m1,m2,t1,t2);
				char* p = tempid();
				outbin(p, m2, sub, m1);
				op.push(p,tt);
				break;
			}
			case EXPRESSION_2:
			{
				char* src = op.top();
				TType srct = op.toptype();
				op.pop(1);
				char* dst = op.top();
				TType dstt = op.toptype();
				op.pop(1);
				//cout<<src<<" dst:"<<dst<<endl;
				checkConvAssign(src,srct,dstt);
				
				outcopy(dst,src);
				break;
			}
			case SHIFT_2:
			{
				char* m1 = op.top();
				TType t1 = op.toptype();
				op.pop(1);
				char* m2 = op.top();
				TType t2 = op.toptype();
				if ((t1==sfloat)||(t2==sfloat)) 
				{
					cout<<"[code-il] float-shift not permitted";
					exit(-1);
				}
				op.pop(1);
				char* p = tempid();
				outbin(p, m2, shiftl, m1);
				op.push(p,t1);
				break;
			}
			case SHIFT_3:
			{
				char* m1 = op.top();
				TType t1 = op.toptype();
				op.pop(1);
				char* m2 = op.top();
				TType t2 = op.toptype();
				op.pop(1);
				if ((t1==sfloat)||(t2==sfloat)) 
				{
					cout<<"[code-il] float-shift not permitted";
					exit(-1);
				}
				char* p = tempid();
				outbin(p, m2, shiftr, m1);
				op.push(p,t1);
				break;
			}
			case IF_1: //if ohne else
			{
				outlabel(label.top());
				label.pop(1);
				break;
			}
			case IF_2: //if mit else
			{
				outlabel(label.top());
				label.pop(2);
				break;
			}
			case ELSE:
			{
				char* l=labelid();
				char* e=label.top();
				label.push(l);
				outjump(l);
				outlabel(e);
				break;
			}
			case COND:
			{

				label.push(labelid());
				outjump(label.top());
				break;

			}
			case WHILE_COND:
			{
				char* e=labelid();
				label.push(e);
				outlabel(e);
				break;
			}
			case WHILE:
			{
				char* label_end=label.top();
				label.pop(1);
				char* label_begin=label.top();
				label.pop(1);
				outjump(label_begin);
				outlabel(label_end);
				break;
			}
			case INIT_PART:
			{
				char* dst = lastident;
				TType dstt = nl.getType(varidx);
				char* src = op.top();
				TType srct = op.toptype();
				op.pop(1);
				checkConvAssign(src,srct,dstt);
				outcopy(dst,src);
				break;
			}
			case FUNCTION_CALL_1:
			{
				outgoto(funcident, true);
				// todo: in dieser tempid muss der r�ckgabewert stehen
				op.push(tempid(),fl.getReturnType(funcidx));
				break;
			}
			case FUNCTION_CALL_2:
			{
				unsigned i = fl.getNum(funcidx);
				for (unsigned j=0;j<i;j++)
				{
					char* s = op.top();
					TType t1 = op.toptype();
					TType t2 = fl.getSigType(funcidx, j);
					checkConvAssign(s,t1,t2);
					outpush(s);
					op.pop(1);
				}
				outgoto(funcident, true);
				// todo: in dieser tempid muss der r�ckgabewert stehen
				op.push(tempid(),fl.getReturnType(funcidx));
				break;
			}
			case FUNC_START:
			{
				func = true;
				break;
			}
			case IMPLEMENTATION_1:
			case IMPLEMENTATION_2:
			case IMPLEMENTATION_3:
			case IMPLEMENTATION_4:
			case IMPLEMENTATION_5:
			case IMPLEMENTATION_6:
			{
				outret("null");
				break;
			}
			case INT_CONSTANT:
			{
				op.push(conid(constcount++),sint); 
				break;
			}
			case FLOAT_CONSTANT:
			{
				op.push(conid(constcount++),sfloat); 
				break;
			}
			case CHAR_CONSTANT:
			{
				op.push(conid(constcount++),schar); 
				break;
			}
			case RETURN_1:
			{
				outret("null");
				break;
			}
			case RETURN_2:
			{
				char* s = op.top();
				TType t1 = op.toptype();
				TType t2 = fl.getReturnType(funcidx);
				checkConvAssign(s,t1,t2);
				outret(s);
				op.pop(1);
				break;
			}
			case PRIMITIVE_3:
			{
				char* t = tempid();
				outun(t, sminus, op.top());
				TType tt = op.toptype();
				op.pop(1);
				op.push(t, tt);
				break;
			}
		}
		start++;
	}
	return 0;
}


char* IL::varid(unsigned i)
{
	char* c = nl.getIdent(i);
	if (c==0) return 0;
	unsigned block = nl.getBlock(i);
	char* n = (char*)malloc(VAR_LENGTH_ID);
	sprintf(n,"_");
	strcpy(n+1,c);
	sprintf(n+strlen(c)+1,"%u",block);
	return n;
}

char* IL::conid(unsigned i)
{
	TType t = cl.getType(i);
	if (t==undeclared) return 0;

	char* n = (char*)malloc(VAR_LENGTH_ID);
	if (t==sint) strcpy(n,"int");
	if (t==schar) strcpy(n,"char");
	if (t==sfloat) strcpy(n,"float");
	if (t==slong) strcpy(n,"long");
	
	sprintf(n+strlen(n),"%u",i);
	return n;

}

char* IL::tempid()
{
	char* n = (char*)malloc(VAR_LENGTH_ID);
	strcpy(n,"temp");
	sprintf (n+4,"%u",tempcount++);

	return n;
}

char* IL::funcid(unsigned i)
{
	char* c = fl.getIdent(i);
	if (c==0) return 0;
	unsigned num = fl.getNum(i);
	char* n = (char*)malloc(VAR_LENGTH_ID);
	strcpy(n,c);
	sprintf(n+strlen(c),"%u",num);

	return n;
}

char* IL::labelid()
{
	char* n = (char*)malloc(VAR_LENGTH_ID);
	strcpy(n,"label");
	sprintf (n+5,"%u",labelcount++);

	return n;
}

void IL::outcopy(char* l, char* r)
{
	cout<<l<<" := "<<r<<";\n";
}

void IL::outbin(char* l, char* x, TBinOp o, char* y)
{
	char* c = (char*)malloc(8);
	switch(o)
	{
		case shiftl: c = "<<"; break;
		case shiftr: c = ">>"; break;
		case mult: c = "*"; break;
		case divi: c = "/"; break;
		case mod: c = "%"; break;
		case add: c = "+"; break;
		case sub: c = "-"; break;
	}
	cout<<l<<" := "<<x<<" "<<c<<" "<<y<<";\n";
}

void IL::outun(char* l, TUnOp u, char* y)
{
	if (u==sminus) cout<<l<<" := -"<<y<<";\n";
}


/* Sprunganweisung ans Label label
 * Bei gesetztem call wird ein Funktionsaufruf get�tigt
 * --> Wichtig nachher im Zielcode, da m�ssen bei call
 * n�mlich die Register gerettet sowie die R�cksprung-
 * adresse gesichert werden.
 * Ohne gesetzes call ein normaler Sprung, wie zb. bei
 * if/else/while/break usw.
 */ 
void IL::outgoto(char* label, bool call)
{
	cout<<(call?"call":"goto");
	cout<<" "<<label<<";\n";
}

void IL::outlabel(char* label)
{
	cout<<label<<":\n";
}

void IL::outjump(char* jmp)
{
	cout<<"jmp "<<jmp<<";\n"; //springe dort hin, wenn cond false
}

void IL::outret(char* l)
{
	cout<<"ret "<<l<<";\n";
}

void IL::outpush(char* l)
{
	cout<<"push "<<l<<";\n";
}


TType IL::checkConv(char*& m1, char*& m2, TType t1, TType t2)
{
	if (t1!=t2) 
	{
		if ((t1==sfloat)&&(t2==sint))
		{
			char* m3 = tempid();
			outconvert(m2,m3,sfloat);
			m2 = m3;
			return sfloat;
		} else if ((t1==sint)&&(t2==sfloat))
		{
			char* m3 = tempid();
			outconvert(m1,m3,sfloat);
			m1 = m3;
			return sfloat;
		} else 
			cout<<"[code-il] warning: types not equal t1: "<<t1<<" t2: "<<t2<<endl;
		
	}
	return t1;
}

TType IL::checkConvAssign(char*& m1, TType t1, TType t2)
{
	if (t1!=t2) 
	{
		if ((t1<=slong)&&(t2==sfloat))
		{
			char* t = tempid();
			outconvert(m1,t,sfloat);
			m1 = t;
			return sfloat;
		} else if ((t1==sfloat)&&(t2<=slong))
		{
			char* t = tempid();
			outconvert(m1,t,t2);
			m1 = t;
			return sint;
		} else if (t1>t2)
		{
			cout<<"[code-il] warning: loss of precision\n";
		} else cout<<"[code-il] warning: types not equal t1: "<<t1<<" t2: "<<t2<<endl;
	}
	return t1;
}
void IL::outconvert(char* m1, char* m2, TType to)
{
	char* c = (char*)malloc(8);
	if (to==schar) c = "Char";
	if (to==sint) c = "Int";
	if (to==slong) c = "Long";
	if (to==sfloat) c = "Float";
	cout<<m2<<" := to"<<c<<"("<<m1<<");\n";
}
