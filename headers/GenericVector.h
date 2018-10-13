#pragma once

const int DIMENSION = 128;

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

template <class T>
GenericVector<T>::GenericVector(int n)
{
    pData = new T[n];
    nSize = n;
};

/*destructor*/
template <class T>
GenericVector<T>::~GenericVector()
{
	delete [] pData;
}





