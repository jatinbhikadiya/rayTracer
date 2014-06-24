/*
 * materail.cpp
 *
 *  Created on: Nov 9, 2012
 *      Author: bhikadiy
 */

#include "material.h"

namespace std {

material::material() {
	// TODO Auto-generated constructor stub
	ns=100;
	Kr=1;
	n1=1;
	Tr=1;
	Krf=1;
	index=0;

}

void material:: assign_name(string n,int i)
{
	//cout<<"\nname "<<n<<" is assigned to material object"<<endl;
	name=n;
	index=i;
}

void material:: assign_ka(string l)
{
	stringstream s;
	string temp;
	double value;
	s<<l;

	s>>temp;
	while(!s.eof())
	{
		s>>value;
		if(!s.fail())
		{	ka.push_back(value);
	    }
		else if(s.eof())
			break;
		else if(s.fail())
		{
			cout<<endl<<"encountered non number value for ambient reflection matrix"<<endl;
		   	exit(1);
		}
	}

	if(ka.size()!=3)
	{
		cout<<endl<<"encounter less or more values for Ka matrix";
	}
	//cout<<"ka done"<<endl;
}
void material::  assign_kd(string l)
{
	stringstream s;
	string temp;
	double value;
	s<<l;
	s>>temp;
	while(!s.eof())
	{
		s>>value;
		//cout<<value<<endl;
		if(!s.fail())
		{	kd.push_back(value);
		}
		else if(s.eof())
			break;
		else if(s.fail())
		{
			cout<<endl<<"encountered non number value for diffusion reflection matrix"<<endl;
			exit(1);
		}
	}
	if(kd.size()!=3)
	{
		cout<<endl<<"encounter less or more values for Kd matrix";
	}
	//cout<<"kd is "<<setw(5)<<kd.at(0)<<setw(5)<<kd.at(1)<<setw(5)<<kd.at(2);
}

void material::  assign_ks(string l)
{
	stringstream s;
	string temp;
	double value;
	s<<l;
	s>>temp;
	while(!s.eof())
	{
		s>>value;
		if(!s.fail())
		{	ks.push_back(value);
		}
		else if(s.eof())
			break;
		else if(s.fail())
		{
			cout<<endl<<"encountered non number value for specular reflection matrix"<<endl;
			exit(1);
		}
	}
	if(ks.size()!=3)
	{
		cout<<endl<<"encounter less or more values for Ks matrix";
	}
}
void material:: assign_ns(string l)
{
	stringstream s;
	string temp;
	s<<l;
	s>>temp;
	s>>ns;
}
void material:: assign_n1(string l)
{
	stringstream s;
	string temp;
	s<<l;
	s>>temp;
	s>>n1;
}

void material:: assign_Tr(string l)
{
	stringstream s;
	string temp;
	s<<l;
	s>>temp;
	s>>Tr;
}

void material:: assign_Kr(string l)
{
	stringstream s;
	string temp;
	s<<l;
	s>>temp;
	s>>Kr;
}

void material:: assign_Krf(string l)
{
	stringstream s;
	string temp;
	s<<l;
	s>>temp;
	s>>Krf;
}
int material:: get_index(string name1)
{
	if (name1 == name)
			return index;
		else
			return -1;
}


material::~material() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
