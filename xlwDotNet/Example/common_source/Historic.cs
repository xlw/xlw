/*
 Copyright (C) 2008 2009  Narinder S Claire

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
using System.Collections.Generic;
using System.Text;
using System.Net;
using xlwDotNet;
using xlwDotNet.xlwTypes;

namespace Example
{
    // Demonstrates some useful features about C#
    // that are difficult to implement in C++ 
    // at least for me 
    public class Historic
    {
        [ExcelExport("Obtains historial market data from yahoo")]
        public static CellMatrix GetHistoricDataFromYahoo(
                   [Parameter("Yahoo Symbol")] string symbol,
                   [Parameter("Begin Date")]   double beginDate,
                   [Parameter("End Date")]     double endDate
            )
        {
            DateTime begin = DateTime.FromOADate(beginDate);
            DateTime end = DateTime.FromOADate(endDate);

            string yahooURL =
               @"http://ichart.finance.yahoo.com/table.csv?s=" + 
               symbol + 
               @"&a=" +
               (begin.Month-1).ToString() +
               @"&b=" +
               begin.Day.ToString() +
               @"&c=" +
               begin.Year.ToString() + 
               @"&d=" +
               (end.Month-1).ToString() +
               @"&e=" +
               end.Day.ToString() +
               @"&f=" +
               end.Year.ToString() +
               @"&g=d&ignore=.csv";

            string historicData = "";
            WebClient webConnection = new WebClient();
            try
            {
                historicData = webConnection.DownloadString(yahooURL);
    
            }
            catch (WebException someWebException)
            {
                throw someWebException;
            }
            finally
            {
                webConnection.Dispose();
            }
            
            historicData = historicData.Replace("\r", "");
            string[] rows = historicData.Split('\n');
            string[] headings = rows[0].Split(',');

            CellMatrix excelData = new CellMatrix(1,headings.Length);
            for (int i = 0; i < headings.Length; ++i)
            {
                excelData[0, i] = new CellValue(headings[i]);
            }
            for (int i = 1; i < rows.Length; ++i)
            {
                string[] thisRow = rows[i].Split(',');
                if (thisRow.Length == headings.Length)
                {
                    CellMatrix row = new CellMatrix(1, headings.Length);
                    row[0, 0] = new CellValue(DateTime.Parse(thisRow[0]).ToOADate());
                    for (int j = 1; j < headings.Length; ++j)
                    {
                        row[0, j] = new CellValue(double.Parse(thisRow[j]));
                    }
                    excelData.PushBottom(row);
                }
            }


            return excelData;




        }
    }
}
