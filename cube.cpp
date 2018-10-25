#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include "CUBE.h"

using namespace std;

int main(int argc, char **argv) {
	vector_t vec;

	int d,m,probes;
	string input_file, output_file, query_file;

	initParametersCube(&d, &m, &probes, input_file, output_file, query_file, argc, argv);

	/*create a Hybercube object*/
	Metric metric = euclidean;

	CUBE cubeObject(d, m, probes, input_file, output_file, query_file, metric);
	cubeObject.executeCUBE(metric);
	//cubeObject.displayCUBE();


}	
