#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>
#include "taco/taco.h"
#include "defines.h"

class Board
{
public:
	Board( int width, int height )
	{
		board = new life_status_t[ width * height ];
		srand( 1 );
	}
	
	~Board()
	{
	    storeBoard("bin/test.result");
	}

	life_status_t getPos( unsigned int x, unsigned int y );

	void setPos( unsigned int x, unsigned int y, life_status_t status );

	void init();

private:
	life_status_t* board;

	void storeBoard(char*);
	void restoreBoard(char*);
// 	int wrap( int pos, bool horizontal );
};

#endif

