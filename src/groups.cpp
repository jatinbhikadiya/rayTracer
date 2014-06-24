/*
 * groups.cpp
 *
 *  Created on: Sep 16, 2012
 *      Author: bhikadiy
 */

#include "groups.h"
#include "string.h"
#include "faces.h"
//#include "vertices.h"
#include <memory>
using namespace std;

groups::groups() {
	// TODO Auto-generated constructor stub
	total_faces=0;
	//vertex_index=0;

}

void groups::assign_name(string &name1, int index1)
{
name=name1;
group_index= index1;
cout<<"object "<<name<<" is generated - object index is "<<group_index<<endl;

}

int groups::get_index(string&name1)
{
	if (name1 == name)
		return group_index;
	else
		return -1;
}

void groups:: print_me()
{
	cout<<"\nname :"<<name;
	cout<<"\n No. Faces : "<<total_faces;
	for(unsigned int i=0;i<face.size();i++)
	{
		cout<<"\nface "<<i<<": ";
		face.at(i).print_me();
	}

}


void groups::assign_faces(vector<int>f, int m_index )
{
	//cout<<" programm is in assign_verticeas under groups.cpp";
	total_faces++;

	faces p;
	face.push_back(p);
	face.at(total_faces-1).assign_values(f,m_index);
	//cout<<"\t"<<"face number "<<total_faces<<" assigned of object "<<name<<endl;
}

string groups:: get_name(void)
{
	return name;
}


int groups::get_total_faces(void)
{
	return total_faces;
}

vector<int> groups::getface(int i)
{
	vector<int>f;

	f=face.at(i).get_face();
	return f;
}

vector<int> groups:: get_vertices_no()
{
return vertices_number;
}

groups::~groups() {
	// TODO Auto-generated destructor stub
}

