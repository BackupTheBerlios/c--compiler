#include "NameList.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

NameList::NameList()
{
	
	no = 0;
	start = (TNameListEntry*)malloc(sizeof(TNameListEntry)*MAX_NO_OF_VARIABLES);
	last = start;
}

unsigned NameList::insert(char* n, unsigned b, TType type, unsigned add, bool isGlobal)
{
	last->name = n;
	last->block = b;
	last->type = type;
	last->add = add;
	last->isGlobal = isGlobal;
	
	last++;
	return (no++)+1;
}

unsigned NameList::isDefined(char* n, unsigned b)
{	
	if (no==0) return 0;
	TNameListEntry* cur = start;
	unsigned c = 1;
	while(1)
	{
		if ((strcmp(cur->name,n)==0)&&(cur->block==b)) return c;
		cur++;
		c++;
		if (cur==start+no) return 0;
	}
}

void NameList::out()
{
	if (no==0) { cout<<"<<leer>>"; return; }
	TNameListEntry* cur = start;
	
	while(1)
	{
		cout<<"Name: "<<cur->name<<" Block: "<<cur->block<<" Type: "<<cur->type<<" Addr: "<<cur->add<<" Global: "<<cur->isGlobal<<"\n";
		cur++;
		if (cur==start+no) return;
	}
}

TType NameList::typeOf(char* n, unsigned b)
{
	TNameListEntry* cur = start;
	while(1)
	{
		cout<<"Name: "<<cur->name<<" Block: "<<cur->block<<" Type: "<<cur->type<<"\n";
		if ((strcmp(n, cur->name)==0)&&(b==cur->block)) return cur->type;
		cur++;
		if (cur==start+no) return svoid;
	}
	
}

char* NameList::getIdent(unsigned u)
{
	if (u==0) return 0;
	return (start+u-1)->name;
}

unsigned NameList::getBlock(unsigned u)
{
	if (u==0) return 0;
	return (start+u-1)->block;
}

TType NameList::getType(unsigned u)
{
	if (u==0) return svoid;
	return (start+u-1)->type;
}

unsigned NameList::getAddr(unsigned u)
{
	if (u==0) return 0;
	return (start+u-1)->add;
}

bool NameList::isGlobal(unsigned u)
{
	if (u==0) return 0;
	return (start+u-1)->isGlobal;
}
