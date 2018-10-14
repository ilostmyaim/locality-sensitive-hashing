#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<fstream>
#include<math.h>
#include "../headers/LSH.h"
#include "../headers/GenericVector.h"


using namespace std;


LSH::LSH(int k, int L, string inputFile, string outputFile)
{
	/*initialize parameters*/
	_k = k;
	_L = L;
	_inputFile = inputFile;
	_outputFile = outputFile;
	_arrayOfHashTables = new Hash*[_L]; //create array of pointers to hashtables
	_hashTableSize = pow(2,_k);
}

void initParameters(int* k, int* L, std::string &input_file, std::string & output_file, std::string & query_file,int argc, char** argv)
{
	int i;
	for(i = 1; i<argc; i++){
		if(strcmp(argv[i], "-o") == 0){
			i++;
			output_file = argv[i];
		}
		else if(strcmp(argv[i],"-q") == 0){
			i++;
			query_file = argv[i];
		}
		else if(strcmp(argv[i],"-d") == 0){
			i++;
			input_file = argv[i];
		}
		else if(strcmp(argv[i],"-k") == 0){
			i++;
			*k=stoi(argv[i]);
		}
		else if(strcmp(argv[i],"-L") == 0){
			i++;
			*L=stoi(argv[i]);
		}
	}
}

