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
	TOperand* lastident = 0;
	TOperand* funcident = 0;
	unsigned funcidx = 0;
	unsigned varidx = 0;
	bool func = false;
	bool relation = false;
	bool switchcond = false;
	unsigned const trueidx = 0xFFFFFFF;
	unsigned const falseidx = 0xFFFFFFE;
	cl.insert(0,falseidx);
	cl.insert(1,trueidx);
	TOperand* truevar = conid(trueidx);
	TOperand* falsevar = conid(falseidx);
	
	

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
				op.push(lastident);
				break;
			}
			case VAR_DECL_ST_2:	break;
			case MULT_DIV_2:
			{
				TOperand* m1 = op.topOp();
				op.pop(1);
				TOperand* m2 = op.topOp();
				op.pop(1);
				TType tt = checkConv(m1,m2);
				TOperand* p = tempid(tt);
				outbin(p, m2, mult, m1);
				op.push(p);
				break;
			}
			case MULT_DIV_3:
			{
				TOperand* m1 = op.topOp();
				op.pop(1);
				TOperand* m2 = op.topOp();
				op.pop(1);
				TType tt = checkConv(m1,m2);
				TOperand* p = tempid(tt);
				outbin(p, m2, divi, m1);
				op.push(p);
				break;
			}
			case MULT_DIV_4:
			{
				TOperand* m1 = op.topOp();
				op.pop(1);
				TOperand* m2 = op.topOp();
				op.pop(1);
				TType tt = checkConv(m1,m2);
				TOperand* p = tempid(tt);
				outbin(p, m2, mod, m1);
				op.push(p);
				break;
			}
			case ADD_SUB_2:
			{
				TOperand* m1 = op.topOp();
				op.pop(1);
				TOperand* m2 = op.topOp();
				op.pop(1);
				TType tt = checkConv(m1,m2);
				TOperand* p = tempid(tt);
				outbin(p, m2, add, m1);
				op.push(p);
				break;
			}
			case ADD_SUB_3:
			{
				TOperand* m1 = op.topOp();
				op.pop(1);
				TOperand* m2 = op.topOp();
				op.pop(1);
				TType tt = checkConv(m1,m2);
				TOperand* p = tempid(tt);
				outbin(p, m2, sub, m1);
				op.push(p);
				break;
			}
			case EXPRESSION_2:
			{
				TOperand* src = op.topOp();
				op.pop(1);
				TOperand* dst = op.topOp();
				
				//cout<<src<<" dst:"<<dst<<endl;
				checkConvAssign(src,dst);

				outcopy(dst,src);
				break;
			}
			case SHIFT_2:
			{
				TOperand* m1 = op.topOp();
				TType t1 = op.toptype();
				op.pop(1);
				TOperand* m2 = op.topOp();
				TType t2 = op.toptype();
				if ((t1==sfloat)||(t2==sfloat))
				{
					cout<<"[code-il] float-shift not permitted";
					exit(-1);
				}
				op.pop(1);
				TOperand* p = tempid(t1);
				outbin(p, m2, shiftl, m1);
				op.push(p);
				break;
			}
			case SHIFT_3:
			{
				TOperand* m1 = op.topOp();
				TType t1 = op.toptype();
				op.pop(1);
				TOperand* m2 = op.topOp();
				TType t2 = op.toptype();
				op.pop(1);
				if ((t1==sfloat)||(t2==sfloat))
				{
					cout<<"[code-il] float-shift not permitted";
					exit(-1);
				}
				TOperand* p = tempid(t1);
				outbin(p, m2, shiftr, m1);
				op.push(p);
				break;
			}
			case IF_1: //if ohne else
			{
				outlabel(cond.topOp());
				cond.pop(1);
				break;
			}
			case IF_2: //if mit else
			{
				outlabel(label.topOp());
				label.pop(1);
				break;
			}
			case ELSE:
			{
				// hier endet der true-block, false-block ueberspringen
				TOperand* l=labelid();
				label.push(l);
				outgoto(l,false);

				//Sprungmarke für cond=false setzen
				outlabel(cond.topOp());
				cond.pop(1);
				break;
			}
			case RELATION_2:
			{
				relation = true;
				TOperand* temp=tempid(slong);
				TOperand* src=op.topOp();
				op.pop(1);
				TOperand* dst=op.topOp();
				outbin(temp,dst,sub,src);
				// ergebnis darf nicht groesser oder gleich 0 sein
				outjump(temp,cond.topOp(),jmpgr);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				outjump(temp,cond.topOp(),jmpeq);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				break;
			}
			case RELATION_3:
			{
				relation = true;
				TOperand* temp=tempid(slong);
				TOperand* src=op.topOp();
				op.pop(1);
				TOperand* dst=op.topOp();
				outbin(temp,src,sub,dst);
				// ergebnis darf nicht groesser oder gleich 0 sein
				outjump(temp,cond.topOp(),jmpgr);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				outjump(temp,cond.topOp(),jmpeq);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				break;
			}
			case RELATION_4:
			{
				relation = true;
				TOperand* temp=tempid(slong);
				TOperand* src=op.topOp();
				op.pop(1);
				TOperand* dst=op.topOp();
				outbin(temp,dst,sub,src);
				// ergebnis darf nicht groesser 0 sein
				outjump(temp,cond.topOp(),jmpgr);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				break;
			}
			case RELATION_5:
			{
				relation = true;
				TOperand* temp=tempid(slong);
				TOperand* src=op.topOp();
				op.pop(1);
				TOperand* dst=op.topOp();
				outbin(temp,src,sub,dst);
				// ergebnis darf nicht groesser 0 sein
				outjump(temp,cond.topOp(),jmpgr);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				break;
			}
			case EQUALITY_2:
			{
				relation = true;
				TOperand* temp=tempid(slong);
				TOperand* src=op.topOp();
				op.pop(1);
				TOperand* dst=op.topOp();
				outbin(temp,src,sub,dst);
				// ergebnis darf muß gleich 0 sein, ansonsten sprung
				outjump(temp,cond.topOp(),jmpne);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				break;
			}
			case EQUALITY_3:
			{
				relation = true;
				TOperand* temp=tempid(slong);
				TOperand* src=op.topOp();
				op.pop(1);
				TOperand* dst=op.topOp();
				outbin(temp,src,sub,dst);
				// ergebnis darf nicht gleich 0 sein, ansonsten sprung
				outjump(temp,cond.topOp(),jmpeq);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
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
					TOperand* src = op.topOp();
					TOperand* temp = tempid(slong);
					
					outbin(temp,src,sub,truevar);
					
					outjump(temp,cond.topOp(),jmpne);	
				}
				if ((relation)&&(switchcond)) 
				{
					op.push(tempid(slong));
					outcopy(op.topOp(), truevar);
				}
				relation = false;
				break;
			}
			case WHILE_COND:
			{
				TOperand* e=labelid();
				label.push(e);
				outlabel(e);
				//Endlabel
				breakst.push(labelid());
				break;
			}
			case WHILE:
			{
				// sprung zum start der while-schleife
				outgoto(label.topOp(),false);
				label.pop(1);
				// austritt aus der schleife
				outlabel(cond.topOp());
				cond.pop(1);
				
				//Breaklabel setzen
				outlabel(breakst.topOp());
				//Breaklabel entfernen
				breakst.pop(1);
				break;
			}
			case INIT_PART:
			{
				TOperand* dst = lastident;
				TOperand* src = op.topOp();
				op.pop(1);
				checkConvAssign(src,dst);
				outcopy(dst,src);
				break;
			}
			case FUNCTION_CALL_1:
			{
				outgoto(funcident, true);
				
				TOperand* t  = tempid(fl.getReturnType(funcidx));
				
				outgetret(t);
				op.push(t);
				break;
			}
			case FUNCTION_CALL_2:
			{
				unsigned i = fl.getNum(funcidx);
				for (unsigned j=0;j<i;j++)
				{
					TOperand* s = op.topOp();
					TOperand* tmp = (TOperand*)malloc(sizeof(TOperand*));
					tmp->vtype = fl.getSigType(funcidx, j);
					checkConvAssign(s,tmp);
					outpush(s);
					op.pop(1);
				}
				
				outgoto(funcident, true);
				
				TOperand* t  = tempid(fl.getReturnType(funcidx));
				outgetret(t);
				op.push(t);
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
				outret(falsevar);
				break;
			}
			case INT_CONSTANT:
			{
				op.push(conid(constcount++));
				break;
			}
			case FLOAT_CONSTANT:
			{
				op.push(conid(constcount++));
				break;
			}
			case CHAR_CONSTANT:
			{
				op.push(conid(constcount++));
				break;
			}
			case RETURN_1:
			{
				outret(falsevar);
				break;
			}
			case RETURN_2:
			{
				TOperand* s = op.topOp();
				
				TOperand* tmp = (TOperand*)malloc(sizeof(TOperand*));
				tmp->vtype = fl.getReturnType(funcidx);
				checkConvAssign(s, tmp);
				outret(s);
				op.pop(1);
				break;
			}
			case PRIMITIVE_3:
			{
				TOperand* t = tempid(slong);
				outun(t, sminus, op.topOp());
				
				op.pop(1);
				op.push(t);
				break;
			}
			case CASE_LABEL_1:
			{
				outlabel(label.topOp());
				label.pop(1);
				label.push(labelid());
				TOperand* temp=tempid(slong);
				TOperand* src=op.topOp();
				op.pop(1);
				TOperand* dst=op.topOp();
				
				outbin(temp,src,sub,dst);
				outjump(temp,label.topOp(),jmpne);
				break;
			}
			case CASE_LABEL_2:
			{
				outlabel(label.topOp());
				label.pop(1);
				label.push(labelid());
				break;
			}
			case SWITCH_START:
			{
				switchcond = true;
				break;
			}
			case SWITCH:
			{
				// übriggebliebenes case-jump label...
				outlabel(label.topOp()); 
				label.pop(1);
				
				//Breaklabel setzen
				outlabel(breakst.topOp());
				//Breaklabel entfernen
				breakst.pop(1);
				
				op.pop(1);
				
				break;
			}
			case SWITCH_COND:
			{
				
				outlabel(cond.topOp());
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
				TOperand* b = breakst.topOp();
				if (b==0) 
				{
					cout<<"[code-il] break statement not within loop or switch\n";
					exit(-1);
				}
				outgoto(breakst.topOp(),false);
			}
		}
		start++;
	}
	cout<<endl;
	ilList.out();
	return 0;
}


TOperand* IL::varid(unsigned i)
{
	TOperand* tmp = (TOperand*)malloc(sizeof(TOperand));
	
	tmp->type = nl.isGlobal(i)?gvar:lvar;
	tmp->vtype = nl.getType(i);
	tmp->add = nl.getAddr(i);
	
	return tmp;
}

TOperand* IL::conid(unsigned i)
{
	TOperand* tmp = (TOperand*)malloc(sizeof(TOperand));
	
	tmp->type = constant;
	tmp->vtype = cl.getType(i);
	tmp->add = cl.getAddr(i);
	
	return tmp;
}

TOperand* IL::tempid(TType t)
{
	char* n = (char*)malloc(VAR_LENGTH_ID);
	strcpy(n,"temp");
	sprintf (n+4,"%u",tempcount++);
	
	TOperand* tmp = (TOperand*)malloc(sizeof(TOperand));
	tmp->type = temp;
	tmp->vtype = t;
	tmp->label = n;
	
	return tmp;
}

TOperand* IL::funcid(unsigned i)
{
	char* c = fl.getIdent(i);
	if (c==0) return 0;
	unsigned num = fl.getNum(i);
	char* n = (char*)malloc(VAR_LENGTH_ID);
	strcpy(n,c);
	sprintf(n+strlen(c),"%u",num);
	
	TOperand* tmp = (TOperand*)malloc(sizeof(TOperand));
	tmp->type = labelstring;
	tmp->label = n;
	
	return tmp;
}

TOperand* IL::labelid()
{
	
	char* n = (char*)malloc(VAR_LENGTH_ID);
	strcpy(n,"label");
	sprintf (n+5,"%u",labelcount++);
	
	TOperand* tmp = (TOperand*)malloc(sizeof(TOperand));
	tmp->type = labelstring;
	tmp->label = n;
	
	return tmp;
}

TOperand* IL::condlabelid()
{
	char* n = (char*)malloc(VAR_LENGTH_ID);
	strcpy(n,"condlabel");
	sprintf (n+9,"%u",condlabelcount++);
	
	TOperand* tmp = (TOperand*)malloc(sizeof(TOperand));
	tmp->type = labelstring;
	tmp->label = n;
	
	return tmp;
}

void IL::outcopy(TOperand* l, TOperand* r)
{

	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=mov_;
	
	op->operand1=(TOperand*)l;
	op->operand2=(TOperand*)r;

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

void IL::outbin(TOperand* l, TOperand* x, TBinOp o, TOperand* y)
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
	op->operand1=(TOperand*)l;
	op->operand2=(TOperand*)x;
	op->operand3=(TOperand*)y;
	ilList.append(op);
}

void IL::outun(TOperand* l, TUnOp u, TOperand* y)
{
	if (u==sminus)
	{
		struct TOp* op=(TOp*)malloc(sizeof(TOp));
		op->TOpType=sminus_;
		op->operand1=(TOperand*)y;
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
void IL::outgoto(TOperand* label, bool call)
{
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=call?call_:goto_;
	op->operand1 = (TOperand*)label;
	ilList.append(op);
}

void IL::outlabel(TOperand* label)
{
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=label_;
	op->operand1 = (TOperand*)label;
	ilList.append(op);
}

void IL::outjump(TOperand* cc,TOperand* jmp,TJmp type)
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
	op->operand1=(TOperand*)cc;
	op->operand2=(TOperand*)jmp;
	ilList.append(op);
}

void IL::outret(TOperand* l)
{
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=ret_;
	op->operand1=(TOperand*)l;
	ilList.append(op);
}

void IL::outpush(TOperand* l)
{
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=push_;
	op->operand1=(TOperand*)l;
	ilList.append(op);
}

void IL::outgetret(TOperand* l)
{
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=getret_;
	op->operand1=(TOperand*)l;
	ilList.append(op);	
}

TType IL::checkConv(TOperand*& m1, TOperand*& m2)
{
	TType t1 = m1->vtype;
	TType t2 = m2->vtype;
	// es duerfen nur temp. variablen als operanden verwendet werden!
	if (((TOperand*)m1)->type!=temp)
	{
		TOperand* t = tempid(t1);
		outcopy(t, m1);
		m1 = t;
	} if (((TOperand*)m2)->type!=temp)
	{
		TOperand* t = tempid(t2);
		outcopy(t, m2);
		m2 = t;
	}
	
	
	if (t1!=t2)
	{
		if ((t1==sfloat)&&(t2==sint))
		{
			TOperand* m3 = tempid(sfloat);
			outconvert(m2,m3,sfloat);
			m2 = m3;
			return sfloat;
		}
		else if ((t1==sint)&&(t2==sfloat))
		{
			TOperand* m3 = tempid(sfloat);
			outconvert(m1,m3,sfloat);
			m1 = m3;
			return sfloat;
		}
		else
			cout<<"[code-il] warning: types not equal t1: "<<t1<<" t2: "<<t2<<endl;

	}
	return t1;
}

TType IL::checkConvAssign(TOperand*& m1, TOperand*& m2)
{
	TType t1 = m1->vtype;
	TType t2 = m2->vtype;
	// es duerfen nur temp. variablen als operanden verwendet werden!
	if (((TOperand*)m1)->type!=temp) 
	{
		TOperand* t = tempid(t1);
		outcopy(t, m1);
		m1 = t;
	}
	
	if (t1!=t2)
	{
		if ((t1<=slong)&&(t2==sfloat))
		{
			TOperand* t = tempid(sfloat);
			outconvert(m1,t,sfloat);
			m1 = t;
			return sfloat;
		}
		else if ((t1==sfloat)&&(t2<=slong))
		{
			TOperand* t = tempid(sint);
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
void IL::outconvert(TOperand* m1, TOperand* m2, TType to)
{
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	unsigned a;
	if (to==schar) a = char_;
	if (to==sint) a = int_;
	if (to==slong) a = long_;
	if (to==sfloat) a = float_;
	op->TOpType=a;
	op->operand1=(TOperand*)m2;
	op->operand2=(TOperand*)m1;
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
