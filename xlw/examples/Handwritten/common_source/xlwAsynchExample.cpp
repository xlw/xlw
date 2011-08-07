
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

    // demonstrate asynchronous functions
    // this is function that will be called
    // it will be called as normal in all versions up to 2007
    // in Excel 2010 it will be called asynchronously
    LPXLFOPER EXCEL_EXPORT xlSlowConcat(LPXLFOPER inStr1, LPXLFOPER inStr2) {
        EXCEL_BEGIN;
        // pretend something really slow happens
        Sleep(5000);
        XlfOper xlStr1(inStr1);
        XlfOper xlStr2(inStr2);

        // Converts the 2 strings.
        std::wstring str1 = xlStr1.AsWstring();
        std::wstring str2 = xlStr2.AsWstring();
        // Returns the concatenation of the 2 string as an XlfOper.
        std::wstring ret = str1 + str2;
        return XlfOper(ret);
        EXCEL_END;
    }

    // thread that wraps the normal call
    // needs to delete the parameter memory once done
    DWORD WINAPI xlSlowConcatThread(LPVOID args)
    {
        XLFOPER* opers = (XLFOPER*)args;
        try
        {
            LPXLFOPER result = xlSlowConcat(&opers[1], &opers[2]);
            XlfExcel::Instance().Call(xlAsyncReturn, 0, 2, &opers[0], result);
        }
        catch(std::exception& e)
        {
            XlfOper result(e.what());
            XlfExcel::Instance().Call(xlAsyncReturn, 0, 2, &opers[0], result);
        }
        catch(...)
        {
            XlfOper result(XlfOper::Error(xlerrNA));
            XlfExcel::Instance().Call(xlAsyncReturn, 0, 2, &opers[0], result);
        }

        xlw::impl::XlfOperProperties<LPXLFOPER>::freeCreatedUsingNew(&opers[1]);
        xlw::impl::XlfOperProperties<LPXLFOPER>::freeCreatedUsingNew(&opers[2]);
        TempMemory::FreeMemoryCreatedUsingNew(opers);
        return 0;
    }

    // this function is called in Excel 2010 to set-up calculation
    void EXCEL_EXPORT xlSlowConcatSync(LPXLFOPER inStr1, LPXLFOPER inStr2, LPXLFOPER asyncId) {
        try
        {
            if (XlfExcel::Instance().IsCalledByFuncWiz())
            {
                THROW_XLW("In Function Wizard");
            }

            XLFOPER* opers = TempMemory::GetMemoryUsingNew<XLFOPER>(3);
            xlw::impl::XlfOperProperties<LPXLFOPER>::copyUsingNew(asyncId, &opers[0]);
            xlw::impl::XlfOperProperties<LPXLFOPER>::copyUsingNew(inStr1, &opers[1]);
            xlw::impl::XlfOperProperties<LPXLFOPER>::copyUsingNew(inStr2, &opers[2]);

            if (CreateThread(NULL, 0, xlSlowConcatThread, opers, 0, NULL) == NULL)
            {
                xlw::impl::XlfOperProperties<LPXLFOPER>::freeCreatedUsingNew(&opers[1]);
                xlw::impl::XlfOperProperties<LPXLFOPER>::freeCreatedUsingNew(&opers[2]);
                TempMemory::FreeMemoryCreatedUsingNew(opers);
                THROW_XLW("Can't create thread");
            }
            return;
        }
        catch(std::exception& e)
        {
            XlfOper result(e.what());
            XlfOper asyncIdOper(asyncId);
            XlfExcel::Instance().Call(xlAsyncReturn, 0, 2, asyncIdOper, result);
        }
        catch(...)
        {
            XlfOper result(XlfOper::Error(xlerrNA));
            XlfOper asyncIdOper(asyncId);
            XlfExcel::Instance().Call(xlAsyncReturn, 0, 2, asyncIdOper, result);
        }
    }

}

namespace {

    XLRegistration::Arg SlowConcatArgs[] = {
        { "string1", "First String", "XLF_OPER" },
        { "string2", "First String", "XLF_OPER" }
    };

    XLRegistration::XLFunctionRegistrationHelper registerSlowConcat(
        "xlSlowConcat", "SlowConcat", "Concatenate a string really slowly to test asynchronous behaviour",
        "xlw Example", SlowConcatArgs, 2,
        false, false, "", "", true);

}
