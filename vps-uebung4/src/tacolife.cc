#include "taco/taco.h"
#include "taco/tacoMain.h"

#include "defines.h"
#include "life/LifeObj.h"

int main(int argc, char** argv)
{
	//initialization of Score and Taco Platforms
	taco::init(argc,argv);

	//determining a mapping strategy for objects
	Cyclic mapping(clientCount+1);
	//creation and placement of objects
	GroupOf<LifeObj> group(clientCount+1, mapping);

	//propagating the serveraddress to the clients
	//by calling client Funktion "int setServer(ObjPtr<LifeObj> server)"
	//maybe use Taco's step operation for groups
	group.step(m2f(&LifeObj::setServer,group[0]));


	//initial printing of the board
	group[0].call(m2f(&LifeObj::printBoard));

	//loop for stepcount
	for(unsigned i=0; i < steps; i++){
		if (i%10==0) std::cerr<<i<<std::endl<<std::flush;
		//let the clients calculate one timestep
		//maybe use step here again
		group.step(vm2f(&LifeObj::makeStep));

		//let the server do the output
		//maybe use call this way, group[0] is the serverobject-pointer
//		group[0].call(vm2f(&LifeObj::printBoard));

		group[0].call(vm2f(&LifeObj::toggleBoard));
	}
	

	return 0;
}
