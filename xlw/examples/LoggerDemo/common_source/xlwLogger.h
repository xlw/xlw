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



#ifndef LOGGER_HEADER_FILE
#define LOGGER_HEADER_FILE

#ifdef WIN32

#ifndef _WIN32_WINNT 
#define _WIN32_WINNT 0x0501
#endif
#ifndef WINVER 
#define WINVER 0x0501
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif


#include<Windows.h>
#include<string>
#include<sstream>
#include<fstream>
#include<ctime>

class xlwLogger {
public :
    static xlwLogger & instance(){static xlwLogger theLogger ;return theLogger;}

    template<class type>
        xlwLogger & operator<<(type theLog){theInnerStream << theLog;Display();return *this;} 

    double GetTau();
    const char* const GetTime();
    
private:
    xlwLogger();
    xlwLogger(const xlwLogger& pl){}
    void Display();
    void Display(const std::string &);

    std::ostringstream theInnerStream;
    std::string theInnerString;
    HWND theConsoleHandle;
    HANDLE theScreenHandle;
    DWORD CharsWritten;
    time_t theTime[3];
    char timeTemp[26];
    unsigned long theTimeIndex;
    std::string EmptyString;

};



// THE MACROS
#define LOGHEADER  << "\n\n  " << (xlwLogger::instance().GetTime()) << " - " \
                    __FILE__ << "   " << __LINE__ << "\n"
  
#define _LOGGER  xlwLogger::instance() LOGHEADER


#endif

#endif


