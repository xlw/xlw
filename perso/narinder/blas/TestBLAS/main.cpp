
#include<iostream>

#ifdef _ACML
#include "acml.h"
#else
#include "cblas.h"

extern "C" void dgemv_(char *TransA, 
					   int *M, 
					   int *N,
					   double *alpha,
			 		   double *A, 
				       int *lda,
                       double *X, 
				       int *incX, 
				       double *beta,
                       double *Y, 
				       int *incY);
#endif


int main() {
	try {

	char TransA[]="N";
	int M = 3;
	int N = 3;
	double alpha =1.0;
	double A[9];
	//int lda ;
    double X[3];
	int incX = 1; 
	double beta = 1.0;
    double Y[3]; 
	int incY = 1;

	for (int lda(3);lda>=2;lda--) {

			for (unsigned long i(0);i<3;i++) {
				X[i] = i;Y[i] = 1;
				for (unsigned long j(0);j<3;j++)A[i+j*3] = i + j ;
			}
			dgemv_( TransA, 
					&M, 
					&N,
					&alpha,
					A, 
					&lda,
					X, 
					&incX, 
					&beta,
					Y, 
					&incY
#ifdef _ACML
					,1);
#else
					);
#endif

			for(unsigned long i(0);i<3;i++) std::cout << Y[i] << "\n";
	}

	}
	catch(std::string str) {
		std::cout << str.c_str() << "\n";
	}


}
