/*
 * Sphere.cpp
 *
 *  Created on: Sep 4, 2013
 *      Author: bhikadiy
 */

#include "Sphere.h"

Sphere::Sphere() {
	x=0,y=0,z=0,r=0,R=0,G=0,B=0,r2=0;
	// TODO Auto-generated constructor stub

}
void Sphere:: assign(std::string line,int mat_ind)
{
	std::istringstream s;
	s.str(line);
	std::string temp;
	s>>temp;
	s>>temp;
	s>>x;
	s>>y;
	s>>z;
	s>>r;
	s>>R;
	s>>G;
	s>>B;
	r2=r*r;
	mat_index=mat_ind;
}

vectors  Sphere:: O_minus_focal_point(std::vector<double>fp)
{
	std::vector<double> omfp;
	omfp.push_back(x-fp.at(0));
	omfp.push_back(y-fp.at(1));
	omfp.push_back(z-fp.at(2));
	vectors OMFP(omfp);
	return OMFP;

}


vectors Sphere:: surf_normal(std::vector<double>pt)
{

	//cout<<"surf normal"<<endl;
	std::vector<double>norm;
	norm.push_back(pt.at(0)-x);
	norm.push_back(pt.at(1)-y);
	norm.push_back(pt.at(2)-z);
	vectors normal(norm);
	normal.normalize();
	//cout<<"surf normal end"<<endl;
	return normal;
}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}

