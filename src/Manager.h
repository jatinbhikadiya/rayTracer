/*
 * Manager.h
 *
 *  Created on: Sep 9, 2013
 *      Author: bhikadiy
 */

#ifndef MANAGER_H_
#define MANAGER_H_
#include "Includes.h"
#include "Sphere.h"
#include "Vectors.h"
#include "Camera.h"
#include "Raytrace.h"
#include "Image.h"
#include "groups.h"
#include "material.h"
#include "Read_objects.h"
#include "light.h"
class Manager {

	Image color_img;
	std::vector<Sphere> spheres;
	std::vector<Camera> cameras;

	vector<groups>objects;
	vector<vertices>ver;
	vector<material>mat;
	vector<light>lights;

public:
	Manager();
	void read_files(char **);
	void read_obj(char *);
	void read_command(char *);

	void ray_trace();
	virtual ~Manager();
};

#endif /* MANAGER_H_ */
