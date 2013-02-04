#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_


#include "Simulator.h"

class RectangleSimulator:public Simulator
{
public:
	RectangleSimulator(int x=MAX_LENGTH,int y=MAX_LENGTH);
	~RectangleSimulator();
protected:
	virtual void initializeMap();
	virtual bool canTerminate();
	virtual void writeDownAns();

	int _x,_y;
};


#endif