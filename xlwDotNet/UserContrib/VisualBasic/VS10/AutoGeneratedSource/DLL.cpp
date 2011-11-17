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
        return (CLR2WCPP(Template::Example::Class1::HelloWorld(
        )));
DOT_NET_EXCEL_END
}

CellMatrix // Echo a matrix
DLLEXPORT EchoMatrix(const CellMatrix& theMatrix)
{
DOT_NET_EXCEL_BEGIN
        return *(CellMatrix*)(xlwTypes::CellMatrix::getInner(Template::Example::Class1::EchoMatrix(
                gcnew xlwTypes::CellMatrix(IntPtr((void*)&theMatrix))
        )));
DOT_NET_EXCEL_END
}

