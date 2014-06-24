/*
 * Sphere.h
 *
 *  Created on: Sep 4, 2013
 *      Author: bhikadiy
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Includes.h"
#include "Vectors.h"
class Sphere {

public:
	Sphere();
	double x,y,z,r,R,G,B,r2,mat_index;
	void assign(std::string,int);
	vectors  O_minus_focal_point(std::vector<double>fp);
	vectors surf_normal(std::vector<double>pt);

	virtual ~Sphere();
};

#endif /* SPHERE_H_ */
