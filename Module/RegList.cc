#include "RegList.h"
#include <iostream>
#include <stdlib.h>
using namespace std;


RegList::RegList()
{
	elems=0;
	start=0;
	end=0;
	maxcount=0;
}

void RegList::invalidate()
{
	for (unsigned i=0;i<elems;i++)
		del(start->op);
	return;
}

bool RegList::del (struct TOperand* op)
{
	TRegListEntry* curr=start;
	TRegListEntry* prev=0;
	while (curr!=0)
	{
		if (curr->op==op)
		{
			if (curr==start)
			{
				start=curr->next;
				return true;
			}
			if (curr==end)
			{
				prev->next=0;
				end=prev;
				return true;
			}
			prev=curr->next;
			return true;
			// todo: Speicher wieder frei geben
		}
		prev=curr;
		curr=curr->next;
	}
	return false;
}


void RegList::append (struct TOperand *op, TReg r)
{
	// Speicherbereich holen, Spillcode in bsm schreiben
	char* x=(char*)malloc(10);
	strcpy(x,"spill_");
	sprintf (x+6,"%u",maxcount++);
	
	bsm<<"// Spillcode: Auslagern"<<endl;
	bsm<<"str.";
	if (op->vtype==schar) bsm<<"b";
	else if (op->vtype==sint) bsm<<"w";
	else if (op->vtype==slong) bsm<<"l";
	else if (op->vtype==sfloat) bsm<<"f";
	bsm<<"\tr"<<r<<", r"<<rnull<<" + "<<x<<endl;
	
	spilldata<<x<<":\tds.";
	if (op->vtype==schar) spilldata<<"b";
	else if (op->vtype==sint) spilldata<<"w";
	else if (op->vtype==slong) spilldata<<"l";
	else if (op->vtype==sfloat) spilldata<<"f";
	spilldata<<"\t1"<<endl;
	
	TRegListEntry* e = (TRegListEntry*)malloc(sizeof(TRegListEntry));
	e->op = op;
	e->label=x;
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

void RegList::append (struct TOperand *op, char* label)
{
	TRegListEntry* e = (TRegListEntry*)malloc(sizeof(TRegListEntry));
	
	e->op = op;
	e->label=label;
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

bool RegList::isValid(struct TOperand *op)
{
	TRegListEntry* curr=start;
	while (curr!=0)
	{
		if (curr->op==op)
			return true;
		curr=curr->next;
	}
// 	cout<<"not valid!\n";
	return false;
}

char* RegList::where(struct TOperand *op)
{
	TRegListEntry* curr=start;
	while (curr!=0)
	{
		if (curr->op==op)
			return curr->label;
		curr=curr->next;
	}
	cout<<"RegList::where error!\n";
	return 0;
}

unsigned RegList::count()
{
	return elems;
}
