#include "Bacom.h"


void Bacom::genAsm()
{
	cout << "\nBASM Ausgabe:\n";
	cout << "sub.w " <<Register::toString( rnull )<<","<<Register::toString( rnull )<<endl;		// Nullregister 0 setzen
	cout << "const_two:  ds.w 2 \n";
	for ( unsigned i = 1; i <= ilList.count(); i++ )
	{
		TOp* e = ilList.getelem( i );
		TOperand* op1 = e->operand1;
		TOperand* op2 = e->operand2;
		TOperand* op3 = e->operand3;

		switch ( e->TOpType )
		{

		case label_:
			{
				cout<<op1->label<<":\n";
				if (op1->type == funclabel)
				{
					// Die Parameter liegen bereits auf dem Stack, jetzt werden die Register gerettet
					outloa(sint, rnull, rnull, "const_two");
					for (int i=0;i<16;i++)
					{
						outstr(sint, (TReg)i, rsp, 0 );
						outsub(sint, rsp, rnull);

					}
					outsub(sint, rnull, rnull);

					// Lokale Basis neu setzen
					outmov(rlb, rsp);

					// Platz schaffen fuer lokales Frame, sp um Framegroesse weiterschieben
					outloa(sint, r0, rnull, fl.getFrameConstant(op1->no) );
					outsub(sint, rsp, rnull);
					cout<<"\n";

					// Fertig!
				}
				break;
			}
		case mov_:
			{
				if ( op1->type == temp ) 	// t:=a;
				{
					TReg r;
					regs.getReg( op1, r );

					if ( op2->type==constant)		// wenn type==constant, dann aus Konstantenliste laden
						outloa( op1->vtype, r, rnull , op2->label );
					else
						outloa( op1->vtype, r, Register::typeToReg( op2->type ), op2->add );

				} else	// a:=t;
				{
					outstr( op1->vtype, regs.whichReg( op2 ), ( ( op1->type == gvar ) ? rglobal : rlb ), op1->add );
					regs.freeReg( op2 );
				}

				break;
			}

		case push_:
			{
				outstr(op1->vtype, regs.whichReg(op1), rsp, op1->add);
				break;
			}



		case jmpgr_: 	// greater zero
		case jmple_: 	// less zero
		case jmpeq_: 	// equal zero
		case jmpne_: 	// not equal
		case mult_:
		case divi_:
		case mod_:	break;
		case add_:

			{
				regs.changeReg( op1, op2 ); 						// Registerdeskriptor aendern (op2 wird zu op1)
				outadd(op1->vtype, regs.whichReg( op1 ), regs.whichReg( op3 ));		// Dann wird der op3 drauf addiert
				regs.freeReg( op3 );
				break;
			}
		case sub_:
			{
				regs.changeReg( op1, op2 ); 						// Registerdeskriptor aendern (op2 wird zu op1)
				outsub(op1->vtype, regs.whichReg( op1 ), regs.whichReg( op3 ));		// Dann wird der op3 subtrahiert
				regs.freeReg( op3 );
				break;
			}
		case shiftl_:
		case shiftr_:
		case sminus_:
		case splus_:
		case call_:
		case goto_:
		case ret_:
		case getret_:	break;
		case char_:
			{
				if (op2->vtype==sfloat)		// evt vorher nach long konvertieren
				{
					TReg r;
					op1->vtype=slong;	// vorher typ auf long, somit wird ein breites register geholt
					regs.getReg(op1, r);
					op1->vtype=sint;
					outcvt(slong, regs.whichReg( op1 ), regs.whichReg( op2 ) );
					regs.freeReg( op2 );
				}
				regs.smallerReg(op2);
				break;
			}
		case int_:
			{
				if (op2->vtype==sfloat)		// evt vorher nach long konvertieren
				{
					TReg r;
					op1->vtype=slong;	// vorher typ auf long, somit wird ein breites register geholt
					regs.getReg(op1, r);
					op1->vtype=sint;
					outcvt(slong, regs.whichReg( op1 ), regs.whichReg( op2 ) );
					regs.freeReg( op2 );
				}
				regs.smallerReg(op2);
				break;
			}
		case long_:	//Todo: in IL.cc noch toLong und toInt einfuegen!
			{
				// wenn convert von int, dann in ein doppelregister stecken
				if (op2->vtype<=sint)
				{
					regs.biggerReg(op2);
					op1=op2;
					regs.changeReg( op1, op2 );
				}
				else	// convert von float
				{
					TReg r;
					regs.getReg(op1, r);
					outcvt(slong, regs.whichReg( op1 ), regs.whichReg( op2 ) );
					regs.freeReg( op2 );
				}
				break;
			}
		case float_:
			{
				// wenn convert von int, dann zuerst in ein doppelregister stecken
				if (op2->vtype<=sint)
				{
					regs.biggerReg(op2);
				}
				// danach convert zu float
				TReg r;
				regs.getReg(op1, r);
				outcvt(op1->vtype, regs.whichReg( op1 ), regs.whichReg( op2 ) );
				regs.freeReg( op2 );
				break;
			}
		default:
			{
				cout << "[bacom] noch nicht implementiert\n";
				break;
			}

		}
	}

	// Konstanten
	cout << endl;
	for (unsigned i=3;i<=cl.getCount();i++)
	{
		cout << "const_" << cl.getAddr(i) <<":\tdc.";
		if ( cl.getType(i) == schar )
			cout << "b";
		else if ( cl.getType(i) == sint )
			cout << "w";
		else if ( cl.getType(i) == slong )
			cout << "l";
		else if ( cl.getType(i) == sfloat )
			cout << "f";

		cout<<" "<<cl.getVal(i)<<endl;
	}

	// interne Konstanten
	for (unsigned i=1;i<=icl.getCount();i++)
	{
		cout << "iconst_" << icl.getAddr(i) <<":\tdc.";
		if ( icl.getType(i) == schar )
			cout << "b";
		else if ( icl.getType(i) == sint )
			cout << "w";
		else if ( icl.getType(i) == slong )
			cout << "l";
		else if ( icl.getType(i) == sfloat )
			cout << "f";

		cout<<" "<<icl.getVal(i)<<endl;
	}
	cout<<"\nstp\n";
}



void Bacom::outloa( TType type, TReg dest, TReg help, int offset )
{
	cout << "loa.";
	if ( type == schar )
		cout << "b";
	else if ( type == sint )
		cout << "w";
	else if ( type == slong )
		cout << "l";
	else if ( type == sfloat )
		cout << "f";
	cout << " " << Register::toString( dest ) << ", " << Register::toString( help ) << "+" << offset << endl;
}

void Bacom::outloa( TType type, TReg dest, TReg help, char* addr )
{
	cout << "loa.";
	if ( type == schar )
		cout << "b";
	else if ( type == sint )
		cout << "w";
	else if ( type == slong )
		cout << "l";
	else if ( type == sfloat )
		cout << "f";
	cout << " " << Register::toString( dest ) << ", " << Register::toString( help ) << "+" << addr << endl;
}

void Bacom::outstr( TType type, TReg src, TReg help, int offset )
{
	cout << "str.";
	if ( type == schar )
		cout << "b";
	else if ( type == sint )
		cout << "w";
	else if ( type == slong )
		cout << "l";
	else if ( type == sfloat )
		cout << "f";
	cout << " " << Register::toString( src ) << ", " << Register::toString( help ) << "+" << offset << endl;
}

void Bacom::outadd( TType type, TReg dest, TReg src )
{
	cout << "add.";
	if ( type == schar )
		cout << "b";
	else if ( type == sint )
		cout << "w";
	else if ( type == slong )
		cout << "l";
	else if ( type == sfloat )
		cout << "f";
	cout << " " << Register::toString( dest ) << ", " << Register::toString( src ) << endl;
}

void Bacom::outsub( TType type, TReg dest, TReg src )
{
	cout << "sub.";
	if ( type == schar )
		cout << "b";
	else if ( type == sint )
		cout << "w";
	else if ( type == slong )
		cout << "l";
	else if ( type == sfloat )
		cout << "f";
	cout << " " << Register::toString( dest ) << ", " << Register::toString( src ) << endl;
}

void Bacom::outmov(TReg r1, TReg r2)
{
	cout << "mov.w " << Register::toString( r1 ) << "," << Register::toString( r2 ) << endl;
}

void Bacom::outcvt(TType type, TReg r1, TReg r2)
{
	cout << "cvt.";
	if (type==sfloat)
		cout << "f " ;
	else if (type==slong)
		cout << "l ";
	cout << Register::toString( r1 ) << "," << Register::toString( r2 ) << endl;
}

