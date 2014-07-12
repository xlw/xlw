#include <xlwDotNet.h>
using namespace System;
using namespace Runtime::InteropServices;
using namespace xlwDotNet;

inline std::wstring CLR2WCPP(String^ clrString) {
    System::IntPtr memHandle = Marshal::StringToHGlobalUni(clrString);
    std::wstring result =  (const wchar_t*)(memHandle.ToPointer());
    Marshal::FreeHGlobal(memHandle);
    return result;
}

std::wstring // Hello World
DLLEXPORT HelloWorld()
{
DOT_NET_EXCEL_BEGIN
        return (CLR2WCPP(Example::Class1::HelloWorld(
        )));
DOT_NET_EXCEL_END
}

