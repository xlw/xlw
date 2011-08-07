#ifndef PAPA_LOGGER_HEADER_FILE
#define PAPA_LOGGER_HEADER_FILE

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

    std::wostringstream theInnerStream;
    std::wstring theInnerString;
    HWND theConsoleHandel;
    HANDLE theScreenHandel;
    DWORD CharsWritten;
    time_t theTime[3];
    char timeTemp[26];
    unsigned long theTimeIndex;
    std::wstring EmptyString;

};



// THE MACROS
#define LOGHEADER  << "\n\n  " << (xlwLogger::instance().GetTime()) << " - " \
                    __FILE__ << "   " << __LINE__ << "\n"
  
#define _LOGGER  xlwLogger::instance() LOGHEADER


#endif

#endif


