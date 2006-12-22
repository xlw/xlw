#include <xlw/MyContainers.h>


#ifdef USE_PARENTHESESES

double Element(const MJMatrix& A, unsigned long i , unsigned long j)
{
	return A(i,j);
}

double& ChangingElement(MJMatrix& A, unsigned long i , unsigned long j)
{
	return A(i,j);
}
#else

double Element(const MJMatrix& A, unsigned long i , unsigned long j)
{
	return A[i][j];
}

double& ChangingElement(MJMatrix& A, unsigned long i , unsigned long j)
{
	return A[i][j];
}
#endif
