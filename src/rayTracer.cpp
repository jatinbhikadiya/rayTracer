//============================================================================
// Name        : HW1.cpp
// Author      : Jatin Bhikadiya
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include "Includes.h"
#include "Manager.h"
#define INFO  "This is the basic Ray Tracer. It takes two input files as arguments. \n1) .obj file which contains information about sphere in the 3D space. \n2) Command file which states how far is the camera from the origin and also tells about gives the information about the output image to be generated.\n"
int through_error(int, std::string str = "\0");
int check_for_error(int, char**);

int main(int argc, char** argv) {
	std::cout << INFO;
	check_for_error(argc, argv);
	Manager m;
	m.read_files(argv);
	m.ray_trace();
	std::cout<<"done\n";
	return EXIT_SUCCESS;
}

int check_for_error(int argc, char** argv) {
	if (argc != 3)
		return through_error(1);

	//check for first file reading failure or whether file is available or not
	std::ifstream istr(argv[1]);
	if (istr.fail())
		return through_error(2, argv[1]);

	//check for second file reading failure or whether file is available or not
	std::ifstream istr1(argv[2]);
	if (istr1.fail())
		return through_error(2, argv[2]);
	return 1;
}

int through_error(int a, std::string str) {
	switch (a) {
	case 1:
		std::cout
				<< "\n\n------ERROR------\nThis program requires two arguments as below.\n1. Wavefront Object File(It must be .obj format)\n2. Command File(Both must exist)\n ";
		return -1;
	case 2:
		std::cout
				<< "\n\n------ERROR------\nStringstream failed to read or file "
				<< str << ". File does not exist\n" << std::endl;
		return -1;
	case 3:
		std::cout << str << " must be wavefront .obj file\n";
		return -1;
	default:
		return -1;

	}
}
