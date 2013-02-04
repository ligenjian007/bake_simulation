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
			map[i][j][0]=3;
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
	if (abs(_prev_temp-t[_x][_y][_h/2])<5e-5 && _time>20000 || t[_x][_y][_h/2]>98) return true;
	else
	{
		_prev_temp=t[_x][_y][_h/2];
		return false;
	}
}

void CircleSimulator::writeDownAns()
{
	char file[50];

	sprintf(file,"buttom%d.ans",_time);
	ofstream outfile(file);
	for (int i=0;i<=MAX_LENGTH;i++)
	{
		for (int j=0;j<=MAX_LENGTH;j++)
			outfile<<t[i][j][1]<<"\t";
		outfile<<endl;
	}
	outfile.close();

	sprintf(file,"center%d.ans",_time);
	outfile.open(file);
	for (int i=0;i<=MAX_LENGTH;i++)
	{
		for (int j=0;j<=MAX_LENGTH;j++)
			outfile<<t[i][j][_h/2]<<"\t";
		outfile<<endl;
	}
	outfile.close();
}