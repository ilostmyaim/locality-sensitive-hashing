#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <math.h>
#include <random>
#include <list>
#include <ctime>
#include "hash.h"
#include "LSH.h"

using namespace std;

using std::default_random_engine;

int seed = time(0);
default_random_engine generator(seed);

Hash::Hash(int b)
{
	this->_tableSize = b;
	_hashTable = new list<item_t>[_tableSize];
}

void Hash::insertItem(item_t item,unsigned int hashValue)
{
	_hashTable[hashValue].push_back(item);
}

/*range search*/
void Hash::traverseBucket(vector_t q, unsigned int hashValue,int R, int C=1)
{
	double distance = 0;
	cout << "Range Search in Bucket["<<hashValue<<"]"<<endl;
	for(auto x: _hashTable[hashValue]){
		/*calculate Eucledian deistance*/
		distance = Euclidean_norm(q,x.vec);
		if( distance < C*R && distance > (C*R)-50){
			cout << "distance: " << distance << endl;
			print_vector(x.vec);
		}	
	}
}
/*Nearest Neighbor serach*/
void Hash::nearestNeighborTraverse(vector_t q, unsigned int hashValue)
{
	double distance = 0;
	double min_distance = 1000000;
	vector_t nearest_vec;
	cout << "NN-Search in Bucket["<<hashValue<<"]"<<endl;
	for(auto x: _hashTable[hashValue]){
		/*calculate Eucledian deistance*/
		distance = Euclidean_norm(q,x.vec);
		if( distance <= min_distance){
			min_distance = distance;
			nearest_vec = x.vec;
		}	
	}
	print_vector(nearest_vec);
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


double Euclidean_norm(vector_t u, vector_t v)
{
	int i;
	int sum = 0;
	for(i = 0; i < (int)v.size(); i++){
		sum = sum + pow(u[i]-v[i],2);
	}
	//cout << "sqrt(sum) = " << sqrt(sum) << endl;
	return sqrt(sum);
}

double inner_product(vector_t u, vector_t v)
{
	int i;
	double sum = 0;
	
	for(i=0; i < (int)v.size(); i++ ){
		sum = sum + u[i]*v[i];
	}

	return sum;
}



L2_Hash::L2_Hash(int w)
{
	normal_distribution<double> distribution(0.0, 1.0);

	
	int i;
	double num = 0;
	for(i=0; i< DIMENSION; i++){
		num = abs(distribution(generator));
		_v.push_back(num);
	}

	
	uniform_int_distribution<int> distribution_2(0,_w);
	_t = distribution_2(generator);
	_w = w;
}

int L2_Hash::hash(vector_t p)
{
	int value = 0;
	value = (int)((inner_product(p, this->_v) + _t) / _w);
	//cout << "hi : " << value << endl;
	return value;
}


void L2_Hash::random_vector()
{
	normal_distribution<double> distribution(0.0, 1.0);

	vector_t vec_1;
	int i;
	double num = 0;
	for(i=0; i< DIMENSION; i++){
		num = abs(distribution(generator));
		vec_1.push_back(num);
	}
	this->_v.clear();
	//print_vector(vec);
	this->_v = vec_1;
	vec_1.clear();
}

double L2_Hash::random_offset()
{
	uniform_int_distribution<int> distribution(0,_w);
	this->_t = distribution(generator);
	//cout << "T = " << this->_t << endl;
}

void print_vector(vector_t v)
{
	cout << "vector: ";
	for(int i = 0;i<v.size();i++){
		cout << v[i] << " ";
	}
	cout << endl;
}
//string L2_Hash_Family::combine()
