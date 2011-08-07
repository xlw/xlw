
#include<sstream>
void xerbla_cpp(char *srname,int info) {
	std::ostringstream errString;
	errString << "XERBLA ERROR : Parameter " << info << " to routine "<<srname << " was incorrect.";
	throw(errString.str());
}
	


extern "C" {
	#include <stdio.h>
	void xerbla_(char *srname, void *vinfo) {

		int *info = (int*)vinfo;
		xerbla_cpp(srname,*info);

	}
}
		