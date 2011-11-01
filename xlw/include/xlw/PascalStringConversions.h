
/*
 Copyright (C) 2011  John Adcock

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef INC_PascalStringConversions_H
#define INC_PascalStringConversions_H

/*!
\file PascalStringConversions.h
\brief defines for conversion functions used when dealing with Excel strings
*/

// $Id$

#include <string>

#if defined(_MSC_VER)
#pragma once
#endif

namespace xlw {

    class PascalStringConversions
    {
    public:
        static char* PascalStringToString(const char* pascalString);
        static std::wstring PascalStringToWString(const char* pascalString);
        static char* StringToPascalString(const std::string& cString);
        static char* WStringToPascalString(const std::wstring& cString);
        static char* WPascalStringToString(const wchar_t* pascalString);
        static std::wstring WPascalStringToWString(const wchar_t* pascalString);
        static wchar_t* StringToWPascalString(const std::string& cString);
        static wchar_t* WStringToWPascalString(const std::wstring& cString);
        static char* PascalStringCopy(const char* pascalString);
        static wchar_t* WPascalStringCopy(const wchar_t* pascalString);
        static char* PascalStringCopyUsingNew(const char* pascalString);
        static wchar_t* WPascalStringCopyUsingNew(const wchar_t* pascalString);
    };

    class StringUtilities
    {
    public:
        static std::string getEnvironmentVariable(const std::string& variableName);
        static std::string getCurrentDirectory();
        static std::string toUpper(std::string inputString);
        static std::string toLower(std::string inputString);
        static void makeUpper(std::string& stringToChange);
        static void makeLower(std::string& stringToChange);
    };
}

#endif

