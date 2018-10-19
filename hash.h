#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <list>


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
	std::list<item_t> *_hashTable;
	
public:
	//constructor
	Hash(int V);
	void insertItem(item_t item,unsigned int hashValue);
	void displayHash();
	int getTableSize();
	void traverseBucket(vector_t, unsigned int, int,int  );

};


double  Euclidean_norm(vector_t u, vector_t v);
double inner_product(vector_t u, vector_t v);
void print_vector(vector_t v);


class L2_Hash{
private:
	vector_t _v;
	int _t; //offset
	int _w; //default value is 4
public:
	L2_Hash(int w);
	int hash(vector_t p);
	void random_vector();
	double random_offset();
	std::string combine();

};
