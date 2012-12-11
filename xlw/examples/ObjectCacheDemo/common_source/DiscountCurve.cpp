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
#include <cmath>

std::string ulToString(unsigned long n);
std::string stripTrailingHash(const std::string &theSource);
void check(const std::string &theName);

std::string // Caches a Discount Curve. The first parameter must be a the name
CreateDiscountCurve(const std::string & theCurveName // The name of the Dicsount curve
                    ,const MyMatrix &theDiscountCurve // A matrix of 2 columns. First column is dates and second column is discounts
             )
{
    if(theDiscountCurve.columns()!=2)
    {
        THROW_XLW("Discount curve must have 2 columns");
    }
    if(theDiscountCurve[0][0]<0.0)
    {
        THROW_XLW("Discount curve dates must be non-negative");
    }
    for(size_t i(1);i<theDiscountCurve.rows(); ++i)
    {
        if(theDiscountCurve[i][0]<=theDiscountCurve[i-1][0])
        {
            THROW_XLW("Dates in Discount Curve must be strictly increasing");
        }
    }


    DiscountCurveCache::instance().insert(std::make_pair(theCurveName,theDiscountCurve));
    std::string theName(theCurveName);
    theName += "#";
    return theName + (ulToString(NumberCache::instance()[theCurveName]++));
}

MyMatrix  // Retrieves a Discount Curve from the cache
RetrieveDiscountCurve(const std::string &theName   // The Name of the Discount Curve
               )
{
    std::string theKey(stripTrailingHash(theName));
    if (DiscountCurveCache::instance().find(theKey) == DiscountCurveCache::instance().end())
    {
        THROW_XLW("Discount Curve not found in Cache");
    }
    return DiscountCurveCache::instance()[theKey];
}

double  // Gets the discount factor from the given curve
Discount(const std::string &theName   // The Name of the Discount Curve
         ,double theDate              // The Date
         )
{
    std::string theKey(stripTrailingHash(theName));
    if (DiscountCurveCache::instance().find(theKey) == DiscountCurveCache::instance().end())
    {
        THROW_XLW("Discount Curve not found in Cache");
    }

    const MyMatrix &theCurve = DiscountCurveCache::instance()[theKey];
    size_t n(theCurve.rows());
    if(theDate<=theCurve[0][0]) return theCurve[0][1];
    if(theDate>=theCurve[n-1][0]) return theCurve[n-1][1];

    size_t i=1;
    while(theCurve[i][0]<theDate)
    {
        ++i;
    }

    double upper(std::log(theCurve[i][1]));
    double lower(std::log(theCurve[i-1][1]));

    double upperCoeff(theDate - theCurve[i-1][0]);
    double lowerCoeff(theCurve[i][0] - theDate);

    return std::exp((upperCoeff * upper  + lowerCoeff * lower) / (theCurve[i][0] -theCurve[i-1][0]));

}
