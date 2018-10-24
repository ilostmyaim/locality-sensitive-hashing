#pragma once

#include<string>
#include<vector>


class Hash;
typedef struct item item_t;
typedef std::vector<double> vector_t;

enum Metric { euclidean , cosine } ;


#define M 60000
const int w = 4;
class LSH {

private:

	int _k; //number of locality-sensitive functions hi
	int _L; //number of hash tables
	std::string _inputFile;
	std::string _outputFile;
	std::string _queryFile;
	Hash **_arrayOfHashTables; //L-Hash objects
	int _hashTableSize;



public:

	LSH(int k=4, int L=5, std::string inputFile = "input_file", std::string outputFile="output_file", std::string queryFile="query_file", Metric metric = euclidean); //constructor
	int get_k();
	int get_L();
	std::string get_inputFile();
	std::string get_outputFile();
	void executeLSH(Metric);
	void displayLSH();
	//void insertLSH(item_t item,unsigned int hashValue, int l);
	void rangeSearch(vector_t q,double R, double C, Metric metric);
	void nearestNeighbor(vector_t, Metric metric);

};

/*parse command line parameters*/
void initParameters(int* k, int* L, std::string & input_file, std::string & output_file, std::string & query_file,int argc, char** argv);





