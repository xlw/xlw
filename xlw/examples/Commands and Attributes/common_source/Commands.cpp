/*

 Copyright (C) 2011 John Adcock
 Copyright (C) 2011 Narunder S Claire


 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include<xlw/XlfOper.h>
#include <windows.h>
#include"reftest.h"
#include<xlw/XlfExcel.h>
#include<xlw/XlOpenClose.h>
#include<xlw/XlfServices.h>



void welcome()
{
    xlw::XlfServices.StatusBar= "This is the XLW Example Project, Enjoy !!    "
                                "Email any questions to xlw-users@lists.sourceforge.net. ";
}



void goodbye()
{
    xlw::XlfServices.Commands.Alert("Thanks for choosing XLW. \n"
                                    "Email any questions to xlw-users@lists.sourceforge.net. ");
}


void testCommand()
{
    // show off the macro commands - who needs VBA :)
    xlw::XlfOper cellRef = xlw::XlfServices.Commands.InputReference("Give me a cell and I'll tell you its formula", "Test Command");
    std::string formula(xlw::XlfServices.Information.GetFormula(cellRef));
    xlw::XlfServices.Commands.Alert(formula);
}