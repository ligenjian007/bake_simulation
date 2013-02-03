#include "circle.h"
#include <math.h>
#include "numeric.h"

CircleSimulator::CircleSimulator(int r)
{
	_r=r;
	_x=_r+5;
	_y=_r+5;
}

CircleSimulator::~CircleSimulator()
{
}

void CircleSimulator::initializeMap()
{
	for (int i=0;i<MAX_LENGTH;i++)
	{
		for (int j=0;j<MAX_LENGTH;j++)
		{
			map[i][j][0]=_oven_temp;
		}
	}

	for (int i=0;i<MAX_LENGTH;i++)
	{
		for (int j=0;j<MAX_LENGTH;j++)
		{
			for (int k=1;k<MAX_LENGTH/2;k++)
			{
				if (sqrt((i-_x)*(i-_x)*1.0+(j-_y)*(j-_y))<_r) map[i][j][k]=3;
				else if (sqrt((i-_x)*(i-_x)*1.0+(j-_y)*(j-_y))>_r+2) map[i][j][k]=1;
				else map[i][j][k]=2;
			}
		}
	}

		for (int i=0;i<MAX_LENGTH+10;i++)
	{
		for (int j=0;j<MAX_LENGTH+10;j++)
		{
			for (int k=MAX_LENGTH/2;k<MAX_LENGTH/2+10;k++)
			{
				map[i][j][k]=1;
			}
		}
	}
}

bool CircleSimulator::canTerminate()
{
	if (_time>2000) return true;
	else return false;
}

double CircleSimulator::nextTemperture(int x,int y,int z)
{
	double temperature;
	if (map[x][y][z]==1 || map[x][y][z]==2) return t[x][y][z];
	temperature=(t[x-1][y][z]+t[x][y-1][z]+t[x][y][z-1]+t[x+1][y][z]+t[x][y+1][z]+t[x][y][z+1])/6;
	return(temperature);
}