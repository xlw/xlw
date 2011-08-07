/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2011 Narinder Claire

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef OUTPUTTER_HELPER
#define OUTPUTTER_HELPER 
#include "Outputter.h"
#include "TypeRegister.h"
#include "IncludeRegister.h"
#include <sstream>
#include"OutputterHelper.h"

void PushBack(std::string& str, char c);
void AddLine(std::vector<char>& file, std::string line);
std::string strip(std::string in);
std::string getdir(std::string in);
void writeOutputFile(const std::string & fileName, const std::vector<char> &theData);


#endif //  OUTPUTTER_HELPER