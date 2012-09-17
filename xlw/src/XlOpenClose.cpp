
/*
Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte
Copyright (C) 2006 Mark Joshi
Copyright (C) 2009 2011 Narinder S Claire
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
#include <xlw/XlOpenClose.h>
#include <vector>
#include <xlw/Win32StreamBuf.h>
#include <xlw/XlFunctionRegistration.h>
#include <xlw/CellMatrix.h>
#include <xlw/TempMemory.h>
#include <xlw/XlfServices.h>
#include "PathUpdater.h"
#include<memory>
#include<string>

// redirect std::cerr at a global level to avoid
// losing the debugging info when xlAutoClose is called
// but Excel still can call the functions
static xlw::CerrBufferRedirector redirectCerr;

extern "C"
{

    long EXCEL_EXPORT xlAutoOpen()
    {
        try
        {
            xlw::XlfExcel::Instance();
            // ensure temporary memory can be created
            xlw::TempMemory::InitializeProcess();

            // when we load any dll's dynamically
            // we want to make sure we look in the
            // current directory
            // static so that this is only done once per process
            static xlw::PathUpdater updatePath;

            // Displays a message in the status bar.
            xlw::XlfServices.StatusBar="Registering library...";

            xlw::XLRegistration::ExcelFunctionRegistrationRegistry::Instance().DoTheRegistrations();

            // Clears the status bar.
            xlw::XlfServices.StatusBar.clear();

            xlw::MacroCache<xlw::Open>::Instance().ExecuteMacros();

            return 1;
        }
        catch(...)
        {
            return 0;
        }
    }

    static bool autoRemoveCalled = false;

    long EXCEL_EXPORT xlAutoClose()
    {
        try
        {
            std::cerr << XLW__HERE__ << "Releasing resources" << std::endl;
            xlw::MacroCache<xlw::Close>::Instance().ExecuteMacros();

            if(autoRemoveCalled)
            {
                // we can safely unregister the functions here as the user has unloaded the
                // xll and so won't expect to be able to use the functions
                xlw::XLRegistration::ExcelFunctionRegistrationRegistry::Instance().DoTheDeregistrations();
            }
            else
            {
                // note that we don't unregister the functions here
                // excel has some strange behaviour when exiting and can
                // call xlAutoClose before the user has been asked about the close
            }


            // if the user then cancels the close then we need to ensure we
            // have enough state to come back to life
            xlw::XlfExcel::DeleteInstance();

            // clear up any temporary memory used
            // but keep enough alive so that excel can still use
            // the functions
            xlw::TempMemory::TerminateProcess();
        }
        catch(...)
        {
            std::cerr << XLW__HERE__ << "Something bad happened in xlAutoClose" << std::endl;
        }
        return 1;
    }

    long EXCEL_EXPORT xlAutoRemove()
    {
        try
        {
            std::cerr << XLW__HERE__ << "Addin being unloaded" << std::endl;

            xlw::MacroCache<xlw::Remove>::Instance().ExecuteMacros();

            // tell auto close we've been called so that we can call deregister
            autoRemoveCalled = true;
        }
        catch(...)
        {
            std::cerr << XLW__HERE__ << "Something bad happened in xlAutoRemove" << std::endl;
        }

        return 1;
    }

}


