#include <xlw/MyContainers.h>


#ifdef USE_PARENTHESESES

double xlw::Element(const MyMatrix& A, unsigned long i , unsigned long j)
{
    return A(i,j);
}

double& xlw::ChangingElement(MyMatrix& A, unsigned long i , unsigned long j)
{
    return A(i,j);
}
#else

double xlw::Element(const MyMatrix& A, unsigned long i , unsigned long j)
{
    return A[i][j];
}

double& xlw::ChangingElement(MyMatrix& A, unsigned long i , unsigned long j)
{
    return A[i][j];
}
#endif
