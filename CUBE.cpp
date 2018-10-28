#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include <fstream>
#include <sstream>
#include<math.h>
#include <algorithm>
#include <chrono>
#include "CUBE.h"
#include "hash.h"
#include "LSH.h"



using namespace std;
using namespace std::chrono;


CUBE::CUBE(int k, int m, int probes, string inputFile, string outputFile, string queryFile,Metric metric)
{
	_k = k;
	_MC = m;
	_probes = probes;
	_inputFile = inputFile;
	_queryFile = queryFile;
	_outputFile = outputFile;
	
	/*read number of vectors from input file*/
	ifstream inFile(_inputFile);
	int count = 0;
	string line;
	if(metric == euclidean) {
		if(inFile.is_open()) {
			while(getline(inFile, line))
				++count;
		}
		cout << "Number of lines read is: " << count << endl;
		_hashTableSize = log2(count);

	}
	else if(metric == cosine){ 
		_hashTableSize = pow(2,_k);
	}



	_hashTable = new Hash(_hashTableSize,_k);

}


int CUBE::get_k()
{
	return this->_k;
}

int CUBE::get_M()
{
	return this->_MC;
}

int CUBE::get_probes()
{
	return this->_probes;
}

string CUBE::get_inputFile()
{
	return this->_inputFile;
}

string CUBE::get_outputFile()
{
	return this->_outputFile;
}

int CUBE::executeCUBE(Metric metric)
{
	int i_vec=0; //counter for L and k respectively
	double R=0;
	string tmp; //for query file
	string line;
	int C=1;
	double pValue=0,qValue=0; //read values from input file and query file here
	vector_t vec; //store p_values to vec while reading
	ifstream inputFile(_inputFile);// input file stream
	ifstream queryFile(_queryFile);
	ofstream outputFile(_outputFile);
	//streambuf *coutbuf = cout.rdbuf();
	//cout.rdbuf(outputFile.rdbuf());
	string hash_string;
	long int hash_value;
	long double actualHashValue=0; 
	static unsigned int vec_id = 0; // id for each vector readen
	static unsigned int q_id = 0;
	item_t item;

	if (inputFile.is_open()) {
		/*start reading points*/
		while(getline(inputFile, line)) {
			stringstream stream(line);
			while(1){
				stream >> pValue;
				if(!stream)
					break;
				vec.push_back(pValue);
			}
			
			
			item.vec = vec;
			vec_id++;
			item.id = vec_id;
			//cout << "VEC_ID = " << vec_id << endl;
			if(metric == euclidean) {
				hash_value = _hashTable->hashCUBE(vec);
				actualHashValue = ((hash_value % M) + M) % _hashTableSize;
				//print_vector(vec);
			}
			else{
				hash_value = _hashTable->cosineHash(vec);
				actualHashValue = hash_value;
			}
			_hashTable->insertItem(item, actualHashValue);
			vec.clear();
		}

		//reinitialize vec_id to zero
		vec_id = 0;
		inputFile.clear();
		inputFile.seekg(0,ios::beg);
		if(inputFile.bad()){
			perror("error");
		}		

	}

	
	/*first read R from query file */
	if(queryFile.is_open()){ 
		cout.precision(9);
		vec.clear();
		getline(queryFile, line);
		stringstream stream(line);
		stream >> tmp >> R;
		cout << "Radius is: " << R << endl;
		if(R == 0){ // find nearest neighbor
			/*********** Nearest neighbor*********/
			auto start = high_resolution_clock::now();
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
				cout << "Nearest neighbor method" << endl;
				q_id++;
				nearestNeighbor(vec,metric);
				vec.clear();
				
			}
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<seconds>(stop-start);
			cout << "Time = " << duration.count() << "seconds" << endl;
		}
		else {
			/*********Range Search***********/
			auto start = high_resolution_clock::now();
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
				cout << "R-near neighbors method "<< endl;
				//print_vector(vec);
				q_id++;
				rangeSearch(vec,R,C,metric);
				vec.clear();
			}
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<seconds>(stop-start);
			cout << "Time = " << duration.count() << "seconds" << endl;
		}
	}
		

	//cout.rdbuf(coutbuf);
	cout << "finished" << endl;

}

void CUBE::displayCUBE()
{

	cout << "display CUBE" << endl;
	_hashTable->displayHash();

}

void CUBE::rangeSearch(vector_t q, double R, double C=1, Metric metric = euclidean)
{
	int i_l;
	string hash_string;
	long int hash_value;
	long double actualHashValue=0;
	long int tmp_hash;
	int tmp_probes;
	tmp_probes = this->_probes; 
	if(metric == euclidean){ 
		hash_value = _hashTable->hashCUBE(q);
		actualHashValue = ((hash_value % M) + M) % _hashTableSize;
		_hashTable->traverseBucket(q, actualHashValue, R, C , metric);
		
		tmp_probes--;
		tmp_hash = actualHashValue - 1;
		while(tmp_probes > 0){ //start checking left neighbor buckets
			if(tmp_hash >= 0){
				_hashTable->traverseBucket(q,tmp_hash, R,C,metric);
				tmp_probes--;
				tmp_hash--;
			}
			else{
				break;
			}
		}
		tmp_hash = actualHashValue + 1;
		while(tmp_probes > 0){ //start checking righ neighbor buckets
			if(tmp_hash < this->_hashTableSize){
				_hashTable->traverseBucket(q,tmp_hash, R,C,metric);
				tmp_probes--;
				tmp_hash++;
			}
			else{
				break;
			}
		}
	}
	else{
		hash_value = _hashTable->cosineHash(q);
		actualHashValue = hash_value;
		_hashTable->traverseBucket(q, actualHashValue, R, C , metric);
		tmp_probes--;
		tmp_hash = actualHashValue - 1;
		while(tmp_probes > 0){ //start checking left neighbor buckets
			if(tmp_hash >= 0){
				_hashTable->traverseBucket(q, actualHashValue, R, C , metric);
				tmp_probes--;
				tmp_hash--;
			}
			else{
				break;
			}
		}
		tmp_hash = actualHashValue + 1;
		while(tmp_probes > 0){ //start checking righ neighbor buckets
			if(tmp_hash < this->_hashTableSize){
				_hashTable->traverseBucket(q, actualHashValue, R, C , metric);
				tmp_probes--;
				tmp_hash++;
			}
			else{
				break;
			}
		}
	}
}


void CUBE::nearestNeighbor(vector_t q,Metric metric)
{
	int i_l;
	string hash_string;
	long int hash_value;
	long double actualHashValue=0; 
	long int tmp_hash;
	int tmp_probes = this->_probes;
	if(metric == euclidean){ 
	
		hash_value = _hashTable->hashCUBE(q);
		actualHashValue = ((hash_value % M) + M) % _hashTableSize;
		_hashTable->nearestNeighborTraverse(q, actualHashValue, this->_MC/3,metric);
		tmp_probes--;
		tmp_hash = actualHashValue - 1;
		while(tmp_probes > 0){ //start checking left neighbor buckets
			if(tmp_hash >= 0){
				_hashTable->nearestNeighborTraverse(q,tmp_hash, this->_MC/3,metric);
				tmp_probes--;
				tmp_hash--;
			}
			else{
				break;
			}
		}
		tmp_hash = actualHashValue + 1;
		while(tmp_probes > 0){ //start checking righ neighbor buckets
			if(tmp_hash < this->_hashTableSize){
				_hashTable->nearestNeighborTraverse(q,tmp_hash, this->_MC/3,metric);
				tmp_probes--;
				tmp_hash++;
			}
			else{
				break;
			}
		}

	
	}
	else{
		hash_value = _hashTable->cosineHash(q);
		actualHashValue = hash_value;
		_hashTable->nearestNeighborTraverse(q, actualHashValue, this->_MC/3,metric);

		tmp_probes--;
		tmp_hash = actualHashValue - 1;
		while(tmp_probes > 0){ //start checking left neighbor buckets
			if(tmp_hash >= 0){
				_hashTable->nearestNeighborTraverse(q,tmp_hash, this->_MC/3,metric);
				tmp_probes--;
				tmp_hash--;
			}
			else{
				break;
			}
		}
		tmp_hash = actualHashValue + 1;
		while(tmp_probes > 0){ //start checking righ neighbor buckets
			if(tmp_hash < this->_hashTableSize){
				_hashTable->nearestNeighborTraverse(q,tmp_hash, this->_MC/3,metric);
				tmp_probes--;
				tmp_hash++;
			}
			else{
				break;
			}
		}
	}
}




void initParametersCube(int* k, int* m, int* probes, std::string &input_file, std::string & output_file, std::string & query_file,string &met,int argc, char** argv)
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
		else if(strcmp(argv[i],"-metric") == 0){
			i++;
			met = argv[i];
		}
		else if(strcmp(argv[i],"-probes") == 0){
			i++;
			*probes=stoi(argv[i]);
		}
	}
		
}