#include <iostream>
#include <fstream>
#include "board/Board.h"

life_status_t Board::getPos( unsigned int x, unsigned int y )
{
	if ( board[ x * boardHeight + y ] == invalid )
		std::cerr << "readPos error, x: " << x << ", y: " << y << std::endl << std::flush;
	return board[ x * boardHeight + y ];
}

void Board::setPos( unsigned int x, unsigned int y, life_status_t status )
{
	board[ x * boardHeight + y ] = status;
}

void Board::init()
{
	restoreBoard("bin/test.board");
}

void Board::storeBoard( char* filename )
{
	std::ofstream boardFile( filename );
	boardFile << boardWidth << std::endl;
	boardFile << boardHeight << std::endl;
	for ( unsigned y = 0;y < boardHeight;y++ )
	{
		for ( unsigned x = 0;x < boardWidth;x++ )
		{
			if ( getPos( x, y ) == alive )
				boardFile << "0";
			else if ( getPos( x, y ) == dead )
				boardFile << ".";
			else
				boardFile << "x";
		}
		// boardFile<<endl;	// debug
	}
	boardFile.close();
}

void Board::restoreBoard( char* filename )
{
	std::ifstream boardFile( filename );
	char stat;
	unsigned width, height;
	boardFile >> width;
	boardFile >> height;
	if ( width != boardWidth || height != boardHeight )
	{
		std::cerr << "Board in file doesn't match BoardSize!\n" << std::flush;
		//exit(-1);
	}
	boardFile.get( stat );	// read over newline
	for ( unsigned y = 0;y < height;y++ )
		for ( unsigned x = 0;x < width;x++ )
		{
			boardFile.get( stat );
			if ( stat == '0' )
				setPos( x, y, alive );
			else if ( stat == '.' )
				setPos( x, y, dead );
			else
			{
				setPos( x, y, invalid );
				std::cerr << "invalid!\n" << std::flush;
				exit( -1 );
			}
		}
	boardFile.close();
}
