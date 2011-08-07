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
#ifndef OBJECT_CAHCE_HEADER
#define OBJECT_CAHCE_HEADER

#include<map>
#include<xlw/ArgList.h>
#include"singleton.h"


class ObjectCache : public singleton<ObjectCache>,public std::map<std::string,CellMatrix>
{
};

class NumberCache : public singleton<NumberCache>,public std::map<std::string,unsigned long>
{
};

class DiscountCurveCache : public singleton<DiscountCurveCache>,public std::map<std::string,MyMatrix>
{
};




#endif