#include "board/BoardServer.h"
#include "board/LocalBoard.h"

#define ZOOM 3
#define RANDOM 7

/**
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
	timestep = -1;
	client = 0;
	
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
			int hello = 0;
			
			// auf client warten
			net->receive(all, &hello, sizeof(hello));
			if (hello=='Y') 
			{
				// in all steht die source:addr!
				logon(&all);
				break;
			} else
			{
				int anything=2;		// client muss noch warten
				net->reply(all, &anything, sizeof(anything));
			}
		}
	
		
		cerr<<"ok\n";
	}
	cout<<"[boardserver] ready\n";
	
	Color alivecol = White;
	Color deadcol = Blue2;
	XWindow* w = new XWindow( BOARD_WIDTH * ZOOM, BOARD_HEIGHT * ZOOM, "Game of Life" );

	for ( int x = 0;x < BOARD_WIDTH;x++ )
	{
		for ( int y = 0;y < BOARD_HEIGHT;y++ )
		{
			if (((LocalBoard*)board_a)->readPos( x, y ) == invalid)
			{
				cout << "Load error, x: " << x << ", y: "<<y<<endl;
				exit(-1);
			}
			w->fillRectangle( ( ((LocalBoard*)board_a)->readPos( x, y ) == alive ) ? alivecol : deadcol, x * ZOOM, y * ZOOM, ZOOM, ZOOM );
		}
	}
	w->flush();
	
	// Und los gehts
	for( timestep = 0 ; timestep<timesteps; timestep++)
	{
		cout<<"[boardserver] step "<<timestep<<endl;
		notcomplete = true;
		while(notcomplete)
		{
			IPAddress all(7654);
			int msg[5];	
			net->receive(all, &msg, sizeof(msg));
			
			if (msg[0]=='S')  //setPos
			{
				//cout<<msg[1]<<" "<<msg[2]<<" | ";
				board_b->setPos(msg[1], msg[2], (life_status_t)msg[3]);
				int anything=msg[ 4 ];
				net->reply(all, &anything, sizeof(anything));

			}
			else if (msg[0]=='G') //getPos
			{
				//cout<<"G";
				int val[ 2 ];
				val[ 0 ] = board_a->readPos(msg[1], msg[2]);
				val[ 1 ] = msg[ 3 ];
// 				cout<<"seqnr: "<<msg[3]<<endl;
				net->reply(all, &val, sizeof(val));
			} else if (msg[0]=='N') //barrier
			{
				//cerr<<"N\n";
				barrier(&all, msg[1], msg[2]);
			} else
			{
				cout<<"[boardserver] unrecognized message\n";
				exit(-1);
			}
			
		}
				
		/********** zeichnen ********/
		char* count = ( char* ) malloc( 16 );
		for ( int x = 0;x < BOARD_WIDTH;x++ )
		{
			for ( int y = 0;y < BOARD_HEIGHT;y++ )
			{
				w->fillRectangle( ( board_b->readPos( x, y ) == alive ) ? alivecol : deadcol, x * ZOOM, y * ZOOM, ZOOM, ZOOM );
			}
		}
		strcpy( count, "Durchlauf: " );
		sprintf( count + 11, "%u", timestep );
		if ( timestep < 10 )
			w->write( Green1, 10, 10, count, 12 );
		else if ( timestep < 100 )
			w->write( Green1, 10, 10, count, 13 );
		else if ( timestep < 1000 )
			w->write( Green1, 10, 10, count, 14 );
		else
			w->write( Green1, 10, 10, count, 15 );
		w->flush();
		/********** ende zeichnen ********/

		// Berechnungsschritt fertig
		cout<<"[boardserver] step "<<timestep<<" completed"<<endl;
		
		// boards tauschen
		Board* temp = board_a;
		board_a = board_b;
		board_b = temp;
		
	}

	// Abmeldung
	for(int i=0; i<clients; i++) 
	{
		cerr<<"[boardserver] waiting for client "<<i<<" to sign off...";
		
		while(1)
		{
			IPAddress all(7654);	
			int msg[5];	
			// auf client warten
			net->receive(all, &msg, sizeof(msg));
			
			if (msg[0]=='N') 
			{
				int anything=0;		// ende
				net->reply(all, &anything, sizeof(anything));
				break;
			}
		}
		cerr<<"ok\n";
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
	int msg[5];
	msg[0] = xstart;
	msg[1] = xend;
	msg[2] = 0;
	msg[3] = board_a->getWidth()-1;
	msg[4] = client;
	
	
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
void BoardServer::barrier(IPAddress* ip, int timestep, int clientid)
{
	cout<<"timestep "<<timestep<<" from client "<<clientid<<endl;
	if (timestep>=(timesteps-1))
	{
		int repl=2;
		net->reply(*ip, &repl, sizeof(repl));
		notcomplete=false;
		return;
	}
	if (this->timestep>timestep)	// client hat die bestaetigung schon einmal gesendet, sonst waere der timestep noch nicht weiter gezaehlt
	{
		int repl=1;
		net->reply(*ip, &repl, sizeof(repl));
		return;
	}
	if (this->timestep<timestep)
	{
		cout<<"[boardserver] received message from timestep "<<timestep<<" but we are in "<<this->timestep<<endl;
		//exit(-1);
	}
	
	completed[clientid] = true;
	cout<<"[boardserver] client "<<clientid<</*" at port "<<ip->getPort()<<*/" finished step "<<timestep<<endl;
	
	
	bool c = true;
	for (int i=0; i<clients; i++)
	{
		c &= completed[i];
		if (!c)
		{
			int repl=2;
			net->reply(*ip, &repl, sizeof(repl));
			return;
		}
	}

	int anything=1;		// naechster schritt
	net->reply(*ip, &anything, sizeof(anything));
	notcomplete = false;
	for(int i=0; i<clients; i++)
	{
		completed[i] = false;
	}
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
		int r  = (timestep==(timesteps-1))?0:1;
		cout<<"server sends: "<<r<<endl;
		net->reply(addresses[i], &r, sizeof(r));
	}
}
