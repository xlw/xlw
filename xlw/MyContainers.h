//
//
//															MyContainers.h
//
//
/*
	everyone has their favoured matrix and array class
	You should alter this file to typedef your favourite of each to MyMatrix and MyVector.

	For MJMatrix it is assumed that a constructor with MyMatrix(unsigned long, unsigned long) exists 
	and that an element can be accessed via thisMatrix[i][j]


*/
#ifndef MY_CONTAINERS_H
#define MY_CONTAINERS_H

#include "MJMatrices.h"
#include <vector>

typedef MJMatrix MyMatrix;
typedef std::vector<double> MyArray;

#endif
