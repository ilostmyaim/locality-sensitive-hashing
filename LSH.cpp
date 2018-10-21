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
		int i_l,j_k,i_vec=0,R; //counter for L and k respectively
		string tmp; //for query file
		string line;
		int C=1;
		double pValue=0,qValue=0; //read values from input file and query file here
		vector<double> vec; //store p_values to vec while reading
		ifstream inputFile(_inputFile);// input file stream
		ifstream queryFile(_queryFile);
		string hash_string;
		L2_Hash l2_hash(w);
		string hash_value;
		long double actualHashValue=0; 
		static unsigned int vec_id = 0; // id for each vector readen
		static unsigned int q_id = 0;
		item_t item;
		

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
							//cout << "Hash string : " << hash_string<< endl;
							hash_value.append(hash_string);
							l2_hash.random_vector();
							l2_hash.random_offset();
							hash_string.clear();
						}
						item.vec = vec;
						vec_id++;
						item.id = vec_id;
						//cout << "VEC_ID = " << vec_id << endl; 
						//cout << hash_value << endl;
						actualHashValue= (stol(hash_value) % M) %_hashTableSize;
						hash_value.clear();
						//cout << "Actual hashvalue " << actualHashValue << endl;
						_arrayOfHashTables[i_l]->insertItem(item,actualHashValue);
						//clear vec and hash_value string
						vec.clear();
						
						i_vec=0;
					}
				
				}
				
	
			}
			//reinitialize vec_id to zero
			vec_id = 0;
			//clear inputFile and start reading again from the beginning
			inputFile.clear();
			inputFile.seekg(0,ios::beg);
			if(inputFile.bad()){
				perror("error");
			}		
		

		}// after filling the hashtables start the query

	
		/*first read R from query file */
		if(queryFile.is_open()){ 
			i_vec = 0;
			vec.clear();
			queryFile >> tmp >> R;
			cout << "Radius is: " << R << endl;
			if(R == 0){ // find nearest neighbor
				/*********** Nearest neighbor*********/
				cout << "Nearest Neighbor" << endl;
				while(queryFile >> pValue) {
					if(i_vec < DIMENSION) {
						vec.push_back(qValue);
						i_vec++;
					}
					else{
						cout << endl;
						cout << "Query: " << q_id << endl;
						q_id++;
						nearestNeighbor(vec);
						vec.clear();
						i_vec=0;
					}
				}
			}
			else {
				cout << "Range Search"<< endl;
				/*********Range Search***********/
				while(queryFile >> pValue) {
					if(i_vec < DIMENSION){
						//cout << pValue << " ";
						vec.push_back(qValue);
						i_vec++;
					}
					else{
						cout << endl;
						//print_vector(vec);
						cout << "Query: " << q_id << endl;
						q_id++;
						rangeSearch(vec,R,C);
						vec.clear();
						i_vec=0;
					}
				}
			}
		}
		


		cout << "finished" << endl;
	}
	else if(metric == cosine){
		//do stuff
	}
}


void LSH::displayLSH()
{
	cout << "display lsh" << endl;
	for(int i = 0;i<this->_L;i++){
		
		cout << "Printing hashtable["<<i<<"]"<<endl;
		_arrayOfHashTables[i]->displayHash();

	}
}


void LSH::rangeSearch(vector_t q, int R, int C=1)
{
	int i_l,j_k;
	string hash_string;
	string hash_value;
	L2_Hash l2_hash(w);
	static unsigned int q_id = 0;
	long double actualHashValue=0; 
	for(i_l = 0; i_l < _L; i_l++){
		for(j_k=0;j_k < _k;j_k++){
			hash_string = to_string(l2_hash.hash(q));
			//cout << "Hash string : " << hash_string<< endl;
			hash_value.append(hash_string);
			l2_hash.random_vector();
			l2_hash.random_offset();
			hash_string.clear();
		}
		actualHashValue= (stol(hash_value) % M) %_hashTableSize;
		//cout << "Inside range search "<< endl;
		//cout << "ActualHashValue: " << actualHashValue << endl;
		cout << "Hashtable["<<i_l<<"]" << endl;
		_arrayOfHashTables[i_l]->traverseBucket(q, actualHashValue, R, C);

		hash_value.clear();
	}
}

void LSH::nearestNeighbor(vector_t q)
{
	int i_l,j_k;
	string hash_string;
	string hash_value;
	L2_Hash l2_hash(w);
	static unsigned int q_id = 0;
	long double actualHashValue=0; 
	for(i_l = 0; i_l < _L; i_l++){
		for(j_k=0;j_k < _k;j_k++){
			hash_string = to_string(l2_hash.hash(q));
			//cout << "Hash string : " << hash_string<< endl;
			hash_value.append(hash_string);
			l2_hash.random_vector();
			l2_hash.random_offset();
			hash_string.clear();
		}
		actualHashValue= (stol(hash_value) % M) %_hashTableSize;
		//cout << "Inside range search "<< endl;
		//cout << "ActualHashValue: " << actualHashValue << endl;
		cout << "Hashtable["<<i_l<<"]" << endl;
		_arrayOfHashTables[i_l]->nearestNeighborTraverse(q, actualHashValue, this->_L);

		hash_value.clear();
	}
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


