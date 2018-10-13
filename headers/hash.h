#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <../headers/GenericVector.h>

class Hash {
private:

	static const int tableSize = N/4;
	struct item {
		GenericVector <int> vec(DIMENSION);
		item* next;
	};

	item* HashTable[tableSize];

public:
	//constructor
	Hash();
	//


};
