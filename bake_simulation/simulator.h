#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

const int MAX_LENGTH=50;

class Simulator
{
protected:
	double _food_temp;
	double _oven_temp;
	double _air_temp;
//	double _edge_temp;
	int _time;
	int _h;
	string _filename;
	double _prev_temp;
//	ofstream outfile;

	int map[MAX_LENGTH+10][MAX_LENGTH+10][MAX_LENGTH/2+10];
	/*
	1:this is the air
	2:this is the pan bottom part
	3:it's in the cake
	4:this is the edge
	*/

	double t[MAX_LENGTH+10][MAX_LENGTH+10][MAX_LENGTH/2+10],t_copy[MAX_LENGTH+10][MAX_LENGTH+10][MAX_LENGTH/2+10];

	void initializeTemper();
//	void writeDownAns();

public:
	Simulator();
	~Simulator();
	void setTemperature(double food_temp,double oven_temp,double air_temp);
	void setOutputFile(string filename);
	void process();

protected:
	virtual void initializeMap(){};
	double nextTemperture(int x,int y,int z);
	virtual bool canTerminate(){return false;};
	virtual void writeDownAns(){};
};

#endif