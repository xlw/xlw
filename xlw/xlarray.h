//
//										xlarray.h
//

#ifndef XL_ARRAY_H
#define XL_ARRAY_H

#include "xlcall32.h"
typedef struct
{
	WORD rows;
	WORD columns;
	double array[1];
}
xlarray;


typedef xlarray* LPXLARRAY;
#endif

