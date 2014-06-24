/*
 * materail.h
 *
 *  Created on: Nov 9, 2012
 *      Author: bhikadiy
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_
#include "Includes.h"

namespace std {

class material {


	string name;
	int index;

public:
	vector<double>ka,kd,ks;
	double ns,n1,Tr,Kr,Krf;
	material();
	void assign_name(string,int);
	void assign_ka(string);
	void assign_kd(string);
	void assign_ks(string);
	void assign_ns(string);
	void assign_n1(string);
	void assign_Tr(string);
	void assign_Kr(string);
	void assign_Krf(string);
	string get_name(){return name;}
	int get_index(string);
	virtual ~material();
};

} /* namespace std */
#endif /* MATERAIL_H_ */
