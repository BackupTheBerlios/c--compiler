#ifndef BOARD_H
#define BOARD_H

#include <sys/types.h>

#define BOARD_WIDTH 101
#define BOARD_HEIGHT 101

enum life_status_t {invalid,dead,alive};

/**
 * A Board is the matrix for the life-simulation.
 *
 * Subclasses must implement the Board(),readPos() and setPos() functions
 * in order to be instanciated.
 */

class Board
{
    public:

        /**
         * Create a board with a given size, where the upper left corner is 0,0
         *
         * @param width is the horizontal size of the board
         * @param height is the vertical size of the board
         */
        Board(size_t width, size_t height) {
			this->width = width;
			this->height = height;
		}

        /**
         * Get the liveliness of a specified element.
         *
	 	 * @param x is the horizontal position of the element
	 	 * @param y is the vertical position of the element
         * @return dead or alive if element exists, else invalid
         */
        virtual enum life_status_t readPos(size_t x,size_t y){return invalid;};

        /**
         * Sets a element to a life status. If position or status is invalid,
	 * nothing is done.
         *
         * @param x is the horizontal position of the element
	 * @param y is the vertical position of the element
	 * @param status is the life status to be set
         */
        virtual void setPos(size_t x, size_t y,enum life_status_t status){};

	/**
	 * Store current board configuration to disk
	 *
	 * @param filename name of the file to store the current
	 * 	board configuration in
	 */
	virtual void storeBoard(char* filename)=0;
	
	/**
	 * Restore current board configuration from disk
	 *
	 * @param filename name of the file to restore the current
	 * 	board configuration from
	 */
	virtual void restoreBoard(char* filename)=0;

	/**
	 * Determine the width of the board.
	 *
	 * @return the width of the board
	 */
	int getWidth() const { return width; }

	/**
	 * Determine the height of the board.
	 *
	 * @return the height of the board
	 */
	int getHeight() const { return height; }

protected:
	int width, height;

};

#endif
