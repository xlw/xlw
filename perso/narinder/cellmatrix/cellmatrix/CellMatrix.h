
#ifndef CELL_MATRIX_H
#define CELL_MATRIX_H


#include "CellValue.h"
#include "MJCellMatrix.h"
#include <xlw/MyContainers.h>
#include <string>
#include <vector>

namespace xlw {

	typedef impl::MJCellMatrix defaultCellMatrixImpl;
    
    class CellMatrix
    {
    public:
		
		//Copy Constructor
		CellMatrix(const CellMatrix &theOther):pimpl(theOther.pimpl.copy()){}


		CellMatrix():pimpl(new impl::MJCellMatrix()){}

		CellMatrix(size_t rows, size_t columns ):pimpl(new defaultCellMatrixImpl(rows,columns)){}
        explicit CellMatrix(double );
        explicit CellMatrix(const std::string & );
        explicit CellMatrix(const std::wstring & );
        explicit CellMatrix(const char* );
        explicit CellMatrix(const MyArray& );
        explicit CellMatrix(const MyMatrix& );
        explicit CellMatrix(unsigned long );
        explicit CellMatrix(int i);

	    CellMatrix & operator=(const CellMatrix &theOther);

	
        const CellValue& operator()(size_t i, size_t j) const
		{
			return pimpl->operator()(i,j);
		}
		CellValue& operator()(size_t i, size_t j) 
		{	
			return pimpl->operator()(i,j);
		}

        size_t RowsInStructure() const
		{
			return pimpl->RowsInStructure();
		}
        size_t ColumnsInStructure() const
		{
			return pimpl->ColumnsInStructure();
		}

        void PushBottom(const CellMatrix& newRows)
		{
			CellMatrix temp(*this);
			temp.pimpl->PushBottom(*(newRows.pimpl));
			temp.swap(*this);

		}

		void swap(CellMatrix &theOther)
		{
			pimpl.swap(theOther.pimpl);
		}
		
	private:
		eshared_ptr<CellMatrix_pimpl_abstract> pimpl;

    };

	CellMatrix MergeCellMatrices(const CellMatrix& Top, const CellMatrix& Bottom);

}

#endif
