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
	if (_time>2000000) return true;
	else return false;
}

double CircleSimulator::nextTemperture(int x,int y,int z)
{
	double temperature;
	double dx1,dx2,ddx,dy1,dy2,ddy,dz1,dz2,ddz,flashtemp;

	if (map[x][y][z]==1 || map[x][y][z]==2) return t[x][y][z];

	dx1=(t[x][y][z]-t[x-1][y][z])/(1*scale);
	dx2=(t[x+1][y][z]-t[x][y][z])/(1*scale);
	ddx=(dx2-dx1)/(1*scale);

	dy1=(t[x][y][z]-t[x][y-1][z])/(1*scale);
	dy2=(t[x][y+1][z]-t[x][y][z])/(1*scale);
	ddy=(dy2-dy1)/(1*scale);

	dz1=(t[x][y][z]-t[x][y][z-1])/(1*scale);
	dz2=(t[x][y][z+1]-t[x][y][z])/(1*scale);
	ddz=(dz2-dz1)/(1*scale);

	flashtemp=(ddx+ddy+ddz)*K/(P*Cp);

	temperature=t[x][y][z]+flashtemp;
	return(temperature);
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