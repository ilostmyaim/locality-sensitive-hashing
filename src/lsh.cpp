#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include "../headers/LSH.h"
#include "../headers/hash.h"


using namespace std;

int main(int argc, char **argv) {
	vector_t vec;
	string line;
	ifstream inputFile("src/input_small", ios::in);

	int k,L;
	string input_file, output_file, query_file;

	/*initialize parameters*/
	initParameters(&k, &L, input_file, output_file, query_file, argc, argv);

	/*create an LSH object*/
	LSH lshObject(k, L, input_file, output_file, query_file);

	int w = 4;
	vector<int> p;
	int i = 1;
	p.reserve(4);
	p.push_back(i);
	p.push_back(i);
	p.push_back(i);
	p.push_back(i);

	vector<int> v;
	v.reserve(4);
	v.push_back(1);
	v.push_back(0);
	v.push_back(0);
	v.push_back(1);

	int j = 0;
	int sum = 0;
	for(;j < (int)v.size(); j++){
		sum = sum + v[j]*p[j];
	}

	int h = (sum+3)/w;
	cout << "H is: " << h << endl;


	int value;
	i=0;
	if (inputFile) {
		while( inputFile >> value) {
			printf("%d ", value);
			if (i < DIMENSION - 1){
				vec.push_back(i);
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
