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
	outloa(sint, rglobal, rnull, "const_global");
	
	// offset bis zum naechsten lokalen frame = 36
	unsigned para = 0;
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
				para = 0;
				bsm<<op1->label<<":\n";
				if (op1->type == funclabel)
				{
					// Die Parameter liegen bereits im lokalem Frame, jetzt werden die Register gerettet
					for (int i=0;i<15;i++)
					{
						outstr(sint, (TReg)i, rsp, 0 );
						outsub(sint, rsp, rnull, "const_two");
					}
					
					// Registerzuordnungen löschen
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
					else if (op2->type==gvar)
						outloa( op1->vtype, r, Register::typeToReg( op2->type ), op2->add );
					else if (op2->type==lvar)
						outloa( op1->vtype, r, Register::typeToReg( op2->type ), -(op2->add) );
					
					

				} else	// a:=t;
				{
					if (op1->type==gvar)
						outstr( op1->vtype, regs.whichReg( op2 ), rglobal,  op1->add );
					else 
						outstr( op1->vtype, regs.whichReg( op2 ), rlb,  -(op1->add) );
					regs.freeReg( op2 );
				}

				break;
			}


		case push_:
		{
			// Paramter ins lokale Frame der aufgerufenen Funktion schreiben
			unsigned offs = para++;
			unsigned add = fl.getParaAdd(op2->no, offs);
			outstr(op1->vtype, regs.whichReg(op1), rsp, -(36+add));
			break;
		}
		
		case ret_:
		{
			// Lokales Frame abräumen
			outadd(sint, rsp, rnull, concat("iconst_", fl.getFrameConstant(op2->no)) );
			
			// Rueckgabewert einschreiben
			if (op1!=0)
			{
				TReg r = regs.whichReg(op1);
				outstr(op1->vtype, r, rsp, 36);
			}
			
			// Register wiederherstellen
			outadd(sint, rsp, rnull, "const_two");
			for (int i=14;i>=0;i--)
			{
				outloa(sint, (TReg)i, rsp, 0 );
				outadd(sint, rsp, rnull, "const_two");
				
			}

			// Rücksprungadresse abräumen 
			outloa( sint, rnull, rsp, 0 );
			
			// Rücksprung
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
				
				// Platz machen für Rückgabewert
				outsub(sint, rsp, rnull, "const_four");
				
				// Rücksprungadresse sichern
				outlic(rglobal, rnull);  // Instruction counter laden
				outadd(sint, rglobal, rnull, "const_lic"); // offset dazuaddieren
				outstr(sint, rglobal, rsp, 0); // auf den stack
				outloa(sint, rglobal, rnull, "const_global"); // restore rglobal
				outsub(sint, rsp, rnull, "const_two"); // stack weiterzählen
				outbra(rnull, op1->label); // Sprung zur Funktion
				
				// Hier kehren wir zurück:
				// in rnull steht jetzt noch die rücksprungadresse!
				outsub(sint, rnull, rnull);
				
				// sp auf rückgabewert schieben
				outadd(sint, rsp, rnull, "const_four");
				
				// Jetzt steht an sp der Rückgabewert --> weitere Behandlung bei getRet
				
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
				//cout<<"getretstr: "<<op1->vtype<<endl;
				outloa(op1->vtype, r, rsp, 0); 

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
					outmov(regs.biggerReg(op2), rnull);	// hoeherwertiges Register nullen
					op2->vtype=slong;	// op2 wird long, damit changeReg weiß, dass op2 nun auch breites Register hat
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
					outmov(regs.biggerReg(op2), rnull);	// hoeherwertiges Register nullen
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
				out_out(sint, regs.whichReg( op2 ));
				regs.changeReg( op1, op2);
				break;
			}
		case charout:
			{
				out_out(schar, regs.whichReg( op2 ));
				regs.changeReg( op1, op2);
				break;
			}
		case longout:
			{
				out_out(slong, regs.whichReg( op2 ));
				regs.changeReg( op1, op2);
				break;
			}
		case floatout:
			{
				out_out(sfloat, regs.whichReg( op2 ));
				regs.changeReg( op1, op2);
				break;
			}
		case intin:
			{
				TReg r;
				regs.getReg(op1, r);
				out_in(sint, regs.whichReg( op1 ));
				break;
			}
		case charin:
			{
				TReg r;
				regs.getReg(op1, r);
				out_in(schar, regs.whichReg( op1 ));
				break;
			}
		case longin:
			{
				TReg r;
				regs.getReg(op1, r);
				out_in(slong, regs.whichReg( op1 ));
				break;
			}
		case floatin:
			{
				TReg r;
				regs.getReg(op1, r);
				out_in(sfloat, regs.whichReg( op1 ));
				break;
			}
		case stop:
			{
				bsm<<"stp\n";
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
	bsm << "const_stack:  dc.w 32764 \n";  // Startwert Stackpointer
	bsm << "const_global:  dc.w 10000 \n";  // Startwert globale variablen
	bsm << "const_lic:  dc.w 22 \n";  // rücksprungoffset zur lic anweisung

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

void Bacom::outlic(TReg r, TReg s)
{
	bsm<<"lic.w "<<Register::toString(r)<<", "<<Register::toString(s) << endl;
}

void Bacom::out_out(TType type, TReg r)
{
	bsm << "out.";
	if ( type == sint )
		bsm << "w ";
	else if ( type == schar )
		bsm << "b ";
	else if ( type == slong )
		bsm << "l ";
	else if ( type == sfloat )
		bsm << "f ";
	bsm<<Register::toString(r)<<endl;
}

void Bacom::out_in(TType type, TReg r)
{
	bsm << "inp.";
	if ( type == sint )
		bsm << "w ";
	else if ( type == schar )
		bsm << "b ";
	else if ( type == slong )
		bsm << "l ";
	else if ( type == sfloat )
		bsm << "f ";
	bsm<<Register::toString(r)<<endl;
}

char* Bacom::concat(char* pre, unsigned numb)
{
	char* c = (char*)malloc(30);
	strcpy(c, pre);
	sprintf (c+7,"%u", numb);
	return c;
}

