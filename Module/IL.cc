#include "IL.h"

IL::IL()
{
	tempcount = 1;
	condition = false;
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
	bool relation = false;
	bool switchcond = false;
	unsigned const trueidx = 0xFFFFFFF;
	unsigned const falseidx = 0xFFFFFFE;
	cl.insert(0,falseidx);
	cl.insert(1,trueidx);
	char* truevar = conid(trueidx);
	char* falsevar = conid(falseidx);
	
	

	while(start<end)
	{
		switch (*start)
		{
			case IDENTIFIER:
			{
				unsigned idx = *++start;
				if (idx>MAX_NO_OF_VARIABLES)
				{
					funcidx = idx;
					funcident = funcid(idx);
					if (func)
					{
						func = false;
						outlabel(funcident);
					}
				}
				else
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
				outlabel(cond.top());
				cond.pop(1);
				break;
			}
			case IF_2: //if mit else
			{
				outlabel(label.top());
				label.pop(1);
				break;
			}
			case ELSE:
			{
				// hier endet der true-block, false-block ueberspringen
				char* l=labelid();
				label.push(l);
				outgoto(l,false);

				//Sprungmarke für cond=false setzen
				outlabel(cond.top());
				cond.pop(1);
				break;
			}
			case RELATION_2:
			{
				relation = true;
				char* temp=tempid();
				char* src=op.top();
				op.pop(1);
				char* dst=op.top();
				outbin(temp,dst,sub,src);
				// ergebnis darf nicht groesser oder gleich 0 sein
				outjump(temp,cond.top(),jmpgr);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				outjump(temp,cond.top(),jmpeq);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				break;
			}
			case RELATION_3:
			{
				relation = true;
				char* temp=tempid();
				char* src=op.top();
				op.pop(1);
				char* dst=op.top();
				outbin(temp,src,sub,dst);
				// ergebnis darf nicht groesser oder gleich 0 sein
				outjump(temp,cond.top(),jmpgr);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				outjump(temp,cond.top(),jmpeq);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				break;
			}
			case RELATION_4:
			{
				relation = true;
				char* temp=tempid();
				char* src=op.top();
				op.pop(1);
				char* dst=op.top();
				outbin(temp,dst,sub,src);
				// ergebnis darf nicht groesser 0 sein
				outjump(temp,cond.top(),jmpgr);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				break;
			}
			case RELATION_5:
			{
				relation = true;
				char* temp=tempid();
				char* src=op.top();
				op.pop(1);
				char* dst=op.top();
				outbin(temp,src,sub,dst);
				// ergebnis darf nicht groesser 0 sein
				outjump(temp,cond.top(),jmpgr);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				break;
			}
			case EQUALITY_2:
			{
				relation = true;
				char* temp=tempid();
				char* src=op.top();
				op.pop(1);
				char* dst=op.top();
				outbin(temp,src,sub,dst);
				// ergebnis darf muß gleich 0 sein, ansonsten sprung
				outjump(temp,cond.top(),jmpne);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				break;
			}
			case EQUALITY_3:
			{
				relation = true;
				char* temp=tempid();
				char* src=op.top();
				op.pop(1);
				char* dst=op.top();
				outbin(temp,src,sub,dst);
				// ergebnis darf nicht gleich 0 sein, ansonsten sprung
				outjump(temp,cond.top(),jmpeq);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				break;
			}
			case COND_START:
			{
				condition=true;
				condinsert=ilList.count();
				cond.push(condlabelid());	// dieses label kommt später hinter den true-block
				break;
			}
			case COND:
			{
				// alle atomaren bedingungen wurden hintereinander durchlaufen, hinter jeder atomaren bedingung
				// wird ein sprung hinter den true-block ausgefuehrt, falls diese bedingung falsch ist

				// wenn man hier angelangt ist(im zwischencode), beginnt der true-block
				// cout<<"\ntrue-block\n";
				condition=false;
				if ((!switchcond)&&(!relation))
				{
					char* src = op.top();
					char* temp = tempid();
					
					outbin(temp,src,sub,truevar);
					
					outjump(temp,cond.top(),jmpne);	
				}
				if ((relation)&&(switchcond)) 
				{
					op.push(tempid());
					outcopy(op.top(), truevar);
				}
				relation = false;
				break;
			}
			case WHILE_COND:
			{
				char* e=labelid();
				label.push(e);
				outlabel(e);
				//Endlabel
				breakst.push(labelid());
				break;
			}
			case WHILE:
			{
				// sprung zum start der while-schleife
				outgoto(label.top(),false);
				label.pop(1);
				// austritt aus der schleife
				outlabel(cond.top());
				cond.pop(1);
				
				//Breaklabel setzen
				outlabel(breakst.top());
				//Breaklabel entfernen
				breakst.pop(1);
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
				
				char* t  = tempid();
				outgetret(t);
				op.push(t,fl.getReturnType(funcidx));
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
				
				char* t  = tempid();
				outgetret(t);
				op.push(t,fl.getReturnType(funcidx));
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
			case CASE_LABEL_1:
			{
				outlabel(label.top());
				label.pop(1);
				label.push(labelid());
				char* temp=tempid();
				char* src=op.top();
				op.pop(1);
				char* dst=op.top();
				
				outbin(temp,src,sub,dst);
				outjump(temp,label.top(),jmpne);
				break;
			}
			case CASE_LABEL_2:
			{
				outlabel(label.top());
				label.pop(1);
				label.push(labelid());
				break;
			}
			case SWITCH_START:
			{
				switchcond = true;
			}
			case SWITCH:
			{
				// übriggebliebenes case-jump label...
				outlabel(label.top()); 
				label.pop(1);
				
				//Breaklabel setzen
				outlabel(breakst.top());
				//Breaklabel entfernen
				breakst.pop(1);
				
				op.pop(1);
				
				break;
			}
			case SWITCH_COND:
			{
				
				outlabel(cond.top());
				cond.pop(1);
				
				// Label fürs Ende des Switch-Block
				breakst.push(labelid());
				// Label fürs erste case
				label.push(labelid());
				switchcond = false;
				break;
			}
			case BREAK:
			{
				char* b = breakst.top();
				if (b==0) 
				{
					cout<<"[code-il] break statement not within loop or switch\n";
					exit(-1);
				}
				outgoto(breakst.top(),false);
			}
		}
		start++;
	}
	cout<<endl;
	ilList.out();
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

char* IL::condlabelid()
{
	char* n = (char*)malloc(VAR_LENGTH_ID);
	strcpy(n,"condlabel");
	sprintf (n+9,"%u",condlabelcount++);

	return n;
}

void IL::outcopy(char* l, char* r)
{

	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=mov_;
	op->operand1=l;
	op->operand2=r;

	if (condition)
	{
		ilList.insert(op,condinsert+1);
		condinsert++;
	}
	else
	{
		ilList.append(op);
	}
}

void IL::outbin(char* l, char* x, TBinOp o, char* y)
{
	unsigned a;
	switch(o)
	{
		case shiftl: a = shiftl_; break;
		case shiftr: a = shiftr_; break;
		case mult: a = mult_; break;
		case divi: a = divi_; break;
		case mod: a = mod_; break;
		case add: a = add_; break;
		case sub: a = sub_; break;
	}
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=a;
	op->operand1=l;
	op->operand2=x;
	op->operand3=y;
	ilList.append(op);
}

void IL::outun(char* l, TUnOp u, char* y)
{
	if (u==sminus)
	{
		struct TOp* op=(TOp*)malloc(sizeof(TOp));
		op->TOpType=sminus_;
		op->operand1=y;
		ilList.append(op);
	}
}


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
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=call?call_:goto_;
	op->operand1=label;
	ilList.append(op);
}

void IL::outlabel(char* label)
{
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=label_;
	op->operand1=label;
	ilList.append(op);
}

void IL::outjump(char* cc,char* jmp,TJmp type)
{
	unsigned a;
	switch(type)
	{
		case jmpgr: a = jmpgr_; break;
		case jmple: a = jmple_; break;
		case jmpeq: a = jmpeq_; break;
		case jmpne: a = jmpne_; break;
	}
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=a;
	op->operand1=cc;
	op->operand2=jmp;
	ilList.append(op);
}

void IL::outret(char* l)
{
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=ret_;
	op->operand1=l;
	ilList.append(op);
}

void IL::outpush(char* l)
{
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=push_;
	op->operand1=l;
	ilList.append(op);
}

void IL::outgetret(char* l)
{
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=getret_;
	op->operand1=l;
	ilList.append(op);	
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
		}
		else if ((t1==sint)&&(t2==sfloat))
		{
			char* m3 = tempid();
			outconvert(m1,m3,sfloat);
			m1 = m3;
			return sfloat;
		}
		else
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
		}
		else if ((t1==sfloat)&&(t2<=slong))
		{
			char* t = tempid();
			outconvert(m1,t,t2);
			m1 = t;
			return sint;
		}
		else if (t1>t2)
		{
			cout<<"[code-il] warning: loss of precision\n";
		}
		else cout<<"[code-il] warning: types not equal t1: "<<t1<<" t2: "<<t2<<endl;
	}
	return t1;
}
void IL::outconvert(char* m1, char* m2, TType to)
{
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	unsigned a;
	if (to==schar) a = char_;
	if (to==sint) a = int_;
	if (to==slong) a = long_;
	if (to==sfloat) a = float_;
	op->TOpType=a;
	op->operand1=m2;
	op->operand2=m1;
	if (condition)
	{
		ilList.insert(op,condinsert+1);
		condinsert++;
	}
	else
	{
		ilList.append(op);
	}

}
