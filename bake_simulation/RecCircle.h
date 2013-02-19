#ifndef _REC_CIRCLE_H_
#define _REC_CIRCLE_H_

#include "simulator.h"

class RecCircleSimulator:public Simulator
{
protected:

	virtual void initializeMap();
	virtual bool canTerminate();
	virtual void writeDownAns();
	
	int _r,_a,_b;
	bool inCornerRanbow(int x,int y,int a1,int a2,int b1,int b2,int r);
	double distance(int x1,int y1,int x2,int y2);

public:
	RecCircleSimulator(int r=MAX_LENGTH/10+2,int a=MAX_LENGTH-20,int b=MAX_LENGTH);
	~RecCircleSimulator();
	virtual double area();
};

#endif 