
#ifndef CELL_MATRIX_PIMPL_I_H
#define CELL_MATRIX_PIMPL_I_H

#include "CellValue.h"
#include <xlw/MyContainers.h>
#include <xlw/eshared_ptr.h>
#include <string>
#include <vector>

namespace xlw {

	class CellMatrix_pimpl_abstract
	{
	public:
		typedef eshared_ptr<CellMatrix_pimpl_abstract> pimpl;

		virtual const CellValue& operator()(size_t i, size_t j) const=0;
		virtual CellValue& operator()(size_t i, size_t j)=0;
		virtual size_t RowsInStructure() const=0;
		virtual size_t ColumnsInStructure() const=0;
		virtual void PushBottom(const CellMatrix_pimpl_abstract& newRows)=0;

	};

}

#endif // CELL_MATRIX_PIMPL_I_H

