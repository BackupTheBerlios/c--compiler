#include "net/IPAddress.h"
#include "net/IPNetwork.h"
#include "net/TCPNetwork.h"
#include "board/Board.h"
#include "board/LocalBoard.h"
#include "board/BoardServer.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc!=3)
	{
		cout<<"Usage: server [clientcount] [steps]\n";
		exit(-1);
	}
	int clients=atoi(argv[1]);
	int steps=atoi(argv[2]);
	TCPNetwork* net = new TCPNetwork(7654);
	LocalBoard* board_a = new LocalBoard(BOARD_WIDTH,BOARD_HEIGHT);
	LocalBoard* board_b = new LocalBoard(BOARD_WIDTH,BOARD_HEIGHT);
	
/*	for ( int x = 0;x < BOARD_WIDTH;x++ )
		for ( int y = 0;y < BOARD_HEIGHT;y++ )
			board_a->setPos(x,y,alive);*/
	board_a->restoreBoard("test.board");
	BoardServer* boardserver = new BoardServer((IPNetwork *)net,clients,board_a,board_b,steps);
	boardserver->start();
	
	board_a->storeBoard("test.result");
}
