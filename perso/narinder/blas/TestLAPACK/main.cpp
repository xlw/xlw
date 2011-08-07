

#include<iostream>

#ifdef _ACML
#include "acml.h"
#else
#include "cblas.h"

extern "C" void dsyev_(char *,
					   char *,
					   int *,
					   double *,
					   int *,
					   double *,
					   double *,
					   int *,
					   int *);
#endif


int main() {
	try {


	char JOBZ[]="V";
	char UPLO[]="U";
	int N(2);
	double A[]={2,1,1,5};
	//int LDA;
	double W[2]={0.0,0.0};
	double WORK[10];

	int LWORK(10);
	int INFO;

	for (int LDA(2);LDA>=1;LDA--) {
		dsyev_(  JOBZ,
				 UPLO,
				 &N,
				 A,
				 &LDA,
				 W,
				 WORK,
				 &LWORK,
				 &INFO
#ifdef _ACML
				 ,1,1);
#else
			     );
#endif
		std::cout<< "\nEigenValues :\n" ;
		for	(unsigned long i(0);i<2;i++) std::cout << W[i] << "\n";
		}
	}
	catch(std::string str) {
		std::cout << str.c_str() << "\n";
	}


}
