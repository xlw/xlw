//
//
//                                  MJCellMatrix.h
//
//
/*
Copyright (C) 2006 Mark Joshi
Copyright (C) 2007, 2008 Eric Ehlers
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

#ifndef MJ_CELL_MATRIX_H
#define MJ_CELL_MATRIX_H


#include <xlw/CellValue.h>
#include <xlw/CellMatrixPimpl.h>
#include <string>
#include <vector>

namespace xlw {

	namespace impl
	{


		class MJCellValue : public CellValue
		{
			enum ValueType
			{
				string, wstring, number, boolean, error, empty
			};
			ValueType Type;

			mutable xlw_tr1::shared_ptr<std::string>  ValueAsString;
			mutable xlw_tr1::shared_ptr<std::wstring> ValueAsWstring;
			double ValueAsNumeric;
			bool ValueAsBool;

			unsigned long ValueAsErrorCode;

		public:
			/// is value an ascii string type
			bool IsAString() const;
			/// is value either an ascii or unicode string
			bool IsString() const;
			/// is value a unicode string
			bool IsAWstring() const;
			bool IsANumber() const;
			bool IsBoolean() const;
			bool IsError() const;
			bool IsEmpty() const;

			MJCellValue(const MJCellValue &);
			MJCellValue(const std::string&);
			MJCellValue(const std::wstring&);
			MJCellValue(double Number);
			MJCellValue(unsigned long Code, bool Error=false); //Error = true if you want an error code
			MJCellValue(bool TrueFalse);
			MJCellValue(int i);

			MJCellValue();

			MJCellValue &operator=(const MJCellValue &theOther)
			{
				MJCellValue(theOther).swap(*this);
				return *this;
			}

			const std::string & StringValue() const;
			const std::wstring& WstringValue() const;
			double NumericValue() const;
			bool BooleanValue() const;
			unsigned long ErrorValue() const;

			operator std::string() const;
			operator std::wstring() const;
			operator bool() const;
			operator double() const;
			operator unsigned long() const;

			void clear()
			{
				MJCellValue().swap(*this);
			}

			void swap(MJCellValue &theOther) // This Does not and SHOULD NOT throw
			{
				ValueAsString.swap(theOther.ValueAsString);
				ValueAsWstring.swap(theOther.ValueAsWstring);
				std::swap(ValueAsNumeric,theOther.ValueAsNumeric);
				std::swap(ValueAsBool,theOther.ValueAsBool);
				std::swap(ValueAsErrorCode,theOther.ValueAsErrorCode);
				std::swap(Type,theOther.Type);

			}


			MJCellValue & assign(const std::string &data)
			{
				MJCellValue(data).swap(*this);
				return *this;
			}
			MJCellValue & assign(const std::wstring& data)
			{
				MJCellValue(data).swap(*this);
				return *this;
			}
			MJCellValue & assign(double data)
			{
				MJCellValue(data).swap(*this);
				return *this;
			}
			MJCellValue & assign(unsigned long data)
			{
				MJCellValue(data).swap(*this);
				return *this;
			}
			MJCellValue & assign(bool data)
			{
				MJCellValue(data).swap(*this);
				return *this;
			}
			MJCellValue & assign(int data)
			{
				MJCellValue(data).swap(*this);
				return *this;
			}
			MJCellValue & assign(error_type e)
			{
				MJCellValue(e.value,true).swap(*this);
				return *this;
			}
		};

		class MJCellMatrix : public CellMatrix_pimpl_abstract
		{
		public:

			MJCellMatrix(const MJCellMatrix &theOther)
			{
				Cells = theOther.Cells;
				Rows = theOther.Rows;
				Columns = theOther.Columns;
			}
			MJCellMatrix();
			MJCellMatrix(size_t rows, size_t columns);

			const CellValue& operator()(size_t i, size_t j) const;
			CellValue& operator()(size_t i, size_t j);

			size_t RowsInStructure() const;
			size_t ColumnsInStructure() const;

			void PushBottom(const CellMatrix_pimpl_abstract& newRows);

		private:

			std::vector<std::vector<MJCellValue> > Cells;
			size_t Rows;
			size_t Columns;

		};


	}
}

#endif // MJ_CELL_MATRIX_H


