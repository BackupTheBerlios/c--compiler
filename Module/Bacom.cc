#include "Bacom.h"


void Bacom::genAsm()
{
	cout<<"\nBASM Ausgabe:\n";
	for(unsigned i=1; i<=ilList.count(); i++)
	{
		TOp* e = ilList.getelem(i);
		TOperand* op1 = e->operand1;
		TOperand* op2 = e->operand2;
		TOperand* op3 = e->operand3;
		
		switch(e->TOpType)
		{
			
			case label_:
			{
				cout<<op1->label<<":\n";
				break;
			}
			case mov_: 
			{
				if (op1->type == temp)	// t:=a;
				{
					TReg r;
					regs.getReg(op1, r);
					
					outloa(op1->vtype, r, Register::typeToReg(op2->type), op2->add);
				} else	// a:=t;
				{
					outstr(op1->vtype, regs.whichReg(op2), ((op1->type==gvar)?rglobal:rlb), op1->add);
					regs.freeReg(op2);
				}
				
				break;
			}
			
			default:
			{
				cout<<"[bacom] noch nicht implementiert\n";
				break;
			}
			
		}
	}
}


void Bacom::outloa(TType type, TReg dest, TReg help, int offset)
{
	cout<<"loa.";
	if (type==schar) cout<<"b";
	else if (type==sint) cout<<"w";
	else if (type==slong) cout<<"l";
	else if (type==sfloat) cout<<"f";
	cout<<" "<<Register::toString(dest)<<" "<<Register::toString(help)<<"+"<<offset<<endl;
}

void Bacom::outstr(TType type, TReg src, TReg help, int offset)
{
	cout<<"str.";
	if (type==schar) cout<<"b";
	else if (type==sint) cout<<"w";
	else if (type==slong) cout<<"l";
	else if (type==sfloat) cout<<"f";
	cout<<" "<<Register::toString(src)<<" "<<Register::toString(help)<<"+"<<offset<<endl;
}



