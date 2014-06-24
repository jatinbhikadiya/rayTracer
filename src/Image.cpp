/*
 * Image.cpp
 *
 *  Created on: Sep 10, 2013
 *      Author: bhikadiy
 */

#include "Image.h"

Image::Image() {
	// TODO Auto-generated constructor stub
	width  = 0;
	height = 0;
	recursion = 0;
}

void Image::assign(std::string line) {
	std::istringstream s;
	s.str(line);
	std::string temp;
	s >> temp;
	s >> Image_name;
	s >> width;
	s >> height;
	s >> recursion;
}

void Image::initialize_image() {
//initialize image
	image.resize(width);
	for (int i = 0; i < width; i++) {
		image[i].resize(height);
		for (int j = 0; j < height; j++) {
			image[i][j].resize(3);
		}
	}
}

void Image::fill_pixel(std::vector<double> & color_value, int row, int col) {
	image.at(row).at(col).at(0) = (int)color_value.at(0);
	image.at(row).at(col).at(1) = (int)color_value.at(1);
	image.at(row).at(col).at(2) = (int)color_value.at(2);

}

void Image::printfile(std::string cam_name) {
	std::stringstream filename;


	filename << Image_name << "_" << cam_name << ".ppm";

	std::cout << "Generating output image " << filename.str().c_str() << std::endl;
	std::ofstream object_file;
	//open file
	object_file.open(filename.str().c_str());
	std::cout << std::endl << "writing image " << filename.str().c_str()<<std::endl;
	object_file << "P3\t" << image.size() << "\t" << image.at(0).size() << "\t"
			<< 256 << std::endl;
	for (unsigned int i = 0; i < image.size(); i++) {
		for (unsigned int j = 0; j < image.at(0).size(); j++) {
			for (int k = 0; k < 3; k++) {
				if( image.at(i).at(j).at(k) > 255)
				{
					 image.at(i).at(j).at(k) = 255;
				}
				object_file << image.at(i).at(j).at(k) << " ";
			}
			object_file << std::endl;
		}
	}
	object_file.close();
	std::cout << std::endl << "Done with writing image" << std::endl;
}

Image::~Image() {
	// TODO Auto-generated destructor stub
}

