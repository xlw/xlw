//
//
//                          MJmatrices.cpp
//
//
/*
 Copyright (C) 2006 Mark Joshi
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

#include <xlw/MJmatrices.h>
#include <algorithm>

xlw::MJMatrix&
xlw::MJMatrix::resize(size_t rows, size_t columns)
{
  if(rows==Rows && columns == Columns)
    return *this;
  else
  {
    if(Start>0)
    {
      delete [] Start;
      delete [] RowStarts;
    }
    Create(rows,columns);
    return *this;
  }

}



void xlw::MJMatrix::Create()
{
    if (Rows*Columns>0)
    {
        Start = new double[Rows*Columns];
        RowStarts = new double*[Rows];

        for (unsigned long i=0; i < Rows; i++)
            RowStarts[i] = Start+i*Columns;
    }
    else
        Start=0;

    for (unsigned long i=0; i < Rows; i++)
        for (unsigned long j=0; j < Columns; j++)
            RowStarts[i][j]=0.0;
}


void xlw::MJMatrix::Create(size_t rows, size_t cols)
{
  Rows = rows;
  Columns = cols;
  Create();
}


xlw::MJMatrix::MJMatrix(size_t Rows_, size_t Columns_)
                :       Rows(Rows_),
                        Columns(Columns_)
{
    Create();
}

xlw::MJMatrix::MJMatrix(const MJMatrix& original)
                :       Rows(original.Rows),
                        Columns(original.Columns)
{
    Create();

    std::copy(original.Start, original.Start+Rows*Columns, Start);

}

xlw::MJMatrix& xlw::MJMatrix::operator=(const MJMatrix& original)
{
    if (this != &original)
    {
        if (Rows != original.Rows || Columns != original.Columns)
        {
            if (Start>0)
            {
                delete[] Start;
                delete[] RowStarts;
            }

            Rows = original.Rows;
            Columns = original.Columns;

            Create();
        }

        std::copy(original.Start, original.Start+Rows*Columns, Start);
    }

    return *this;
}


xlw::MJMatrix::~MJMatrix()
{
    if (Start >0)
    {
        delete[] Start;
        delete[] RowStarts;
    }
}
