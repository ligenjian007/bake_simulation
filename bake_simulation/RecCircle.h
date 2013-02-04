#ifndef _REC_CIRCLE_H_
#define _REC_CIRCLE_H_

#include "simulator.h"

class RecCircleSimulator:public Simulator
{
protected:
	int _r,_a,_b;
	virtual void initializeMap();
	virtual double nextTemperture(int x,int y,int z);
	virtual bool canTerminate();

public:
	RecCircleSimulator(int r=5,int a=60,int b=40);
	~RecCircleSimulator();
}

#endif 