/*
 Copyright (C) 2008 2009 2011 Narinder S Claire

 This file is part of XLWDOTNET, a free-software/open-source C# wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLWDOTNET is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef XLW_DOT_NET_H
#define XLW_DOT_NET_H

// Shouldn't really need this file, but I think theres an
// oversigt by the xlw people.


#include<xlw/MyContainers.h>
#include<xlw/CellMatrix.h>
#include<xlw/ArgList.h>
#include<string>
#include<xlw/XlfException.h>




#define DLLEXPORT __declspec(dllexport)

#ifndef  ERRCELLS_NOT_REQUIRED
namespace {
    std::string errMessage;
    xlw::CellMatrix errCells;
}
#endif 

#define DOT_NET_EXCEL_BEGIN  try {
#define DOT_NET_EXCEL_END \
} catch (xlwDotNet::cellMatrixException^ theError ) { \
   String^ ErrorMessage = theError->Message;\
   errCells = CellMatrix(std::string((const char*)(Marshal::StringToHGlobalAnsi(ErrorMessage).ToPointer())));\
   errCells.PushBottom ( *(xlw::CellMatrix*)((theError->inner).ToPointer()));\
   throw(errCells);\
} catch (XlfException& theError) { \
    throw(theError); \
} catch (std::runtime_error& theError){\
    throw(theError); \
} catch (std::string& theError){\
    throw(theError); \
} catch (const char* theError){\
    throw(theError); \
} catch (System::Exception^ theError ) { \
    String^ ErrorType = theError->GetType()->ToString() + " : " + theError->Message ;\
    String^ StackTrace = theError->StackTrace;\
    xlw::ArgumentList theArg = xlw::ArgumentList((const char*)(Marshal::StringToHGlobalAnsi(ErrorType).ToPointer()));\
    theArg.add("StackTrace",std::string((const char*)(Marshal::StringToHGlobalAnsi(StackTrace).ToPointer())));\
    errCells = theArg.AllData();\
    throw(errCells);\
}


using namespace xlw;

#endif
