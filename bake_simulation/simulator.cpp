#include "Simulator.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include "numeric.h"

using namespace std;

Simulator::Simulator()
{
	_time=0;
	_food_temp=0;
	_oven_temp=0;
	_air_temp=0;
//	_edge_temp=0;
	_h=MAX_LENGTH/2;
	_filename="sim";
}

Simulator::~Simulator()
{
}


void Simulator::setTemperature(double food_temp,double oven_temp,double air_temp)
{
	_food_temp=food_temp;
	_oven_temp=oven_temp;
	_air_temp=air_temp;
	_prev_temp=food_temp-100;
}

void Simulator::process()
{
	initializeMap();
	initializeTemper();
	while (!canTerminate())
	{
		if (_time%2000==0)
			writeDownAns();
		for (int i=1;i<=MAX_LENGTH;i++)
			for (int j=1;j<=MAX_LENGTH;j++)
				for (int k=1;k<=_h;k++)
				{
					t[i][j][k]=nextTemperture(i,j,k);
				}
		memcpy(t_copy,t,sizeof(t));
		_time++;
		if (_time%200==0)
			cout<<"time "<<_time<<" simulated, center temperature: "<<t[MAX_LENGTH/2][MAX_LENGTH/2][MAX_LENGTH/4]<<endl;
	}
}

void Simulator::initializeTemper()
{
	for (int i=0;i<=MAX_LENGTH+1;i++)
		for (int j=0;j<=MAX_LENGTH+1;j++)
			for (int k=0;k<=MAX_LENGTH+1;k++)
			{
				if (map[i][j][k]==1) t[i][j][k]=_air_temp;
				if (map[i][j][k]==2) t[i][j][k]=_oven_temp;
				if (map[i][j][k]==3) t[i][j][k]=_food_temp;
			}
}

void Simulator::setOutputFile(string filename)
{
	_filename=filename;
}

double Simulator::nextTemperture(int x,int y,int z)
{
	double temperature;
	double dx1,dx2,ddx,dy1,dy2,ddy,dz1,dz2,ddz,flashtemp;

	if (map[x][y][z]==1 || map[x][y][z]==2 || map[x][y][z]==4) return t[x][y][z];

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
