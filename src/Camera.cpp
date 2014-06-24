/*
 * Camera.cpp
 *
 *  Created on: Sep 10, 2013
 *      Author: bhikadiy
 */

#include "Camera.h"

Camera::Camera() {
	// TODO Auto-generated constructor stub
	far_d = 0;
	near_d = 0;
	focal_length=0;
	near_plane.push_back(0);
	near_plane.push_back(0);
	near_plane.push_back(-1);
	far_plane.push_back(0);
	far_plane.push_back(0);
	far_plane.push_back(-1);
}

void Camera::assign(std::string line) {

	near_plane.resize(3);
	far_plane.resize(3);

	std::istringstream s;
	s.str(line);
	std::string temp;
	s >> temp;
	s >> cam_name;
	for(int i=0;i<3;i++)
	{
		double t;
		s>>t;
		prp.push_back(t);
	}
	std::vector<double> temp_vpn, temp_vup;
	for(int i=0;i<3;i++)
	{
		double t;
		s>>t;
		temp_vpn.push_back(t);
	}
	vpn.assignvector(temp_vpn);
	vpn.normalize();

	for(int i=0;i<3;i++)
	{
		double t;
		s>>t;
		temp_vup.push_back(t);
	}
	vup.assignvector(temp_vup);

	s >> near_d;
	s >> far_d;

	focal_length = near_d;


}

/*std::vector<double> Camera::get_point_on_near(vectors ray,
		std::vector<double> focal_point) {
	// for ray R=P0+tV and plane P*N+d=0 ---> intersection is Point = P0+ tV where t = -(P0*N+d)/(V*N) = distance here
	double distance, fp_dot_n, v_dot_n;
	vectors fp(focal_point);
	fp_dot_n = near_p.dot(fp);
	v_dot_n = near_p.dot(ray);
	distance = (-1) * (fp_dot_n - near_d) / (v_dot_n);

	std::vector<double> point_on_near;
	point_on_near.push_back(focal_point.at(0) + distance * ray.vect.at(0));
	point_on_near.push_back(focal_point.at(1) + distance * ray.vect.at(1));
	point_on_near.push_back(focal_point.at(2) + distance * ray.vect.at(2));
	return point_on_near;
}

std::vector<double> Camera::get_point_on_far(vectors ray,
		std::vector<double> focal_point) {
	double distance, fp_dot_n, v_dot_n;
	vectors fp(focal_point);
	fp_dot_n = far_p.dot(fp);
	v_dot_n = far_p.dot(ray);
	distance = (-1) * (fp_dot_n - far_d) / (v_dot_n);

	std::vector<double> point_on_far;
	point_on_far.push_back(focal_point.at(0) + distance * ray.vect.at(0));
	point_on_far.push_back(focal_point.at(1) + distance * ray.vect.at(1));
	point_on_far.push_back(focal_point.at(2) + distance * ray.vect.at(2));

	vectors temp(point_on_far);
	 temp.printvect();
	return point_on_far;
}

bool Camera::check_point_position(std::vector<double> point) {
	vectors p(point);
	double point2near, point2far;
	point2near = p.dot(near_p) - near_d;
	point2far = p.dot(far_p) - far_d;
	if (point2near * point2far < 0) {
		return 1;
	} else {
		return 0;
	}
}*/

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

