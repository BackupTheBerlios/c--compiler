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
	bool func = false;

	while(start<end)
	{
		switch (*start)
		{
			case IDENTIFIER:
			{
				funcident = 0;
				unsigned idx = *++start;
				if (idx>MAX_NO_OF_VARIABLES) {
					funcident = funcid(idx); 
					if (func)
					{
						func = false;
						outlabel(funcident);
					}
				} else 
				{
					lastident = varid(idx);
				}
				//if (funcident!=0) cout<<"FUNCID:"<<funcident<<endl;
				break;
			}
			case VARIABLE:
			{
				op.push(lastident);
				break;
			}
			case VAR_DECL_ST_2:	break;
			case MULT_DIV_2:
			{
				char* m1 = op.top();
				op.pop(1);
				char* m2 = op.top();
				op.pop(1);
				char* p = tempid();
				outbin(p, m2, mult, m1);
				op.push(p);
				break;
			}
			case MULT_DIV_3:
			{
				char* m1 = op.top();
				op.pop(1);
				char* m2 = op.top();
				op.pop(1);
				char* p = tempid();
				outbin(p, m2, divi, m1);
				op.push(p);
				break;
			}
			case MULT_DIV_4:
			{
				char* m1 = op.top();
				op.pop(1);
				char* m2 = op.top();
				op.pop(1);
				char* p = tempid();
				outbin(p, m2, mod, m1);
				op.push(p);
				break;
			}
			case ADD_SUB_2:
			{
				char* m1 = op.top();
				op.pop(1);
				char* m2 = op.top();
				op.pop(1);
				char* p = tempid();
				outbin(p, m2, add, m1);
				op.push(p);
				break;
			}
			case ADD_SUB_3:
			{
				char* m1 = op.top();
				op.pop(1);
				char* m2 = op.top();
				op.pop(1);
				char* p = tempid();
				outbin(p, m2, sub, m1);
				op.push(p);
				break;
			}
			case EXPRESSION_2:
			{
				char* src = op.top();
				op.pop(1);
				char* dst = op.top();
				op.pop(1);
				outcopy(dst,src);
				break;
			}
			case SHIFT_2:
			{
				char* m1 = op.top();
				op.pop(1);
				char* m2 = op.top();
				op.pop(1);
				char* p = tempid();
				outbin(p, m2, shiftl, m1);
				op.push(p);
				break;
			}
			case SHIFT_3:
			{
				char* m1 = op.top();
				op.pop(1);
				char* m2 = op.top();
				op.pop(1);
				char* p = tempid();
				outbin(p, m2, shiftr, m1);
				op.push(p);
				break;
			}
			case INIT_PART:
			{
				char* dst = lastident;
				char* src = op.top();
				op.pop(1);
				outcopy(dst,src);
				break;
			}
			case FUNCTION_CALL_1:
			{
				outgoto(funcident, true);
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
				outret();
				break;
			}
			case INT_CONSTANT:		op.push(conid(constcount++)); break;
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
	if (t==0) return 0;

	char* n = (char*)malloc(VAR_LENGTH_ID);
	if (t==sint) strcpy(n,"int");
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
{}


/* Sprunganweisung ans Label label
 * Bei gesetztem call wird ein Funktionsaufruf getätigt
 * --> Wichtig nachher im Zielcode, da müssen bei call
 * nämlich die Register gerettet sowie die Rücksprung-
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

void IL::outret()
{
	cout<<"ret;\n";
}
