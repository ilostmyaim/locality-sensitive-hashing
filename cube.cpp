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
	string input_file, output_file, query_file, met;
	Metric metric;
	/*initialize parameters*/
	initParametersCube(&d, &m, &probes, input_file, output_file, query_file, met, argc, argv);
	if(met.compare("cosine") == 0) { 
		metric = cosine;
	}
	else{ 
		metric = euclidean;
	}

	/*create a Hybercube object*/
	//metric = cosine;
	CUBE cubeObject(d, m, probes, input_file, output_file, query_file, metric);

	ofstream outputFile(output_file);
	streambuf *coutbuf = cout.rdbuf();
	cout.rdbuf(outputFile.rdbuf());

	
	cubeObject.executeCUBE(metric);
	
	//cubeObject.displayCUBE();
	
	cout.rdbuf(coutbuf);


}	
