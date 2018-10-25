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

LSH::LSH(int k, int L, string inputFile, string outputFile, string queryFile,Metric metric)
{
	/*initialize parameters*/
	_k = k;
	_L = L;
	_inputFile = inputFile;
	_outputFile = outputFile;
	_queryFile = queryFile;
	_arrayOfHashTables = new Hash*[_L]; //create array of pointers to hashtables
	ifstream inFile(_inputFile);
	int count = 0;
	string line;
	if(metric == euclidean) {
		if(inFile.is_open()) {
			while(getline(inFile, line))
				++count;
		}
		cout << "Number of lines read is: " << count << endl;
		_hashTableSize = count / 16;

	}
	else if(metric == cosine){ 
		_hashTableSize = pow(2,_k);
	}
	for(int i = 0;i<_L;i++){ 
		_arrayOfHashTables[i] = new Hash(_hashTableSize,_k);	
	}
}

void LSH::executeLSH(Metric metric)
{
	//do stuff
	int i_l,i_vec=0; //counter for L and k respectively
	double R=0;
	string tmp; //for query file
	string line;
	int C=1;
	double pValue=0,qValue=0; //read values from input file and query file here
	vector_t vec; //store p_values to vec while reading
	ifstream inputFile(_inputFile);// input file stream
	ifstream queryFile(_queryFile);
	string hash_string;
	long int hash_value;
	long double actualHashValue=0; 
	static unsigned int vec_id = 0; // id for each vector readen
	static unsigned int q_id = 0;
	item_t item;
	
		for(i_l=0;i_l<_L;i_l++){
			/*start reading points*/
			//
			if (inputFile.is_open()) {
				while(getline(inputFile, line)) {
					stringstream stream(line);
					while(1){
						stream >> pValue;
						if(!stream)
							break;
						vec.push_back(pValue);
					}
					//create hi hash functions and concatenate to create g
					item.vec = vec;
					vec_id++;
					item.id = vec_id;
					//cout << "VEC_ID = " << vec_id << endl;
					print_vector(vec); 
					if(metric == euclidean){
						hash_value = _arrayOfHashTables[i_l]->hash(vec);
						actualHashValue = ((hash_value % M) + M) % _hashTableSize;
					}
					else{
						hash_value = _arrayOfHashTables[i_l]->cosineHash(vec);
						actualHashValue = hash_value;
					}
					
					//cout << "Actual hashvalue " << actualHashValue << endl;
					_arrayOfHashTables[i_l]->insertItem(item,actualHashValue);
					//clear vec and hash_value string
					vec.clear();
					//vec.push_back(pValue);
					
				
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
		if(queryFile.is_open()){ 
		vec.clear();
		getline(queryFile, line);
		stringstream stream(line);
		stream >> tmp >> R;
		cout << "Radius is: " << R << endl;
		if(R == 0){ // find nearest neighbor
			/*********** Nearest neighbor*********/
			cout << "Nearest Neighbor" << endl;
			while(getline(queryFile, line)) {
				stringstream stream(line);
				while(1){
					stream >> pValue;
					if(!stream)
						break;
					vec.push_back(pValue);
				}
				
				cout << endl;
				cout << "Query: " << q_id << endl;
				q_id++;
				nearestNeighbor(vec,metric);
				vec.clear();
				
			}
		}
		else {
			cout << "Range Search"<< endl;
			/*********Range Search***********/
			while(getline(queryFile, line)) {
				stringstream stream(line);
				while(1){
					stream >> pValue;
					if(!stream)
						break;
					vec.push_back(pValue);
				}
				
				cout << endl;
				cout << "Query: " << q_id << endl;
				print_vector(vec);
				q_id++;
				rangeSearch(vec,R,C,metric);
				vec.clear();
			}
		}
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


void LSH::rangeSearch(vector_t q, double R, double C=1, Metric metric = euclidean)
{
	int i_l;
	string hash_string;
	long int hash_value;
	long double actualHashValue=0; 
	if(metric == euclidean){ 
		for(i_l = 0; i_l < _L; i_l++){
			
	
			hash_value = _arrayOfHashTables[i_l]->hash(q);
			//cout << "hash_value = " << hash_value << endl;
			actualHashValue = ((hash_value % M) + M) % _hashTableSize;
			//cout << "actualHashValue = " << actualHashValue << endl;
			//cout << "Inside range search "<< endl;
			//cout << "ActualHashValue: " << actualHashValue << endl;
			//cout << "Hashtable["<<i_l<<"]" << endl;
			_arrayOfHashTables[i_l]->traverseBucket(q, actualHashValue, R, C , metric);
		}
	}
	else{
		for(i_l = 0; i_l < _L; i_l++){
	
			hash_value = _arrayOfHashTables[i_l]->cosineHash(q);
			//cout << "hash_value = " << hash_value << endl;
			actualHashValue = hash_value;
			//cout << "actualHashValue = " << actualHashValue << endl;
			//cout << "Inside range search "<< endl;
			//cout << "ActualHashValue: " << actualHashValue << endl;
			//cout << "Hashtable["<<i_l<<"]" << endl;
			_arrayOfHashTables[i_l]->traverseBucket(q, actualHashValue, R, C , metric);
		}
	}
}

void LSH::nearestNeighbor(vector_t q,Metric metric)
{
	int i_l;
	string hash_string;
	long int hash_value;
	long double actualHashValue=0; 
	if(metric == euclidean){ 
		for(i_l = 0; i_l < _L; i_l++){
			hash_value = _arrayOfHashTables[i_l]->hash(q);
			actualHashValue = ((hash_value % M) + M) % _hashTableSize;
			//cout << "Inside range search "<< endl;
			//cout << "ActualHashValue: " << actualHashValue << endl;
			//cout << "Hashtable["<<i_l<<"]" << endl;
			_arrayOfHashTables[i_l]->nearestNeighborTraverse(q, actualHashValue, this->_L,metric);
		}
	}
	else{
		for(i_l = 0; i_l < _L; i_l++){
			hash_value = _arrayOfHashTables[i_l]->cosineHash(q);
			actualHashValue = hash_value;
			//cout << "Inside range search "<< endl;
			//cout << "ActualHashValue: " << actualHashValue << endl;
			//cout << "Hashtable["<<i_l<<"]" << endl;
			_arrayOfHashTables[i_l]->nearestNeighborTraverse(q, actualHashValue, this->_L,metric);
		}

	}
}

void initParameters(int* k, int* L, std::string &input_file, std::string & output_file, std::string & query_file,int argc, char** argv)
{
	int i;
	//int k_flag = 0, L_flag = 1, input_flag = 1, output_flag = 1, query_flag = 1;
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
			*L=stoi(argv[i]);
			//L_flag = 1;
		}
	}
}


