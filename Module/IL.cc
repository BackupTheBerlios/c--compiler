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
	bool firstfunc = true;
	unsigned constcount = 2;
	TOperand* lastident = 0;
	TOperand* funcident = 0;
	unsigned funcidx = 0;
	unsigned varidx = 0;
	bool func = false;
	bool relation = false;
	bool switchcond = false;

	// True / False Konstanten
	unsigned const trueidx = 0;
	unsigned const falseidx = 1;
	cl.insert(0,falseidx);
	cl.insert(1,trueidx);
	TOperand* truevar = conid(trueidx);
	TOperand* falsevar = conid(falseidx);


	// Erzeugung des Operanden für die main-Funktion (für den Sprung dorthin)
	TOperand* mainfunc = (TOperand*)malloc(sizeof(TOperand));
	mainfunc->label = "main0";
	mainfunc->type = funclabel;
	mainfunc->no = fl.getMainFunc();

	TOperand* lastfunclabel;

	// Traversierung durchlaufen

	while(start<end)
	{
		switch (*start)
		{
		case IDENTIFIER:
			{
				// ein Ident, kann eine Variable oder eine Funktion sein

				unsigned idx = *++start;
				if (idx>MAX_NO_OF_VARIABLES)
				{
					funcidx = idx;
					funcident = funcid(idx);
					if (func)
					{
						func = false;
						outlabel(funcident);
						lastfunclabel = funcident;
					}
				}
				else
				{
					lastident = varid(idx);
					varidx = idx;
				}
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
				cout<<"exp2";
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
				TType t1 = m1->vtype;
				op.pop(1);
				TOperand* m2 = op.topOp();
				TType t2 = m2->vtype;
				op.pop(1);
				if ((t1==sfloat)||(t2==sfloat))
				{
					cout<<"[code-il] float-shift not permitted";
					exit(-1);
				}
				TType tt = checkConv(m1,m2);
				TOperand* p = tempid(tt);
				outbin(p, m2, shiftl, m1);
				op.push(p);
				break;
			}
		case SHIFT_3:
			{
				TOperand* m1 = op.topOp();
				TType t1 = m1->vtype;
				op.pop(1);
				TOperand* m2 = op.topOp();
				TType t2 = m2->vtype;
				op.pop(1);
				if ((t1==sfloat)||(t2==sfloat))
				{
					cout<<"[code-il] float-shift not permitted";
					exit(-1);
				}
				TType tt = checkConv(m1,m2);
				TOperand* p = tempid(tt);
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
				TOperand* src = op.topOp();
				op.pop(1);
				TOperand* dst = op.topOp();
				op.pop(1);
				TType tt = checkConv(src,dst);
				TOperand* temp = tempid(tt);

				outbin(temp,dst,sub,src);
				op.push(temp);

				if (condition)
				{
					// ergebnis darf nicht groesser oder gleich 0 sein
					outjump(temp,cond.topOp(),jmpgr);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
					outjump(temp,cond.topOp(),jmpeq);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				}
				break;
			}
		case RELATION_3:
			{
				relation = true;
				TOperand* src = op.topOp();
				op.pop(1);
				TOperand* dst = op.topOp();
				op.pop(1);
				TType tt = checkConv(src,dst);
				TOperand* temp = tempid(tt);

				outbin(temp,src,sub,dst);
				op.push(temp);

				if (condition)
				{
					// ergebnis darf nicht groesser oder gleich 0 sein
					outjump(temp,cond.topOp(),jmpgr);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
					outjump(temp,cond.topOp(),jmpeq);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				}
				break;
			}
		case RELATION_4:
			{
				relation = true;
				TOperand* src = op.topOp();
				op.pop(1);
				TOperand* dst = op.topOp();
				op.pop(1);
				TType tt = checkConv(src,dst);
				TOperand* temp = tempid(tt);

				outbin(temp,dst,sub,src);
				op.push(temp);

				if (condition)
				{
					// ergebnis darf nicht groesser 0 sein
					outjump(temp,cond.topOp(),jmpgr);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				}
				break;
			}
		case RELATION_5:
			{
				relation = true;
				TOperand* src = op.topOp();
				op.pop(1);
				TOperand* dst = op.topOp();
				op.pop(1);
				TType tt = checkConv(src,dst);
				TOperand* temp = tempid(tt);

				outbin(temp,src,sub,dst);
				op.push(temp);

				if (condition)
				{
					// ergebnis darf nicht groesser 0 sein
					outjump(temp,cond.topOp(),jmpgr);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				}
				break;
			}
		case EQUALITY_2:
			{
				relation = true;
				TOperand* src = op.topOp();
				op.pop(1);
				TOperand* dst = op.topOp();
				op.pop(1);
				TType tt = checkConv(src,dst);
				TOperand* temp = tempid(tt);

				outbin(temp,src,sub,dst);

				op.push(temp);
				if (condition)
				{
					// ergebnis muß gleich 0 sein, ansonsten sprung
					outjump(temp,cond.topOp(),jmpne);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				}
				break;
			}
		case EQUALITY_3:
			{
				relation = true;
				TOperand* src = op.topOp();
				op.pop(1);
				TOperand* dst = op.topOp();
				op.pop(1);
				TType tt = checkConv(src,dst);
				TOperand* temp = tempid(tt);

				outbin(temp,src,sub,dst);
				op.push(temp);

				if (condition)
				{
					// ergebnis darf nicht gleich 0 sein, ansonsten sprung
					outjump(temp,cond.topOp(),jmpeq);	// wenn bedingung falsch, springe zu nächstem condlabel (ueber if-block)
				}
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
					op.pop(1);
					TType tt = checkConv(src,truevar);
					TOperand* temp = tempid(tt);

					outbin(temp,src,sub,truevar);
					op.push(temp);

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

				TType tp = fl.getReturnType(funcidx);
				if (tp!=svoid)
				{
					TOperand* t  = tempid(tp);
					outgetret(t);
					op.push(t);
				}
				break;
			}
		case FUNCTION_CALL_2:
			{
				int i = fl.getNum(funcidx)-1;
				int j = i;
				for (;i>=0;i--)
				{
					TOperand* s = op.topOp();
					TOperand* tmp = (TOperand*)malloc(sizeof(TOperand));
					tmp->vtype = fl.getSigType(funcidx, j-i);
					checkConvAssign(s, tmp);

					outpush(s, funcident);
					op.pop(1);
				}

				outgoto(funcident, true);

				TType tp = fl.getReturnType(funcidx);
				if (tp!=svoid)
				{
					TOperand* t  = tempid(tp);
					outgetret(t);
					op.push(t);
				}
				break;
			}
		case FUNCTION_CALL_INT_OUT:
			{
				TOperand* m = op.topOp();
				TOperand* p = tempid(sint);
				op.pop(1);
				checkConvAssign(m, p);
				outio(intout, p, m);
				op.push(p);
				break;
			}
		case FUNCTION_CALL_CHAR_OUT:
			{
				TOperand* m = op.topOp();
				TOperand* p = tempid(schar);
				op.pop(1);
				checkConvAssign(m, p);
				outio(charout, p, m);
				op.push(p);
				break;
			}
		case FUNCTION_CALL_LONG_OUT:
			{
				TOperand* m = op.topOp();
				TOperand* p = tempid(slong);
				op.pop(1);
				checkConvAssign(m, p);
				outio(longout, p, m);
				op.push(p);
				break;
			}
		case FUNCTION_CALL_FLOAT_OUT:
			{
				TOperand* m = op.topOp();
				TOperand* p = tempid(sfloat);
				op.pop(1);
				checkConvAssign(m, p);
				outio(floatout, p, m);
				op.push(p);
				break;
			}
		case FUNCTION_CALL_INT_IN:
			{
				TOperand* p = tempid(sint);
				outio(intin, p);
				op.push(p);
				break;
			}
		case FUNCTION_CALL_CHAR_IN:
			{
				TOperand* p = tempid(schar);
				outio(charin, p);
				op.push(p);
				break;
			}
		case FUNCTION_CALL_LONG_IN:
			{
				TOperand* p = tempid(slong);
				outio(longin, p);
				op.push(p);
				break;
			}
		case FUNCTION_CALL_FLOAT_IN:
			{
				TOperand* p = tempid(sfloat);
				outio(floatin, p);
				op.push(p);
				break;
			}
		case FUNC_START:
			{
				if (firstfunc) { outgoto(mainfunc, true); outstop(); firstfunc=false; }
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
				outret(0, lastfunclabel);
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
				outret(0, lastfunclabel);
				break;
			}
		case RETURN_2:
			{
				TOperand* s = op.topOp();

				TOperand* tmp = (TOperand*)malloc(sizeof(TOperand*));
				tmp->vtype = fl.getReturnType(funcidx);
				checkConvAssign(s, tmp);
				outret(s, lastfunclabel);
				op.pop(1);
				break;
			}
		case PRIMITIVE_3:
			{
				TOperand* t = tempid(op.topOp()->vtype);
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

				TOperand* src = op.topOp();
				op.pop(1);
				TOperand* dst = op.topOp();
				op.pop(1);
				TType tt = checkConv(src,dst);
				TOperand* temp = tempid(tt);

				outbin(temp,src,sub,dst);
				op.push(temp);
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
	tmp->label = (char*)malloc(6+10);
	strcpy(tmp->label,"const_");
	sprintf (tmp->label+6,"%u",i);
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
	tmp->type = funclabel;
	tmp->label = n;
	tmp->no = i;

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
	op->operand3=0;

	ilList.append(op);
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
		op->operand1=l;
		op->operand2=y;
		op->operand3=0;
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
	op->operand2=0;
	op->operand3=0;
	ilList.append(op);
}

void IL::outlabel(TOperand* label)
{
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=label_;
	op->operand1 = (TOperand*)label;
	op->operand2=0;
	op->operand3=0;
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
	op->operand3=0;
	ilList.append(op);
}

void IL::outret(TOperand* l, TOperand* f)
{
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=ret_;
	op->operand1=(TOperand*)l;
	op->operand2=(TOperand*)f;
	op->operand3=0;
	ilList.append(op);
}

void IL::outpush(TOperand* l, TOperand* f)
{
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=push_;
	op->operand1=(TOperand*)l;
	op->operand2=(TOperand*)f;
	op->operand3=0;
	ilList.append(op);
}

void IL::outgetret(TOperand* l)
{
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=getret_;
	op->operand1=(TOperand*)l;
	op->operand2=0;
	op->operand3=0;
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
	}
	if (((TOperand*)m2)->type!=temp)
	{
		TOperand* t = tempid(t2);
		outcopy(t, m2);
		m2 = t;
	}


	if (t1!=t2)
	{
		if ( t1==sfloat || t2==sfloat )		// konvertieren nach float
		{
			TOperand* m3 = tempid(sfloat);
			if ( t1==sfloat )
			{
				outconvert(m2,m3,sfloat);
				m2 = m3;
			}
			else
			{
				outconvert(m1,m3,sfloat);
				m1 = m3;
			}
			return sfloat;
		}
		else if ( t1==slong || t2==slong )	// konvertieren nach long
		{
			TOperand* m3 = tempid(slong);
			if ( t1==slong )
			{
				outconvert(m2,m3,slong);
				m2 = m3;
			}
			else
			{
				outconvert(m1,m3,slong);
				m1 = m3;
			}
			return slong;
		}
		else if ( t1==sint || t2==sint )	// konvertieren nach int
		{
			TOperand* m3 = tempid(sint);
			if ( t1==sint )
			{
				outconvert(m2,m3,sint);
				m2 = m3;
			}
			else
			{
				outconvert(m1,m3,sint);
				m1 = m3;
			}
			return sint;
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
		cout<<"t1: "<<t1<<"t2: "<<t2<<endl;
		if ((t1<=slong)&&(t2==sfloat))						// konvertieren nach float
		{
			TOperand* t = tempid(sfloat);
			outconvert(m1,t,sfloat);
			m1 = t;
			return sfloat;
		}
		else if ( ( (t1==sfloat) || (t1==sint) || (t1==schar) )&&(t2==slong))	// konvertieren nach long
		{
			TOperand* t = tempid(slong);
			outconvert(m1,t,slong);
			m1 = t;
			return slong;
		}
		else if ( ( (t1==sfloat) || (t1==slong) || (t1==schar) )&&(t2==sint))	// konvertieren nach int
		{
			TOperand* t = tempid(sint);
			outconvert(m1,t,sint);
			m1 = t;
			return sint;
		}
		else if ( ( (t1==sfloat) || (t1==slong) || (t1==sint) )&&(t2==schar))	// konvertieren nach char
		{
			TOperand* t = tempid(schar);
			outconvert(m1,t,schar);
			m1 = t;
			return schar;
		}
		else if (t1>t2)
		{
			cout<<"[code-il] warning: loss of precision\n";

		}
		else
		{
			// Type1 ganzzahlig, kleiner als Type2
			cout<<"[code-il] warning: types not equal t1: "<<t1<<" t2: "<<t2<<endl;


		}
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
	op->operand3=0;
	ilList.append(op);

}

void IL::outio(TOpType type, TOperand* p, TOperand* m)
{
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=type;
	op->operand1=p;
	op->operand2=m;
	op->operand3=0;
	ilList.append(op);
}

void IL::outio(TOpType type, TOperand* p)
{
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=type;
	op->operand1=p;
	op->operand2=0;
	op->operand3=0;
	ilList.append(op);
}

void IL::outstop()
{
	struct TOp* op=(TOp*)malloc(sizeof(TOp));
	op->TOpType=stop;
	op->operand1=0;
	op->operand2=0;
	op->operand3=0;
	ilList.append(op);
}
