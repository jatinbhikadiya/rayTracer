/*
 * groups.h
 *
 *  Created on: Sep 16, 2012
 *      Author: bhikadiy
 */

#ifndef GROUPS_H_
#define GROUPS_H_

using namespace std;
#include <iostream>
#include <vector>
#include "faces.h"


class groups {

	string name;
	int group_index;
	int total_faces;
public:
	vector<faces>face;
	vector<int>all_vertices;
    vector<int>vertices_number;
	groups();
	int get_index(string&);
	void print_me();
	string get_name(void);
	void assign_name(string &, int);
	vector<int> getface(int);
	void assign_faces(vector<int>, int );
	vector<int> get_vertices_no(void);
	int get_total_faces(void);
	virtual ~groups();
};

#endif /* GROUPS_H_ */
