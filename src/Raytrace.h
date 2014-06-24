/*
 * Raytrace.h
 *
 *  Created on: Sep 10, 2013
 *      Author: bhikadiy
 */

#ifndef RAYTRACE_H_
#define RAYTRACE_H_

#include "Includes.h"
#include "Sphere.h"
#include "Manager.h"
#include "Image.h"
#include "Camera.h"
#include "Vectors.h"
#include "groups.h"
#include "material.h"
#include "Read_objects.h"
#include "light.h"
class Ray_trace {

	std::vector<Sphere> &spheres;
	Image &color_img;

	Camera &cam;
	std::vector<double> focal_point;
	double n_current,n_next;
	vector<groups>objects;
	vector<vertices>ver;
	vector<material>mat;
	vector<light>lights;
	int recursion_refl, recursion_refr;



public:
	Ray_trace();
	Ray_trace(std::vector<Sphere>&s, Image &i, Camera &c,vector<groups>&o,
	vector<vertices>&v,vector<material>&m,vector<light>&l) :spheres(s), color_img(i),cam(c),
			objects(o),ver(v),mat(m),lights(l)	{};
	void ray_trace();
	void ray_refl(std::vector<double> &,vectors,vector<double>& );
	double intersection_sphere(vectors ,int  ,vector<double>);
	double intersection_object(vectors ,int , int ,vector<double>);
	void point_refl_ellipse(vector<int>, double , vector<double>&,vectors ,vector<double> );
	void cal_diffuse_sphere(vector<double>, vector<int>,int,vector<double>&,vectors);
	void cal_spec_sphere(vector<double>, vector<int>,int ,vector<double>&,vectors , vectors);
	int shadow(vectors , vector<double>,vector<int>,double );



	void point_refl_objects(vector<int>, double , vector<double>&,vectors,vector<double>);
	//int  shad_objects(vectors , vector<double>,vector<int>,double);

	void cal_spec_objects(vector<double>, vector<int>,int,vector<double>&,vectors , vectors );
	void cal_diffuse_objects(vector<double>, vector<int>,int,vector<double>&,vectors);

	void cal_reflection_sphere(vector<double>pt,vector<int >surf, vector<double> &ref,vectors r );
	void cal_reflection_objects(vector<double>pt,vector<int >surf, vector<double> &ref,vectors r );
	void cal_refraction_sphere(vector<double>pt,vector<int >surf, vector<double> &refr,vectors r );

	void printfile(std::vector<std::vector<std::vector<double> > > &,
			std::string, std::string);

	virtual ~Ray_trace();
};

#endif /* RAYTRACE_H_ */
