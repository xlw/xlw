/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2011 Narinder S Claire

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef FUNCTIONIZER_H
#define FUNCTIONIZER_H

#include "Tokenizer.h"
#include "FunctionModel.h"
#include <vector>

void splitWords(const std::string&theSentence, std::vector<std::string> & theWords);
std::vector<FunctionModel> ConvertToFunctionModel(const std::vector<Token>& input,
                                                  std::string& LibraryName,
                                                  std::vector<std::string> &openMethods, 
                                                  std::vector<std::string> &closeMethods);



#endif
