#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include "../headers/GenericVector.h"
#include "../headers/LSH.h"


using namespace std;

int main(int argc, char **argv) {
	GenericVector <int> vec(DIMENSION);
	string line;
	ifstream inputFile("src/input_small", ios::in);

	int k,L;
	string input_file, output_file, query_file;

	initParameters(&k, &L, input_file, output_file, query_file, argc, argv);
	cout << k << endl;
	cout << L << endl;
	cout << output_file << endl;


	int value;
	int i=0;
	if (inputFile) {
		while( inputFile >> value) {
			printf("%d ", value);
			if (i < DIMENSION - 1){
				vec[i] = value;
				i++;
			}
			else{
				cout << value << "vklj" << endl;
				i=0;
				break;
			}
		}
	}
	else{
		cout << "couldnt open file" << endl;
	}

	return 0;

}
