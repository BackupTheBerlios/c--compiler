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
		
		while(1)
		{
			IPAddress all(7654);	
			char hello;
			
			// auf client warten
			net->receive(all, &hello, sizeof(char));
			if (hello=='X') 
			{
				// in all steht die sourceaddr!
				logon(&all);
				break;
			}
		}
	
		
		cerr<<"ok\n";
	}
	cout<<"[boardserver] ready\n";
	
	notifyAll();
	
	// Und los gehts
	for( ; timestep<timesteps; timestep++)
	{
		cout<<"[boardserver] step "<<timestep<<endl;
		notcomplete = true;
		while(notcomplete)
		{
			IPAddress all(7654);
			int msg[4];	
			net->receive(all, &msg, sizeof(msg));
			
			if (msg[0]==2)  //setPos
			{
				cout<<"S";
				board_b->setPos(msg[1], msg[2], (life_status_t)msg[3]);
				char anything;
				net->reply(all, &anything, 1);
			}
			else if (msg[0]==1) //getPos
			{
				cout<<"G";
				int val = board_a->readPos(msg[1], msg[2]);
				net->reply(all, &val, sizeof(life_status_t));
			} else if (msg[0]=='N') //barrier
			{
				cout<<"N";
				barrier(&all, msg[1]);
			} else
			{
				cout<<"[boardserver] unrecognized message\n";
				exit(-1);
			}
			
		}
		// Berechnungsschritt fertig
		cout<<"[boardserver] step "<<timestep<<" completed"<<endl;
		// boards tauschen
		Board* temp = board_a;
		board_a = board_b;
		board_b = temp;
		
		// Clients benachrichtigen
		notifyAll();
		
		
	}
	cout<<"[boardserver] fertig\n";
	
	
}

	
void BoardServer::logon(IPAddress* ip)
{
	
	// in addressliste eintragen
	addresses[client] = *ip;
	
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
	if (timestep==-1) return;
	if (this->timestep!=timestep)
	{
		cout<<"[boardserver] received message from timestep "<<timestep<<" but we are in "<<this->timestep<<endl;
		//exit(-1);
	}
	for(int i; i<clients; i++)
	{
		if (addresses[i] == *ip)
		{
			completed[i] = true;
			cout<<"[boardserver] client "<<i<<" finished step "<<timestep<<endl;
		}
	}
	bool c = true;
	for(int i; i<clients; i++) 
	{
		c &= completed[i];
		if (!c) return;
	}
	notcomplete = false; 
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
void BoardServer::notifyAll()
{
	for (int i=0; i<clients; i++)
	{
		// 1 wenns noch einen nächsten Schritt gibt, sonst 0
		char r  = (timestep==(timesteps-1))?0:1;
		net->reply(addresses[i], &r, 1);
	}
}



