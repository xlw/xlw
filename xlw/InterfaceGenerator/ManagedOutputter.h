/*
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

#ifndef MANAGED_OUTPUTTER_H
#define MANAGED_OUTPUTTER_H

#include"OutputterHelper.h"

void OutputFileCreatorMan(std::vector<FunctionDescription>& functionVector,
                                      std::string inputFileName,
                                      std::string LibraryName,
                                      std::vector<char> &outputVector_h,
                                      std::vector<char> &outputVector_cpp
                                       );

#endif //MANAGED_OUTPUTTER_H