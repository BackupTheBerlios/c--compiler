#include "X/XWindow.h"
#include "net/IPAddress.h"
#include "net/IPNetwork.h"
#include "net/UDPNetwork.h"
#include "client/LifeClient.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc!=2)
	{
		cout<<"Usage: client [server]\n";
		exit(-1);
	}
	char* server=argv[1];
	
	UDPNetwork* net = new UDPNetwork();
	LifeClient* client = new LifeClient((IPNetwork *)net,server,7654);

}

