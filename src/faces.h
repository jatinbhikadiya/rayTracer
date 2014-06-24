/*
 * faces.h
 *
 *  Created on: Sep 16, 2012
 *      Author: bhikadiy
 */

#ifndef FACES_H_
#define FACES_H_
#include "Vectors.h"
#include "vertices.h"

using namespace std;
class faces {

	vector<int>face;
	int face_index;
	vector<double> v0;

public:

	int  mat_index;
	vectors f1,f2,fptov0,q,normal;
	faces();
	void print_me();
	void cal_fptov(vector<double>f,vector<vertices>&);
	vectors cal_ptov(vector<double>f);
	void assign_values(vector<int>,int);
	vector<int> get_values();
	vector<int> get_face();
	virtual ~faces();
};

#endif /* FACES_H_ */
