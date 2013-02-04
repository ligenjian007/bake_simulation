#include "Rectangle.h"
#include "numeric.h"

RectangleSimulator::RectangleSimulator(int x,int y)
{
	_x=x;
	_y=y;
};

RectangleSimulator::~RectangleSimulator(){};

void RectangleSimulator::initializeMap()
{
	for (int i=0;i<MAX_LENGTH+10;i++)
	{
		for (int j=0;j<MAX_LENGTH+10;j++)
		{
			map[i][j][0]=2;
		}
	}

	for (int i=0;i<MAX_LENGTH+10;i++)
	{
		for (int j=0;j<MAX_LENGTH+10;j++)
		{
			for (int k=1;k<_h;k++)
			{
				if (i==0 || j==0 || i==_x || j==_y) map[i][j][k]=2;
				else if (i>0 && i<_x && j>0 && j<_y) map[i][j][k]=3;
				else map[i][j][k]=1;
			}
		}
	}

	for (int i=0;i<MAX_LENGTH+10;i++)
	{
		for (int j=0;j<MAX_LENGTH+10;j++)
		{
			for (int k=_h;k<MAX_LENGTH/2+10;k++)
			{
				map[i][j][k]=1;
			}
		}
	}
	
}

bool RectangleSimulator::canTerminate()
{
	if (_time>2000000) return true;
	else return false;
}

/*
double RectangleSimulator::nextTemperture(int x,int y,int z)
{
	double temperature;
	if (map[x][y][z]==1 || map[x][y][z]==2) return t[x][y][z];
	temperature=(t[x-1][y][z]+t[x][y-1][z]+t[x][y][z-1]+t[x+1][y][z]+t[x][y+1][z]+t[x][y][z+1])/6;
	return(temperature);
}
*/

double RectangleSimulator::nextTemperture(int x,int y,int z)
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

void RectangleSimulator::writeDownAns()
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

	sprintf(file,"edge-left%d.ans",_time);
	ofstream outfile1(file);
	for (int j=0;j<=_y;j++)
	{
		for (int k=0;k<=MAX_LENGTH/2;k++)
			outfile1<<t[1][j][k]<<"\t";
		outfile1<<endl;
	}
	outfile1.close();

	sprintf(file,"edge-right%d.ans",_time);
	ofstream outfile2(file);
	for (int j=0;j<=_y;j++)
	{
		for (int k=0;k<=MAX_LENGTH/2;k++)
			outfile2<<t[_x-1][j][k]<<"\t";
		outfile2<<endl;
	}
	outfile2.close();

	sprintf(file,"edge-front%d.ans",_time);
	ofstream outfile3(file);
	for (int i=0;i<=_x;i++)
	{
		for (int k=0;k<=MAX_LENGTH/2;k++)
			outfile3<<t[i][1][k]<<"\t";
		outfile3<<endl;
	}
	outfile3.close();

	sprintf(file,"edge-behind%d.ans",_time);
	ofstream outfile4(file);
	for (int i=0;i<=_x;i++)
	{
		for (int k=0;k<=MAX_LENGTH/2;k++)
			outfile4<<t[0][_y-1][k]<<"\t";
		outfile4<<endl;
	}
	outfile4.close();

}