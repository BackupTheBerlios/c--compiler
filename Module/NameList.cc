#include "NameList.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

NameList::NameList()
{
	
	no = 0;
	start = (TNameListEntry*)malloc(sizeof(TNameListEntry)*1024);
	last = start;
}

unsigned NameList::insert(char* n, unsigned b, char* ttype)
{
	last->name = n;
	last->block = b;
	last->ttype = ttype;
	
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
		cout<<"Name: "<<cur->name<<" Block: "<<cur->block<<" Type: "<<cur->ttype<<"\n";
		cur++;
		if (cur==start+no) return;
	}
}

char* NameList::typeOf(char* n, unsigned b)
{
	TNameListEntry* cur = start;
	while(1)
	{
		cout<<"Name: "<<cur->name<<" Block: "<<cur->block<<" Type: "<<cur->ttype<<"\n";
		if ((strcmp(n, cur->name)==0)&&(b==cur->block)) return cur->ttype;
		cur++;
		if (cur==start+no) return 0;
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




