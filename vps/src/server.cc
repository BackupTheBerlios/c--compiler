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
	
	board_a->restoreBoard("test.board");
			
	BoardServer* boardserver = new BoardServer((IPNetwork *)net,1,(Board *)board_a,(Board *)board_b,10);
	
	boardserver->start();
}
