#include <stdlib.h>
#include "board/LocalBoard.h"


enum life_status_t LocalBoard::readPos(unsigned int x, unsigned int y) {
	return myMatrix[x][y];
}

void LocalBoard::setPos(unsigned int x, unsigned int y, life_status_t status) {
	myMatrix[x][y] = status;
}


/**
	* Store current board configuration to disk
	*
	* @param filename name of the file to store the current
	* 	board configuration in
	*/
void LocalBoard::storeBoard(char* filename)
{
}

/**
	* Restore current board configuration from disk
	*
	* @param filename name of the file to restore the current
	* 	board configuration from
	*/
void LocalBoard::restoreBoard(char* filename)
{
}
