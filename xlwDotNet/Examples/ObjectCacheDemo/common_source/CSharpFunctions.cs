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
using System.Linq;
using xlwDotNet;
using xlwDotNet.xlwTypes;


namespace xlwObjectCachDemo
{
    public class Class1
    {

        public static string stripTrailingHash(string theSource)
        {
            if (!theSource.Contains('#'))
            {
                return theSource;
            }
            int posHash = theSource.IndexOf('#');
            return theSource.Substring(0, posHash);
        }

        [ExcelExport("Caches a CellMatrix. The first Cell must be the name")]
        public static string CreateObject(
            [Parameter("The Object to be cached")]  CellMatrix theObject)
        {
            if (!theObject[0, 0].IsAString)
            {
                throw new Exception("Expected value to be name of the object");
            }
            string theName = theObject[0, 0].StringValue();

            ObjectCache.Instance[theName] = theObject.Clone();
            if (!NumberCache.Instance.ContainsKey(theName))
            {
                NumberCache.Instance[theName] = 0;
            }


            return theName + "#" + (NumberCache.Instance[theName]++).ToString();
        }


        [ExcelExport("Retrieves an object from the cache")]
        public static CellMatrix RetrieveObject(
                            [Parameter("The Name of the object")]  string theName)
        {
            string theKey = stripTrailingHash(theName);
            if (!ObjectCache.Instance.ContainsKey(theKey))
            {
                throw new Exception("Object not found in Cache");
            }
            return ObjectCache.Instance[theKey];

        }

    }
}


