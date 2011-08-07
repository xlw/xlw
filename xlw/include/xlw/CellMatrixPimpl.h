/*
Copyright (C) 2006 Mark Joshi
Copyright (C) 2009 2011 Narinder S Claire


This file is part of XLW, a free-software/open-source C++ wrapper of the
Excel C API - http://xlw.sourceforge.net/

XLW is free software: you can redistribute it and/or modify it under the
terms of the XLW license.  You should have received a copy of the
license along with this program; if not, please email xlw-users@lists.sf.net

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the license for more details.
*/
#ifndef CELL_MATRIX_PIMPL_I_H
#define CELL_MATRIX_PIMPL_I_H

#include <xlw/CellValue.h>
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
		virtual  ~CellMatrix_pimpl_abstract()
		{
		}

	};

}

#endif // CELL_MATRIX_PIMPL_I_H

