
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
#include <xlw/XlfServices.h>
using namespace xlw;


extern "C" {

    /*!
     * Demonstrates calling Excel Service functions from within a
     * a function, for this to work you must set the MacroSheetEquivalent
     * to true when registering.
     * This function gets the formula in the current cell when calculated
     */
    LPXLFOPER EXCEL_EXPORT xlCurrentFormula() {
        EXCEL_BEGIN;
        XlfOper activeCell(XlfServices.Information.GetActiveCell());
        return XlfOper(XlfServices.Information.GetFormula(activeCell));
        EXCEL_END;
    }
}

namespace 
{
    // Register the function CurrentFormula as volatile and MacroSheetEquivalent
    XLRegistration::XLFunctionRegistrationHelper registerCurrentFormula(
        "xlCurrentFormula", "CurrentFormula", "Returns the formula in the current cell "
        "by calling Excel Macro functions",
        "xlw Example", 0, 0, true, false, "", "", false, true);
}
