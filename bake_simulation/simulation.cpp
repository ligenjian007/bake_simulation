#include "rectangle.h"
#include "circle.h"

int main()
{
	//Simulator *sim=new RectangleSimulator();
	//sim->setTemperature(25.7,185,100);
	//sim->process();
	Simulator *sim=new CircleSimulator();
	sim->setTemperature(25.7,185,100);
	sim->process();
	return 1;
}
