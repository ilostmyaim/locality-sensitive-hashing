#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include "../headers/LSH.h"
#include "../headers/GenericVector.h"


using namespace std;


LSH::LSH(int k, int L, string inputFile, string outputFile)
{
	_k = k;
	_L = L;
	_inputFile = inputFile;
	_outputFile = outputFile;
	_arrayOfHashTables = new Hash*[L]; //create array of pointers to hashtables


}

void LSH::LSH_resize(int L)
{


}
