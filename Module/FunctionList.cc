#include "FunctionList.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

FunctionList::FunctionList()
{
	last = 0;
}

void FunctionList::insert(char* n, char* sig, char* ret, unsigned num, bool proto)
{
	if (last==0)
	{
		last = (TFunctionListEntry*)malloc(sizeof(TFunctionListEntry));
		last->name = n;
		last->signature = sig;
		last->rettype = ret;
		last->num = num;
		last->next = 0;
		last->proto = proto;
	} else
	{
		TFunctionListEntry* tmp = (TFunctionListEntry*)malloc(sizeof(TFunctionListEntry));
		tmp->name = n;
		tmp->signature = sig;
		tmp->rettype = ret;
		tmp->num = num;
		tmp->next = last;
		tmp->proto = proto;
		last = tmp;
	}
	
}

bool FunctionList::isDefined(char* n, unsigned num, bool proto)
{	
	if (last==0) return false;
	TFunctionListEntry* cur = last;
	while(1)
	{
		//cout<<"name: "<<n<<" Sig: "<<sig<<"  curname: "<<cur->name<<" cursig: "<<cur->signature<<"\n";
		// NOCH KEINE AUSWERTUNG DER SIGNATUR
		//if ((strcmp(cur->name,n)==0)&&(strcmp(cur->signature,sig)==0)) return true; 
		if ((strcmp(cur->name,n)==0)&&(cur->num==num)&&(cur->proto&!proto)) return true; 
		cur = cur->next;
		if (cur==0) return false;
	}
}

void FunctionList::out()
{
	if (last==0) { cout<<"<<leer>>"; return; }
	TFunctionListEntry* cur = last;
	while(1)
	{
		cout<<"Name: "<<cur->name<<" Sig: "<<cur->signature<<" Ret: "<<cur->rettype<<"\n";
		cur = cur->next;
		if (cur==0) return;
	}
}

