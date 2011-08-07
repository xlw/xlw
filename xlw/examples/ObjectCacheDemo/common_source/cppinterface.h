
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

#ifndef TEST_H
#define TEST_H

#include "xlw/MyContainers.h"
#include <xlw/CellMatrix.h>
#include <xlw/DoubleOrNothing.h>
#include <xlw/ArgList.h>

using namespace xlw;

//<xlw:libraryname=ObjectCachDemo



std::string // Caches a CellMatrix. The first Cell must be the name
CreateObject(const CellMatrix &theObject // The Object to be cached
             );

CellMatrix  // Retrieves an object from the cache
RetrieveObject(const std::string &theName   // The Name of the object
               );


std::string // Caches a Discount Curve. The first parameter must be a the name
CreateDiscountCurve(const std::string & theCurveName // The name of the Dicsount curve
                    ,const MyMatrix &theDiscountCurve // A matrix of 2 columns. First column is dates and second column is discounts
             );

MyMatrix  // Retrieves a Discount Curve from the cache
RetrieveDiscountCurve(const std::string &theName   // The Name of the Discount Curve
               );

double  // Gets the discount factor from the given curve
Discount(const std::string &theName   // The Name of the Discount Curve
         ,double theDate              // The Date
         );



#endif
