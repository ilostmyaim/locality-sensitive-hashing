#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include "GenericVector.h"





class Hash {
private:

	//static const int tableSize = N/4;
	struct item {
		GenericVector <int> vec;
		item* next;
	};

	item** HashTable;
	int hashTableSize; //hashTableSize = 2^k

public:
	//constructor
	Hash();
	//


};

