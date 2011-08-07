//
/*
 Copyright (C) 2009 2010 2011 Narinder S Claire


 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include<cppinterface.h>
#include"../Objects/ObjectCache.h"
#include <iostream>
#include <sstream>

#ifdef _MSC_VER
#pragma warning (disable : 4996)
#endif


std::string ulToString(unsigned long n)
{
    std::ostringstream theStream;

    theStream << n;
    return theStream.str() ;
}

std::string stripTrailingHash(const std::string &theSource)
{
    size_t posHash = theSource.find('#');
    if(posHash==std::string::npos) return theSource;
    return theSource.substr(0,posHash);
}

void check(const std::string &theName)
{
    if(theName.find('#')==std::string::npos)
    {
        THROW_XLW("Character '#' not allowed in object name");
    }
}

std::string CreateObject(const CellMatrix &theObject)
{
    if(!theObject(0,0).IsAString() && !theObject(0,0).IsAWstring())
    {
        THROW_XLW("Expected value to be name of the object");
    }
    std::string theName = theObject(0,0).StringValue();

    ObjectCache::instance()[theName]=theObject;
    theName += "#";
    return theName + (ulToString(NumberCache::instance()[theName]++));
}

CellMatrix RetrieveObject(const std::string &theName)
{
    std::string theKey(stripTrailingHash(theName));
    if (ObjectCache::instance().find(theKey) == ObjectCache::instance().end())
    {
        THROW_XLW("Object not found in Cache");
    }
    return ObjectCache::instance()[theKey];

}

