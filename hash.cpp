#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <math.h>
#include <random>
#include <list>
#include <ctime>
#include <chrono>
#include <iomanip>
#include "LSH.h"
#include "hash.h"


using namespace std;
using namespace std::chrono;

using std::default_random_engine;

int seed = time(0);
default_random_engine generator(seed);

Hash::Hash(int b,int k)
{
	this->_tableSize = b;
	//cout << "Hashtable size is: " << _tableSize << endl;
	this->_w = 200; 
	for(int i = 0;i<k;i++){
		this->vec_t.push_back(random_offset());
		this->vec_v.push_back(random_vector());
	}

	_hashTable = new list<item_t>[_tableSize];

}

void Hash::insertItem(item_t item,unsigned int hashValue)
{
	_hashTable[hashValue].push_back(item);
}

/*range search*/
void Hash::traverseBucket(vector_t q, long int hashValue,double R, double C=1,Metric metric=euclidean)
{
	double distance = 0;
	//cout << "Range Search in Bucket["<<hashValue<<"]"<<endl;
	for(auto x: _hashTable[hashValue]){
		/*calculate Eucledian deistance*/
		if(metric == euclidean) { 
			distance = euclideanNorm(q,x.vec);
			if( distance < C*R){
				cout << "Item: "<< x.id << " " << distance << endl;
				//cout << "distance: " << distance << endl;
				//print_vector(x.vec);
			}
		}
		else if(metric == cosine) {
			distance = 1 -cosineSimilarity(q,x.vec);
			if( distance < C*R){ 
				cout << "Item: "<< x.id << " " << distance << endl;
				//cout << "cosine distance: " << distance << endl;
				//print_vector(x.vec);
			}
		}	
	}
}
/*Nearest Neighbor serach*/
void Hash::nearestNeighborTraverse(vector_t q, long int hashValue, int L, Metric metric)
{
	double distance = 0;
	double min_distance = 1000000;
	int count_retrieved = 0;
	int nearest_id = 0;
	vector_t nearest_vec;
	int approximateNN_flag = 0;
	auto start_appNN = high_resolution_clock::now();
	auto start_NN = high_resolution_clock::now();
	cout.precision(9);
	//cout << "NN-Search in Bucket["<<hashValue<<"]"<<endl;
	for(auto x: _hashTable[hashValue]){
		/*calculate Eucledian deistance*/
		if(metric == euclidean){ 
			distance = euclideanNorm(q,x.vec);
			count_retrieved++;
			if(count_retrieved > 3*L && approximateNN_flag == 0){
				auto stop_appNN = high_resolution_clock::now();
				duration<double> duration_appNN = (stop_appNN - start_appNN);
				cout<< "*****************************************" << endl;
				cout << "Approximate NN: " << x.id << endl; 
				cout << "Distance: " << distance << endl;
				//printf("Approximate NN time: %.7fs\n" ,duration_appNN.count());
				cout << "Approximate NN time: " << duration_appNN.count() << std::fixed << endl;
				cout<< "*****************************************" << endl;
				//cout << "Approximate NN time: " << (duration_appNN).count() << endl;
				//print_vector(x.vec);
				approximateNN_flag = 1;
			}
			if( distance <= min_distance){
				min_distance = distance;
				nearest_id = x.id;
				nearest_vec = x.vec;
			}
		}
		else if (metric == cosine){
			min_distance = 4;
			distance = 1 - cosineSimilarity(q, x.vec);
			count_retrieved++;
			if(count_retrieved > 3*L && approximateNN_flag == 0){
				auto stop_appNN = high_resolution_clock::now();
				duration<double> duration_appNN = (stop_appNN - start_appNN);
				cout<< "*****************************************" << endl;
				cout << "Approximate NN: " << x.id << endl; 
				cout << "Distance: " << distance << endl;
				//printf("Approximate NN time: %.7fs\n" ,duration_appNN.count());
				cout << "Approximate NN time: " << duration_appNN.count() << std::fixed<<endl;
				cout<< "*****************************************" << endl;
				//print_vector(x.vec);
				approximateNN_flag = 1;
			}
			if( distance <= min_distance){
				min_distance = distance;
				nearest_id = x.id;
				nearest_vec = x.vec;
			}
		}	
	}
	auto stop_NN = high_resolution_clock::now();
	/*calculate time for Nearest neighbor*/
	duration<double> duration_NN = (stop_NN - start_NN);
	cout << "Nearest neighbor: " << nearest_id << endl;
	cout << "distanceTrue: " << min_distance << endl;
	//printf("tLSH: %.7fs\n" ,duration_NN.count());
	cout << "tLSH: " << duration_NN.count() << std::fixed << endl;
}

void Hash::displayHash()
{
	for(int i = 0;i<this->_tableSize;i++){
		cout << "Bucket["<<i<<"]"<<endl;
		for(auto x: _hashTable[i]){
			cout << " --> " << x.id;
		}
		cout << endl;
	}
}

int Hash::getTableSize()
{
	return this->_tableSize;
}


double euclideanNorm(vector_t u, vector_t v)
{
	int i;
	int sum = 0;
	for(i = 0; i < (int)v.size(); i++){
		sum = sum + pow(u[i]-v[i],2);
	}
	//cout << "sqrt(sum) = " << sqrt(sum) << endl;
	return sqrt(sum);
}

double cosineSimilarity(vector_t x, vector_t y)
{
	double dot = 0, denom_x = 0, denom_y = 0;
	dot = innerProduct(x, y);
	denom_x = innerProduct(x, x);
	denom_y = innerProduct(y, y);

	return ( dot / (sqrt(denom_x) * sqrt(denom_y)) );

}

double innerProduct(vector_t u, vector_t v)
{
	int i;
	double sum = 0;
	
	for(i=0; i < (int)v.size(); i++ ){
		sum = sum + u[i]*v[i];
	}

	return sum;
}




long int Hash::hash(vector_t p)
{
	long int value = 0;
	long int sum = 0;
	uniform_int_distribution<int> distribution(0,200);//initialize for R value
	for(int i=0;i<(int)this->vec_v.size();i++){ 
		value = ((innerProduct(p, this->vec_v[i]) + vec_t[i]) / _w);
		//sum of hi functions to create f
		sum+= (distribution(generator) * value);
	}
	//cout << "Sum is: " << sum << endl;
	return sum;
}

long int Hash::cosineHash(vector_t p)
{
	long int value = 0;
	string hi;
	long int hash_value = 0;
	for(int i = 0; i<(int)this->vec_v.size();i++){
		value = ((innerProduct(p, this->vec_v[i])));
		if(value >= 0){
			hi.append("1");
		}
		else{
			hi.append("0");
		}
	}
	//cout << "hi: " << hi << endl;
	hash_value = stol(hi, nullptr, 2);
	
	return hash_value ;

}

long int Hash::hashCUBE(vector_t p)
{
	long int value = 0;
	long int sum = 0;
	string hi;
	int one_zero = 0;
	int found = 0;
	uniform_int_distribution<int> distribution(0,200);//initialize for ri value
	uniform_int_distribution<int> CUBEdistribution(0,1);
	for(int i=0;i<(int)this->vec_v.size();i++){
		found = 0;
		value = ((innerProduct(p, this->vec_v[i]) + vec_t[i]) / _w);
		for(int j=0;j<this->value_vec.size();j++){
			if(value == this->value_vec[j]){ //if value already exists in value_vec
				//proceed and append the appropriate one or zero to hi string
				found = 1;
				one_zero = this->one_zero_vec[j];
				if(one_zero == 0){
					hi.append("0");
				}
				else{
					hi.append("1");
				}
				break;// exit search in value_vec
			}
		}	
		if(found == 0){// if value doesn't exist in value_vec,then add value to value_vec
			this->value_vec.push_back(value);
			one_zero = CUBEdistribution(generator); //coin tosh
			this->one_zero_vec.push_back(one_zero);//add one_zero to one_zero_vec
			if(one_zero == 0){
				hi.append("0");
			}
			else{
				hi.append("1");
			}
		}
		//sum of hi functions to create f
		//sum+= (distribution(generator) * value);
	}
	value = stol(hi, nullptr, 2);

	return value;

}

vector_t Hash::random_vector()
{
	normal_distribution<double> distribution(0.0, 1.0);

	vector_t vec_1;
	int i;
	double num = 0;
	for(i=0; i< DIMENSION; i++){
		num = distribution(generator);
		vec_1.push_back(num);
	}
	
	return vec_1;
}

double Hash::random_offset()
{
	uniform_int_distribution<int> distribution(0,_w);
	double t;
	t = distribution(generator);
	return t;
	//cout << "T = " << this->_t << endl;
}

void print_vector(vector_t v)
{
	cout << "vector: ";
	for(int i = 0;i<(int)v.size();i++){
		cout << v[i] << " ";
	}
	cout << endl;
}
//string L2_Hash_Family::combine()
