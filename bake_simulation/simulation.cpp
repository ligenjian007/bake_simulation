#include "rectangle.h"

int main()
{
	Simulator *rec=new RectangleSimulator();
	rec->setTemperature(10,10,10);
	rec->process();
	return 1;
}
