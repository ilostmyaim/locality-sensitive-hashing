#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include <fstream>
#include <sstream>
#include<math.h>
#include <algorithm>
#include "CUBE.h"
#include "hash.h"
#include "LSH.h"



using namespace std;


CUBE::CUBE(int k, int m, int probes, string inputFile, string outputFile, string queryFile,Metric metric)
{
	_k = k;
	_MC = m;
	_probes = probes;
	_inputFile = inputFile;
	_queryFile = queryFile;
	_outputFile = outputFile;
	//_hashTable = new Hash()

}



void initParameters(int* k, int* m, int* probes, std::string &input_file, std::string & output_file, std::string & query_file,int argc, char** argv)
{
	int i;
	//int k_flag = 0, m_flag = 1, input_flag = 1, output_flag = 1, query_flag = 1;
	for(i = 1; i<argc; i++){
		if(strcmp(argv[i], "-o") == 0){
			i++;
			output_file = argv[i];
			//output_flag = 1;
		}
		else if(strcmp(argv[i],"-q") == 0){
			i++;
			query_file = argv[i];
			//query_flag = 1;
		}
		else if(strcmp(argv[i],"-d") == 0){
			i++;
			input_file = argv[i];
			//input_flag = 1;
		}
		else if(strcmp(argv[i],"-k") == 0){
			i++;
			*k=stoi(argv[i]);
			//k_flag = 1;
		}
		else if(strcmp(argv[i],"-L") == 0){
			i++;
			*m=stoi(argv[i]);
			//m_flag = 1;
		}
		else if(strcmp(argv[i],"-probes") == 0){
			i++;
			*probes=stoi(argv[i]);
		}
	}
}