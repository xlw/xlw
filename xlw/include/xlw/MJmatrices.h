//
//
//                          MJmatrices.h
//
//
/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2007 Tim Brunne
 Copyright (C) 2009 Narinder S Claire
 
 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/
/*
    a simple matrix class
    it has been kept so that its interface is minimal to facilitate interchange
    with other matrix classes


  */
#ifndef MJMATRICES_H
#define MJMATRICES_H


#include <cstddef>

using std::size_t;

namespace xlw {

    class MJMatrix
    {
    public:

        explicit MJMatrix(size_t Rows_=0, size_t Cols_=0);
        MJMatrix(const MJMatrix& original);

        MJMatrix& operator=(const MJMatrix& original);

        ~MJMatrix();


        inline size_t rows() const;
        inline size_t columns() const;
        inline size_t size1() const;
        inline size_t size2() const;

        inline MJMatrix& operator+=(const MJMatrix& addend);

        MJMatrix& resize(size_t rows, size_t columns);

        inline double* operator[](size_t i);
        inline const double* const operator[](size_t i) const;

        inline const double& operator()(size_t i, size_t j) const;
        inline double& operator()(size_t i, size_t j);



    private:

        size_t Rows;
        size_t Columns;
        double** RowStarts;
        double* Start;

        void Create();
        void Create(size_t rows, size_t cols);
    };

    inline const double& MJMatrix::operator()(size_t i, size_t j) const
    {
#ifdef _DEBUG
    if (i >= Rows || j >= Columns)
        throw("index out of bounds");
#endif
        return RowStarts[i][j];
    }

    inline double& MJMatrix::operator()(size_t i, size_t j)
    {
#ifdef _DEBUG
    if (i >= Rows || j >= Columns)
        throw("index out of bounds");
#endif

        return RowStarts[i][j];
    }

    inline const double* const MJMatrix::operator[](size_t i) const
    {
#ifdef _DEBUG
    if (i >= Rows )
        throw("index out of bounds");
#endif

        return RowStarts[i];
    }



    inline double*  MJMatrix::operator[](size_t i)
    {
#ifdef _DEBUG
    if (i >= Rows )
        throw("index out of bounds");
#endif

        return RowStarts[i];
    }

    inline size_t MJMatrix::rows() const
    {
        return Rows;
    }

    inline size_t MJMatrix::columns() const
    {
        return Columns;
    }

    inline size_t MJMatrix::size1() const
    {
        return Rows;
    }

    inline size_t MJMatrix::size2() const
    {
        return Columns;
    }


    inline MJMatrix& MJMatrix::operator+=(const MJMatrix& addend)
    {
#ifdef _DEBUG
        if (addend.rows() != rows() || addend.columns() != columns())
            throw("bad addition");
#endif

        double* i = Start;
        double *j = addend.Start;
        double* end = Start+Rows*Columns;
        while (i != end)
        {
            *i += *j;
            ++i;
            ++j;
        }

        return *this;

    }

}

#endif
