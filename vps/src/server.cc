#include "net/IPAddress.h"
#include "net/IPNetwork.h"
#include "net/UDPNetwork.h"
#include "board/Board.h"
#include "board/LocalBoard.h"
#include "board/BoardServer.h"
#include <iostream>
using namespace std;

int main()
{
	UDPNetwork* net = new UDPNetwork(7654);
	LocalBoard* board_a = new LocalBoard(BOARD_WIDTH,BOARD_HEIGHT);
	LocalBoard* board_b = new LocalBoard(BOARD_WIDTH,BOARD_HEIGHT);
	
/*	for ( int x = 0;x < BOARD_WIDTH;x++ )
		for ( int y = 0;y < BOARD_HEIGHT;y++ )
			board_a->setPos(x,y,alive);*/
	board_a->restoreBoard("test.board");
	
	BoardServer* boardserver = new BoardServer((IPNetwork *)net,1,board_a,board_b,100);
	
	boardserver->start();
}
