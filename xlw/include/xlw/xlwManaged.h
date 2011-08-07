/*
 Copyright (C) 2011  Narinder S Claire

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef MANAGED_XLW_H
#define MANAGED_XLW_H


namespace {
    std::string errMessage;
    xlw::CellMatrix errCells;
}

#define MANAGED_EXECL_BEGIN  try {
#define MANAGED_EXECL_END \
} catch (System::Runtime::InteropServices::SEHException^ ) { \
	throw; \
}\
catch (System::Exception^ theError ) { \
    String^ ErrorType = theError->GetType()->ToString() + " : ";\
        String^ ErrorMessage = theError->Message;\
        String^ StackTrace = theError->StackTrace;\
        xlw::ArgumentList theArg = xlw::ArgumentList((const char*)(Marshal::StringToHGlobalAnsi(ErrorType).ToPointer()));\
        theArg.add("ErrorMessage",std::string((const char*)(Marshal::StringToHGlobalAnsi(ErrorMessage).ToPointer())));\
        theArg.add("StackTrace",std::string((const char*)(Marshal::StringToHGlobalAnsi(StackTrace).ToPointer())));\
        errCells = theArg.AllData();\
    throw(errCells);\
}



#endif //  MANAGED_XLW_H


