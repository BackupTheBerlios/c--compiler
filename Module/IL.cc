#include "IL.h"



IL::IL()
{
	tempcount = 1;
}

/* generiert die Zwischensprache.
 * Durchlaufen der postfixlinearisierung von
 * start bis end.
 */
char* IL::genIL(unsigned* start, unsigned* end)
{
  cout<<endl;
  unsigned constcount = 1;
  char* lastident = 0;
  
  while(start<end)
  {
    
    
    switch (*start)
    {
	case IDENTIFIER:		{
				
					lastident = varid(*++start);
					 
					break;
					}
	case VARIABLE:			op.push(lastident);break;
      	case VAR_DECL_ST_2:		break;
      	case MULT_DIV_2:		{
					char* m1 = op.top();
					op.pop(1); 
					char* m2 = op.top();
					op.pop(1);
					char* p = tempid();
					outbin(p, m2, mult, m1);
					op.push(p);
					
					
					break;
					}
	case ADD_SUB_2:		{
					char* m1 = op.top();
					op.pop(1); 
					char* m2 = op.top();
					op.pop(1);
					char* p = tempid();
					outbin(p, m2, add, m1);
					op.push(p);
					
					
					break;
					}
	case EXPRESSION_2:		{
					char* src = op.top();
					op.pop(1);
					char* dst = op.top();
					op.pop(1);
					outcopy(dst,src);
					}
      case INT_CONSTANT:		op.push(conid(constcount++)); break;
    }
    start++;
  }
  return 0;
}


char* IL::varid(unsigned i)
{
	char* c = nl.getIdent(i);
	if (c==0) return 0;
	unsigned block = nl.getBlock(i);
	char* n = (char*)malloc(VAR_LENGTH_ID);
	strcpy(n,c);
	sprintf(n+strlen(c),"%u",block);
	return n;
}

char* IL::conid(unsigned i)
{
	TType t = cl.getType(i);
	if (t==0) return 0;
	
	char* n = (char*)malloc(VAR_LENGTH_ID);
	if (t==sint) strcpy(n,"int");
	sprintf(n+strlen(n),"%u",i);
	return n;

}

char* IL::tempid()
{
	char* n = (char*)malloc(VAR_LENGTH_ID);
	strcpy(n,"temp");
	sprintf (n+4,"%u",tempcount++);
	
	return n;
}

void IL::outcopy(char* l, char* r)
{
	cout<<l<<" := "<<r<<";\n";
}

void IL::outbin(char* l, char* x, TBinOp o, char* y)
{
	char* c = (char*)malloc(8);
	switch(o)
	{
		case shiftl: c = "<<"; break;
		case shiftr: c = ">>"; break;
		case mult: c = "*"; break; 
		case divi: c = "/"; break;
		case add: c = "+"; break;
		case sub: c = "-"; break;
	}
	cout<<l<<" := "<<x<<" "<<c<<" "<<y<<";\n";	
}

void IL::outun(char* l, TUnOp u, char* y)
{
}
