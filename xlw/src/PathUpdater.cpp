
/*
Copyright (C) 2009 Narinder S Claire
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

#include <xlw/XlfWindows.h>

#include "PathUpdater.h"
#include <xlw/xlw.h>
#include <vector>
#include <xlw/TempMemory.h>
#include <xlw/XlfServices.h>
#include<memory>
#include<string>

xlw::PathUpdater::PathUpdater()
{
    MEMORY_BASIC_INFORMATION theInfo ;
    HMODULE theHandle = NULL;
    char theDLLPathChar [MAX_PATH + 1] = "";
    DWORD dwRet = 0;
    std::string originalPathValue(StringUtilities::getEnvironmentVariable("PATH"));
    bool ok(!originalPathValue.empty());

    dwRet = static_cast<DWORD>(VirtualQuery (((LPCVOID)this), &theInfo,(static_cast<DWORD> (sizeof (MEMORY_BASIC_INFORMATION)))));
    if (dwRet)
    {
        theHandle = ((HMODULE) (theInfo.AllocationBase));
        GetModuleFileName (theHandle, theDLLPathChar , MAX_PATH);
        xlw::XlfServices.StatusBar = theDLLPathChar;
    }
    else
    {
        ok = false;
        std::cerr << XLW__HERE__ <<" Could not attain path of DLL" << std::endl;
    }
    if(ok)
    {
        std::string theDLLPath(theDLLPathChar);
        std::string newPathValue(originalPathValue);
        std::string::size_type pos = theDLLPath.find_last_of("\\");
        newPathValue+= ";"+theDLLPath.substr(0,pos);

        if (!SetEnvironmentVariable("Path", newPathValue.c_str()))
        {
            std::cerr << XLW__HERE__ << " SetEnvironmentVariable failed to set PATH" << std::endl;
            ok = false;
        }
        else
        {
            std::cerr << XLW__HERE__ << " PATH set successfully " << std::endl;
        }
    }
    if(!ok)
    {
        std::cerr << XLW__HERE__ << " Warning: Unable to initialise PATH to directory of library " << std::endl;
    }
}

xlw::PathUpdater::~PathUpdater()
{
}
