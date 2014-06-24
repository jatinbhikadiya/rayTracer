/*
 * Vectors.cpp
 *
 *  Created on: Sep 27, 2012
 *      Author: bhikadiy
 */

#include "Vectors.h"


vectors::vectors()
{
	// TODO Auto-generated constructor stub
	vect.push_back(0);
	vect.push_back(0);
	vect.push_back(0);

}
vectors::vectors(std::vector<double>xyz)
{
		vect.push_back(xyz.at(0));
		vect.push_back(xyz.at(1));
		vect.push_back(xyz.at(2));
}

void vectors::assignvector(std::vector<double>xyz)
{
		vect[0]=xyz.at(0);
		vect[1]=xyz.at(1);
		vect[2]=xyz.at(2);
}
void vectors:: cross(vectors a,vectors b)
{
	vect[0]=(a.vect[1]*b.vect[2])-(a.vect[2]*b.vect[1]);
	vect[1]=(a.vect[2]*b.vect[0])-(a.vect[0]*b.vect[2]);
	vect[2]=(a.vect[0]*b.vect[1])-(a.vect[1]*b.vect[0]);
}

double vectors:: dot(vectors b)
{
	double dot=(vect[0]*b.vect[0])+ (vect[1]*b.vect[1]) + (vect[2]*b.vect[2]);
	//cout<<"dot done"<<endl;
	return dot;
}

double vectors::magnitude()
{
	double mag=sqrt((vect[0]*vect[0])+(vect[1]*vect[1])+(vect[2]*vect[2]));
	return mag;
}

void vectors:: printvect()
{
	std::cout<<std::endl<<"\t\tx\t\ty\t\tz";
	std::cout<<std::endl<<"\t\t"<<vect[0]<<"\t\t"<<vect[1]<<"\t\t"<<vect[2];
}

void vectors:: normalize()
{
	double amag=magnitude();
	vect[0]=vect[0]/amag;
	vect[1]=vect[1]/amag;
	vect[2]=vect[2]/amag;
}

std::vector<double> vectors::getvect()
{
	return vect;
}

vectors::~vectors()
{
	// TODO Auto-generated destructor stub
}

 /* namespace std */
