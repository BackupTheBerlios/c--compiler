#include "X/XWindow.h"
#include "net/IPAddress.h"
#include "net/IPNetwork.h"
#include "net/UDPNetwork.h"
#include "board/Board.h"
#include "board/LocalBoard.h"
#include "board/BoardServer.h"
#include <iostream>
using namespace std;

#define ZOOM 5
#define RANDOM 7

int main()
{
	UDPNetwork* net = new UDPNetwork(7654);
	LocalBoard* board_a = new LocalBoard(BOARD_WIDTH,BOARD_HEIGHT);
	LocalBoard* board_b = new LocalBoard(BOARD_WIDTH,BOARD_HEIGHT);
	
	board_a->restoreBoard("test.board");
			
	BoardServer* boardserver = new BoardServer((IPNetwork *)net,1,(Board *)board_a,(Board *)board_b,10);
	
	boardserver->start();
	
	// test fuers board, kommt spaeter in den client
	Color alivecol = White;
	Color deadcol  = Blue2;

	// init
/*	for (int x=0;x<BOARD_WIDTH;x++)
		for (int y=0;y<BOARD_HEIGHT;y++)
			board_a->setPos(x , y, (((rand()%RANDOM)==2) ? alive : dead) );*/
/*	board_a->restoreBoard("test.board"); 

	XWindow* w=new XWindow(BOARD_WIDTH*ZOOM, BOARD_HEIGHT*ZOOM, "Game of Life");

	int i=0;

	char* count=(char*)malloc(16);
	unsigned neighbours_alive;
	while(true)
	{
		for (int x=0;x<BOARD_WIDTH;x++)
		{
			for (int y=0;y<BOARD_HEIGHT;y++)
			{
				// set count of neighbours
				neighbours_alive=0;

				int yTop,yBottom,xLeft,xRight;
				if (y==0) {yTop=BOARD_HEIGHT-1;yBottom=y+1;}
				else if (y==BOARD_HEIGHT-1) {yTop=y-1;yBottom=0;}
				else {yTop=y-1;yBottom=y+1;}
				if (y==0) {xLeft=BOARD_WIDTH-1;xRight=x+1;}
				else if (x==BOARD_WIDTH-1) {xLeft=x-1;xRight=0;}
				else {xLeft=x-1;xRight=x+1;}

				if (board_a->readPos(xLeft,yTop)==alive) neighbours_alive++;	// top left
				if (board_a->readPos(xLeft,y)==alive) neighbours_alive++;	// top
				if (board_a->readPos(xLeft,yBottom)==alive) neighbours_alive++;	// top right
				if (board_a->readPos(x,yTop)==alive) neighbours_alive++;	// left
				if (board_a->readPos(x,yBottom)==alive) neighbours_alive++;	// right
				if (board_a->readPos(xRight,yTop)==alive) neighbours_alive++;	// top left
				if (board_a->readPos(xRight,y)==alive) neighbours_alive++;	// top
				if (board_a->readPos(xRight,yBottom)==alive) neighbours_alive++;// top right

				if ( x>=BOARD_WIDTH || x<0 || y>=BOARD_HEIGHT || y<0 )
					cout<<"Index out of bounds!\n";

				// set positions on board_b
				if (neighbours_alive==3 && board_a->readPos(x,y)==dead)
				{
					board_b->setPos(x,y, alive);
// 					cout<<"alive\n";
				}
				else
				{
					if ((board_a->readPos(x,y)==alive) && (neighbours_alive<2 || neighbours_alive>3))
					{
						board_b->setPos(x,y, dead);
// 						cout<<"dead\n";
					}
					else
						board_b->setPos(x,y, board_a->readPos(x,y));
				}
				w->fillRectangle( (board_b->readPos(x, y)==alive)?alivecol:deadcol, x*ZOOM, y*ZOOM, ZOOM, ZOOM);
			}
		}
		i++;
		strcpy(count, "Durchlauf: ");
		sprintf(count+11,"%u",i);
		if (i<10)
			w->write(Green1,10,10,count,12);
		else if (i<100)
			w->write(Green1,10,10,count,13);
		else if (i<1000)
			w->write(Green1,10,10,count,14);
		else
			w->write(Green1,10,10,count,15);
		w->flush();
		LocalBoard* board_cache=board_b;
		board_b=board_a;
		board_a=board_cache;
	}*/
}
