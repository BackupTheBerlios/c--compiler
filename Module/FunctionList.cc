#include "FunctionList.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

FunctionList::FunctionList()
{
	no = 0;
	start = (TFunctionListEntry*)malloc(sizeof(TFunctionListEntry)*MAX_NO_OF_FUNCTIONS);
	last = start;
}


unsigned FunctionList::insert(char* n, TType* sig, TType ret, unsigned num, bool proto, unsigned maxsp)
{
	if (no!=0) 
	{
		TFunctionListEntry* cur = start;
		unsigned c = MAX_NO_OF_VARIABLES+1;
		while(1)
		{
			if ((strcmp(cur->name,n)==0)&&(cur->num==num)&&(cur->proto)) 
			{
				cur->proto = 0;
				return c;
			}
			cur++;
			c++;
			if (cur==start+no) break;
		}
	}
	last->name = n;
	last->signature = sig;
	last->rettype = ret;
	last->num = num;
	last->next = 0;
	last->proto = proto;
	last->maxsp = maxsp;
	last++;
	return (no++)+MAX_NO_OF_VARIABLES+1;
}



unsigned FunctionList::isDefined(char* n, unsigned num, bool proto)
{	
	if (no==0) return 0;
	TFunctionListEntry* cur = start;
	unsigned c = MAX_NO_OF_VARIABLES+1;
	while(1)
	{
		//cout<<"name: "<<n<<" Sig: "<<sig<<"  curname: "<<cur->name<<" cursig: "<<cur->signature<<"\n";
		// NOCH KEINE AUSWERTUNG DER SIGNATUR
		//if ((strcmp(cur->name,n)==0)&&(strcmp(cur->signature,sig)==0)) return true; 
		if ((strcmp(cur->name,n)==0)&&(cur->num==num)&&(!(cur->proto&&proto))) return c;
		cur++;
		c++;
		if (cur==start+no) return 0;
	}
}

void FunctionList::out()
{
	if (no==0) { cout<<"<<leer>>"; return; }
	TFunctionListEntry* cur = start;
	
	while(1)
	{
		cout<<"Name: "<<cur->name<<" Sig: ";
		for(unsigned i=0;i<cur->num;i++) cout<<*(cur->signature+i)<<" ";
		cout<<" Ret: "<<cur->rettype<<" Proto: "<<cur->proto<<" Max-SP: "<<cur->maxsp<<"\n";
		cur++;
		if (cur==start+no) return;
	}
}


char* FunctionList::getIdent(unsigned u)
{
	if (u==0) return 0;
	return (start+u-MAX_NO_OF_VARIABLES-1)->name;
}

unsigned FunctionList::getNum(unsigned u)
{
	if (u==0) return 0;
	return (start+u-MAX_NO_OF_VARIABLES-1)->num;
}

unsigned FunctionList::nextId()
{
	return (no+MAX_NO_OF_VARIABLES+1);
}

char* FunctionList::checkForUnImplemented()
{
	if (no==0) return 0;
	TFunctionListEntry* cur = start;
	
	while(1)
	{
		if (cur->proto==1) return cur->name;
		cur++;
		if (cur==start+no) return 0;
	}
}


unsigned FunctionList::isProto(char* n, unsigned num)
{	
	if (no==0) return 0;
	TFunctionListEntry* cur = start;
	unsigned c = MAX_NO_OF_VARIABLES+1;
	while(1)
	{
		//cout<<"name: "<<n<<" Sig: "<<sig<<"  curname: "<<cur->name<<" cursig: "<<cur->signature<<"\n";
		// NOCH KEINE AUSWERTUNG DER SIGNATUR
		//if ((strcmp(cur->name,n)==0)&&(strcmp(cur->signature,sig)==0)) return true; 
		if ((strcmp(cur->name,n)==0)&&(cur->num==num)&&(cur->proto)) return c;
		cur++;
		c++;
		if (cur==start+no) return 0;
	}
}

TType FunctionList::getSigType(unsigned u, unsigned s)
{
	TFunctionListEntry* pos = start+u-MAX_NO_OF_VARIABLES-1;
	TType* sig = pos->signature;
	return *(sig+s);
}

TType FunctionList::getReturnType(unsigned u)
{
	TFunctionListEntry* pos = start+u-MAX_NO_OF_VARIABLES-1;
	return pos->rettype;
}




