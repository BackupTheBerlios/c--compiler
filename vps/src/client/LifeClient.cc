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
	seqn=0;
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
	cout << "[client] calculating... \n";
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
	int message[ 4 ] = { 0,0,0,0 };
	int req = 'Y';
	

	// beim server anmelden
	net->request( server, &req, sizeof(req), &message, sizeof(message) );

	// grenzen setzen
	x1 = message[ 0 ];
	x2 = message[ 1 ];
	y1 = message[ 2 ];
	y2 = message[ 3 ];
	board_a = new LocalBoard((x2-x1+3), (y2-y1+3));		// board wird zum cachen verwendet, es wird der zu berechnende Ausschnitt, sowie ein Rand von 1 gespeichert
// 	cout<<"Abmasse cache_board: x: "<<(x2-x1+3)<<", y: "<<(y2-y1+3)<<endl;
	return 0;
}

/**
* Loops until server signals end of the simulation, and calls makeStep() for the next simulation cycle
*/
void LifeClient::loop()
{
	int message = 0;
	int req[2];	// request next Step
	req[0] = 'N';
	req[1] = -1;
	cout<<"A";
 	net->request( server, &req, sizeof(req), &message, sizeof(message));
	cout<<"B";
	int step = 0;
	while (message!=0)	// if Server sends 1, we calculate the next Step
	{
		cout<<"*";
		makeStep();
		req[0] = 'N';
		req[1] = step++;
		message = 0;
		
		net->request( server, &req, 8,  &message, 4 );
		cout<<"server sends: "<<message<<" from "<<server.getAddr()<<endl;
	}
}

/**
* Calculate status for the next timestep on the given boardpart
*/
void LifeClient::makeStep()
{
	unsigned neighbours_alive;
	int x_,y_;
	// daten holen
	for (int x=(x1-1);x<=x2+1;x++)
	{
// 		if(x%10==0) cout<<x<<endl;
		for (int y=(y1-1);y<=y2+1;y++)
		{
			// Punkte fuer die Anfrage bestimmen
			if (y==-1)			y_=BOARD_HEIGHT-1;
			else if (y==BOARD_HEIGHT)	y_=0;
			else				y_=y;
			if (x==-1)			x_=BOARD_WIDTH-1;
			else if (x==BOARD_WIDTH)	x_=0;
			else				x_=x;
			
			int response[ 2 ];
			int req[ 4 ];
			req[ 0 ] = 'G';			// Anfrage eines Punktes
			req[ 1 ] = x_;
			req[ 2 ] = y_;
			req[ 3 ] = seqn++;
// 			cout<<"G";
// 			cout<<"get-req an Server - x_: "<<req[ 1 ]<<", y_: "<<req[ 2 ]<<", x: "<<x<<", y: "<<y<<", setzen an: x: "<<(x-(x1-1))<<", y: "<<(y-(y1-1))<<endl;
			net->request( server, &req, sizeof(req), &response, sizeof(response) );
			while (req[ 3 ]!=response[ 1 ])
			{
//  				cout<<"get seqnr mismatch: "<<req[3]<<", "<<response[1]<<"req - x_: "<<req[ 1 ]<<", y_: "<<req[ 2 ]<<endl;
				net->request( server, &req, sizeof(req), &response, sizeof(response) );
			}
// 			if (req[ 3 ]==response[ 1 ]) cout<<"get erfolg!\n";
			if (response[ 0 ]==invalid)
				cout<<"x_: "<<x_<<", y_: "<<y<<", error!\n";
			board_a->setPos( (x-(x1-1)), (y-(y1-1)), (life_status_t)response[ 0 ]);

		}
	}
	
	// berechnung durchfuehren und daten uebermitteln
	for (int x=1;x<=(x2-x1)+1;x++)
	{
// 		if(x%10==0) cout<<x<<endl;
		for (int y=1;y<=(y2-y1)+1;y++)
		{
			// set count of neighbours
			neighbours_alive=0;

			if (board_a->readPos(x-1, y-1)==alive) neighbours_alive++;	// top left
			if (board_a->readPos(x,   y-1)==alive) neighbours_alive++;	// top
			if (board_a->readPos(x+1, y-1)==alive) neighbours_alive++;	// top right
			if (board_a->readPos(x-1, y)==alive) neighbours_alive++;	// left
			if (board_a->readPos(x+1, y)==alive) neighbours_alive++;	// right
			if (board_a->readPos(x-1, y+1)==alive) neighbours_alive++;	// bottom left
			if (board_a->readPos(x,   y+1)==alive) neighbours_alive++;	// bottom
			if (board_a->readPos(x+1, y+1)==alive) neighbours_alive++;	// bottom right

			if ( x>BOARD_WIDTH || x<0 || y>BOARD_HEIGHT || y<0 )
				cout<<"Index out of bounds!\n";

			int response;
			int req[ 5 ];
			req[ 0 ] = 'S';			// Setzen eines Punktes
			req[ 1 ] = (x-1)+x1;
			req[ 2 ] = (y-1)+y1;
			req[ 4 ] = seqn++;
			
// 			cout<<"set-req an Server - x: "<<req[ 1 ]<<", y: "<<req[ 2 ]<<", abhaengig von cache_board: x: "<<x<<", y: "<<y<<endl;

			// transmit positions to server
			life_status_t status=board_a->readPos(x,y);
			if (neighbours_alive==3 && status==dead)
			{
				req[ 3 ] = alive;
			}
			else
			{
				if ((status==alive) && (neighbours_alive<2 || neighbours_alive>3))
				{
					req[ 3 ] = dead;
				}
				else
					req[ 3 ] = status;
			}
			net->request( server, &req, sizeof(req), &response, sizeof(response) );
			while (req[ 4 ]!=response)
			{
// 				cout<<"set seqnr mismatch: "<<req[4]<<", "<<response<<endl;
				net->request( server, &req, sizeof(req), &response, sizeof(response) );
			}
// 			if (req[ 4 ]==response) cout<<"set erfolg!\n";

		}
	}

}
