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
	int _hashTableSize;



public:

	LSH(int k=4, int L=5, std::string inputFile = "input_file", std::string outputFile="output_file"); //constructor
	int get_k();
	int get_L();
	std::string get_inputFile();
	std::string get_outputFile();







};

/*parse command line parameters*/
void initParameters(int* k, int* L, std::string & input_file, std::string & output_file, std::string & query_file,int argc, char** argv);


class L2Hash {

private:
	int _r;
	int _b,
	int _w;

public:
	L2Hash(std::vector<int> , int , int);
	int hash(std::vector<int>);
	int L2_norm(std::vector<int>, std::vector<int>);



};

class L2HashFamily{
private:
	int _w;
	int _d;

public:
	L2HashFamily(int w, int d);

	L2Hash create_hash_func();
	std::vector<int> rand_vec();
	int rand_offset();
	string combine(); //concatenate hash values from hi functions


};


