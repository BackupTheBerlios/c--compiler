#include "client/LifeClient.h"

/*
* Constructor gets a pointer to a IPNetwork object for communication,
* additionally the contact data for the server.
*
* @param net is the network object for communication
* @param servername is the name of the server for example "ep", not an ip address in ascii-representation
* @param port is the portnumber the boardserver listens
*/
LifeClient::LifeClient( IPNetwork* net, char* servername, short port )
{
	this->net = net;
	// set address and port
	server.resolve( servername, port );
	cout << "[client] contacting server: ";

	// connect to server
	if ( startUp() == -1 )
	{
		cout << "failed!\n";
		exit( -1 );
	}
	cout << "successful!\n";
	cout << "[client] x1: " << x1 << " x2: " << x2 << " y1: " << y1 << " y2: " << y2 << endl;
	cout << "[client] calculating... ";
	loop();
	cout << "finished!\n";
}

LifeClient::~LifeClient()
{}


/**
* This function contacts the server and gets the outlines of the boarpart which should be worked on.
*
* @return a -1 if logon failed, else 0
*/
int LifeClient::startUp()
{
	int message[ 4 ];
	int req = 'X';

	// beim server anmelden
	net->request( server, &req, 4, &message, 20 );

	// grenzen setzen
	x1 = message[ 0 ];
	x2 = message[ 1 ];
	y1 = message[ 2 ];
	y2 = message[ 3 ];
	return 0;
}

/**
* Loops until server signals end of the simulation, and calls makeStep() for the next simulation cycle
*/
void LifeClient::loop()
{
	char message;
	int req[2];	// request next Step
	req[0] = 'N';
	req[1] = -1;
 	net->request( server, &req, 8, &message, sizeof(message) );
	
	int step = 0;
	while (message==1)	// if Server sends 1, we calculate the next Step
	{
		makeStep();
		req[1] = step++;
		net->request( server, &req, 8,  &message, sizeof(message) );
	}
	cout<<"server sends: "<<message<<endl;
}

/**
* Calculate status for the next timestep on the given boardpart
*/
void LifeClient::makeStep()
{
	LocalBoard* board_a = new LocalBoard((x2-x1+2), (y2-y1+2));		// board wird zum cachen verwendet
	unsigned neighbours_alive;
	int x_,y_;
	// daten holen
	for (int x=(x1-1);x<(x2+1);x++)
	{
		for (int y=(y1-1);y<(y2+1);y++)
		{
			if (y==-1) 			y_=BOARD_HEIGHT-1;
			else if (y==BOARD_HEIGHT) 	y_=0;
			else				y_=y;
			if (x==-1) 			x_=BOARD_WIDTH-1;
			else if (x==BOARD_WIDTH) 	x_=0;
			else				x_=x;
			
			int message;					// todo: evt reihenfolge vertauscht?! wenn ja, einfach laufende nummer ins paket packen
			int req[3];
			req[ 0 ] = 1;			// Anfrage eines Punktes
			req[ 1 ] = x_;
			req[ 2 ] = y_;
// 			cout<<"G";
			net->request( server, &req, 12, &message, sizeof(message) );
			cout<<message<<" ";
			board_a->setPos(x-(x1-1), y-(y1-1), (life_status_t)message);
		}
	}
	
	// berechnung durchfuehren und daten uebermitteln
	for (int x=1;x<(x2-x1);x++)
	{
		for (int y=1;y<(y2-y1);y++)
		{
			// set count of neighbours
			neighbours_alive=0;

			if (board_a->readPos(x-1,y+1)==alive) neighbours_alive++;	// top left
			if (board_a->readPos(x-1,y)==alive) neighbours_alive++;		// top
			if (board_a->readPos(x-1,y+1)==alive) neighbours_alive++;	// top right
			if (board_a->readPos(x,y+1)==alive) neighbours_alive++;		// left
			if (board_a->readPos(x,y-1)==alive) neighbours_alive++;		// right
			if (board_a->readPos(x+1,y+1)==alive) neighbours_alive++;	// top left
			if (board_a->readPos(x+1,y)==alive) neighbours_alive++;		// top
			if (board_a->readPos(x+1,y-1)==alive) neighbours_alive++;	// top right

// 			if ( x>=BOARD_WIDTH || x<0 || y>=BOARD_HEIGHT || y<0 )
// 				cout<<"Index out of bounds!\n";

			char message;
			int req[ 4 ];
			req[ 0 ] = 2;			// Setzen eines Punktes
			req[ 1 ] = x+x1;
			req[ 2 ] = y+y1;
			// transmit positions to server
			if (neighbours_alive==3 && board_a->readPos(x,y)==dead)
			{
				req[ 3 ] = alive;
			}
			else
			{
				if ((board_a->readPos(x,y)==alive) && (neighbours_alive<2 || neighbours_alive>3))
				{
					req[ 3 ] = dead;
				}
				else
					req[ 3 ] = board_a->readPos(x,y);
			}

// 			cout<<"S";
			net->request( server, &req, 16, &message, sizeof(message) );

		}
	}
	
}
