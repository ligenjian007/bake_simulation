#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_


#include "Simulator.h"

class RectangleSimulator:public Simulator
{
public:
	RectangleSimulator(int x=50,int y=50);
	~RectangleSimulator();
protected:
	virtual void initializeMap();
	virtual double nextTemperture(int x,int y,int z);
	virtual bool canTerminate();
	virtual void writeDownAns();

	int _x,_y;
};


#endif