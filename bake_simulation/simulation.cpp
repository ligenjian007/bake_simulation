#include "rectangle.h"
#include "circle.h"

int main()
{
	Simulator *sim=new RectangleSimulator();
	sim->setTemperature(20,200,10);
	sim->process();
	//Simulator *sim=new CircleSimulator();
	//sim->setTemperature(20,200,40);
	//sim->process();
	return 1;
}
