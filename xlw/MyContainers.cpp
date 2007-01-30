#include <xlw/MyContainers.h>


#ifdef USE_PARENTHESESES

double Element(const MyMatrix& A, unsigned long i , unsigned long j)
{
	return A(i,j);
}

double& ChangingElement(MyMatrix& A, unsigned long i , unsigned long j)
{
	return A(i,j);
}
#else

double Element(const MyMatrix& A, unsigned long i , unsigned long j)
{
	return A[i][j];
}

double& ChangingElement(MyMatrix& A, unsigned long i , unsigned long j)
{
	return A[i][j];
}
#endif
