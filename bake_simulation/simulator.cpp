#include "Simulator.h"
#include <string.h>
#include <iostream>
#include <stdio.h>

using namespace std;

Simulator::Simulator()
{
	_time=0;
	_food_temp=0;
	_oven_temp=0;
	_air_temp=0;
	_h=MAX_LENGTH/2;
}

Simulator::~Simulator()
{
}


void Simulator::setTemperature(int food_temp,int oven_temp,int air_temp)
{
	_food_temp=food_temp;
	_oven_temp=oven_temp;
	_air_temp=air_temp;
}

void Simulator::process()
{
	initializeMap();
	initializeTemper();
	while (!canTerminate())
	{
		for (int i=1;i<=MAX_LENGTH;i++)
			for (int j=1;j<=MAX_LENGTH;j++)
				for (int k=1;k<=_h;k++)
				{
					t[i][j][k]=nextTemperture(i,j,k);
				}
		memcpy(t_copy,t,sizeof(t));
		writeDownAns();
		_time++;
		cout<<"time "<<_time<<" simulated finished"<<endl;
	}
}

void Simulator::initializeTemper()
{
	for (int i=0;i<=MAX_LENGTH+1;i++)
		for (int j=0;j<=MAX_LENGTH+1;j++)
			for (int k=0;k<=MAX_LENGTH+1;k++)
			{
				if (map[i][j]==1) t[i][j][k]=_air_temp;
				if (map[i][j]==2) t[i][j][k]=_oven_temp;
				if (map[i][j]==3)
				{
					if (k==0) t[i][j][k]=_oven_temp;
					else if (k<=_h) t[i][j][k]=_food_temp;
					else t[i][j][k]=_air_temp;
				}
			}
}

void Simulator::setOutputFile(string filename)
{
	_filename=filename;
}

void Simulator::writeDownAns()
{
	char file[50];
	sprintf(file,"%s\\%d.dat",_filename.c_str(),_time);
	outfile.open(file);
	for (int i=0;i<MAX_LENGTH;i++)
	{
		for (int j=0;j<MAX_LENGTH;j++)
			outfile<<t[i][j][1]<<"\t";
		outfile<<endl;
	}
	outfile.close();
}