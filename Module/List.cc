#include "List.h"
#include <iostream>
#include <stdlib.h>
using namespace std;


List::List()
{
	elems=0;
	start=0;
	end=0;
}

void List::del (unsigned n)
{
	if (elems==0 || n>elems || n<1)
	{
		cout<<"error while List::del\n";
		return;
	}
	TListEntry* curr=start;
	TListEntry* prev;
	for (unsigned i=0; i<n-1; i++)
	{
		prev=curr;
		curr=curr->next;
	}
	if (n==1)
	{
		start=curr->next;
	}
	else if (n==elems)
	{
		prev->next=0;
		end=prev;
	}
	else
	{
		prev->next=curr->next;
	}
	free(curr);
	if (elems==1)
	{
		start=0;
		end=0;
	}
	elems--;
	return;
}


void List::append (struct TOp *op)
{
	TListEntry* e = (TListEntry*)malloc(sizeof(TListEntry));
	e->op = op;
	e->next = 0;
	if (elems==0)
	{
		start=e;
	}
	else
	{
		end->next=e;
	}
	end=e;
	elems++;
}

void List::insert (struct TOp *op, unsigned n)
{
	if (n>elems+1 || n<1)
	{
		cout<<"error while List::insert\n";
		return;
	}
	TListEntry* e = (TListEntry*)malloc(sizeof(TListEntry));
	e->op = op;
	e->next = 0;
	if (elems==0)
	{
		start=e;
	}
	TListEntry* curr=start;
	TListEntry* prev;
	for (unsigned i=0; i<n-1; i++)
	{
		prev=curr;
		curr=curr->next;
	}
	prev->next=e;
	e->next=curr;
	elems++;
	if (elems==n) end=e;
}

struct TOp* List::getelem(unsigned n)
{
	if (elems==0 && n>elems) return (TOp*)0;
	TListEntry* curr=start;
	for (unsigned i=0; i<n-1; i++)
	{
		curr=curr->next;
	}
	return curr->op;
}

unsigned List::count()
{
	return elems;
}

void List::out()
{
	cout<<"IL-List:\n";
	if (elems==0) return;
	TListEntry* curr=start;
	for (unsigned i=0; i<elems; i++)
	{
		switch (curr->op->TOpType)
		{
			case mov_:
			cout<<"mov";
			break;

			case jmpgr_:
			cout<<"jmpgr";
			break;

			case jmple_:
			cout<<"jmple";
			break;

			case jmpeq_:
			cout<<"jmpeq";
			break;

			case jmpne_:
			cout<<"jmpne";
			break;

			case mult_:
			cout<<"mult";
			break;

			case divi_:
			cout<<"div";
			break;

			case mod_:
			cout<<"mod";
			break;

			case add_:
			cout<<"add";
			break;

			case sub_:
			cout<<"sub";
			break;

			case shiftl_:
			cout<<"shiftl";
			break;

			case shiftr_:
			cout<<"shiftr";
			break;

			case sminus_:
			cout<<"minus";
			break;

			case splus_:
			cout<<"plus";
			break;

			case call_:
			cout<<"call";
			break;

			case goto_:
			cout<<"goto";
			break;

			case label_:
			cout<<"label";
			break;

			case ret_:
			cout<<"ret";
			break;

			case getret_:
			cout<<"getret";
			break;

			case push_:
			cout<<"push";
			break;

			case char_:
			cout<<"toChar";
			break;

			case int_:
			cout<<"toInt";
			break;

			case long_:
			cout<<"toLong";
			break;

			case float_:
			cout<<"tofloat";
			break;
			
			case intout:
			cout<<"intout";
			break;
			
			case charout:
			cout<<"charout";
			break;
			
			case longout:
			cout<<"longout";
			break;
			
			case floatout:
			cout<<"floatout";
			break;

			case intin:
			cout<<"intin";
			break;
			
			case charin:
			cout<<"charin";
			break;
			
			case longin:
			cout<<"longin";
			break;
			
			case floatin:
			cout<<"floatin";
			break;
		}
		
		for (int i=0;i<3;i++)
		{
			TOperand* co;
			if (i==0) co = curr->op->operand1;
			if (i==1) co = curr->op->operand2;
			if (i==2) co = curr->op->operand3;
			if (co==0) break;
			cout<<"\t";
			if (co->type==lvar) cout<<"lb+";
			if (co->type==gvar) cout<<"g:";
// 			if (co->type==constant) cout<<"c:";
			if ((co->type==labelstring) || (co->type==temp) || (co->type==constant)|| (co->type==funclabel)) cout<<co->label; else cout<<co->add;
		
		}
	
		cout<<";"<<endl;
		curr=curr->next;
	}
	return;
}
