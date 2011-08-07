/*
 Copyright (C) 2011 Narinder S Claire
 Copyright (C) 2011 John Adcock

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifdef WIN32
#include "xlwLogger.h"
#include<ctime>
#include <iostream>

xlwLogger::xlwLogger(){
    theConsoleHandle= GetConsoleWindow();
    if(theConsoleHandle)
    {
        if(!FreeConsole())
        {
            // FIXME: lets see if problems is here
            std::cerr << "can't free console window" << std::endl;
        }
    }

    BOOL flag = AllocConsole();
    if(flag == 0)
    {
        // FIXME: update logic so that failure here is a real error
        std::cerr << "can't create console window" << std::endl;
    }
    theConsoleHandle= GetConsoleWindow();
    if(theConsoleHandle)
    {
        // FIXME: should throw here if we can't find a console by the time we get here
        std::cerr << "haven't got a console window" << std::endl;
    }
    theScreenHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    char titlePtr[]=" xlwLogger Window \0";

    SetConsoleTitle(titlePtr);

    // try and stop the user from being able to close the logging window
    HWND hWnd = FindWindow(NULL, titlePtr);
    if(hWnd)
    {
        RemoveMenu(GetSystemMenu(hWnd, FALSE), SC_CLOSE, MF_BYCOMMAND);
    }

    time(&theTime[0]);
    theInnerStream << " xlwLogger Initiated    "
                   << ctime(&theTime[0])
                   << " \n Code Compiled "
                   << __TIME__  << "  "
                   << __DATE__;
    Display();

    theTimeIndex=0;

}


void xlwLogger::Display(){
    WriteConsole(theScreenHandle,
                 theInnerStream.str().c_str(),
                 (DWORD)theInnerStream.str().size(),
                 &CharsWritten, 0);
    theInnerStream.str(EmptyString);

}
void xlwLogger::Display(const std::string& theLog ){
    WriteConsole(theScreenHandle,
                 theLog.c_str(),
                 (DWORD)theLog.size(),
                 &CharsWritten, 0);
}
double xlwLogger::GetTau() {
    theTimeIndex = 1-theTimeIndex;
    time(&theTime[theTimeIndex]);
    return difftime(theTime[theTimeIndex],theTime[1-theTimeIndex]);
}

const char* const xlwLogger::GetTime() {
    time_t tem(time(&theTime[2]));
    char * timePtr = asctime(gmtime(&tem));
    for(unsigned long i(0);i<8;i++)timeTemp[i]=char(timePtr[i+11]);
    timeTemp[8]=0;
    return timeTemp;
}


#endif
