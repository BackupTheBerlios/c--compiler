#include "X/XWindow.h"
#include "net/IPAddress.h"
#include "net/IPNetwork.h"
#include "net/UDPNetwork.h"
#include "client/LifeClient.h"
#include <iostream>
using namespace std;

int main()
{
	UDPNetwork* net = new UDPNetwork();
// 	LifeClient* client = new LifeClient((IPNetwork *)net,"localhost",7654);
	LifeClient* client = new LifeClient((IPNetwork *)net,"192.168.123.2",7654);
// 	LifeClient* client = new LifeClient((IPNetwork *)net,"192.168.208.154",7654);
}

