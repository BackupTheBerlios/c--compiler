#include <iostream>

#include "taco/taco.h"

#include "defines.h"
#include "board/Board.h"

class LifeObj : public GroupMember<LifeObj>
{
public:
	LifeObj( int rank );
	void setServer( ObjectPtr<LifeObj> server ) {this->server = server;}
	life_status_t getPos( int x, int y );
	void setPos( int x, int y, life_status_t status );
	void makeStep();
	void toggleBoard();
	void printBoard();
	~LifeObj();

private:
	int id;
	unsigned myFirstRow;
	unsigned myLastRow;
	Board *board_a;
	Board *board_b;
	ObjectPtr<LifeObj> server;


	void calculateElement( int x, int y );
};

