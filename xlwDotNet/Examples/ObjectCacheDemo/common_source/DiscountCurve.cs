
/*
 Copyright (C) 2012  Narinder S Claire

 This file is part of XLWDOTNET, a free-software/open-source C# wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 XLWDOTNET is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net
 
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/


using System;
using xlwDotNet;
using xlwDotNet.xlwTypes;

namespace xlwObjectCachDemo
{
    public static class DiscountCurve
    {
        
        [ExcelExport("Caches a Discount Curve. The first parameter must be a the name")]
        public static string CreateDiscountCurve(
                                 [Parameter("The name of the Dicsount curve")]  string theCurveName,
                                 [Parameter("A matrix of 2 columns. First column is dates and second column is discounts")]  MyMatrix theDiscountCurve
             )
        {
            if (theDiscountCurve.columns != 2)
            {
                throw new Exception("Discount curve must have 2 columns");
            }
            if (theDiscountCurve[0, 0] < 0.0)
            {
                throw new Exception("Discount curve dates must be non-negative");
            }
            for (int i = 1; i < theDiscountCurve.rows; ++i)
            {
                if (theDiscountCurve[i, 0] <= theDiscountCurve[i - 1, 0])
                {
                    throw new Exception("Dates in Discount Curve must be strictly increasing");
                }
            }


            DiscountCurveCache.Instance[theCurveName] = theDiscountCurve.Clone();
            string theName = theCurveName;
            if (!NumberCache.Instance.ContainsKey(theCurveName))
            {
                NumberCache.Instance[theCurveName] = 0;
            }


            return theName + "#" + (NumberCache.Instance[theCurveName]++).ToString();
        }

        [ExcelExport("Retrieves a Discount Curve from the cache")]
        public static MyMatrix RetrieveDiscountCurve(
                             [Parameter("The Name of the Discount Curve")]  string theName
               )
        {
            string theKey = Class1.stripTrailingHash(theName);
            if (!DiscountCurveCache.Instance.ContainsKey(theKey))
            {
                throw new Exception("Discount Curve not found in Cache");
            }
            return DiscountCurveCache.Instance[theKey];
        }

        [ExcelExport("Gets the discount factor from the given curve")]
        public static double Discount(
                     [Parameter("The Name of the Discount Curve")]  string theName,
                     [Parameter("The Date")]  double theDate
                 )
        {
            string theKey = Class1.stripTrailingHash(theName);
            if (!DiscountCurveCache.Instance.ContainsKey(theKey))
            {
                throw new Exception("Discount Curve not found in Cache");
            }

            MyMatrix theCurve = DiscountCurveCache.Instance[theKey];
            int n = theCurve.rows;
            if (theDate <= theCurve[0, 0]) return theCurve[0, 1];
            if (theDate >= theCurve[n - 1, 0]) return theCurve[n - 1, 1];

            int i = 1;
            while (theCurve[i, 0] < theDate)
            {
                ++i;
            }

            double upper = Math.Log(theCurve[i, 1]);
            double lower = Math.Log(theCurve[i - 1, 1]);

            double upperCoeff = theDate - theCurve[i - 1, 0];
            double lowerCoeff = theCurve[i, 0] - theDate;

            return Math.Exp((upperCoeff * upper + lowerCoeff * lower) / (theCurve[i, 0] - theCurve[i - 1, 0]));

        }


    }
}
