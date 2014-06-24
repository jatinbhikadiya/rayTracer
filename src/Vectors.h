/*
 * Vectors.h
 *
 *  Created on: Sep 27, 2012
 *      Author: bhikadiy
 */

#ifndef VECTORS_H_
#define VECTORS_H_

#include<vector>
#include<iostream>
#include<cmath>

class vectors {

public:
	std::vector<double> vect;
	vectors();
	vectors(std::vector<double>);
	void assignvector(std::vector<double>);
	void cross(vectors, vectors);
	double dot(vectors);
	double magnitude();
	void printvect();
	void normalize();
	std::vector<double> getvect();
	virtual ~vectors();

};

/* namespace std */
#endif /* VECTORS_H_ */
