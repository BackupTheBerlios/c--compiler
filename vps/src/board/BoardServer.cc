#include "board/BoardServer.h"
/*
* @param net is a pointer to a network object for communication
* @param clientcount is the number of clients, which will register
* @param board_a is just a Board
* @param board_b is just another Board
* @param timesteps is the amount simulationcycles, 0 means infinity timesteps
*/
BoardServer::BoardServer(IPNetwork* net,int clientcount, Board* board_a, Board* board_b, int timesteps)
{	
	this->net = net;
	clients = clientcount;
	this->board_a = board_a;
	this->board_b = board_b;
	this->timesteps = timesteps;
	timestep = 0;
	
}


BoardServer::~BoardServer(){};


void BoardServer::start()
{
	// Anmeldung
	for(int i=0; i<clients; i++) 
	{
		cerr<<"[boardserver] waiting for client "<<i<<"...";
		logon();
		cerr<<"ok\n";
	}
	cout<<"[boardserver] ready\n";
	/*
	// Und los gehts
	for(timestep; timestep<timesteps; timestep++)
	{
		notcomplete = true;
		while(notcomplete)
		{
			IPAddress all(7654);
			char msg[13];	
			net->receive(all, &msg, sizeof(msg));
			int x = *(int*)(msg+1);
			int y = *(int*)(msg+5);
			int val = *(int*)(msg+9);
			
			if (*msg==1)  //setPos
				board_b->setPos(x, y, val);
			else if (*msg==2) //getPos
			{
				val = board_b->readPos(x, y);
				net->reply(all, msg, sizeof(msg));
			} else if (*msg==3) //barrier
			{
				barrier(all, timestep);
			} else
			{
				cout<<"[boardserver] unrecognized message\n";
				exit(-1);
			}
			
		}
	}
	*/
	
}

	
void BoardServer::logon()
{
	IPAddress all(7654);
	
	char hello;
	// auf client warten
	net->receive(all, &hello, sizeof(char));
	
	// in addressliste eintragen (in all steht jetzt die sourceaddr!)
	addresses[client] = (IPAddress)all;
	
	// feldauschnitt bestimmen
	int xstart = client*(board_a->getHeight()/clients);
	int xend = xstart+(board_a->getHeight()/clients)-1;
	
	// nachricht erzeugen
	int msg[4];
	msg[0] = xstart;
	msg[1] = xend;
	msg[2] = 0;
	msg[3] = board_a->getWidth()-1;
	
	
	// abschicken
	net->reply(addresses[client++], msg, sizeof(msg)); 
} 

/**
* This function is the global barrier for interstepsynchronization. All clients must call
* this function, before any of them gets a reply from the server. The reply can tell a client to
* calculate the next timestep or inform him of the end of simulation.
*
* @param ip is the address of the calling client
* @param timestep is the finished timestep which the client is signalling
*/
void BoardServer::barrier(IPAddress* ip,int timestep)
{
	 
}

/**
* This function tells a client, that it can continue to work or that the end of the simulation is reached.
*
* @param ip is the address of the client which should be notified
*/
void BoardServer::notify(IPAddress* ip){}

/**
* The more general notify, which sends the same notification to all clients.
*/
void BoardServer::notifyAll(){}




