#ifndef DLL_H
#define DLL_H

#include <xlwDotNet.h>

//<xlw:libraryname=NonPassive


std::wstring //Gets the Address of the calling cell 
MyAddress(double x // x
);

std::wstring //Writes string to status bar
MessageInStatusBar(const std::wstring&  Message // The String 
);

double // 
GetPid();

#endif 
