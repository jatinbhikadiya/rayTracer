/*
 * Image.h
 *
 *  Created on: Sep 10, 2013
 *      Author: bhikadiy
 */

#ifndef IMAGE_H_
#define IMAGE_H_
#include "Includes.h"
class Image {

	std::string Image_name;
	std::vector<std::vector<std::vector<double> > > image;
	int width,height,recursion;
public:
	Image();
	void initialize_image();
	void printfile(std::string);
	void  assign(std::string);
	void fill_pixel(std::vector<double> &, int , int );
	inline void clear_image(){image.clear();}
	inline int get_width(){return width;};
	inline int get_height(){return height;};
	inline int get_recursion(){return recursion;};

	virtual ~Image();
};

#endif /* IMAGE_H_ */
