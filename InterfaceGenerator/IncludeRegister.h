//
//
//                            IncludeRegister.h
//
//
/*
    This is a singleton, its used to decide what extra files to include from xlwTest.cpp 
    Such a file should only be included if the type involved is used somewhere. 
    So we build a map of args to includes
    and a map of args to bools to check whether its been used.

    We pass back a set to ensure no argument duplication.
*/
/*
 Copyright (C) 2006 Mark Joshi
 
 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net
 
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/
#ifndef INCLUDE_REGISTER
#define INCLUDE_REGISTER

#include <set>
#include <map>
#include <string>
#include "Singleton.h"

class IncludeRegistry : public Singleton<IncludeRegistry>
{
public: 
    friend class Singleton<IncludeRegistry>;
    
    void Register(const std::string& arg, const std::string& include);
    void UseArg(const std::string& arg);

    std::set<std::string> GetIncludes() const; 

private:
    IncludeRegistry()
    {}
    IncludeRegistry(const IncludeRegistry&)
    {}

    std::map<std::string,std::string> ArgInclude;
    std::map<std::string, bool> ArgUsed;

};
#endif
