#ifndef functionlist_h
#define functionlist_h

class FunctionList
{
public:


struct TFunctionListEntry
{
	char* name;
	char* signature;
	char* rettype;
	unsigned num;
	struct TFunctionListEntry* next;
	bool proto;
};

FunctionList();

void insert(char*, char*, char*, unsigned, bool);

bool isDefined(char*, unsigned, bool);

void out();



private:
	
	struct TFunctionListEntry* last;
	
};




#endif
