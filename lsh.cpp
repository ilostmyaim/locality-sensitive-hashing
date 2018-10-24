#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include "LSH.h"
#include "hash.h"


using namespace std;

int main(int argc, char **argv) {
	vector_t vec;
	string line;

	int k,L;
	string input_file, output_file, query_file;

	/*initialize parameters*/
	initParameters(&k, &L, input_file, output_file, query_file, argc, argv);

	/*create an LSH object*/
	Metric metric = cosine;
	LSH lshObject(k, L, input_file, output_file, query_file,metric);
	lshObject.executeLSH(metric);
	//lshObject.displayLSH();




	return 0;

}
