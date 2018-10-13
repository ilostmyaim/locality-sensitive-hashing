#pragma once

#define DIMENSION 128

template <class T>
class GenericVector {
	T * pData;
	int nSize;
  public:
	GenericVector();
    GenericVector(int);
    ~GenericVector();
    T& operator [] (int i) {return pData[i];}
};





