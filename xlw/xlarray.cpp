//
//							    xlarray.cpp
//

#include "xlarray.h"

NEMatrix GetMatrix(LPXLARRAY input)
{
	int rows = input->rows;
	int cols = input->columns;

	NEMatrix result(rows,cols);
	for (int i=0; i < rows; ++i)
		for (int j=0; j < cols; ++j)
		{
			int k = i*cols+j;
			double val = input->data[k];
			result(i,j)= val;
		}
	return result;
}
