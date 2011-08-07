//
//
//                                                                IncludeRegistry.cpp
//
//
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
#include "IncludeRegister.h"

void IncludeRegistry::Register(const std::string& arg, const std::string& include)
{
    if (include =="")
        return;

    ArgInclude.insert(std::make_pair(arg,include));
    ArgUsed.insert(std::make_pair(arg,false));
}

std::set<std::string> IncludeRegistry::GetIncludes() const
{
    std::set<std::string> includes;

    for (std::map<std::string,bool>::const_iterator it = ArgUsed.begin(); it!=ArgUsed.end(); ++it)
    {
        if (it->second)
            includes.insert(ArgInclude.find(it->first)->second);
    }

    return includes;
}

void IncludeRegistry::UseArg(const std::string& arg)
{
    std::map<std::string,bool>::iterator it = ArgUsed.find(arg);
    if (it != ArgUsed.end())
        it->second =true;
}
