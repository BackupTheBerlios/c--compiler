#ifndef LOCALBOARD_H
#define LOCALBOARD_H

#include "board/Board.h"

/**
 * This class implements the functions readPos(...) and setPos(...)
 *
 * Furthermore it is responsible to initialize a board for the game
 * for local use.
 */

class LocalBoard: public Board {
public:
	/**
	 * Constructor gets the Dimension of the board.
	 */
	LocalBoard(int width, int height):Board(width,height){};

	/**
	 * Function supplies the status of the depicted element.
	 *
	 * @param x is the horizontal position
	 * @param y is the vertical position
	 */
	enum life_status_t readPos(unsigned int x, unsigned int y);

	/**
	 * Function sets a depicted element to specified status.
	 *
	 * @param x is the horizontal position
	 * @param y is the vertical position
	 * @param status is status value to sed
	 */
	void setPos(unsigned int x, unsigned int y, life_status_t status);

	/**
	 * Store current board configuration to disk
	 *
	 * @param filename name of the file to store the current
	 * 	board configuration in
	 */
	void storeBoard(char* filename);
	
	/**
	 * Restore current board configuration from disk
	 *
	 * @param filename name of the file to restore the current
	 * 	board configuration from
	 */
	void restoreBoard(char* filename);

private:
	/**
	* This is the matrix
	*/
	enum life_status_t myMatrix[BOARD_WIDTH][BOARD_HEIGHT];

};

#endif
