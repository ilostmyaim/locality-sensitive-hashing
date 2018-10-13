#include "../headers/GenericVector.h"


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

