#include "Stack.h"
#include <iostream>
#include <stdlib.h>
using namespace std;


#include <stdlib.h>

Stack::Stack()
{
	tos = 0;
}


void Stack::pop (int n)
{

	if ((n>0)&&(tos!=0))
	{
		tos = tos->next;
		pop(--n);
	}
}

void Stack::push (char* name)
{
	TStackEntry* e = (TStackEntry*)malloc(sizeof(TStackEntry));
	e->ret.name = name;
	e->next = tos;
	if (tos==0) start = e;
	tos = e;

}

void Stack::push (TType type)
{
	TStackEntry* e = (TStackEntry*)malloc(sizeof(TStackEntry));
	e->type = type;
	e->next = tos;
	if (tos==0) start = e;
	tos = e;

}


void Stack::push (char* name, TType type)
{
	TStackEntry* e = (TStackEntry*)malloc(sizeof(TStackEntry));
	e->ret.name = name;
	e->type = type;
	e->next = tos;
	if (tos==0) start = e;
	tos = e;

}

void Stack::push (unsigned block)
{
	TStackEntry* e = (TStackEntry*)malloc(sizeof(TStackEntry));
	e->ret.block = block;
	e->next = tos;
	if (tos==0) start = e;
	tos = e;
}

char* Stack::first ()
{

	if (tos==0) return 0;

	char* re = start->ret.name;
	TStackEntry* ctos = tos;
	while(1)
	{
		if (ctos==0) return 0;

	if (ctos->next == start) { start = ctos; ctos->next = 0; break; }
		if (ctos->next == 0) { tos = 0; start = 0; break; }
		ctos = ctos->next;
	}

	return re;
}

TType Stack::firsttype ()
{

	if (tos==0) return undeclared;

	TType re = start->type;
	TStackEntry* ctos = tos;
	while(1)
	{
		if (ctos==0) return undeclared;

	if (ctos->next == start) { start = ctos; ctos->next = 0; break; }
		if (ctos->next == 0) { tos = 0; start = 0; break; }
		ctos = ctos->next;
	}

	return re;
}




unsigned Stack::firsti ()
{
	if (tos==0) return 0;
	unsigned re = start->ret.block;
	TStackEntry* ctos = tos;
	while(1)
	{
		if (ctos==0) return 0;

	if (ctos->next == start) { start = ctos; ctos->next = 0; break; }
		if (ctos->next == 0) { tos = 0; start = 0; break; }
		ctos = ctos->next;
	}
	return re;
}

unsigned Stack::count()
{
	unsigned ct = 0;
	if (tos==0) return 0;
	TStackEntry* ctos = tos;
	while(1)
	{

		if (ctos==0) return ct;

		ctos = ctos->next;
		ct++;
	}
}

char* Stack::top ()
{
	if (tos!=0) return tos->ret.name;
	return 0;
}


TType Stack::toptype()
{
	if (tos!=0) return tos->type;
	return undeclared;
}


unsigned Stack::topi (unsigned i)
{
	if (i==0)
	{
		if (tos!=0) return tos->ret.block;
		return 0;
	}
	else
	{
		TStackEntry* ctos = tos;
		for (unsigned x=0;x<i;x++)
		{
			if (ctos==0) return 0;
			ctos = ctos->next;
		}
		if (ctos==0) return 0;

		return ctos->ret.block;
	}


}

void Stack::out()
{
	TStackEntry* ctos = tos;
	while(1)
	{
		if (ctos==0) return;
		cout<<ctos->ret.block<<"\n";
		ctos = ctos->next;
	}
}
