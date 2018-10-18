#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include <fstream>
#include <sstream>
#include<math.h>
#include <algorithm>
#include "LSH.h"
#include "hash.h"



using namespace std;

LSH::LSH(int k, int L, string inputFile, string outputFile, string queryFile)
{
	/*initialize parameters*/
	_k = k;
	_L = L;
	_inputFile = inputFile;
	_outputFile = outputFile;
	_queryFile = queryFile;
	_arrayOfHashTables = new Hash*[_L]; //create array of pointers to hashtables
	_hashTableSize = pow(2,_k);
	for(int i = 0;i<_L;i++){ 
		_arrayOfHashTables[i] = new Hash(_hashTableSize);
		
	}
}

void LSH::executeLSH(Metric metric)
{
	if(metric == euclidean){
		//do stuff
		int i_l,j_k,i_vec=0; //counter for L and k respectively
		int w = 4;
		string line;
		double pValue=0; //read values from input file here
		vector<double> vec; //store p_values to vec while reading
		ifstream inputFile(_inputFile);// input file stream
		string hash_string;
		L2_Hash l2_hash(w);
		string hash_value;
		long double actualHashValue=0; 
		static unsigned int vec_id = 0; // id for each vector readen
		item_t item;

		

		cout << "Im innnnn"<< endl;
		

		for(i_l=0;i_l<_L;i_l++){
			/*start reading points*/
			//
			if (inputFile.is_open()) {
				while(inputFile >> pValue) {
					if(i_vec < DIMENSION){ 
						vec.push_back(pValue);
						i_vec++;
					}
					else{//create hi hash functions and concatenate to create g
						for(j_k=0;j_k < _k;j_k++){
							hash_string = to_string(l2_hash.hash(vec));
							cout << "Hash string : " << hash_string<< endl;
							hash_value.append(hash_string);
							l2_hash.random_vector();
							hash_string.clear();
						}
						item.vec = vec;
						vec_id++;
						item.id = vec_id;
						cout << hash_value << endl;
						actualHashValue= (stol(hash_value) % M) %_hashTableSize;
						hash_value.clear();
						cout << "Actual hashvalue " << actualHashValue << endl;
						_arrayOfHashTables[i_l]->insertItem(item,actualHashValue);
						//clear vec and hash_value string
						vec.clear();
						
						i_vec=0;
					}
				
				}
				
	
			}
			if(inputFile.bad()){
				perror("error");
			}
			
		

		}
	}
	else if(metric == cosine){
		//do stuff
	}
}


void LSH::insertLSH(item_t item,unsigned int hashValue, int l)
{
	
}

void initParameters(int* k, int* L, std::string &input_file, std::string & output_file, std::string & query_file,int argc, char** argv)
{
	int i;
	int k_flag = 0, L_flag = 1, input_flag = 1, output_flag = 1, query_flag = 1;
	for(i = 1; i<argc; i++){
		if(strcmp(argv[i], "-o") == 0){
			i++;
			output_file = argv[i];
			output_flag = 1;
		}
		else if(strcmp(argv[i],"-q") == 0){
			i++;
			query_file = argv[i];
			query_flag = 1;
		}
		else if(strcmp(argv[i],"-d") == 0){
			i++;
			input_file = argv[i];
			input_flag = 1;
		}
		else if(strcmp(argv[i],"-k") == 0){
			i++;
			*k=stoi(argv[i]);
			k_flag = 1;
		}
		else if(strcmp(argv[i],"-L") == 0){
			i++;
			*L=stoi(argv[i]);
			L_flag = 1;
		}
	}
}


