
/*
 Copyright (C) 2011 John Adcock

 This file is part of xlw, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 xlw is free software: you can redistribute it and/or modify it under the
 terms of the xlw license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

// $Id$

#include <xlw/xlw.h>
using namespace xlw;

extern "C" {

    LPXLFOPER EXCEL_EXPORT xlMatrixTest(LPXLFOPER inRows, LPXLFOPER inCols) {
        EXCEL_BEGIN;
        XlfOper xlRows(inRows);
        XlfOper xlCols(inCols);

        RW nbRows(xlRows.AsInt());
        RW nbCols(xlCols.AsInt());
        XlfOper result(nbRows, nbCols);

        for(RW row(0); row < nbRows; ++row)
        {
            for(RW col(0); col < nbCols; ++col)
            {
                if(row == col)
                {
                    result(row, col) = 1.0;
                }
                else
                {
                    result(row, col) = 0.0;
                }
            }
        }

        return result;
        EXCEL_END;
    }

    LPXLOPER EXCEL_EXPORT xlMatrixTest4(LPXLOPER inRows, LPXLOPER inCols) {
        EXCEL_BEGIN;
        XlfOper4 xlRows(inRows);
        XlfOper4 xlCols(inCols);

        RW nbRows(xlRows.AsInt());
        RW nbCols(xlCols.AsInt());
        XlfOper4 result(nbRows, nbCols);
        // may be truncated
        nbRows = result.rows();
        nbCols = result.columns();

        for(RW row(0); row < nbRows; ++row)
        {
            for(RW col(0); col < nbCols; ++col)
            {
                if(row == col)
                {
                    result(row, col) = 1.0;
                }
                else
                {
                    result(row, col) = 0.0;
                }
            }
        }

        return result;
        EXCEL_END_4;
    }

    LPXLOPER12 EXCEL_EXPORT xlMatrixTest12(LPXLOPER12 inRows, LPXLOPER12 inCols) {
        EXCEL_BEGIN;
        XlfOper12 xlRows(inRows);
        XlfOper12 xlCols(inCols);

        RW nbRows(xlRows.AsInt());
        RW nbCols(xlCols.AsInt());
        XlfOper12 result(nbRows, nbCols);
        // may be truncated
        nbRows = result.rows();
        nbCols = result.columns();

        for(RW row(0); row < nbRows; ++row)
        {
            for(RW col(0); col < nbCols; ++col)
            {
                if(row == col)
                {
                    result(row, col) = 1.0;
                }
                else
                {
                    result(row, col) = 0.0;
                }
            }
        }

        return result;
        EXCEL_END_12;
    }
}

namespace {

    XLRegistration::Arg MatrixTestArgs[] = {
        { "rows", "Number of rows", "XLF_OPER" },
        { "cols", "Number of columns", "XLF_OPER" }
    };

    XLRegistration::XLFunctionRegistrationHelper registerMatrixTest(
        "xlMatrixTest", "MatrixTest", "Generate an identity matrix",
        "xlw Example", MatrixTestArgs, 2);

    XLRegistration::Arg MatrixTest4Args[] = {
        { "rows", "Number of rows", "P" },
        { "cols", "Number of columns", "P" }
    };

    XLRegistration::XLFunctionRegistrationHelper registerMatrixTest4(
        "xlMatrixTest4", "MatrixTest4", "Generate an identity matrix",
        "xlw Example", MatrixTest4Args, 2, false, false, "P");

    XLRegistration::Arg MatrixTest12Args[] = {
        { "rows", "Number of rows", "Q" },
        { "cols", "Number of columns", "Q" }
    };

    XLRegistration::XLFunctionRegistrationHelper registerMatrixTest12(
        "xlMatrixTest12", "MatrixTest12", "Generate an identity matrix",
        "xlw Example", MatrixTest12Args, 2, false, false, "Q");
}
