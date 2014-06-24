/*
 * Manager.cpp
 *
 *  Created on: Sep 9, 2013
 *      Author: bhikadiy
 */

#include "Manager.h"

Manager::Manager() {
	// TODO Auto-generated constructor stub

}

void Manager::read_files(char **argv) {

	Read_objects reader(objects,ver,spheres,mat);
	vector<int> total_numbers = reader.read_file(argv[1]);
	std::cout<<"\ntotal objects :"<<total_numbers.at(0)<<" match : "<<objects.size();
	std::cout<<"\ntotal spheres :"<<total_numbers.at(1)<<" match :"<<spheres.size();
	std::cout<<"\ntotal vertices :"<<total_numbers.at(2)<<" match :"<<ver.size()<<std::endl;

	read_command(argv[2]);

}


void Manager::read_command(char * command_file_name) {

	std::ifstream command_file;
	command_file.open(command_file_name);
	int light_index =0;
	if (command_file.is_open()) {
		std::cout << "Reading commands from " << command_file_name << std::endl;
		while (!command_file.eof()) {
			std::string line, a, temp;
			std::istringstream s;
			getline(command_file, line);
			s.str(line);
			s >> a;
			if (a == "c") {
				Camera temp;
				temp.assign(line);
				cameras.push_back(temp);
			}
			if (a == "r") {
				color_img.assign(line);
			}
			if(a == "l")
			{
				light l;
				l.pushvalues(line,light_index);
				lights.push_back(l);
			}
		}
	}
	cout<<"no of lights :"<<lights.size()<<endl;
}

void Manager::ray_trace() {

	for (unsigned int i = 0; i < cameras.size(); i++) {
		cout<<"\ncamera :"<<cameras.at(i).getname()<<endl;
		Ray_trace r(spheres, color_img, cameras.at(i),objects,ver,mat,lights);
		color_img.initialize_image();

		r.ray_trace();
		color_img.printfile(cameras.at(i).getname() + "color");
		color_img.clear_image();
	}

}



Manager::~Manager() {
	// TODO Auto-generated destructor stub
}

