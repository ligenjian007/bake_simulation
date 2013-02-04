#ifndef _CIRCLE_H_
#define _CIRCLE_H_


#include "Simulator.h"

class CircleSimulator:public Simulator
{
public:
	CircleSimulator(int r=MAX_LENGTH/2-3);
	~CircleSimulator();
protected:
	virtual void initializeMap();
	virtual bool canTerminate();
	virtual void writeDownAns();

	int _r,_x,_y;
};


#endif