#include <stdlib.h>
#include "life/LifeObj.h"

LifeObj::LifeObj( int rank )
{
	id = rank;
	// allocate memory for serverboards and initialize
	if ( id == 0 )
	{
		board_a = new Board( boardWidth, boardHeight );
		board_b = new Board( boardWidth, boardHeight );
		board_a->init();

	}
	else
	{
		std::cerr << "clientNr:" << id;
		// calculate the rows each client has to work on
		int rows = boardHeight / clientCount + 1;
		myFirstRow = (id - 1) * rows;
		myLastRow = myFirstRow + rows -1;

		// last clients last row is eventually lowered because of aligning
		if(myLastRow >= boardHeight)
		    myLastRow = boardHeight -1;

		std::cerr << ", startRow:" << myFirstRow;
		std::cerr << ", endRow:" << myLastRow << std::endl << std::flush;
	}
}

LifeObj::~LifeObj()
{
	// free memory for serverboards
	if ( id == 0 )
	{
		delete board_a;
		delete board_b;
	}
}

life_status_t LifeObj::getPos( int x, int y )
{
	return board_a->getPos( x, y );
}

void LifeObj::setPos( int x, int y, life_status_t status )
{
	board_b->setPos( x, y, status );
}

void LifeObj::makeStep()
{
	if ( id != 0 )
	{
		for ( unsigned x = 0; x < boardWidth; x++ )
			for ( unsigned y = myFirstRow; y <= myLastRow; y++ )
				calculateElement( x, y );
	}
}

void LifeObj::toggleBoard()
{
	Board * tmp = board_a;
	board_a = board_b;
	board_b = tmp;
}

void LifeObj::printBoard()
{
/*	for ( unsigned i = 0; i < boardHeight; i++ )
	{
		for ( unsigned j = 0; j < boardWidth; j++ )
		{
			std::cerr << board_a->getPos( j, i );
		}
		std::cerr << std::endl << std::flush;
	}
	std::cerr << std::endl << std::endl;
*/
}


void LifeObj::calculateElement( int x, int y )
{
	// calculate neighbourhood
	int neighbours_alive = 0;
	for ( int i = x - 1; i <= x + 1; i++ )
		for ( int j = y - 1; j <= y + 1; j++ )
			// count not the actual element we are working on
			if ( !( i == x && j == y ) && server->invoke( m2f( &LifeObj::getPos, (i+boardWidth)%boardWidth, (j+boardHeight)%boardHeight ) ) == alive )
			{
				neighbours_alive++;
			//	std::cerr<<"_";
			}
//	std::cerr << neighbours_alive << std::endl << std::flush;
	// set new status
	if ( neighbours_alive == 3)
	{
		server->call( vm2f( &LifeObj::setPos, x, y, alive ) );
//		std::cerr<<".";
	}
	else if ( neighbours_alive != 2 )
	{
		server->call( vm2f( &LifeObj::setPos, x, y, dead ) );
	}
	else
	{
		server->call( vm2f( &LifeObj::setPos, x, y,  server->invoke( m2f( &LifeObj::getPos, x, y ) )) );
	}
}
