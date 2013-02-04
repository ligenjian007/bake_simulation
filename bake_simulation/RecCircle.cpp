#include "RecCircle.h"
#include "numeric.h"
#include <math.h>

#define PRINT_MAP

RecCircleSimulator::RecCircleSimulator(int r,int a,int b)
{
	_r=r;
	_a=a;
	_b=b;
}

RecCircleSimulator::~RecCircleSimulator(){}

void RecCircleSimulator::initializeMap()
{
	int ain1,ain2,bin1,bin2,aout,bout,r;
	ain1 = _r;
	ain2 = _a - _r;
	bin1 = _r;
	bin2 = _b - _r;
	aout= _a;
	bout= _b;
	r= _r;

	for (int i=0;i<MAX_LENGTH+10;i++)
	{
		for (int j=0;j<MAX_LENGTH+10;j++)
		{
			map[i][j][0]=2;
		}
	}//the bottom heat, which is the oven temperature

	for (int i=0;i<MAX_LENGTH+10;i++)
	{
		for (int j=0;j<MAX_LENGTH+10;j++)
		{
			if (i>0 && i<aout && j>0 && j<bout)
			{
				if ((i>=ain1 && i<=ain2) || (j>=bin1 && j<=bin2))
					map[i][j][1]=3;
				else if (inCornerRanbow(i,j,ain1,ain2,bin1,bin2,r))
					map[i][j][1]=3;
				else map[i][j][1]=2;
			}
			else map[i][j][1]=2;
		}
	}//the food above the bottom, which is food inner and oven outer

	//flood fill the oven part with air
	for (int i=0;i<MAX_LENGTH+10;i++)
	{
		for (int j=0;j<MAX_LENGTH+10;j++)
			if (map[i][j][1]==2)
			{
				bool with_food=false;
				if (i>0 && map[i-1][j][1]==3) with_food=true;
				if (j>0 && map[i][j-1][1]==3) with_food=true;
				if (i<MAX_LENGTH+9 && map[i+1][j][1]==3) with_food=true;
				if (j<MAX_LENGTH+9 && map[i][j+1][1]==3) with_food=true;
				if (!with_food) 
					map[i][j][1]=1;
				else map[i][j][1]=2;
			}
	}

#ifdef PRINT_MAP
	ofstream outfile ("map1.txt");
	for (int i=0;i<=MAX_LENGTH+10;i++)
	{
		for (int j=0;j<=MAX_LENGTH+10;j++)
			outfile<<map[i][j][1]<<"\t";
		outfile<<endl;
	}
	outfile.close();
#endif

	for (int i=0;i<MAX_LENGTH+10;i++)
		for (int j=0;j<MAX_LENGTH+10;j++)
			for (int k=2;k<=_h;k++)
				map[i][j][k]=map[i][j][1];
	//the food above has the same map as the food above bottom

#ifdef PRINT_MAP
	outfile.open("map2.txt");
	for (int i=0;i<=MAX_LENGTH;i++)
	{
		for (int j=0;j<=MAX_LENGTH;j++)
			outfile<<map[i][j][1]<<"\t";
		outfile<<endl;
	}
	outfile.close();
#endif

	for (int i=0;i<MAX_LENGTH+10;i++)
		for (int j=0;j<MAX_LENGTH+10;j++)
			for (int k=_h+1;k<MAX_LENGTH/2+10;k++)
				map[i][j][k]=1;
	//the left part can be treated as air finally

#ifdef PRINT_MAP
	outfile.open("map.txt");
	for (int i=0;i<=MAX_LENGTH;i++)
	{
		for (int j=0;j<=MAX_LENGTH;j++)
			outfile<<map[i][j][1]<<"\t";
		outfile<<endl;
	}
	outfile.close();
#endif

}

double RecCircleSimulator::distance(int x1,int y1,int x2,int y2)
{
	return (sqrt((x1-x2)*(x1-x2)*1.0+(y1-y2)*(y1-y2)));
}

bool RecCircleSimulator::inCornerRanbow(int x,int y,int a1,int a2,int b1,int b2,int r)
{
	if (distance(x,y,a1,b1)<=r) return true;
	else if (distance(x,y,a1,b2)<=r) return true;
	else if (distance(x,y,a2,b1)<=r) return true;
	else if (distance(x,y,a2,b2)<=r) return true;
	else return false;
}

void RecCircleSimulator::writeDownAns()
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

bool RecCircleSimulator::canTerminate()
{
	if (abs(_prev_temp-t[_a/2][_b/2][_h/2])<5e-5 && _time>20000 || t[_a/2][_b/2][_h/2]>98) return true;
	else 
	{
		_prev_temp=t[_a/2][_b/2][_h/2];
		return false;
	}
}