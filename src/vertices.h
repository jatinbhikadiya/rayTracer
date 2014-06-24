/*
 * vertices.h
 *
 *  Created on: Sep 16, 2012
 *      Author: bhikadiy
 */

#ifndef VERTICES_H_
#define VERTICES_H_
#include <vector>
using namespace std;
class vertices {

	//double x,y,z,wm;
	int vertex_index;
	vector<double>ver;
public:

	vertices();
	vertices(const vertices &);
	void assign_values(vector<double>&);
	void change_values(vector<double>&);
	vector<double> get_values();

	virtual ~vertices();
};

#endif /* VERTICES_H_ */
