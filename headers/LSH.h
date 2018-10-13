#pragma once

#include<string>
#include "../headers/hash.h"

class LSH {

private:

	int _k; //number of locality-sensitive functions hi
	int _L; //number of hash tables
	std::string _inputFile;
	std::string _outputFile;
	Hash** _arrayOfHashTables; //L-hashtables



public:

	LSH(int k=4, int L=5, std::string inputFile = "input_file", std::string outputFile="output_file"); //constructor





};

/*parse command line parameters*/
void initParameters(int* k, int* L, std::string & input_file, std::string & output_file, std::string & query_file,int argc, char** argv);

