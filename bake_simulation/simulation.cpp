#include "rectangle.h"
#include "circle.h"
#include "RecCircle.h"

int main()
{
	int simNo;
	cout<<"please input the shape number you want to simulate:( 1:rectangular 2:circle 3:rectangular-circle)"<<endl;
	cin>>simNo;
	if (simNo==1)
	{
		Simulator *sim=new RectangleSimulator(40,50);
		sim->setTemperature(25.7,186,180);
		sim->process();
	}
	else if (simNo==2)
	{
		Simulator *sim=new CircleSimulator();
		sim->setTemperature(25.7,186,180);
		sim->process();
	}
	else if (simNo==3)
	{
		RecCircleSimulator *sim=new RecCircleSimulator();
		sim->setTemperature(25.7,186,180);
		sim->process();
	}
	return 1;
}
