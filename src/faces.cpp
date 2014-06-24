/*
 * faces.cpp
 *
 *  Created on: Sep 16, 2012
 *      Author: bhikadiy
 */
#include <iostream>
#include "faces.h"

#include <vector>
using namespace std;

faces::faces() {
	// TODO Auto-generated constructor stub

}

vector<int> faces::get_values()
{
	return face;
}

void faces:: print_me()
{

	for(unsigned int i=0;i<face.size();i++)
	{
		cout<<face.at(i)<<" ";
	}
	cout<<" \t Material :"<<mat_index;
}
void faces::assign_values(vector<int>v, int m_index)
{
	//cout<<endl;
	mat_index=m_index;
	for (int i=0;i<(int)v.size();i++)
		{

		face.push_back(v.at(i));
		//cout<<face.at(i)<<"\t";
		}


}

void faces:: cal_fptov(vector<double>f,vector<vertices>&ver)
{
	vector<double>v1,v2,face1,face2,face3;
	v0=ver.at(face.at(0)-1).get_values();
	v1=ver.at(face.at(1)-1).get_values();
	v2=ver.at(face.at(2)-1).get_values();
	face1.push_back(v1.at(0)-v0.at(0));
	face1.push_back(v1.at(1)-v0.at(1));
	face1.push_back(v1.at(2)-v0.at(2));
	face2.push_back(v2.at(0)-v0.at(0));
	face2.push_back(v2.at(1)-v0.at(1));
	face2.push_back(v2.at(2)-v0.at(2));
	face3.push_back(v2.at(0)-v1.at(0));
	face3.push_back(v2.at(1)-v1.at(1));
	face3.push_back(v2.at(2)-v1.at(2));

	//	cout<<face.size()<<endl;
	//	cout<<"v0 is "<<setw(8)<<v0.at(0)<<setw(8)<<v0.at(1)<<setw(8)<<v0.at(2)<<endl;
	//	cout<<"v1 is "<<setw(8)<<v1.at(0)<<setw(8)<<v1.at(1)<<setw(8)<<v1.at(2)<<endl;
	//	cout<<"v2 is "<<setw(8)<<v2.at(0)<<setw(8)<<v2.at(1)<<setw(8)<<v2.at(2)<<endl;
	f1.assignvector(face1);
	f2.assignvector(face2);
	vectors f3(face3);
	normal.cross(f1,f3);
	normal.normalize();
		//cout<<endl;
		//cout<<endl<<ver.size();
	vector<double> fp2v;
	fp2v.push_back(f.at(0)-v0.at(0));
	fp2v.push_back(f.at(1)-v0.at(1));
	fp2v.push_back(f.at(2)-v0.at(2));
	fptov0.assignvector(fp2v);
	q.cross(fptov0,f1);
	//q.normalize();

}


vectors faces:: cal_ptov(vector<double>f)
{

	//	cout<<face.size()<<endl;
	//	cout<<"v0 is "<<setw(8)<<v0.at(0)<<setw(8)<<v0.at(1)<<setw(8)<<v0.at(2)<<endl;
	//	cout<<"v1 is "<<setw(8)<<v1.at(0)<<setw(8)<<v1.at(1)<<setw(8)<<v1.at(2)<<endl;
	//	cout<<"v2 is "<<setw(8)
		//cout<<endl;
		//cout<<endl<<ver.size();
	vector<double> p2v;
	p2v.push_back(f.at(0)-v0.at(0));
	p2v.push_back(f.at(1)-v0.at(1));
	p2v.push_back(f.at(2)-v0.at(2));
	vectors ptov0;
	ptov0.assignvector(p2v);
	return ptov0;
	//q.normalize();

}

vector<int> faces::get_face()
{
	return face;
}

faces::~faces() {
	// TODO Auto-generated destructor stub
}

