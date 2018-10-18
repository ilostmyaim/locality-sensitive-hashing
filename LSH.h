#pragma once

#include<string>
#include<vector>
#include "hash.h"

enum Metric { euclidean , cosine };

#define M 60000000000
class LSH {

private:

	int _k; //number of locality-sensitive functions hi
	int _L; //number of hash tables
	std::string _inputFile;
	std::string _outputFile;
	std::string _queryFile;
	Hash **_arrayOfHashTables; //L-Hash objects
	int _hashTableSize;



public:

	LSH(int k=4, int L=5, std::string inputFile = "input_file", std::string outputFile="output_file", std::string queryFile="query_file"); //constructor
	int get_k();
	int get_L();
	std::string get_inputFile();
	std::string get_outputFile();
	int hash(int ,int);
	void executeLSH(Metric);
	void insertLSH(item_t item,unsigned int hashValue, int l);

};

/*parse command line parameters*/
void initParameters(int* k, int* L, std::string & input_file, std::string & output_file, std::string & query_file,int argc, char** argv);





