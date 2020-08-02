/*
 Copyright (C) 2011 John Adcock
 Copyright (C) 2012 Narinder S Claire

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
using namespace System;
#include<xlw/xlw.h>
#include"managedCellMatrix.h"

std::string CLR2CPP(String^ clrString);

namespace xlwDotNet
{
    public ref class XlwExcel
    {

    public:
        XlwExcel()
        {
        }


        static property int version
        {
            int get()
            {
                return xlw::XlfExcel::Instance().excelVersion();
            }
        }

        static xlwTypes::CellMatrix^ RTD(String^ rtdServer, Int32 topicId)
        {
            // make sure everything is set up inside the library
            xlw::XlfExcel::Instance();
            xlw::XlfOper resultOper;
            xlw::XlfExcel::Instance().Call(xlfRtd, resultOper, 3, xlw::XlfOper(CLR2CPP(rtdServer)), xlw::XlfOper(), xlw::XlfOper(topicId));
            xlw::CellMatrix* resultMatrix(new xlw::CellMatrix(resultOper.AsCellMatrix()));
            return gcnew xlwTypes::CellMatrix((IntPtr)resultMatrix, true);
        }

		static ref class StatusBar
		{
		public:
			static property String^ message
			{
			      void set(String ^message)
				  {
					  xlw::XlfExcel::Instance();
					  xlw::XlfOper resultOper;
					  xlw::XlfServices.StatusBar = CLR2CPP(message);
				  }
			}

		};

			static property bool IsEscPressed
		{
			bool get()
			{
				xlw::XlfExcel::Instance();
				xlw::XlfOper ret;
				xlw::XlfExcel::Instance().Call(xlAbort, ret, 1, xlw::XlfOper(false));
				return ret.AsBool();
			}
		}
    };
}
