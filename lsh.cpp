#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <chrono>
#include "LSH.h"
#include "hash.h"


using namespace std;
using namespace std::chrono;

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
	auto start = high_resolution_clock::now();
	lshObject.executeLSH(metric);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop-start);

	cout << "Time = " << duration.count() << "seconds" << endl;
	//lshObject.displayLSH();




	return 0;

}
