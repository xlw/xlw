/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte

 This file is part of xlw, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 xlw is free software: you can redistribute it and/or modify it under the
 terms of the xlw license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/


// $Id$

#include <xlw/xlw.h>

extern "C"
{

  LPXLOPER EXCEL_EXPORT xlCirc(XlfOper xlDiam)
  {
    EXCEL_BEGIN;
    // Converts d to a double.
    double ret=xlDiam.AsDouble();
    // Multiplies it.
    ret *= 3.14159;
    // Returns the result as a XlfOper.
    return XlfOper(ret);
    EXCEL_END;
  }

  LPXLOPER EXCEL_EXPORT xlConcat(XlfOper xlStr1, XlfOper xlStr2)
  {
    EXCEL_BEGIN;
    // Converts the 2 strings.
    std::string str1 = xlStr1.AsString();
    std::string str2 = xlStr2.AsString();
    // Returns the concatenation of the 2 string as a XlfOper.
    std::string ret = str1+str2;
    return XlfOper(ret.c_str());
    EXCEL_END;
  }

  LPXLOPER EXCEL_EXPORT xlStats(XlfOper xlTargetRange)
  {
    EXCEL_BEGIN;
    XlfRef target = xlTargetRange.AsRef();
    // Initialization of the counter variables.
    size_t i,j;
    // Size of the range referenced.
    size_t n = target.GetNbRows();
    size_t m = target.GetNbCols();
    size_t popSize = n*m;
    // Temporary variables.
    double averageTmp = 0.0;
    double varianceTmp = 0.0;

    // XlfExcel::Coerce method (internally called) will return to Excel
    // if one of the cell was invalidated and need to be recalculated.
    // Excel will calculate this cell and call again our function.
    // Thus we copy first all the data to avoid to partially compute the
    // average for nothing since one of the cell might be uncalculated.
    double * temp = 0;
    // Allocate a buffer where to copy the values.
    temp = new double[popSize];
    try
    {
      for (i = 0; i < n; ++i)
        for (j = 0; j < m; ++j)
        {
          // copy all values.
          temp[i*m+j] = target(i,j).AsDouble();
        }
      // All cells are copied. We do the actual work.
      for (i = 0; i < popSize; ++i)
      {
        // sums the values.
        averageTmp += temp[i];
        // sums the squared values.
        varianceTmp += temp[i] * temp[i];
      }
    }
    // Tidy up buffer if something wrong occurs.
    catch(...)
    {
      // should be safe.
      delete[] temp;
      throw;
    }
    // Tidy up buffer if nothing wrong occurs.
    delete[] temp;
    // Initialization of the resultArray.
    double resultArray[2];
    // compute average.
    double& average = resultArray[0];
    average = averageTmp / popSize;
    // compute variance
    double& variance = resultArray[1];
    variance = varianceTmp / popSize - average * average;
    // Create the XlfOper returned with the resultArray containing the values.
    return XlfOper(1,2,resultArray);
    EXCEL_END;
  }

  long EXCEL_EXPORT xlAutoOpen()
  {
//    EXCEL_BEGIN;

    // Displays a message in the status bar.
    XlfExcel::Instance().SendMessage("Registering library...");

    // Registers the first function xlCirc.
    // Variable description of type R (default).
    XlfArgDesc diameter("diameter","Diameter of the circle");
    // xlCirc function description function as Circ.
    XlfFuncDesc circ("xlCirc","Circ","Computes the circumference of a circle","xlw Example");
    // Set the diameter argument definition for circ.
    circ.SetArguments(diameter);
    // Registers the function circ.
    circ.Register();


    // Registers the second function xlConcat.
    // Argument descriptions.
    XlfArgDesc str1("string1","First string");
    XlfArgDesc str2("string2","Second string");
    // xlConcat function description as concat.
    XlfFuncDesc concat("xlConcat","Concat","Concatenate two strings in one","xlw Example");
    // Set the arguments for the function. Note how you create a XlfArgDescList from
    // two or more XlfArgDesc (operator+). You can not push the XlfArgDesc one by one.
    concat.SetArguments(str1+str2);
    // Registers the concat function.
    concat.Register();


    // Registers the third function xlStats.
    // Argument descriptions.
    XlfArgDesc pop("Population","Target range containing the population");
    // xlStats Function description
    XlfFuncDesc stats("xlStats","Stats","returns a (1x2) range containing the average and the variance of a numeric population","xlw Example");
    // Sets the arguments for the function.
    stats.SetArguments(pop);
    // Registers the stats function.
    stats.Register();

    // Clears the status bar.
    XlfExcel::Instance().SendMessage();
    return 1;

//    EXCEL_END;
  }

}
