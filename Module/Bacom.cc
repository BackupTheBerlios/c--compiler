#include "Bacom.h"


void Bacom::genAsm()
{
	for(unsigned i=1; i<=ilList.count(); i++)
	{
		TOp* e = ilList.getelem(i);
		switch(e->TOpType)
		{
			case mov_: cout<<"mov"; break;
			
		}
	}
}

