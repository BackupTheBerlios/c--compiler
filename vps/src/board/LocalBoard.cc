#include <stdlib.h>
#include "board/LocalBoard.h"


enum life_status_t LocalBoard::readPos(unsigned int x, unsigned int y)
{
	if (myMatrix[x][y]==invalid)
		cout << "readPos error, x: " << x << ", y: "<<y<<endl;
	return myMatrix[x][y];
}

void LocalBoard::setPos(unsigned int x, unsigned int y, life_status_t status)
{
	myMatrix[x][y] = status;
}

void LocalBoard::storeBoard(char* filename)
{
	ofstream boardFile(filename);
	boardFile<<BOARD_WIDTH<<endl;
	boardFile<<BOARD_HEIGHT<<endl;
	for (unsigned x=0;x<BOARD_WIDTH;x++)
		for (unsigned y=0;y<BOARD_HEIGHT;y++)
		{
			if (readPos(x,y)==alive)
				boardFile<<"0";
			else if (readPos(x,y)==dead)
				boardFile<<".";
			else
				boardFile<<"x";
		}
	boardFile.close();
}

void LocalBoard::restoreBoard(char* filename)
{
	ifstream boardFile(filename);
	char stat;
	unsigned width, height;
	boardFile>>width;
	boardFile>>height;
	if (width!=BOARD_WIDTH || height!=BOARD_HEIGHT)
	{
		cout<<"Board in file doesn't match BoardSize!\n";
		//exit(-1);
	}
	boardFile.get(stat);	// read over newline
	for (unsigned x=0;x<width;x++)
		for (unsigned y=0;y<height;y++)
		{
			boardFile.get(stat);
			if (stat=='0')
				setPos(x,y,alive);
			else if (stat=='.')
				setPos(x,y,dead);
			else
			{
				setPos(x,y,invalid);
				cout<<"invalid!\n";
				exit(-1);
			}
		}
	boardFile.close();
}
