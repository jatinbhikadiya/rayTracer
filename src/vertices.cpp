/*
 * vertices.cpp
 *
 *  Created on: Sep 16, 2012
 *      Author: bhikadiy
 */

#include "vertices.h"
#include <iostream>
#include <vector>
#include <memory>
using namespace std;
vertices::vertices() {
	// TODO Auto-generated constructor stub

}

vertices :: vertices(const vertices& v)
{
	vertex_index=v.vertex_index;
	ver=v.ver;
}

vector<double> vertices::get_values()
{
	return ver;

}

void vertices::assign_values(vector<double>&v)
{
	//cout<<endl<<v.at(0)<<"\t"<<v.at(1)<<"\t"<<v.at(2)<<"\t"<<v.at(3)<<"\t"<<endl;
	for (int i=0;i<(int)v.size();i++)
		{
		//cout<<v.at(i)<<"\t"<<i<<endl;
		ver.push_back(v.at(i));

		}
	//cout<<endl<<ver.at(0)<<ver.at(1)<<ver.at(2)<<ver.at(3)<<"\t"<<endl;
	//cout<<endl<<ver.size();

}

void vertices::change_values(vector<double>&v)
{
	for (int i=0;i<(int)v.size();i++)
			{
			//cout<<v.at(i)<<"\t"<<i<<endl;
			ver.at(i)=v.at(i);

			}
}
vertices::~vertices() {
	// TODO Auto-generated destructor stub
}

