
#include<sstream>
void xerbla_cpp(char *srname,int info) {
	std::ostringstream errString;
	errString << "XERBLA ERROR : Parameter " << info << " to routine "<<srname << " was incorrect.";
	throw(errString.str());
}
	


extern "C" {
	// the standard error handling function is called xerbla in fortran. It will be exposed as xerbla_
        // here we have a replacement
	#include <stdio.h>
	void xerbla_(char *srname, void *vinfo) {
		//srname is a pointer to the subroutine where the error happened

		int *info = (int*)vinfo;   // info now points to the integer identifying 
		xerbla_cpp(srname,*info);  // the incorrect parameter

	}
}
		