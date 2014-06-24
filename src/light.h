/*
 * light.h
 *
 *  Created on: Nov 12, 2012
 *      Author: bhikadiy
 */

#ifndef LIGHT_H_
#define LIGHT_H_
#include "Includes.h"
namespace std {

class light {

	int index;
public:
	light();
	int w;
	double x,y,z,r,g,b;
	void pushvalues(string,int );
	virtual ~light();
};

} /* namespace std */
#endif /* LIGHT_H_ */
