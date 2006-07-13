
/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte
 Copyright (C) 2006 Mark Joshi

 This file is part of xlw, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 xlw is free software: you can redistribute it and/or modify it under the
 terms of the xlw license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net
 
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/



#include "XlOpenClose.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "Win32StreamBuf.h"
#include <xlw/XlFunctionRegistration.h>
#include <xlw/CellMatrix.h>

Win32StreamBuf debuggerStreamBuf;
std::streambuf * oldStreamBuf;

extern "C"
{

  long EXCEL_EXPORT xlAutoOpen()
  {
    oldStreamBuf = std::cerr.rdbuf(&debuggerStreamBuf);
    std::cerr << __HERE__ << "std::cerr redirected to MSVC debugger" << std::endl;

    // Displays a message in the status bar.
    XlfExcel::Instance().SendMessage("Registering library...");

	XLRegistration::ExcelFunctionRegistrationRegistry::Instance().DoTheRegistrations();
	
    // Clears the status bar.
    XlfExcel::Instance().SendMessage();
    return 1;
  }

  long EXCEL_EXPORT xlAutoClose()
  {
    std::cerr << __HERE__ << "Releasing ressources" << std::endl;
    delete &XlfExcel::Instance();
    std::cerr.rdbuf(oldStreamBuf);
    return 1;
  }

}
