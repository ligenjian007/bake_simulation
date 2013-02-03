#include "Rectangle.h"

RectangleSimulator::RectangleSimulator(int x,int y)
{
	_x=x;
	_y=y;
};

RectangleSimulator::~RectangleSimulator(){};

void RectangleSimulator::initializeMap()
{
	for (int i=0;i<MAX_LENGTH+10;i++)
		for (int j=0;j<MAX_LENGTH+10;j++)
		{
			if (i==0 || j==0 || i==_x || j==_y) map[i][j]=2;
			else if (i>0 && i<_x && j>0 && j<_y) map[i][j]=1;
			else map[i][j]=3;
		}
}

bool RectangleSimulator::canTerminate()
{
	if (_time==30) return true;
	else return false;
}

double RectangleSimulator::nextTemperture(int x,int y,int z)
{
	return t[x][y][z];
}