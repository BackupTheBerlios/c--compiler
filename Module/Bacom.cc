#include "Bacom.h"

Bacom::Bacom()
{
	bsm.open("test.bsm");
}

Bacom::~Bacom()
{
	bsm.close();
}



void Bacom::genAsm()
{
	cout << "\nBASM Ausgabe:\n";
	bsm << "sub.w " <<Register::toString( rnull )<<","<<Register::toString( rnull )<<endl;		// Nullregister 0 setzen
	outloa(sint, rsp, rnull, "const_stack");
	
	// offset bis zum naechsten lokalen frame = 32
	unsigned para = 32;
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
				para = 32;
				bsm<<op1->label<<":\n";
				if (op1->type == funclabel)
				{
					// Die Parameter liegen bereits im lokalem Frame, jetzt werden die Register gerettet
					//outloa(sint, rnull, rnull, "const_two");
					for (int i=0;i<15;i++)
					{
						outstr(sint, (TReg)i, rsp, 0 );
						outsub(sint, rsp, rnull, "const_two");
					}
					
					// Registerzuordnungen l�schen
					regs.invalidate();

					// Lokale Basis neu setzen
					outmov(rlb, rsp);

					// Platz schaffen fuer lokales Frame, sp um Framegroesse weiterschieben
					outsub(sint, rsp, rnull, concat("iconst_", fl.getFrameConstant(op1->no)) );
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
			// Paramter ins lokale Frame der aufgerufenen Funktion schreiben
			outstr(op1->vtype, regs.whichReg(op1), rsp, para);
			para+=((op1->vtype>=slong)?4:(op1->vtype+1));
			break;
		}
		
		case ret_:
		{
			// Lokales Frame abr�umen
			outadd(sint, rsp, rnull, concat("iconst_", fl.getFrameConstant(op2->no)) );
			
			//Rueckgabewert
			if (op1!=0)
			{
				
				TReg r = regs.whichReg(op1);
				int offs;
				if (op1->vtype>=slong) offs = -16; else offs = -14;
				outstr(op1->vtype, r, rsp, offs);
			}
			
			// Register wiederherstellen
			for (int i=14;i>=0;i--)
			{
				outloa(sint, (TReg)i, rsp, 0 );
				outadd(sint, rsp, rnull, "const_two");
				
			}

			// R�cksprungadresse abr�umen 
			outloa( sint, rnull, rsp, 0 );
			
			// R�cksprung
			outbra(rnull, 0);
	
			
			break;
		}
			
			

		case jmpgr_: 	// greater zero
			{
				outjmp(rnull, op2->label, jmpgr);
				break;
			}
		case jmple_: 	// less zero
			{
				outjmp(rnull, op2->label, jmple);
				break;
			}
		case jmpeq_: 	// equal zero
			{
				outjmp(rnull, op2->label, jmpeq);
				break;
			}
		case jmpne_: 	// not equal
			{
				outjmp(rnull, op2->label, jmpne);
				break;
			}
		case mult_:
			{
				regs.changeReg( op1, op2 ); 						// Registerdeskriptor aendern (op2 wird zu op1)
				outmul(op1->vtype, regs.whichReg( op1 ), regs.whichReg( op3 ));		// Dann wird der op3 damit multipliziert
				regs.freeReg( op3 );
				break;
			}
		case divi_:
			{
				regs.changeReg( op1, op2 ); 						// Registerdeskriptor aendern (op2 wird zu op1)
				outdiv(op1->vtype, regs.whichReg( op1 ), regs.whichReg( op3 ));		// Dann wird der op1 durch op3 geteilt
				regs.freeReg( op3 );
				break;
			}
		case mod_:
			{
				regs.changeReg( op1, op2 ); 						// Registerdeskriptor aendern (op2 wird zu op1)
				outdiv(op1->vtype, regs.whichReg( op1 ), regs.whichReg( op3 ));		// Dann wird der op1 durch op3 geteilt
				outmul(op1->vtype, regs.whichReg( op1 ), regs.whichReg( op3 ));		// Nun wird op3 mit dem Ergebnis multipliziert
				regs.freeReg( op3 );
				break;
			}
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
			{
				regs.changeReg( op1, op2 ); 						// Registerdeskriptor aendern (op2 wird zu op1)
				outshl(op1->vtype, regs.whichReg( op1 ), regs.whichReg( op3 ));		// Dann wird der op1 um op3 stellen nach links geshiftet
				regs.freeReg( op3 );
				break;
			}
		case shiftr_:
			{
				regs.changeReg( op1, op2 ); 						// Registerdeskriptor aendern (op2 wird zu op1)
				outshr(op1->vtype, regs.whichReg( op1 ), regs.whichReg( op3 ));		// Dann wird der op1 um op3 stellen nach rechts geshiftet
				regs.freeReg( op3 );
				break;
			}
		case sminus_:
			{
				cout << "[bacom] sminus noch nicht implementiert\n";
				break;
			}
		case splus_:
			{
				cout << "[bacom] splus noch nicht implementiert\n";
				break;
			}
		case call_:
			{
				// Parameter liegen schon auf dem Stack
				// Also: R�cksprungadresse sichern
				
				outlic(rnull, rnull, 18);  // Instruction counter laden
				outstr(sint, rnull, rsp, 0); // auf den stack
				outsub(sint, rnull, rnull);
				outsub(sint, rsp, rnull, "const_two"); // stack weiterz�hlen
				outbra(rnull, op1->label); // Sprung zur Funktion
				
				// Hier kehren wir zur�ck:
				// in rnull steht jetzt noch die r�cksprungadresse!
				outsub(sint, rnull, rnull);
				
				// stackpointer muss auch noch zur�ckgeschoben werden:
				
				TType ret = fl.getReturnType(op1->no);
				
				if ((ret==slong)||(ret==sfloat)) outadd(sint, rsp, rnull, "const_six");
				else if (ret<slong) outadd(sint, rsp, rnull, "const_four");
				else outadd(sint, rsp, rnull, "const_two"); //void
				
				// Jetzt steht an sp der R�ckgabewert --> weitere Behandlung bei getRet
				
				
				// fertig
				
				break;
			}
		case goto_:
			{
				outbra(rnull, op1->label);
				break;
			}
		case getret_:
			{
				TReg r;
				// spillcode fehlt noch
				regs.getReg(op1, r);
				outstr(op1->vtype, r, rsp, 0); 

				break;
			}
		case char_:	// todo: abschneiden
			{
				if (op2->vtype==sfloat)		// float vorher nach long konvertieren
				{
					TReg r;
					op1->vtype=slong;	// vorher typ auf long, somit wird ein breites register geholt
					regs.getReg(op1, r);
					outcvt(slong, regs.whichReg( op1 ), regs.whichReg( op2 ) );
					regs.freeReg( op2 );
					regs.smallerReg(op1);
					break;
				}
				if (op2->vtype==slong)
				{
					regs.smallerReg(op2);
				}
				op2->vtype=schar;		// typ setzen, damit typen von op1 und op2 gleich
				regs.changeReg( op1, op2 );
				break;
			}
		case int_:
			{
				if (op2->vtype==sfloat)		// float vorher nach long konvertieren
				{
					TReg r;
					op1->vtype=slong;	// vorher typ auf long, somit wird ein breites register geholt
					regs.getReg(op1, r);
					outcvt(slong, regs.whichReg( op1 ), regs.whichReg( op2 ) );
					regs.freeReg( op2 );
					regs.smallerReg(op1);
					break;
				}
				if (op2->vtype==slong)
				{
					regs.smallerReg(op2);
				}
				op2->vtype=sint;		// typ setzen, damit typen von op1 und op2 gleich
				regs.changeReg( op1, op2 );
				break;
			}
		case long_:
			{
				if (op2->vtype<=sint)		// wenn convert von int/char, dann in ein doppelregister stecken
				{
					regs.biggerReg(op2);
					op2->vtype=slong;	// op2 wird long, damit changeReg wei�, dass op2 nun auch breites Register hat
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
				if (op2->vtype<=sint)		// wenn convert von int, dann zuerst in ein doppelregister stecken
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
		case intout:
			{
				outintout(regs.whichReg( op2 ));
				regs.changeReg( op1, op2);
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
	for (unsigned i=0;i<cl.getCount();i++)
	{
		bsm << "const_" << i <<":\tdc.";
		if ( cl.getType(i) == schar )
			bsm << "b";
		else if ( cl.getType(i) == sint )
			bsm << "w";
		else if ( cl.getType(i) == slong )
			bsm << "l";
		else if ( cl.getType(i) == sfloat )
			bsm << "f";

		bsm<<" "<<cl.getVal(i)<<endl;
	}

	// interne Konstanten
	for (unsigned i=1;i<=icl.getCount();i++)
	{
		bsm << "iconst_" << i <<":\tdc.";
		if ( icl.getType(i) == schar )
			bsm << "b";
		else if ( icl.getType(i) == sint )
			bsm << "w";
		else if ( icl.getType(i) == slong )
			bsm << "l";
		else if ( icl.getType(i) == sfloat )
			bsm << "f";

		bsm<<" "<<icl.getVal(i)<<endl;
	}
	
	bsm << "stp\n";
	bsm << "const_two:  dc.w 2 \n";
	bsm << "const_four:  dc.w 4 \n";
	bsm << "const_six:  dc.w 6 \n";
	bsm << "const_stack:  dc.w 65534 \n";  // Startwert Stackpointer

}

void Bacom::outloa( TType type, TReg dest, TReg help, int offset )
{
	bsm << "loa.";
	if ( type == schar )
		bsm << "b";
	else if ( type == sint )
		bsm << "w";
	else if ( type == slong )
		bsm << "l";
	else if ( type == sfloat )
		bsm << "f";
	bsm << " " << Register::toString( dest ) << ", " << Register::toString( help ) << ((offset>=0)?"+":"") << offset << endl;
}

void Bacom::outloa( TType type, TReg dest, TReg help, char* addr )
{
	bsm << "loa.";
	if ( type == schar )
		bsm << "b";
	else if ( type == sint )
		bsm << "w";
	else if ( type == slong )
		bsm << "l";
	else if ( type == sfloat )
		bsm << "f";
	bsm << " " << Register::toString( dest ) << ", " << Register::toString( help ) << "+" << addr << endl;
}

void Bacom::outstr( TType type, TReg src, TReg help, int offset )
{
	bsm << "str.";
	if ( type == schar )
		bsm << "b";
	else if ( type == sint )
		bsm << "w";
	else if ( type == slong )
		bsm << "l";
	else if ( type == sfloat )
		bsm << "f";
	bsm << " " << Register::toString( src ) << ", " << Register::toString( help ) << ((offset>=0)?"+":"") << offset << endl;
}

void Bacom::outadd( TType type, TReg dest, TReg src )
{
	bsm << "add.";
	if ( type == schar )
		bsm << "b";
	else if ( type == sint )
		bsm << "w";
	else if ( type == slong )
		bsm << "l";
	else if ( type == sfloat )
		bsm << "f";
	bsm << " " << Register::toString( dest ) << ", " << Register::toString( src ) << endl;
}

void Bacom::outadd( TType type, TReg dest, TReg src, char* c )
{
	bsm << "add.";
	if ( type == schar )
		bsm << "b";
	else if ( type == sint )
		bsm << "w";
	else if ( type == slong )
		bsm << "l";
	else if ( type == sfloat )
		bsm << "f";
	bsm << " " << Register::toString( dest ) << ", " << Register::toString( src ) << " + "<<c<< endl;
}


void Bacom::outsub( TType type, TReg dest, TReg src )
{
	bsm << "sub.";
	if ( type == schar )
		bsm << "b";
	else if ( type == sint )
		bsm << "w";
	else if ( type == slong )
		bsm << "l";
	else if ( type == sfloat )
		bsm << "f";
	bsm << " " << Register::toString( dest ) << ", " << Register::toString( src ) << endl;
}

void Bacom::outsub( TType type, TReg dest, TReg src, char* c )
{
	bsm << "sub.";
	if ( type == schar )
		bsm << "b";
	else if ( type == sint )
		bsm << "w";
	else if ( type == slong )
		bsm << "l";
	else if ( type == sfloat )
		bsm << "f";
	bsm << " " << Register::toString( dest ) << ", " << Register::toString( src ) << " + "<<c<< endl;
}

void Bacom::outmul( TType type, TReg dest, TReg src )
{
	bsm << "mul.";
	if ( type == schar )
		bsm << "b";
	else if ( type == sint )
		bsm << "w";
	else if ( type == slong )
		bsm << "l";
	else if ( type == sfloat )
		bsm << "f";
	bsm << " " << Register::toString( dest ) << ", " << Register::toString( src ) << endl;
}

void Bacom::outdiv( TType type, TReg dest, TReg src )
{
	bsm << "div.";
	if ( type == schar )
		bsm << "b";
	else if ( type == sint )
		bsm << "w";
	else if ( type == slong )
		bsm << "l";
	else if ( type == sfloat )
		bsm << "f";
	bsm << " " << Register::toString( dest ) << ", " << Register::toString( src ) << endl;
}

void Bacom::outshl( TType type, TReg dest, TReg src )
{
	bsm << "shl.";
	if ( type == sint )
		bsm << "w";
	else if ( type == slong )
		bsm << "l";
	bsm << " " << Register::toString( dest ) << ", " << Register::toString( src ) << endl;
}

void Bacom::outshr( TType type, TReg dest, TReg src )
{
	bsm << "shr.";
	if ( type == sint )
		bsm << "w";
	else if ( type == slong )
		bsm << "l";
	bsm << " " << Register::toString( dest ) << ", " << Register::toString( src ) << endl;
}

void Bacom::outmov(TReg r1, TReg r2)
{
	bsm << "mov.w " << Register::toString( r1 ) << "," << Register::toString( r2 ) << endl;
}

void Bacom::outcvt(TType type, TReg r1, TReg r2)
{
	bsm << "cvt.";
	if (type==sfloat)
		bsm << "f " ;
	else if (type==slong)
		bsm << "l ";
	bsm << Register::toString( r1 ) << ", " << Register::toString( r2 ) << endl;
}

void Bacom::outbra(TReg r, char* c)
{
	bsm<<"bra "<<Register::toString( r )<<"+"<<c<<endl;
}


void Bacom::outbra(TReg r, int offs)
{
	bsm<<"bra "<<Register::toString( r )<<"+"<<offs<<endl;
}


void Bacom::outjmp(TReg r, char* c, TJmp type)
{
	if (type==jmple)
		bsm<<"ble ";
	else if (type==jmpne)
		bsm<<"bne ";
	else if (type==jmpgr)
		bsm<<"bgr ";
	else if (type==jmpeq)
		bsm<<"beq ";
	bsm<<Register::toString( r )<<"+"<<c<<endl;
}

void Bacom::outlic(TReg r, TReg s, int offs)
{
	bsm<<"lic.w "<<Register::toString(r)<<", "<<Register::toString(s)<<"+"<<offs<<endl;
}

void Bacom::outintout(TReg r)
{
	bsm<<"out.w "<<Register::toString(r)<<endl;
}

char* Bacom::concat(char* pre, unsigned numb)
{
	char* c = (char*)malloc(30);
	strcpy(c, pre);
	sprintf (c+7,"%u", numb);
	return c;
}

