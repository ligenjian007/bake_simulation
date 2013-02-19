#include "rectangle.h"
#include "circle.h"
#include "RecCircle.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>

//#define PRINT_EACH_SCORE

using namespace std;

int campareSimulate();
int cmdSimulate();
double tradeOffSimulate(double p,int A,int w,int l,int r,ofstream & final);
int num_function(int x,int y,double w,double l,double scale);
double even_function(double varTotal,double varFTotal);

int main()
{
	double p;
	int A;
	double w,l;
	double score;
	int r=8;
	ofstream final_list("final_result.txt");
	p=0;
	cout<<"please input the A and W/L, each is divided by space"<<endl;
	cin>>A>>w>>l;
	final_list<<"the scale of the cake is "<<sqrt(A/(r*r*3.14159))<<endl;
	for (int i=0;i<101;i++)
	{
		score=tradeOffSimulate(p,A,w,l,r,final_list);
		cout<<"the max score when p="<<p<<" and w="<<w<<" l="<<l<<" is "<<score<<endl;
		p+=0.01;
	}
	return 1;
	final_list.close();
}


int campareSimulate()
{
	double air_temp=180;
	double oven_temp=185.9;
	double food_temp=25.7;
	double varTotal,varFTotal;
	int r;
	char filename[50];


	cout<<"please input the radius of the circle"<<endl;
	cin>>r;

	sprintf(filename,"radius=%d-result.txt",r);
	ofstream result_file(filename);
	sprintf(filename,"radius=%d-fomated-result.txt",r);
	ofstream format_file(filename);

	Simulator *circle_sim=new CircleSimulator(r);
	circle_sim->setTemperature(food_temp,oven_temp,air_temp);
	circle_sim->process();
	result_file<<"circle with radius "<<r<<" time:"<<circle_sim->time()<<":"<<endl;
	varTotal=circle_sim->varOfTotal();
	varFTotal=circle_sim->varFOfTotal();
	result_file<<"\tsquare variance:"<<varTotal<<endl;
	result_file<<"\tcube variance:"<<varFTotal<<endl;
	format_file<<"circle(r="<<r<<"):"<<endl;
	format_file<<circle_sim->time()<<"\t"<<2*r<<"\t"<<2*r<<"\t"<<varTotal<<"\t"<<varFTotal<<endl;
	delete circle_sim;

	for (int i=1;i<MAX_LENGTH;i++)
	{
		for (int j=1;j<=i;j++)
			if (fabs(i*j-r*r*3.14)<10)
			{
				Simulator *rec_sim=new RectangleSimulator(i,j);
				rec_sim->setTemperature(food_temp,oven_temp,air_temp);
				rec_sim->process();
				result_file<<"rectangle with "<<i<<"*"<<j<<" time:"<<rec_sim->time()<<":"<<endl;
				varTotal=rec_sim->varOfTotal();
				varFTotal=rec_sim->varFOfTotal();
				result_file<<"\tsquare variance:"<<varTotal<<endl;
				result_file<<"\tcube variance:"<<varFTotal<<endl;
				format_file<<"rectangle(x="<<i<<",y="<<j<<"):"<<endl;
				format_file<<rec_sim->time()<<"\t"<<i<<"\t"<<j<<"\t"<<varTotal<<"\t"<<varFTotal<<endl;
				delete rec_sim;
			}
	}

	for (int i=1;i<MAX_LENGTH;i++)
	{
		for (int j=1;j<i;j++)
			for (int k=4;k<j/2-4;k++)
				if (fabs(i*j-k*k*(4-3.14159)-r*r*3.14159)<5)
				{
					Simulator *rec_cir_sim=new RecCircleSimulator(k,i,j);
					rec_cir_sim->setTemperature(food_temp,oven_temp,air_temp);
					rec_cir_sim->process();
					result_file<<"rec-circle with"<<i<<"*"<<j<<" radius="<<k<<" time="<<rec_cir_sim->time()<<":"<<endl;
					varTotal=rec_cir_sim->varOfTotal();
					varFTotal=rec_cir_sim->varFOfTotal();
					result_file<<"\tsquare variance:"<<varTotal<<endl;
					result_file<<"\tcube variance:"<<varFTotal<<endl;
					format_file<<"rectangle-circle(x="<<i<<",y="<<j<<",r="<<k<<"):"<<endl;
					format_file<<rec_cir_sim->time()<<"\t"<<i<<"\t"<<j<<"\t"<<varTotal<<"\t"<<varFTotal<<endl;
					delete rec_cir_sim;
				}
	}
	
	result_file.close();
	return 1;
}


int cmdSimulate()
{
	Simulator *sim;
	ofstream varOut("variable.txt");
	double varButtom,varFButtom,varTotal,varFTotal;
	int simNo;

	cout<<"please input the shape number you want to simulate:"<<endl;
	cout<<"( 1:rectangular 2:circle 3:rectangular-circle)"<<endl;
	cin>>simNo;

	if (simNo==1)
		sim=new RectangleSimulator(40,50);
	else if (simNo==2)
		sim=new CircleSimulator();
	else if (simNo==3)
		sim=new RecCircleSimulator();

	sim->setTemperature(25.7,186,180);
	sim->process();

	varButtom=sim->varOfButtom();
	varFButtom=sim->varFOfButtom();
	varTotal=sim->varOfTotal();
	varFTotal=sim->varFOfTotal();

	cout<<"the variance of the buttom is "<<varButtom<<endl;
	varOut<<"the variance of the buttom is "<<varButtom<<endl;
	cout<<"the Forth variance of the buttom is"<<varFButtom<<endl;
	varOut<<"the Forth variance of the buttom is "<<varFButtom<<endl;
	cout<<"the variance of the total is"<<varTotal<<endl;
	varOut<<"the variance of the total is "<<varTotal<<endl;
	cout<<"the Forth variance of the total is"<<varFTotal<<endl;
	varOut<<"the Forth variance of the total is "<<varFTotal<<endl;

	varOut.close();
	return 1;
}
//this is the interface for test.

double tradeOffSimulate(double p,int A,int w,int l,int r,ofstream & final)
{
	double max_score,score;
	max_score=-1000;
	int x,y,time;
	double varTotal,varFTotal,var_min=1000000,var_max=0,even_score,final_even;
	int num_min=1000000,num_max=0,num_score,final_num;
	
	//the next is the simulation of circle
	char filename[50];
	char shape[50];
	char max_name[50];

	sprintf(filename,"radius=%d-fomated-result.txt",r);
	ifstream format_file(filename);
	ifstream pre_file(filename);

	while (pre_file>>shape)
	{
		int num;
		pre_file>>time>>x>>y>>varTotal>>varFTotal;
		num=num_function(x,y,w,l,sqrt(A/(r*r*3.14159)));
		if (num<num_min) num_min=num;
		if (num>num_max) num_max=num;
		if (varTotal>var_max) var_max=varTotal;
		if (varTotal<var_min) var_min=varTotal;
	}
	pre_file.close();

#ifdef PRINT_EACH_SCORE
	sprintf(filename,"r=%d,p=%f,w=%d,l=%d.ans",r,p,w,l);
	ofstream ansFile(filename);
#endif

	while (format_file>>shape)
	{
		format_file>>time>>x>>y>>varTotal>>varFTotal;
		num_score=num_function(x,y,w,l,sqrt(A/(r*r*3.14159)));
		even_score=even_function(varTotal,varFTotal);
		score=p*num_score/(num_max-num_min)+(1-p)*even_score/(-var_max+var_min);

#ifdef PRINT_EACH_SCORE
		ansFile<<shape<<endl;
		ansFile<<"num:"<<num_score<<"\teven:"<<even_score<<endl;
#endif

		if (score>max_score)
		{
			strcpy(max_name,shape);
			max_score=score;
			final_num=num_score;
			final_even=even_score;
		}
	}

#ifdef PRINT_EACH_SCORE
	cout<<"the max shape is"<<max_name<<endl;
	cout<<"the score of the shape is"<<max_score<<endl;

	ansFile<<"when p is"<<p<<", the max shape is "<<max_name<<endl;
	ansFile<<"the score of the shape is "<<max_score<<endl;
#endif

	final<<"when p is "<<p<<", the max shape is "<<max_name<<endl;
	final<<"the number score is: "<<final_num<<endl;
	final<<"the even score is: "<<final_even<<endl;
	final<<"the score of the shape is "<<max_score<<endl;

	return max_score;

#ifdef PRINT_EACH_SCORE
	ansFile.close();
#endif

}

int num_function(int x,int y,double w,double l,double scale)
{
	int n1,n2;
	n1=((int)(w/scale/x))*((int)(l/scale/y));
	n2=((int)(w/scale/y))*((int)(l/scale/x));
	if (n1>n2) return n1;
	else return n2;
}

double even_function(double valTotal,double varFTotal)
{
	return valTotal;
}