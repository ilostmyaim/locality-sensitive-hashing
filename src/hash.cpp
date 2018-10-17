#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <math.h>
#include <random>
#include "../headers/hash.h"

using namespace std;

Hash::Hash()
{

}


double Euclidean_norm(vector_t u, vector_t v)
{
	int i;
	int sum = 0;
	for(i = 0; i < (int)v.size(); i++){
		sum = sum + pow(u[i]-v[i],2);
	}
	return sqrt(sum);
}

double inner_product(vector_t u, vector_t v)
{
	int i;
	int sum = 0;
	for(i=0; i < (int)v.size(); i++ ){
		sum = sum + u[i]*v[i];
	}

	return sum;
}


L2_Hash::L2_Hash(vector_t v, int t, int w)
{
	_v = v;
	_t = t;
	_w = w;
}

int L2_Hash::hash(vector_t p)
{
	return int((inner_product(p, _v) + _t) / _w);
}

L2_Hash_Family::L2_Hash_Family(int w, int d)
{
	_w = w;
	_d = d;
}

L2_Hash L2_Hash_Family::create_hash_function()
{
	L2_Hash L2_HashObj(random_vector(),random_offset(), _w);
	return L2_HashObj;
}

vector_t L2_Hash_Family::random_vector()
{
	default_random_engine generator;
	normal_distribution<double> distribution(0.0, 1.0);

	vector_t vec;
	int i;
	double num = 0;
	for(i=0; i< DIMENSION; i++){
		num = distribution(generator);
		vec.push_back(num);
	}

	return vec;
}

double L2_Hash_Family::random_offset()
{
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0,_w);

	return distribution(generator);
}


