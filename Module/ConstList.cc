#include "ConstList.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

ConstList::ConstList()
{
	last = 0;
}
void ConstList::insert(char c, unsigned ct)
{
	if (last==0)
	{
		last = (TConstListEntry*)malloc(sizeof(TConstListEntry));
		last->val.c = c;
		last->t = schar;
		last->next = 0;
		last->ct = ct;
	} else
	{
		TConstListEntry* tmp = (TConstListEntry*)malloc(sizeof(TConstListEntry));
		tmp->val.c = c;
		tmp->t = schar;
		tmp->ct = ct;
		tmp->next = last;
		last = tmp;
	}
	
}

void ConstList::insert(int c, unsigned ct)
{
	if (last==0)
	{
		last = (TConstListEntry*)malloc(sizeof(TConstListEntry));
		last->val.i = c;
		last->t = sint;
		last->next = 0;
		last->ct = ct;
	} else
	{
		TConstListEntry* tmp = (TConstListEntry*)malloc(sizeof(TConstListEntry));
		tmp->val.i = c;
		tmp->t = sint;
		tmp->ct = ct;
		tmp->next = last;
		last = tmp;
	}
	
}
void ConstList::insert(double c, unsigned ct)
{
	if (last==0)
	{
		last = (TConstListEntry*)malloc(sizeof(TConstListEntry));
		last->val.f = c;
		last->t = sfloat;
		last->next = 0;
		last->ct = ct;
	} else
	{
		TConstListEntry* tmp = (TConstListEntry*)malloc(sizeof(TConstListEntry));
		tmp->val.f = c;
		tmp->t = sfloat;
		tmp->ct = ct;
		tmp->next = last;
		last = tmp;
	}
	
}




TType ConstList::getType(unsigned u)
{
	if (last==0)  return (TType)0;
	TConstListEntry* cur = last;
	while(1)
	{
		if (cur->ct = u) return cur->t;
		cur = cur->next;
		if (cur==0) return (TType)0;
	}
	return (TType)0;
}



void ConstList::out()
{
	if (last==0) { cout<<"<<leer>>"; return; }
	TConstListEntry* cur = last;
	
	while(1)
	{
		cout<<"No: "<<cur->ct<<" Val: ";
		if (cur->t==schar) cout<<cur->val.c;
		else if (cur->t==sint) cout<<cur->val.i;
		else if (cur->t==sfloat) cout<<cur->val.f;
		cout<<endl;
		cur = cur->next;
		if (cur==0) return;
	}
}

