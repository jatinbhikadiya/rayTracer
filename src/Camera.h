/*
 * Camera.h
 *
 *  Created on: Sep 10, 2013
 *      Author: bhikadiy
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#include "Includes.h"
#include "Vectors.h"
class Camera {

	double focal_length,near_d,far_d;
	std::string cam_name;
	vectors vpn, vup;
	std::vector<double> prp,near_plane,far_plane;

public:
	Camera();
	void assign(std::string);
	inline std::string getname() {
		return cam_name;
	}

	inline double get_fl() {
		return focal_length;
	}
	inline std::vector<double> get_prp() {
		return prp;
	}
	inline double get_near(){
		return near_d;
	}
	inline double get_far(){
			return far_d;
	}
	inline vectors get_vpn(){
		return vpn;
	}
	inline vectors get_vup(){
		return vup;
	}
	std::vector<double>  get_point_on_near(vectors , std::vector<double> );
	std::vector<double>  get_point_on_far(vectors , std::vector<double> );
	bool check_point_position(std::vector<double>);


	virtual ~Camera();
};

#endif /* CAMERA_H_ */
