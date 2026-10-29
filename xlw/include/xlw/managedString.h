#ifndef XLW_MANAGED_STRING_H
#define XLW_MANAGED_STRING_H

#include <string>

inline std::string CLR2CPP(System::String^ clrString)
{
    System::IntPtr memHandle =
        System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(clrString);
    std::string result;
    try
    {
        result = static_cast<const char*>(memHandle.ToPointer());
    }
    catch (...)
    {
        System::Runtime::InteropServices::Marshal::FreeHGlobal(memHandle);
        throw;
    }
    System::Runtime::InteropServices::Marshal::FreeHGlobal(memHandle);
    return result;
}

inline std::wstring CLR2WCPP(System::String^ clrString)
{
    System::IntPtr memHandle =
        System::Runtime::InteropServices::Marshal::StringToHGlobalUni(clrString);
    std::wstring result;
    try
    {
        result = static_cast<const wchar_t*>(memHandle.ToPointer());
    }
    catch (...)
    {
        System::Runtime::InteropServices::Marshal::FreeHGlobal(memHandle);
        throw;
    }
    System::Runtime::InteropServices::Marshal::FreeHGlobal(memHandle);
    return result;
}

#endif
