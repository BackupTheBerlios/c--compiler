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
};

LifeClient::~LifeClient(){};


/**
* This function contacts the server and gets the outlines of the boarpart which should be worked on.
*
* @return a -1 if logon failed, else 0
*/
int LifeClient::startUp()
{
	char message[20];
	char req[]="hello server";
	net->request(server,(void *)req,13,message,20);
	cout<<"[client] received: "<<message<<endl;
	
	
	return 0;
};

/**
* Loops until server signals end of the simulation, and calls makeStep() for the next simulation cycle
*/
void LifeClient::loop(){};

/**
* Calculate status for the next timestep on the given boardpart
*/
void LifeClient::makeStep(){};
