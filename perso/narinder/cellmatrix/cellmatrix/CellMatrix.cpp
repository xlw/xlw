#include"CellMatrix.h"

namespace xlw
{

	CellMatrix & CellMatrix::operator=(const CellMatrix &theOther)
	{
		CellMatrix temp(theOther);
		temp.swap(*this);
		return *this;
	}


        CellMatrix::CellMatrix(double data):pimpl(new defaultCellMatrixImpl(1,1))
		{
			(*pimpl)(1,1)=data;
		}
        CellMatrix::CellMatrix(const std::string &  data):pimpl(new defaultCellMatrixImpl(1,1))
		{
			(*pimpl)(1,1)=data;
		}
        CellMatrix::CellMatrix(const std::wstring &  data):pimpl(new defaultCellMatrixImpl(1,1))
		{
			(*pimpl)(1,1)=data;
		}
        CellMatrix::CellMatrix(const char* data):pimpl(new defaultCellMatrixImpl(1,1))
		{
			(*pimpl)(1,1)=std::string(data);
		}
        CellMatrix::CellMatrix(const MyArray& data):pimpl(new defaultCellMatrixImpl(data.size(),1))
		{
			for(size_t i(0); i < data.size(); ++i)
			{
				(*pimpl)(i,0) = data[i];
			}
		}
		CellMatrix::CellMatrix(const MyMatrix& data):pimpl(new defaultCellMatrixImpl(data.rows(),data.columns()))
		{
			
			for(size_t i(0); i < data.rows(); ++i)
			{
				for(size_t j(0); j < data.columns(); ++j)
				{
				  (*pimpl)(i,j) = data(i,j);
				}
			}
			
		}
        CellMatrix::CellMatrix(unsigned long data):pimpl(new defaultCellMatrixImpl(1,1))
		{
			(*pimpl)(1,1)=data;
		}
        CellMatrix::CellMatrix(int data):pimpl(new defaultCellMatrixImpl(1,1))
		{
			(*pimpl)(1,1)=data;
		}

		CellMatrix MergeCellMatrices(const CellMatrix& Top, const CellMatrix& Bottom)
		{
			CellMatrix temp(Top);
			temp.PushBottom(Bottom);
			return temp;
		}
}