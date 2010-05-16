#include <xlwDotNet.h>
using namespace System;
using namespace Runtime::InteropServices;
using namespace xlwDotNet;

std::wstring //Gets the Address of the calling cell 
 DLLEXPORT MyAddress(double x)
{
DOT_NET_EXCEL_BEGIN 
        return (const wchar_t*)(Marshal::StringToHGlobalUni(Example::Class1::MyAddress(
                x
        )).ToPointer());
DOT_NET_EXCEL_END
}
std::wstring //Writes string to status bar
 DLLEXPORT MessageInStatusBar(const std::wstring&  Message)
{
DOT_NET_EXCEL_BEGIN 
        return (const wchar_t*)(Marshal::StringToHGlobalUni(Example::Class1::MessageInStatusBar(
                 gcnew String(Message.c_str())
        )).ToPointer());
DOT_NET_EXCEL_END
}
double // 
 DLLEXPORT GetPid()
{
DOT_NET_EXCEL_BEGIN 
        return Example::Class1::GetPid(
        );
DOT_NET_EXCEL_END
}
