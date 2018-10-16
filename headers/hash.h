#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>


const int DIMENSION(128);
typedef std::vector<double> vector_t;


class Hash {
private:

	//static const int tableSize = N/4;
	struct item {
		vector_t _vec;
		item* _next;
	};

	item** _HashTable;
	int _hashTableSize; //hashTableSize = 2^k

public:
	//constructor
	Hash();
	//


};


double  Euclidean_norm(vector_t u, vector_t v);
double inner_product(vector_t u, vector_t v);


class L2_Hash{
private:
	vector_t _v; //random projection vector
	int _t; //offset
	int _w; //default value is 4
public:
	L2_Hash(vector_t v, int t, int w);
	int hash(vector_t p);

};

class L2_Hash_Family{

private:
	int _w;
	int _d; //dimension of vector
public:
	L2_Hash_Family(int w, int d);
	L2_Hash create_hash_function();
	vector_t random_vector();
	double random_offset();
	std::string combine();
};
