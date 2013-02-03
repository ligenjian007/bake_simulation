#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

const int MAX_LENGTH=200;

class Simulator
{
protected:
	int _food_temp;
	int _oven_temp;
	int _air_temp;
	int _time;
	int _h;
	string _filename;
	ofstream outfile;

	int map[MAX_LENGTH+10][MAX_LENGTH+10];
	/*
	1:this is the air
	2:this is the pan part
	3:it's in the cake
	*/

	double t[MAX_LENGTH+10][MAX_LENGTH+10][MAX_LENGTH/2+10],t_copy[MAX_LENGTH+10][MAX_LENGTH+10][MAX_LENGTH/2+10];

	void initializeTemper();
	void writeDownAns();

public:
	Simulator();
	~Simulator();
	void setTemperature(int food_temp,int oven_temp,int air_temp);
	void setOutputFile(string filename=string("output"));
	void process();

protected:
	virtual void initializeMap(){};
	virtual double nextTemperture(int x,int y,int z){return 0;};
	virtual bool canTerminate(){return false;};
};

#endif