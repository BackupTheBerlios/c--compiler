#include "ConstList.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

ConstList::ConstList()
{
	last = 0;
	curadd = 0;
	nmb = 0;
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
	}
	else
	{
		TConstListEntry* tmp = (TConstListEntry*)malloc(sizeof(TConstListEntry));
		tmp->val.c = c;
		tmp->t = schar;
		tmp->ct = ct;
		tmp->next = last;
		last = tmp;
	}
	last->add = curadd++;
	nmb++;
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
	}
	else
	{
		TConstListEntry* tmp = (TConstListEntry*)malloc(sizeof(TConstListEntry));
		tmp->val.i = c;
		tmp->t = sint;
		tmp->ct = ct;
		tmp->next = last;
		last = tmp;
	}


	curadd = align(curadd,2);
	last->add = curadd;
	curadd+=2;
	nmb++;
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
	}
	else
	{
		TConstListEntry* tmp = (TConstListEntry*)malloc(sizeof(TConstListEntry));
		tmp->val.f = c;
		tmp->t = sfloat;
		tmp->ct = ct;
		tmp->next = last;
		last = tmp;
	}
	curadd = align(curadd,4);
	last->add = curadd;
	curadd+=4;
	nmb++;
}




TType ConstList::getType(unsigned u)
{
	if (last==0)  return (TType)0;
	TConstListEntry* cur = last;
	while(1)
	{
		if (cur->ct == u) return cur->t;
		cur = cur->next;
		if (cur==0) return (TType)0;
	}
	return (TType)0;
}


unsigned ConstList::getAddr(unsigned u)
{
	if (last==0)  return 0;
	TConstListEntry* cur = last;
	while(1)
	{
		if (cur->ct == u) return cur->add;
		cur = cur->next;
		if (cur==0) return 0;
	}
	return 0;
}


char* ConstList::getVal(unsigned u)
{
	if (last==0)  return 0;
	TConstListEntry* cur = last;
	while(1)
	{
		if (cur->ct == u)
		{
			char* n=(char*)malloc(10);
			if (cur->t==schar) sprintf (n,"%c",cur->val.c);
			else if (cur->t==sint) sprintf (n,"%i",cur->val.i);
			else if (cur->t==sfloat) sprintf (n,"%f",cur->val.f);
			else sprintf (n,"%u",cur->val.u);
			return n;
		}
		cur = cur->next;
		if (cur==0) return 0;
	}
	return 0;
}

int ConstList::getIntVal(unsigned u)
{
	if (last==0)  return 0;
	TConstListEntry* cur = last;
	while(1)
	{
		if (cur->ct == u) return cur->val.i;
		cur = cur->next;
		if (cur==0) return 0;
	}
	return 0;
	
}


void ConstList::out()
{
	if (last==0) { cout<<"<<leer>>"; return; }
	TConstListEntry* cur = last;

	while(1)
	{
		cout<<"No: "<<cur->ct<<" Val: ";
		if (cur->t==schar) cout<<cur->val.c<<"\tType: Char";
		else if (cur->t==sint) cout<<cur->val.i<<"\tType: Int";
		else if (cur->t==sfloat) cout<<cur->val.f<<"\tType: Float";
		cout<<" Addr: "<<cur->add<<endl;
		cur = cur->next;
		if (cur==0) return;
	}
}

unsigned ConstList::align(unsigned size, unsigned alignm)
{
	return ((size+alignm-1)/alignm)*alignm;
}

unsigned ConstList::getSize()
{
	return curadd;
}

unsigned ConstList::getCount()
{
	return nmb;
}
