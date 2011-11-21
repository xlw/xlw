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

#include <xlw/PascalStringConversions.h>
#include <xlw/TempMemory.h>
#include <xlw/macros.h>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <locale>

#ifndef WC_NO_BEST_FIT_CHARS
#define WC_NO_BEST_FIT_CHARS 0x00000400
#endif


char * xlw::PascalStringConversions::PascalStringToString(const char* pascalString)
{
    // Must use datatype unsigned char (BYTE) to process 0th byte
    // otherwise numbers greater than 128 are incorrect
    size_t n = static_cast<BYTE>(pascalString[0]);
    char* result = TempMemory::GetMemory<char>(n + 1);
    memcpy(result, pascalString + 1, n);
    result[n] = 0;
    return result;
}

std::wstring xlw::PascalStringConversions::PascalStringToWString(const char* pascalString)
{
    // Must use datatype unsigned char (BYTE) to process 0th byte
    // otherwise numbers greater than 128 are incorrect
    size_t n = static_cast<BYTE>(pascalString[0]);
    std::wstring result(n, L'\0');
    MultiByteToWideChar(CP_ACP, 0, pascalString + 1, (int)n, &result[0], (int)n);
    return result;
}

char* xlw::PascalStringConversions::StringToPascalString(const std::string& cString)
{
    size_t n(cString.length());

    if (n > 255)
    {
        std::cerr << XLW__HERE__ << "String truncated to 255 bytes" << std::endl;
        n = 255;
    }
    // One byte more for the string length (convention used by Excel)
    // and another so that the string is null terminated so that the
    // debugger sees it correctly
    LPSTR result = TempMemory::GetMemory<char>(n + 2);
    strncpy(result + 1, cString.c_str(), n);
    result[n + 1] = 0;
    result[0] = static_cast<BYTE>(n);
    return result;
}

char* xlw::PascalStringConversions::WStringToPascalString(const std::wstring& cString)
{
    size_t n(cString.length());

    if (n > 255)
    {
        std::cerr << XLW__HERE__ << "String truncated to 255 bytes" << std::endl;
        n = 255;
    }
    // One byte more for the string length (convention used by Excel)
    // and another so that the string is null terminated so that the
    // debugger sees it correctly
    LPSTR result = TempMemory::GetMemory<char>(n + 2);
    WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, cString.c_str(), (int)n, result + 1, (int)n, NULL, NULL);
    result[n + 1] = 0;
    result[0] = static_cast<BYTE>(n);
    return result;
}

char* xlw::PascalStringConversions::WPascalStringToString(const wchar_t* pascalString)
{
    size_t n = pascalString[0];
    char* result = TempMemory::GetMemory<char>(n + 1);
    result[n] = 0;
    if(n > 0)
    {
        WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, pascalString + 1, (int)n, result, (int)n, NULL, NULL);
    }
    return result;
}

std::wstring xlw::PascalStringConversions::WPascalStringToWString(const wchar_t* pascalString)
{
    // Must use datatype unsigned char (BYTE) to process 0th byte
    // otherwise numbers greater than 128 are incorrect
    size_t n = pascalString[0];
    std::wstring result(pascalString + 1, pascalString + 1 + n);
    return result;
}

wchar_t* xlw::PascalStringConversions::StringToWPascalString(const std::string& cString)
{
    size_t n(cString.length());

    if (n > 32767) {
        std::cerr << XLW__HERE__ << "String truncated to 32767 bytes" << std::endl;
        n = 32767;
    }

    // One byte more for the string length (convention used by Excel)
    // and another so that the string is null terminated so that the
    // debugger sees it correctly
    wchar_t* result  = TempMemory::GetMemory<wchar_t>(n+2);
    MultiByteToWideChar(CP_ACP, 0, cString.c_str(), (int)n, result + 1, (int)n);
    result[n + 1] = 0;
    result[0] = static_cast<XCHAR>(n);
    return result;
}

wchar_t* xlw::PascalStringConversions::WStringToWPascalString(const std::wstring& cString)
{
    size_t n(cString.length());

    if (n > 32766)
    {
        std::cerr << XLW__HERE__ << "String truncated to 32766 bytes" << std::endl;
        n = 32766;
    }
    // One byte more for the string length (convention used by Excel)
    // and another so that the string is null terminated so that the
    // debugger sees it correctly
    wchar_t* result = TempMemory::GetMemory<wchar_t>(n + 2);
    wcsncpy(result + 1, cString.c_str(), n);
    result[n + 1] = 0;
    result[0] = static_cast<wchar_t>(n);
    return result;
}


char* xlw::PascalStringConversions::PascalStringCopy(const char* pascalString)
{
    size_t n = static_cast<BYTE>(pascalString[0]);
    LPSTR result = TempMemory::GetMemory<char>(n + 2);
    memcpy(result, pascalString, n + 1);
    result[n + 1] = 0;
    return result;
}

wchar_t* xlw::PascalStringConversions::WPascalStringCopy(const wchar_t* pascalString)
{
    size_t n = static_cast<wchar_t>(pascalString[0]);
    wchar_t* result = TempMemory::GetMemory<wchar_t>(n + 2);
    memcpy(result, pascalString, (n + 1) * sizeof(wchar_t));
    result[n + 1] = 0;
    return result;
}

char* xlw::PascalStringConversions::PascalStringCopyUsingNew(const char* pascalString)
{
    size_t n = static_cast<BYTE>(pascalString[0]);
    LPSTR result = TempMemory::GetMemoryUsingNew<char>(n + 2);
    memcpy(result, pascalString, n + 1);
    result[n + 1] = 0;
    return result;
}

wchar_t* xlw::PascalStringConversions::WPascalStringCopyUsingNew(const wchar_t* pascalString)
{
    size_t n = static_cast<wchar_t>(pascalString[0]);
    wchar_t* result = TempMemory::GetMemoryUsingNew<wchar_t>(n + 2);
    memcpy(result, pascalString, (n + 1) * sizeof(wchar_t));
    result[n + 1] = 0;
    return result;
}

std::string xlw::StringUtilities::getEnvironmentVariable(const std::string& variableName)
{
    const DWORD bufferSize=4096;
    std::vector<char> result(bufferSize);
    DWORD dwRet = GetEnvironmentVariable(variableName.c_str(), &result[0], bufferSize);
    if(bufferSize < dwRet)
    {
        result.resize(dwRet);
        dwRet = GetEnvironmentVariable(variableName.c_str(), &result[0], dwRet);
    }
    if(!dwRet)
    {
        std::cerr << XLW__HERE__ <<" Could not obtain " << variableName << " Environment variable " <<  std::endl;
        return "";
    }
    return &result[0];
}

std::string xlw::StringUtilities::getCurrentDirectory()
{
    std::vector<char> result;
    DWORD dwRet = GetCurrentDirectory(0, 0);
    if(dwRet)
    {
        result.resize(dwRet);
        dwRet = GetCurrentDirectory(dwRet, &result[0]);
    }
    if(!dwRet)
    {
        std::cerr << XLW__HERE__ <<" Could not obtain Current directory " <<  std::endl;
        return "";
    }
    return &result[0];
}


std::string xlw::StringUtilities::toUpper(std::string inputString)
{
    makeUpper(inputString);
    return inputString;
}

std::string xlw::StringUtilities::toLower(std::string inputString)
{
    makeLower(inputString);
    return inputString;
}


void xlw::StringUtilities::makeUpper(std::string& stringToChange)
{
    std::transform(stringToChange.begin(),stringToChange.end(),stringToChange.begin(),(int(*)(int))std::toupper);
}

void xlw::StringUtilities::makeLower(std::string& stringToChange)
{
    std::transform(stringToChange.begin(),stringToChange.end(),stringToChange.begin(),(int(*)(int))std::tolower);
}

