/*
 * Readobjects.h
 *
 *  Created on: Sep 18, 2012
 *      Author: bhikadiy
 */

#ifndef READ_OBJECTS_H_
#define READ_OBJECTS_H_
#include "Includes.h"
#include "groups.h"
#include "vertices.h"
#include "Vectors.h"
#include "Sphere.h"
#include "material.h"

class Read_objects {

	vector<groups>&objects;
	vector<vertices>&ver;
	vector<Sphere>&spheres;
	int total_objects, total_vertices, total_spheres,total_faces,current_mat_index;
	string current_object, current_mat;
	vector<material>&mat;


public:
	Read_objects(vector<groups>&obj,vector<vertices>&v,vector<Sphere>&s,vector<material>&m):objects(obj),ver(v),spheres(s),mat(m){};
	vector<int> read_file(char* );
	void obj_first_pass(char *);
	void obj_second_pass(char *);

	char* get_filepath(char* file_name);
	void  pushback_v(vector<double>&);
	void read_mat(string , char*);
	int get_group_index(string &);
	int get_material_index(string &);
	void pushback_g(string);
	void pushback_e(string,int );
	void face_errors(int&,vector<int>&);
	void read_v(string&, int);
	void convert2vectors(vector<vectors>&,vector<int>&);
	bool check_colinear(vector<vectors>);
	bool check_coplanar(vector<vectors>&);
	bool check_convex(vector<vectors>&);

	virtual ~Read_objects();
};

 /* namespace std */
#endif /* READOBJECTS_H_ */
