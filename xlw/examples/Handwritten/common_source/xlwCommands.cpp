
/*
 Copyright (C) 2011 John Adcock
 Copyright (C) 2011 Narinder S Claire

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
#include <xlw/XlOpenClose.h>
#include <xlw/XlfServices.h>
using namespace xlw;


void welcome()
{
    XlfServices.StatusBar = "This is the XLW Handwritten Project, Enjoy !!       " 
                            "Email any questions to xlw-users@lists.sourceforge.net. " ;
}

// Registers welcome() to be executed by xlAutoOpen
// method must have return type void and take no parameters.
// You can register as many functions as you like.
namespace 
{
    MacroCache<Open>::MacroRegistra welcome_registra("welcome","welcome",welcome);
}

void goodbye()
{
    xlw::XlfServices.Commands.Alert("Thanks for choosing XLW. \n"
                                    "Email any questions to xlw-users@lists.sourceforge.net. ");
}
// Registers goodbye() to be executed by xlAutoClose
// method must have return type void and take no parameters.
// You can register as many functions as you like.
namespace 
{
    MacroCache<Close>::MacroRegistra goodbye_registra("goodbye","goodbye",goodbye);
}


extern "C" 
{
    int EXCEL_EXPORT xlTestCmd() 
    {
        EXCEL_BEGIN;
        xlw::XlfServices.Commands.Alert("This is the TestCmd function\n"
                                        "Email any questions to xlw-users@lists.sourceforge.net. ");
        EXCEL_END_CMD;
    }

    // demonstrates creating a new sheet and getting data onto it
    int EXCEL_EXPORT xlModifySheet() 
    {
        EXCEL_BEGIN;

        // Have to use when adding formulas as not all
        // functions seem to be reentrant
        xlw::DisableCalculation whileInScope;

        // Use when adding data to speed things up
        xlw::DisableScreenUpdates whileInScope2;

        xlw::XlfServices.Commands.InsertWorkSheet();
        // first way of refering to cells is to convert names to cell refs
        // remember to prefix names with ! to avoid getting references to missing
        // macro sheet
        XlfOper topRight(xlw::XlfServices.Information.GetCellRefA1("!A1"));
        xlw::XlfServices.Cell.SetContents(topRight, "Hello Xlw User");
        xlw::XlfServices.Cell.SetFont(topRight, "Times New Roman");
        xlw::XlfServices.Cell.SetFontSize(topRight, 20.0);
        xlw::XlfServices.Cell.SetHeight(topRight, 25.0);

        // next way is to use strings in R1C1 format
        xlw::XlfServices.Cell.SetContents("R2C1", "Number");
        xlw::XlfServices.Cell.SetContents("R2C2", "Square");

        for(int i(0); i < 1001; ++i)
        {
            // last way is to use XlfRef objects
            xlw::XlfServices.Cell.SetContents(XlfRef(i+2, 0), i);
            // can add formulas using relative notation
            xlw::XlfServices.Cell.SetContents(XlfRef(i+2, 1), "=R[0]C[-1]^2");
        }
        EXCEL_END_CMD;
    }
}

namespace 
{

    XLRegistration::XLCommandRegistrationHelper registerTestCmd(
        "xlTestCmd", "TestCmd", "A Test Command",
        "Handwritten", "Test Command");

    XLRegistration::XLCommandRegistrationHelper modifySheetCmd(
        "xlModifySheet", "ModifySheet", "A Test Command that modifies the sheet",
        "Handwritten", "Modify Sheet");

}
