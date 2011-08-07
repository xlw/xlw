/*
 Copyright (C) 2008 2009  Narinder S Claire
 Copyright (C) 2011 John Adcock

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
using namespace System;
using namespace Runtime::InteropServices;

#include<string>

std::string CLR2CPP(String^ clrString)
{
    System::IntPtr memHandle = Marshal::StringToHGlobalAnsi(clrString);
    std::string result =  (const char*)(memHandle.ToPointer());
    Marshal::FreeHGlobal(memHandle);
    return result;
}
