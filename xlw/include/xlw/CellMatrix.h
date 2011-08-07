/*
Copyright (C) 2006 Mark Joshi
Copyright (C) 2007, 2008 Eric Ehlers
Copyright (C) 2009 2011 Narinder S Claire
Copyright (C) 2011 John Adcock

This file is part of XLW, a free-software/open-source C++ wrapper of the
Excel C API - http://xlw.sourceforge.net/

XLW is free software: you can redistribute it and/or modify it under the
terms of the XLW license.  You should have received a copy of the
license along with this program; if not, please email xlw-users@lists.sf.net

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the license for more details.
*/
#ifndef CELL_MATRIX_H
#define CELL_MATRIX_H


#include <xlw/CellValue.h>
#include "xlw/MyContainers.h"
#include <string>
#include <vector>

namespace xlw {


	class CellMatrix
	{
	public:

		//Copy Constructor
		CellMatrix(const CellMatrix &theOther):pimpl(theOther.pimpl.copy()){}


		CellMatrix(size_t rows, size_t columns):pimpl(new CellMatrixImpl(rows, columns)){}

		CellMatrix():pimpl(new CellMatrixImpl()){}


		CellMatrix(double data):pimpl(new CellMatrixImpl(1,1))
		{
			(*pimpl)(0,0)=data;
		}

		CellMatrix(const std::string &  data):pimpl(new CellMatrixImpl(1,1))
		{
			(*pimpl)(0,0)=data;
		}

		CellMatrix(const std::wstring &  data):pimpl(new CellMatrixImpl(1,1))
		{
			(*pimpl)(0,0)=data;
		}
		
		CellMatrix(const char* data):pimpl(new CellMatrixImpl(1,1))
		{
			(*pimpl)(0,0)=std::string(data);
		}
		
		CellMatrix(const MyArray& data):
		pimpl(new CellMatrixImpl(ArrayTraits<MyArray>::size(data),1))
		{
			for(size_t i(0); i < ArrayTraits<MyArray>::size(data); ++i)
			{
				(*pimpl)(i,0) = ArrayTraits<MyArray>::getAt(data,i);
			}
		}
		
		CellMatrix(const MyMatrix& data):
		pimpl(new CellMatrixImpl(MatrixTraits<MyMatrix>::rows(data),MatrixTraits<MyMatrix>::columns(data)))
		{

			for(size_t i(0); i < MatrixTraits<MyMatrix>::rows(data); ++i)
			{
				for(size_t j(0); j < MatrixTraits<MyMatrix>::columns(data); ++j)
				{
					(*pimpl)(i,j) = MatrixTraits<MyMatrix>::getAt(data,i,j);
				}
			}

		}
		
		CellMatrix(unsigned long data):pimpl(new CellMatrixImpl(1,1))
		{
			(*pimpl)(0,0)=data;
		}
		
		CellMatrix(int data):pimpl(new CellMatrixImpl(1,1))
		{
			(*pimpl)(0,0)=data;
		}

		CellMatrix & operator=(const CellMatrix &theOther)
		{
            CellMatrix temp(theOther);
			temp.swap(*this);
			return *this;
		}

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

		void PushBottom(const CellMatrix & newRows)
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

	inline CellMatrix MergeCellMatrices(const CellMatrix& Top, const CellMatrix& Bottom)
	{
		CellMatrix temp(Top);
		temp.PushBottom(Bottom);
		return temp;
	}



}

#endif
