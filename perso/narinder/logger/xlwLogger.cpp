
#ifdef WIN32
#include "xlwLogger.h"

#include<ctime>

xlwLogger::xlwLogger(){
    theConsoleHandel= GetConsoleWindow();
    if(theConsoleHandel)FreeConsole();

    BOOL flag = AllocConsole();
    theConsoleHandel= GetConsoleWindow();
    theScreenHandel = GetStdHandle(STD_OUTPUT_HANDLE);
    wchar_t titlePtr[]=L" xlwLogger Window \0";
    
    SetConsoleTitle(LPCWSTR(titlePtr));

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
    WriteConsole(theScreenHandel,
                 theInnerStream.str().c_str(),
                 theInnerStream.str().size(),
                 &CharsWritten, 0);
    theInnerStream.str(EmptyString);
    
}
void xlwLogger::Display(const std::string& theLog ){
    WriteConsole(theScreenHandel,
                 theLog.c_str(),
                 theLog.size(),
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
    for(unsigned long i(0);i<8;i++)timeTemp[i]=wchar_t(timePtr[i+11]);
    timeTemp[8]=0;
    return timeTemp;
}


#endif
