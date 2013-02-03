#ifndef _CIRCLE_H_
#define _CIRCLE_H_


#include "Simulator.h"

class CircleSimulator:public Simulator
{
public:
	CircleSimulator(int r=80);
	~CircleSimulator();
protected:
	virtual void initializeMap();
	virtual double nextTemperture(int x,int y,int z);
	virtual bool canTerminate();

	int _r,_x,_y;
};


#endif