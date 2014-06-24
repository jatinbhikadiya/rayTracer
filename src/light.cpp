/*
 * light.cpp
 *
 *  Created on: Nov 12, 2012
 *      Author: bhikadiy
 */

#include "light.h"

namespace std {

light::light() {
	// TODO Auto-generated constructor stub

}

void light:: pushvalues(string line, int ind)
{
	index=ind;
	istringstream ss;
	string c;
	ss.str(line);
	ss>>c;
	vector<double> value;
	double v;
	while(!ss.eof())
	{
		ss>>v;
		if(!ss.fail())
		{	value.push_back(v);
		//cout<<value;
		}
		else
		{
			if(!ss.eof())
			{
				cout<<endl<<"encountered non number value for command parameters.\ncheck command line:\n"<<line<<endl;
				exit(1);
			}
		}
	}

	if(value.size()>7)
	{
		cout<<"\nthere are excessive parameters in command line:\n"<<line<<endl;
		exit(1);
	}
	else if(value.size()<7)
	{
		cout<<"\nthere are less parameters in command line:\n"<<line<<endl;
		exit(1);
	}
	if(value.at(3)<10e-6)
	{
		cout<<"Warning : camera is at infinite distance.\n"<<"check line :"<<line;
		///exit(1);
	}
	x=value.at(0);
	y=value.at(1);
	z=value.at(2);
	w=value.at(3);
	if(abs(w)>10e-6)
	{
		x /=w ;
		y /=w ;
		z /=w ;
	}
	r=value.at(4);
	g=value.at(5);
	b=value.at(6);
	cout<<"light is at "<<x<<" "<<y<<" "<<z<<endl;
	cout<<"r g b is "<<setw(5)<<r<<setw(5)<<g<<setw(5)<<b<<endl;



}

light::~light() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
