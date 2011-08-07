
/*
Copyright (C) 2011 Narinder S Claire

This file is part of XLW, a free-software/open-source C++ wrapper of the
Excel C API - http://xlw.sourceforge.net/

XLW is free software: you can redistribute it and/or modify it under the
terms of the XLW license.  You should have received a copy of the
license along with this program; if not, please email xlw-users@lists.sf.net

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the license for more details.
*/


#ifndef NCMATRICES_H
#define NCMATRICES_H


#include <cstddef>
#include <vector>
#include <xlw/eshared_ptr.h>
#include <xlw/XlfException.h>

using std::size_t;

namespace xlw {

    class NCMatrix
    {


        struct NCMatrixData
        {
            NCMatrixData(size_t Rows_, size_t Cols_):theRows(Rows_),
                theArray(Rows_ * Cols_),
                Rows(Rows_),
                Columns(Cols_)
            {
                if(theArray.size() >0 )
                {
                    for (size_t i=0; i < Rows; i++)
                    {
                        theRows[i] = theArray.begin() + i * Columns;
                    }
                    std::fill(theArray.begin(), theArray.end(),0.0);
                }
            }

            NCMatrixData(const NCMatrixData& theOther) :
                theRows(theOther.Rows),
                theArray(theOther.theArray),
                Rows(theOther.Rows),
                Columns(theOther.Columns)
            {
                for (size_t i=0; i < Rows; i++)
                {
                    theRows[i] = theArray.begin() + i * Columns;
                }
            }

            std::vector<std::vector<double>::iterator > theRows;
            std::vector<double> theArray;
            size_t Rows;
            size_t Columns;

        private:
            // never should need the following
            NCMatrixData & operator=(const NCMatrixData&);
        };


    public:
        typedef std::vector<double>::iterator iterator;
        typedef std::vector<double>::const_iterator const_iterator;

        explicit NCMatrix(size_t Rows_=0, size_t Cols_=0);

        NCMatrix(const NCMatrix& original);

        NCMatrix& operator=(const NCMatrix& original);


        inline size_t rows() const;
        inline size_t columns() const;
        inline size_t size1() const;
        inline size_t size2() const;

        inline NCMatrix& operator+=(const NCMatrix& addend);

        NCMatrix& resize(size_t rows, size_t columns);

        inline iterator operator[](size_t i);
        inline const_iterator operator[](size_t i) const;

        inline const double& operator()(size_t i, size_t j) const;
        inline double& operator()(size_t i, size_t j);

        // We have added to the interface here 28-03-2011
        // but swap is generally an accepted method in container
        // interfaces
        inline void swap(NCMatrix& theOther);// this cannot throw !

        ~NCMatrix(){}

    private:
        inline void check_row(size_t j)const;
        inline void check_column(size_t i)const;


        eshared_ptr<NCMatrixData> theData;

    };

    // The following 2 methods will get dropped
    // by the compiler optimiser anyway
    void NCMatrix::check_row(size_t i)const
    {
#ifdef _DEBUG
        if (i >= theData->Rows)
            throw XlfOutOfBounds();
#endif
    }

    void NCMatrix::check_column(size_t j)const
    {
#ifdef _DEBUG
        if (j >= theData->Columns)
            throw XlfOutOfBounds();
#endif
    }

    const double& NCMatrix::operator()(size_t i, size_t j) const
    {
        check_row(i);
        check_column(j);
        return theData->theRows[i][j];
    }

    double& NCMatrix::operator()(size_t i, size_t j)
    {
        check_row(i);
        check_column(j);
        return theData->theRows[i][j];
    }

    NCMatrix::const_iterator  NCMatrix::operator[](size_t i) const
    {
        check_row(i);
        return theData->theRows[i];
    }



    NCMatrix::iterator  NCMatrix::operator[](size_t i)
    {
        check_row(i);
        return theData->theRows[i];
    }

    size_t NCMatrix::rows() const
    {
        return theData->Rows;
    }

    size_t NCMatrix::columns() const
    {
        return theData->Columns;
    }

    size_t NCMatrix::size1() const
    {
        return theData->Rows;
    }

    size_t NCMatrix::size2() const
    {
        return theData->Columns;
    }


    NCMatrix& NCMatrix::operator+=(const NCMatrix& addend)
    {
#ifdef _DEBUG
        if (addend.rows() != rows() || addend.columns() != columns())
            throw XlfGeneralException("bad matrix addition");
#endif

        NCMatrix::iterator i = theData->theArray.begin();
        NCMatrix::const_iterator j = addend.theData->theArray.begin();
        while (i != theData->theArray.end())
        {
            *i++ += *j++;

        }

        return *this;

    }

    void NCMatrix::swap(NCMatrix& theOther) // this cannot throw !
    {
        theData.swap(theOther.theData);
    }

}

#endif // NCMatrices


