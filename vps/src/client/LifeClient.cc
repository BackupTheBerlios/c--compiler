#include "client/LifeClient.h"

/*
* Constructor gets a pointer to a IPNetwork object for communication,
* additionally the contact data for the server.
*
* @param net is the network object for communication
* @param servername is the name of the server for example "ep", not an ip address in ascii-representation
* @param port is the portnumber the boardserver listens
*/
LifeClient::LifeClient(IPNetwork* net, char* servername, short port)
{
	this->net=net;
	// set address and port
	server.resolve(servername, port);
	cout<<"[client] contacting server: ";
	
	// connect to server
	if (startUp()==-1)
	{
		cout<<"failed!\n";
		exit(-1);
	}
	cout<<"successful!\n";
	cout<<"[client] x1: "<<x1<<" x2: "<<x2<<" y1: "<<y1<<" y2: "<<y2<<endl;	
}

LifeClient::~LifeClient(){}


/**
* This function contacts the server and gets the outlines of the boarpart which should be worked on.
*
* @return a -1 if logon failed, else 0
*/
int LifeClient::startUp()
{
	int message[4];
	char req[]="X";
	
	// beim server anmelden
	net->request(server, (void*)req, 1, (void*)message, 20);
	
	// grenzen setzen
	x1 = message[0];
	x2 = message[1];
	y1 = message[2];
	y2 = message[3];		
	return 0;
}

/**
* Loops until server signals end of the simulation, and calls makeStep() for the next simulation cycle
*/
void LifeClient::loop(){}

/**
* Calculate status for the next timestep on the given boardpart
*/
void LifeClient::makeStep(){}
