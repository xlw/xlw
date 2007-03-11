//
//										xlarray.h
//

#ifndef XL_ARRAY_H
#define XL_ARRAY_H

#include "xlcall32.h"
#include "MyContainers.h"

struct xlarray
{
	WORD rows;
	WORD columns;
	double data[1];
};


typedef xlarray* LPXLARRAY;


NEMatrix GetMatrix(LPXLARRAY);

#endif

