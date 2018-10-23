#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <list>

enum Metric;

const int DIMENSION(128);

const int neighbours = 2;

typedef std::vector<double> vector_t;

typedef struct item{
	vector_t vec;
	unsigned int id;
} item_t;

class Hash {
private:
	int _tableSize;
	int _w; //default value is 4
	vector_t vec_t; //keep offset t here
	std::vector<vector_t > vec_v; //keep random vectors here(v for euclidean , ri for cosine)
	std::list<item_t> *_hashTable;
	
public:
	//constructor
	Hash(int b, int );
	void insertItem(item_t item,unsigned int hashValue);
	void displayHash();
	int getTableSize();
	void traverseBucket(vector_t, long int, int,int ,Metric metric);
	void nearestNeighborTraverse(vector_t q, long int hashValue, int L ,Metric metric);

	long int hash(vector_t p);
	long int cosineHash(vector_t p);
	vector_t random_vector();
	double random_offset();
	std::string combine();

};


double  euclideanNorm(vector_t u, vector_t v);
double cosineSimilarity(vector_t x, vector_t y);
double innerProduct(vector_t u, vector_t v);
void print_vector(vector_t v);


