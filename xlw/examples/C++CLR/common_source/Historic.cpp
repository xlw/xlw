/*
 Copyright (C) 2011  Narinder S Claire

 XLWDOTNET is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

// To avoid name clashes with windows headers need
// to include the c++ stuff first
#include <xlw/Xlw.h>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::Net;
using namespace Runtime::InteropServices;


std::string CLR2CPP(String^ clrString);

String^ CPP2CLR(const std::string &cppString);

xlw::CellMatrix // Obtains historial market data from yahoo
GetHistoricDataFromYahoo(
                          std::string  symbol // Yahoo Symbol
                         ,DateTime begin // Begin Date
                         ,DateTime end //End Date
                         )
{
    
            String^ yahooURL = gcnew String (
               CPP2CLR(std::string("http://ichart.finance.yahoo.com/table.csv?s=")) +
               CPP2CLR(symbol) +
               "&a=" +
               (begin.Month-1).ToString() +
               "&b=" +
               begin.Day.ToString() +
               "&c=" +
               begin.Year.ToString() +
               "&d=" +
               (end.Month-1).ToString() +
               "&e=" +
               end.Day.ToString() +
               "&f=" +
               end.Year.ToString() +
               "&g=d&ignore=.csv");

            String^ historicData = "";
            WebClient^ webConnection = gcnew WebClient();
            try
            {
                historicData = webConnection->DownloadString(yahooURL);

            }
            catch (WebException^ someWebException)
            {
                throw someWebException;
            }


            historicData = historicData->Replace("\r", "");
            array<String^>^ rows = historicData->Split('\n');
            array<String^>^ headings = rows[0]->Split(',');

            xlw::CellMatrix excelData(1,headings->Length);
            for (int i = 0; i < headings->Length; ++i)
            {
                excelData(0, i) = CLR2CPP(headings[i]);
            }
            for (int i = 1; i < rows->Length; ++i)
            {
                array<String^>^ thisRow = rows[i]->Split(',');
                if (thisRow->Length == headings->Length)
                {
                    xlw::CellMatrix row = xlw::CellMatrix(1, headings->Length);
                    row(0, 0) = DateTime::Parse(thisRow[0]).ToOADate();
                    for (int j = 1; j < headings->Length; ++j)
                    {
                        row(0, j) = Double::Parse(thisRow[j]);
                    }
                    excelData.PushBottom(row);
                }
            }

            return excelData;
}


