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
	LSH lshObject(k, L, input_file, output_file, query_file);
	Metric metric = euclidean;
	lshObject.executeLSH(metric);




	return 0;

}
